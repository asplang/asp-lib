# Test of sort stability.

def compare(a, b):
    return a <=> b

r = ..-10:-1
print(r)
print(list(r))
print(sorted(r, compare))

del compare, r
