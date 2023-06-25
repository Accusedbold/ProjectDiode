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

class Resource {
  Resource(std::wstring const& name, ResourceType type) : m_name(name), m_type(type) {

  }

  std::wstring GetName() { return m_name; }
  ResourceType GetType() { return m_type; }

  virtual ~Resource() = default;
private:
  std::wstring m_name;
  ResourceType m_type;
};

using ResourceID = unsigned long long;
using ResourceMap = std::unordered_map<ResourceID, std::shared_ptr<Resource>>;
using ResourceMapMap = std::unordered_map<ResourceType, ResourceMap>;
using ResourceIDMap = std::unordered_map<std::wstring, ResourceID>;
using ResourceIDMapMap = std::unordered_map<ResourceType, ResourceIDMap>;
using ResourceNameMap = std::unordered_map<ResourceID, std::wstring>;
using ResourceNameMapMap = std::unordered_map<ResourceType, ResourceNameMap>;
using ResourceTypeIDMap = std::unordered_map<ResourceType, ResourceID>;

#endif
