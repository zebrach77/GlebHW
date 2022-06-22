def select_sort(arr):
    for i in range(len(arr)-1):
        for j in range(i, len(arr)):
            if arr[j]<arr[i]:
                temp = arr[j]
                arr[j] = arr[i]
                arr[i] = temp
    return arr


a = [int(i) for i in input().split()]
print(select_sort(a))