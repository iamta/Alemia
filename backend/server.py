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
from train import Train, Predictor, get_predictors

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
@app.route("/api/")
def default_route():
    return "Alemia API\n"


# Prediction route
@app.route("/api/predict", methods=["POST"])
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
    features = feature_extraction.retrain_data_one(extraction_full_path + "/")
    features = preprocessor.transform_entry(features)

    # Predict the grades
    grades = {}
    predictors = get_predictors()
    for predictor in predictors:
        grades[predictor.model_name] = round(predictor.predict([features])[0], 2)


    '''
    # Dump the grades into the specific CSV file
    grades_df = pandas.read_csv(GRADES_CSV_FILENAME)
    grades_df.loc[len(grades_df.index)] = [last_student_scanned, grade]
    grades_df = grades_df[["label", "grade"]]
    grades_df.to_csv(GRADES_CSV_FILENAME, index=False)
    '''

    # Return a result
    result = {"predicted_grades": grades}
    return jsonify(result)


# Grade adjusting route
@app.route("/api/adjust_grade", methods=["GET"])
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
@app.route("/api/retrain_model", methods=["GET"])
def model_retraining_route():

    # Create a thread that retrain the model
    Thread(target=retrain_model).start()

    # Return a result
    result = {"status": "ok"}
    return jsonify(result)

@app.route("/api/stud_statistics/<stud_name>", methods=["GET"])
def get_stud_stats(stud_name):

    with open("../data/features.csv","rt") as file:
        data = file.read().split('\n')
        columns = data[0].split(',')[:-1]
        
        for student in data:
            if stud_name in student.split(','):
                result = {}
                for column, value in zip(columns, student.split(',')):
                    result[column]=value
                return jsonify(result)   

# Function for retraining the machine learning model
def retrain_model():
    global predictor, preprocessor

    Train(check=True).train()
    predictor = Predictor()
    preprocessor = Preprocessor()

    print("[+] Successfully retrained the model")


warnings.simplefilter(action="ignore", category=RuntimeWarning)

#def main():
    #global preprocessor, predictor

    # Initialize the dataset
if (INIT_DATASET):
    feature_extraction.init_setup()

# Train the model
if (TRAIN_MODEL):
    Train(check=True).train()

# Initialize some parts of the pipeline
predictor = Predictor()
preprocessor = Preprocessor()

    # Run the web server
    #app.run(host="0.0.0.0", port=3001, debug=True)


#f __name__ == "__main__":

    # Disable warnings
    #warnings.simplefilter(action="ignore", category=RuntimeWarning)

    #main()