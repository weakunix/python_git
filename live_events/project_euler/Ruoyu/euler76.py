'''
'''

#Vars

#User def functions
def f(n, MinTestVal, layer, original) -> int:
    MaxTestVal = n // 2
    count = 1
    for i in range(MinTestVal, MaxTestVal + 1):
        if n == 100:
            original = i
        print(original, i, layer)
        count += f(n - i, i, layer + 1, original)
    return count

#Main
if __name__ == '__main__':
    print(f(100, 1, 1, None))
