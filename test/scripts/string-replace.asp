import string

s = 'axbxxcxxxdefxxxxgx'
print(s)
print(string.replace(s, 'xx', 'X'))
for i in -1..6:
    print(i, string.replace(s, 'xx', 'X', i))
print(string.replace(s, 'z', 'Z'))
