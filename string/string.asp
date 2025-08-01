#
# String functions.
#
# These functions are based on Python's string methods and should behave in a
# similar fashion. For functions where Python's version accepts start and end
# parameters, the Asp version omits these since it is simple for the caller to
# slice the string beforehand.
#

from string_class import *

def center(str, width, fillchar = ' '):
    assert \
        type(str) == type('') and type(width) == type(0) and \
        type(fillchar) == type('') and len(fillchar) == 1
    str_len = len(str)
    right_fill_len = (width - str_len) // 2
    if right_fill_len >= 0:
        left_fill_len = width - str_len - right_fill_len
        str = left_fill_len * fillchar + str + right_fill_len * fillchar
    return str

def checktrans(table):
    if type(table) != type({:}):
        return False
    for key, value in table:
        if type(key) != type('') or len(key) != 1 or \
            value is not None and type(value) != type(''):
            return False
    return True

def count(str, sub):
    str_len = len(str)
    sub_len = len(sub)
    if sub_len > str_len:
        return 0
    count = 0
    i = 0
    while i + sub_len <= str_len:
        match = True
        for j in ..sub_len:
            if str[i + j] != sub[j]:
                match = False
                break
        else:
            j = 0
        if match:
            count += 1
            i += j
        i += 1
    return count

def endswith(str, suffix):
    assert type(str) == type('')
    suffix_len = len(suffix)
    if type(suffix) == type(''):
        return suffix_len == 0 or str[-suffix_len ..] == suffix
    else:
        suffixes = suffix
        for suffix in suffixes:
            assert type(suffix) == type('')
            if suffix_len == 0 or str[-suffix_len ..] == suffix:
                return True
        return False

def expandtabs(str, tabsize = 8):
    assert type(str) == type('') and type(tabsize) == type(0)
    result = ''
    pos = 0
    for c in str:
        if c == '\t':
            result += ' '
            pos += 1
            while pos % tabsize != 0:
                result += ' '
                pos += 1
        else:
            result += c
            pos += 1
            if c in '\r\n':
                pos = 0
    return result

def find(str, sub):
    assert type(str) == type('') and type(sub) == type('')
    str_len = len(str)
    sub_len = len(sub)
    if sub_len > str_len:
        return -1
    for i in ..str_len:
        match = True
        for j in ..sub_len:
            if str[i + j] != sub[j]:
                match = False
                break
        if match:
            return i
    return -1

def join(iterable, sep = ''):
    assert type(sep) == type('')
    result = ''
    first = True
    for str in iterable:
        assert type(str) == type('')
        if first:
            first = False
        else:
            result += sep
        result += str
    return result

def ljust(str, width, fillchar = ' '):
    assert \
        type(str) == type('') and type(width) == type(0) and \
        type(fillchar) == type('') and len(fillchar) == 1
    fill_len = width - len(str)
    if fill_len > 0:
        str += fill_len * fillchar
    return str

def lstrip(str, chars = None):
    assert \
        type(str) == type('') and \
        (chars is None or type(chars) == type(''))
    i = 0;
    for c in str:
        if not (isspace(c) if chars is None else c in chars):
            break
        i += 1
    return str[i..]

def maketrans(*args):
    args_len = len(args)
    assert args_len >= 1 and args_len <= 3
    if args_len == 1:
        table = args[0]
        assert checktrans(table)
    else:
        keys, values = args[..2]
        assert type(keys) == type('') and type(values) == type('')
        map_len = len(keys)
        assert len(values) == map_len
        table = {:}
        vi = iter(values)
        for key in keys:
            table <- key : next(vi)
        if args_len >= 3:
            keys = args[2]
            assert type(keys) == type('')
            for key in keys:
                table <- key : None
    return table

def partition(str, sep):
    pos = find(str, sep)
    return (str, '', '') if pos == -1 \
        else (str[.. pos], sep, str[pos + len(sep) ..])

def removeprefix(str, prefix):
    return str[len(prefix) ..] if startswith(str, prefix) else str

def removesuffix(str, suffix):
    return str[.. -len(suffix)] if endswith(str, suffix) else str

def replace(str, old, new):
    assert \
        type(str) == type('') and \
        type(old) == type('') and type(new) == type('')
    result = ''
    while True:
        pos = find(str, old)
        if pos < 0:
            result += str
            return result
        result += str[..pos] + new
        str = str[pos + len(old) ..]

def rfind(str, sub):
    assert type(str) == type('') and type(sub) == type('')
    str_len = len(str)
    sub_len = len(sub)
    if sub_len > str_len:
        return -1
    for i in str_len - sub_len .. -1 : -1:
        match = True
        for j in ..sub_len:
            if str[i + j] != sub[j]:
                match = False
                break
        if match:
            return i
    return -1

def rjust(str, width, fillchar = ' '):
    assert \
        type(str) == type('') and type(width) == type(0) and \
        type(fillchar) == type('') and len(fillchar) == 1
    fill_len = width - len(str)
    if fill_len > 0:
        str = fill_len * fillchar + str
    return str

def rpartition(str, sep):
    pos = rfind(str, sep)
    return ('', '', str) if pos == -1 \
        else (str[.. pos], sep, str[pos + len(sep) ..])

def rsplit(str, sep = None, maxsplit = -1):
    assert \
        type(str) == type('') and \
        (sep is None or type(sep) == type('') and len(sep) > 0) and \
        type(maxsplit) == type(0)
    if maxsplit <= 0:
        return split(str, sep, maxsplit)
    def rev(s):
        result = ''
        for c in reversed(s):
            result += c
        return result
    rev_result = split(rev(str), None if sep is None else rev(sep), maxsplit)
    result = []
    for rev_word in reversed(rev_result):
        result <- rev(rev_word)
    return result

def rstrip(str, chars = None):
    assert \
        type(str) == type('') and \
        (chars is None or type(chars) == type(''))
    i = len(str);
    for c in reversed(str):
        if not (isspace(c) if chars is None else c in chars):
            break
        i -= 1
    return str[..i]

def split(str, sep = None, maxsplit = -1):
    assert \
        type(str) == type('') and \
        (sep is None or type(sep) == type('') and len(sep) > 0) and \
        type(maxsplit) == type(0)
    result = []
    word = ''
    if sep is None:
        si = 0
        for c in str:
            if isspace(c):
                if word:
                    result <- word
                    word = ''
            else:
                if maxsplit >= 0 and len(result) >= maxsplit:
                    word += str[si..]
                    break
                word += c
            si += 1
        if word:
            result <- word
    else:
        str_len = len(str)
        sep_len = len(sep)
        match = False
        i = 0
        while i <= str_len - sep_len:
            match = str[i .. i + sep_len] == sep
            if match:
                result <- word
                word = ''
                i += sep_len
            else:
                if maxsplit >= 0 and len(result) >= maxsplit:
                    match = False
                    break
                word += str[i]
                i += 1
        if not match:
            word += str[i..]
        if word or match:
            result <- word
    return result

def splitlines(str, keepends = False, ends = None):
    assert type(str) == type('')
    keepends = not not keepends
    if ends is None:
        ends = ( \
            '\r\n', \   # ASCII CR+LF Carriage Return + Line Feed (DOS/Windows)
            '\n', \     # ASCII LF Line Feed (Unix/Linux)
            '\r', \     # ASCII CR Carriage Return (Old Macintosh)
            '\v', \     # ASCII VT Vertical Tabulation
            '\f', \     # ASCII FF Form Feed
            '\x1c', \   # ASCII FS File Separator
            '\x1d', \   # ASCII GS Group Separator
            '\x1e', \   # ASCII RS Record Separator
            '\x85', \   # ISO/IEC 6429 C1 Control Code NEL Next Line
            )
    for end in ends:
        assert type(end) == type('')
    str_len = len(str)
    result = []
    word = ''
    match = False
    i = 0
    while i <= str_len - 1:
        match = False
        for end in ends:
            end_len = len(end)
            if str[i .. i + end_len] == end:
                match = True
                break
        if match:
            if keepends:
                word += end
            result <- word
            word = ''
            i += end_len
        else:
            word += str[i]
            i += 1
    if not match:
        word += str[i..]
    if word:
        result <- word
    return result

def startswith(str, prefix):
    assert type(str) == type('')
    prefix_len = len(prefix)
    if type(prefix) == type(''):
        return str[.. prefix_len] == prefix
    else:
        prefixes = prefix
        for prefix in prefixes:
            assert type(prefix) == type('')
            if str[.. prefix_len] == prefix:
                return True
        return False

def strip(str, chars = None):
    assert \
        type(str) == type('') and \
        (chars is None or type(chars) == type(''))
    result = ''
    for c in str:
        if not (isspace(c) if chars is None else c in chars):
            result += c
    return result

def translate(str, table):
    assert type(str) == type('') and checktrans(table)
    result = ''
    for c in str:
        if c in table:
            value = table[c]
            if value is not None:
                result += value
        else:
            result += c
    return result

def zfill(str, width):
    assert type(str) == type('') and type(width) == type(0)
    str_len = len(str)
    fill_len = width - str_len
    if fill_len <= 0:
        return str
    prefixed = str_len > 0 and str[0] in '+-'
    prefix = str[.. prefixed]
    suffix = str[prefixed ..]
    return prefix + fill_len * '0' + suffix
