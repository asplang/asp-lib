def compare(a, b):
    return a - b

lst = [42, 13]
print(lst)
print(sorted(lst, compare))

del compare, lst
