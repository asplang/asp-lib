import string

for s in '', 'aa', 'a 2', 'aa2', '234', ' \t', '\t \f', '\x80':
    print('%r isalpha? %s' % (s, string.isalpha(s),))
    print('%r isalnum? %s' % (s, string.isalnum(s),))
    print('%r isascii? %s' % (s, string.isascii(s),))
    print('%r isblank? %s' % (s, string.isblank(s),))
    print('%r isdigit? %s' % (s, string.isdigit(s),))
    print('%r isprintable? %s' % (s, string.isprintable(s),))
    print('%r isspace? %s' % (s, string.isspace(s),))
    print('---')
