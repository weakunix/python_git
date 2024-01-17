import subprocess as sp
res = 0
while (not res):
    res = int(sp.check_output("python3 gen.py > test.in && ./b < test.in > actual.out && ../ct < test.in > wrong.out && diff actual.out wrong.out | wc -l", shell=True).decode())
