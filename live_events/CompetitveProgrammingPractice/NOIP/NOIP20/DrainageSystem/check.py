import subprocess as sp

for i in range(1, 4):
    print(int(sp.check_output(f"./ds < sample/{i}.in > test.out && diff test.out ans/{i}.out | wc -l", shell=True).decode()))
sp.check_output("rm test.out", shell=True)
