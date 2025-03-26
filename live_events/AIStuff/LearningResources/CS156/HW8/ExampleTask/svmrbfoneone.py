import numpy as np
import pandas as pd
from sklearn import svm

def get15(X, y):
    newX = np.array([])
    newy = np.array([])

    for i in range(len(X)):
        if y[i] == 1 or y[i] == 5:
            try:
                newX = np.vstack((newX, X[i]))
                newy = np.hstack((newy, [1 if y[i] == 1 else -1]))
            except:
                newX = X[i]
                newy = np.array([1 if y[i] == 1 else -1])
    return (newX, newy)

if __name__ == '__main__':
    train = pd.read_csv('train.csv', delim_whitespace = True, header = None)
    test = pd.read_csv('test.csv', delim_whitespace = True, header = None)

    Xtrain = train.iloc[:, [1, 2]].to_numpy()
    ytrain = np.ravel(train.iloc[:, [0]].to_numpy())
    Xtrain, ytrain = get15(Xtrain, ytrain)
    
    Xtest = test.iloc[:, [1, 2]].to_numpy()
    ytest = np.ravel(test.iloc[:, [0]].to_numpy())
    Xtest, ytest = get15(Xtest, ytest)

    for i in [0.01, 1, 100, 1e4, 1e6]:
        model = svm.SVC(kernel = 'rbf', C = i, gamma = 1)
        model.fit(Xtrain, ytrain)
        print(f'C = {i}: ein({np.mean(ytrain != model.predict(Xtrain))}) eout({np.mean(ytest != model.predict(Xtest))}) svcnt({sum(model.n_support_)})')
