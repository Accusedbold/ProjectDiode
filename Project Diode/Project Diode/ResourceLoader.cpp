/******************************************************************/
/*!
	All content (C) John Salguero, all rights reserved.
	Reproduction or disclosure of this file or its contents without the
	prior written consent of John Salguero is prohibited.

	\file    ResourceLoader.cpp
	\author  John Salguero
	\date    July 1, 2023
	\brief
		This cpp file defines the Resource Loader class which
		is responsible for loading in resources into the game
		memory
*/
/********************************************************************/
#include "stdafx.h"
#include "ResourceLoader.h"
#include "Model.h"
#include "Texture.h"

ResourceLoader* ResourceLoader::m_Instance = nullptr;

/******************************************************************************/
/*!
					LoadResource

\author   John Salguero

\brief    Loads the resource given a type, name, and id. This will not load
					in Materials, since those get loaded in from the model, however
					The Resource Manager still manages those, as materials can be
					shared between meshes.

\param    type
					The type of Resource to load

\param    name
					The name of the resource to load

\param    id
					The ID to give the resource

\return   std::shared_ptr<Resource>
					The Resource that got loaded in
*/
/******************************************************************************/
std::shared_ptr<Resource> ResourceLoader::operator()(ResourceType type, std::wstring const& name, ResourceID id)
{
	switch (type) {
	case ResourceType::Texture:
		return LoadTexture(name, id);
	case ResourceType::Model:
		return LoadModel(name, id);
	case ResourceType::CubeMap:
		return LoadCubeMap(name, id);
	default:
		return std::shared_ptr<Resource>();
	}
}

/******************************************************************************/
/*!
					GetInstance

\author   John Salguero

\brief    Returns an instance of the singleton resource loader.

\return   ResourceLoader*
					The Resource Loader
*/
/******************************************************************************/
ResourceLoader* ResourceLoader::GetInstance()
{
	if (!m_Instance)
		m_Instance = new ResourceLoader;
	return m_Instance;
}

/******************************************************************************/
/*!
					LoadCubeMap

\author   John Salguero

\brief    Loads in the cubemap to GPU memory via OpenGL.

\param    name
					The name of the directory with the cube map to load

\param    id
					The id to use in initializing the texture

\return   std::shared_ptr<Resource>
					The Texture that got loaded in
*/
/******************************************************************************/
std::shared_ptr<Resource> ResourceLoader::LoadCubeMap(std::wstring const& name, ResourceID id)
{
	std::wstring filenames[6] = {
	{TEXTURE_DIRECTORY + name + POS_X_FILENAME},
	{TEXTURE_DIRECTORY + name + NEG_X_FILENAME},
	{TEXTURE_DIRECTORY + name + POS_Y_FILENAME},
	{TEXTURE_DIRECTORY + name + NEG_Y_FILENAME},
	{TEXTURE_DIRECTORY + name + POS_Z_FILENAME},
	{TEXTURE_DIRECTORY + name + NEG_Z_FILENAME}
	};

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	for (GLenum i = 0; i < 6; ++i) {
		std::string cName;
		std::transform(filenames[i].begin(), filenames[i].end(), std::back_inserter(cName), [](wchar_t c) {return (char)c; });
		SDL_Surface* surface = IMG_Load(cName.c_str());
		FATAL_ERRORIF(!surface, "Could not load in Texture Name: " + cName);

		// Load texture data into OpenGL
		switch (surface->format->format)
		{
		case SDL_PIXELFORMAT_RGB24:
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, surface->w, surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);
			break;
		case SDL_PIXELFORMAT_ARGB8888:
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, surface->w, surface->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, surface->pixels);
			break;
		case SDL_PIXELFORMAT_ABGR8888:
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
			break;
		default:
			break;
		}
		// Free SDL surface (we don't need it anymore)
		SDL_FreeSurface(surface);
	}

	// Set texture parameters
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	std::shared_ptr<Texture> loadedTexture(new Texture(name, id, ResourceType::CubeMap));
	loadedTexture->m_textureID = textureID;

	return loadedTexture;
}

/******************************************************************************/
/*!
					LoadModel

\author   John Salguero

\brief    Loads in the model to memory.

\param    name
					The name of the model to load

\param    id
					The id to use in initializing the model

\return   std::shared_ptr<Resource>
					The Model that got loaded in
*/
/******************************************************************************/
std::shared_ptr<Resource> ResourceLoader::LoadModel(std::wstring const& name, ResourceID id)
{
	fs::path filePath = MODEL_DIRECTORY + name + L".model";
	std::ifstream inputFile(filePath, std::ios::binary);
	FATAL_ERRORIF(!inputFile.is_open(), "Could not open file: " + filePath.string());

	std::shared_ptr<Model>loadedModel(new Model(name, id));
	inputFile >> *loadedModel;
	inputFile.close();

	return loadedModel;
}

/******************************************************************************/
/*!
					LoadTexture

\author   John Salguero

\brief    Loads in the texture to memory.

\param    name
					The name of the texture to load

\param    id
					The id to use in initializing the texture

\return   std::shared_ptr<Resource>
					The Texture that got loaded in
*/
/******************************************************************************/
std::shared_ptr<Resource> ResourceLoader::LoadTexture(std::wstring const& name, ResourceID id)
{

	std::wstring filename = TEXTURE_DIRECTORY + name;
	std::string cName;
	std::transform(filename.begin(), filename.end(), std::back_inserter(cName), [](wchar_t c) {return (char)c;});
	SDL_Surface* surface = IMG_Load(cName.c_str());
	FATAL_ERRORIF(!surface, "Could not load in Texture Name: " + cName);

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Set texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Load texture data into OpenGL
	switch (surface->format->format)
	{
	case SDL_PIXELFORMAT_RGB24:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, surface->w, surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);
		break;
	case SDL_PIXELFORMAT_ARGB8888:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, surface->w, surface->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, surface->pixels);
		break;
	default:
		break;
	}

	// Free SDL surface (we don't need it anymore)
	SDL_FreeSurface(surface);
	std::shared_ptr<Texture> loadedTexture(new Texture(name, id));
	loadedTexture->m_textureID = textureID;

	return loadedTexture;
}

void ResourceLoader::LoadResources()
{
	fs::path directoryPath = "Resources/Textures";
	
	directoryPath = "Resources/Models";
	
	directoryPath = "Resources/Shaders";
	
}
