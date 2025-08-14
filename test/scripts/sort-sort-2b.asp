# Test of sorting a 2-element unsorted list.

from sort import sort

def compare(a, b):
    return a - b

lst = [42, 13]
print(lst)
sort(lst, compare)
print(lst)

del compare, lst
