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
	m_timeKeeper += dt;
	auto transform = m_player->has(Transform).lock();
	auto camera = m_player->has(Camera).lock();

	double period = 10000.0; // Oscillation period in milliseconds
	double range = 10.0;     // Value range (-10 to 10)

	while(m_timeKeeper > period) m_timeKeeper -= period; // Wrap time within the oscillation period
	double normalizedTime = m_timeKeeper / period; // Normalize time between 0 and 1

	// Use a sine function to oscillate the value between -1 and 1,
	// and then scale and shift it to the desired range (-10 to 10)
	double Zvalue = cos(normalizedTime * 2.0f * M_PI) * range;
	double Xvalue = sin(normalizedTime * 2.0f * M_PI) * -range;
	double YValue = 10;

	auto position = glm::vec3(Xvalue, YValue, Zvalue);
	transform->SetPosition(position);
	camera->SetLookAt(glm::vec4(-position, 0.0f));
	
}

int GameManager::Release()
{
	return 0;
}

void GameManager::Initialize()
{
	WARN("This is a hacked thing - please remove");

	// Create the archetype Bikini Babe
	std::wstring name(L"Bikini Babe");
	auto& of = *ObjectFactory::GetInstance();
	auto obj = of.CreateGenericArchetype(name).lock();
	auto renderable = 
		std::static_pointer_cast<Renderable>(of.GiveArchetypeComponent(name, ComponentType::Renderable).lock());
	of.GiveArchetypeComponent(name, ComponentType::Transform);
	auto model = std::static_pointer_cast<Model>(ResourceManager::GetInstance()->GetResource(ResourceType::Model, L"CC_Standard_B").lock());
	renderable->SetModel(model);

	// Create the Archetype Player
	std::wstring player(L"Oogler");
	auto pObj = of.CreateGenericArchetype(player).lock();
	of.GiveArchetypeComponent(player, ComponentType::Transform);
	of.GiveArchetypeComponent(player, ComponentType::Camera);

	// Instantiate the Bikini Babe
	of.CreateArchetypedObject(name);

	// Instantiate the player
	m_player = of.CreateArchetypedObject(player).lock();

}
