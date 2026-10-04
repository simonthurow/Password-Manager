#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <string>

class Account{
public:
    Account(const std::string& url, const std::string& username, const std::string& password) : _url(url), _username(username), _password(password){}

    std::string getUrl() const;
    std::string getUsername() const;
    std::string getPassword() const;
private:
    std::string _url;
    std::string _username;
    std::string _password;
};

#endif