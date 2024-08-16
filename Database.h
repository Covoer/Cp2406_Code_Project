#pragma once

#include <iostream>
#include <vector>
#include "Employee.h"

namespace Records {
    const int kFirstEmployeeNumber = 1000;

    class Database
    {
    public:
        Employee& addEmployee(const std::string& firstName,
                              const std::string& middleName,
                              const std::string& lastName,
                              const std::string& address);

        Employee& getEmployee(int employeeNumber);
        Employee& getEmployee(const std::string& firstName,
                              const std::string& lastName);

        void displayAll() const;
        void displayCurrent() const;
        void displayFormer() const;

        void generateNewDatabase();
        void saveToFile(const std::string& filename) const;
        void loadFromFile(const std::string& filename);

        void editEmployee(int employeeNumber); // Edit employee details
        std::vector<Employee> searchEmployees(const std::string& query, const std::string& field) const; // New method to search employees

    private:
        std::vector<Employee> mEmployees;
        int mNextEmployeeNumber = kFirstEmployeeNumber;
    };
}
