import matplotlib.pyplot as plt
import numpy as np
from sklearn import svm
import cvxopt

def K(x1, x2):
    return (1 + np.dot(x1, x2)) ** 2

if __name__ == '__main__':
    X = np.array([
        [1, 0],
        [0, 1],
        [0, -1],
        [-1, 0],
        [0, 2],
        [0, -2],
        [-2, 0]
    ])
    y = np.array([-1, -1, -1, 1, 1, 1, 1])

    Kmat = np.zeros((7, 7))
    for i in range(7):
        for j in range(7):
            Kmat[i][j] = K(X[i], X[j])

    Pmat = cvxopt.matrix(np.outer(y, y) * Kmat, tc = 'd')
    qmat = cvxopt.matrix(-np.ones(7), tc = 'd')

    Gmat = cvxopt.matrix(-np.eye(7), tc = 'd')
    hmat = cvxopt.matrix(np.zeros(7), tc = 'd')

    Amat = cvxopt.matrix(y.reshape(1, -1), tc = 'd')
    bmat = cvxopt.matrix(0.0, tc = 'd')

    cvxopt.solvers.options['show_progress'] = False
    alpha = np.ravel(cvxopt.solvers.qp(Pmat, qmat, Gmat, hmat, Amat, bmat)['x'])
    
    print(alpha) #wrong??? (different alphas)

    #======

    model = svm.SVC(kernel = 'poly', degree = 2, gamma = 1, C = 1e9, coef0 = 1)
    model.fit(X, y)
    print(model.dual_coef_)
