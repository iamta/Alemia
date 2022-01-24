#!/usr/bin/env python3

from flask import Flask, request, jsonify
from flask_cors import CORS
from Crypto.Hash import MD5
from threading import Thread
import pandas
import zipfile
import os
import time
import warnings
import feature_extraction
from preprocessor import Preprocessor
from train import Train, Predictor

DOWNLOAD_DIRECTORY = "uploads"
EXTRACTION_DIRECTORY = "../data/raw/train"
GRADES_CSV_FILENAME = "../data/grades.csv"
INIT_DATASET = False
TRAIN_MODEL = True

last_student_scanned = None
preprocessor = None
predictor = None

# Create the Flask web app
app = Flask(__name__)
CORS(app)


# Default route
@app.route("/")
def default_route():
    return "Alemia API\n"


# Prediction route
@app.route("/predict", methods=["POST"])
def predict_route():

    global last_student_scanned, preprocessor, predictor

    # Get arguments
    uploaded_file = request.files["file"]

    # Generate a filename and save the file locally
    unique_filename = uploaded_file.filename + str(time.time())
    unique_filename = MD5.new(unique_filename.encode("utf-8")).hexdigest()
    last_student_scanned = unique_filename
    full_path = os.path.join(DOWNLOAD_DIRECTORY, unique_filename + ".zip")
    uploaded_file.save(full_path)

    # Extract the uploaded archive
    extraction_full_path = os.path.join(EXTRACTION_DIRECTORY, unique_filename)
    os.makedirs(extraction_full_path)
    with zipfile.ZipFile(full_path, "r") as zip_file:
        zip_file.extractall(extraction_full_path)

    # Get features
    print(extraction_full_path)
    features = feature_extraction.retrain_data_one(extraction_full_path + "/")
    features = preprocessor.transform_entry(features)

    # Predict the grade
    grade = predictor.predict([features])[0]
    grade = round(grade, 2)

    # Dump the grade into the specific CSV file
    grades_df = pandas.read_csv(GRADES_CSV_FILENAME)
    grades_df.loc[len(grades_df.index)] = [last_student_scanned, grade]
    grades_df = grades_df[["label", "grade"]]
    grades_df.to_csv(GRADES_CSV_FILENAME, index=False)

    # Return a result
    result = {"predicted_grade": grade}
    return jsonify(result)


# Prediction route for multiple files
@app.route("/predict_multiple", methods=["POST"])
def predict_multiple_route():

    global last_student_scanned, preprocessor, predictor

    # Get arguments
    uploaded_file = request.files["file"]

    # Generate a filename and save the file locally
    unique_filename = uploaded_file.filename + str(time.time())
    unique_filename = MD5.new(unique_filename.encode("utf-8")).hexdigest()
    last_student_scanned = unique_filename
    full_path = os.path.join(DOWNLOAD_DIRECTORY, unique_filename + ".zip")
    uploaded_file.save(full_path)

    # Extract the uploaded archive
    extraction_full_path = os.path.join(EXTRACTION_DIRECTORY, unique_filename)
    os.makedirs(extraction_full_path)

    grade_list = []

    with zipfile.ZipFile(full_path, "r") as zip_file:
        zip_file.extractall(extraction_full_path)

        dirs = list(set([os.path.dirname(x) for x in zip_file.namelist()]))
        topdirs = [os.path.split(x)[0] for x in dirs]

        mylist = []
        for elem in topdirs:
            if elem.count('/') == 2:
                mylist.append(elem)

        mylist.sort()
        for x in mylist:
            # Get features
            features = feature_extraction.retrain_data_one(extraction_full_path + "/" + x + "/")
            features = preprocessor.transform_entry(features)

            # Predict the grade
            grade = predictor.predict([features])[0]
            grade = round(grade, 2)

            # Dump the grade into the specific CSV file
            grades_df = pandas.read_csv(GRADES_CSV_FILENAME)
            grades_df.loc[len(grades_df.index)] = [last_student_scanned, grade]
            grades_df = grades_df[["label", "grade"]]
            grades_df.to_csv(GRADES_CSV_FILENAME, index=False)

            print(grade)
            grade_list.append(grade)

    # Return a result
    result = {"predicted_grade": grade_list}
    return jsonify(result)


# Grade adjusting route
@app.route("/adjust_grade", methods=["GET"])
def grade_adjustment_route():

    global last_student_scanned

    # Get arguments
    adjusted_grade = request.args.get("adjusted_grade", type=float)

    # Save the adjusted grade into the labels file
    grades_df = pandas.read_csv(GRADES_CSV_FILENAME)
    grades_df.loc[grades_df["label"] == last_student_scanned,
                  "grade"] = adjusted_grade
    grades_df = grades_df[["label", "grade"]]
    grades_df.to_csv(GRADES_CSV_FILENAME, index=False)

    # Return a result
    result = {"status": "ok"}
    return jsonify(result)


# Model retraining route
@app.route("/retrain_model", methods=["GET"])
def model_retraining_route():

    # Get arguments
    model = request.args.get("model", type=int)

    # Create a thread that retrain the model
    Thread(target=retrain_model(model)).start()

    # Return a result
    result = {"status": "ok"}
    return jsonify(result)


# Function for retraining the machine learning model
def retrain_model(model):
    global predictor, preprocessor

    Train(check=True).train()
    predictor = Predictor(model)
    preprocessor = Preprocessor()

    print("[+] Successfully retrained the model")


def main():
    global preprocessor, predictor

    # Initialize the dataset
    if (INIT_DATASET):
        feature_extraction.init_setup()

    # Train the model
    if (TRAIN_MODEL):
        Train(check=True).train()

    # Initialize some parts of the pipeline
    predictor = Predictor(1)
    preprocessor = Preprocessor()

    # Run the web server
    app.run(host="0.0.0.0", port=3001, debug=True)


if __name__ == "__main__":

    # Disable warnings
    warnings.simplefilter(action="ignore", category=RuntimeWarning)

    main()