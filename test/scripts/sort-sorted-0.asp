# Test of generating a sorted list from an empty list.

from sort import sorted

def compare(a, b):
    return a - b

lst = []
print(lst)
print(sorted(lst, compare))

del compare, lst
