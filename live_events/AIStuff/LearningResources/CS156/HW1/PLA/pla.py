import random
import matplotlib.pyplot as plt
import numpy as np

class Perceptron: 
    def __init__(self, n, e):
        self.n = n #size of data set
        self.e = e #number of error points used
        self.st1 = 0 #x of first point for target function line
        self.st2 = 0 #y
        self.en1 = 0 #x of second point
        self.en2 = 0 #y
        self.dtx1 = [] #data set x1
        self.dtx2 = [] #data set x2
        self.dty = [] #data set y
        self.w = np.array([]) #w

    def getsign(self, val):
        if (val == 0):
            return 0
        return 1 if val > 0 else -1

    def getxval(self):
        return 2 * random.random() - 1

    def getyval(self, x1, x2):
        v1 = np.array([self.st1 - self.en1, x1 - self.en1])
        v2 = np.array([self.st2 - self.en2, x2 - self.en2])
        return 1 if np.cross(v1, v2) > 0 else -1

    def getdatapt(self, idx):
        return np.array([1, self.dtx1[idx], self.dtx2[idx]])

    def update(self):
        misclass = []
        for i in range(self.n):
            if (self.getsign(np.dot(self.w, self.getdatapt(i))) != self.dty[i]):
                misclass.append(i)
        if (len(misclass) == 0):
            return False
        cur = random.choice(misclass)
        self.w = np.add(self.w, self.dty[cur] * self.getdatapt(cur))
        return True

    def trial(self):
        self.st1 = self.getxval();
        self.st2 = self.getxval();
        self.en1 = self.getxval();
        self.en2 = self.getxval();

        self.dtx1 = [self.getxval() for i in range(self.n)]
        self.dtx2 = [self.getxval() for i in range(self.n)]
        self.dty = [self.getyval(self.dtx1[i], self.dtx2[i]) for i in range(self.n)]

        cnt = 0
        self.w = np.array([0, 0, 0])
        while (self.update()):
            cnt += 1

        #self.showplot()

        return cnt

    def error(self):
        cnt = 0
        for i in range(self.e):
            x1 = self.getxval()
            x2 = self.getxval()
            y = self.getyval(x1, x2)
            cnt += (self.getsign(np.dot(self.w, np.array([1, x1, x2]))) != y)
        return cnt / self.e

    def showplot(self):
        plt.axis((-1, 1, -1, 1)) #settings

        plt.scatter([self.st1, self.en1], [self.st2, self.en2], s = 10) #end points of target function

        m = (self.st2 - self.en2) / (self.st1 - self.en1) #target
        b = self.st2 - m * self.st1
        plt.plot([-1, 1], [-m + b, m + b], 'b-')

        plt.scatter(self.dtx1, self.dtx2, c = ['green' if self.dty[i] == 1 else 'red' for i in range(self.n)], s = 20) #data set
        
        if (self.w[2] != 0): #hypothesis
            m = -self.w[1] / self.w[2]
            b = -self.w[0] / self.w[2]
            plt.plot([-1, 1], [-m + b, m + b], 'm-')

        plt.show() #show plot

if __name__ == '__main__':
    t = 1000 #number of trials
    n = 100 #size of dataset
    e = 1000 #number of points used for error testing
    totcnt = 0 #total count for iterations for convergence
    toterr = 0 #total error

    model = Perceptron(n, e) #perceptron model

    for i in range(t):
        print(f'Test case {i}')
        totcnt += model.trial()
        toterr += model.error()
    print(totcnt / t)
    print(toterr / t)
