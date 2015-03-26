/*

  INScore Project

  Copyright (C) 2015  Grame

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

#include "QtWebSocketController.h"

using namespace std;
namespace inscore
{

#ifdef WIN32
#include <windows.h>
# define _uwait(n)	Sleep(n)
#else
#include <unistd.h>
# define _uwait(n)	usleep(n * 1000);
#endif

//-------------------------------------------------------------------------------
QtWebSocketController::QtWebSocketController(const WebSocketInformer* infos)
	: fInfos(infos), fServer (0)
{}

QtWebSocketController::~QtWebSocketController()		{ stop(); delete fServer; }

//-------------------------------------------------------------------------------
bool QtWebSocketController::start (int /*port*/)
{
	stop();
	QThread::start();
	int timeout = 100;   // 100 mls timeout
	do {
		_uwait(10);
		timeout -= 10;
	} while (!running() || (timeout > 0));
	return running();
}

//-------------------------------------------------------------------------------
void QtWebSocketController::setFrequency(int frequency)	{ if (fServer) fServer->setFrequency(frequency); }
bool QtWebSocketController::running() const				{ return fServer ? fServer->isListening() : false; }

//-------------------------------------------------------------------------------
void QtWebSocketController::stop()
{
	if (isRunning()) {
		quit();
		wait();
		delete fServer;
		fServer = 0;
	}
}

//-------------------------------------------------------------------------------
int QtWebSocketController::clients() const
{
	return fServer ? fServer->getClients() : 0;
}

//-------------------------------------------------------------------------------
void QtWebSocketController::run()
{
	fServer = new QtWebSocketServer (fInfos->getFrequency(), fInfos->getView());
	if (fServer) {
		fServer->start(fInfos->getPort());
		exec();
	}
}

}