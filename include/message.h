#pragma once
#include <string>
using namespace std;

class Message
{
    char* sender;
public:
    Message(char*);
    void sendinfo();
    void sendprivate();
    void sendalert();
};
