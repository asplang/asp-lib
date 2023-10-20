#include "crc.h"

#include <asp.h>
#include <stdint.h>
#include <stdbool.h>

static AspRunResult remake_crc_spec(AspEngine *, AspDataEntry *, crc_spec_t *);

ASP_LIB_API AspRunResult AspLib_crc_make_spec
    (AspEngine *engine,
     AspDataEntry *width, AspDataEntry *poly,
     AspDataEntry *init,
     AspDataEntry *refin, AspDataEntry *refout,
     AspDataEntry *xorout,
     AspDataEntry **returnValue)
{
    if (!AspIsInteger(width) ||
        !AspIsInteger(poly) ||
        !AspIsInteger(init) ||
        !AspIsBoolean(refin) ||
        !AspIsBoolean(refout) ||
        !AspIsInteger(xorout))
        return AspRunResult_UnexpectedType;
    int32_t signedWidthValue;
    AspIntegerValue(width, &signedWidthValue);
    if (signedWidthValue <= 0 || signedWidthValue > 32)
        return AspRunResult_ValueOutOfRange;
    uint8_t widthValue = (uint8_t)*(uint32_t *)&signedWidthValue;
    uint32_t polyValue, initValue, xoroutValue;
    AspIntegerValue(poly, (uint32_t *)&polyValue);
    AspIntegerValue(init, (uint32_t *)&initValue);
    AspIntegerValue(xorout, (uint32_t *)&xoroutValue);
    bool refinValue = AspIsTrue(engine, refin);
    bool refoutValue = AspIsTrue(engine, refout);

    crc_spec_t spec = crc_make_spec
        (widthValue, polyValue,
         initValue, refinValue, refoutValue, xoroutValue);

    /* Prepare to create a spec tuple. */
    AspDataEntry *specTuple = AspNewTuple(engine);
    if (specTuple == 0)
        return AspRunResult_OutOfDataMemory;

    /* Pack the width, shift, refin, and refout parameters into word 0. */
    {
        uint32_t wordValue = spec.width | spec.shift << 8;
        if (spec.refin)
            wordValue |= 1 << 16;
        if (spec.refout)
            wordValue |= 1 << 17;
        AspDataEntry *word = AspNewInteger(engine, *(int32_t *)&wordValue);
        if (word == 0)
            return AspRunResult_OutOfDataMemory;
        bool appendSuccess = AspTupleAppend
            (engine, specTuple, word, true);
        if (!appendSuccess)
            return AspRunResult_OutOfDataMemory;
    }

    /* Add the mask as word 1. */
    {
        AspDataEntry *word = AspNewInteger(engine, *(int32_t *)&spec.mask);
        if (word == 0)
            return AspRunResult_OutOfDataMemory;
        bool appendSuccess = AspTupleAppend
            (engine, specTuple, word, true);
        if (!appendSuccess)
            return AspRunResult_OutOfDataMemory;
    }

    /* Pack the byte table four entries to a word, and add the table as
       word 2. */
    {
        AspDataEntry *byteTable = AspNewTuple(engine);
        if (byteTable == 0)
            return AspRunResult_OutOfDataMemory;
        for (unsigned i = 0;
             i < sizeof spec.byte_table / sizeof *spec.byte_table;
             i += 4)
        {
            uint32_t entryValue =
                spec.byte_table[i] |
                spec.byte_table[i + 1] << 8 |
                spec.byte_table[i + 2] << 16 |
                spec.byte_table[i + 3] << 24;
            AspDataEntry *element = AspNewInteger
                (engine, *(int32_t *)&entryValue);
            if (element == 0)
                return AspRunResult_OutOfDataMemory;
            bool elementAppendSuccess = AspTupleAppend
                (engine, byteTable, element, true);
            if (!elementAppendSuccess)
                return AspRunResult_OutOfDataMemory;
        }

        bool appendSuccess = AspTupleAppend
            (engine, specTuple, byteTable, true);
        if (!appendSuccess)
            return AspRunResult_OutOfDataMemory;
    }

    /* Copy the CRC table as word 3. */
    {
        AspDataEntry *crcTable = AspNewTuple(engine);
        if (crcTable == 0)
            return AspRunResult_OutOfDataMemory;
        for (unsigned i = 0;
             i < sizeof spec.crc_table / sizeof *spec.crc_table;
             i++)
        {
            AspDataEntry *element = AspNewInteger
                (engine, *(int32_t *)&spec.crc_table[i]);
            if (element == 0)
                return AspRunResult_OutOfDataMemory;
            bool elementAppendSuccess = AspTupleAppend
                (engine, crcTable, element, true);
            if (!elementAppendSuccess)
                return AspRunResult_OutOfDataMemory;
        }

        bool appendSuccess = AspTupleAppend
            (engine, specTuple, crcTable, true);
        if (!appendSuccess)
            return AspRunResult_OutOfDataMemory;
    }

    /* Add the init value as word 4. */
    {
        AspDataEntry *word = AspNewInteger(engine, *(int32_t *)&spec.init);
        if (word == 0)
            return AspRunResult_OutOfDataMemory;
        bool appendSuccess = AspTupleAppend
            (engine, specTuple, word, true);
        if (!appendSuccess)
            return AspRunResult_OutOfDataMemory;
    }

    /* Add the xorout value as word 5. */
    {
        AspDataEntry *word = AspNewInteger(engine, *(int32_t *)&spec.xorout);
        if (word == 0)
            return AspRunResult_OutOfDataMemory;
        bool appendSuccess = AspTupleAppend
            (engine, specTuple, word, true);
        if (!appendSuccess)
            return AspRunResult_OutOfDataMemory;
    }

    *returnValue = specTuple;
    return AspRunResult_OK;
}

static AspRunResult remake_crc_spec
    (AspEngine *engine, AspDataEntry *specTuple, crc_spec_t *spec)
{
    if (!AspIsTuple(specTuple))
        return AspRunResult_UnexpectedType;

    /* Extract the width, shift, refin, and refout parameters from word 0. */
    {
        AspDataEntry *word = AspElement(engine, specTuple, 0);
        if (word == 0 || !AspIsInteger(word))
            return AspRunResult_UnexpectedType;
        uint32_t wordValue;
        AspIntegerValue(word, (int32_t *)&wordValue);
        spec->width = wordValue & 0xFF;
        spec->shift = wordValue >> 8 & 0xFF;
        spec->refin = (wordValue & 0x10000) != 0;
        spec->refout = (wordValue & 0x20000) != 0;
    }

    /* Extract the mask from word 1. */
    {
        AspDataEntry *word = AspElement(engine, specTuple, 1);
        if (word == 0 || !AspIsInteger(word))
            return AspRunResult_UnexpectedType;
        AspIntegerValue(word, (int32_t *)&spec->mask);
    }

    /* Extract the byte table from word 2. */
    {
        AspDataEntry *byteTable = AspElement(engine, specTuple, 2);
        if (byteTable == 0 || !AspIsTuple(byteTable))
            return AspRunResult_UnexpectedType;
        for (unsigned i = 0;
             i < sizeof spec->byte_table / sizeof *spec->byte_table / 4;
             i++)
        {
            AspDataEntry *element = AspElement(engine, byteTable, i);
            if (element == 0 || !AspIsInteger(element))
                return AspRunResult_UnexpectedType;
            uint32_t bytes;
            AspIntegerValue(element, (int32_t *)&bytes);
            int baseIndex = i * 4;
            spec->byte_table[baseIndex] = bytes & 0xFF;
            spec->byte_table[baseIndex + 1] = bytes >> 8 & 0xFF;
            spec->byte_table[baseIndex + 2] = bytes >> 16 & 0xFF;
            spec->byte_table[baseIndex + 3] = bytes >> 24 & 0xFF;
        }
    }

    /* Copy the CRC table from word 3. */
    {
        AspDataEntry *crcTable = AspElement(engine, specTuple, 3);
        if (crcTable == 0 || !AspIsTuple(crcTable))
            return AspRunResult_UnexpectedType;
        for (unsigned i = 0;
             i < sizeof spec->crc_table / sizeof *spec->crc_table;
             i++)
        {
            AspDataEntry *element = AspElement(engine, crcTable, i);
            if (element == 0 || !AspIsInteger(element))
                return AspRunResult_UnexpectedType;
            AspIntegerValue(element, (int32_t *)&spec->crc_table[i]);
        }
    }

    /* Extract the init value from word 4. */
    {
        AspDataEntry *word = AspElement(engine, specTuple, 4);
        if (word == 0 || !AspIsInteger(word))
            return AspRunResult_UnexpectedType;
        AspIntegerValue(word, (int32_t *)&spec->init);
    }

    /* Extract the xorout value from word 5. */
    {
        AspDataEntry *word = AspElement(engine, specTuple, 5);
        if (word == 0 || !AspIsInteger(word))
            return AspRunResult_UnexpectedType;
        AspIntegerValue(word, (int32_t *)&spec->xorout);
    }

    return AspRunResult_OK;
}

ASP_LIB_API AspRunResult AspLib_crc_calc
    (AspEngine *engine,
     AspDataEntry *specTuple, AspDataEntry *s,
     AspDataEntry **returnValue)
{
    if (!AspIsString(s))
        return AspRunResult_UnexpectedType;
    crc_spec_t spec;
    AspRunResult remakeSpecResult = remake_crc_spec
        (engine, specTuple, &spec);
    if (remakeSpecResult != AspRunResult_OK)
        return remakeSpecResult;

    /* Calculate CRC. */
    crc_session_t session;
    crc_start(&spec, &session);
    char buffer[16];
    for (unsigned i = 0; i < AspCount(s); i += sizeof buffer)
    {
        size_t size;
        AspStringValue(engine, s, &size, buffer, i, sizeof buffer);
        crc_add(&spec, &session, buffer, (unsigned)size);
    }
    crc_arg_t crcValue = crc_finish(&spec, &session);

    /* Return CRC value. */
    *returnValue = AspNewInteger(engine, *(int32_t *)&crcValue);
    if (*returnValue == 0)
        return AspRunResult_OutOfDataMemory;

    return AspRunResult_OK;
}

ASP_LIB_API AspRunResult AspLib_crc_start
    (AspEngine *engine,
     AspDataEntry *specTuple,
     AspDataEntry **returnValue)
{
    crc_spec_t spec;
    AspRunResult remakeSpecResult = remake_crc_spec
        (engine, specTuple, &spec);
    if (remakeSpecResult != AspRunResult_OK)
        return remakeSpecResult;

    /* Create CRC session. */
    crc_session_t session;
    crc_start(&spec, &session);

    /* Return the session as a list. */
    *returnValue = AspNewList(engine);
    AspDataEntry *crc = AspNewInteger(engine, *(int32_t *)&session.crc);
    if (*returnValue == 0 || crc == 0)
        return AspRunResult_OutOfDataMemory;
    bool appendSuccess = AspListAppend
        (engine, *returnValue, crc, true);
    if (!appendSuccess)
        return AspRunResult_OutOfDataMemory;

    return AspRunResult_OK;
}

ASP_LIB_API AspRunResult AspLib_crc_add
    (AspEngine *engine,
     AspDataEntry *specTuple, AspDataEntry *sessionList, AspDataEntry *s,
     AspDataEntry **returnValue)
{
    if (!AspIsString(s) || !AspIsList(sessionList))
        return AspRunResult_UnexpectedType;
    crc_spec_t spec;
    AspRunResult remakeSpecResult = remake_crc_spec
        (engine, specTuple, &spec);
    if (remakeSpecResult != AspRunResult_OK)
        return remakeSpecResult;
    AspDataEntry *crc = AspElement(engine, sessionList, 0);
    if (crc == 0 || !AspIsInteger(crc))
        return AspRunResult_UnexpectedType;

    /* Add to the CRC. */
    crc_session_t session;
    AspIntegerValue(crc, (int32_t *)&session.crc);
    char buffer[16];
    for (unsigned i = 0; i < AspCount(s); i += sizeof buffer)
    {
        size_t size;
        AspStringValue(engine, s, &size, buffer, i, sizeof buffer);
        crc_add(&spec, &session, buffer, (unsigned)size);
    }

    /* Update the session. */
    bool eraseSuccess = AspListErase(engine, sessionList, 0);
    if (!eraseSuccess)
        return AspRunResult_Application;
    crc = AspNewInteger(engine, *(int32_t *)&session.crc);
    if (crc == 0)
        return AspRunResult_OutOfDataMemory;
    bool appendSuccess = AspListAppend
        (engine, sessionList, crc, true);
    if (!appendSuccess)
        return AspRunResult_OutOfDataMemory;

    return AspRunResult_OK;
}

ASP_LIB_API AspRunResult AspLib_crc_finish
    (AspEngine *engine,
     AspDataEntry *specTuple, AspDataEntry *sessionList,
     AspDataEntry **returnValue)
{
    if (!AspIsList(sessionList))
        return AspRunResult_UnexpectedType;
    crc_spec_t spec;
    AspRunResult remakeSpecResult = remake_crc_spec
        (engine, specTuple, &spec);
    if (remakeSpecResult != AspRunResult_OK)
        return remakeSpecResult;
    AspDataEntry *crc = AspElement(engine, sessionList, 0);
    if (crc == 0 || !AspIsInteger(crc))
        return AspRunResult_UnexpectedType;

    /* Finish CRC calculation. */
    crc_session_t session;
    AspIntegerValue(crc, (int32_t *)&session.crc);
    crc_arg_t crcValue = crc_finish(&spec, &session);

    /* Return CRC value. */
    *returnValue = AspNewInteger(engine, *(int32_t *)&crcValue);
    if (*returnValue == 0)
        return AspRunResult_OutOfDataMemory;

    return AspRunResult_OK;
}
