import string

lst = ['', 'abcde', '', '123']
s = string.join(lst, 'xy')
print('Joining %s' % (lst, ))
print('s = %r' % (s, ))
print('---')
