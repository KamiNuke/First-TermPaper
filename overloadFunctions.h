#pragma once
#include <iostream>

enum class EngineType
{
    Engine,
    ICEngine,
    JetEngine,

    MAX_ENGINE
};

std::ostream& operator<<(std::ostream& out, const EngineType type);