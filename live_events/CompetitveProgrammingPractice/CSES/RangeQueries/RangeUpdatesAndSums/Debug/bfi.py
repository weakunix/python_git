inpt = input().split(' ')
n = int(inpt[0])
q = int(inpt[1])
arr = input().split(' ')
arr.pop()
for i in range(len(arr)):
    arr[i] = int(arr[i])
for i in range(q):
    query = input().split(' ');
    query.pop()
    for j in range(len(query)):
        query[j] = int(query[j])
    if (query[0] == 3):
        ans = 0
        for j in range(query[1] - 1, query[2]):
            ans += arr[j]
        print(ans)
        continue
    elif (query[0] == 1):
        for j in range(query[1] - 1, query[2]):
            arr[j] += query[3]
    else:
        for j in range(query[1] - 1, query[2]):
            arr[j] = query[3]
