/******************************************************************/
/*!
	All content (C) John Salguero, all rights reserved.
	Reproduction or disclosure of this file or its contents without the
	prior written consent of John Salguero is prohibited.

	\file    ResourceManager.h
	\author  John Salguero
	\date    June 25, 2023
	\brief
		This header file defines the Resource Manager class which
		Manages the different resources loaded in the game
*/
/********************************************************************/
#ifndef _ResourceManager_H
#define _ResourceManager_H

#include "Resource.h" // ResourceID
#include "Shader.h"   // Shader

class ResourceManager : public std::enable_shared_from_this<ResourceManager> {

public:
	// Retrieves a resource
	std::weak_ptr<Resource> GetResource(ResourceType type, ResourceID index) const;
	std::weak_ptr<Resource> GetResource(ResourceType type, std::wstring const& name);

	// Loads a resource
	ResourceID LoadResource(ResourceType type, std::wstring const& name);
	// used to specify if a resource's ID
	ResourceID LoadResource(ResourceType type, std::wstring const& name, ResourceID hint);

private:
	// Specifically loads in a Shader and takes care of what a shader needs
	ResourceID LoadShader(std::wstring const&, ResourceID);
	// Specifically loads in a Model and takes care of what a shader needs
	ResourceID LoadModel(std::wstring const&, ResourceID);
	// Get a new ID number to use
	ResourceID GetNewID(ResourceType);
	// Create Resource Map
	void CreateResourceMap(ResourceType);
	// inserts a new resource into the maps
	void InsertNewResource(ResourceType, std::wstring const&, ResourceID, std::shared_ptr<Resource> const&);
	// maps the resource maps to types
	ResourceMapMap m_ResourceMap;
	// maps ID to name
	ResourceNameMapMap m_ResourceNameMap;
	// maps names to ID
	ResourceIDMapMap m_ResourceIDMap;
	// the next ID to use
	ResourceTypeIDMap m_IDs;
	// Mutex so that we can load Resources from multiple threads
	std::mutex m_Mutex;
};

#endif
