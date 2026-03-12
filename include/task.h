#pragma once
#include <string>
#include <ctime>
using namespace std;

class prioritylevel {
private:
    string priorityslevel;
public:
    prioritylevel();
    void setPriorityLevel(string new_prioritylevel);
    string getPrioritysLevel();
};

class TaskCreation {
private:
    int taskId;
    string taskTitle;
    string taskDescription;
    string status;
    prioritylevel priority;
    string assignee;
    string assignedTo;
    time_t creationTime;
    int ttlSeconds;

public:
    TaskCreation();
    TaskCreation(int, string, string, string, string, string, int = 0);
    TaskCreation(int, string, string, string, string, string, string, time_t, int);

    void AssignTask(string, string);
    void DelegateTask(string, string);
    void DeleteTask();
    void UpdateTaskStatus(string);
    void DisplayTask();

    static void ListAllTasks();

    int getTaskId();
};

TaskCreation* findTaskById(int);
int getNextTaskId();
void ShowExpiredTasks();
string replaceUnderscoresWithSpaces(const string&);
void replaceSpacesWithUnderscores(string&);
