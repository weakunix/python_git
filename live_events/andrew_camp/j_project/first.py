from sympy import *
x = Symbol('x')
y = Symbol('y')
expr = 20*x - 15*y
print(sympify(expr))

expr2 = x**2/2+y/3
pprint(expr2)
