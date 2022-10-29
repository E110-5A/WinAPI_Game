#include "jsScene.h"
#include "jsGameObject.h"
namespace js
{

	Scene::Scene()
	{
		mObjects.resize(_COLLIDER_LAYER);
	}

	Scene::~Scene()
	{
		for (size_t y = 0; y < _COLLIDER_LAYER; ++y)
		{
			for (size_t x = 0; x < mObjects[y].size(); ++x)
			{
				delete mObjects[y][x];
				mObjects[y][x] = nullptr;
			}
		}
		
	}

	void Scene::Initialize()
	{
		for (size_t y = 0; y < _COLLIDER_LAYER; ++y)
		{
			for (size_t x = 0; x < mObjects[y].size(); ++x)
			{
				if (mObjects[y][x] != nullptr)
					mObjects[y][x]->Initialize();
			}
		}
	}

	void Scene::Tick()
	{
		for (size_t y = 0; y < _COLLIDER_LAYER; ++y)
		{
			for (size_t x = 0; x < mObjects[y].size(); ++x)
			{
				if (mObjects[y][x] != nullptr)
					mObjects[y][x]->Tick();
			}
		}
	}

	void Scene::Render(HDC hdc)
	{
		for (size_t y = 0; y < _COLLIDER_LAYER; ++y)
		{
			for (size_t x = 0; x < mObjects[y].size(); ++x)
			{
				if (mObjects[y][x] != nullptr)
					mObjects[y][x]->Render(hdc);
			}
		}
	}

	void Scene::AddGameObject(GameObject* obj, eColliderLayer type)
	{
		if (nullptr != obj)
			mObjects[(UINT)type].push_back(obj);
	}

}