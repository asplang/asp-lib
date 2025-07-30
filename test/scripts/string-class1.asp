import string
from codec import encode_u8

def print_titles():
    print(5 * ' ', end = '')
    print('alnum alpha blank cntrl digit graph lower punct space upper xdigit')

def print_lines():
    print(5 * ' ', end = '')
    print('----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ------')

for i in ..256:
    if i != 0 and i % 32 == 0: print_lines()
    if i % 32 == 0:
        print_titles(); print_lines()
    c = encode_u8(i)
    print \
        ('%s %s %s %s %s %s %s %s %s %s %s %s' % \
         (string.center(('%r' % (c,))[1..-1], 4), \
          string.center('%s' % (string.isalnum(c),), 5), \
          string.center('%s' % (string.isalpha(c),), 5), \
          string.center('%s' % (string.isblank(c),), 5), \
          string.center('%s' % (string.iscntrl(c),), 5), \
          string.center('%s' % (string.isdigit(c),), 5), \
          string.center('%s' % (string.isgraph(c),), 5), \
          string.center('%s' % (string.islower(c),), 5), \
          string.center('%s' % (string.ispunct(c),), 5), \
          string.center('%s' % (string.isspace(c),), 5), \
          string.center('%s' % (string.isupper(c),), 5), \
          string.center('%s' % (string.isxdigit(c),), 6)))
