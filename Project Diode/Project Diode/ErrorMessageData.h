/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    ErrorMessageData.h
  \author  John Salguero
  \date    June 22, 2023
  \brief
    This header file is used to declare the data class for the
    Error Message Class used to communicate an error event
*/
/********************************************************************/
#ifndef _ErrorMessageData
#define _ErrorMessageData

class ErrorMessageData {
public:
  //  Constructor
  ErrorMessageData(const std::string, bool, const char*, const char*, int);

  // Default Destructor for Message Base Class
  virtual ~ErrorMessageData() = default;

  // Getters
  const std::string GetErrorMessage();
  bool GetIsFatal();
  const char* GetFuncName();
  const char* GetSourceFile();
  int GetLineNum();

private:
  // The message to be shown with the error
  std::string m_ErrorMessage;
  // Whether or not the error is fatal
  bool m_IsFatal;
  // name of the function the error is in
  const char* m_FuncName;
  // name of the file the error is in
  const char* m_SourceFile;
  // the line number of the error
  int m_LineNum;
};


#endif
