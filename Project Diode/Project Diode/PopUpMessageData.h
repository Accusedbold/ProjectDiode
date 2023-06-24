/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    PopUpMessageData.h
  \author  John Salguero
  \date    June 24, 2023
  \brief
    This header file is used to declare the data class for the
    Popup Message Class used to communicate a message to the user
*/
/********************************************************************/
#ifndef _PopupMessageData
#define _PopupMessageData

class PopUpMessageData {
public:
  //  Constructor
  PopUpMessageData(const std::string);

  // Default Destructor for Message Base Class
  virtual ~PopUpMessageData() = default;

  // Getters
  const std::string GetMessage();

private:
  // The message to be shown with the Popup
  std::string m_Message;
};


#endif
