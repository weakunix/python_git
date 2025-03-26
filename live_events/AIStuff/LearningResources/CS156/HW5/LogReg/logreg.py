import matplotlib.pyplot as plt
import numpy as np
from sklearn import linear_model

class LogReg:
    def __init__(self, n, tol, eta, e):
        self.n = n #size of data set
        self.tol = tol #tolerance
        self.eta = eta #learning rate
        self.e = e #error points
        self.st1 = 0 #x of first point for target function line
        self.st2 = 0 #y
        self.en1 = 0 #x of second point
        self.en2 = 0 #y
        self.X = np.array([]) #data set X
        self.y = np.array([]) #data set y
        self.w = np.array([]) #hypothesis w

    def getrand(self):
        return np.random.uniform(-1, 1)

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

    def geterr(self, x, y):
        return np.log(1 + np.exp(-y * np.dot(self.w, x)))

    def trial(self):
        self.st1 = self.getrand();
        self.st2 = self.getrand();
        self.en1 = self.getrand();
        self.en2 = self.getrand();

        self.X = np.array([self.getx() for i in range(self.n)])
        self.y = np.array([self.gety(self.X[i]) for i in range(self.n)])

        self.w = np.array([0, 0, 0])
        pastw = self.w
        epoch = 0
        
        while (True):
            curord = [i for i in range(self.n)]
            np.random.shuffle(curord)
            epoch += 1

            for i in curord:
                grad = (-self.y[i] / (1 + np.exp(self.y[i] * np.dot(self.w, self.X[i])))) * self.X[i]
                self.w = self.w - eta * grad
            
            if (np.linalg.norm(self.w - pastw) < self.tol):
                break

            pastw = self.w

        ###self.showplot()

        return epoch

    def geteout(self):
        tot = 0
        for i in range(self.e):
            x = self.getx()
            y = self.gety(x)
            tot += self.geterr(x, y)
        return tot / self.e

    def showplot(self):
        plt.axis((-1, 1, -1, 1)) #settings

        plt.scatter([self.st1, self.en1], [self.st2, self.en2], s = 10) #end points of target function

        m = (self.st2 - self.en2) / (self.st1 - self.en1) #target
        b = self.st2 - m * self.st1
        plt.plot([-1, 1], [-m + b, m + b], 'b-')

        plt.scatter(self.X[:, 1], self.X[:, 2], c = ['green' if self.y[i] == 1 else 'red' for i in range(self.n)], s = 20) #data set

        plt.show() #show plot

if __name__ == '__main__':
    t = 100 #number of trials
    n = 100 #size of dataset
    tol = 0.01 #tolerance
    eta = 0.01
    e = 1000 #error points

    toteout = 0
    totepoch = 0

    model = LogReg(n, tol, eta, e) #linear regression for classification

    for i in range(t):
        print(f'Test case {i}')
        totepoch += model.trial()
        toteout += model.geteout()

    print(toteout / t)
    print(totepoch / t)
