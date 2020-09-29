'''Albreto tools that can be used for Euler Problems and other math problems'''
#imports
import numpy as np

#functions
##if number is prime
def is_prime(num):
    for i in range(2, int(np.sqrt(num)) + 1):
        if num % i == 0:
            return False
    return True
