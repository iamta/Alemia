from preprocessor import GRADES_DATASET
from preprocessor import FEATURES_DATASET

import torch
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim

import pandas as pd
import numpy as np 
from sklearn.model_selection import train_test_split

WEIGHTS_FILE = "../data/weightspytorchh.pt"

class Predictor:
    def __init__(self, model_name=WEIGHTS_FILE):

        self.model = torch.load(model_name)

    # returns <class 'numpy.ndarray'>
    def predict(self, features):
        #this padding is wrong (or model trained is not build correctly)
        features[0] =np.append(features[0], [0,0,0,0,0])
  
        predictionInput = torch.tensor(features).float()

        predictionResult = self.model(predictionInput)

        return predictionResult.detach().numpy().tolist()[0]


# Classes below are used for training 

class HomeworkDataset(torch.utils.data.Dataset):
    def __init__(self, dataframe):
        self._df = dataframe

    def __len__(self): 
        return len(self._df)

    def __getitem__(self, idx): #[]
        item = self._df.iloc[idx] 
        features=[]
        for i in self._df.columns[2:-1]:
          features.append(item[i])
        return {'features': torch.tensor(features, dtype=torch.float32),
                'labels' : torch.tensor([item['grade']], dtype=torch.float32)}

class RegressionModel(nn.Module):
    def __init__(self, in_feat=1, out_feat=1):
        super().__init__()
        self.fc = nn.Linear(in_feat, out_feat) # Definesc o retea neuronala cu un singur strat Fully Connected

    def forward(self, x):
        out = self.fc(x)
        return out

class Train:
    def __init__(self, check = True):
        # for now, train will be made using only liniar regression
        return


    def train(self):    
        featuretable = pd.read_csv(FEATURES_DATASET)
        gradestable = pd.read_csv(GRADES_DATASET)

        dataframe = pd.merge(featuretable, gradestable,on="label") # concatenez tabelele in functie de label
        dataframe=dataframe[dataframe['grade'].notna()]
        dataframe.head()

        dataframe.drop(['Unnamed: 22'],axis=1,inplace=True) #elimin coloana Unnamed: 22

        train_frame, test_frame = train_test_split(dataframe, test_size=0.2)

        print('Total: {} \nTrain: {} \nTest: {}'.format(len(dataframe), len(train_frame), len(test_frame)))

        # Utilizam clasa wrapper Homework Dataset
        train_set = HomeworkDataset(train_frame)
        test_set = HomeworkDataset(test_frame)

        model = RegressionModel(20,1) # generez o instanta a modelului

        LEARNING_RATE = 1e-10 # Rata de invatare
        NR_EPOCHS = 10 # Numarul de epoci
        BATCH_SIZE = 32 # Numarul de samples dintr-un batc

        criterion = nn.MSELoss() #atentie: turi utilizeaza Root MSE

        optimizer = optim.SGD(model.parameters(), lr=LEARNING_RATE)

        # Pregatim o modalitate de loggare a informatiilor din timpul antrenarii
        log_info = []

        # Pregatim DataLoader-ul pentru antrenare
        train_loader = torch.utils.data.DataLoader(train_set, batch_size=BATCH_SIZE, shuffle=True)

        # Trecem modelul in modul train
        model.train() 



        ########### Training Loop #############

        # pentru fiecare epoca (1 epoca = o iteratie peste intregul set de date)
        for epoch in range(NR_EPOCHS):
            print('Running epoch {}'.format(epoch))

            epoch_losses = []
            
            # pentru fiecare batch de BATCH_SIZE exemple din setul de date    
            for i, batch in enumerate(train_loader):

                inputs, labels = batch['features'], batch['labels']
                
                # anulam gradientii deja acumulati la nivelul retelei neuronale
                optimizer.zero_grad()

                # FORWARD PASS: trecem inputurile prin retea
                outputs = model(inputs)

                # Calculam LOSSul dintre etichetele prezise si cele reale
                loss = criterion(outputs, labels)

                # BACKPRPAGATION: calculam gradientii propagand LOSSul in retea
                loss.backward()

                # Utilizam optimizorul pentru a modifica parametrii retelei in functie de gradientii acumulati
                optimizer.step()

                # Salvam informatii despre antrenare (in cazul nostru, salvam valoarea LOSS)
                epoch_losses.append(loss.item()) 
            log_info.append((epoch, np.mean(epoch_losses)))

        #Salvare model
        #torch.save(model.state_dict(),WEIGHTS_FILE)
        torch.save(model,WEIGHTS_FILE)

    def test(self, model_name=WEIGHTS_FILE):
        #todo: implement
        return

    def calculate_test(self, model_name = WEIGHTS_FILE):
        #todo: implement
        return

