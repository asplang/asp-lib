import string

s = 'abcde.xyz'
print(s)
for prefix in '', 'a', 'aa', 'abc', s, s + ' ':
    print('Starts with \'%s\'? %s' % \
        (prefix, string.startswith(s, prefix)))
    print('Prefix \'%s\' removed: \'%s\'' % \
        (prefix, string.removeprefix(s, prefix)))
print('---')
for suffix in '', 'z', 'xz', '.xyz', s, s + ' ':
    print('Ends with \'%s\'? %s' % \
        (suffix, string.endswith(s, suffix)))
    print('Suffix \'%s\' removed: \'%s\'' % \
        (suffix, string.removesuffix(s, suffix)))
print('---')
print('\'\' starts with \'\'? %s' % (string.startswith('', ''),))
print('\'\' ends with \'\'? %s' % (string.endswith('', ''),))
