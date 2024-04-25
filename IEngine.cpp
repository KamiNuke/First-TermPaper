#include "IEngine.h"

const int IEngine::getPower() const
{
    return m_enginePower;
}

const std::string IEngine::getName() const
{
    return m_engineName;
}