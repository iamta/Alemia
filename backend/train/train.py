from preprocessor import Preprocessor
import numpy as np
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestRegressor
from sklearn.linear_model import LinearRegression, SGDRegressor, Ridge
from sklearn.metrics import mean_squared_error
from sklearn.svm import SVR
import math
import os
import joblib

WEIGHTS_FILE = "../data/weights.apt"

# Training class
# Allows for two methods - RandomForest and LinearRegression
# Generates comparision graphs between multiple methods
# Generates predicted - ground truth graph


class Train:
    def __init__(self, check=False):

        if check is True:
            self.regressor = RandomForestRegressor()
        else:
            self.regressor = LinearRegression()

        #TODO(@apostolescus)
        self.x, self.y, self.test_data, _ = Preprocessor().get_dataset()

    # False to get test data, True to get train data
    def _get_test_train_data(self, train, all = False):

        if all is True:
            return self.x, self.y
        
        x_train, x_test, y_train, y_test = train_test_split(self.x,
                                                            self.y,
                                                            test_size=0.2)

        if train is True:
            return x_train, y_train
        else:
            return x_test, y_test

    def train(self):

        x_train, y_train = self._get_test_train_data(True, True)
        self.regressor.fit(x_train, y_train)

        joblib.dump(self.regressor, WEIGHTS_FILE)

    #test method - plots the difference btw prediction and ground truth
    def test(self, model_name=WEIGHTS_FILE):

        self.regressor = joblib.load(model_name)

        x_test, y_test = self._get_test_train_data(False)

        y_predicted = self.regressor.predict(x_test)

        plt.plot(y_test - y_predicted, marker='o', linestyle='')
        plt.axhline(y=0, color="r", linestyle="-")
        plt.title("Diferenta nota reala-prezisa Linear Regression")
        plt.ylabel("Eroarea de predictie")
        plt.xlabel("Id date test")
        # plt.show()
        plt.savefig("graph.png")

    #compares multiple prediction methods
    #generates graphic representation of RMSE
    def test_multiple_methods(self):

        x_train, y_train = self._get_test_train_data(True)
        x_test, y_test = self._get_test_train_data(False)

        linear_regressor = LinearRegression()
        svr_regressor = SVR()
        random_forest_regressor = RandomForestRegressor()
        ridge_regressor = Ridge()

        linear_regressor.fit(x_train, y_train)
        svr_regressor.fit(x_train, y_train)
        random_forest_regressor.fit(x_train, y_train)
        ridge_regressor.fit(x_train, y_train)

        svr_predict = svr_regressor.predict(x_test)
        linear_predict = linear_regressor.predict(x_test)
        random_forest_predict = random_forest_regressor.predict(x_test)
        ridge_predict = ridge_regressor.predict(x_test)

        # print("Linear Predict :", linear_predict)
        # print("True notes: ", y_test)

        rmse_SVR = self._calculate_rmse(y_test, svr_predict)
        print("RMSE SVR: ", rmse_SVR)

        rmse_Linear = self._calculate_rmse(y_test, linear_predict)
        print("RMSE Linear Regression: ", rmse_Linear)

        rmse_Forest = self._calculate_rmse(y_test, random_forest_predict)
        print("RMSE Random Forest: ", rmse_Forest)

        rmse_Ridge = self._calculate_rmse(y_test, ridge_predict)
        print("RMSE Ridge: ", rmse_Ridge)

        x = ['Linear Reg.', 'Rand. Forest', 'Ridge', 'SVR']
        y = [rmse_Linear, rmse_Forest, rmse_Ridge, rmse_SVR]

        counter = 0

        for i in y:
            if round(i, 4) == 0:
                x[counter] = x[counter] + "\n" + str(round(i, 15))
            else:
                x[counter] = x[counter] + "\n" + str(round(i, 4))
            counter += 1

        plt.bar(x, y)
        plt.ylabel("Valoare RMSE")
        plt.xlabel("Algoritm")
        plt.title("Comparație RMSE")
        plt.savefig("model_comparision.png")
        plt.show()

    def _calculate_rmse(self, y_test, y_predicted):

        mse = mean_squared_error(y_test, y_predicted)
        rmse = np.sqrt(mse)

        return rmse

    def calculate_test(self, model_name = WEIGHTS_FILE):
        self.regressor = joblib.load(model_name)

        y_predicted = self.regressor.predict(self.test_data)
    
        f = open("../others/results.txt", "w")

        for i in y_predicted:
            f.write(str(round(i,2)) + "\n")
  
        return y_predicted

    def _load_true_notes(self):

        array = np.loadtxt("true_notes")
        print("True notes:",array)

        return array


class Predictor:
    def __init__(self, model_name=WEIGHTS_FILE):

        self.model = joblib.load(model_name)

    # returns <class 'numpy.ndarray'>
    def predict(self, features):

        prediction = self.model.predict(features)

        return prediction


#How to run

train = Train(True)
train.train()
train.calculate_test()

# true_notes = train._load_true_notes()
# prd = Predictor()
# # x_test, y_test = train._get_test_train_data(False)
# y_true = prd.predict(train.test_data)
# print(y_true)
# # y_prd = prd.predict(x_test)

# # print(y_true)
# print("RMSE: ", train._calculate_rmse(y_true, true_notes))

