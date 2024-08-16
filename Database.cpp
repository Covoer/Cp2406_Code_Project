#include <iostream>
#include <fstream>
#include <stdexcept>
#include "Database.h"

using namespace std;

namespace Records {

    Employee& Database::addEmployee(const string& firstName,
                                    const string& middleName,
                                    const string& lastName,
                                    const string& address)
    {
        Employee theEmployee(firstName, lastName);
        theEmployee.setMiddleName(middleName);
        theEmployee.setAddress(address);
        theEmployee.setEmployeeNumber(mNextEmployeeNumber++);
        theEmployee.hire();
        mEmployees.push_back(theEmployee);

        return mEmployees[mEmployees.size() - 1];
    }

    std::vector<Employee> Database::searchEmployees(const std::string& query, const std::string& field) const {
        std::vector<Employee> results;

        for (const auto& employee : mEmployees) {
            if (field == "first") {
                if (employee.getFirstName().find(query) != std::string::npos) {
                    results.push_back(employee);
                }
            } else if (field == "middle") {
                if (employee.getMiddleName().find(query) != std::string::npos) {
                    results.push_back(employee);
                }
            } else if (field == "last") {
                if (employee.getLastName().find(query) != std::string::npos) {
                    results.push_back(employee);
                }
            } else if (field == "address") {
                if (employee.getAddress().find(query) != std::string::npos) {
                    results.push_back(employee);
                }
            }
        }

        return results;
    }

    void Database::editEmployee(int employeeNumber) {
        Employee& emp = getEmployee(employeeNumber);

        string newAddress;
        cout << "Enter new address (leave empty to keep current): ";
        cin.ignore();
        getline(cin, newAddress);
        if (!newAddress.empty()) {
            emp.setAddress(newAddress);
        }

        int newSalary;
        cout << "Enter new salary (enter 0 to keep current): ";
        cin >> newSalary;
        if (newSalary > 0) {
            emp.setSalary(newSalary);
        }

        char changeStatus;
        cout << "Change hire status? (y/n): ";
        cin >> changeStatus;
        if (changeStatus == 'y' || changeStatus == 'Y') {
            char hireStatus;
            cout << "Is the employee hired? (y/n): ";
            cin >> hireStatus;
            if (hireStatus == 'y' || hireStatus == 'Y') {
                emp.hire();
            } else {
                emp.fire();
            }
        }

        cout << "Employee " << employeeNumber << " updated." << endl;
    }

    void Database::saveToFile(const std::string& filename) const {
        ofstream outFile(filename);

        if (!outFile) {
            cerr << "Error: Could not open file " << filename << " for writing." << endl;
            return;
        }

        for (const auto& employee : mEmployees) {
            outFile << employee.getFirstName() << " "
                    << employee.getMiddleName() << " "
                    << employee.getLastName() << " "
                    << employee.getAddress() << " "
                    << employee.getEmployeeNumber() << " "
                    << employee.getSalary() << " "
                    << (employee.isHired() ? "Hired" : "Fired") << endl;
        }

        outFile.close();
    }

    void Database::loadFromFile(const std::string& filename) {
        ifstream inFile(filename);

        if (!inFile) {
            cerr << "Error: Could not open file " << filename << " for reading." << endl;
            return;
        }

        mEmployees.clear(); // Clear the current database before loading new data

        string firstName, middleName, lastName, address, status;
        int employeeNumber, salary;

        while (inFile >> firstName >> middleName >> lastName >> address >> employeeNumber >> salary >> status) {
            Employee theEmployee(firstName, lastName);
            theEmployee.setMiddleName(middleName);
            theEmployee.setAddress(address);
            theEmployee.setEmployeeNumber(employeeNumber);
            theEmployee.setSalary(salary);
            if (status == "Hired") {
                theEmployee.hire();
            } else {
                theEmployee.fire();
            }
            mEmployees.push_back(theEmployee);
            mNextEmployeeNumber = employeeNumber + 1;
        }

        inFile.close();
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





