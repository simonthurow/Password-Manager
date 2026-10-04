#include "IEncryptionMethod.hpp"

class VigenereMethod final : public IEncryptionMethod{
public:
    explicit VigenereMethod(const std::string& key) : IEncryptionMethod(key){}

    std::string encrypt(const std::string& input) const override{
        const size_t len = _key.size();
        const size_t alphaLen = _alphabet.size();
        std::string output;
        output.reserve(input.size());
    
        for(size_t i=0; i<input.size(); ++i){
            uint8_t p = _alphabet.find(input[i]);
            uint8_t k = _alphabet.find(_key[i%len]);
            if(k==std::string::npos || p ==std::string::npos) {
                output.push_back(input[i]);
                continue;
            }
            output.push_back(_alphabet[(p+k)%alphaLen]);
        }
        return output;
    }

    std::string decrypt(const std::string& input) const override{
        const size_t len = _key.size();
        const size_t alphaLen = _alphabet.size();
        std::string output;
        output.reserve(input.size());
    
        for(size_t i=0; i<input.size(); ++i){
            uint8_t p = _alphabet.find(input[i]);
            uint8_t k = _alphabet.find(_key[i%len]);
            if(k==std::string::npos || p ==std::string::npos) {
                output.push_back(input[i]);
                continue;
            }
            output.push_back(_alphabet[(p+alphaLen-k)%alphaLen]);
        }
        return output;
    }

};
