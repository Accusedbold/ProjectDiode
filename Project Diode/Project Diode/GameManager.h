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

  using UpdateFxn = void (GameManager::*)(double);

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

  // Handle input from the user
  void HandleSceneInput(std::shared_ptr<Message> const&);

  // The function used to update the device
  UpdateFxn m_UpdateFxn = &GameManager::SetUpHackedCube;
  // Hacked player object
  WARN("This is Hacked, please Remove");
  void SetUpHackedBlockMan(double dt);
  void SetUpHackedBikiniBabe(double dt);
  void SetUpHackedVampire(double dt);
  void SetUpHackedWarriorBabe(double dt);
  void SetUpHackedJade(double dt);
  void SetUpHackedCube(double dt);
  void SetUpHackedTriangle(double dt);
  void SetUpHackedCamera(double dt);
  void OogleObject(double dt);
  std::shared_ptr<Object> m_player;
  std::shared_ptr<Object> m_object;
  double m_timeKeeper = 0;
};

#endif
