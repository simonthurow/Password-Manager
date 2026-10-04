#include "IEncryptionMethod.hpp"
#include "Account.hpp"
#include "DisplayStruct.hpp"
#include "Math.hpp"
#include <vector>
#include <fstream>
#include <sstream>
#include <math.h>

class FileManager{
public:
    FileManager(const std::string& fname, IEncryptionMethod& encryptionmethod) : _fname(fname), _encryptionmethod(encryptionmethod){}

    std::string readFilePassword() const;
    bool changeFilePassword(const std::string& newPassword);
    bool readAccounts(std::vector<Account>& accounts, displayStruct& display) const;
    bool writePassAndAccounts(const std::vector<Account>& accounts, const std::string& filePassword) const;
private:
    const std::string _fname;
    IEncryptionMethod& _encryptionmethod;
};

