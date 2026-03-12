#include "audit.h"
#include "timemanager.h"
#include <fstream>
using namespace std;

Audit a;

void Audit::add(string s1, string s2)
{
    const string dataDir = "data/";
    fstream audit;
    audit.open((dataDir + "audit.txt").c_str(), ios::app);
    TimeManager t;
    string stamp = t.CurrentTime();
    char* u = nullptr; // fix: initialize to nullptr

    fstream auth;
    auth.open((dataDir + "users.txt").c_str(), ios::in);

    fstream no;
    no.open((dataDir + "noofuser.txt").c_str(), ios::in);
    int size;
    no >> size;
    no.close();
    extern int logged;
    for(int k = 0; k < size; k++)
    {
        char arr1[20], arr2[20], arr3[3];
        for(int i = 0; 1; i++)
        {
            auth.get(arr1[i]);
            if(arr1[i] == '-')
            {
                arr1[i] = '\0';
                break;
            }
        }
        for(int i = 0; 1; i++)
        {
            auth.get(arr2[i]);
            if(arr2[i] == '-')
            {
                arr2[i] = '\0';
                break;
            }
        }
        auth.get(arr3[0]);
        auth.get(arr3[1]);
        arr3[2] = '\0';

        if(k == logged)
        {
            int i1 = 0;
            for(; arr1[i1] != '\0'; i1++);
            u = new char[i1];
            for(int i = 0; i < i1; i++)
                u[i] = arr1[i];
            u[i1] = '\0';
        }

        char temp;
        auth.get(temp);
    }
    auth.close();
    string name = (u != nullptr) ? string(u) : "Unknown";
    audit << '[' << stamp << ']' << ' ' << name << ' ' << s1 << " (" << s2 << ")\n";
    audit.close();
    if(u) delete[] u;
}

void a_add(string s1, string s2) {
    a.add(s1, s2);
}

ostream& operator<<(ostream& cout, Audit a1)
{
    const string dataDir = "data/";
    fstream show;
    show.open((dataDir + "audit.txt").c_str(), ios::in);
    cout << " Date&Time            User	  Task         Details\n";
    char temp;
    while(show.get(temp))
        cout << temp;

    show.close();
    return cout;
}