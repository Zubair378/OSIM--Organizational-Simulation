#include "policyengine.h"
#include <iostream>
using namespace std;

policyengine pe;

int policyengine::getrole(string role_to_check) {
    for (int i = 0; i < 5; i++) {
        if (role_to_check == this->role[i]) {
            return i;
        }
    }
    return -1;
}

bool policyengine::candelegate(string assigner, string assign_to) {
    int assignerRole = getrole(assigner);
    int assigneeRole = getrole(assign_to);

    if (assignerRole < assigneeRole) {
        cout << "Assigner (" << assigner << ") can delegate the task to assignee (" << assign_to << ")" << endl;
        return true;
    } else {
        cout << "Assigner (" << assigner << ") cannot delegate the task to assignee (" << assign_to << ")" << endl;
        return false;
    }
}

bool policyengine::canassign(string assignerRole_str, string assigneeRole_str) {
    int assignerRoleIndex = getrole(assignerRole_str);
    int assigneeRoleIndex = getrole(assigneeRole_str);

    if (assignerRoleIndex == -1 || assigneeRoleIndex == -1) {
        cout << "Invalid role provided for assignment check." << endl;
        return false;
    }

    if (assignerRoleIndex > assigneeRoleIndex) {
        cout << "Task can be assigned by " << assignerRole_str << " to " << assigneeRole_str << endl;
        return true;
    } else {
        cout << "Task cannot be assigned by " << assignerRole_str << " to " << assigneeRole_str << " (permission denied)" << endl;
        return false;
    }
}

bool policyengine::cansend_message(string message_type, string sender_role, string receiver_role) {
    int senderROLE = getrole(sender_role);
    int receiverROLE = getrole(receiver_role);

    if (message_type == "ALERT") {
        if (senderROLE >= receiverROLE && senderROLE >= 1) {
            cout << "Alert message can be sent from " << sender_role << " to " << receiver_role << endl;
            return true;
        } else {
            cout << "Alert message cannot be sent by " << sender_role << " to " << receiver_role << " (permission denied)" << endl;
            return false;
        }
    } else if (message_type == "INFO") {
        cout << "Info message can be sent from " << sender_role << " to " << receiver_role << endl;
        return true;
    } else if (message_type == "PRIVATE") {
        cout << "Private message can be sent from " << sender_role << " to " << receiver_role << endl;
        return true;
    }

    cout << "Unknown message type: " << message_type << endl;
    return false;
}

bool policyengine::decrypt_message(string, string) {
    // No actual decryption logic, just return true as placeholder
    return true;
}

bool policyengine::isValidRole(string role) {
    for (int i = 0; i < 5; i++) {
        if (role == this->role[i]) {
            return true;
        }
    }
    return false;
}
