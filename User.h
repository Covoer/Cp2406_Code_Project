#pragma once

#include <string>

class User {
public:
    User() = default;
    User(const std::string& username, const std::string& password, const std::string& role);

    void setUsername(const std::string& username);
    const std::string& getUsername() const;

    void setPassword(const std::string& password);
    const std::string& getPassword() const;

    void setRole(const std::string& role);
    const std::string& getRole() const;

private:
    std::string mUsername;
    std::string mPassword;
    std::string mRole; // "Manager" or "Employee"
};
