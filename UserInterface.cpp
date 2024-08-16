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
void saveDatabaseToFile(const Database& db); // New function declaration

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
            saveDatabaseToFile(employeeDB); // Save database to a file
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
    cout << "8) Save database to file" << endl; // New menu option
    cout << "0) Quit" << endl;
    cout << endl;
    cout << "---> ";
    
    cin >> selection;
    
    return selection;
}

void saveDatabaseToFile(const Database& db) // New function to save database to a file
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

void doHire(Database& db)
{
    log("Start");

    string firstName;
    string middleName;  // New variable
    string lastName;
    string address;     // New variable

    cout << "First name? ";
    cin >> firstName;

    cout << "Middle name? ";  // Prompt for middle name
    cin >> middleName;

    cout << "Last name? ";
    cin >> lastName;

    cout << "Address? ";  // Prompt for address
    cin.ignore();  // To clear any newline character left in the input buffer
    getline(cin, address);  // Use getline to allow spaces in the address

    db.addEmployee(firstName, middleName, lastName, address);  // Pass all arguments

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

void generateDatabase(Database& db) // New function to generate the database
{
    log("Generating a new database with 8,000 employees.");
    db.generateNewDatabase();
    log("Database generation complete.");
}



