def compare(a, b):
    return a - b

lst = [42, 13]
print(lst)
sort(lst, compare)
print(lst)

del compare, lst
