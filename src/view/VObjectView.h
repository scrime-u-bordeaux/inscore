/*

  INScore Project

  Copyright (C) 2009,2011  Grame

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/


#ifndef __VObjectView__
#define __VObjectView__

#include <iostream>

#include "IObject.h"
#include "GraphicEffect.h"

//#include <QRect>

namespace inscore
{

/*!
\addtogroup ITLView 
@{
*/

//--------------------------------------------------------------------------
/**
*	\brief a graphic view of a IObject that uses a QGraphicsItem to render.
*/
class VObjectView
{
	public :
		virtual ~VObjectView()	{}

		virtual void updateView(IObject * object)			= 0;
		virtual void updateObjectSize( IObject * object )	= 0;
		virtual void setParentView (IObject * object)		= 0;
		virtual void setParentItem( VObjectView* master )	= 0;

		virtual void setEffect (GraphicEffect& effect)		= 0;
		virtual GraphicEffect getEffect () const			= 0;

		/// \brief Maps the IObject [-1,1] y coordinate to the referenceRect().
		virtual double relative2SceneY(float y) const						= 0;
		/// \brief Maps the IObject [-1,1] x coordinate to the referenceRect().
		virtual double relative2SceneX(float x) const						= 0;
		/// \brief Maps the IObject [0,2] width value to the corresponding referenceRect() value.
		virtual double relative2SceneWidth(float width) const				= 0;
		/// \brief Maps the IObject [0,2] height value to the corresponding referenceRect() value.
		virtual double relative2SceneHeight(float height) const				= 0;

		/// \brief Maps the referenceRect() width value to the corresponding [0,2] value.
		virtual double scene2RelativeWidth(float width) const				= 0;
		/// \brief Maps the referenceRect() height value to the corresponding [0,2] value.
		virtual double scene2RelativeHeight(float height) const				= 0;
		/// \brief Maps the referenceRect() x value to the corresponding [-1,1] value.
		virtual double scene2RelativeX(float x) const						= 0;
		/// \brief Maps the referenceRect() y value to the corresponding [-1,1] value.
		virtual double scene2RelativeY(float y) const						= 0;

		/// \brief updates the local mapping (do nothing at IObject level) 
		virtual void	updateLocalMapping (IObject* obj)	{}
		/// \brief initialize an object view (do nothing at IObject level)
		virtual void	initialize (IObject* obj)			{}

};

/*!@} */

} // end namespoace

#endif
