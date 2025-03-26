import random
import matplotlib.pyplot as plt
import numpy as np
from sklearn import linear_model

class LinReg: 
    def __init__(self, n, e):
        self.n = n #size of data set
        self.e = e #number of error points used
        self.st1 = 0 #x of first point for target function line
        self.st2 = 0 #y
        self.en1 = 0 #x of second point
        self.en2 = 0 #y
        self.X = np.array([]) #data set X
        self.y = np.array([]) #data set y
        self.w = np.array([]) #hypothesis w

    def getrand(self):
        return 2 * random.random() - 1

    def getx(self):
        return np.array([1, self.getrand(), self.getrand()])

    def gety(self, x):
        v1 = np.array([self.st1 - self.en1, x[1] - self.en1])
        v2 = np.array([self.st2 - self.en2, x[2] - self.en2])
        return 1 if np.cross(v1, v2) > 0 else -1

    def getsign(self, val):
        if (val == 0):
            return 0
        return 1 if val > 0 else -1

    def check(self, ptx, pty):
        return self.getsign(np.dot(self.w, ptx)) == pty

    def trial(self):
        self.st1 = self.getrand();
        self.st2 = self.getrand();
        self.en1 = self.getrand();
        self.en2 = self.getrand();

        self.X = np.array([self.getx() for i in range(self.n)])
        self.y = np.array([self.gety(self.X[i]) for i in range(self.n)])

        model = linear_model.LinearRegression()
        model.fit(self.X, self.y)
        self.w = model.coef_
        self.w[0] = model.intercept_
        
        ###self.showplot()

    def ein(self):
        cnt = 0
        for i in range(self.n):
            cnt += not self.check(self.X[i], self.y[i])
        ###print(cnt)
        ###self.showplot()
        return cnt / self.n

    def eout(self):
        cnt = 0
        for i in range(self.e):
            x = self.getx()
            y = self.gety(x)
            ###plt.scatter([x[1]], [x[2]], s = 10, c = 'cyan')
            cnt += not self.check(x, y)
        ###print(cnt)
        ###self.showplot()
        return cnt / self.e

    def showplot(self):
        plt.axis((-1, 1, -1, 1)) #settings

        plt.scatter([self.st1, self.en1], [self.st2, self.en2], s = 10) #end points of target function

        m = (self.st2 - self.en2) / (self.st1 - self.en1) #target
        b = self.st2 - m * self.st1
        plt.plot([-1, 1], [-m + b, m + b], 'b-')

        plt.scatter(self.X[:, 1], self.X[:, 2], c = ['green' if self.y[i] == 1 else 'red' for i in range(self.n)], s = 20) #data set

        m = -self.w[1] / self.w[2] #hypothesis
        b = -self.w[0] / self.w[2]
        plt.plot([-1, 1], [-m + b, m + b], 'm-')

        plt.show() #show plot

if __name__ == '__main__':
    t = 1000 #number of trials
    n = 100 #size of dataset
    e = 1000 #number of points used for error testing

    totein = 0
    toteout = 0

    model = LinReg(n, e) #linear regression for classification

    for i in range(t):
        print(f'Test case {i}')
        model.trial()
        totein += model.ein()
        toteout += model.eout()

    print(totein / t)
    print(toteout / t)
