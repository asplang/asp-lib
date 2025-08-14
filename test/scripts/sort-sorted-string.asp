# Test of sorting a string.

import sort
import string

def compare(a, b):
    return a <=> b

s = 'zrpqba'
print(s)
print(list(s))
print(sort.sorted(s, compare))

print('---')

s = 'the quick brown fox jumps over the lazy dog'
print('%r' % (s,))
print('%r' % (string.join(sort.sorted(s, compare)),))

del compare, s
