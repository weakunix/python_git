import subprocess as sp

#TEST CASE COUNT
cnt = 4

#EXECUTABLE
fi = "cn"

for i in range(1, cnt + 1):
    print(int(sp.check_output(f"./{fi} < sample/{i}.in > test.out && diff test.out ans/{i}.out | wc -l", shell=True).decode()))
sp.check_output("rm test.out", shell=True)
