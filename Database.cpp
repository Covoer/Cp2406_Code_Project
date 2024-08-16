#include <iostream>
#include <stdexcept>
#include "Database.h"

using namespace std;

namespace Records {

    Employee& Database::addEmployee(const string& firstName,
                                    const string& middleName, // Added middle name
                                    const string& lastName,
                                    const string& address) // Added address
    {
        Employee theEmployee(firstName, lastName);
        theEmployee.setMiddleName(middleName); // Set middle name
        theEmployee.setAddress(address);       // Set address
        theEmployee.setEmployeeNumber(mNextEmployeeNumber++);
        theEmployee.hire();
        mEmployees.push_back(theEmployee);

        return mEmployees[mEmployees.size() - 1];
    }

    Employee& Database::getEmployee(int employeeNumber)
    {
        for (auto& employee : mEmployees) {
            if (employee.getEmployeeNumber() == employeeNumber) {
                return employee;
            }
        }
        throw logic_error("No employee found.");
    }

    Employee& Database::getEmployee(const string& firstName, const string& lastName)
    {
        for (auto& employee : mEmployees) {
            if (employee.getFirstName() == firstName &&
                employee.getLastName() == lastName) {
                    return employee;
            }
        }
        throw logic_error("No employee found.");
    }

    void Database::displayAll() const
    {
        for (const auto& employee : mEmployees) {
            employee.display();
        }
    }

    void Database::displayCurrent() const
    {
        for (const auto& employee : mEmployees) {
            if (employee.isHired())
                employee.display();
        }
    }

    void Database::displayFormer() const
    {
        for (const auto& employee : mEmployees) {
            if (!employee.isHired())
                employee.display();
        }
    }

    void Database::generateNewDatabase() {
        vector<string> firstNames = {"John", "Jane", "Alex", "Emily", "Chris", "Pat", "Sam", "Jordan", "Taylor", "Morgan", 
                                     "Cameron", "Casey", "Drew", "Hunter", "Riley", "Quinn", "Shawn", "Blake", "Jesse", "Dana"};
        vector<string> middleNames = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T"};
        vector<string> lastNames = {"Smith", "Johnson", "Williams", "Jones", "Brown", "Davis", "Miller", "Wilson", "Moore", "Taylor", 
                                    "Anderson", "Thomas", "Jackson", "White", "Harris", "Martin", "Thompson", "Garcia", "Martinez", "Robinson"};
        
        int id = 1;
        for (const auto& firstName : firstNames) {
            for (const auto& middleName : middleNames) {
                for (const auto& lastName : lastNames) {
                    string address = "123" + to_string(id) + " Main St, City, ST, 12345";
                    addEmployee(firstName, middleName, lastName, address);
                    id++;
                }
            }
        }
    }

}

