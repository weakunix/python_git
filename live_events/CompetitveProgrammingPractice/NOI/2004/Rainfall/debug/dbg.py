import subprocess as sp

#FILES
cor = 'wc'
wrg = 'r'

res = 0 
while (not res):
    res = int(sp.check_output(f"python3 gen.py > test.in && ./{cor} < test.in > actual.out && ../{wrg} < test.in > wrong.out && diff actual.out wrong.out | wc -l", shell=True).decode())
