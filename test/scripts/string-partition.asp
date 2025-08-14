import string

for s in '', 'a', 'axc', 'axbcdxxe', ' xx abc xx ', 'xx abc xx':
    print('s = %r' % (s, ))
    print('partition(\'x\') = %s' % (string.partition(s, 'x'),))
    print('rpartition(\'x\') = %s' % (string.rpartition(s, 'x'),))
    print('partition(\'xx\') = %s' % (string.partition(s, 'xx'),))
    print('rpartition(\'xx\') = %s' % (string.rpartition(s, 'xx'),))
    print('---')
