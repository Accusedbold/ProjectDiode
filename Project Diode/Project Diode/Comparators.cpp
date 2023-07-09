/******************************************************************/
/*!
	All content (C) John Salguero, all rights reserved.
	Reproduction or disclosure of this file or its contents without the
	prior written consent of John Salguero is prohibited.

	\file    Comparators.h
	\author  John Salguero
	\date    July 4, 2023
	\brief
		This cpp file defines the Comparators functors, which are
		a set of funtors used to order lists in useful ways
*/
/********************************************************************/
#include "stdafx.h"

bool RenderableComparator::operator()(std::shared_ptr<Renderable> const& obj1, std::shared_ptr<Renderable> const& obj2) const
{
	return obj1->GetModelID() > obj2->GetModelID();
}
