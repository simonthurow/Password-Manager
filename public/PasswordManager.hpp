#include "Account.hpp"
#include "IPasswordRetriever.hpp"
#include "IEncryptionMethod.hpp"
#include "FileManager.hpp"
#include "../private/Security.cpp"

#include <vector>

class PasswordManager{
public:
    PasswordManager(const std::string& fname, const std::string& key, const IPasswordRetriever& retriever, IEncryptionMethod& encryptionmethod); 

    bool addAccount(const bool autogen);
    bool deleteAccount(const int index);
    bool displayAccounts(const std::string& filter="") const;
    bool selectAccount(const int index) const;
    bool changeFilePassword();
    bool exit() const;
private:
    std::vector<Account> _accounts;
    std::string _key;
    const IPasswordRetriever& _retriever;
    FileManager _fm;
};