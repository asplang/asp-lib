import string

for s in '', 'a', 'xx', 'abc', 'axc', 'axbcdxxe', ' xx abc xx ':
    print('s = %r' % (s, ))
    print('find(\'x\') = %r' % (string.find(s, 'x'),))
    print('rfind(\'x\') = %r' % (string.rfind(s, 'x'),))
    print('find(\'xx\') = %r' % (string.find(s, 'xx'),))
    print('rfind(\'xx\') = %r' % (string.rfind(s, 'xx'),))
    print('---')
