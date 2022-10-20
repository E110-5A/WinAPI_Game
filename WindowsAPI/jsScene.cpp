#include "jsScene.h"
#include "jsGameObject.h"
namespace js
{

	jsScene::jsScene()
	{
	}

	jsScene::~jsScene()
	{
		for (size_t obj = 0; obj < m_GameObj.size(); ++obj)
		{
			delete m_GameObj[obj];
			m_GameObj[obj] = nullptr;
		}
	}

	void jsScene::Initialize()
	{
		for (size_t obj = 0; obj < m_GameObj.size(); ++obj)
		{
			m_GameObj[obj]->Initialize();
		}
	}

	void jsScene::Tick()
	{
		for (size_t obj = 0; obj < m_GameObj.size(); ++obj)
		{
			m_GameObj[obj]->Tick();
		}
	}

	void jsScene::Render(HDC _dc)
	{
		for (size_t obj = 0; obj < m_GameObj.size(); ++obj)
		{
			m_GameObj[obj]->Render(_dc);
		}
	}

	void jsScene::AddGameObject(jsGameObject* _obj)
	{
		if (nullptr != _obj)
			m_GameObj.push_back(_obj);
	}

}