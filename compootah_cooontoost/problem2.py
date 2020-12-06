def function(x):
    if x>= 10:
        return function(x - 4) + 2
    elif 6 < x < 10:
        return function(x + 1) - 1
    elif x <= 6:
        return x+3

print(function(function(function(16))))