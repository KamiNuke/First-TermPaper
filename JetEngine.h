#pragma once
#include "ICEngine.h"

class JetEngine : public ICEngine
{
public:
	JetEngine(const std::string name, unsigned int enginePower)
		: ICEngine{ name, enginePower } {}
	const char* getClassName() const;
};

