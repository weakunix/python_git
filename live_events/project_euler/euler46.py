#imports
import numpy as np

#vars
count = 1
is_true = True

#user def functions
##check if prime
def is_prime(num):
	print(num)
	for i in range(2, int(np.sqrt(num)) + 1):
		if num % i == 0:
    	return False
  return True

#check for odd composite number that can't be written as the sum of a prime and twice a sqaure
while True:
	count += 2
	print(count)
	if not is_prime(count):
		#for i in range(1, int(np.sqrt(int(count / 2))) + 1):
		for i in range(1, int(count / 2) + 1):
			if not is_prime(count - 2 * i ** 2):
				break
				is_true = False
		if not is_true:
			break
print(count)
