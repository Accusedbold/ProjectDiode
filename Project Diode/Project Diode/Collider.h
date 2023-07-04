/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    Collider.h
  \author  John Salguero
  \date    July 4, 2023
  \brief
    This header file declares the Collider class, which is a class that
    allows for colision detection.

*/
/********************************************************************/
#ifndef Collider_H
#define Collider_H

class Collider : public Component, public std::enable_shared_from_this<Collider> {

public:
  // Clones the component
  std::shared_ptr<Component> CloneComponent() const override;
  // updates the component
  void Update(double) override;
  // Releases the component
  void Release() override;
  // Initializes the component
  void Initialize() override;
 
protected:
};

#endif