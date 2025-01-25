/*
 * Asp script function library implementation: In-place sort function.
 *
 * Sorting is accomplished using the insertion sort algorithm.
 */

#include <asp.h>
#include <stdbool.h>
#include <stdint.h>

#if ASP_VERSION < 0x01020200
#error The sort library requires Asp engine version 1.2.2.0 or greater
#endif

/* In place sort. */
ASP_LIB_API AspRunResult AspLib_sort
    (AspEngine *engine,
     AspDataEntry *list,
     AspDataEntry *compare,
     AspDataEntry **returnValue)
{
    AspRunResult result = AspRunResult_OK;

    /* Define local state variable symbols. */
    int32_t
        stateSymbol = AspNextSymbol(engine),
        iSymbol = AspNextSymbol(engine),
        niSymbol = AspNextSymbol(engine),
        jSymbol = AspNextSymbol(engine),
        pjSymbol = AspNextSymbol(engine);

    /* Create or load state values for this invocation. */
    int32_t state;
    AspDataEntry *i, *ni, *j, *pj;
    if (!AspAgain(engine))
    {
        /* Determine the number of items in the list. */
        int32_t count;
        result = AspCount(engine, list, &count);
        if (result != AspRunResult_OK)
            return result;
        if (count <= 1)
            return AspRunResult_OK;

        /* Check object types. */
        if (!AspIsList(list) || !AspIsFunction(compare))
            return AspRunResult_UnexpectedType;

        /* Initialize state. */
        state = 0;

        /* Create applicable iterators. */
        i = AspNewIterator(engine, list, false);
        if (i == 0 || !AspStoreLocal(engine, iSymbol, i, true))
            return AspRunResult_OutOfDataMemory;
        AspUnref(engine, AspNext(engine, i));
        ni = AspNewIterator(engine, i, false);
        if (ni == 0 || !AspStoreLocal(engine, niSymbol, ni, true))
            return AspRunResult_OutOfDataMemory;
        j = pj = 0;
    }
    else
    {
        /* Load state and iterators. */
        AspIntegerValue(AspLoadLocal(engine, stateSymbol), &state);
        i = AspLoadLocal(engine, iSymbol);
        ni = AspLoadLocal(engine, niSymbol);
        j = AspLoadLocal(engine, jSymbol);
        pj = AspLoadLocal(engine, pjSymbol);
    }

    bool exit = false;
    while (!exit)
    {
        switch (state)
        {
            default:
                return AspRunResult_Application;

            case 0:
                /* Check if all elements have been inserted. */
                if (!AspIsTrue(engine, i))
                {
                    exit = true;
                    break;
                }

                AspUnref(engine, AspNext(engine, ni));
                j = AspNewIterator(engine, i, true);
                if (j == 0 || !AspStoreLocal(engine, jSymbol, j, true))
                    return AspRunResult_OutOfDataMemory;
                state++;

                /* Fall through... */

            case 1:
                /* Check if the candidate element has been compared against all
                   the sorted elements. */
                pj = AspNewIterator(engine, j, false);
                if (pj == 0 || !AspStoreLocal(engine, pjSymbol, pj, true))
                    return AspRunResult_OutOfDataMemory;
                AspUnref(engine, AspNext(engine, j));
                if (!AspIsTrue(engine, j))
                    state += 2;
                else
                {
                    /* Compare the candidate element to the current sorted
                       element. */
                    AspAddPositionalArgument(engine, AspAt(engine, j), true);
                    AspAddPositionalArgument(engine, AspAt(engine, i), true);
                    state++;
                    exit = true;
                    result = AspCall(engine, compare);
                }

                break;

            case 2:
            {
                /* Fetch and consume the comparison's return value. */
                AspDataEntry *compareResultEntry;
                result = AspReturnValue(engine, &compareResultEntry);
                int32_t compareResult;
                if (!AspIntegerValue(compareResultEntry, &compareResult))
                    return AspRunResult_UnexpectedType;
                AspUnref(engine, compareResultEntry);

                if (compareResult > 0)
                {
                    /* Keep searching for the element to swap with. */
                    state--;
                    break;
                }

                /* Fall through... */
            }

            case 3:
                /* Swap elements. */
                if (!AspAtSame(engine, i, pj))
                {
                    AspDataEntry *oj = AspNewIterator(engine, pj, true);
                    if (oj == 0)
                        return AspRunResult_OutOfDataMemory;
                    AspDataEntry *iValue = AspAt(engine, i);
                    if (!AspEraseAt(engine, i) ||
                        !AspInsertAt(engine, oj, iValue, true))
                        return AspRunResult_OutOfDataMemory;
                    AspUnref(engine, oj);
                }

                /* Prepare to handle the next element. */
                i = AspNewIterator(engine, ni, false);
                if (i == 0 || !AspStoreLocal(engine, iSymbol, i, true))
                    return AspRunResult_OutOfDataMemory;
                state = 0;
                break;
        }
    }

    /* Store the state values for the next invocation. */
    if (result != AspRunResult_OK)
    {
        AspDataEntry *stateEntry = AspNewInteger(engine, state);
        if (stateEntry == 0)
            return AspRunResult_OutOfDataMemory;
        if (!AspStoreLocal(engine, stateSymbol, stateEntry, true) ||
            !AspStoreLocal(engine, niSymbol, ni, false))
            return AspRunResult_OutOfDataMemory;
    }

    return result;
}
