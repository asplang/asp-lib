# Test of generating a sorted list from a 2-element unsorted list.

import sort

def compare(a, b):
    return a - b

lst = [42, 13]
print(lst)
print(sort.sorted(lst, compare))

del compare, lst
