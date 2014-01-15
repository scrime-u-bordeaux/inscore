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


#include "ISceneSync.h"
#include "IMessage.h"
#include "Updater.h"

using namespace std;

namespace inscore
{

const string ISceneSync::fTypeString = "syncnode";

//--------------------------------------------------------------------------
ISceneSync::ISceneSync(IObject * parent) : IVNode("sync", parent)
{
	fMsgHandlerMap["*"]	= TMethodMsgHandler<ISceneSync>::create(this, &ISceneSync::syncMsg);
	fMsgHandlerMap[kwatch_GetSetMethod]		= 0L;
	fMsgHandlerMap[kwatchplus_SetMethod]	= 0L;
}

//--------------------------------------------------------------------------
void ISceneSync::accept (Updater* u)
{
	u->updateTo (SISceneSync(this));
}

//--------------------------------------------------------------------------
SMaster ISceneSync::getMaster(SIObject o) const
{
	ISync::const_iterator found = fSync.find(o);
	return (found != fSync.end()) ? found->second : 0;
}

//--------------------------------------------------------------------------
std::vector<SMaster> ISceneSync::getMasters(SIObject o) const
{
    std::pair<ISync::const_iterator,ISync::const_iterator> range = fSync.equal_range(o);
    std::vector<SMaster> masters;
    for(ISync::const_iterator it = range.first; it !=range.second; it++)
        masters.push_back(it->second);
    return masters;
}

//--------------------------------------------------------------------------
void ISceneSync::sort (IObject::subnodes& nodes)
{
	if (fSync.modified()) {
//		fSync.topologicalSort (nodes);
		fSync.modified(false);
	}
}

//--------------------------------------------------------------------------
static SIMessage buildSyncMsg (const string& address, SIObject o, const SMaster master)
{
	string target = o->name();
	if (master) {
		const string& smap = master->getSlaveMapName();
		if (smap.size()) target += ":" + smap;
		SIMessage msg = IMessage::create(address);
		if (msg) {
			*msg << target;
			*msg << *master;
		}
		return msg;
	}
	return IMessage::create(address, target);
}

//--------------------------------------------------------------------------
SIMessageList ISceneSync::getMsgs (const IMessage* msg) const
{
	SIMessageList outMsgs = IObject::getMsgs (msg);
	if (outMsgs->list().size()) return outMsgs;

	const string& address = getOSCAddress();
	if (msg->size() == 1) {
		string who = msg->param(0)->value<string>("-");
		string name, mapname;
		name2mapName (who, name, mapname);
		subnodes list;
		if (fParent->find(name, list)) {
			for (subnodes::const_iterator i = list.begin(); i != list.end(); i++) {				
				SIMessage msg = buildSyncMsg (address, *i,  getMaster(*i));
				outMsgs->list().push_back (msg);
			}
		}
	}
	else if (msg->size() == 0) {
		for (ISync::const_iterator i = fSync.begin(); i != fSync.end(); i++) {
			SIMessage msg = buildSyncMsg (address, i->first,  i->second);
			outMsgs->list().push_back (msg);
		}
	}
	return outMsgs;	
}

//--------------------------------------------------------------------------
// propagates modification state from masters to slaves
//--------------------------------------------------------------------------
void ISceneSync::ptask ()
{
	for (ISync::iterator i = fSync.begin(); i != fSync.end(); i++) {
		const SIObject& master = i->second->getMaster();
		if (master->getState() & kModified)
			i->first->setState(kMasterModified);
	}
}

//--------------------------------------------------------------------------
// message handlers
//--------------------------------------------------------------------------
#define MAP_NAME_SEPARATOR ':'
//--------------------------------------------------------------------------
bool ISceneSync::name2mapName (const string& str, string& name, string& map) const
{
	size_t sepPos = str.find_first_of(MAP_NAME_SEPARATOR);
	if ( sepPos != string::npos ) {
		name = str.substr(0, sepPos);
		map = str.substr( sepPos+1, name.length() + 1);		
		return true;
	}
	name = str;
	map = "";
	return false;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus ISceneSync::syncMsg (const std::string& slave)
{
	subnodes so;
	if (!fParent->find(slave, so)) return MsgHandler::kBadParameters;		// no target objects to be slave
	for (subnodes::iterator i = so.begin(); i != so.end(); i++) {
		delsync(*i);
		(*i)->UseGraphic2GraphicMapping (false);
		(*i)->setState (kMasterModified);
	}
	return MsgHandler::kProcessed;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus ISceneSync::syncMsg (const std::string& slave, const std::string& slaveMap, 
									const std::string& master, const std::string& masterMap,
									Master::StretchType stretch, Master::SyncType syncmode, Master::VAlignType valign)
{
	subnodes so;
	if (!fParent->find(slave, so)) return MsgHandler::kBadParameters;		// no target objects to be slave
	subnodes mos;
	if (!fParent->exactfind(master, mos)) return MsgHandler::kBadParameters;

	for (unsigned int j = 0; j < mos.size(); j++) {
		SIObject mo = mos[j];
		for (subnodes::iterator i = so.begin(); i != so.end(); i++) {
			SMaster m = Master::create(mo, valign, stretch, syncmode, masterMap , slaveMap );
			sync(*i, m);
			(*i)->setState (kMasterModified);
		}
	}
	return MsgHandler::kProcessed;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus ISceneSync::syncMsg (const IMessage* msg)	
{
	int n = msg->size();
	string slave, slaveMapName;
	int nextindex = 0;
	if (msg->message().size()) {
		name2mapName (msg->message(), slave, slaveMapName);
		if (!n) return syncMsg (slave);
	}
	else if (n) {
		name2mapName (msg->param(0)->value<string>(""), slave, slaveMapName);
		if (n > 1) nextindex = 1;
		else return syncMsg (slave);
	}
	else return MsgHandler::kBadParameters;
	
	string master, masterMapName;
	name2mapName (msg->param(nextindex)->value<string>(""), master, masterMapName);
	Master::VAlignType align = Master::kDefaultSyncAlign;
	Master::StretchType stretch = Master::kDefaultStretch;
	Master::SyncType syncType = Master::kDefaultSync;
	for (int i=nextindex+1; i<n; i++) {
		string mode = msg->param(i)->value<string>("");
		Master::VAlignType val = Master::string2syncalign(mode);
		if (val != Master::kUnknown) align = val;
		else {
			Master::StretchType sval = Master::string2stretchmode(mode);
			if (sval != Master::kStretchUnknown) stretch = sval;
			else {
				Master::SyncType mval = Master::string2synctype(mode);
				if (mval != Master::kTypeUnknown) syncType = mval;
			}
		}
	}
	return syncMsg (slave, slaveMapName, master, masterMapName, stretch, syncType, align);
}

//--------------------------------------------------------------------------
// the 'get' to retrieve all the objects parameters
SIMessageList ISceneSync::getAllParams() const
{
	SIMessageList outMsgs = 	IObject::getAllParams();
	ISync::const_iterator i = fSync.begin();
	// and distribute the message to synced nodes
	while (i != fSync.end()) {
		const SIObject& elt = i->first;
		SIMessage msg = IMessage::create(getOSCAddress(), "get");
		msg->add (elt->name());
		outMsgs->list().push_back (getMsgs(msg)->list());
		i++;
	}
	return outMsgs;
}

//--------------------------------------------------------------------------
void ISceneSync::print (ostream& out) const
{
	out << "  nodes synchronization :" << endl << fSync;	
}

}
