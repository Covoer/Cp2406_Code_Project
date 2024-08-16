#include "User.h"

User::User(const std::string& username, const std::string& password, const std::string& role)
    : mUsername(username), mPassword(password), mRole(role) {}

void User::setUsername(const std::string& username) {
    mUsername = username;
}

const std::string& User::getUsername() const {
    return mUsername;
}

void User::setPassword(const std::string& password) {
    mPassword = password;
}

const std::string& User::getPassword() const {
    return mPassword;
}

void User::setRole(const std::string& role) {
    mRole = role;
}

const std::string& User::getRole() const {
    return mRole;
}
