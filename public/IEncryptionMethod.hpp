#ifndef IENCRYPTIONMETHOD_H
#define IENCRYPTIONMETHOD_H

#include <iostream>
#include <string>

class IEncryptionMethod{
public:
    explicit IEncryptionMethod(const std::string& key) : _key(key){}
    virtual ~IEncryptionMethod() = default;

    void changeKey(const std::string& newKey) {_key = newKey;}
    virtual std::string encrypt(const std::string& input) const = 0;
    virtual std::string decrypt(const std::string& input) const = 0;
protected:
    std::string _key;
    std::string _alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789~!@#$^&*()-_+={}[]|;:',./";
};

#endif
