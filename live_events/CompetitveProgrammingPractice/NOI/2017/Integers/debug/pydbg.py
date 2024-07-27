import subprocess as sp

#FILES
wrg = 'i'

res = 0 
while (not res):
    res = int(sp.check_output(f"python3 gen.py > test.in && python3 pycor.py < test.in > actual.out && ../{wrg} < test.in > wrong.out && diff actual.out wrong.out | wc -l", shell=True).decode())
    print('a')
