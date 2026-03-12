#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "misc.h"
#include "timemanager.h"
#include "audit.h"
#include "user.h"
#include "notification.h"
#include "message.h"
#include "policyengine.h"
#include "task.h"
#include "roles.h"
using namespace std;

// Declare global variable for audit logging
int logged = 0;

extern int logged;
extern Audit a;

int main()
{
    const string dataDir = "data/";
    int iii=0;
    int raw=0;
    while(iii<3)
    {
        cout<<"\n\n";
		cout<<"	 __      __       .__                                  __           .____                 .__         __________                        \n";
		cout<<"	/  \\    /  \\ ____ |  |   ____  ____   _____   ____   _/  |_  ____   |    |    ____   ____ |__| ____   \\______   \\_____     ____   ____  \n";
		cout<<"	\\   \\/\\/   // __ \\|  | _/ ___\\/  _ \\ /     \\_/ __ \\  \\   __\\/  _ \\  |    |   /  _ \\ / ___\\|  |/    \\   |     ___/\\__  \\   / ___\\_/ __ \\ \n";
		cout<<"	 \\        /\\  ___/|  |_\\  \\__(  <_> )  Y Y  \\  ___/   |  | (  <_> ) |    |__(  <_> ) /_/  >  |   |  \\  |    |     / __ \\_/ /_/  >  ___/ \n";
		cout<<"	  \\__/\\  /  \\___  >____/\\___  >____/|__|_|  /\\___  >  |__|  \\____/  |_______ \\____/\\___  /|__|___|  /  |____|    (____  /\\___  / \\___  >\n";
		cout<<"	       \\/       \\/          \\/            \\/     \\/                         \\/    /_____/         \\/                  \\//_____/      \\/ \n";
		cout<<"\n\n";
		char name[20],pass[20];
		cout<<"Enter User-Name: ";
		enter(name);
		cout<<"Enter Password: ";
		enter(pass);
		

        fstream auth;
        auth.open((dataDir + "users.txt").c_str(),ios::in);
        int ii=0;
        int c=0;
        while(!auth.eof())
        {
            char arr1[20],arr2[20],arr3[3];
            for(int i=0;1;i++)
            {
                auth.get(arr1[i]);
                if(arr1[i]=='-')
                {
                    arr1[i]='\0';
                    break;
                }
            }
            for(int i=0;1;i++)
            {
                auth.get(arr2[i]);
                if(arr2[i]=='-')
                {
                    arr2[i]='\0';
                    break;
                }
            }
            char* arr4=decrypt(arr2);
            auth.get(arr3[0]);
            auth.get(arr3[1]);
            arr3[2]='\0';

            if(checkequal(arr1,name) && checkequal(arr4,pass))
            {
                TimeManager t;
                string s=t.CurrentTime();
                s[17]+=3;
                int pp=(s[17]-48)*10+(s[18]-48);
                if(pp>=60)
                {
                    if(s[15]=='9')
                    {
                        if(s[14]=='5')
                        {
                            s[12]+=1;
                            s[14]='0';	
                        }
                        else
                        s[14]+=1;
                        s[15]='0';
                    }
                    else
                    {
                        s[15]+=1;
                    }
                }
                pp=pp%60;
                s[17]=(pp/10)+48;
                s[18]=pp%10+48;
                srand(time(0));
                int OTP=rand()%99999+100000;
                fstream otp;
                otp.open((dataDir + "otp.txt").c_str(),ios::trunc|ios::out);
                otp<<OTP;
                otp.close();

                cout<<"Enter otp (after 30 sec,it will expire)";
                int oo;
                cin>>oo;

                if(t.TTLcheck(s))
                {
                    if(oo==OTP)
                    {
                        cout<<"OTP verified!!\n";
                        c++;
                        a.add("Login","Kuch to Waja ho gi");
                        cout<<"\t\t\t\tSuccessfull login!\n";
                        logged=ii;
                        if(checkequal(arr3, (char*)"ex"))
                        {
                            // Executive panel
                            Base* e=new Executive;
                            delete e;
                        }
                        else if(checkequal(arr3, (char*)"ma"))
                        {
                            Base* m=new Manager ;
                            delete m;
                        }
                        else if(checkequal(arr3, (char*)"di"))
                        {
                            Base* d=new Director;
                            delete d;
                        }
                        else if(checkequal(arr3, (char*)"em"))
                        {
                            Base* e=new Employee;
                            delete e;
                        }
                        else if(checkequal(arr3, (char*)"ju"))
                        {
                            Base* j=new Junior;
                            delete j;
                        }
                    }
                    else
                    {
                        cout<<"Incorrect OTP!!\n";
                        cin.ignore();
                        break;
                    }
                }
                else
                {
                    cout<<"OTP Expired!!\nTry to Login again...\n";
                }

                iii=0;
                break;
            }
            delete arr4;
            char temp;
            auth.get(temp);
            ii++;
            raw++;
        }
        if(!c)
        {
            cout<<"Invalid User\n";
            a.add("Failed_login","Koi to kuch karne ki try kar raha hai");
        }
        auth.close();
        iii++;
    }
    return 0;
}
