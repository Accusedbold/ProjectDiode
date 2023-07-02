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
#ifndef Debug_H
#define Debug_H

// Error Defines
#define SYSTEM_RELEASE_ERROR -1
#define ERROR_WINDOW_FAILED -2
#define FATAL_RUNTIME_ERROR -4

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

// Used to send a fatal error message to the systems
#define FATAL_ERROR(str) \
{\
  std::shared_ptr<void> data(new ErrorMessageData(std::string(str), true, __FUNCTION__, __FILE__, __LINE__));\
  std::shared_ptr<Message> const newError = std::shared_ptr<Message>(new Message(L"Error Message", MessageType::ErrorMessage, data));\
  Engine::GetInstance()->ImmediateMessage(newError); \
}

// Used to send a popup message to the user
#define POPUP(str) \
{\
  std::shared_ptr<void> data(new PopUpMessageData(std::string(str)));\
  std::shared_ptr<Message> const newPopup = std::shared_ptr<Message>(new Message(L"PopUp Message", MessageType::PopUp, data));\
  Engine::GetInstance()->ImmediateMessage(newPopup); \
}

// Used to send a fatal error message to the systems if expression is true
#define FATAL_ERRORIF(exp, str) \
{\
  if(exp)\
    FATAL_ERROR(str) \
}

//////////////////////////////////////////////////////////////////////////////////////// BEGIN Ignored in Release mode
#ifdef _DEBUG

// Used to send a non fatal error messages to the systems
#define NONFATAL_ERROR(str) \
{\
  std::shared_ptr<void> data(new ErrorMessageData(std::string(str), false, __FUNCTION__, __FILE__, __LINE__));\
  std::shared_ptr<Message> const newError = std::shared_ptr<Message>(new Message(L"Error Message", MessageType::ErrorMessage, data)); \
  Engine::GetInstance()->ImmediateMessage(newError); \
}

// Used to send a debug message to the user
#define DEBUG_POPUP(str) \
{\
  POPUP(str) \
}

// Used to send a non fatal error messages under a certain condition
#define ERRORIF(exp, str) \
{\
  if(exp)\
    NONFATAL_ERROR(str) \
}

// Sends a non fatal error message if an expression is false
#define ASSERT(exp, str) \
{\
  if(!(exp))\
    NONFATAL_ERROR(str) \
}

// debug breakpoints
#if defined(WIN32)
#define DEBUGME() {if (IsDebuggerPresent()) DebugBreak();}
#else
#define DEBUGME() {(void)sizeof(int);}

#endif

//////////////////////////////////////////////////////////////////////////////////////// END Ignored in Release mode
#else 

#define DEBUG_POPUP(str) {(void)sizeof(str);}
#define NONFATAL_ERROR(str) {(void)sizeof(str);}
#define ERRORIF(expr, str) {(void)sizeof(expr); (void)sizeof(str);}
#define ASSERT(expr, str) {(void)sizeof(expr);}
#define DEBUGME() 

#endif 
//////////////////////////////////////////////////////////////////////////////////////// _DEBUG


#endif // !_Debug
