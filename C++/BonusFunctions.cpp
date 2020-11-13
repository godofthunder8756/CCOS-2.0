#include "BonusFunctions.h"

bool strcmp(const char* str1, const char* str2) {

    uint64 len = strlen(str1);

    if (strlen(str2) != len)
        return false;

    for (uint64 i = 0; i < len; i++)
        if (str1[i] != str2[i])
            return false;

    return true;
}

uint64 strlen(const char* str)
{
    uint64 len;
    for (len = 0; str[len] != 0; len++);
    return len;
}