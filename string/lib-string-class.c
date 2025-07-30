/*
 * Asp script function library implementation: string classification functions.
 */

#include <asp.h>
#include <ctype.h>

static AspRunResult is_in_class
    (AspEngine *, AspDataEntry *str,
     int (*classify_func)(int), bool emptyResult,
     AspDataEntry **returnValue);
static int is_ascii(int c);
static AspRunResult convert
    (AspEngine *, AspDataEntry *str,
     int (*convert_func)(int),
     AspDataEntry **returnValue);

ASP_LIB_API AspRunResult AspLib_isalnum
    (AspEngine *engine,
     AspDataEntry *str,
     AspDataEntry **returnValue)
{
    return is_in_class(engine, str, isalnum, false, returnValue);
}

ASP_LIB_API AspRunResult AspLib_isalpha
    (AspEngine *engine,
     AspDataEntry *str,
     AspDataEntry **returnValue)
{
    return is_in_class(engine, str, isalpha, false, returnValue);
}

ASP_LIB_API AspRunResult AspLib_isascii
    (AspEngine *engine,
     AspDataEntry *str,
     AspDataEntry **returnValue)
{
    return is_in_class(engine, str, is_ascii, true, returnValue);
}

ASP_LIB_API AspRunResult AspLib_isblank
    (AspEngine *engine,
     AspDataEntry *str,
     AspDataEntry **returnValue)
{
    return is_in_class(engine, str, isblank, false, returnValue);
}

ASP_LIB_API AspRunResult AspLib_iscntrl
    (AspEngine *engine,
     AspDataEntry *str,
     AspDataEntry **returnValue)
{
    return is_in_class(engine, str, iscntrl, false, returnValue);
}

ASP_LIB_API AspRunResult AspLib_isdigit
    (AspEngine *engine,
     AspDataEntry *str,
     AspDataEntry **returnValue)
{
    return is_in_class(engine, str, isdigit, false, returnValue);
}

ASP_LIB_API AspRunResult AspLib_isgraph
    (AspEngine *engine,
     AspDataEntry *str,
     AspDataEntry **returnValue)
{
    return is_in_class(engine, str, isgraph, false, returnValue);
}

ASP_LIB_API AspRunResult AspLib_islower
    (AspEngine *engine,
     AspDataEntry *str,
     AspDataEntry **returnValue)
{
    return is_in_class(engine, str, islower, false, returnValue);
}

ASP_LIB_API AspRunResult AspLib_isprintable
    (AspEngine *engine,
     AspDataEntry *str,
     AspDataEntry **returnValue)
{
    return is_in_class(engine, str, isprint, true, returnValue);
}

ASP_LIB_API AspRunResult AspLib_ispunct
    (AspEngine *engine,
     AspDataEntry *str,
     AspDataEntry **returnValue)
{
    return is_in_class(engine, str, ispunct, false, returnValue);
}

ASP_LIB_API AspRunResult AspLib_isspace
    (AspEngine *engine,
     AspDataEntry *str,
     AspDataEntry **returnValue)
{
    return is_in_class(engine, str, isspace, false, returnValue);
}

ASP_LIB_API AspRunResult AspLib_isupper
    (AspEngine *engine,
     AspDataEntry *str,
     AspDataEntry **returnValue)
{
    return is_in_class(engine, str, isupper, false, returnValue);
}

ASP_LIB_API AspRunResult AspLib_isxdigit
    (AspEngine *engine,
     AspDataEntry *str,
     AspDataEntry **returnValue)
{
    return is_in_class(engine, str, isxdigit, false, returnValue);
}

static AspRunResult is_in_class
    (AspEngine *engine, AspDataEntry *str,
     int (*classify_func)(int), bool emptyResult,
     AspDataEntry **returnValue)
{
    if (!AspIsString(str))
        return AspRunResult_UnexpectedType;

    int32_t str_len;
    #if ASP_VERSION < 0x01010000
    str_len = (int32_t)AspCount(str);
    #else
    AspRunResult result = AspCount(engine, str, &str_len);
    if (result != AspRunResult_OK)
        return result;
    #endif

    bool answer = emptyResult;
    if (str_len != 0)
    {
        answer = true;
        for (int32_t i = 0; i < str_len; i++)
        {
            if (!classify_func(AspStringElement(engine, str, i)))
            {
                answer = false;
                break;
            }
        }
    }

    return
        (*returnValue = AspNewBoolean(engine, answer)) == 0 ?
        AspRunResult_OutOfDataMemory : AspRunResult_OK;
}

static int is_ascii(int c)
{
    return (c & 0x7F) == c;
}

/*
lower - Return a copy of the string with all uppercase chars converted to lower.
upper - Return a copy of the string with all lowercase chars converted to upper.
*/

ASP_LIB_API AspRunResult AspLib_lower
    (AspEngine *engine,
     AspDataEntry *str,
     AspDataEntry **returnValue)
{
    return convert(engine, str, tolower, returnValue);
}

ASP_LIB_API AspRunResult AspLib_upper
    (AspEngine *engine,
     AspDataEntry *str,
     AspDataEntry **returnValue)
{
    return convert(engine, str, toupper, returnValue);
}

static AspRunResult convert
    (AspEngine *engine, AspDataEntry *str,
     int (*convert_func)(int),
     AspDataEntry **returnValue)
{
    if (!AspIsString(str))
        return AspRunResult_UnexpectedType;

    int32_t str_len;
    #if ASP_VERSION < 0x01010000
    str_len = (int32_t)AspCount(str);
    #else
    AspRunResult result = AspCount(engine, str, &str_len);
    if (result != AspRunResult_OK)
        return result;
    #endif

    *returnValue = AspNewString(engine, "", 0);
    if (*returnValue == 0)
        return AspRunResult_OutOfDataMemory;

    for (int32_t i = 0; i < str_len; i++)
    {
        char c = convert_func(AspStringElement(engine, str, i));
        if (!AspStringAppend(engine, *returnValue, &c, 1))
            return AspRunResult_OutOfDataMemory;
    }

    return AspRunResult_OK;
}
