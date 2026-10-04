#include "../public/PasswordManager.hpp"

displayStruct display;

PasswordManager::PasswordManager(const std::string& fname, const std::string& key, const IPasswordRetriever& retriever, IEncryptionMethod& encryptionmethod) : _key(key), _retriever(retriever), _fm(fname, encryptionmethod){
    if(!Security::comparePasswords(_fm.readFilePassword(), key)) throw "error";
    display.maxDigits = 0;
    display.maxUrl = 0;
    display.maxUsername = 0;

    _fm.readAccounts(_accounts, display);
}

bool PasswordManager::addAccount(bool autogen){
    std::string url, username, password;

    std::cout << "Url: ";
    std::cin >> url;
    std::cout << "\n";
    std::cout << "Username: ";
    std::cin >> username;
    std::cout << "\n";
    if(autogen){
        password = Security::generateStrongPassword();
    } else {
        std::cout << "Password: ";
        Security::hideKey(password);
    }

    Account a(url, username, password);
    _accounts.push_back(a);

    display.maxDigits = numDigits(_accounts.size()-1);
    display.maxUrl = max(display.maxUrl, url.size());
    display.maxUsername = max(display.maxUsername, username.size());

    return true;
}

bool PasswordManager::deleteAccount(const int index){
    auto _index = static_cast<std::vector<Account>::size_type>(index);
    if(index < 0 || _index > _accounts.size()-1 || _accounts.empty()) return false;
    _accounts.erase(_accounts.begin()+_index);

    display.maxDigits = numDigits(_accounts.size()-1);
    display.maxUrl = 0;
    display.maxUsername = 0;

    for(auto a : _accounts){
        display.maxUrl = max(display.maxUrl, a.getUrl().size());
        display.maxUsername = max(display.maxUsername, a.getUsername().size());
    }

    return true;
}

inline void divider(){
    std::cout << "+";
    for(int i=0; i<(display.maxDigits+display.maxUrl+display.maxUsername+8);++i) std::cout << "-";
    std::cout << "+\n";
}

inline void nSpaces(int n){
    while(n>0){
        std::cout << " ";
        --n;
    }
}

bool PasswordManager::displayAccounts(const std::string& filter) const{
    if(_accounts.empty()){
        std::cout << "Currently no accounts safed." << std::endl;
        return false;
    }
    
    for(size_t index=0; index<_accounts.size(); ++index){
        if(_accounts[index].getUrl().find(filter) != std::string::npos || _accounts[index].getUsername().find(filter) != std::string::npos){
            divider();
            //std::cout << "| " << index << " | " << _accounts[index].getUrl() << " | " << _accounts[index].getUsername() << " |\n";
            std::cout << "| " << index;
            nSpaces(display.maxDigits-numDigits(index));
            std::cout << " | " << _accounts[index].getUrl();
            nSpaces(display.maxUrl-_accounts[index].getUrl().size());
            std::cout << " | " << _accounts[index].getUsername();
            nSpaces(display.maxUsername-_accounts[index].getUsername().size());
            std::cout << " |\n";
        }
    }
    divider();

    return true;
}

bool PasswordManager::selectAccount(const int index) const{
    auto _index = static_cast<std::vector<Account>::size_type>(index);
    if(index < 0 || _index > _accounts.size()-1 || _accounts.empty()) return false;
    _retriever.retrievePassword(_accounts[_index].getPassword());
    std::cout << "Password retrieved for " << _accounts[_index].getUrl() << " and " << _accounts[_index].getUsername() << std::endl;
    return true;
}

bool PasswordManager::changeFilePassword(){
    std::string newKey;
    Security::hideKey(newKey);
    _key = newKey;
    return _fm.changeFilePassword(newKey);
}

bool PasswordManager::exit() const{
    return _fm.writePassAndAccounts(_accounts, Security::sha256(_key));
}