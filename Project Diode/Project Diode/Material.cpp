#include "stdafx.h"

Material::Material(std::wstring const& name, ResourceID id) :
	Resource(name, ResourceType::Material, id)
{}

MaterialBuffer::MaterialBuffer(Material const& conv) :
 m_Ambient(conv.m_Ambient),
 m_Diffuse(conv.m_Diffuse),
 m_Specular(conv.m_Specular),
 m_Emissive(conv.m_Emissive),
 m_Transparency(conv.m_Transparency),
 m_Shininess(conv.m_Shininess),
 m_Reflectivity(conv.m_Reflectivity)
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
