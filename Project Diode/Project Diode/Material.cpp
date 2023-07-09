#include "stdafx.h"

Material::Material(std::wstring const& name, ResourceID id) :
	Resource(name, ResourceType::Material, id) 
{}

ShaderFlags Material::GetMaterialFlags() const
{
	ShaderFlags retVal = 0;
	for (int i = 0; i < static_cast<int>(MapType::Count); ++i) {
		if (m_MappingTextures[i])
			retVal |= (1l << i);
	}
	if (m_Type == MaterialType::Phong)
		retVal |= PHONG_FLAG;
	if (m_Transparency > 0.0f || (retVal & TRANSPARENCY_MAP_FLAG))
		retVal |= TRANSPARENCY_FLAG;
	return retVal;
}
