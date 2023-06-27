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
#ifndef _ANIMATION
#define _ANIMATION

class Animation {
public:

private:
  // brings takes the verticies from model space to world space
  std::vector<glm::mat4> m_globalTransform;
  // The delay in ms between each frame
  unsigned m_FrameDelay;
  // The count of how many frames are in the animation
  unsigned m_Count;
};

#endif