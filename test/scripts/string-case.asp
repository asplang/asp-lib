import string

for s in '', 'AbCd12_xX', '123':
    print('s = %r' % (s, ))
    print('lower(s) = %r' % (string.lower(s), ))
    print('upper(s) = %r' % (string.upper(s), ))
    print('---')
