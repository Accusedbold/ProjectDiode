/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    Main.cpp
  \author  John Salguero
  \date    June 18, 2023
  \brief
    This cpp file defines the Engine class functions, which is a class that drives the
    messaging system, game loop and updates each system accordingly
*/
/********************************************************************/
#include "stdafx.h"

int main(int argc, char* argv[]) {
	Engine::GetInstance()->GameLoop();
  Engine::DestroyInstance();
  return 0;
}