#include "IEncryptionMethod.hpp"

class NoEncryptionMethod final : public IEncryptionMethod {
public:
    explicit NoEncryptionMethod(const std::string& key) : IEncryptionMethod(key) {}

    std::string encrypt(const std::string& input) const override{
        return input;
    }
    std::string decrypt(const std::string& input) const override{
        return input;
    }
};
