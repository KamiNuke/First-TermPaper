#pragma once
#include "Engine.h"

class ICEngine : public Engine
{
public:
	ICEngine(const std::string name, unsigned int enginePower)
		: Engine{ name, enginePower } {}
	const char* getClassName() const;
};

