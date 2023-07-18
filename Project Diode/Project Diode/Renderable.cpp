/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    Renderable.cpp
  \author  John Salguero
  \date    June 25, 2023
  \brief
    This cpp file declares the Renderable class, which is a
    component that is used in conjunction with the Graphics
    System to draw things to the screen

*/
/********************************************************************/
#include "stdafx.h"
#include "Joint.h"
#include "Animation.h"

/******************************************************************************/
/*!
          CloneComponent

\author   John Salguero

\brief    Creates a clone of the current component

\return   std::shared_ptr<Component>
          The clone of the component
*/
/******************************************************************************/
std::shared_ptr<Component> Renderable::CloneComponent() const
{
  auto clone = std::static_pointer_cast<Renderable>(ObjectFactory::GetInstance()->CreateComponent(m_Type));

  *clone = *this;

	return clone;
}

/******************************************************************************/
/*!
           Update

\author    John Salguero

\brief     Updates the component

\return    void

*/
/******************************************************************************/
void Renderable::Update(double dt)
{
  if (m_isAnimating)
  {
    // update the times 
    m_CurrFrameTime += static_cast<float>(dt);

    auto const& animations = m_Model->m_skeleton[0].m_Animations;
    auto const& animation = m_Model->m_skeleton[0].m_Animations[m_AnimationID];
    float delay = static_cast<float>(animation.m_FrameDelay);
    while (m_CurrFrameTime > delay)
    {
      m_CurrFrameTime -= delay;
      m_CurrFrame++;
      if (m_CurrFrame >= animation.m_Count - 1)
      {
        m_AnimationID = m_nextAnimationID;
        if (++m_nextAnimationID == animations.size())
          m_nextAnimationID = 0;
        m_CurrFrame = 0;
      }
    }
    m_CurrAnimationFrameInterpolation = m_CurrFrameTime / delay;
    
  }
}

/******************************************************************************/
/*!
           Release

\author    John Salguero

\brief     Releases the component

\return    void

*/
/******************************************************************************/
void Renderable::Release()
{
}

/******************************************************************************/
/*!
           Initialize

\author    John Salguero

\brief     Initialize the component

\return    void

*/
/******************************************************************************/
void Renderable::Initialize()
{
}

/******************************************************************************/
/*!
           GetModelID

\author    John Salguero

\brief     Gets the model ID

\return    ResourceID
           The ID of the model uses to draw to the screen

*/
/******************************************************************************/
ResourceID Renderable::GetModelID() const
{
  return m_Model->GetID();
}

/******************************************************************************/
/*!
           GetModelID

\author    John Salguero

\brief     Gets the model

\return    shared_ptr<Model>
           The pointer to the model the renderable uses to draw to the screen

*/
/******************************************************************************/
std::shared_ptr<Model> Renderable::GetModel() const
{
  return m_Model;
}

/******************************************************************************/
/*!
           IsTransparent

\author    John Salguero

\brief     Gets whether the renderable is transparent. This affects the whole
           Renderable and not just some of the meshes, which may already be
           transparent.

\return    bool
           whether the renderable is transparent

*/
/******************************************************************************/
bool Renderable::IsTransparent() const
{
  return m_IsTransparent;
}

/******************************************************************************/
/*!
           GetTransparency

\author    John Salguero

\brief     How transparent the renderable is. This affects the entire model
           and not just some of the meshes

\return    float
           1 is fully transparent, 0 is fully opaque.

*/
/******************************************************************************/
float Renderable::GetTransparency() const
{
  return m_TransparencyFactor;
}

/******************************************************************************/
/*!
           IsVisible

\author    John Salguero

\brief     Whether the renderable should be drawn

\return    bool
           whether to draw the renderable.

*/
/******************************************************************************/
bool Renderable::IsVisible() const
{
  return m_Visible;
}

/******************************************************************************/
/*!
           IsDebug

\author    John Salguero

\brief     Whether the renderable should be drawn only as a debug object

\return    bool
           whether to draw the renderable as a debug object.

*/
/******************************************************************************/
bool Renderable::IsDebug() const
{
  return m_Debug;
}

/******************************************************************************/
/*!
           HasAnimation

\author    John Salguero

\brief     Whether the renderable has animation

\return    bool
           whether to draw the renderable has animation.

*/
/******************************************************************************/
bool Renderable::HasAnimation() const
{
  return m_HasAnimation;
}

/******************************************************************************/
/*!
           GetMaterialFlags

\author    John Salguero

\brief     the different materials in the current Model

\return    std::set<long>
           The different Materials in the model.

*/
/******************************************************************************/
std::set<long> const& Renderable::GetMaterialFlags()
{
  return m_MaterialFlags;
}

/******************************************************************************/
/*!
           GetAnimationIndices

\author    John Salguero

\brief     Obtains Animation data, which determines which frame to use

\param     currAnimationIndex
           output which animtaion to use

\param     currFrame
           output which frame of the animation to use

\param     animInterpolation
           output how much to interpolate betweeen the animations


\return    void

*/
/******************************************************************************/
void Renderable::GetAnimationIndices(size_t& currAnimationIndex, size_t& currFrame, float& animInterpolation)
{
  currAnimationIndex = m_AnimationID;
  currFrame = m_CurrFrame;
  animInterpolation = m_CurrAnimationFrameInterpolation;
}

/******************************************************************************/
/*!
          SetModel

\author   John Salguero

\brief    Changes the model of the renderable, assumes the model is properly set 
          upon creation. IF the model changes after creations, sends out a message
          that can be handled by graphics system letting it know to reorder
          how it draws that model based on its flags. You really shouldn't
          use this except for object creation. There is the possibility of
          dangling a model that the resource manager has expunged.

\param    modelID
          ID of the new model to draw

\return   void

*/
/******************************************************************************/
void Renderable::SetModel(ResourceID modelID)
{
  auto sharedModel = 
    std::static_pointer_cast<Model>(
      ResourceManager::GetInstance()->GetResource(ResourceType::Model, modelID).lock());
  SetModel(sharedModel);
}

/******************************************************************************/
/*!
          SetModel

\author   John Salguero

\brief    Changes the model of the renderable, assumes the model is properly set
          upon creation. IF the model changes after creations, sends out a message
          that can be handled by graphics system letting it know to reorder
          how it draws that model based on its flags. You really shouldn't
          use this except for object creation. There is the possibility of
          dangling a model that the resource manager has expunged.

\param    model
          pointer of the model to set

\return   void

*/
/******************************************************************************/
void Renderable::SetModel(std::shared_ptr<Model>& modelPtr)
{
  // gets the model to set values for the renderable
  m_PrevModel = m_Model;
  m_Model = modelPtr;
  if (m_PrevModel == m_Model)
    return;

  auto const& model = *m_Model;
  // sets the material flags of the renderable
  m_MaterialFlags.clear();
  for (auto const& mesh : model.m_meshes) {
    for (auto const& material : mesh.m_Materials) {
      long flags = material->GetMaterialFlags();
      m_MaterialFlags.insert(flags);
    }
  }

  m_HasAnimation = !model.m_skeleton.empty();

  // Determins if the graphics system needs to know about the change
  if (m_PrevModel)
  {
    std::shared_ptr<Message>msg(
      new Message(L"Renderable", MessageType::ModelChange, std::enable_shared_from_this<Renderable>::shared_from_this()));
    Engine::GetInstance()->ImmediateMessage(msg);
  }
}

/******************************************************************************/
/*!
          SetIsAnimating

\author   John Salguero

\brief    Sets the status of animation, false means paused animation

\param    isAnimating
          Whether the model is animating

\return   void

*/
/******************************************************************************/
void Renderable::SetIsAnimating(bool isAnimating)
{
  m_isAnimating = isAnimating;
}

/******************************************************************************/
/*!
          SetIsTransparent

\author   John Salguero

\brief    Sets whether or not the whole renderable is affected by the transparency
          factor. Meshes that are already transparent within the model will
          remain transparent

\param    transparent
          Whether the model is transparent

\return   void

*/
/******************************************************************************/
void Renderable::SetIsTransparent(bool transparent)
{
  if (m_IsTransparent == transparent)
    return;
  m_IsTransparent = transparent;


  std::shared_ptr<Message>msg(
    new Message(L"Renderable", MessageType::TransparencyChange, std::enable_shared_from_this<Renderable>::shared_from_this()));
  Engine::GetInstance()->ImmediateMessage(msg);
}

/******************************************************************************/
/*!
          SetTransparency

\author   John Salguero

\brief    Sets the transparency factor. 1 is fully transparent, 0 is fully opaque.

\param    transparency
          The transparency factor of the renderable

\return   void

*/
/******************************************************************************/
void Renderable::SetTransparency(float transparency)
{
  m_TransparencyFactor = transparency;
}

/******************************************************************************/
/*!
          SetVisible

\author   John Salguero

\brief    Sets the whether the renderable should be drawn.

\param    visible
          whether the renderable should be drawn.

\return   void

*/
/******************************************************************************/
void Renderable::SetVisible(bool visible)
{
  m_Visible = visible;
}

/******************************************************************************/
/*!
          SetDebug

\author   John Salguero

\brief    Sets the whether the renderable should be drawn.

\param    visible
          whether the renderable should be drawn.

\return   void

*/
/******************************************************************************/
void Renderable::SetDebug(bool debug)
{
  m_Debug = debug;
}

