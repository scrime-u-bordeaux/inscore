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

#include <iostream>

#include "TimeEventAble.h"
#include "EventsAble.h"
#include "TInterval.h"
 
namespace interlude
{

//----------------------------------------------------------------------
void TimeEventAble::handleTimChange (rational from, rational to) const
{
	for (std::set<RationalInterval>::const_iterator i=fWatchList.begin(); i != fWatchList.end(); i++) {
		if (i->include(from) && !i->include(to)) {			// leaving the time interval
			send (fEventsHandler->getTimeMsgs (EventsAble::kTimeLeave, *i));
		}
		else if (!i->include(from) && i->include(to)) {		// entering the time interval
			send (fEventsHandler->getTimeMsgs (EventsAble::kTimeEnter, *i));
		}				
	}
}

//----------------------------------------------------------------------
void TimeEventAble::send (const std::vector<SEventMessage>& msgs) const
{
	for (unsigned int i=0; i<msgs.size(); i++)
		msgs[i]->send();
}

//----------------------------------------------------------------------
void TimeEventAble::watchTime(const RationalInterval& interval)	{ fWatchList.insert (interval); }
void TimeEventAble::clearTime()									{ fWatchList.clear(); }
void TimeEventAble::delTime(const RationalInterval& interval)	{ fWatchList.erase (interval); }

} // end namespoace
