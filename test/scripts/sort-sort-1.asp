# Test of sorting a single-element list.

from sort import sort

def compare(a, b):
    return a - b

lst = [42]
print(lst)
sort(lst, compare)
print(lst)

del compare, lst
