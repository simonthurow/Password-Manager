#include "../public/FileManager.hpp"

std::string FileManager::readFilePassword() const{
    std::ifstream infile(_fname);
    std::string password;

    if(infile.is_open()){
        std::getline(infile, password);
    }

    return password;
}

bool FileManager::changeFilePassword(const std::string& newPassword){
    _encryptionmethod.changeKey(newPassword);
    return true;
}

bool FileManager::readAccounts(std::vector<Account>& accounts, displayStruct& display) const{
    std::ifstream infile(_fname);
    std::string line;

    if(infile.is_open()){
        std::getline(infile, line);
        while(std::getline(infile, line)){
            std::istringstream iss(line);
            std::string url, username, password;
            if(iss >> url >> username >> password){
                url      = _encryptionmethod.decrypt(url);
                username = _encryptionmethod.decrypt(username);
                password = _encryptionmethod.decrypt(password);

                Account a(url, username, password);
                accounts.push_back(a);

                display.maxUrl = max(display.maxUrl, url.size());
                display.maxUsername = max(display.maxUsername, username.size());
            }
        }
        display.maxDigits = numDigits(accounts.size()-1);
        return true;
    }
    return false;
}

bool FileManager::writePassAndAccounts(const std::vector<Account>& accounts, const std::string& filePassword) const{
    std::ofstream file;
    file.open(_fname); 
    file << filePassword << "\n";
    for(auto account : accounts){
        file << _encryptionmethod.encrypt(account.getUrl()) << " " << _encryptionmethod.encrypt(account.getUsername()) << " " << _encryptionmethod.encrypt(account.getPassword()) << "\n";
    }
    file.close();
    return true;
}