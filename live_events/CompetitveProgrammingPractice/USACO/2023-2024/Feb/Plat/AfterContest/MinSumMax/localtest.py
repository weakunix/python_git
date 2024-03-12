import subprocess as sp

for i in range(1, 25):
    print(int(sp.check_output(f"./msm < real/{i}.in > test.out && diff test.out real/{i}.out | wc -l", shell=True).decode()))
