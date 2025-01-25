# Test of sort stability.

def compare(a, b):
    return a <=> b

s = 'zrpqba'
print(s)
print(list(s))
print(sorted(s, compare))

del compare, s
