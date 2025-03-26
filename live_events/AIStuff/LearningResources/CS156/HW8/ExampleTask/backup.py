import numpy as np
import pandas as pd
import cvxopt
from sklearn import svm

def getsign(val):
    return 1 if val > 0 else -1

def polyK(x1, x2, q):
    return (1 + np.dot(x1, x2)) ** q

def g(alpha, sv, b, X, y, curx):
    for i in sv:
        b += alpha[i] * y[i] * polyK(X[i], curx, q)
    return getsign(b)

if __name__ == '__main__':
    tar = 0
    q = 2
    c = 0.01
    zero = 1e-5
    
    data = pd.read_csv('train.csv', delim_whitespace = True, header = None)

    X = data.iloc[:, [1, 2]].to_numpy()
    y = np.ravel(data.iloc[:, [0]].to_numpy())
    n = len(X)
    y = np.array([1 if y[i] == tar else -1 for i in range(n)])

    Pmat = cvxopt.matrix(np.outer(y, y) * (X @ X.T))
    qmat = cvxopt.matrix(-np.ones(n))

    Gmat = cvxopt.matrix(np.vstack((-np.eye(n), np.eye(n))))
    hmat = cvxopt.matrix(np.hstack((np.zeros(n), c * np.ones(n))))

    Amat = cvxopt.matrix(y, (1, n), tc 'd')
    bmat = cvxopt.matrix(0.0)

    cvxopt.solvers.options['show_progress'] = False
    alpha = np.ravel(cvxopt.solvers.qp(Pmat, qmat, Gmat, hmat, Amat, bmat)['x'])

    sv = []
    for i in range(n):
        if alpha[i] > zero:
            sv.append(i)

    assert(len(sv) != 0)
    
    b = y[sv[0]]
    for i in sv:
        b -= alpha[i] * y[i] * polyK(X[i], X[sv[0]], q)
    
    ein = 0
    for i in range(n):
        ein += g(alpha, sv, b, X, y, X[i]) != y[i]
    print(ein / n)
