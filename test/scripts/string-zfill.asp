import string

for w in 0, 3, 5:
    for s in '', '1', '123', '+123', '-123', '123456789':
        print('s = %r' % (s, ))
        print('zfill(%d) = %r' % (w, string.zfill(s, w)))
        print('---')
