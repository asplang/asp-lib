# Test of generating a sorted list from a 2-element presorted list.

import sort

def compare(a, b):
    return a - b

lst = [13, 42]
print(lst)
print(sort.sorted(lst, compare))

del compare, lst
