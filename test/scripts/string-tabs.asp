import string

strs = []
strs <- ''
strs <- '\tabcdef'
strs <- 'a\tbcdef'
strs <- 'ab\tcdef'
strs <- 'abc\tdef'
strs <- 'abcd\tef'
strs <- 'abcde\tf'
strs <- 'abcdef\t'
strs <- '01\t012\r\n0123\t01234'
strs <- '1234\tx\ty\t\txyzz\n\tblah\tbla\tX'
for s in strs:
    print('Expanding tabs in %r:' % (s,))
    es = string.expandtabs(s, tabsize = 4)
    print('000000000011111111112222222222')
    print('012345678901234567890123456789')
    print('%s|' % (es, ))
    print('---')
