# Test of sorting a 2-element presorted list.

from sort import sort

def compare(a, b):
    return a - b

lst = [13, 42]
print(lst)
sort(lst, compare)
print(lst)

del compare, lst
