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

#include "TComposition.h"
#include "VGraphicsItemView.h"
#include "maptypes.h"
#include "TSegment.h"

#include <QtDebug>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include "QStretchTilerItem.h"

#include "IObject.h"
#include "TMessageEvaluator.h"
#include "VExport.h"

#define NB_OF_COLORS 12

using namespace libmapping;

namespace inscore
{

// Array of colors of mapping debug items.
QColor brushColors[NB_OF_COLORS] = {	Qt::darkBlue , Qt::darkRed , Qt::darkYellow , Qt::darkCyan , Qt::darkGreen , Qt::darkMagenta , 
										Qt::blue , Qt::red , Qt::yellow , Qt::cyan , Qt::green , Qt::magenta };

//------------------------------------------------------------------------------------------------------------
//												Member functions
//------------------------------------------------------------------------------------------------------------
VGraphicsItemView::VGraphicsItemView( QGraphicsScene * scene , QGraphicsItem * item )
{
	fItem = item;
	scene->addItem( item );
    fScene = scene;
    fParent = 0;
    fNbMasters = 0;
	fBrushColorStartIndex = 0;
}

//------------------------------------------------------------------------------------------------------------
VGraphicsItemView::~VGraphicsItemView()
{
	deleteDebugItems();

	QList<QGraphicsItem*> children = fItem->childItems();	// Break all links with children
	for (int i = 0 ; i < children.size() ; i++ )
		children[i]->setParentItem(0);
    
    for(std::map<SMaster,QStretchTilerItem*>::iterator it = fTilerItems.begin(); it != fTilerItems.end(); it++)
    {
        if(it->second->scene())
            fScene->removeItem(it->second);
    }
    
    for(std::map<SMaster, QStretchTilerItem*>::iterator i = fTilerItems.begin(); i != fTilerItems.end(); i++)
    {
        delete i->second;
    }
    
    fTilerItems.clear();
    
    if(fItem->scene())
        fItem->scene()->removeItem( fItem );					// Remove the QGraphicsItem from the scene.

	delete fItem;	
}

//------------------------------------------------------------------------------------------------------------
void VGraphicsItemView::deleteDebugItems()
{
	for ( int i = 0 ; i < fDebugItems.size() ; i++ )		// Delete object's debug items
		delete fDebugItems[i];
		
	fDebugItems.clear();
}

//------------------------------------------------------------------------------------------------------------
// Map debug: parse all the object's mapping and add colored rectangles to show the mapped zones.
//------------------------------------------------------------------------------------------------------------
void VGraphicsItemView::drawMapping(IObject* o)
{	
	//if (fIsStretchOn) return;		// don't know where to draw

	int count = 0;
	// For each time<->graphic mapping.
	for (TMapable::const_iterator i = o->namedMappings().begin() ; i != o->namedMappings().end() ; i++, count++ )
	{
		QColor mapColor1 = brushColors[(count++ + fBrushColorStartIndex)%NB_OF_COLORS];
		QColor mapColor2 = brushColors[(count + fBrushColorStartIndex)%NB_OF_COLORS];
		mapColor1.setAlpha (90);
		mapColor2.setAlpha (90);
		
		float z = 0;
		int colorindex = 0;
		const RelativeTime2GraphicRelation& rt2g = i->second->direct();
		// For each time segment in the mapping, draw its corresponding GraphicSegment.
		for (RelativeTime2GraphicRelation::const_iterator j = rt2g.begin(); j != rt2g.end() ; j++ )
		{
			RelativeTimeSegment timeSegment = j->first;
			QString timeString = ((std::string)timeSegment.interval()).c_str();
			const std::set<GraphicSegment>& related = j->second;
			// For each master segment corresponding to the slave segment.
			for ( std::set<GraphicSegment>::const_iterator j=related.begin() ; j != related.end(); j++ )
			{
				const QColor& color = (colorindex & 1) ? mapColor2 : mapColor1;
				QRectF qtRect = iObject2QGraphicsItem( *j );
				QGraphicsRectItem * mappingSegment = new QGraphicsRectItem( qtRect , item() );
				mappingSegment->setPen( QPen( color ) );
				mappingSegment->setBrush( QBrush( color) );
				mappingSegment->setZValue( ++z );
				fDebugItems << mappingSegment;

				// Add dates
				QGraphicsTextItem * textItem = new QGraphicsTextItem( timeString , mappingSegment );
				textItem->setDefaultTextColor( Qt::black );
				float scale = 4.0f;
				textItem->setScale(1.0f/scale);
				if (colorindex & 1)
					textItem->setPos( qtRect.x() , qtRect.y() + qtRect.height()); // + textItem->boundingRect().height()/scale );
				else
					textItem->setPos( qtRect.x() , qtRect.y() - textItem->boundingRect().height()/scale );
				textItem->setZValue(z);
			}
			colorindex++;
		}
	}
}

//------------------------------------------------------------------------------------------------------------
// Debug graphic feedback : displays the bounding rectangle and the object name
//------------------------------------------------------------------------------------------------------------
void VGraphicsItemView::drawNameAndBBox(IObject* o)
{	
	//if (fIsStretchOn) return;		// don't know where to draw

//	TFloatRect boundingRect = o->getBoundingRect();
//	QRectF boundingRectQt( 
//		relative2SceneX(boundingRect.pos().x()) , 
//		relative2SceneY( boundingRect.pos().y() ) , 
//		relative2SceneWidth( boundingRect.size().width() ), 
//		relative2SceneHeight( boundingRect.size().height() )
//	);

	// Add an item for the bounding rect
	QRectF bboxRectQt = fItem->boundingRect();

	QGraphicsRectItem * boundingRectItem = new QGraphicsRectItem( bboxRectQt );
	boundingRectItem->setPen( QPen( QBrush(Qt::red) , 0 , Qt::DashLine) );
	boundingRectItem->setZValue( item()->zValue() + 0.1f );
	boundingRectItem->setParentItem(item());
//	item()->scene()->addItem( boundingRectItem );
	fDebugItems << boundingRectItem;
	
	// Add an item for the name.
	QGraphicsTextItem * textItem = new QGraphicsTextItem( o->name().c_str() , boundingRectItem );
	textItem->setDefaultTextColor( Qt::red );
//	float scale = 1.0f;
//	textItem->scale(1.0f/scale,1.0f/scale);
//	if (fIsStretchOn)
//		textItem->setPos( boundingRectQt.x() , boundingRectQt.y() - textItem->boundingRect().height()/scale );
//	else
		textItem->setPos( bboxRectQt.x() , bboxRectQt.y() - textItem->boundingRect().height() );
}

//------------------------------------------------------------------------------------------------------------
/*void VGraphicsItemView::setParentView (IObject * object) // not used ...
{
	VObjectView * parentView = 0;
	if (object) {
        const SIObject parent = object->getParent();
        const Master* master = parent ? parent->getMaster(object) : 0;
    
//		const SIScene scene = object->getScene();
//		const Master* master = scene ? scene->getMaster(object) : 0;

		if (master && !master->getMaster()->getDeleted()){
			parentView = master->getMaster()->getView();
        }
	}
	setParentItem( parentView );
}*/

//------------------------------------------------------------------------------------------------------------
void VGraphicsItemView::updateObjectSize(IObject* o)
{	
	o->setWidth( getIObjectWidth() );
	o->setHeight( getIObjectHeight() );
}

//------------------------------------------------------------------------------------------------------------
void VGraphicsItemView::updateTransform(IObject* o)
{
//	fItem->resetTransform();	// Resets the transform (scale and rotation) before setting the new values.
	QTransform matrix;
	TFloatSize shear = o->getShear();
	if (shear)
		matrix.shear(shear.width(), shear.height());
	if (o->getRotateX())
		matrix.rotate(o->getRotateX(), Qt::XAxis);
	if (o->getRotateY())
		matrix.rotate(o->getRotateY(), Qt::YAxis);
	if (o->getRotateZ())
		matrix.rotate(o->getRotateZ(), Qt::ZAxis);
	fItem->setTransform (matrix);	
}

//------------------------------------------------------------------------------------------------------------
void VGraphicsItemView::updateItemHStretch(QStretchTilerItem * item, const SGraphic2GraphicMapping& slave2Master)
{
    item->setStretch(true);
    item->setRect(item->parentItem() ? item->parentItem()->boundingRect():item->scene()->sceneRect());
    float x = item->boundingRect().center().x();
    float y = item->boundingRect().center().y();
    item->setPos( x, y);
    
    item->resetTransform();
    item->setTransform(QTransform::fromTranslate(-x, -y), true);
    Graphic2GraphicRelation::const_iterator iter;
    for ( iter = slave2Master->direct().begin() ; iter != slave2Master->direct().end() ; iter++ )	// For each slave segment.
    {
        if ( !iter->first.size() )	// Skip empty segments.
            continue;

        QRectF slaveSourceRect = iObject2QGraphicsItem( iter->first, item->boundingRect() );
			
        const std::set<GraphicSegment>& related = iter->second;
        // For each master segment corresponding to the slave segment.
        for ( std::set<GraphicSegment>::const_iterator i=related.begin() ; i != related.end(); i++ )
        {
            if ( !i->size() )	// Skip empty segments.
                continue;

            QRectF masterDestRect = iObject2QGraphicsItem( *i, item->parentItem()->boundingRect() );
            item->addSegment( slaveSourceRect , masterDestRect );
        }
    }
}

//------------------------------------------------------------------------------------------------------------
void VGraphicsItemView::updateItemNoStretch(QStretchTilerItem* item, IObject* o, SMaster master)
{
    item->setStretch(false);
    
    double width = relative2SceneWidth(o->getSyncWidth(master->getMaster()->name()), item);
    double height = relative2SceneHeight(o->getSyncHeight(master->getMaster()->name()), item);
    
    double x = relative2SceneX( o->getSyncPos(master->getMaster()->name()).x(), item );
    double y = relative2SceneY( o->getSyncPos(master->getMaster()->name()).y(), item );
    
    item->setRect(QRectF(0,0,width,height));
    updateGeometry(item, o, x, y, 1.f);
}

//------------------------------------------------------------------------------------------------------------
void VGraphicsItemView::updateGeometry(QGraphicsItem* item, IObject* o, float x, float y, float scale)
{
    //	Sets the item position in the QGraphicsScene, using 'relative coordinate -> QGraphicsScene coordinate'
    //	mapping functions.
    item->setPos(x, y);
    item->resetTransform();	// Resets the transform (scale and rotation) before setting the new values.
    updateTransform (o);
    QRectF bbrect = item->boundingRect();
    double xo = bbrect.width()  * (o->getXOrigin() + 1) * scale / 2;
    double yo = bbrect.height() * (o->getYOrigin() + 1) * scale / 2;
    item->setTransform(QTransform::fromTranslate(-xo, -yo), true);
}

//------------------------------------------------------------------------------------------------------------
void VGraphicsItemView::updateItem(QGraphicsItem* item, IObject* o)
{
    // Visibility
    item->setVisible(  o->getVisible() );

    // Z order. A negative 'z' value puts the object behind its parent - if it has one.
    item->setFlag( QGraphicsItem::ItemStacksBehindParent , (o->getZOrder() < 0) );
    item->setZValue(  o->getZOrder() );
}

//------------------------------------------------------------------------------------------------------------
void VGraphicsItemView::updateView(IObject* o)
{
    std::vector<SMaster> masters = o->getParent()? o->getParent()->getMasters(o) : o->getScene()->getMasters(o);
    
    setSlave(masters);

	// slave mode: setup and use of fTilerItem
    for(std::map<SMaster, QStretchTilerItem*>::iterator i = fTilerItems.begin(); i != fTilerItems.end(); i++)
    {
        SMaster master = i->first;
        QStretchTilerItem * fTilerItem = fTilerItems.find(master)->second;
        fTilerItem->clearSegments();
            
        fTilerItem->setOpacity (o->getA() / 255.f);
        
        const SGraphic2GraphicMapping& slave2Master = o->getSlave2MasterMapping(master->getMaster()->name());
        bool isHStretch =  o->UseGraphic2GraphicMapping(master->getMaster()->name());
            
        if(slave2Master && isHStretch)
        {
            updateItemHStretch(fTilerItem, slave2Master);
        }
        else
        {
            updateItemNoStretch(fTilerItem, o, master);
        }
        updateItem(fTilerItem, o);
        fTilerItem->update();
    }
    // the item is not slaved
	if(fTilerItems.empty())
	{
        fItem->setScale(  o->getScale() );
	    updateGeometry(fItem, o, relative2SceneX(o->getXPos()), relative2SceneY(o->getYPos()), o->getScale());
        updateItem(fItem, o);
    }


	//Exports the item if necessary.
	if ( o->getExportFlag().length() ) {
		VExport::exportItem( item() , o->getExportFlag().c_str() ,  o->getScale() ,  o->getScale(), o->getDrawChildren() );
		const IMessageList*	msgs = o->getMessages(EventsAble::kExport);
		if (msgs) {
			MouseLocation mouse (0, 0, 0, 0, 0, 0);
			EventContext env(mouse, libmapping::rational(0,1), o);
			TMessageEvaluator me;
			SIMessageList outmsgs = me.eval (msgs, env);
			if (outmsgs && outmsgs->list().size()) outmsgs->send();
		}
		
	}

	//	Debug mapping mode:
	//		- erase mapping QGraphicsRectItem anyways
	//		- create new mapping QGraphicsRectItems if "Debug Mapping Mode" is on.
	deleteDebugItems();

	// ----------------------------------------------------------------------------------------------
	// Map debug: parse all the object's mapping and add colored rectangles to show the mapped zones.
	if ( o->mapDebug() ) drawMapping (o);
	// ----------------------------------------------------------------------------------------------
	// Debug graphic feedback : displays the bounding rectangle and the object name
	if ( o->nameDebug() ) drawNameAndBBox (o);
    
}

//------------------------------------------------------------------------------------------------------------
// check if automatic mapping (build from object duration) needs to be refreshed
//------------------------------------------------------------------------------------------------------------
static bool checkAutoRefresh (IObject* object, const RelativeTime2GraphicRelation& rel)
{
	return object->fAutoMap && object->durationModified();
}

//------------------------------------------------------------------------------------------------------------
void VGraphicsItemView::buildDefaultMapping (IObject* object)
{
//	if ((object->namedMappings().size() == 1) && ()) return;  // no need to build the default mapping
	
	const SRelativeTime2GraphicMapping& map = object->getMapping("");
	// Check if the un-named mapping exists or if it needs to be refreshed. 
	if ( !map ||  checkAutoRefresh(object, map->direct()))	
	{	
		// If not, build a default mapping : the current [0 ; duration[ <-> the whole graphic space of the object.
		RelativeTimeSegment wholeTimeSegment( rational(0,1) , object->getDuration() );
		GraphicSegment		wholeGraphicSegment( -1 , -1 , 1 , 1 );
		
		SRelativeTime2GraphicMapping t2g_mapping = TMapping<rational,1,float,2>::create();
		t2g_mapping->add ( wholeTimeSegment , wholeGraphicSegment );
		object->setMapping( "" , t2g_mapping);
		object->fAutoMap = true;
		object->localMapModified(true);
	}
}

//------------------------------------------------------------------------------------------------------------
QStretchTilerItem* VGraphicsItemView::buildTiler()
{
    return new QStretchTilerItem( fItem );
}

//------------------------------------------------------------------------------------------------------------
void VGraphicsItemView::itemChanged()
{
    for(std::map<SMaster, QStretchTilerItem*>::iterator it = fTilerItems.begin(); it != fTilerItems.end(); it++)
    {
        it->second->needUpdate(true);
    }
}

//------------------------------------------------------------------------------------------------------------
void VGraphicsItemView::findNewSync(SMaster master)
{
    std::map<SMaster, QStretchTilerItem*>::iterator it = fTilerItems.find(master);
    QStretchTilerItem * fTilerItem;
    if(it == fTilerItems.end())
    {
        fTilerItem = buildTiler();
        VGraphicsItemView * masterView = dynamic_cast<VGraphicsItemView*>(master->getMaster()->getView());
        fTilerItem->setParentItem(masterView->item());
        fTilerItems.insert(std::pair<SMaster, QStretchTilerItem*>(master,fTilerItem));
    }
}

//------------------------------------------------------------------------------------------------------------
void VGraphicsItemView::findObsoleteSync(std::vector<SMaster> masters)
{
    std::map<SMaster, QStretchTilerItem*>::iterator it;
    for(it = fTilerItems.begin(); it != fTilerItems.end(); it++)
    {
        if(std::find(masters.begin(), masters.end(), it->first) == masters.end())
        {
            if(it->second->scene())
                fScene->removeItem(it->second);
            else
                it->second->setParentItem(0);
            fTilerItems.erase(it);
        }
    }
}

//------------------------------------------------------------------------------------------------------------
void VGraphicsItemView::setSlave( std::vector<SMaster> masters )
{
    if(fNbMasters == masters.size()) return; //there is no master-slave relation to add or remove
    
	for(int i = 0; i < masters.size(); i++)    // we first look for new masters, in order to add new representation
    {
        SMaster master = masters[i];
        findNewSync(master);
    }
    
    findObsoleteSync(masters); // Then we check if some representation could be obsolete (master/slave relation deleted)
    
    if(!fNbMasters)    // this is the first master added, so we have to remove the classic fItem and switch to the slaved verison
    {
        if(fItem->scene())
            fScene->removeItem(fItem);
    }
    fNbMasters = masters.size(); // finally we update the number of masters
}

//------------------------------------------------------------------------------------------------------------
//											Conversion methods
//------------------------------------------------------------------------------------------------------------
QRectF VGraphicsItemView::referenceRect(QGraphicsItem * specItem) const
{
    if(specItem)
        return specItem->parentItem() ? specItem->parentItem()->boundingRect() : fScene->sceneRect();
    else
        return fParent ? fParent->boundingRect() : fScene->sceneRect();
}

//------------------------------------------------------------------------------------------------------------
double VGraphicsItemView::relative2SceneX(float x, QGraphicsItem * specItem) const
{
	const QRectF& refRect = referenceRect(specItem);
	// + 1 parce que l'espace Qt va de 0->... et interlude de -1 à ...
	return (( x + 1 ) * refRect.width()) / 2.0f + refRect.x();
}

//------------------------------------------------------------------------------------------------------------
double VGraphicsItemView::relative2SceneY(float y, QGraphicsItem * specItem) const
{
	const QRectF& refRect = referenceRect(specItem);
	return (( y + 1 ) *  refRect.height()) / 2.0f  + refRect.y();
}

//--------------------------------------------------------------------------
double VGraphicsItemView::relative2SceneWidth(float width, QGraphicsItem * specItem) const
{
	return (referenceRect(specItem).width() * width)/2.0f;
}

//--------------------------------------------------------------------------
double VGraphicsItemView::relative2SceneHeight(float height, QGraphicsItem * specItem) const
{
	return (referenceRect(specItem).height() * height)/2.0f;
}

//--------------------------------------------------------------------------
//QRectF VGraphicsItemView::relative2SceneRect( const TFloatRect& rect  ) const
//{
//	QPointF a( relative2SceneX(rect.x()) , relative2SceneY(rect.y()) ); 
//	QPointF b( relative2SceneX(rect.right()) , relative2SceneY(rect.bottom()) );
//	return QRectF( a.x() , a.y() , b.x() - a.x() , b.y() - a.y() );
//}

//--------------------------------------------------------------------------
double VGraphicsItemView::scene2RelativeWidth(float width, QGraphicsItem * specItem) const
{
	return 2.0f * width / referenceRect(specItem).width();
}

//--------------------------------------------------------------------------
double VGraphicsItemView::scene2RelativeHeight(float height, QGraphicsItem * specItem) const
{
	return 2.0f * height / referenceRect(specItem).height();
}

//------------------------------------------------------------------------------------------------------------
double VGraphicsItemView::scene2RelativeX(float x, QGraphicsItem * specItem) const
{
	const QRectF& refRect = referenceRect(specItem);
	return ( x - refRect.x() ) / ( refRect.width() / 2.0f ) - 1 ;
}

//------------------------------------------------------------------------------------------------------------
double VGraphicsItemView::scene2RelativeY(float y, QGraphicsItem * specItem) const
{
	const QRectF& refRect = referenceRect(specItem);
	return ( y - refRect.y() ) / ( refRect.height() / 2.0f ) - 1 ;
}

//------------------------------------------------------------------------------------------------------------
TFloatPoint VGraphicsItemView::qGraphicsItem2IObject(const QPointF& point) const
{
	return qGraphicsItem2IObject( point , item()->boundingRect() );
}

//------------------------------------------------------------------------------------------------------------
TFloatPoint VGraphicsItemView::qGraphicsItem2IObject(const QPointF& point, const QRectF& rect) const
{
	double x = (point.x() - rect.x()) / (rect.width()/2.0f) - 1;
	double y = (point.y() - rect.y()) / (rect.height()/2.0f) - 1;
	return TFloatPoint(x,y);
}

//------------------------------------------------------------------------------------------------------------
QPointF VGraphicsItemView::iObject2QGraphicsItem(const TFloatPoint& point) const
{
	return iObject2QGraphicsItem(point, item()->boundingRect());
}

//------------------------------------------------------------------------------------------------------------
QRectF VGraphicsItemView::iObject2QGraphicsItem(const TFloatRect& rect) const
{
	return iObject2QGraphicsItem(rect, item()->boundingRect());
}

//------------------------------------------------------------------------------------------------------------
QRectF VGraphicsItemView::iObject2QGraphicsItem(const GraphicSegment& s) const
{
	TFloatRect r ( TFloatPoint(s.left(), s.top()), TFloatPoint(s.right(), s.bottom()) );
	return iObject2QGraphicsItem( r );
}

//------------------------------------------------------------------------------------------------------------
QPointF VGraphicsItemView::iObject2QGraphicsItem(const TFloatPoint& point, const QRectF& qrect) const
{
//	double x = ( point.x() + 1 ) * ( qrect.width() / 2.0f ) + qrect.x();
//	double y = ( point.y() + 1 ) * ( qrect.height() / 2.0f ) + qrect.y();
	double x = (( point.x() + 1 ) * qrect.width())  / 2.0f + qrect.x();
	double y = (( point.y() + 1 ) * qrect.height()) / 2.0f + qrect.y();
	return QPointF( x,y );
}

//------------------------------------------------------------------------------------------------------------
QRectF VGraphicsItemView::iObject2QGraphicsItem(const GraphicSegment& s, const QRectF& qrect) const
{
	QPointF a = iObject2QGraphicsItem(TFloatPoint(s.xinterval().first(), s.yinterval().first()), qrect);
	QPointF b = iObject2QGraphicsItem(TFloatPoint(s.xinterval().second(), s.yinterval().second()), qrect);
	return QRectF( a.x() , a.y() , b.x() - a.x() , b.y() - a.y() );
}

//------------------------------------------------------------------------------------------------------------
QRectF VGraphicsItemView::iObject2QGraphicsItem(const TFloatRect& rect, const QRectF& qrect) const
{
	QPointF a = iObject2QGraphicsItem(rect.pos(), qrect);
	QPointF b = iObject2QGraphicsItem(rect.brpos(), qrect);
	return QRectF( a.x() , a.y() , b.x() - a.x() , b.y() - a.y() );
}

} // end namespoace
