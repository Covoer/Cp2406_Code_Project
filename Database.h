#pragma once

#include <iostream>
#include <vector>
#include "Employee.h"
#include "User.h"

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

        void editEmployee(int employeeNumber);
        std::vector<Employee> searchEmployees(const std::string& query, const std::string& field) const;

        // User management functions
        void createUser(const std::string& username, const std::string& password, const std::string& role);
        void editUser(const std::string& username, const std::string& newPassword, const std::string& newRole);
        void deleteUser(const std::string& username);
        void saveUsersToFile(const std::string& filename) const;
        void loadUsersFromFile(const std::string& filename);
        User* authenticateUser(const std::string& username, const std::string& password);

    private:
        std::vector<Employee> mEmployees;
        std::vector<User> mUsers; // List of users
        int mNextEmployeeNumber = kFirstEmployeeNumber;
    };
}

