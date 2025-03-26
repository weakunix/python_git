import numpy as np
import pandas as pd
from sklearn import svm

if __name__ == '__main__':
    q = 2
    c = 0.01
    zero = 1e-5
    
    data = pd.read_csv('train.csv', delim_whitespace = True, header = None)

    for tar in range(10):
        X = data.iloc[:, [1, 2]].to_numpy()
        y = np.ravel(data.iloc[:, [0]].to_numpy())
        n = len(X)
        y = np.array([1 if y[i] == tar else -1 for i in range(n)])

        model = svm.SVC(kernel = 'poly', degree = q, C = c, gamma = 1, coef0 = 1)
        model.fit(X, y)

        ypred = model.predict(X)
        print(f'Test {tar}: ein({np.mean(y != ypred)}) svcnt({sum(model.n_support_)})')
