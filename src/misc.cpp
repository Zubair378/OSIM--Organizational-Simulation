#include "misc.h"
#include <iostream>
using namespace std;

char* encrypt(char* a)
{
    int s = 0;
    for(; a[s] != '\0'; s++)
        ;
    s++;
    char* b = new char[s];
    for(int i = 0; a[i] != '\0'; i++)
    {
        if(i % 2 == 0)
            b[i] = a[i] - 3;
        else
            b[i] = a[i];
    }
    b[s-1] = '\0';
    return b;
}

char* decrypt(char* a)
{
    int s = 0;
    for(; a[s] != '\0'; s++);
    s++;
    char* b = new char[s];
    for(int i = 0; a[i] != '\0'; i++)
    {
        if(i % 2 == 0)
            b[i] = a[i] + 3;
        else
            b[i] = a[i];
    }
    b[s-1] = '\0';
    return b;
}

void enter(char* a)
{
    for(int i = 0; 1; i++)
    {
        cin.get(a[i]);
        if(a[i] == '\n')
        {
            a[i] = '\0';
            break;
        }
    }
}

bool checkequal(char* a, char* b)
{
    int i1 = 0, i2 = 0;
    for(; a[i1] != '\0'; i1++);
    for(; b[i2] != '\0'; i2++);
    if(i1 != i2)
        return false;
    for(int i = 0; a[i] != '\0' && b[i] != '\0'; i++)
    {
        if(a[i] != b[i])
            return false;
    }
    return true;
}
