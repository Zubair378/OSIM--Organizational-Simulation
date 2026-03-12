#include "user.h"
#include <iostream>
#include <fstream>
using namespace std;

// Forward declarations for used functions
void enter(char* a);
char* encrypt(char* a);
extern void a_add(string, string);

Users::Users()
{
    const string dataDir = "data/";
    char n[20], p[20], r[3];
    cout << "Enter the new User-name: ";
    cin.ignore();
    enter(n);
    cout << "Enter the password: ";
    enter(p);
    cout << "Select the role for user:\n";
    cout << "1.Director\n";
    cout << "2.Manager\n";
    cout << "3.Employee\n";
    cout << "4.Junior\n";

    int i;
    cin >> i;
    switch(i)
    {
        case 1:
            r[0] = 'd'; r[1] = 'i';
            break;
        case 2:
            r[0] = 'm'; r[1] = 'a';
            break;
        case 3:
            r[0] = 'e'; r[1] = 'm';
            break;
        case 4:
            r[0] = 'j'; r[1] = 'u';
            break;
        default:
            cout << "wrong input!...program going to shuuuu....\n";
            exit(1);
    }
    r[2] = '\0';

    string ep = encrypt(p);
    fstream add;
    add.open((dataDir + "users.txt").c_str(), ios::app);
    add << n;
    add << '-';
    add << ep;
    add << '-';
    add << r;
    add << "\n";
    add.close();
    cout << "User added Successfully!";

    fstream update;
    update.open((dataDir + "noofuser.txt").c_str(), ios::in | ios::out);
    int no1;
    update >> no1;
    no1++;
    update.close();
    fstream khaali;
    khaali.open((dataDir + "noofuser.txt").c_str(), ios::trunc | ios::out);
    khaali << no1;
    khaali.close();

    a_add("New_User_Added", "Zaroorat The bhe");
}
