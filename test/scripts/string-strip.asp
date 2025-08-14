import string

for s in ' \tabc', 'abc \t', ' \tabc \t':
    print('s = %r' % (s,))
    print('lstrip(s) = %r' % (string.lstrip(s),))
    print('lstrip(s, \'a\') = %r' % (string.lstrip(s, 'a'),))
    print('rstrip(s) = %r' % (string.rstrip(s),))
    print('rstrip(s, \'c\') = %r' % (string.rstrip(s, 'c'),))
    print('strip(s) = %r' % (string.strip(s),))
    print('strip(s, \'ac\') = %r' % (string.strip(s, 'ac'),))
    print('---')
