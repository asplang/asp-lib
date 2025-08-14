import string

s = 'the quick brown fox jumps over the lazy dog'
print('Original %s' % (s,))
print('---')

def test(table):
    print('Table: %s' % (table,))
    print('Result: %s' % (string.translate(s, table),))
    print('---')

dict1 = {:}
dict1 <- 'a' : '1'
dict1 <- 'b' : '2'
dict1 <- 'c' : '3'
dict1 <- 'z' : None

test(string.maketrans(dict1))
test(string.maketrans('abcdefghijklm', 'ABCDEFGHIJKLM'))
test(string.maketrans('abcdefghijklm', 'ABCDEFGHIJKLM', 'nopqrstuvwxyz'))
test(string.maketrans('', '', ' '))
