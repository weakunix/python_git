import numpy as np
import pandas as pd

def toz1(X):
    return np.array([np.array([1, x[0], x[1]]) for x in X])

def toz2(X):
    return np.array([np.array([1, x[0], x[1], x[0] * x[1], x[0] ** 2, x[1] ** 2]) for x in X])

def getvsall(y, tar):
    return np.array([np.array([1 if i[0] == tar else -1]) for i in y])

def get15(X, y): 
    newX = np.array([])
    newy = np.array([])

    for i in range(len(X)):
        if y[i] == 1 or y[i] == 5:
            try:
                newX = np.vstack((newX, X[i]))
                newy = np.vstack((newy, [1 if y[i] == 1 else -1]))
            except:
                newX = X[i]
                newy = np.array([1 if y[i] == 1 else -1])
    return (newX, newy)

if __name__ == '__main__':
    train = pd.read_csv('train.csv', delim_whitespace = True, header = None)
    test = pd.read_csv('test.csv', delim_whitespace = True, header = None)

    lam = 1

    for i in range(10):
        Xtrain = train.iloc[:, [1, 2]].to_numpy()
        ytrain = train.iloc[:, [0]].to_numpy()
        ytrain = getvsall(ytrain, i)
        Z1train = toz1(Xtrain)
        Z2train = toz2(Xtrain)

        Xtest = test.iloc[:, [1, 2]].to_numpy()
        ytest = test.iloc[:, [0]].to_numpy()
        ytest = getvsall(ytest, i)
        Z1test = toz1(Xtest)
        Z2test = toz2(Xtest)

        w1 = np.linalg.inv(Z1train.T @ Z1train + lam * np.eye(3)) @ Z1train.T @ ytrain
        w2 = np.linalg.inv(Z2train.T @ Z2train + lam * np.eye(6)) @ Z2train.T @ ytrain

        e1in = np.mean([1 if i > 0 else -1 for i in np.ravel(Z1train @ w1)] != np.ravel(ytrain))
        e1out = np.mean([1 if i > 0 else -1 for i in np.ravel(Z1test @ w1)] != np.ravel(ytest))
        e2in = np.mean([1 if i > 0 else -1 for i in np.ravel(Z2train @ w2)] != np.ravel(ytrain))
        e2out = np.mean([1 if i > 0 else -1 for i in np.ravel(Z2test @ w2)] != np.ravel(ytest))

        print(f'Digit {i} | linear ein: {e1in} | linear eout: {e1out} | quad ein: {e2in} | quad eout: {e2out}')

    print('---')

    for l in [0.01, 1]:
        Xtrain = train.iloc[:, [1, 2]].to_numpy()
        ytrain = train.iloc[:, [0]].to_numpy()
        Xtrain, ytrain = get15(Xtrain, ytrain)
        Ztrain = toz2(Xtrain)

        Xtest = test.iloc[:, [1, 2]].to_numpy()
        ytest = test.iloc[:, [0]].to_numpy()
        Xtest, ytest = get15(Xtest, ytest)
        Ztest = toz2(Xtest)

        w = np.linalg.inv(Ztrain.T @ Ztrain + l * np.eye(6)) @ Ztrain.T @ ytrain

        ein = np.mean([1 if i > 0 else -1 for i in np.ravel(Ztrain @ w)] != np.ravel(ytrain))
        eout = np.mean([1 if i > 0 else -1 for i in np.ravel(Ztest @ w)] != np.ravel(ytest))

        print(f'Lamda {l} | ein: {ein} | eout: {eout}')
