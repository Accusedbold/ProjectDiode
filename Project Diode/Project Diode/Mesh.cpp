#include "stdafx.h"

void Mesh::GenerateDataBuffer()
{
  // Create the VAO that openGL will use
  glGenVertexArrays(1, m_VAO);
  // Bind it so that we may add an EBO to the state
  glBindVertexArray(m_VAO[0]);
  // size of the entire data
  size_t size = 0;
  // Setup all the attributes for the VAO and obtain the size of the data
  // Material Indices - use short for faster data transfers
  size += m_PosIndicies.size() * sizeof(GLushort);
  size += m_Positions.size() * sizeof(glm::vec4);
  size += m_Normals.size() * sizeof(glm::vec4);
  size += m_Tangents.size() * sizeof(glm::vec4);
  size += m_BiTangents.size() * sizeof(glm::vec4);
  size += m_Colors.size() * sizeof(glm::vec4);
  size += m_UVs.size() * sizeof(glm::vec2);
  size += m_SkeletalIndices.size() * MAX_BONE_INFLUENCE * sizeof(GLushort);
  size += m_SkeletalWeights.size() * MAX_BONE_INFLUENCE * sizeof(float);

  m_Data = new char[size];

  // Create the VBO and EBO which will be bound to the VAO
  GLuint buffers[2];
  glGenBuffers(2, buffers);
  GLuint& vbo = buffers[0], & ebo = buffers[1];
  // bind 
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

  size_t offset = 0;
  // Material indicies are per face, so each vertex of the triangle should have the same material
  // making indices shorts since that makes data transfer faster
  glVertexAttribPointer(0, 1, GL_UNSIGNED_SHORT, GL_FALSE, 0, reinterpret_cast<const void*>(offset));
  for (auto index : m_MaterialIndices)
  {
    for (int i = 0; i < 3; ++i)
    {
      (*reinterpret_cast<GLushort*>(m_Data + offset)) = static_cast<GLushort>(index);
      offset += sizeof(GLushort);
    }
  }
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<const void*>(offset));
  std::memcpy(m_Data + offset, m_Positions.data(), m_Positions.size() * sizeof(glm::vec4));
  offset += m_Positions.size() * sizeof(glm::vec4);
  glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<const void*>(offset));
  std::memcpy(m_Data + offset, m_Normals.data(), m_Normals.size() * sizeof(glm::vec4));
  offset += m_Normals.size() * sizeof(glm::vec4);
  glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<const void*>(offset));
  std::memcpy(m_Data + offset, m_Tangents.data(), m_Tangents.size() * sizeof(glm::vec4));
  offset += m_Tangents.size() * sizeof(glm::vec4);
  glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<const void*>(offset));
  std::memcpy(m_Data + offset, m_BiTangents.data(), m_BiTangents.size() * sizeof(glm::vec4));
  offset += m_BiTangents.size() * sizeof(glm::vec4);
  glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<const void*>(offset));
  std::memcpy(m_Data + offset, m_Colors.data(), m_Colors.size() * sizeof(glm::vec4));
  offset += m_Colors.size() * sizeof(glm::vec4);
  glVertexAttribPointer(6, 2, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<const void*>(offset));
  std::memcpy(m_Data + offset, m_UVs.data(), m_UVs.size() * sizeof(glm::vec2));
  offset += m_UVs.size() * sizeof(glm::vec2);
  glVertexAttribPointer(7, 4, GL_UNSIGNED_SHORT, GL_FALSE, 0, reinterpret_cast<const void*>(offset));
  for (auto skelIndexVec : m_SkeletalIndices)
  {
    for (auto index : skelIndexVec)
    {
      (*reinterpret_cast<GLushort*>(m_Data + offset)) = static_cast<GLushort>(index);
      offset += sizeof(GLushort);
    }
  }
  glVertexAttribPointer(8, 4, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<const void*>(offset));
  for (auto skelWeightVec : m_SkeletalWeights)
  {
    std::memcpy(m_Data + offset, skelWeightVec.data(), skelWeightVec.size() * sizeof(float));
    offset += skelWeightVec.size() * sizeof(float);
  }

  // enable the attributes
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  glEnableVertexAttribArray(3);
  glEnableVertexAttribArray(4);
  glEnableVertexAttribArray(5);
  glEnableVertexAttribArray(6);
  glEnableVertexAttribArray(7);
  glEnableVertexAttribArray(8);

  // populate the VBO and EBO
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_PosIndicies.size() * sizeof(size_t), m_PosIndicies.data(), GL_STATIC_DRAW);
  glBufferData(GL_ARRAY_BUFFER, size, m_Data, GL_STATIC_DRAW);

  // unbind the VAO and delete the count for the VBO ad EBO so their lifetime are tied to the VAO
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  WARN("non-conformant Drivers Exist where the deletion of these do not let them persist despite having a resource count with the VAO");
  glDeleteBuffers(2, buffers);

}

Mesh::~Mesh()
{
  if (m_Data)
    delete[] m_Data;
  if (m_VAO)
    glDeleteBuffers(1, m_VAO);
}
