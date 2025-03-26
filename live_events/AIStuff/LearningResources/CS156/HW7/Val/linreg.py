import numpy as np
import pandas as pd

def toz(x):
    x1 = x[0]
    x2 = x[1]
    return np.array([1, x1, x2, x1 ** 2, x2 ** 2, x1 * x2, abs(x1 - x2), abs(x1 + x2)])

def getsign(val):
    return 0 if val == 0 else (1 if val > 0 else -1)

def check(w, z, y):
    return getsign(np.dot(w, z)) == y

def geterr(w, Z, y):
    cnt = 0
    for i in range(len(Z)):
        cnt += not check(w, Z[i], y[i])
    return cnt / len(Z)

if __name__ == '__main__':
    din = pd.read_csv('datain.csv', header = None)
    dout = pd.read_csv('dataout.csv', header = None)

    X = din.iloc[:, [0, 1]].to_numpy()
    y = din.iloc[:, [2]].to_numpy()
    Z = np.array([toz(X[i]) for i in range(len(X))])

    #25 and 10
    '''
    Ztrain = Z[:25, :]
    Zval = Z[25:, :]
    ytrain = y[:25, :]
    yval = y[25:, :]
    '''

    #10 and 25
    Ztrain = Z[25:, :]
    Zval = Z[:25, :]
    ytrain = y[25:, :]
    yval = y[:25, :]

    W = [
        (np.linalg.inv(Ztrain[:, :i].T @ Ztrain[:, :i]) @ Ztrain[:, :i].T @ ytrain).ravel()
        for i in range(4, 9)
    ]

    for i in range(4, 9):
        print(f'Ein {i - 1}: {geterr(W[i - 4], Zval[:, :i], yval)}')

    X = dout.iloc[:, [0, 1]].to_numpy()
    y = dout.iloc[:, [2]].to_numpy()
    Z = np.array([toz(X[i]) for i in range(len(X))])

    for i in range(4, 9):
        print(f'Eout {i - 1}: {geterr(W[i - 4], Z[:, :i], y)}')
