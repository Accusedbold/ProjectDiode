/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    ObjectFactory.h
  \author  John Salguero
  \date    June 24, 2023
  \brief
    This header file declares the ObjectFactory class, which is a class 
    that creates and Manages Objects.

*/
/********************************************************************/
#ifndef ObjectFactory_H
#define ObjectFactory_H

// precompiler define used to help add component factories
#define RegisterComponent(type) ObjectFactory::GetInstance()->AddComponentFactory(ComponentType::##type, std::shared_ptr<ComponentBaseFactory>(new ComponentFactory<type, ComponentType::##type>()));

class ObjectFactory : public std::enable_shared_from_this<ObjectFactory> {

  // Private constructor, using the singleton pattern
  ObjectFactory() = default;
public:
  // Virtual Destructor - good practice to remember
  ~ObjectFactory() = default;

  // Retrieves the instance of the singleton
  [[nodiscard]] static ObjectFactory* GetInstance();

  /* Creates a Generic Object */
  std::weak_ptr<Object> CreateGenericObject();

  /* Creates a Generic Object for Archetyping purposes */
  std::weak_ptr<Object> CreateGenericArchetype(const std::wstring& ArchetypeName);

  /* Creates an Archetype */
  std::weak_ptr<Object> CreateArchetypedObject(const std::wstring& ArchetypeName);

  /* Creates a Component */
  [[nodiscard]] std::shared_ptr<Component> CreateComponent(ComponentType);

  /* Add Archetype */
  void AddArchetype(const std::wstring& ArchetypeName, std::weak_ptr<Object> const&);

  /* Add Component Factory */
  void AddComponentFactory(ComponentType, std::shared_ptr<ComponentBaseFactory>);

  /* Add a component to the object using its default values */
  std::weak_ptr<Component> const GiveObjectComponent(std::weak_ptr<Object> const&, ComponentType);
  std::weak_ptr<Component> const GiveObjectComponent(ObjectID, ComponentType);

  /* Add a specific component to the object */
  std::weak_ptr<Component> const GiveObjectComponent(std::weak_ptr<Object> const&, std::weak_ptr<Component> const&);
  std::weak_ptr<Component> const GiveObjectComponent(ObjectID, std::weak_ptr<Component> const&);

  /* Add a component to the archetype using its default values */
  std::weak_ptr<Component> const GiveArchetypeComponent(std::weak_ptr<Object> const&, ComponentType);
  std::weak_ptr<Component> const GiveArchetypeComponent(const std::wstring&, ComponentType);

  /* Add a specific component to the archetype */
  std::weak_ptr<Component> const GiveArchetypeComponent(std::weak_ptr<Object> const&, std::weak_ptr<Component> const&);
  std::weak_ptr<Component> const GiveArchetypeComponent(const std::wstring&, std::weak_ptr<Component> const&);


  /* Destroys a given Object */
  void Destroy(std::weak_ptr<Object> const&);

  /* Destroys an Object with a given id */
  void Destroy(ObjectID);

  /* Destroy All the Objects */
  void DestroyAllObjects();

  /* Destroys a Given Archetype */
  void DestroyArchetype(const std::wstring& ArchetypeName);

  /* Destroys the Archetypes */
  void DestroyAllArchetypes();

  /* Releases all the Resources */
  int Release();

  /* Updates all the objects */
  void Update(double dt);
private:
  /* Instance of the Singleton */
  static ObjectFactory* m_Instance;

  /* tracks the last object ID */
  ObjectID m_ID;

  /* Map of All the Objects */
  std::unordered_map<ObjectID, std::shared_ptr<Object>> m_ObjectMap;

  /* Map of all the component Factories */
  std::unordered_map<ComponentType, std::shared_ptr<ComponentBaseFactory>> m_ComponentFactoryMap;

  /* Map of All the Archetypes */
  std::unordered_map <std::wstring, std::shared_ptr<Object>> m_ArchetypeMap;

};

#endif // !_ObjectFactory
