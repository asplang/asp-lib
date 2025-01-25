# Test of sort stability.

def compare0(a, b):
    return a[0] - b[0]

lst = [(83, 1), (86, 1), (77, 1), (35, 1), (93, 1), (35, 2)]
print('Original:           ', lst)
print('Sorted out of place:', sorted(lst, compare0))
print('Original (again):   ', lst)
sort(lst, compare0)
print('Sorted in place:    ', lst)

del compare0, lst
