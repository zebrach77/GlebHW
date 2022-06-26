def merge_arrs(arr1, arr2):
    ind1 = 0
    ind2 = 0
    res = []
    while ind1 < len(arr1) and ind2 < len(arr2):
        if arr1[ind1] < arr2[ind2]:
            res.append(arr1[ind1])
            ind1 += 1
        else:
            res.append(arr2[ind2])
            ind2 += 1

    for i in range(ind1, len(arr1)):
        res.append(arr1[i])
    for i in range(ind2, len(arr2)):
        res.append(arr2[i])
    return res



def merge_sort(arr):
    if len(arr) <= 1:
        return arr
    else:
        l = len(arr) // 2
        return merge_arrs(merge_sort(arr[:l]), merge_sort(arr[l:]))


a = [int(i) for i in input().split()]
print(merge_sort(a))
