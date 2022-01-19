import numpy as np

primes = set()
is_prime = True


with open('million_primes.txt', 'w') as prime_file:
    for i in range(2, 10 ** 6 + 1):
        if __name__ == '__main__':
            if i % 10 ** 5 == 0:
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
            primes.add(i)
            prime_file.write(f'{str(i)}\n')
