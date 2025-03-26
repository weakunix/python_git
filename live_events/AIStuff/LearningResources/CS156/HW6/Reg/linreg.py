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

if __name__ == '__main__':
    din = pd.read_csv('datain.csv')
    dout = pd.read_csv('dataout.csv')

    k = -1
    lam = 10 ** k

    #lam = 0 #no reg

    Xin = din.iloc[:, [0, 1]].to_numpy()
    yin = din.iloc[:, [2]].to_numpy()
    Zin = np.array([toz(Xin[i]) for i in range(len(Xin))])

    Xout = dout.iloc[:, [0, 1]].to_numpy()
    yout = dout.iloc[:, [2]].to_numpy()
    Zout = np.array([toz(Xout[i]) for i in range(len(Xout))])

    w = (np.linalg.inv(Zin.T @ Zin + lam * np.eye(8)) @ Zin.T @ yin).ravel()

    totein = 0
    toteout = 0

    for i in range(len(Zin)):
        totein += not check(w, Zin[i], yin[i])

    for i in range(len(Zout)):
        toteout += not check(w, Zout[i], yout[i])

    print(totein / len(Xin))
    print(toteout / len(Xout))
