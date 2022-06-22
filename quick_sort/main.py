import random

def find_partition(arr, l, r):
    base_elem_ind = random.randint(l, r)
    base_elem = arr[base_elem_ind]
    ind1 = l
    ind2 = r
    while ind1 <= ind2:
        while arr[ind1] < base_elem:
            ind1 += 1
        while arr[ind2] > base_elem:
            ind2 -= 1
        if ind1 <= ind2:
            temp = arr[ind1]
            arr[ind1] = arr[ind2]
            arr[ind2] = temp
            # if arr[ind1] == base_elem:
            #     base_elem_ind = ind1
            # if arr[ind2] == base_elem:
            #     base_elem_ind = ind2
            ind1 += 1
            ind2 -= 1

    return ind2, arr #???






def qsort(arr, l_ind, r_ind):
    if l_ind >= r_ind:
        return arr
    base, arr = find_partition(arr, l_ind, r_ind)
    arr = qsort(arr, l_ind, base) #???
    arr = qsort(arr, base+1, r_ind)
    return arr


a = [int(i) for i in input().split()]
print(qsort(a, 0, len(a)-1))