/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    Object.h
  \author  John Salguero
  \date    June 24, 2023
  \brief
    This header file declares the Object class, which is a class that 
    holds the different components that define each of the entities
    in the game. This uses the Enity Component System (ECS) software 
    architectural pattern.

*/
/********************************************************************/
#ifndef _Object
#define _Object

// Forward Declarations
class ObjectFactory;

class Object : public std::enable_shared_from_this<Object> {

  comrade ObjectFactory;
  // Private constructor, only the factory should make objects
  Object();


public:

private:

};

#endif // !_Object
