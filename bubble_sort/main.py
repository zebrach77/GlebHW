def bubble_sort(arr):
    for i in range(len(arr)):
        if len(arr) <= 1:
            return arr
        ind = 1
        while ind < len(arr):
            if arr[ind-1] > arr[ind]:
                temp = arr[ind-1]
                arr[ind-1] = arr[ind]
                arr[ind] = temp
            ind += 1
    return arr
a = [int(i) for i in input().split()]
print(bubble_sort(a))



