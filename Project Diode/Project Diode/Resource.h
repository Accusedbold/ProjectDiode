/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    iResource.h
  \author  John Salguero
  \date    June 25, 2023
  \brief
    This header file declares the iResource class, which is a type
    that is managed by resource Managers

*/
/********************************************************************/
#ifndef _iResource
#define _iResource

using ResourceID = unsigned long long;

class Resource {
public:
  Resource(std::wstring const& name, ResourceType type, ResourceID id) : 
    m_name(name), m_type(type), m_ID(id) {}
  virtual ~Resource() = default;

  std::wstring GetName() { return m_name; }
  ResourceType GetType() { return m_type; }

private:
  // name of the resource
  std::wstring m_name;
  // type of the resource
  ResourceType m_type;
  // id of the resource
  ResourceID m_ID;
};

using ResourceMap = std::unordered_map<ResourceID, std::shared_ptr<Resource>>;
using ResourceMapMap = std::unordered_map<ResourceType, ResourceMap>;
using ResourceIDMap = std::unordered_map<std::wstring, ResourceID>;
using ResourceIDMapMap = std::unordered_map<ResourceType, ResourceIDMap>;
using ResourceNameMap = std::unordered_map<ResourceID, std::wstring>;
using ResourceNameMapMap = std::unordered_map<ResourceType, ResourceNameMap>;
using ResourceTypeIDMap = std::unordered_map<ResourceType, ResourceID>;
#endif
