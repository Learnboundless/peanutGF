#pragma once

#include <queue>
#include "redObj.h"

class renderQue
{
public:
	~renderQue() { instance = nullptr; }

	static renderQue* Get() 
	{
		if (instance == nullptr)
			instance = new renderQue;
		return instance;
	}
private:
	static renderQue* instance;

private:
	//‰÷»æ∂”¡–

};

static renderQue* redQue = renderQue::Get();