#imports
import numpy as np, sympy

#vars
nums = [str(i) for i in range(10)] #all numbers
allo = { '+': lambda x, y: x + y, #all operators
         '-': lambda x, y: x - y,
         '*': lambda x, y: x * y,
         '/': lambda x, y: x / y,
         '^': lambda x, y: x ** y,
         'uniadd' : lambda x: x,
         'unisub' : lambda x: -x }
unio = { 'uniadd', 'unisub' } #uni operations
allf = { 'max' : max, #all functions
         'min' : min,
         'gcd' : gcd,
         'lcm' : lcm }
pr = { '+': 0, #order of operations
       '-': 0,
       '*': 1,
       '/': 1,
       '^': 2,
       'uniadd' : 3,
       'unisub' : 3 }

#reverse polish calculation functions
##tokenize numbers and symbols
def tokenize(expr):
    tokenized = [] #tokenized expression
    dot = False #if there is a decimal point
    for i in expr:

