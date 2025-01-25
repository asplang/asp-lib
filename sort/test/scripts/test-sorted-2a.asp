def compare(a, b):
    return a - b

lst = [13, 42]
print(lst)
print(sorted(lst, compare))

del compare, lst
