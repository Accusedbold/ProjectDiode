/******************************************************************/
/*!
	All content (C) John Salguero, all rights reserved.
	Reproduction or disclosure of this file or its contents without the
	prior written consent of John Salguero is prohibited.

	\file    ResourceManager.cpp
	\author  John Salguero
	\date    June 25, 2023
	\brief
		This cpp file defines the Resource Manager member functions, 
		which Manages the different resources loaded in the game
*/
/********************************************************************/
#include "stdafx.h"
#include "ResourceLoader.h"   // ResourceLoader
#include "ResourceManager.h"  // ResourceManager
#include "Model.h"						// Model

ResourceManager* ResourceManager::m_Instance = nullptr;

/******************************************************************************/
/*!
					GetInstance

\author   John Salguero

\brief    Returns an instance of the singleton ResourceManager

\return   ResourceManager*
					Instance of the resource manager
*/
/******************************************************************************/
ResourceManager* ResourceManager::GetInstance()
{
	if (!m_Instance)
		m_Instance = new ResourceManager();
	return m_Instance;
}

/******************************************************************************/
/*!
					GetResource

\author   John Salguero

\brief    Given a type and Index of a Resource, returns a pointer to said
					Resource. If the resource does not exist, crash.

\param    type
					The Resource type to get

\param    index
					The Resource Index to get

\return   std::weak_ptr<Resource>
					pointer to the Resource
*/
/******************************************************************************/
std::weak_ptr<Resource> ResourceManager::GetResource(ResourceType type, ResourceID index) const
{
	auto mapIt = m_ResourceMap.find(type);
	if (mapIt != m_ResourceMap.end())
	{
		auto ResourceIt = mapIt->second.find(index);
		if (ResourceIt != mapIt->second.end())
			return ResourceIt->second;
		FATAL_ERROR(
			"Resource not found with type: " + std::to_string(static_cast<int>(type)) + 
			" and ID: " + std::to_string(index));
	}

	FATAL_ERROR(
		"Resource map not found with type: " + std::to_string(static_cast<int>(type)));

	return std::weak_ptr<Resource>();
}

/******************************************************************************/
/*!
					GetResource

\author   John Salguero

\brief    Given the type and name, retrieves the pointer to the resource. If the
					Resource has not already been loaded in, load said resource.

\param    type
					The Type of the resource to get

\param		name
					The name of the resource to get

\return   std::weak_ptr<Resource>
					Pointer of the resource
*/
/******************************************************************************/
std::weak_ptr<Resource> ResourceManager::GetResource(ResourceType type, std::wstring const& name)
{
	// lock during reads and writes
	m_Mutex.lock();
	// get an iterator to the resource map
	auto mapIt = m_ResourceMap.find(type);
	// if we don't have a map for the resource type create the related maps
	if (mapIt == m_ResourceMap.end())
	{
		CreateResourceMap(type);
		// unlock after writing and before loading
		m_Mutex.unlock();
		// Load in the Resource and return the resource
		ResourceID id = LoadResource(type, name);
		auto resourceIt = m_ResourceMap.find(type)->second.find(id);
		if (resourceIt != m_ResourceMap.find(type)->second.end())
			return resourceIt->second;
		else
			return std::weak_ptr<Resource>();
	}
	/// We have a have a map for the resource already
	// get an iterator to the map of IDs
	auto const& IDMap = m_ResourceIDMap.find(type)->second;
	auto IDIt = IDMap.find(name);
	// If we do not have an ID already, resource needs to be loaded
	if (IDIt == IDMap.end()) 
	{
		// unlock after writing and before loading
		m_Mutex.unlock();
		// Load in the Resource and return the resource
		ResourceID id = LoadResource(type, name);
		auto resourceIt = m_ResourceMap.find(type)->second.find(id);
		if (resourceIt != m_ResourceMap.find(type)->second.end())
			return resourceIt->second;
		else
			return std::weak_ptr<Resource>();
	}
	// We Do have ID already, just return the resource
	m_Mutex.unlock();
	return m_ResourceMap[type][IDIt->second];
}

/******************************************************************************/
/*!
					LoadResource

\author   John Salguero

\brief    Given a type, and its name - loads in the resource.

\param    type
					The type of the resource to load

\param    name
					The name of the resource to load

\return   ResourceID
					The resultant ID given to the resource
*/
/******************************************************************************/
ResourceID ResourceManager::LoadResource(ResourceType type, std::wstring const& name)
{
	m_Mutex.lock();
	// get an iterator to the resource map
	auto mapIt = m_ResourceMap.find(type);

	// The Resource map does not exist, make it
	if (mapIt == m_ResourceMap.end()) {
		CreateResourceMap(type);
		mapIt = m_ResourceMap.find(type);
	}
	// Get an iterator to the map of IDs
	auto IDIt = m_ResourceIDMap[type].find(name);
	// if the ID exists alread, we already loaded it in
	if (IDIt != m_ResourceIDMap[type].end()) {
		m_Mutex.unlock();
		return IDIt->second;
	}
	// get a new id
	ResourceID id = GetNewID(type);

	std::shared_ptr<Resource> loadedResource = (*ResourceLoader::GetInstance())(type, name, id);
	if(loadedResource)
		InsertNewResource(type, name, id, loadedResource);

	m_Mutex.unlock();
	return id;
}

/******************************************************************************/
/*!
					LoadResource

\author   John Salguero

\brief    Loads the resource given a type, name, and hint. Will attempt
					to give the resource the hint as an ID, but will default to
					regulat ID generation if the ID is taken.

\param    type
					The type of Resource to load

\param    name
					The name of the resource to load

\param    hint
					The preferred ID to give the resource

\return   ResourceID
					The resultant ID given to the resource
*/
/******************************************************************************/
ResourceID ResourceManager::LoadResource(ResourceType type, std::wstring const& name, ResourceID hint)
{
	m_Mutex.lock();
	auto IDIt = m_IDs.find(type);
	// if the maps don't exist - make them
	if (IDIt == m_IDs.end())
		CreateResourceMap(type);
	auto nameMap = m_ResourceNameMap.find(type)->second;
	auto nameIt = nameMap.find(hint);
	// if the id is already in use, just load it in regularly
	if (nameIt != nameMap.end())
	{
		m_Mutex.unlock();
		return LoadResource(type, name);
	}
	 // We can use the hint, load in the prospective Resource depending on type
	std::shared_ptr<Resource> loadedResource = (*ResourceLoader::GetInstance())(type, name, hint);
	if(loadedResource)
		InsertNewResource(type, name, hint, loadedResource);

	m_Mutex.unlock();
	return hint;
}

/******************************************************************************/
/*!
					GetNewID

\author   John Salguero

\brief    Given a type, finds a suitable ID that has not yet been used.

\param    type
					The type of resource we are looking for an ID

\return   ResourceID
					A proper ID that can be used for the type
*/
/******************************************************************************/
ResourceID ResourceManager::GetNewID(ResourceType type)
{
	auto IDIt = m_IDs.find(type);
	ResourceID retVal = 0;
	// if the resource map does not exist
	if (IDIt == m_IDs.end())
	{
		CreateResourceMap(type);
		IDIt = m_IDs.find(type);
	}
	
	auto const& nameMap = m_ResourceNameMap.find(type)->second;
	auto nameIt = nameMap.find(IDIt->second);
	// find a Resource ID that does not exist yet
	while (nameIt != nameMap.end())
	{
		nameIt = nameMap.find(++(IDIt->second));
	}
	// we found the ID to use
	retVal = IDIt->second++;
	

	return retVal;
}

/******************************************************************************/
/*!
					CreateResourceMap

\author   John Salguero

\brief    Creates a resource map if one does not already exist. This should
					only be called if the mutex is locked.

\param    type
					The type of resource map to make

\return   void
*/
/******************************************************************************/
void ResourceManager::CreateResourceMap(ResourceType type)
{
	m_ResourceMap.insert(std::pair<ResourceType, ResourceMap>(type, ResourceMap()));
	m_ResourceNameMap.insert(std::pair<ResourceType, ResourceNameMap>(type, ResourceNameMap()));
	m_ResourceIDMap.insert(std::pair<ResourceType, ResourceIDMap>(type, ResourceIDMap()));
	m_IDs.insert(std::pair<ResourceType, ResourceID>(type, 0));
}

/******************************************************************************/
/*!
					InsertNewResource

\author   John Salguero

\brief    Given its name, and id, and the resource - inserts it into the memory
					manager.

\param    name
					The name of the resource to insert

\param    id
					The id of the resource to insert

\param    resource
					The actual resource to insert

\return   void
*/
/******************************************************************************/
void ResourceManager::InsertNewResource(
	ResourceType type, std::wstring const& name, ResourceID id, std::shared_ptr<Resource> const& resource)
{
	m_Mutex.lock();
	m_ResourceMap[type].insert(std::pair<ResourceID, std::shared_ptr<Resource>>(id, resource));
	m_ResourceNameMap[type].insert(std::pair<ResourceID, std::wstring>(id, name));
	m_ResourceIDMap[type].insert(std::pair<std::wstring, ResourceID>(name, id));
	m_Mutex.unlock();
}

/******************************************************************************/
/*!
					InsertNewResource

\author   John Salguero

\brief    Given its name and the resource - inserts it into the memory
					manager. The manager will pick the id. ID should be proper when
					calling this

\param    name
					The name of the resource to insert

\param    resource
					The actual resource to insert

\return   void
*/
/******************************************************************************/
void ResourceManager::InsertNewResource(
	ResourceType type, std::wstring const& name, std::shared_ptr<Resource> const& resource)
{
	ResourceID id = GetNewID(type);
	resource->m_ID = id;
	m_Mutex.lock();
	m_ResourceMap[type].insert(std::pair<ResourceID, std::shared_ptr<Resource>>(id, resource));
	m_ResourceNameMap[type].insert(std::pair<ResourceID, std::wstring>(id, name));
	m_ResourceIDMap[type].insert(std::pair<std::wstring, ResourceID>(name, id));
	m_Mutex.unlock();
}
