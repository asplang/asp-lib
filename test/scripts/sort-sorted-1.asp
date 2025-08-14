# Test of generating a sorted list from a single-element list.

from sort import sorted

def compare(a, b):
    return a - b

lst = [42]
print(lst)
print(sorted(lst, compare))

del compare, lst
