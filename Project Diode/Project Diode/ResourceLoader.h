/******************************************************************/
/*!
	All content (C) John Salguero, all rights reserved.
	Reproduction or disclosure of this file or its contents without the
	prior written consent of John Salguero is prohibited.

	\file    ResourceLoader.h
	\author  John Salguero
	\date    July 1, 2023
	\brief
		This header file defines the Resource Loader class which
		is responsible for loading in resources into the game
		memory
*/
/********************************************************************/
#ifndef ResourceLoader_H
#define ResourceLoader_H

// Forward Declaration
class ResourceManager;

class ResourceLoader {

	// Constructs the ResourceLoader
	ResourceLoader() = default;
public:
	// Loads a resource Depending on its type into memory
	std::shared_ptr<Resource> operator()(ResourceType type, std::wstring const& name, ResourceID id);
	// Function that gets the instance of the resource loader
	static ResourceLoader* GetInstance();
private:
	// Loads in the Shader
	std::shared_ptr<Resource> LoadCubeMap(std::wstring const& name, ResourceID id);
	// Loads in the Model
	std::shared_ptr<Resource> LoadModel(std::wstring const& name, ResourceID id);
	// Loads in the Texture
	std::shared_ptr<Resource> LoadTexture(std::wstring const& name, ResourceID id);
	// Loads in a material so it can be used in multiple meshes
	void LoadResources();

	// Instance of the resource loader
	static ResourceLoader* m_Instance;
};
#endif