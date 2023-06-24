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
#ifndef _ObjectFactory
#define _ObjectFactory

using ObjectID = unsigned long;

class ObjectFactory : public std::enable_shared_from_this<ObjectFactory> {

  // Private constructor, using the singleton pattern
  ObjectFactory() = default;
public:
  // Virtual Destructor - good practice to remember
  ~ObjectFactory() = default;


private:
  /* tracks the last object ID */
  ObjectID m_ID;

  /* Map of All the Objects */
  std::unordered_map<ObjectID, std::shared_ptr<Object>> mObjectMap;

  /* Map of all the component Factories */
  std::unordered_map<ComponentType, std::shared_ptr<ComponentBaseFactory>> mComponentFactoryMap;

  /* Map of All the Archetypes */
  std::unordered_map <std::wstring, std::shared_ptr<Object>> mArchetypeMap;

};

#endif // !_ObjectFactory
