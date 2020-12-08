with open("solutionBFIed.txt", "w+") as f:
    a = []
    for i in range(100):
        a.append(oct(i) + " | " + str(i) + "\n")
    f.write("".join(a))