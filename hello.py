import sys

#fp = open('test.txt','w')
#print("Hello World! (stderr)",file=fp)
print("Hello World! (stderr)",file=sys.stderr)
print("Hello World! (stdout)",file=sys.stdout)
