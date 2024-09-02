import subprocess as sp

#FILES
wrg = 'rng'

res = 0 
while (not res):
    res = int(sp.check_output(f"python3 gen.py > test.in && python3 corpy.py < test.in > actual.out && ../{wrg} < test.in > wrong.out && diff actual.out wrong.out | wc -l", shell=True).decode())
