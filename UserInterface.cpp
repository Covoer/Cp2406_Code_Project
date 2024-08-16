#include <iostream>
#include <fstream>
#include <stdexcept>
#include "my_debugger.h"
#include "Database.h"

using namespace std;
using namespace Records;

int displayMenu();
void doHire(Database& db);
void doFire(Database& db);
void doPromote(Database& db);
void generateDatabase(Database& db);
void saveDatabaseToFile(const Database& db);
void loadDatabaseFromFile(Database& db);
void editEmployee(Database& db); // New function declaration

int main()
{
    log("started");
    Database employeeDB;

    bool done = false;
    while (!done) {
        int selection = displayMenu();
        switch (selection) {
        case 0:
            log("case 0");
            done = true;
            break;
        case 1:
            doHire(employeeDB);
            break;
        case 2:
            doFire(employeeDB);
            break;
        case 3:
            doPromote(employeeDB);
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
            generateDatabase(employeeDB);
            break;
        case 8:
            saveDatabaseToFile(employeeDB);
            break;
        case 9:
            loadDatabaseFromFile(employeeDB);
            break;
        case 10:
            editEmployee(employeeDB); // Edit employee details
            break;
        default:
            cerr << "Unknown command." << endl;
            break;
        }
    }

    return 0;
}

int displayMenu()
{
    int selection;

    cout << endl;
    cout << "Employee Database" << endl;
    cout << "-----------------" << endl;
    cout << "1) Hire a new employee" << endl;
    cout << "2) Fire an employee" << endl;
    cout << "3) Promote an employee" << endl;
    cout << "4) List all employees" << endl;
    cout << "5) List all current employees" << endl;
    cout << "6) List all former employees" << endl;
    cout << "7) Generate new database" << endl;
    cout << "8) Save database to file" << endl;
    cout << "9) Load database from file" << endl;
    cout << "10) Edit employee" << endl; // New menu option
    cout << "0) Quit" << endl;
    cout << endl;
    cout << "---> ";
    
    cin >> selection;
    
    return selection;
}

void editEmployee(Database& db) // New function to edit employee details
{
    int employeeNumber;
    cout << "Enter the employee number to edit: ";
    cin >> employeeNumber;

    try {
        db.editEmployee(employeeNumber); // Call the edit function in the Database class
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