/******************************************************************/
/*!
	All content (C) John Salguero, all rights reserved.
	Reproduction or disclosure of this file or its contents without the
	prior written consent of John Salguero is prohibited.

	\file    GameManager.cpp
	\author  John Salguero
	\date    July 2, 2023
	\brief
		This cpp file declares the the GameManager Class which
		is used to manage and drive the logic of the game
*/
/********************************************************************/
#include "stdafx.h"

GameManager::GameManager(std::wstring& name) : System(name)
{
}

void GameManager::Update(double dt)
{
	(this->*m_UpdateFxn)(dt);
}

int GameManager::Release()
{
	return 0;
}

void GameManager::Initialize()
{

}

void GameManager::SetUpHackedBlockMan(double)
{
	WARN("This is a hacked thing - please remove");

	// Create the archetype BlockMan
	std::wstring name(L"BlockMan");
	auto& of = *ObjectFactory::GetInstance();
	auto obj = of.CreateGenericArchetype(name).lock();
	auto renderable =
		std::static_pointer_cast<Renderable>(of.GiveArchetypeComponent(name, ComponentType::Renderable).lock());
	of.GiveArchetypeComponent(name, ComponentType::Transform);
	auto model = std::shared_ptr<Model>(new Model(name, 0));
	model->m_meshes.resize(2);
	{ // HEAD
		auto& mesh = model->m_meshes[0];
		for (int i = 0; i < 8; ++i)
			mesh.m_Positions.push_back(glm::vec4(i % 2 * -.375f + .1875f, i % 4 / 2 * -.375f + .1875f + 0.9375f, i / 4 * -.375f + .1875f, 1.0f));
		mesh.m_Indices.insert(mesh.m_Indices.end(), {
			0,5,1,4,5,0, // Top
			2,3,7,2,7,6, // Bottom
			0,1,3,2,0,3, // Front
			5,4,7,7,4,6, // Back
			1,5,7,1,7,3, // Left
			4,0,6,6,0,2 });
		mesh.m_Materials.emplace_back(new Material(L"Lambert_Red", 0));
		mesh.m_MaterialIndices.resize(36, 0);
		auto& material = mesh.m_Materials[0];
		material->m_Ambient = glm::vec4(0.0f);
		material->m_Diffuse = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
		material->m_Specular = glm::vec4(0.0f);
		material->m_Emissive = glm::vec4(0.0f);
		material->m_Transparency = 0.0f;
		material->m_Reflectivity = 0.0f;
		material->m_Type = MaterialType::Lambert;
		mesh.GenerateDataBuffer();
		ResourceManager::GetInstance()->InsertNewResource(material->GetType(), material->GetName(), material);
	}
	{// Body
		auto& mesh = model->m_meshes[1];
		for (int i = 0; i < 8; ++i)
			mesh.m_Positions.push_back(glm::vec4(i % 2 * -1.0f + .5f, i % 4 / 2 * -2.0f + .75f, i / 4 * -0.5f + .25f, 1.0f));
		mesh.m_Indices.insert(mesh.m_Indices.end(), {
			0,5,1,4,5,0, // Top
			2,3,7,2,7,6, // Bottom
			0,1,3,2,0,3, // Front
			5,4,7,7,4,6, // Back
			1,5,7,1,7,3, // Left
			4,0,6,6,0,2 });
		mesh.m_Materials.emplace_back(new Material(L"Lambert_Blue", 1));
		mesh.m_MaterialIndices.resize(36, 0);
		auto& material = mesh.m_Materials[0];
		material->m_Ambient = glm::vec4(0.0f);
		material->m_Diffuse = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
		material->m_Specular = glm::vec4(0.0f);
		material->m_Emissive = glm::vec4(0.0f);
		material->m_Transparency = 0.0f;
		material->m_Reflectivity = 0.0f;
		material->m_Type = MaterialType::Lambert;
		mesh.GenerateDataBuffer();
		ResourceManager::GetInstance()->InsertNewResource(material->GetType(), material->GetName(), material);
	}
	ResourceManager::GetInstance()->InsertNewResource(model->GetType(), model->GetName(), model);
	renderable->SetModel(model);

	// Instantiate the Block Men
	int cube = 22;
	for (int i = 0; i < cube * cube * cube; ++i)
	{
		float x = (-cube + (i % cube) + cube / 2) * 5;
		float z = (-cube + ((i / cube) % cube) + cube / 2) * 5;
		float y = (-cube + ((i / cube) / cube) + cube / 2) * 5;
		of.CreateArchetypedObject(name).lock()->has(Transform).lock()->SetPosition({x,y,z});
	}

	// Instantiate the player
	m_UpdateFxn = &GameManager::SetUpHackedCamera;
}

void GameManager::SetUpHackedBikiniBabe(double)
{
	WARN("This is a hacked thing - please remove");

	// Create the archetype Bikini Babe
	std::wstring name(L"Bikini Babe");
	auto& of = *ObjectFactory::GetInstance();
	auto obj = of.CreateGenericArchetype(name).lock();
	auto renderable =
		std::static_pointer_cast<Renderable>(of.GiveArchetypeComponent(name, ComponentType::Renderable).lock());
	auto transform =
		std::static_pointer_cast<Transform>(of.GiveArchetypeComponent(name, ComponentType::Transform).lock());
	auto model = std::static_pointer_cast<Model>(ResourceManager::GetInstance()->GetResource(ResourceType::Model, L"Bikini_Babe").lock());
	renderable->SetModel(model);
	renderable->SetIsAnimating(true);
	transform->SetScale({ .025f,.025f,.025f });
	transform->SetPosition({ 0.0f, -3.0f, 0.0f });

	// Instantiate the Bikini Babe
	m_object = of.CreateArchetypedObject(name).lock();

	// Oogle the object
	m_UpdateFxn = &GameManager::SetUpHackedCamera;
}

void GameManager::SetUpHackedWarriorBabe(double)
{
	WARN("This is a hacked thing - please remove");

	// Create the archetype Bikini Babe
	std::wstring name(L"Warrior Babe");
	auto& of = *ObjectFactory::GetInstance();
	auto obj = of.CreateGenericArchetype(name).lock();
	auto renderable =
		std::static_pointer_cast<Renderable>(of.GiveArchetypeComponent(name, ComponentType::Renderable).lock());
	auto transform =
		std::static_pointer_cast<Transform>(of.GiveArchetypeComponent(name, ComponentType::Transform).lock());
	auto model = std::static_pointer_cast<Model>(ResourceManager::GetInstance()->GetResource(ResourceType::Model, L"Warrior").lock());
	renderable->SetModel(model);
	renderable->SetIsAnimating(true);
	transform->SetScale({ .025f,.025f,.025f });
	transform->SetPosition({ 0.0f, -3.0f, 0.0f });

	// Instantiate the Bikini Babe
	m_object = of.CreateArchetypedObject(name).lock();

	// Oogle the object
	m_UpdateFxn = &GameManager::SetUpHackedCamera;
}

void GameManager::SetUpHackedJade(double)
{
	WARN("This is a hacked thing - please remove");

	// Create the archetype Jade
	std::wstring name(L"Jade");
	auto& of = *ObjectFactory::GetInstance();
	auto obj = of.CreateGenericArchetype(name).lock();
	auto renderable =
		std::static_pointer_cast<Renderable>(of.GiveArchetypeComponent(name, ComponentType::Renderable).lock());
	auto transform =
		std::static_pointer_cast<Transform>(of.GiveArchetypeComponent(name, ComponentType::Transform).lock());
	auto model = std::static_pointer_cast<Model>(ResourceManager::GetInstance()->GetResource(ResourceType::Model, L"jade").lock());
	renderable->SetModel(model);
	renderable->SetIsAnimating(true);
	transform->SetScale({ .025f,.025f,.025f });
	transform->SetPosition({ 0.0f, -3.0f, 0.0f });
	constexpr float radians = glm::radians(-90.0f);
  transform->SetRotation(glm::angleAxis(radians, glm::vec3(1.0f, 0.0f, 0.0f)));

	// Instantiate Jade
	m_object = of.CreateArchetypedObject(name).lock();

	// Oogle the object
	m_UpdateFxn = &GameManager::SetUpHackedCamera;
}

void GameManager::SetUpHackedCamera(double)
{
	WARN("This is a hacked thing - please remove");

	// Create the Archetype Player
	std::wstring player(L"Oogler");
	auto& of = *ObjectFactory::GetInstance();
	auto pObj = of.CreateGenericArchetype(player).lock();
	std::static_pointer_cast<Transform>(of.GiveArchetypeComponent(player, ComponentType::Transform).lock())->SetPosition({ 0.0f, 0.0f, 7.0f });
	of.GiveArchetypeComponent(player, ComponentType::Camera);
	of.GiveArchetypeComponent(player, ComponentType::CameraController);

	// Instantiate the Player
	of.CreateArchetypedObject(player);

	// Oogle the object
	m_UpdateFxn = &GameManager::OogleObject;
}

void GameManager::SetUpHackedCube(double)
{
	WARN("This is a hacked thing - please remove");

	// Create the archetype Cube
	std::wstring name(L"Cube");
	auto& of = *ObjectFactory::GetInstance();
	auto obj = of.CreateGenericArchetype(name).lock();
	auto renderable =
		std::static_pointer_cast<Renderable>(of.GiveArchetypeComponent(name, ComponentType::Renderable).lock());
	auto transform =
		std::static_pointer_cast<Transform>(of.GiveArchetypeComponent(name, ComponentType::Transform).lock());
	auto model = std::static_pointer_cast<Model>(ResourceManager::GetInstance()->GetResource(ResourceType::Model, L"Crate").lock());
	renderable->SetModel(model);
	renderable->SetIsAnimating(false);

	// Instantiate the Cube
	m_object = of.CreateArchetypedObject(name).lock();

	// Oogle the object
	m_UpdateFxn = &GameManager::SetUpHackedCamera;
}

void GameManager::SetUpHackedTriangle(double)
{
	WARN("This is a hacked thing - please remove");

	// Create the archetype Triangle
	std::wstring name(L"Triangle");
	auto& of = *ObjectFactory::GetInstance();
	auto obj = of.CreateGenericArchetype(name).lock();
	auto renderable =
		std::static_pointer_cast<Renderable>(of.GiveArchetypeComponent(name, ComponentType::Renderable).lock());
	of.GiveArchetypeComponent(name, ComponentType::Transform);
	auto model = std::shared_ptr<Model>(new Model(name, 0));
	model->m_meshes.resize(1);
	auto& mesh = model->m_meshes[0];
	// Vertices
	mesh.m_Positions.push_back(glm::vec4(-4.78539085, -3.25717545, 165.623718, 1.0f));
	mesh.m_Positions.push_back(glm::vec4(-4.87418938, -3.26421595, 165.668549, 1.0f));
	mesh.m_Positions.push_back(glm::vec4(-4.60879135, -3.56536198, 165.460693, 1.0f));
	// Indices
	mesh.m_Indices.insert(mesh.m_Indices.end(), { 0,1,2 });
	mesh.m_Materials.emplace_back(new Material(L"Lambert_Black", 0));
	mesh.m_MaterialIndices.resize(3, 0);
	auto& material = mesh.m_Materials[0];
	material->m_Ambient = glm::vec4(0.0f);
	material->m_Diffuse = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	material->m_Specular = glm::vec4(0.0f);
	material->m_Transparency = 0.0f;
	material->m_Reflectivity = 0.0f;
	material->m_Type = MaterialType::Lambert;


	mesh.GenerateDataBuffer();
	ResourceManager::GetInstance()->InsertNewResource(model->GetType(), model->GetName(), model);
	ResourceManager::GetInstance()->InsertNewResource(material->GetType(), material->GetName(), material);
	renderable->SetModel(model);

	// Instantiate the Triangle
	of.CreateArchetypedObject(name);

	// Instantiate Bikini Babe
	m_UpdateFxn = &GameManager::SetUpHackedBikiniBabe;
}

void GameManager::OogleObject(double)
{
	//m_timeKeeper += dt;
	//auto transform = m_player->has(Transform).lock();
	//auto camera = m_player->has(Camera).lock();

	//double period = 5000.0; // Oscillation period in milliseconds
	//double range = 10.0;     // Value range (-10 to 10)

	//while (m_timeKeeper > period) m_timeKeeper -= period; // Wrap time within the oscillation period
	//double normalizedTime = m_timeKeeper / period; // Normalize time between 0 and 1

	//// Use a sine function to oscillate the value between -1 and 1,
	//// and then scale and shift it to the desired range (-10 to 10)
	//double Zvalue = cos(normalizedTime * 2.0f * M_PI) * range;
	//double Xvalue = sin(normalizedTime * 2.0f * M_PI) * -range;
	//double YValue = sin(normalizedTime * 2.0f * M_PI) * range;

	//auto position = glm::vec3(Xvalue, YValue, Zvalue);
	//transform->SetPosition(position);
	//camera->SetLookAt(glm::vec4(-position, 0.0f));
}
