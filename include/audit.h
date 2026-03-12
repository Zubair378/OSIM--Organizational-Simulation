#pragma once
#include <string>
#include <iostream>
using namespace std;

class Audit
{
public:
    void add(string, string);
    friend ostream& operator<<(ostream&, Audit);
};
extern Audit a;
void a_add(string, string);