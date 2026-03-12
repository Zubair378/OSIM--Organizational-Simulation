# OSIM - Organizational Simulation and Internal Management System

OSIM is a C++ console-based organizational workflow simulator. It models how an internal company system can manage users, role-based permissions, tasks, notifications, internal messaging, OTP-based login, and audit logging.

This project is built as a file-based academic OOP system, so all persistent data is stored in text files instead of a database.

## Overview

OSIM simulates a small organizational hierarchy and allows users to interact based on their role in that hierarchy. The system combines:

- user authentication
- OTP verification
- task creation and assignment
- task delegation with permission checks
- internal messaging
- notification logging
- audit trail tracking

The project is useful as an Object-Oriented Programming demonstration because it shows inheritance, modular design, encapsulation, file handling, and role-based access control inside one application.

## Roles in the System

The current codebase works with these organizational roles:

- Executive
- Director
- Manager
- Employee
- Junior

These roles are used by the policy engine to decide who can assign tasks, delegate work, and send messages.

## Main Features

### User Login with OTP

The application starts in the terminal and asks the user for:

- username
- password
- OTP

After correct credentials are entered, the program generates an OTP and writes it to `data/otp.txt`. The user must read the value from that file and enter it into the terminal before it expires.

### Role-Based Access Control

Permission logic is handled by the policy engine. The hierarchy is ordered as:

- Junior
- Employee
- Manager
- Director
- Executive

This hierarchy determines whether a user can:

- assign a task to another role
- delegate a task to another role
- send certain message types

### Task Management

The task module supports:

- creating tasks
- assigning tasks
- delegating tasks
- updating task status
- deleting tasks
- listing all tasks
- loading a task by ID
- checking expired tasks using TTL

Each task includes:

- task ID
- title
- description
- status
- priority
- assigner role
- assigned role
- creation timestamp
- TTL in seconds

### Internal Messaging

The messaging system supports:

- info messages
- private messages
- alert messages

Messages are written into user-specific inbox and alert files.

### Notifications

Authorized users can generate notifications. These are written to `notification.txt` with timestamps.

### Audit Trail

Important actions such as login, failed login, task creation, assignment, and delegation are recorded in `audit.txt`.

## How the Program Works

### Login Flow

1. The program starts from `main.cpp`.
2. The user enters a username and password.
3. The program reads `data/users.txt` to verify credentials.
4. The stored password is compared using the project's custom decryption logic.
5. If the credentials match, an OTP is generated.
6. The OTP is written into `data/otp.txt`.
7. The user enters the OTP in the console.
8. If the OTP is valid and not expired, login succeeds.
9. The role code from `data/users.txt` is used to select the correct role object.

### Role Dispatch

After login, the system maps the user to one of these role classes:

- `Executive`
- `Director`
- `Manager`
- `Employee`
- `Junior`

These classes inherit from a shared base role structure declared in `roles.h`.

## Project Structure

The repository is now organized into three folders:

```text
OSIM--Organizational-Simulation/
|- src/
|- include/
|- data/
|- README.md
```

| File | Purpose |
|---|---|
| `src/main.cpp` | Entry point, login flow, OTP generation, role dispatch |
| `include/user.h` / `src/user.cpp` | User creation and user-file updates |
| `include/roles.h` / `src/roles.cpp` | Base and derived role behavior, task-related actions, inbox handling |
| `include/task.h` / `src/task.cpp` | Task creation, assignment, delegation, deletion, listing, status updates, TTL handling |
| `include/message.h` / `src/message.cpp` | Info, private, and alert messaging |
| `include/notification.h` / `src/notification.cpp` | Notification creation and display |
| `include/audit.h` / `src/audit.cpp` | Audit logging and audit display |
| `include/policyengine.h` / `src/policyengine.cpp` | Role comparison and permission checks |
| `include/misc.h` / `src/misc.cpp` | Helper utilities such as input handling and simple encryption/decryption |
| `include/timemanager.h` / `src/timemanager.cpp` | Time formatting and TTL verification |

## Data Files Used by the Program

The project stores its persistent data in text files.

| File | Purpose |
|---|---|
| `data/users.txt` | Stores usernames, encrypted passwords, and role codes |
| `data/noofuser.txt` | Stores total number of users |
| `data/otp.txt` | Stores the current OTP for login |
| `data/Tasks.txt` | Stores all task records |
| `data/audit.txt` | Stores audit logs |
| `data/notification.txt` | Stores notifications |
| `data/*_inbox.txt` | Stores user inbox messages |
| `data/*_alert.txt` | Stores user alerts |

### User Record Format

`users.txt` uses this format:

```text
username-encryptedPassword-roleCode
```

Role codes:

- `ex` = Executive
- `di` = Director
- `ma` = Manager
- `em` = Employee
- `ju` = Junior

### Task Record Format

`Tasks.txt` stores records in this structure:

```text
taskId title description status priority assignee assignedTo creationTime ttlSeconds
```

Spaces in titles and descriptions are converted to underscores before writing to file.

## Existing Demo Accounts

The checked-in project data currently contains these demo users:

| Username | Password | Role |
|---|---|---|
| `admin` | `123` | Executive |
| `admin11` | `123` | Director |
| `admin22` | `123` | Manager |
| `admin33` | `123` | Employee |
| `admin44` | `123` | Junior |
| `chachu` | `1122` | Manager |

These passwords are based on the current encryption and decryption logic used in the source code.

## Requirements

To build and run this project on Windows, you need:

- Git
- a C++ compiler such as MinGW g++
- terminal access in the project folder
- all source and text data files present in the same directory

This README assumes Windows PowerShell or Command Prompt.

## Quick Start

### Clone the Repository

```powershell
git clone https://github.com/Zubair378/OSIM--Organizational-Simulation.git
```

### Move into the Project Folder

```powershell
cd OSIM--Organizational-Simulation
```

### Compile the Program

```powershell
g++ -Iinclude src/main.cpp src/audit.cpp src/message.cpp src/misc.cpp src/notification.cpp src/policyengine.cpp src/roles.cpp src/task.cpp src/timemanager.cpp src/user.cpp -o osim.exe
```

### Run the Executable

```powershell
.\osim.exe
```

## Full Windows Setup and Run Commands

```powershell
git clone https://github.com/Zubair378/OSIM--Organizational-Simulation.git
cd OSIM--Organizational-Simulation
g++ -Iinclude src/main.cpp src/audit.cpp src/message.cpp src/misc.cpp src/notification.cpp src/policyengine.cpp src/roles.cpp src/task.cpp src/timemanager.cpp src/user.cpp -o osim.exe
.\osim.exe
```

## Run from an Already Existing Local Folder

If the project is already present on your system, use:

```powershell
cd E:\oop\final
g++ -Iinclude src/main.cpp src/audit.cpp src/message.cpp src/misc.cpp src/notification.cpp src/policyengine.cpp src/roles.cpp src/task.cpp src/timemanager.cpp src/user.cpp -o osim.exe
.\osim.exe
```

## OTP Check During Login

After entering username and password, the program writes the generated OTP to `data/otp.txt`.

You can read it in PowerShell with:

```powershell
Get-Content .\data\otp.txt
```

## Example Usage

1. Run the program.
2. Login using one of the demo accounts.
3. Open `data/otp.txt` and enter the generated OTP.
4. Continue with the role-specific flow.
5. Create or manage tasks.
6. Send internal messages or alerts.
7. Review `data/Tasks.txt`, `data/audit.txt`, and `data/notification.txt` to inspect stored results.

## Current Implementation Notes

These notes are important if someone is reviewing the repository:

- The project is a console-based prototype, not a production system.
- Data is stored in plain text files instead of a database.
- OTP delivery is file-based only and is not connected to email or SMS.
- The project builds successfully with MinGW g++ on Windows.
- The current build shows warnings in `roles.cpp` related to string literal handling.
- The role classes are connected to the login flow, but some post-login menu behavior appears incomplete in the current checked-in version.
- The message encryption logic is simple and educational, not secure for real-world use.

## If `g++` Is Not Recognized

If your terminal says `g++` is not recognized:

1. Install MinGW-w64.
2. Add the MinGW `bin` folder to your system `PATH`.
3. Restart the terminal.
4. Run the compile command again.

## Suggested Future Improvements

Possible improvements for the next version:

- complete the role-specific interactive menus
- replace plain text storage with a database
- use proper password hashing
- improve OTP handling and delivery
- improve input validation and error handling
- fix the remaining compile warnings in `roles.cpp`
- standardize file formatting and naming

## Conclusion

OSIM is an academic C++ management system project that demonstrates how authentication, hierarchy-based permissions, tasks, messaging, notifications, and auditing can be combined in one file-based console application.

It is a solid OOP project for demonstrating core programming concepts and system design in a simple and understandable way.

