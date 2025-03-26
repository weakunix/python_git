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
cnt = 0

while (E(u,v) > 1e-14):
    du = dEdu(u, v)
    dv = dEdv(u, v)
    u -= eta * du
    v -= eta * dv
    cnt += 1
print(cnt)
print(u, v)
