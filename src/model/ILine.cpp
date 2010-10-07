/*

  INScore Project

  Copyright (C) 2009,2010  Grame

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

#include "ILine.h"
#include "IMessage.h"
#include "Updater.h"

using namespace std;

namespace interlude
{

const string ILine::kLineType("line");
//--------------------------------------------------------------------------
ILine::ILine( const std::string& name, IObject* parent ) : IShapeMap(name, parent), fView(0)
{ 
	fTypeString = kLineType;
	fGetMsgHandlerMap[""] = TGetParamMsgHandler< TFloatPoint >::create( getPoint() );
	
	fPenWidth = 1.0f;
}

//--------------------------------------------------------------------------
void ILine::accept (Updater* u)
{
	u->updateTo (SILine(this));
}

//--------------------------------------------------------------------------
void ILine::print (ostream& out) const
{
	IShapeMap::print (out);
	out << fPoint << endl;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus ILine::set (const IMessage* msg)	
{
	MsgHandler::msgStatus status = IObject::set(msg);
	if (status & (MsgHandler::kProcessed + MsgHandler::kProcessedNoChange)) return status; 

	if (msg->params().size() == 3) {
		const float err = -5555;
		float ax = msg->params()[1]->value<float>(err);
		float ay = msg->params()[2]->value<float>(err);

		if ( (ax != err) && (ay != err) )
		{
			setPoint( TFloatPoint(ax,ay) );
			status = MsgHandler::kProcessed;
			newData(true);
		}
		else status = MsgHandler::kProcessedNoChange;
	}
	else status = MsgHandler::kBadParameters;
	return status;
}

}
