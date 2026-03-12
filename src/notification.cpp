#include "notification.h"
#include <fstream>
#include <ctime>
using namespace std;

notification nn;

notification::notification() {}

notification::notification(char* a)
{
    string type, sender_role, receiver_role, message;

    cout << "Enter notification type (warning/alert): ";
    cin.ignore();
    getline(cin, type);

    sender_role = string(a);
    receiver_role = "Junior";

    cout << "Enter message: ";
    getline(cin, message);

    setnotification(type, sender_role, receiver_role, message);
}

void notification::setnotification(string type, string sender, string receiver, const string& message_content) {
    const string dataDir = "data/";
    if ((type != "warning" && type != "alert")) {
        cout << "Invalid notification type: " << type << ". Must be 'warning' or 'alert'." << endl;
        return;
    }
    if (sender != "Manager" && sender != "Director" && sender != "Executive") {
        cout << "Notification sender role " << sender << " is not authorized for type " << type << "." << endl;
        return;
    }

    time_t now = time(0);
    ofstream file((dataDir + "notification.txt").c_str(), ios::app);
    if (file.is_open()) {
        file << "Notification Type: " << type << endl;
        file << "Sender Role: " << sender << endl;
        file << "Message: " << message_content << endl;
        file << "Timestamp: " << ctime(&now);
        file << "------------------------" << endl;
        cout << "Notification sent successfully and logged." << endl;
        // a.add("Notification_Sent","Ho gi majboori");
    } else {
        cout << "Error opening data/notification.txt for writing." << endl;
    }
    if(file.is_open()) file.close();
}

void notification::displayAllNotifications() {
    const string dataDir = "data/";
    ifstream file((dataDir + "notification.txt").c_str());
    if (!file.is_open()) {
        cout << "No notifications found or error opening data/notification.txt." << endl;
        return;
    }

    string line;
    cout << "\n--- All Notifications ---" << endl;
    bool notifications_exist = false;
    while (getline(file, line)) {
        notifications_exist = true;
        cout << line << endl;
    }
    if (!notifications_exist) {
        cout << "No notifications in the log file." << endl;
    }
    cout << "-----------------------" << endl;
    file.close();
}

ostream& operator<<(ostream& cout, notification nnn)
{
    nn.displayAllNotifications();
    return cout;
}
