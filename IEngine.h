#pragma once
#include <string>


class IEngine
{
public:
    IEngine(const std::string name, unsigned int enginePower)
        : m_engineName{ name }, m_enginePower{ enginePower } {}

    const int getPower() const;
    const std::string getName() const;

    virtual const char* getClassName() const = 0;
protected:
    unsigned int m_enginePower;
    const std::string m_engineName;
};