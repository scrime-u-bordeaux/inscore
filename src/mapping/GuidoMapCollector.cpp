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

#include "maptypes.h"
#include "ITLError.h"
#include "QGuidoGraphicsItem.h"

#include "GuidoMapCollector.h"

using namespace std;


namespace inscore
{

//----------------------------------------------------------------------
static inline rational guidodate2rational (const GuidoDate& d)		{ return rational (d.num, d.denom); }

//----------------------------------------------------------------------
void GuidoMapCollector::Graph2TimeMap( const FloatRect& box, const TimeSegment& dates, const GuidoElementInfos& infos )
{
	// Guido mapping filtering: the Guido map doesn't fit the Interlude mapping constraints and should be reworked.
	if (fFilter && !(*fFilter)(infos))	return;		// element is filtered by the filter

	RelativeTimeSegment tseg = relativeTimeSegment(dates);
	if ( tseg.empty() )	return;						// empty time segments are filtered

	GraphicSegment gseg = graphicSegment(box, fCurrentPageOrigin);
	if ( gseg.empty() )	return;						// empty graphic segments are filtered

	for (Time2GraphicMap::const_iterator i = fOutMap->begin(); i != fOutMap->end(); i++) {
		if ( tseg.intersect( i->first ) )
			return;									// intersecting segments are filtered
		if ( gseg.intersect( i->second ) )
			return;
	}
	(*fOutMap)[tseg] = gseg;
}

//----------------------------------------------------------------------
void GuidoMapCollector::process (Time2GraphicMap* outmap)
{
	fOutMap = outmap;
	if (!fItem || !fOutMap) return;

	for ( int page = fItem->firstVisiblePage() ; page <= fItem->lastVisiblePage() ; page++ ) {
		fCurrentPageOrigin = fItem->pageManager()->pagePos(page);
		float w = fItem->pageManager()->pageSize(page).width();
		float h = fItem->pageManager()->pageSize(page).height();
		GuidoGetMap( fItem->getGRHandler(), page, w, h, fSelector, *this );
	}
}

//----------------------------------------------------------------------
void GuidoStaffCollector::process (Time2GraphicMap* outmap)
{
	if (!fItem || !outmap) return;

	for ( int page = fItem->firstVisiblePage() ; page <= fItem->lastVisiblePage() ; page++ ) {
		fCurrentPageOrigin = fItem->pageManager()->pagePos(page);
		float w = fItem->pageManager()->pageSize(page).width();
		float h = fItem->pageManager()->pageSize(page).height();
		::Time2GraphicMap map;
		GuidoErrCode err = GuidoGetStaffMap( fItem->getGRHandler(), page, w, h, fStaffNum, map );
		if (err == guidoNoErr) {
			for (::Time2GraphicMap::const_iterator i=map.begin(); i!=map.end(); i++) {
				RelativeTimeSegment ts (guidodate2rational(i->first.first), guidodate2rational(i->first.second));
				GraphicSegment gs ( fCurrentPageOrigin.x()+i->second.left, fCurrentPageOrigin.y()+i->second.top, 
									fCurrentPageOrigin.x()+i->second.right, fCurrentPageOrigin.y()+i->second.bottom);
				(*outmap)[ts] = gs;
			}
		}
		else {
			ITLErr << "error getting staff " << fStaffNum << " map on page " << page << ": " << GuidoGetErrorString(err) << ITLEndl;
			break;
		}
	}
}



//----------------------------------------------------------------------
void GuidoSystemCollector::process (Time2GraphicMap* outmap)
{
	if (!fItem || !outmap) return;

	if (fFlatMode) processNoDiv (outmap);
	else for ( int page = fItem->firstVisiblePage() ; page <= fItem->lastVisiblePage() ; page++ ) {
		fCurrentPageOrigin = fItem->pageManager()->pagePos(page);
		float w = fItem->pageManager()->pageSize(page).width();
		float h = fItem->pageManager()->pageSize(page).height();
		::Time2GraphicMap map;
		GuidoErrCode err = GuidoGetSystemMap( fItem->getGRHandler(), page, w, h, map );
		if (err == guidoNoErr) {
			for (::Time2GraphicMap::const_iterator i=map.begin(); i!=map.end(); i++) {
				RelativeTimeSegment ts (guidodate2rational(i->first.first), guidodate2rational(i->first.second));
				GraphicSegment gs ( fCurrentPageOrigin.x()+i->second.left, fCurrentPageOrigin.y()+i->second.top, 
									fCurrentPageOrigin.x()+i->second.right, fCurrentPageOrigin.y()+i->second.bottom);
				(*outmap)[ts] = gs;
			}
		}
		else {
			ITLErr << "error getting system map on page " << page << ": " << GuidoGetErrorString(err) << ITLEndl;
			break;
		}
	}
}

//----------------------------------------------------------------------
// computes the system map without subdivision
//----------------------------------------------------------------------
void GuidoSystemCollector::processNoDiv (Time2GraphicMap* outmap)
{
	int M,m,s;
	GuidoGetVersionNums (&M, &m, &s);
	if (GuidoCheckVersionNums (1, 4, 2) != guidoNoErr)
		ITLErr << "correct system map requires GUIDOEngine version 1.4.2 or greater - current version is "
				<< M << "." << m << "." << s << ITLEndl;

	GuidoMapCollector systemCollector(fItem, kGuidoSystem);
	GuidoMapCollector slicesCollector(fItem, kGuidoSystemSlice);

	Time2GraphicMap systemMap, slicesMap;
	systemCollector.process (&systemMap);
	slicesCollector.process(&slicesMap);

	Time2GraphicMap::const_iterator slicesIter = slicesMap.begin();
	Time2GraphicMap::const_iterator systemIter = systemMap.begin();
	
	while (systemIter != systemMap.end()) {
		if (slicesIter == slicesMap.end()) {
			cerr << "unexpected slices segmentation end while collecting system map" << endl;
			break;
		}

		GraphicSegment gs = systemIter->second;
		FloatInterval slicexi = slicesIter->second.xinterval();
		GraphicSegment adjusted (FloatInterval(slicexi.first(), gs.xinterval().second()), gs.yinterval());
		(*outmap)[systemIter->first] = adjusted;

		// skip the remaining slices until the next line
		float prevx = slicexi.first();
		float sysy = systemIter->second.yinterval().first();
		while (slicesIter != slicesMap.end()) {
			float x = slicesIter->second.xinterval().first();
			float y = slicesIter->second.yinterval().first();
			if ((x < prevx) || (y < sysy)) break;			
			prevx = x;
			slicesIter++;
		}
		systemIter++;
	}
}

} // end namespoace
