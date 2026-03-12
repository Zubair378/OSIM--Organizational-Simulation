#include <iostream>
#include "task.h"
#include "roles.h"
#include "audit.h"
#include "policyengine.h"
#include "misc.h"
#include "notification.h"
#include "message.h"
#include "timemanager.h"
#include <fstream>
#include <string>
using namespace std;

TaskCreation* Base::currentTask = nullptr;

void Base::CreateTask(string assignee_role)
{
    // ...existing code from k.cpp Base::CreateTask...
    string title, desc, status_new, assignedTo_role;
    int ttl_val;

    cout << "Enter task title: ";
    cin.ignore();
    getline(cin, title);

    cout << "Enter task description: ";
    getline(cin, desc);

    status_new = "Created";
    assignedTo_role = "---";

    cout << "Enter TTL in seconds (0 for no expiry): ";
    cin >> ttl_val;
    if (cin.fail()) {
        cout << "Invalid TTL input. Using 0 (no expiry)." << endl;
        cin.clear();
        ttl_val = 0;
    }
    cin.ignore(1024, '\n');

    int newId = getNextTaskId();
    if (currentTask != nullptr) {
        delete currentTask;
        currentTask = nullptr;
    }
    currentTask = new TaskCreation(newId, title, desc, status_new, assignee_role, assignedTo_role, ttl_val);
    if (currentTask->getTaskId() == 0) {
        delete currentTask;
        currentTask = nullptr;
    } else {
        cout << "Task creation process finished for ID: " << currentTask->getTaskId() << " & is also loaded as current task" << endl;
        a.add("Task_Created", "Bas Banaya hai to banaya hai");
    }
}

void Base::AssignTask(string new_assigner_role)
{
    // ...existing code from k.cpp Base::AssignTask...
    if (currentTask == nullptr) {
        cout << "No task is currently loaded/selected. Please find a task first." << endl;
        exit(1);
    }
    currentTask->DisplayTask();

    string new_assignedTo_role;
    cout << "Enter new 'assigned to' (Username): ";
    cin.ignore();
    getline(cin, new_assignedTo_role);
	const string dataDir = "data/";
	fstream auth((dataDir + "users.txt").c_str(), ios::in);

    while (!auth.eof()) {
        char arr1[20], arr2[20], arr3[3];
        for (int i = 0; 1; i++) {
            auth.get(arr1[i]);
            if (arr1[i] == '-') {
                arr1[i] = '\0';
                break;
            }
        }
        for (int i = 0; 1; i++) {
            auth.get(arr2[i]);
            if (arr2[i] == '-') {
                arr2[i] = '\0';
                break;
            }
        }
        auth.get(arr3[0]);
        auth.get(arr3[1]);
        arr3[2] = '\0';

        if (checkequal(&new_assignedTo_role[0], arr1)) {
            if (checkequal(arr3, "ex")) {
                new_assignedTo_role = "Base\0";
                break;
            } else if (checkequal(arr3, "di")) {
                new_assignedTo_role = "Director\0";
                break;
            } else if (checkequal(arr3, "ma")) {
                new_assignedTo_role = "Manager\0";
                break;
            } else if (checkequal(arr3, "em")) {
                new_assignedTo_role = "Employee\0";
                break;
            } else if (checkequal(arr3, "di")) {
                new_assignedTo_role = "Junior\0";
                break;
            }
        }
        char temp;
        auth.get(temp);
    }
    auth.close();

    if (pe.canassign(new_assigner_role, new_assignedTo_role)) {
        currentTask->AssignTask(new_assigner_role, new_assignedTo_role);
        a.add("Task_Assigned", "Ho gaya assigned");
    } else {
        cout << "Assignment failed due to role permission issues." << endl;
    }
}

void Base::SelectTask()
{
    // ...existing code from k.cpp Base::SelectTask...
    TaskCreation::ListAllTasks();
    int id_to_find;
    cout << "Enter task ID to find and load: ";
    cin >> id_to_find;
    if (cin.fail()) {
        cout << "Invalid ID input." << endl;
        cin.clear();
        cin.ignore(1024, '\n');
    }
    cin.ignore(1024, '\n');

    if (currentTask != nullptr) {
        delete currentTask;
        currentTask = nullptr;
    }
    currentTask = findTaskById(id_to_find);
    if (currentTask == nullptr) {
        cout << "Task with ID " << id_to_find << " not found or failed to load." << endl;
    } else {
        cout << "Task ID " << id_to_find << " loaded as current task." << endl;
    }
}

void Base::Inbox()
{
    // ...existing code from k.cpp Base::Inbox...
	const string dataDir = "data/";
    extern int logged;
    string f;
	fstream auth((dataDir + "users.txt").c_str(), ios::in);
    int ii = 0;
    int ff = 0;
	fstream no((dataDir + "noofuser.txt").c_str(), ios::in);
    int size;
    no >> size;
    no.close();
    for (int k = 0; k < size; k++) {
        char arr1[20], arr2[20], arr3[3];
        for (int i = 0; 1; i++) {
            auth.get(arr1[i]);
            if (arr1[i] == '-') {
                arr1[i] = '\0';
                break;
            }
        }
        for (int i = 0; 1; i++) {
            auth.get(arr2[i]);
            if (arr2[i] == '-') {
                arr2[i] = '\0';
                break;
            }
        }
        auth.get(arr3[0]);
        auth.get(arr3[1]);
        arr3[2] = '\0';

        if (ii != logged) {
            // ...existing code...
        } else {
			f = dataDir + string(arr1) + "_inbox.txt";
        }
        char temp;
        auth.get(temp);
        ii++;
    }
    auth.close();

    fstream inbox;
    inbox.open(f.c_str(), ios::in);

    while (inbox.peek() != EOF) {
        char arr[20];
        for (int i = 0; 1; i++) {
            inbox.get(arr[i]);
            if (arr[i] == ':')
                break;
        }
        char temp;
        inbox.get(temp);
        char mess[200] = {};
        for (int i = 0; 1; i++) {
            inbox.get(mess[i]);
            if (mess[i] == '\n') {
                mess[i] = '\0';
                break;
            }
        }
        string message = decrypt(mess);
        cout << arr << message;
        cout << "\n";
    }
    inbox.close();
}

void Base::DelegateTask(string)
{
    // Empty base implementation
}

// Derived class constructors (menus) are already in k.cpp and main.cpp, so only empty bodies here if needed.
Executive::Executive() {



}
Director::Director(){
  
	Director();
	void DelegateTask(string );
 

}
Manager::Manager() {

    Manager();
	void DelegateTask(string);

}
Employee::Employee() {

    Employee();
	void DelegateTask(string);

}
Junior::Junior() {
    Junior();
	void DelegateTask(string);



}

void Director::DelegateTask(string delegator_role) { 



    
	if (currentTask == nullptr) {
	     cout << "No task is currently loaded/selected. Please Select a task first." << endl;
	    Director();
	}
	currentTask->DisplayTask();

	string delegatee_role;
	

	cout << "Enter Username to which u want to delegate: ";
	getline(cin, delegatee_role);
	const string dataDir = "data/";
	fstream auth((dataDir + "users.txt").c_str(),ios::in);
        
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
		auth.get(arr3[0]);
		auth.get(arr3[1]);
		arr3[2]='\0';
		
		if(checkequal(&delegatee_role[0],arr1))
		{
			if(checkequal(arr3,"ex"))
			{
				delegatee_role="Executive\0";
				break;
			}
			else if(checkequal(arr3,"di"))
			{
				delegatee_role="Director\0";
				break;
			}
			else if(checkequal(arr3,"ma"))
			{
				delegatee_role="Manager\0";
				break;
			}
			else if(checkequal(arr3,"em"))
			{
				delegatee_role="Employee\0";
				break;
			}
			else if(checkequal(arr3,"di"))
			{
				delegatee_role="Junior\0";
				break;
			}
		}
		
		char temp;
		auth.get(temp);
	}
        
        auth.close();

	

	
	    if (pe.candelegate(delegator_role, delegatee_role)) { // Policy check
		currentTask->DelegateTask(delegator_role, delegatee_role);
		a.add("Task_Delegated","Nahi hua ho ga");
	    } else {
		cout << "Delegation failed due to role permission issues." << endl;
	    }
	


}
void Manager::DelegateTask(string s) { 

if (currentTask == nullptr) {
	     cout << "No task is currently loaded/selected. Please Select a task first." << endl;
	    Manager();
	}
	currentTask->DisplayTask();

	string delegator_role, delegatee_role;
	cout << "Enter delegator's role (who is performing the delegation): ";
	delegator_role="Manager";

	cout << "Enter Username to which u want to delegate: ";
	getline(cin, delegatee_role);
	const string dataDir = "data/";
	fstream auth((dataDir + "users.txt").c_str(),ios::in);
        
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
		auth.get(arr3[0]);
		auth.get(arr3[1]);
		arr3[2]='\0';
		
		if(checkequal(&delegatee_role[0],arr1))
		{
			if(checkequal(arr3,"ex"))
			{
				delegatee_role="Executive\0";
				break;
			}
			else if(checkequal(arr3,"di"))
			{
				delegatee_role="Director\0";
				break;
			}
			else if(checkequal(arr3,"ma"))
			{
				delegatee_role="Manager\0";
				break;
			}
			else if(checkequal(arr3,"em"))
			{
				delegatee_role="Employee\0";
				break;
			}
			else if(checkequal(arr3,"di"))
			{
				delegatee_role="Junior\0";
				break;
			}
		}
		
		char temp;
		auth.get(temp);
	}
        
        auth.close();

	

	
	    if (pe.candelegate(delegator_role, delegatee_role)) { // Policy check
		currentTask->DelegateTask(delegator_role, delegatee_role);
		a.add("Task_Delegated","Nahi hua ho ga");
	    } else {
		cout << "Delegation failed due to role permission issues." << endl;
	    }





 }
void Employee::DelegateTask(string s) { 


    if (currentTask == nullptr) {
	     cout << "No task is currently loaded/selected. Please Select a task first." << endl;
	    Employee();
	}
	currentTask->DisplayTask();

	string delegator_role, delegatee_role;
	cout << "Enter delegator's role (who is performing the delegation): ";
	delegator_role="Employee";

	cout << "Enter Username to which u want to delegate: ";
	getline(cin, delegatee_role);
	const string dataDir = "data/";
	fstream auth((dataDir + "users.txt").c_str(),ios::in);
        
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
		auth.get(arr3[0]);
		auth.get(arr3[1]);
		arr3[2]='\0';
		
		if(checkequal(&delegatee_role[0],arr1))
		{
			if(checkequal(arr3,"ex"))
			{
				delegatee_role="Executive\0";
				break;
			}
			else if(checkequal(arr3,"di"))
			{
				delegatee_role="Director\0";
				break;
			}
			else if(checkequal(arr3,"ma"))
			{
				delegatee_role="Manager\0";
				break;
			}
			else if(checkequal(arr3,"em"))
			{
				delegatee_role="Employee\0";
				break;
			}
			else if(checkequal(arr3,"di"))
			{
				delegatee_role="Junior\0";
				break;
			}
		}
		
		char temp;
		auth.get(temp);
	}
        
        auth.close();

	

	
	    if (pe.candelegate(delegator_role, delegatee_role)) { // Policy check
		currentTask->DelegateTask(delegator_role, delegatee_role);
		a.add("Task_Delegated","Nahi hua ho ga");
	    } else {
		cout << "Delegation failed due to role permission issues." << endl;
	    }
 }
void Junior::DelegateTask(string s) { 


      {
	if (currentTask == nullptr) {
	     cout << "No task is currently loaded/selected. Please Select a task first." << endl;
	    Junior();
	}
	currentTask->DisplayTask();

	string delegator_role, delegatee_role;
	cout << "Enter delegator's role (who is performing the delegation): ";
	delegator_role="Junior";

	cout << "Enter Username to which u want to delegate: ";
	getline(cin, delegatee_role);
	const string dataDir = "data/";
	fstream auth((dataDir + "users.txt").c_str(),ios::in);
        
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
		auth.get(arr3[0]);
		auth.get(arr3[1]);
		arr3[2]='\0';
		
		if(checkequal(&delegatee_role[0],arr1))
		{
			if(checkequal(arr3,"ex"))
			{
				delegatee_role="Junior\0";
				break;
			}
			else if(checkequal(arr3,"di"))
			{
				delegatee_role="Director\0";
				break;
			}
			else if(checkequal(arr3,"ma"))
			{
				delegatee_role="Manager\0";
				break;
			}
			else if(checkequal(arr3,"em"))
			{
				delegatee_role="Employee\0";
				break;
			}
			else if(checkequal(arr3,"di"))
			{
				delegatee_role="Junior\0";
				break;
			}
		}
		
		char temp;
		auth.get(temp);
	}
        
        auth.close();

	

	
	    if (pe.candelegate(delegator_role, delegatee_role)) { // Policy check
		currentTask->DelegateTask(delegator_role, delegatee_role);
		a.add("Task_Delegated","Nahi hua ho ga");
	    } else {
		cout << "Delegation failed due to role permission issues." << endl;
	    }
 }
 }
