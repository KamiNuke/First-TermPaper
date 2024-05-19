#include "overloadFunctions.h"

std::ostream& operator<<(std::ostream& out, const EngineType type)
{
    switch (type)
    {
    case EngineType::Engine:
        out << "Engine";
        break;
    case EngineType::ICEngine:
        out << "ICEngine";
        break;
    case EngineType::JetEngine:
        out << "JetEngine";
        break;
    default:
        out << "Error";
        break;
    }

    return out;
}
