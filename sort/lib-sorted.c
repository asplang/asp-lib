/*
 * Asp script function library implementation: sorted function.
 *
 * Sorting is accomplished using the insertion sort algorithm.
 */

#include <asp.h>
#include <stdbool.h>
#include <stdint.h>

#if ASP_VERSION < 0x01020200
#error The sort library requires Asp engine version 1.2.2.0 or greater
#endif

/* Sort iterable to new list. */
ASP_LIB_API AspRunResult AspLib_sorted
    (AspEngine *engine,
     AspDataEntry *iterable,
     AspDataEntry *compare,
     AspDataEntry **returnValue)
{
    AspRunResult result = AspRunResult_OK;

    /* Define local state variable symbols. */
    int32_t
        stateSymbol = AspNextSymbol(engine),
        iSymbol = AspNextSymbol(engine),
        jSymbol = AspNextSymbol(engine);

    /* Create or load state values for this invocation. */
    int32_t state;
    AspDataEntry *i, *j;
    if (!AspAgain(engine))
    {
        /* Check object types. */
        if (!AspIsIterable(iterable) && !AspIsIterator(iterable) ||
            !AspIsFunction(compare))
            return AspRunResult_UnexpectedType;

        /* Create an output list. */
        *returnValue = AspNewList(engine);
        if (*returnValue == 0)
            return AspRunResult_OutOfDataMemory;

        /* Initialize state. */
        state = 0;

        /* Create the initial read iterator. */
        i = AspNewIterator(engine, iterable, false);
        if (i == 0 || !AspStoreLocal(engine, iSymbol, i, true))
            return AspRunResult_OutOfDataMemory;
        if (!AspIsTrue(engine, i))
            return AspRunResult_OK;

        j = 0;
    }
    else
    {
        /* Load state and iterators. */
        AspIntegerValue(AspLoadLocal(engine, stateSymbol), &state);
        i = AspLoadLocal(engine, iSymbol);
        j = AspLoadLocal(engine, jSymbol);
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

                /* Start searching for the next element's insertion point. */
                j = AspNewIterator(engine, *returnValue, true);
                if (j == 0 || !AspStoreLocal(engine, jSymbol, j, true))
                    return AspRunResult_OutOfDataMemory;
                state++;

                /* Fall through... */

            case 1:
                /* Check if the candidate element has been compared against all
                   the sorted elements. */
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
                    /* Keep searching for the insertion point. */
                    AspUnref(engine, AspNext(engine, j));
                    state--;
                    break;
                }

                /* Fall through... */
            }

            case 3:
            {
                /* Insert the element. */
                AspDataEntry *iValue = AspAt(engine, i);
                bool insertResult = AspInsertAt
                    (engine, j, iValue, true);
                if (!insertResult)
                    return AspRunResult_OutOfDataMemory;

                /* Prepare to handle the next element. */
                AspUnref(engine, AspNext(engine, i));
                state = 0;
                break;
            }
        }
    }

    /* Store the state values for the next invocation. */
    if (result != AspRunResult_OK)
    {
        AspDataEntry *stateEntry = AspNewInteger(engine, state);
        if (stateEntry == 0)
            return AspRunResult_OutOfDataMemory;
        if (!AspStoreLocal(engine, stateSymbol, stateEntry, true) ||
            !AspStoreLocal(engine, iSymbol, i, false))
            return AspRunResult_OutOfDataMemory;
    }

    return result;
}
