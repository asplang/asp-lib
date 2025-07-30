#
# String functions.
#
# These functions are based on Python's string methods and should behave in a
# similar fashion.
#

from string_class import *

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

def find(str, sub):
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

def center(str, width, fillchar = ' '):
    assert \
        type(str) == type('') and type(fillchar) == type('') and \
        len(fillchar) == 1
    left = True
    while len(str) < width:
        if left:
            str = fillchar + str
        else:
            str += fillchar
        left = not left
    return str

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
        type(str) == type('') and type(fillchar) == type('') and \
        len(fillchar) == 1
    while len(str) < width:
        str += fillchar
    return str

def lstrip(str, chars = None):
    assert type(str) == type('')
    assert chars is None or type(chars) == type('')
    i = 0;
    for c in str:
        if not (isspace(c) if chars is None else c in chars):
            break
        i += 1
    return str[i..]

def rfind(str, sub):
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
        type(str) == type('') and type(fillchar) == type('') and \
        len(fillchar) == 1
    while len(str) < width:
        str = fillchar + str
    return str

def rstrip(str, chars = None):
    assert type(str) == type('')
    assert chars is None or type(chars) == type('')
    i = len(str);
    for c in reversed(str):
        if not (isspace(c) if chars is None else c in chars):
            break
        i -= 1
    return str[..i]

def split(str, sep = None):
    assert type(str) == type('')
    assert sep is None or (type(sep) == type('') and len(sep) > 0)
    result = []
    word = ''
    if sep is None:
        for c in str:
            if isspace(c):
                if word:
                    result <- word
                    word = ''
            else:
                word += c
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
                word += str[i]
                i += 1
        if not match:
            word += str[i..]
        if word or match:
            result <- word
    return result

def strip(str, chars = None):
    assert type(str) == type('')
    assert chars is None or type(chars) == type('')
    result = ''
    for c in str:
        if not (isspace(c) if chars is None else c in chars):
            result += c
    return result
