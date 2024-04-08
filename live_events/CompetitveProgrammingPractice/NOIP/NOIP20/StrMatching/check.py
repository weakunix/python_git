import subprocess as sp

for i in range(1, 5):
    print(int(sp.check_output(f"./sm < sample/{i}.in > test.out && diff test.out ans/{i}.out | wc -l", shell=True).decode()))
sp.check_output("rm test.out", shell=True)
