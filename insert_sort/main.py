def insert_to_arr(arr, ind_from, ind_to):
    for i in range(ind_to, ind_from):
        temp = arr[i]
        arr[i] = arr[ind_from]
        arr[ind_from] = temp
    return arr



def ind_to_insert(arr, elem, last_ind):
    for i in range(last_ind+1):
        if elem < arr[i]:
            return i
    return last_ind+1


def insert_sort(arr):
    if not arr:
        return arr
    ind = 1
    while ind < len(arr):
        ind_t_i = ind_to_insert(arr, arr[ind], ind)
        arr = insert_to_arr(arr, ind, ind_t_i)
        ind+=1
    return arr


a = [int(i) for i in input().split()]
print(insert_sort(a))

# 1 3 4 5 6 | 2 8 10 9
# 1 2 4 5 6 | 3 8 10 9
