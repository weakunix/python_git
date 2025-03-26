import numpy as np
import pandas as pd
from sklearn import svm
from sklearn.model_selection import KFold

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
    data = pd.read_csv('train.csv', delim_whitespace = True, header = None)

    X = data.iloc[:, [1, 2]].to_numpy()
    y = np.ravel(data.iloc[:, [0]].to_numpy())
    X, y = get15(X, y)

    avgecv = np.array([0.0 for i in range(5)])
    bestcnt = np.array([0.0 for i in range(5)])

    for i in range(100):
        kf = KFold(n_splits = 10, shuffle = True)

        ecv = np.array([0.0 for i in range(5)])
        
        for train, val in kf.split(X):
            Xtrain = X[train]
            Xval = X[val]

            ytrain = y[train]
            yval = y[val]

            for i, j in enumerate([0.0001, 0.001, 0.01, 0.1, 1]):
                model = svm.SVC(kernel = 'poly', degree = 2, C = j, gamma = 1, coef0 = 1)
                model.fit(Xtrain, ytrain)
                ecv[i] += np.mean(yval != model.predict(Xval))

        ecv /= 10
        print(ecv)

        avgecv = avgecv + ecv

        best = (ecv[0], 0)
        for i in range(5):
            best = min((ecv[i], i), best)
        bestcnt[best[1]] += 1
    
    print(bestcnt)
    print(avgecv / 100)
