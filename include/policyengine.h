#pragma once
#include <string>
using namespace std;

class policyengine {
private:
    string role[5] = {"Junior", "Employee", "Manager", "Director", "Executive"};
public:
    int getrole(string);
    bool candelegate(string, string);
    bool canassign(string, string);
    bool cansend_message(string, string, string);
    bool decrypt_message(string, string);
    bool isValidRole(string);
};
extern policyengine pe;
