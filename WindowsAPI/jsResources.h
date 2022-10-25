#pragma once
#include "Common.h"
#include "jsResource.h"

namespace js
{

	template<typename T>
	class jsResources
	{
	public:
		typedef std::map<std::wstring, jsResource*>::iterator ResourceIter;

		static T* Find(const std::wstring& key)
		{
			// 리소스 중복체크
			ResourceIter iter = mResources.find(key);
			if (iter != mResources.end())
			{
				return dynamic_cast<T*>(iter->second);
			}
			return nullptr;
		}
		static T* Load(const std::wstring& key, const std::wstring& path)
		{
			T* resource = Find(key);
			if (nullptr != resource)
				return resource;

			resource = new T;
			if (FAILED(resource->Load(path)))
			{
				MessageBox(nullptr, L"Image Load Failed!!", L"Error", MB_OK);
				return nullptr;
			}

			resource->SetKey(key);
			resource->SetPath(path);

			mResources.insert(std::make_pair(key, resource));
			return dynamic_cast<T*>(resource);
		}

	private:
		static std::map<std::wstring, jsResource*> mResources;
	};

	

	template <typename T>
	std::map<std::wstring, jsResource*> jsResources<T>::mResources;
}