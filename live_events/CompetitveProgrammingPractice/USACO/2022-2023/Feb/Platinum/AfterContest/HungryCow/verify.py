import subprocess as sp
for i in range(1, 23):
    res = int(sp.check_output(f"./hc < real/{i}.in > test.out && diff test.out real/{i}.out | wc -l", shell=True).decode())
    print(i, res)

