#include "../public/Account.hpp"


std::string Account::getUrl() const{
    return this->_url;
}
std::string Account::getUsername() const{
    return this->_username;
}
std::string Account::getPassword() const{
    return this->_password;
}
