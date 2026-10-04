#ifndef IPASSWORDRETRIEVER_H
#define IPASSWORDRETRIEVER_H

#include <iostream>

class IPasswordRetriever{
public:
    virtual ~IPasswordRetriever() = default;
    virtual void retrievePassword(const std::string& password) const = 0;
};

#endif

