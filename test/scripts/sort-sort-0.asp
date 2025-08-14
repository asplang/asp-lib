# Test of sorting an empty list.

from sort import sort

def compare(a, b):
    return a - b

lst = []
print(lst)
sort(lst, compare)
print(lst)

del compare, lst
