#include "renderQueue.h"
#include "redObj.h"



renderQue* renderQue::instance = nullptr;

bool renderQue::Push(redObj* obj) {
	if (obj != nullptr)
	{
		m_redQue.push(obj);
		m_backVector.push_back(obj);
		return true;
	}
	else return false;
}
redObj* renderQue::Top() {
	if (!m_redQue.empty())
	{
		return m_redQue.top();
	}
	else
		return nullptr;
}

void renderQue::Pop() {
	m_redQue.pop();
}

void renderQue::ParseRes(LPDIRECT3DDEVICE9 dev) {
	for (std::vector<redObj*>::const_iterator iter =instance->m_backVector.begin(); iter != instance->m_backVector.end(); iter++)
	{
		(*iter)->initRes(dev);
	}
}

void renderQue::Render() {
	std::priority_queue<redObj*> tempRenderList = m_redQue;
	while (!tempRenderList.empty())
	{
		tempRenderList.top()->renderSel();
		tempRenderList.pop();
	}
}


