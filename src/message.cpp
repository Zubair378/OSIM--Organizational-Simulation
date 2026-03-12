#include "message.h"
#include <iostream>
#include <fstream>
#include "misc.h"
#include "policyengine.h"
#include <cstring>
using namespace std;

extern int logged;
extern policyengine pe;

Message::Message(char* a)
{
    int i1 = 0;
    for(; a[i1] != '\0'; i1++);
    sender = new char[i1];
    for(int i = 0; i < i1; i++)
        sender[i] = a[i];
    sender[i1] = '\0';

    cout << "Select the option\n";
    cout << "1.Send Info\n";
    cout << "2.Send Private Message\n";
    cout << "3.Send Alert\n";
    cout << "0.Back to Main Menu\n";
    int i;
    cin >> i;
    switch(i)
    {
        case 1:
            sendinfo();
            break;
        case 2:
            sendprivate();
            break;
        case 3:
            sendalert();
            break;
        default:
            break;
    }
}

void Message::sendinfo()
{
    const string dataDir = "data/";
    cout << "Select Role to which u want to Send Information\n";
    cout << "1.Executive\n";
    cout << "2.Director\n";
    cout << "3.Manager\n";
    cout << "4.Employee\n";
    cout << "5.Junior\n";
    int i;
    cin >> i;
    string reciever;
    if(i == 1) reciever = "Executive";
    else if(i == 2) reciever = "Director";
    else if(i == 3) reciever = "Manager";
    else if(i == 4) reciever = "Employee";
    else if(i == 5) reciever = "Junior";
    else return;

    if (pe.cansend_message("INFO", sender, reciever))
    {
        char message[100];
        cout << "Enter the information: ";
        cin.ignore();
        enter(message);
        char* u = nullptr;

        fstream auth((dataDir + "users.txt").c_str(), ios::in);
        fstream no((dataDir + "noofuser.txt").c_str(), ios::in);
        int size;
        no >> size;
        no.close();
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

        auth.open((dataDir + "users.txt").c_str(), ios::in);
        int ii = 0;
        while(!auth.eof())
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

            bool match = false;
            if(i == 1 && strcmp(arr3, "ex") == 0) match = true;
            else if(i == 2 && strcmp(arr3, "di") == 0) match = true;
            else if(i == 3 && strcmp(arr3, "ma") == 0) match = true;
            else if(i == 4 && strcmp(arr3, "em") == 0) match = true;
            else if(i == 5 && strcmp(arr3, "ju") == 0) match = true;

            if(match)
            {
                fstream mess;
                string f = dataDir + string(arr1) + "_inbox.txt";
                mess.open(f.c_str(), ios::app);
                mess << u << ": ";
                mess << encrypt(message) << "\n";
                mess.close();
            }
            char temp;
            auth.get(temp);
            ii++;
        }
        auth.close();
        if(u) delete[] u;
    }
}

void Message::sendprivate()
{
    const string dataDir = "data/";
    char* u = nullptr;
    cout << "Select User to Send Message\n";
    fstream auth((dataDir + "users.txt").c_str(), ios::in);
    int ii = 0, ff = 0;
    fstream no((dataDir + "noofuser.txt").c_str(), ios::in);
    int size;
    no >> size;
    no.close();
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

        if(ii != logged)
        {
            cout << ff+1 << '.' << arr1 << endl;
            ff++;
        }
        else
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
        ii++;
    }
    auth.close();
    int i;
    cin >> i;
    ff = 0;
    auth.open((dataDir + "users.txt").c_str(), ios::in);
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

        if(ff != logged)
        {
            if(i == ff+1)
            {
                string reciever;
                if(strcmp(arr3, "ex") == 0) reciever = "Executive";
                else if(strcmp(arr3, "di") == 0) reciever = "Director";
                else if(strcmp(arr3, "ma") == 0) reciever = "Manager";
                else if(strcmp(arr3, "em") == 0) reciever = "Employee";
                else if(strcmp(arr3, "ju") == 0) reciever = "Junior";

                if (pe.cansend_message("PRIVATE", sender, reciever))
                {
                    fstream mess;
                    string f = dataDir + string(arr1) + "_inbox.txt";
                    mess.open(f.c_str(), ios::app);
                    char message[100];
                    cout << "Enter the information: ";
                    cin.ignore();
                    enter(message);
                    mess << u << ": ";
                    mess << encrypt(message) << "\n";
                    mess.close();
                }
            }
        }
        char temp;
        auth.get(temp);
        ff++;
    }
    auth.close();
    if(u) delete[] u;
}

void Message::sendalert()
{
    const string dataDir = "data/";
    char* u = nullptr;
    cout << "Select User to Send Alert\n";
    fstream auth((dataDir + "users.txt").c_str(), ios::in);
    int ii = 0, ff = 0;
    fstream no((dataDir + "noofuser.txt").c_str(), ios::in);
    int size;
    no >> size;
    no.close();
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

        if(ii != logged)
        {
            cout << ff+1 << '.' << arr1 << endl;
            ff++;
        }
        else
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
        ii++;
    }
    auth.close();
    int i;
    cin >> i;
    ff = 0;
    auth.open((dataDir + "users.txt").c_str(), ios::in);
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

        if(ff != logged)
        {
            if(i == ff+1)
            {
                string reciever;
                if(strcmp(arr3, "ex") == 0) reciever = "Executive";
                else if(strcmp(arr3, "di") == 0) reciever = "Director";
                else if(strcmp(arr3, "ma") == 0) reciever = "Manager";
                else if(strcmp(arr3, "em") == 0) reciever = "Employee";
                else if(strcmp(arr3, "ju") == 0) reciever = "Junior";

                if (pe.cansend_message("ALERT", sender, reciever))
                {
                    fstream mess;
                    string f = dataDir + string(arr1) + "_alert.txt";
                    mess.open(f.c_str(), ios::app);
                    char message[100];
                    cout << "Enter Alert Statement: ";
                    cin.ignore();
                    enter(message);
                    mess << u << ": ";
                    mess << message << "\n";
                    mess.close();
                }
            }
        }
        char temp;
        auth.get(temp);
        ff++;
    }
    auth.close();
    if(u) delete[] u;
}
