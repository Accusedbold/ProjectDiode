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
#include "ResourceManager.h"

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

std::weak_ptr<Resource> ResourceManager::GetResource(ResourceType type, std::wstring const& name)
{
	// lock during reads and writes
	m_Mutex.lock();
	// get an iterator to the resource map
	auto mapIt = m_ResourceMap.find(type);
	// if we don't have a map for the resource type create the related maps
	if (mapIt == m_ResourceMap.end())
	{
		m_ResourceMap.insert(std::pair<ResourceType, ResourceMap>(type, ResourceMap()));
		m_ResourceNameMap.insert(std::pair<ResourceType, ResourceNameMap>(type, ResourceNameMap()));
		m_ResourceIDMap.insert(std::pair<ResourceType, ResourceIDMap>(type, ResourceIDMap()));
		m_IDs.insert(std::pair<ResourceType, ResourceID>(type, 0));
		// unlock after writing and before loading
		m_Mutex.unlock();
		// Load in the Resource and return the resource
		ResourceID id = LoadResource(type, name);
		return m_ResourceMap.find(type)->second.find(id)->second;
	}
	/// We have a have a map for the resource already
	// get an iterator to the map of IDs
	auto IDMap = m_ResourceIDMap.find(type)->second;
	auto IDIt = IDMap.find(name);
	// If we do not have an ID already, resource needs to be loaded
	if (IDIt == IDMap.end()) 
	{
		// unlock after writing and before loading
		m_Mutex.unlock();
		// Load in the Resource and return the resource
		ResourceID id = LoadResource(type, name);
		return m_ResourceMap.find(type)->second.find(id)->second;
	}
	// We Do have ID already, just return the resource
	m_Mutex.unlock();
	return m_ResourceMap[type][IDIt->second];
}

ResourceID ResourceManager::LoadResource(ResourceType type, std::wstring const& name)
{
	// get an iterator to the resource map
	auto mapIt = m_ResourceMap.find(type);

	// The Resource map does not exist, make it
	if (mapIt == m_ResourceMap.end()) {
		m_ResourceMap.insert(std::pair<ResourceType, ResourceMap>(type, ResourceMap()));
		mapIt = m_ResourceMap.find(type);
	}
	// Get an iterator to the map of IDs
	auto IDIt = m_ResourceIDMap.find(name);
	// if the ID exists alread, we already loaded it in
	if (IDIt != m_ResourceIDMap.end())
		return IDIt->second;
	// get a new id
	ResourceID id = m_R

	WARN("TODO: Loading in the resources Hardcoding some in")
		switch (type) {
		case ResourceType::Model:
			std::shared_ptr<Model> loadedModel(new Model);
			loadedModel->
				break;
		}
	return std::weak_ptr<Resource>();
}

ResourceID ResourceManager::LoadResource(ResourceType type, std::wstring const& name, ResourceID hint)
{
	return ResourceID();
}
