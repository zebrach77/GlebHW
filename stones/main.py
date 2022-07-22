def int2bin(num):
    s = ''
    temp = num
    while temp > 0:
        if temp % 2 == 0:
            s = "0" + s
        else:
            s = "1" + s
        temp = temp // 2
    return s


def all2one(item, mxlen):
    return "0"*(mxlen-len(item)) + item

def carr_count(arr, max_len):
    carr = []
    for i in range(max_len):
        count = 0
        for j in range(len(arr)):
            if arr[j][i] == "1":
                count += 1
        carr.append(count)
    return carr


arr = [int2bin(int(i)) for i in input().split()]
max_len = max(map(len, arr))
arr = list(map(lambda x: all2one(x, max_len), arr))


print(arr)


carr = []
for i in range(max_len):
    count = []
    for j in range(len(arr)):
        if arr[j][i] == "1":
            count.append(arr[j])
    carr.append(count)
print(carr)
