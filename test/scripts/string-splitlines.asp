import string

strs = []
strs <- ''
strs <- '\r'
strs <- '\r\n'
strs <- '\n'
strs <- '\n\r'
strs <- '123\nabc\rxyzzy\r\n3.14\n\rzzz'
strs <- 'pqr\vstu\fvw\x1c\x1d\x1ezyx\x85zz'
strs <- 'abc\rdef\r'
strs <- 'abc\r\ndef\r\n'
strs <- 'abc\n\r'
strs <- 'abc\r\n\r'
for s in strs:
    print('Splitting %r into lines' % (s,))
    for keepends in False, True:
        for ends in None, '\r', '\n':
            print('keepends=%s ends=%r %r' % \
                (keepends, ends, \
                 string.splitlines(s, keepends = keepends, ends = ends)))
    print('---')
