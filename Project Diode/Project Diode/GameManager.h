/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    GameManager.h
  \author  John Salguero
  \date    July 2, 2023
  \brief
    This header file declares the the GameManager Class which
    is used to manage and drive the logic of the game
*/
/********************************************************************/
#ifndef GameManager_H
#define GameManager_H

// System to handle and maintain the window state
class GameManager : public System, public std::enable_shared_from_this<GameManager> {
public:
  // Constructor
  GameManager(std::wstring& name);

  // Updates the function on a per frame basis
  virtual void Update(double dt);

  // Releases the system and deletes all allocations
  virtual int Release();

  // Initializes the system
  virtual void Initialize();

private:
  // Hacked player object
  WARN("This is Hacked, please Remove");
  std::shared_ptr<Object> m_player;
  double m_timeKeeper = 0;
};

#endif
