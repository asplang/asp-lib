# Test of sorting a small list.

import sort

def compare_ints(a, b):
    return a - b

items = [42, -7, 3, 6]
print(items)
sort.sort(items, compare_ints)
print(items)
