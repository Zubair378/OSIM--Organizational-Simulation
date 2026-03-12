#pragma once
#include <string>
using namespace std;

class TimeManager
{
public:
    string CurrentTime();
    bool TTLcheck(string, int = 11, int = 0, int = 0);
};