import numpy as np

primes = []
is_prime = True

for i in range(2, 10 ** 6 + 1):
    if __name__ == '__main__':
        print(i)
    is_prime = True
    can_pop = []
    for k in primes:
        if k > int(np.sqrt(i)):
            break
        if i % k == 0:
            is_prime = False
            break
    if is_prime:
        primes.append(i)

f = open('billion_primes.txt', 'w')
for i in primes:
    f.write(f'{str(i)}\n')
