/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    Debug.h
  \author  John Salguero
  \date    June 18, 2023
  \brief
    This header file is used to declare things that makes it easier to debug the program
    during compile and runtime.
*/
/********************************************************************/
#ifndef _Debug
	#define _Debug

// for funsies
#define comrade friend

// STR is used to convert a macro parameter into a string constant
#define STR(x) #x
// XSTR is used to convert a defined macro argument's definition into a string constant
#define XSTR(x) STR (x)
// This can be used with stringify to create a wide string literal of a define's parameter
#define WIDE(x) L ## x

// Used to keep notes and reminders during compilation
#define NOTE( MESSAGE ) __pragma( message (__FILE__ "(" XSTR(__LINE__) ") : NOTE [ " MESSAGE " ]") )

// Used to add a user defined warning during compilation
#define WARN( MESSAGE ) __pragma( message (__FILE__ "(" XSTR(__LINE__) ") : WARNING [ " MESSAGE " ]") )



#endif // !_Debug
