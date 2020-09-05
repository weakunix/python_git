#imports
import euler49 as e49

#vars
count = 0 #which number we are on
permutation = True

#brute forcing to find 6 permuted multiples
while True:
    count += 1
    permutation = True
    if len(str(count * 6)) == len(str(count)):
        for i in range(2, 7):
            if not e49.is_perm(count, count * i):
                permutation = False
                break
        if permutation:
            raise SystemExit(f'{count} is the smallest positive integer such that 1 - 6 times {count} are all permutations of each other')
