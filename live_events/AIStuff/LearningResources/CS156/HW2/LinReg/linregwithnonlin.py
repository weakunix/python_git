import random
import matplotlib.pyplot as plt
import numpy as np
from sklearn import linear_model

class LinReg:
    def __init__(self, n):
        self.n = n #size of data set
        self.X = np.array([]) #data set X
        self.y = np.array([]) #data set y
        self.w = np.array([]) #hypothesis w

    def getrand(self):
        return 2 * random.random() - 1

    def getx(self):
        return np.array([1, self.getrand(), self.getrand()])

    def gety(self, x):
        cur = 1 if x[1] ** 2 + x[2] ** 2 > 0.6 else -1
        if (random.random() < 0.1):
            cur *= -1
        return cur

    def getsign(self, val):
        if (val == 0):
            return 0
        return 1 if val > 0 else -1

    def check(self, ptx, pty):
        return self.getsign(np.dot(self.w, ptx)) == pty

    def trial(self):
        self.X = np.array([self.getx() for i in range(self.n)])
        self.y = np.array([self.gety(self.X[i]) for i in range(self.n)])

        linregmod = linear_model.LinearRegression(fit_intercept = False)
        linregmod.fit(self.X, self.y)
        self.w = linregmod.coef_

        ###self.showplot()

    def ein(self):
        cnt = 0
        for i in range(self.n):
            cnt += not self.check(self.X[i], self.y[i])
        ###print(cnt)
        ###self.showplot()
        return cnt / self.n

    def showplot(self):
        plt.axis((-1, 1, -1, 1)) #settings

        theta = np.linspace(0, 2 * np.pi, 400) #target
        x = np.sqrt(0.6) * np.cos(theta)
        y = np.sqrt(0.6) * np.sin(theta)
        plt.plot(x, y, color = 'blue')

        plt.scatter(self.X[:, 1], self.X[:, 2], c = ['green' if self.y[i] == 1 else 'red' for i in range(self.n)], s = 20) #data set

        m = -self.w[1] / self.w[2] #hypothesis
        b = -self.w[0] / self.w[2]
        plt.plot([-1, 1], [-m + b, m + b], 'm-')

        plt.show() #show plot

if __name__ == '__main__':
    t = 1000 #number of trials
    n = 1000 #size of dataset

    totein = 0

    model = LinReg(n) #linear regression for classification

    for i in range(t):
        print(f'Test case {i}')
        model.trial()
        totein += model.ein()

    print(totein / t)
    model.showplot()
