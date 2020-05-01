lines = []
with open('bing.txt', 'r') as b:
    for line in b:
        lines.append(line[:-1])
print(lines)
