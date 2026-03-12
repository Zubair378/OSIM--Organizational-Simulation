#include "task.h"
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

static const string kTasksFile = "data/Tasks.txt";
static const string kTempFile = "data/Temp.txt";

// Implementations for prioritylevel
prioritylevel::prioritylevel() {
    this->priorityslevel = "low";
}

void prioritylevel::setPriorityLevel(string new_prioritylevel) {
    if (new_prioritylevel == "low" || new_prioritylevel == "medium" || new_prioritylevel == "high") {
        this->priorityslevel = new_prioritylevel;
        cout << "Priority level set to: " << this->priorityslevel << endl;
    } else {
        cout << "Invalid priority level provided: '" << new_prioritylevel << "'. Setting to default (low)." << endl;
        this->priorityslevel = "low";
    }
}

string prioritylevel::getPrioritysLevel() {
    return priorityslevel;
}

// Implementations for TaskCreation and related functions
TaskCreation::TaskCreation(int TaskID_param, string title_param, string description_param, string status_param, string assignee_param, string assignedTo_param, int ttlSeconds_param ) {
    this->taskId = 0; 

    int UniqueTaskId_file;
    string filetitle_read, filedescription_read, filestatus_read, filepriority_str_read, fileassignee_read, fileassignedto_read;
    time_t fileCreationTime_read;
    int filettlSeconds_read;

    ifstream checkFile(kTasksFile.c_str());
    bool id_exists = false;
    if (checkFile.is_open()) { 
        while(checkFile >> UniqueTaskId_file >> filetitle_read >> filedescription_read >> filestatus_read >> filepriority_str_read >> fileassignee_read >> fileassignedto_read >> fileCreationTime_read >> filettlSeconds_read) {
            if (UniqueTaskId_file == TaskID_param) {
                id_exists = true;
                break;
            }
        }
        checkFile.close();
    } 

    if (id_exists) {
        cout << "Task ID " << TaskID_param << " already exists. Task not created." << endl;
        
        return;
    }

    
    this->taskId = TaskID_param;
    this->taskTitle = title_param;
    this->taskDescription = description_param;
    this->status = status_param;
    this->assignee = assignee_param;
    this->assignedTo = assignedTo_param;
    this->creationTime = time(0); 
    this->ttlSeconds = ttlSeconds_param;

    string p_priority_input;
    cout << "Enter the priority level for new task (low || medium || high): ";
    cin >> p_priority_input;
    cin.ignore(1024, '\n'); 
    this->priority.setPriorityLevel(p_priority_input);

    
    string safeTitle = this->taskTitle;
    string safeDescription = this->taskDescription;
    

    replaceSpacesWithUnderscores(safeTitle);
    replaceSpacesWithUnderscores(safeDescription);
    

    ofstream outFile(kTasksFile.c_str(), ios::app);
    if(outFile.is_open()) {
        outFile << this->taskId << "\t"
                << safeTitle << "\t"
                << safeDescription << "\t"
                << this->status << "\t" 
                << this->priority.getPrioritysLevel() << "\t"
                << this->assignee << "\t" 
                << this->assignedTo << "\t" 
                << this->creationTime << "\t"
                << this->ttlSeconds << endl;
        cout << "Task " << this->taskId << " created and saved to file." << endl;
    } else {
        cout << "Error opening Tasks.txt for writing. Task not saved." << endl;
        this->taskId = 0; 
    }
    if(outFile.is_open()) outFile.close();
}


TaskCreation::TaskCreation(int loaded_TaskID, string loaded_title, string loaded_description,
             string loaded_status, string loaded_priority_str, string loaded_assignee,
             string loaded_assignedTo, time_t loaded_creationTime, int loaded_ttlSeconds)
    : taskId(loaded_TaskID), taskTitle(loaded_title), taskDescription(loaded_description),
      status(loaded_status), assignee(loaded_assignee), assignedTo(loaded_assignedTo),
      creationTime(loaded_creationTime), ttlSeconds(loaded_ttlSeconds) {
    
    this->priority.setPriorityLevel(loaded_priority_str);
}


void TaskCreation::AssignTask(string new_assignee, string new_assignedTo) { // Renamed parameters
    this->assignee = new_assignee;
    this->assignedTo = new_assignedTo;
    this->status = "assigned";

    
    ifstream inFile(kTasksFile.c_str());
    ofstream outFile(kTempFile.c_str());

    int FileId_iter;
    int FileTtl_iter;
    string FileTitle_iter, FileDescription_iter, FileStatus_iter, FilePriority_iter, FileAssignee_iter, FileAssignedTo_iter;
    time_t FileTime_iter;

    if (!inFile.is_open() || !outFile.is_open()) {
        cout << "Error opening files for assigning task." << endl;
        if(inFile.is_open()) inFile.close();
        if(outFile.is_open()) outFile.close();
        return;
    }

    bool taskFoundAndUpdated = false;
    while (inFile >> FileId_iter >> FileTitle_iter >> FileDescription_iter >> FileStatus_iter >> FilePriority_iter >> FileAssignee_iter >> FileAssignedTo_iter >> FileTime_iter >> FileTtl_iter) {
        if(FileId_iter == this->taskId) {
            taskFoundAndUpdated = true;
          
            
            
            outFile << FileId_iter << "\t"
                    << FileTitle_iter << "\t"       
                    << FileDescription_iter << "\t"
                    << this->status << "\t"         
                    << FilePriority_iter << "\t"    
                    << this->assignee << "\t"       
                    << this->assignedTo << "\t"     
                    << FileTime_iter << "\t"       
                    << FileTtl_iter << endl;       
        } else {
            
            outFile << FileId_iter << "\t" << FileTitle_iter << "\t" << FileDescription_iter << "\t" << FileStatus_iter << "\t" << FilePriority_iter << "\t" << FileAssignee_iter << "\t" << FileAssignedTo_iter << "\t" << FileTime_iter << "\t" << FileTtl_iter << endl;
        }
    }

    inFile.close();
    outFile.close();

    if (taskFoundAndUpdated) {
        remove(kTasksFile.c_str());
        rename(kTempFile.c_str(), kTasksFile.c_str());
        cout << "Task " << this->taskId << " assigned successfully" << endl;
    } else {
        remove(kTempFile.c_str()); 
        cout << "Error: Task " << this->taskId << " not found during assignment update." << endl;
    }
}

void TaskCreation::DelegateTask(string new_delegator,string new_delegatee) { 
    this->assignee = new_delegator; 
    this->assignedTo = new_delegatee; 
    this->status = "delegated";

    ifstream inFile(kTasksFile.c_str());
    ofstream outFile(kTempFile.c_str());
    
    int FileId_iter;
    int FileTtl_iter;
    string FileTitle_iter, FileDescription_iter, FileStatus_iter, FilePriority_iter, FileAssignee_iter, FileAssignedTo_iter;
    time_t FileTime_iter;

    if (!inFile.is_open() || !outFile.is_open()) {
        cout << "Error opening files for delegating task." << endl;
        if(inFile.is_open()) inFile.close();
        if(outFile.is_open()) outFile.close();
        return;
    }
    bool taskFoundAndUpdated = false;
    while (inFile >> FileId_iter >> FileTitle_iter >> FileDescription_iter >> FileStatus_iter >> FilePriority_iter >> FileAssignee_iter >> FileAssignedTo_iter >> FileTime_iter >> FileTtl_iter) {
        if(FileId_iter == this->taskId) {
            taskFoundAndUpdated = true;
            outFile << FileId_iter << "\t"
                    << FileTitle_iter << "\t"
                    << FileDescription_iter << "\t"
                    << this->status << "\t"         
                    << FilePriority_iter << "\t"
                    << this->assignee << "\t"      
                    << this->assignedTo << "\t"     
                    << FileTime_iter << "\t"
                    << FileTtl_iter << endl;
        } else {
            outFile << FileId_iter << "\t" << FileTitle_iter << "\t" << FileDescription_iter << "\t" << FileStatus_iter << "\t" << FilePriority_iter << "\t" << FileAssignee_iter << "\t" << FileAssignedTo_iter << "\t" << FileTime_iter << "\t" << FileTtl_iter << endl;
        }
    }
    inFile.close();
    outFile.close();

    if (taskFoundAndUpdated) {
        remove(kTasksFile.c_str());
        rename(kTempFile.c_str(), kTasksFile.c_str());
        cout << "Task " << this->taskId << " delegated successfully" << endl;
    } else {
        remove(kTempFile.c_str());
        cout << "Error: Task " << this->taskId << " not found during delegation update." << endl;
    }
}

void TaskCreation::DeleteTask() {
    ifstream inFile(kTasksFile.c_str());
    ofstream outFile(kTempFile.c_str());
    
    int FileId_iter;
    int FileTtl_iter;
    string FileTitle_iter, FileDescription_iter, FileStatus_iter, FilePriority_iter, FileAssignee_iter, FileAssignedTo_iter;
    time_t FileTime_iter;

    if (!inFile.is_open() || !outFile.is_open()) {
        cout << "Error opening files for deleting task." << endl;
        if(inFile.is_open()) inFile.close();
        if(outFile.is_open()) outFile.close();
        return;
    }
    bool taskFound = false; 
    int tasksKept = 0;
    while (inFile >> FileId_iter >> FileTitle_iter >> FileDescription_iter >> FileStatus_iter >> FilePriority_iter >> FileAssignee_iter >> FileAssignedTo_iter >> FileTime_iter >> FileTtl_iter) {
        if(FileId_iter == this->taskId) {
            taskFound = true;
           
        } else {
            tasksKept++;
            outFile << FileId_iter << "\t" << FileTitle_iter << "\t" << FileDescription_iter << "\t" << FileStatus_iter << "\t" << FilePriority_iter << "\t" << FileAssignee_iter << "\t" << FileAssignedTo_iter << "\t" << FileTime_iter << "\t" << FileTtl_iter << endl;
        }
    }
    inFile.close();
    outFile.close();

    if (taskFound) {
        remove(kTasksFile.c_str());
        if (tasksKept > 0) { 
             rename(kTempFile.c_str(), kTasksFile.c_str());
        } else { 
             remove(kTempFile.c_str()); 
             
        }
        cout << "Task with ID " << this->taskId << " deleted successfully from file." << endl;
    } else {
        remove(kTempFile.c_str()); 
        cout << "Task with ID " << this->taskId << " not found, no deletion performed from file." << endl;
    }
     
}

void TaskCreation::UpdateTaskStatus(string new_status_param) { // Renamed parameter
    this->status = new_status_param;
    

    ifstream inFile(kTasksFile.c_str());
    ofstream outFile(kTempFile.c_str());
    
    int FileId_iter;
    int FileTtl_iter;
    string FileTitle_iter, FileDescription_iter, FileStatus_iter, FilePriority_iter, FileAssignee_iter, FileAssignedTo_iter;
    time_t FileTime_iter;

    if (!inFile.is_open() || !outFile.is_open()) {
        cout << "Error opening files for updating task status." << endl;
        if(inFile.is_open()) inFile.close();
        if(outFile.is_open()) outFile.close();
        return;
    }
    bool taskFoundAndUpdated = false;
    while (inFile >> FileId_iter >> FileTitle_iter >> FileDescription_iter >> FileStatus_iter >> FilePriority_iter >> FileAssignee_iter >> FileAssignedTo_iter >> FileTime_iter >> FileTtl_iter) {
        if(FileId_iter == this->taskId) {
            taskFoundAndUpdated = true;
            outFile << FileId_iter << "\t"
                    << FileTitle_iter << "\t"
                    << FileDescription_iter << "\t"
                    << this->status << "\t"         
                    << FilePriority_iter << "\t"
                    << FileAssignee_iter << "\t"
                    << FileAssignedTo_iter << "\t"
                    << FileTime_iter << "\t"
                    << FileTtl_iter << endl;
        } else {
            outFile << FileId_iter << "\t" << FileTitle_iter << "\t" << FileDescription_iter << "\t" << FileStatus_iter << "\t" << FilePriority_iter << "\t" << FileAssignee_iter << "\t" << FileAssignedTo_iter << "\t" << FileTime_iter << "\t" << FileTtl_iter << endl;
        }
    }
    inFile.close();
    outFile.close();

    if (taskFoundAndUpdated) {
        remove(kTasksFile.c_str());
        rename(kTempFile.c_str(), kTasksFile.c_str());
        cout << "Task " << this->taskId << " status updated to: " << this->status<< endl;
    } else {
        remove(kTempFile.c_str());
         cout << "Error: Task " << this->taskId << " not found during status update." << endl;
    }
}

void TaskCreation::DisplayTask() {
    if (taskId == 0) {
        cout << "Cannot display task: Task ID is invalid (possibly creation failed or not loaded)." << endl;
        return;
    }
    cout << "\n--- Task Details (Object in Memory) ---" << endl;
    cout << "Task ID: " << taskId << endl;
    cout << "Title: " << taskTitle << endl;
    cout << "Description: " << taskDescription << endl;
    cout << "Status: " << status << endl;
    cout << "Priority: " << priority.getPrioritysLevel() << endl;
    cout << "Assigner (Role): " << assignee << endl;
    cout << "Assigned To (Role): " << assignedTo << endl;
    // ctime adds a newline character at the end of its string
    cout << "Creation Time: " << (creationTime == 0 ? "Not set" : ctime(&creationTime));
    cout << "TTL (seconds): " << ttlSeconds << (ttlSeconds == 0 ? " (No Expiry)" : "") << endl;
    cout << "---------------------------------------\n" << endl;
}

void TaskCreation::ListAllTasks() {
    ifstream file(kTasksFile.c_str());
    if (!file.is_open()) {
        cout << "Error opening tasks file or no tasks exist yet." << endl;
        return;
    }

    cout << "\n--- All Tasks (from File) ---" << endl;
    int count = 0;
    int id_file;
    int ttl_file;
    string title_file, desc_file, status_file, priority_file, assignee_file, assignedTo_file;
    time_t time_file;

    while (file >> id_file >> title_file >> desc_file >> status_file >> priority_file >> assignee_file >> assignedTo_file >> time_file >> ttl_file) {
        count++;
        cout << "Task ID: " << id_file
             << " | Title: " << replaceUnderscoresWithSpaces(title_file)
             << " | Status: " << replaceUnderscoresWithSpaces(status_file) 
             << " | Priority: " << priority_file 
             << " | Assigned To: " << replaceUnderscoresWithSpaces(assignedTo_file) 
             << endl;
    }

    if (count == 0) {
        cout << "No tasks found in Tasks.txt." << endl;
    }
    cout << "\nTotal tasks: " << count << endl;
    cout << "-----------------------------\n" << endl;
    file.close();
}

int TaskCreation::getTaskId() { return taskId; }

// Implementations for helper functions
string replaceUnderscoresWithSpaces(const string& str) {
    string result = str;
    for (int i = 0; i < result.length(); i++) {
        if (result[i] == '_') {
            result[i] = ' ';
        }
    }
    return result;
}

void replaceSpacesWithUnderscores(string& str) {
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == ' ') {
            str[i] = '_';
        }
    }
}

int getNextTaskId() {
    ifstream file(kTasksFile.c_str());
    if (!file.is_open()) {
        return 1;
    }

    int maxId = 0;
    int FileId_iter;
    string dummy_str;
    time_t dummy_time;
    int dummy_int;

    while (file >> FileId_iter >> dummy_str >> dummy_str >> dummy_str >> dummy_str >> dummy_str >> dummy_str >> dummy_time >> dummy_int) {
        if (FileId_iter > maxId) {
            maxId = FileId_iter;
        }
    }
    file.close();
    return maxId + 1;
}

void ShowExpiredTasks() {
    ifstream file(kTasksFile.c_str());
    if (!file.is_open()) {
        cout << "Error opening tasks file or no tasks exist yet." << endl;
        return;
    }

    cout << "\n--- Expired Tasks ---" << endl;
    int expired_count = 0;
    int id_file;
    int ttl_file;
    string title_file, desc_file, status_file, priority_file, assignee_file, assignedTo_file;
    time_t createdAt_file;
    time_t currentTime = time(0);

    while (file >> id_file >> title_file >> desc_file >> status_file >> priority_file >> assignee_file >> assignedTo_file >> createdAt_file >> ttl_file) {
        if (ttl_file > 0 && difftime(currentTime, createdAt_file) > ttl_file) {
            expired_count++;
            cout << "Task ID: " << id_file
                 << " | Title: " << replaceUnderscoresWithSpaces(title_file)
                 << " | Status: " << replaceUnderscoresWithSpaces(status_file)
                 << " | Priority: " << priority_file
                 << " | Expired (Created: " << ctime(&createdAt_file) << ")" << endl;
        }
    }

    if (expired_count == 0) {
        cout << "No expired tasks found." << endl;
    }
    cout << "\nTotal expired tasks: " << expired_count << endl;
    cout << "---------------------\n" << endl;
    file.close();
}

TaskCreation* findTaskById(int taskId_to_find) {
    ifstream file(kTasksFile.c_str());
    if (!file.is_open()) {
        return nullptr;
    }

    int FileId_local;
    int FileTtl_local;
    string FileTitle_local, FileDescription_local, FileStatus_local, FilePriority_local, FileAssignee_local, FileAssignedTo_local;
    time_t FileTime_local;

    while (file >> FileId_local >> FileTitle_local >> FileDescription_local >> FileStatus_local >> FilePriority_local >> FileAssignee_local >> FileAssignedTo_local >> FileTime_local >> FileTtl_local) {
        if (FileId_local == taskId_to_find) {
            file.close();
            TaskCreation* task = new TaskCreation(
                FileId_local,
                replaceUnderscoresWithSpaces(FileTitle_local),
                replaceUnderscoresWithSpaces(FileDescription_local),
                replaceUnderscoresWithSpaces(FileStatus_local),
                FilePriority_local,
                replaceUnderscoresWithSpaces(FileAssignee_local),
                replaceUnderscoresWithSpaces(FileAssignedTo_local),
                FileTime_local,
                FileTtl_local
            );
            return task;
        }
    }
    file.close();
    return nullptr;
}