import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import cvxopt

def getsign(val):
    return 1 if val > 0 else -1

def getf(x):
    return getsign(x[1] - x[0] + 0.25 * np.sin(np.pi * x[0]))

def getK(x1, x2, lam):
    return np.exp(-lam * np.dot(x1 - x2, x1 - x2))

def getrandx():
    return np.array([np.random.uniform(-1, 1) for i in range(2)])

def getdataset(n):
    X = np.array([getrandx() for i in range(n)])
    y = np.array([getf(X[i]) for i in range(n)])
    return (X, y)

def getsvmval(alpha, X, y, sv, b, lam, x, sign = True):
    for i in sv:
        b += alpha[i] * y[i] * getK(x, X[i], lam)
    return getsign(b) if sign else b

def getsvmerr(alpha, X, y, sv, b, lam, Xtest, ytest):
    cnt = 0
    for i in range(len(Xtest)):
        cnt += getsvmval(alpha, X, y, sv, b, lam, Xtest[i], True) != ytest[i]
    return cnt / len(Xtest)

def getrbfval(w, Mu, lam, x, sign = True):
    b = w[0]
    for i in range(len(Mu)):
        b += w[i + 1] * getK(x, Mu[i], lam)
    return getsign(b) if sign else b

def getrbferr(w, Mu, lam, Xtest, ytest):
    cnt = 0
    for i in range(len(Xtest)):
        cnt += getrbfval(w, Mu, lam, Xtest[i], True) != ytest[i]
    return cnt / len(Xtest)

def showplot(X, y, sv, Mu, Xtest):
    plt.xlim(-1, 1)
    plt.ylim(-1, 1)

    x1 = np.linspace(-1, 1, 400)
    x2 = x1 - 0.25 * np.sin(np.pi * x1)

    plt.plot(x1, x2, color = 'b')

    plt.scatter(X[:, 0], X[:, 1], color = ['green' if y[i] == 1 else 'red' for i in range(len(X))], s = 20)

    plt.scatter(X[sv, 0], X[sv, 1], color = 'black', s = 100, marker = '*')
    
    plt.scatter(Mu[:, 0], Mu[:, 1], color = 'cyan', s = 100, marker = '*')

    plt.scatter(Xtest[:, 0], Xtest[:, 1], color = 'purple', s = 100, marker = '^')

    plt.show()


def showsvmheatmap(X, y, sv, alpha, b, lam):
    plt.xlim(-1, 1)
    plt.ylim(-1, 1)
    
    plotx = np.linspace(-1, 1, 100)
    ploty = np.linspace(-1, 1, 100)
    plotx, ploty = np.meshgrid(plotx, ploty)
    plotz = np.zeros_like(plotx)
    for i in range(plotx.shape[0]):
        for j in range(plotx.shape[1]):
            cur = np.array([plotx[i, j], ploty[i, j]])
            plotz[i, j] = getsvmval(alpha, X, y, sv, b, lam, cur, False)
    plt.imshow(plotz, extent=[-1, 1, -1, 1], origin='lower', cmap='viridis', aspect='auto')
    plt.colorbar()
    
    x1 = np.linspace(-1, 1, 400)
    x2 = x1 - 0.25 * np.sin(np.pi * x1)

    plt.plot(x1, x2, color = 'b')

    #plt.scatter(X[:, 0], X[:, 1], color = ['green' if y[i] == 1 else 'red' for i in range(len(X))], s = 20)

    plt.scatter(X[sv, 0], X[sv, 1], color = 'black', s = 100, marker = '*')
    for i, (x1, x2) in enumerate(X[sv]):
        plt.text(x1, x2, np.round(alpha[sv[i]] * y[sv[i]], 2), fontsize = 9, color = 'red', ha = 'left')

    print(alpha[sv])

    print(b)
    plt.show()

def showrbfheatmap(X, y, Mu, w, lam):
    plt.xlim(-1, 1)
    plt.ylim(-1, 1)

    plotx = np.linspace(-1, 1, 100)
    ploty = np.linspace(-1, 1, 100)
    plotx, ploty = np.meshgrid(plotx, ploty)
    plotz = np.zeros_like(plotx)
    for i in range(plotx.shape[0]):
        for j in range(plotx.shape[1]):
            cur = np.array([plotx[i, j], ploty[i, j]])
            plotz[i, j] = getrbfval(w, Mu, lam, cur, False)
    plt.imshow(plotz, extent=[-1, 1, -1, 1], origin='lower', cmap='viridis', aspect='auto')
    plt.colorbar()

    x1 = np.linspace(-1, 1, 400)
    x2 = x1 - 0.25 * np.sin(np.pi * x1)

    plt.plot(x1, x2, color = 'b')

    #plt.scatter(X[:, 0], X[:, 1], color = ['green' if y[i] == 1 else 'red' for i in range(len(X))], s = 20)
    
    plt.scatter(Mu[:, 0], Mu[:, 1], color = 'cyan', s = 100, marker = '*')
    for i, (mu1, mu2) in enumerate(Mu):
        plt.text(mu1, mu2, np.round(w[i + 1], 2), fontsize = 9, color = 'red')

    print(w[0])
    plt.show()

if __name__ == '__main__':
    n = 100
    e = 1000
    lam = 1.5
    k = 9
    zero = 1e-5

    X, y = getdataset(n)

    #svm
    Kmat = np.zeros((n, n))
    for i in range(n):
        for j in range(n):
            Kmat[i][j] = getK(X[i], X[j], lam)

    Pmat = cvxopt.matrix(np.outer(y, y) * Kmat, tc = 'd')
    qmat = cvxopt.matrix(-np.ones(n), tc = 'd')
    
    Gmat = cvxopt.matrix(-np.eye(n), tc = 'd')
    hmat = cvxopt.matrix(np.zeros(n), tc = 'd')

    Amat = cvxopt.matrix(y.reshape(1, n), tc = 'd')
    bmat = cvxopt.matrix(0, tc = 'd')

    cvxopt.solvers.options['show_progress'] = False
    alpha = np.ravel(cvxopt.solvers.qp(Pmat, qmat, Gmat, hmat, Amat, bmat)['x'])

    sv = [i for i in range(n) if alpha[i] > zero]

    b = y[sv[0]]
    for i in sv:
        b -= alpha[i] * y[i] * getK(X[sv[0]], X[i], lam)

    if getsvmerr(alpha, X, y, sv, b, lam, X, y) != 0:
        raise SystemError('Run failed (SVM hard margin)')

    #rbf
    prvmu = np.array([[-2, -2] for i in range(k)])
    Mu = np.array([getrandx() for i in range(k)])
    belong = [[] for i in range(k)]

    while not np.array_equal(prvmu, Mu):
        prvmu = Mu
        for i in range(k):
            belong[i] = []
        for i in range(n):
            best = (1e9, -1)
            for j in range(k):
                best = min((np.dot(X[i] - Mu[j], X[i] - Mu[j]), j), best)
            assert(best[1] != -1)
            belong[best[1]].append(i)
        for i in range(k):
            Mu[i] = np.array([0, 0])
            for j in belong[i]:
                Mu[i] += X[j]
            if len(belong[i]) > 0:
                Mu[i] /= len(belong[i])
    
    if min([len(i) for i in belong]) == 0:
        raise SystemError('Run failed (K-means cluster empty)')

    Phi = np.ones((n, k + 1))
    for i in range(n):
        for j in range(1, k + 1):
            Phi[i][j] = getK(X[i], Mu[j - 1], lam)

    showsvmheatmap(X, y, sv, alpha, b, lam)

    w = np.linalg.inv(Phi.T @ Phi) @ Phi.T @ y
    showrbfheatmap(X, y, Mu, w, lam)

    w = np.linalg.inv(Phi.T @ Phi + 0.1 * np.eye(k + 1)) @ Phi.T @ y
    showrbfheatmap(X, y, Mu, w, lam)

    #out of sample
    '''
    for i in range(e):
        Xtest, ytest = getdataset(1)
        print(f'SVM signal: {getsvmval(alpha, X, y, sv, b, lam, Xtest[0], False)}')
        print(f'RBF signal: {getrbfval(w, Mu, lam, Xtest[0], False)}')
        print(f'SVM correct: {not getsvmerr(alpha, X, y, sv, b, lam, Xtest, ytest)}')
        print(f'RBF correct: {not getrbferr(w, Mu, lam, Xtest, ytest)}')
        showplot(X, y, sv, Mu, Xtest)
    '''
