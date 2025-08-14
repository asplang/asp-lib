import string

for w in 0, 3, 4, 5:
    for s in '', 'x', 'xy', 'xyz', 'xyzzy', 'xyzzy1':
        print('s = %r' % (s,))
        print('ljust(%d)  = %r' % (w, string.ljust(s, w)))
        print('rjust(%d)  = %r' % (w, string.rjust(s, w)))
        print('center(%d) = %r' % (w, string.center(s, w)))
        print('---')
