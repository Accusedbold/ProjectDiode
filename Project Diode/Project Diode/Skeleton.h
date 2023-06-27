/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    Skeleton.h
  \author  John Salguero
  \date    June 26, 2023
  \brief
    This header file declares the Skeleton class, which is am object
    owned by Models that describe the animations each part of the
    models do.
*/
/********************************************************************/
#ifndef _SKELETON
#define _SKELETON

struct Joint; // forward declaration

struct Skeleton {
public:

private:
  std::vector<Joint> m_Joints;
};

#endif