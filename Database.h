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
                              const std::string& address); // Updated method signature

        Employee& getEmployee(int employeeNumber);
        Employee& getEmployee(const std::string& firstName,
                              const std::string& lastName);

        void displayAll() const;
        void displayCurrent() const;
        void displayFormer() const;

        void generateNewDatabase(); // New method to generate 8,000 employees

    private:
        std::vector<Employee> mEmployees;
        int mNextEmployeeNumber = kFirstEmployeeNumber;
    };
}

