/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    Main.cpp
  \author  John Salguero
  \date    June 18, 2023
  \brief
    This cpp file defines the main functions, which is used to run
    the game from start
*/
/********************************************************************/
#include "stdafx.h"

/******************************************************************************/
/*!
          main

\author   John Salguero

\brief    The entrypoint to the application.

\param    argc
          count of the args present

\param    argv
          array of the commandline arguments

\return   Error code. 0 means it exited safely

*/
/******************************************************************************/
int main(int, char*[]) {

  // Memory Manager should be the first thing to initialize
  //MemoryManager::GetInstance();

  int retCode = 0;
  if(Engine::GetInstance()->Inititialize())
    retCode |= Engine::GetInstance()->GameLoop();
  retCode |= ObjectFactory::GetInstance()->Release();
	Engine::DestroyInstance();

  // Memory Manager should be the last thing destroyed -
  // With it goes all allocated memory
  MemoryManager::DestroyInstance();
  return retCode;
}