/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    Joint.h
  \author  John Salguero
  \date    June 26, 2023
  \brief
    This header file declares the Joint class, which is am object
    owned by Skeleton that describe the animations each part of the
    models do.
*/
/********************************************************************/
#ifndef Joint_H
#define Joint_H

struct Animation; // forward declaration

struct Joint {

  // brings takes the verticies from bone space to model space
  QuaternionTransform m_globalBindposeInverse;
  // index to this joint's parent joint in the skeleton's vector of joints (if parent does not exist, value is -1)
  int m_parentIndex;
  // The frames of each animation
  std::vector<Animation> m_Animations;
};

#endif