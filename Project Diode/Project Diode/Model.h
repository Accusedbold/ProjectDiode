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
#ifndef _Model
#define _Model

class Model : public std::enable_shared_from_this<Model>
{
public:

private:
  // collection of Meshes the model owns
  std::vector<Mesh> m_meshes;
  // The current animation frame
  int m_CurrFrame;
  // how much between the frames that need to be slurped
  float m_FrameInterpolation;
  // how much between the animations that need to be slurped
  float m_AnimInterpolation;
  // whether the animation is playing
  bool m_isAnimating;
  // The current animation
  int m_AnimationID;  
  // The next Animation
  int m_nextAnimationID;
  // A calculated middle
  glm::vec4 m_centroid;
  // How to scale on each axis
  glm::vec3 m_scalar;
  // The overall Model Transformation
  glm::mat4 m_modelTranformation;
  // The skeleton of a rigged model
  //Skeleton m_skeleton;
};

#endif

