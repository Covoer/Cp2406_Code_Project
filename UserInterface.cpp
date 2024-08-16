#include <iostream>
#include <fstream>
#include <stdexcept>
#include "my_debugger.h"
#include "Database.h"

using namespace std;
using namespace Records;

int displayMenu(const User& user);
void doHire(Database& db);
void doFire(Database& db);
void doPromote(Database& db);
void generateDatabase(Database& db);
void saveDatabaseToFile(const Database& db);
void loadDatabaseFromFile(Database& db);
void editEmployee(Database& db);
void searchEmployees(Database& db);
void createUser(Database& db);
void editUser(Database& db);
void deleteUser(Database& db);

int main()
{
    log("started");
    Database employeeDB;

    // Load users from file
    employeeDB.loadUsersFromFile("users.txt");

    User* loggedInUser = nullptr;
    string username, password;
    bool done = false;

    // Loop until the user successfully logs in or decides to exit
    while (!done) {
        cout << "Username: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;

        loggedInUser = employeeDB.authenticateUser(username, password);

        if (!loggedInUser) {
            cerr << "Invalid username or password." << endl;
            char choice;
            cout << "Do you want to try again? (y/n): ";
            cin >> choice;

            if (choice == 'n' || choice == 'N') {
                done = true;  // Exit the loop if the user chooses not to try again
            }
        } else {
            done = true;  // Exit the loop when the user successfully logs in
        }
    }

    if (!loggedInUser) {
        cout << "Exiting the program. Goodbye!" << endl;
        return 0;  // Exit the program if the user decides not to try again
    }

    // Once logged in, proceed with the main program
    cout << "Welcome, " << loggedInUser->getUsername() << "! You are logged in as " << loggedInUser->getRole() << "." << endl;

    done = false;  // Reset the done flag for the main menu loop
    while (!done) {
        int selection = displayMenu(*loggedInUser);
        switch (selection) {
        case 0:
            log("case 0");
            done = true;
            break;
        case 1:
            if (loggedInUser->getRole() == "Manager") doHire(employeeDB);
            else cout << "Access Denied." << endl;
            break;
        case 2:
            if (loggedInUser->getRole() == "Manager") doFire(employeeDB);
            else cout << "Access Denied." << endl;
            break;
        case 3:
            if (loggedInUser->getRole() == "Manager") doPromote(employeeDB);
            else cout << "Access Denied." << endl;
            break;
        case 4:
            employeeDB.displayAll();
            break;
        case 5:
            employeeDB.displayCurrent();
            break;
        case 6:
            employeeDB.displayFormer();
            break;
        case 7:
            if (loggedInUser->getRole() == "Manager") generateDatabase(employeeDB);
            else cout << "Access Denied." << endl;
            break;
        case 8:
            if (loggedInUser->getRole() == "Manager") saveDatabaseToFile(employeeDB);
            else cout << "Access Denied." << endl;
            break;
        case 9:
            if (loggedInUser->getRole() == "Manager") loadDatabaseFromFile(employeeDB);
            else cout << "Access Denied." << endl;
            break;
        case 10:
            if (loggedInUser->getRole() == "Manager") editEmployee(employeeDB);
            else cout << "Access Denied." << endl;
            break;
        case 11:
            searchEmployees(employeeDB);
            break;
        case 12:
            if (loggedInUser->getRole() == "Manager") createUser(employeeDB);
            else cout << "Access Denied." << endl;
            break;
        case 13:
            if (loggedInUser->getRole() == "Manager") editUser(employeeDB);
            else cout << "Access Denied." << endl;
            break;
        case 14:
            if (loggedInUser->getRole() == "Manager") deleteUser(employeeDB);
            else cout << "Access Denied." << endl;
            break;
        default:
            cerr << "Unknown command." << endl;
            break;
        }
    }

    // Save users to file before exit
    employeeDB.saveUsersToFile("users.txt");

    return 0;
}

int displayMenu(const User& user)
{
    int selection;

    cout << endl;
    cout << "Employee Database" << endl;
    cout << "-----------------" << endl;
    if (user.getRole() == "Manager") {
        cout << "1) Hire a new employee" << endl;
        cout << "2) Fire an employee" << endl;
        cout << "3) Promote an employee" << endl;
    }
    cout << "4) List all employees" << endl;
    cout << "5) List all current employees" << endl;
    cout << "6) List all former employees" << endl;
    if (user.getRole() == "Manager") {
        cout << "7) Generate new database" << endl;
        cout << "8) Save database to file" << endl;
        cout << "9) Load database from file" << endl;
        cout << "10) Edit employee" << endl;
    }
    cout << "11) Search employee" << endl;
    if (user.getRole() == "Manager") {
        cout << "12) Create user" << endl;
        cout << "13) Edit user" << endl;
        cout << "14) Delete user" << endl;
    }
    cout << "0) Quit" << endl;
    cout << endl;
    cout << "---> ";
    
    cin >> selection;
    
    return selection;
}

void createUser(Database& db)
{
    string username, password, role;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    cout << "Enter role (Manager/Employee): ";
    cin >> role;

    db.createUser(username, password, role);
    cout << "User " << username << " created." << endl;
}

void editUser(Database& db)
{
    string username, newPassword, newRole;
    cout << "Enter username to edit: ";
    cin >> username;
    cout << "Enter new password: ";
    cin >> newPassword;
    cout << "Enter new role (Manager/Employee): ";
    cin >> newRole;

    try {
        db.editUser(username, newPassword, newRole);
        cout << "User " << username << " updated." << endl;
    } catch (const std::logic_error& exception) {
        cerr << "Unable to find user: " << exception.what() << endl;
    }
}

void deleteUser(Database& db)
{
    string username;
    cout << "Enter username to delete: ";
    cin >> username;

    try {
        db.deleteUser(username);
        cout << "User " << username << " deleted." << endl;
    } catch (const std::logic_error& exception) {
        cerr << "Unable to find user: " << exception.what() << endl;
    }
}

void searchEmployees(Database& db) // New function to search for employees
{
    string query;
    string field;

    cout << "Search by (first/middle/last/address): ";
    cin >> field;
    cout << "Enter search query: ";
    cin.ignore();
    getline(cin, query);

    vector<Employee> results = db.searchEmployees(query, field);

    if (results.empty()) {
        cout << "No employees found matching the query." << endl;
    } else {
        for (const auto& employee : results) {
            employee.display();
        }
    }
}

void editEmployee(Database& db)
{
    int employeeNumber;
    cout << "Enter the employee number to edit: ";
    cin >> employeeNumber;

    try {
        db.editEmployee(employeeNumber);
    } catch (const std::logic_error& exception) {
        cerr << "Unable to find employee: " << exception.what() << endl;
    }
}

void saveDatabaseToFile(const Database& db)
{
    string filename;
    cout << "Enter the filename to save the database: ";
    cin >> filename;

    ifstream inFile(filename);
    if (inFile) {
        char choice;
        cout << "File " << filename << " already exists. Overwrite? (y/n): ";
        cin >> choice;

        if (choice != 'y' && choice != 'Y') {
            cout << "Save operation cancelled." << endl;
            return;
        }
    }

    db.saveToFile(filename);
    cout << "Database saved to " << filename << endl;
}

void loadDatabaseFromFile(Database& db)
{
    string filename;
    cout << "Enter the filename to load the database: ";
    cin >> filename;

    db.loadFromFile(filename);
    cout << "Database loaded from " << filename << endl;
}

void doHire(Database& db)
{
    log("Start");

    string firstName;
    string middleName;
    string lastName;
    string address;

    cout << "First name? ";
    cin >> firstName;

    cout << "Middle name? ";
    cin >> middleName;

    cout << "Last name? ";
    cin >> lastName;

    cout << "Address? ";
    cin.ignore();
    getline(cin, address);

    db.addEmployee(firstName, middleName, lastName, address);

    log("End");
}

void doFire(Database& db)
{
    log("Start");
    int employeeNumber;

    cout << "Employee number? ";
    cin >> employeeNumber;

    try {
        Employee& emp = db.getEmployee(employeeNumber);
        emp.fire();
        cout << "Employee " << employeeNumber << " terminated." << endl;
    } catch (const std::logic_error& exception) {
        cerr << "Unable to terminate employee: " << exception.what() << endl;
    }
    log("End");
}

void doPromote(Database& db)
{
    log("Start");
    int employeeNumber;
    int raiseAmount;

    cout << "Employee number? ";
    cin >> employeeNumber;
    cout << "How much of a raise? ";
    cin >> raiseAmount;

    try {
        Employee& emp = db.getEmployee(employeeNumber);
        emp.promote(raiseAmount);
    } catch (const std::logic_error& exception) {
        cerr << "Unable to promote employee: " << exception.what() << endl;
    }
    log("End");
}

void generateDatabase(Database& db)
{
    log("Generating a new database with 8,000 employees.");
    db.generateNewDatabase();
    log("Database generation complete.");
}