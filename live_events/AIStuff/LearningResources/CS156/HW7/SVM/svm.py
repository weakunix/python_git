import matplotlib.pyplot as plt
import numpy as np
from sklearn import linear_model
import cvxopt

def getrand():
    return np.random.uniform(-1, 1)

def getx():
    return np.array([getrand(), getrand()])

def gety(x, st1, st2, en1, en2):
    v1 = np.array([st1 - en1, x[0] - en1])
    v2 = np.array([st2 - en2, x[1] - en2])
    return 1 if np.cross(v1, v2) > 0 else -1

def getset(n, st1, st2, en1, en2):
    X = np.array([getx() for i in range(n)])
    y = np.array([gety(X[i], st1, st2, en1, en2) for i in range(n)])
    if (len(set(y)) == 1):
        return getset(n, st1, st2, en1, en2)
    return (X, y)

def getsign(val):
    if (val == 0):
        return 0
    return 1 if val > 0 else -1

def showplot(n, st1, st2, en1, en2, X, y, perc, svmw, svmb):
    plt.axis((-1, 1, -1, 1)) #settings

    plt.scatter([st1, en1], [st2, en2], s = 10) #end points of target function

    m = (st2 - en2) / (st1 - en1) #target
    b = st2 - m * st1
    plt.plot([-1, 1], [-m + b, m + b], 'b-')

    plt.scatter(X[:, 0], X[:, 1], c = ['green' if y[i] == 1 else 'red' for i in range(n)], s = 20) #data set

    m = -perc[1] / perc[2] #hypothesis perceptron
    b = -perc[0] / perc[2]
    plt.plot([-1, 1], [-m + b, m + b], 'm-')

    m = -svmw[0] / svmw[1] #hypothesis svm
    b = -svmb / svmw[1]
    plt.plot([-1, 1], [-m + b, m + b], 'c-')

    plt.show() #show plot

class Perceptron:
    def __init__(self):
        self.n = 0
        self.X = np.array([])
        self.y = np.array([])
        self.w = np.array([])

    def check(self, x, y):
        return getsign(np.dot(self.w, x)) == y

    def update(self):
        wrong = []
        for i in range(self.n):
            if (not self.check(self.X[i], self.y[i])):
                wrong.append(i)
        if (len(wrong) == 0):
            return False
        cur = np.random.choice(wrong)
        self.w = self.w + self.y[cur] * self.X[cur]
        return True

    def train(self, X, y):
        self.n = len(X)
        self.X = np.hstack((
            np.ones((self.n, 1)),
            X
        ))
        self.y = y
        self.w = np.array([0 for i in range(3)])
        
        while (self.update()):
            pass

    def test(self, X, y):
        X = np.hstack((
            np.ones((len(X), 1)),
            X
        ))
        cnt = 0
        for i in range(len(X)):
            cnt += not self.check(X[i], y[i])
        return cnt / len(X)

class SVM:
    def __init__(self):
        self.n = 0
        self.X = np.array([])
        self.y = np.array([])
        self.w = np.array([])
        self.b = 0
        self.svcnt = 0

    def check(self, x, y):
        return getsign(np.dot(self.w, x) + self.b) == y

    def train(self, X, y):
        self.n = len(X)
        self.X = X
        self.y = y

        P = cvxopt.matrix(
            np.array([
                np.array([
                    self.y[i] * self.y[j] * np.dot(self.X[i], self.X[j])
                    for j in range(n)
                ])
                for i in range(n)
            ]),
            tc = 'd'
        )
        q = cvxopt.matrix(-np.ones(n), tc = 'd')

        G = cvxopt.matrix(-np.eye(n), tc = 'd')
        h = cvxopt.matrix(np.zeros(n), tc = 'd')

        A = cvxopt.matrix(np.array([self.y]), tc = 'd')
        b = cvxopt.matrix(np.array([[0]]), tc = 'd')

        cvxopt.solvers.options['show_progress'] = False
        alpha = np.ravel(cvxopt.solvers.qp(P, q, G, h, A, b)['x'])
        
        zero = 1e-5
        sv = []
        for i in range(self.n):
            if (alpha[i] > zero):
                sv.append(i)

        assert(len(sv) != 0)

        self.w = np.array([0 for i in range(2)])
        for i in sv:
            self.w = self.w + alpha[i] * self.y[i] * self.X[i]

        self.b = self.y[sv[0]] - np.dot(self.w, self.X[sv[0]])

        self.svcnt = len(sv)
    
    def test(self, X, y):
        cnt = 0
        for i in range(len(X)):
            cnt += not self.check(X[i], y[i])
        return cnt / len(X)

if __name__ == '__main__':
    t = 1000 #number of trials
    n = 100 #size of dataset
    e = 1000

    modelp = Perceptron()
    models = SVM()

    pbetter = 0
    sbetter = 0
    svcnt = 0

    for i in range(t):
        print(f'Test {i}')

        st1 = getrand()
        st2 = getrand()
        en1 = getrand()
        en2 = getrand()
        
        Xin, yin = getset(n, st1, st2, en1, en2)
        
        modelp.train(Xin, yin)
        models.train(Xin, yin)

        ###showplot(n, st1, st2, en1, en2, X, y, modelp.w, models.w, models.b)

        Xout, yout = getset(e, st1, st2, en1, en2)

        eoutp = modelp.test(Xout, yout)
        eouts = models.test(Xout, yout)

        pbetter += (eoutp < eouts)
        sbetter += (eouts < eoutp)
        svcnt += models.svcnt

    print(pbetter)
    print(sbetter)
    print(svcnt / t)
    
    showplot(n, st1, st2, en1, en2, Xin, yin, modelp.w, models.w, models.b)
