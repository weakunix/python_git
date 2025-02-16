import subprocess as sp

#TEST CASE COUNT
cnt = 20

#EXECUTABLE
fi = "c"

#OUT FORMAT
out = "ans"

for i in range(1, cnt + 1):
    print(int(sp.check_output(f"./{fi} < {i}.in > test.out && diff test.out {i}.{out} | wc -l", shell=True).decode()))
sp.check_output("rm test.out", shell=True)
