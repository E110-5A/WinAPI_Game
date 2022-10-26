#include "jsScene.h"
#include "jsGameObject.h"
namespace js
{

	Scene::Scene()
	{
	}

	Scene::~Scene()
	{
		for (size_t obj = 0; obj < m_GameObj.size(); ++obj)
		{
			delete m_GameObj[obj];
			m_GameObj[obj] = nullptr;
		}
	}

	void Scene::Initialize()
	{
		for (size_t obj = 0; obj < m_GameObj.size(); ++obj)
		{
			m_GameObj[obj]->Initialize();
		}
	}

	void Scene::Tick()
	{
		for (size_t obj = 0; obj < m_GameObj.size(); ++obj)
		{
			m_GameObj[obj]->Tick();
		}
	}

	void Scene::Render(HDC _dc)
	{
		for (size_t obj = 0; obj < m_GameObj.size(); ++obj)
		{
			m_GameObj[obj]->Render(_dc);
		}
	}

	void Scene::AddGameObject(GameObject* _obj)
	{
		if (nullptr != _obj)
			m_GameObj.push_back(_obj);
	}

}