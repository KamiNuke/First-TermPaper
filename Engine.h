#pragma once
#include "IEngine.h"

class Engine : public IEngine
{
public:
	Engine(const std::string name, unsigned int enginePower)
		: IEngine{ name, enginePower } {}
	const char* getClassName() const;
};
