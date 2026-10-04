#include "IEncryptionMethod.hpp"

class AESMethod final : public IEncryptionMethod{
public:
    explicit AESMethod(const std::string& key) : IEncryptionMethod(key){}

    std::string encrypt(const std::string& input) const override{
       //use AES algorithm library to encrypt input data 
    }

    std::string decrypt(const std::string& input) const override{
       //use AES algorithm library to decrypt input data
    }

};

