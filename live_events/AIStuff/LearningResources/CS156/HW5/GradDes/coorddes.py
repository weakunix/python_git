import numpy as np

def E(u, v):
    return (u * np.exp(v) - 2 * v * np.exp(-u)) ** 2

def dEdu(u, v):
    return 2 * (u * np.exp(v) - 2 * v * np.exp(-u)) * (np.exp(v) + 2 * v * np.exp(-u))

def dEdv(u, v):
    return 2 * (u * np.exp(v) - 2 * v * np.exp(-u)) * (u * np.exp(v) - 2 * np.exp(-u))

u = 1
v = 1
eta = 0.1

for i in range(15):
    du = dEdu(u, v)
    u -= eta * du
    dv = dEdv(u, v)
    v -= eta * dv

print(E(u, v))
