#pragma once

#include<queue> 
#include<vector> 
#include <d3d9.h>

class redObj;

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
	std::priority_queue<redObj*> m_redQue;
	std::vector<redObj*> m_backVector;
public:
	bool Push(redObj* obj);
	redObj* Top();
	void Pop();
	void ParseRes(LPDIRECT3DDEVICE9 dev);
	void Render();
};

static renderQue* redQue = renderQue::Get();