import string

strs = []
strs <- ' 1 2 \t3 '
strs <- '  '
strs <- ''
for s in strs:
    print('Splitting \'%s\'' % (s,))
    print(string.split(s))
    print(string.rsplit(s))
    print('---')

sep = ',;'
strs = []
strs <- 'abc,;d,;,;ef,;'
strs <- ',;,abc,;d,;,;ef,'
strs <- ',;'
strs <- ','
strs <- ''
for s in strs:
    print('Splitting \'%s\' with %s' % (s, sep))
    print(string.split(s, sep))
    print(string.rsplit(s, sep))
    print('---')

s = '12 23 34 45 56 67'
for max in -1..8:
    print('Splitting \'%s\', max=%d' % (s, max))
    print(string.split(s, maxsplit = max))
    print(string.rsplit(s, maxsplit = max))
    print('---')

sep = '-'
s = '12-23-34-45-56-67'
for max in -1..8:
    print('Splitting \'%s\' with %s, max=%d' % (s, sep, max))
    print(string.split(s, sep, maxsplit = max))
    print(string.rsplit(s, sep, maxsplit = max))
    print('---')

s = '12  23  34  45  56  67'
for max in -1..8:
    print('Splitting \'%s\', max=%d' % (s, max))
    print(string.split(s, maxsplit = max))
    print(string.rsplit(s, maxsplit = max))
    print('---')

sep = '<>'
s = '12<>23<>34<>45<>56<>67'
for max in -1..8:
    print('Splitting \'%s\' with %s, max=%d' % (s, sep, max))
    print(string.split(s, sep, maxsplit = max))
    print(string.rsplit(s, sep, maxsplit = max))
    print('---')
