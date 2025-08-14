import string

for s in '', 'a', 'axc', 'axbcdxxe', ' xx abc xx ', 'xxxxxx', 'xxxxxxx':
    print('s = %r' % (s, ))
    print('count(\'x\') = %r' % (string.count(s, 'x'), ))
    print('count(\'xx\') = %r' % (string.count(s, 'xx'), ))
    print('---')
