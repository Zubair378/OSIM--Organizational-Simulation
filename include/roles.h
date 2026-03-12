#pragma once
#include "task.h"
#include <string>
using namespace std;

class Base {
public:
    static TaskCreation* currentTask;
    void CreateTask(string);
    void AssignTask(string);
    virtual void DelegateTask(string);
    void SelectTask();
    void Inbox();
};

class Executive : public Base {
public:
    Executive();
};

class Director : public Base {
public:
    Director();
    void DelegateTask(string);
};

class Manager : public Base {
public:
    Manager();
    void DelegateTask(string);
};

class Employee : public Base {
public:
    Employee();
    void DelegateTask(string);
};

class Junior : public Base {
public:
    Junior();
    void DelegateTask(string);
};
