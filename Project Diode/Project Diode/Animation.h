/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    Animation.h
  \author  John Salguero
  \date    June 26, 2023
  \brief
    This header file declares the Animtation class, which is am object
    owned by Skeleton that describe the animations each part of the
    models do.
*/
/********************************************************************/
#ifndef Animation_H
#define Animation_H

struct Animation {

  // The Name of the Animation
  std::wstring m_Name;
  // brings takes the verticies from model space to animated space
  std::vector<QuaternionTransform> m_globalTransform;
  // brings takes the verticies from bone space to animated space
  std::vector<QuaternionTransform> m_AnimatedTransform;
  // The delay in ms for the next frame
  unsigned m_FrameDelay;
  // The count of how many frames are in the animation
  unsigned m_Count;
};

#endif