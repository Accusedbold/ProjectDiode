/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    Model.h
  \author  John Salguero
  \date    June 24, 2023
  \brief
    This header file declares the Model class, which is a
    resource that contains meshes that are drawn by OpenGL

*/
/********************************************************************/
#ifndef Model_H
#define Model_H

struct Mesh; // forward declaration
struct Joint;
using Skeleton = std::vector<Joint>;

struct Model : public Resource, public std::enable_shared_from_this<Model>
{
  Model(std::wstring const& name, ResourceID id);

  // collection of Meshes the model owns
  std::vector<Mesh> m_meshes;
  // A calculated middle
  glm::vec4 m_centroid;
  // The skeleton of a rigged model
  Skeleton m_skeleton;
};

#endif

