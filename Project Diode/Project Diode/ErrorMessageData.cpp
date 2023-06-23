/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    ErrorMessageData.h
  \author  John Salguero
  \date    June 22, 2023
  \brief
    This cpp file is used to declare the data class for the
    Error Message Class used to communicate an error event
*/
/********************************************************************/

#include "stdafx.h"

/******************************************************************************/
/*!
            ErrorMessage

\author     John Salguero

\brief      Constructor for the error message sent to the systems

\param      errorMessage
            The message given to the user

\param      isFatal
            Whether this is a Fatal error or not

\param      funcName
            The name of the function the error is found in

\param      sourceFile
            The file the error is found in

\param      lineNum
            The line number the error is found on
*/
/******************************************************************************/
ErrorMessageData::ErrorMessageData(const std::string errorMessage, bool isFatal, const char* funcName, const char* sourceFile, int lineNum) :
	 m_ErrorMessage(errorMessage), m_IsFatal(isFatal), m_FuncName(funcName), m_SourceFile(sourceFile), m_LineNum(lineNum)
{

}


/******************************************************************************/
/*!
           GetErrorMessage

\author    John Salguero

\brief     Returns the error message from the error message

\return    m_ErrorMessage
           The message shown to the user

*/
/******************************************************************************/
const std::string ErrorMessageData::GetErrorMessage()
{
  return m_ErrorMessage;
}

/******************************************************************************/
/*!
           GetIsFatal

\author    John Salguero

\brief     Returns whether or not the error is fatal

\return    m_IsFatal
           Whether or not the error is fatal

*/
/******************************************************************************/
bool ErrorMessageData::GetIsFatal()
{
  return m_IsFatal;
}

/******************************************************************************/
/*!
            GetFuncName

\author     John Salguero

\brief      Returns the function name the error is found in

\return     m_FuncName
            The function name the error is found in

*/
/******************************************************************************/
const char* ErrorMessageData::GetFuncName()
{
  return m_FuncName;
}

/******************************************************************************/
/*!
            GetSourceFile

\author     John Salguero

\brief       Returns the source file the error is found in

\return     m_FuncName
            The source file the error is found in

*/
/******************************************************************************/
const char* ErrorMessageData::GetSourceFile()
{
  return m_SourceFile;
}

/******************************************************************************/
/*!
             GetLineNum

\author      John Salguero

\brief       Returns the line number the error is found in

\return      mFuncName
             The line number the error is found in

*/
/******************************************************************************/
int ErrorMessageData::GetLineNum()
{
  return m_LineNum;
}
