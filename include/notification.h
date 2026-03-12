#pragma once
#include <string>
#include <iostream>
using namespace std;

class notification {
public:
    notification();
    notification(char*);
    void setnotification(string type, string sender, string receiver, const string& message_content);
    void displayAllNotifications();
    friend ostream& operator<<(ostream&, notification);
};
extern notification nn;
