import torch
import torch.nn as nn
import torch.optim as optim

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split


# Necesare suprascrierea functiei __len__ si supraincarcarea operatorului []
class GradesDataset(torch.utils.data.Dataset):
    def __init__(self, dataFrame):
        self._df = dataFrame

    def __len__(self):
        return len(self._df)

    def __getitem__(self, idx):  # []
        item = self._df.iloc[idx]
        features = []
        for feature in self._df.columns[2:-1]:
            features.append(item[feature])

        return {'features': torch.tensor(features, dtype=torch.float32),
                'labels': torch.tensor([item['grade']], dtype=torch.float32)}


# Necesare a fi suprascrise metodele __init__ si forward
class RegressionModel(nn.Module):
    def __init__(self, in_feat=2, out_feat=1):
        super().__init__()
        self.fc = nn.Linear(in_feat, out_feat)

    def forward(self, x):
        out = self.fc(x)
        return out


# Citim datele din fisierele .csv
featuresFrame = pd.read_csv('../data/features.csv')
gradesFrame = pd.read_csv('../data/grades.csv')

# Concatenam ambele tabele
dataFrame = pd.merge(featuresFrame, gradesFrame, on="label")
dataFrame = dataFrame[dataFrame['grade'].notna()]


# Stergem coloana Unnamed: 22
dataFrame.drop(['Unnamed: 22'], axis=1, inplace=True)

# Impartim dataFrame-ul in doua frame-uri
# unul pentru antrenare si unul pentru test
train_frame, test_frame = train_test_split(dataFrame, test_size=0.2)

# Creeam set-urile de date
train_set = GradesDataset(train_frame)
test_set = GradesDataset(test_frame)

# Numarul de feature-uri din set-ul dataFrame
input_number = len(dataFrame.columns[2:-1])
model = RegressionModel(input_number, 1)

LEARNING_RATE = 1e-10  # Rata de invatare
NR_EPOCHS = 6  # Numarul de epoci
BATCH_SIZE = 32  # Numarul de samples dintr-un batch

criterion = nn.MSELoss()  # functia cost (loss)
# algoritmul de optimizare (Stochastic Gradient Descent)
optimizer = optim.SGD(model.parameters(), lr=LEARNING_RATE)


# Pregatim o modalitate de loggare a informatiilor din timpul antrenarii
log_info = []

# Pregatim DataLoader-ul pentru antrenare
train_loader = torch.utils.data.DataLoader(
    train_set, batch_size=BATCH_SIZE, shuffle=True)

# Trecem modelul in modul train
model.train()


########### Training Loop #############

# pentru fiecare epoca (1 epoca = o iteratie peste intregul set de date)
for epoch in range(NR_EPOCHS):
    #print('Running epoch {}'.format(epoch))

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

# Graficul LOSS-ului pe parcursul antrenarii
# X = [x for x, loss in log_info]
# Y = [loss for x, loss in log_info]
# plt.plot(X, Y)
# plt.xlabel("Epoch")
# plt.ylabel("LOSS")
# plt.show()

# print(model.fc.weight, model.fc.bias)
torch.save(model.state_dict(), "../data/model.pt")
