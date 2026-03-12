#include "timemanager.h"
#include <ctime>
#include <string>
using namespace std;

string TimeManager::CurrentTime()
{
    time_t now = time(0);
    tm* localTime = localtime(&now);
    char buffer[100];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localTime);

    return string(buffer);
}

bool TimeManager::TTLcheck(string s, int i, int sec1, int sec2)
{
    if(i>=19)
        return true;

    TimeManager t;
    string c = t.CurrentTime();
    int t1 = (c[i]-48)*10 + (c[i+1]-48);
    int t2 = (s[i]-48)*10 + (s[i+1]-48);

    if(i==17)
    {
        sec1 += t1;
        sec2 += t2;
        if(sec1 > sec2)
            return false;
    }

    sec1 += t1*60;
    sec2 += t2*60;

    i += 3;

    return TTLcheck(s, i, sec1, sec2);
}