
///<reference path="../model/ILine.ts"/>
///<reference path="../lib/TPoint.ts"/>
///<reference path="VHtmlSvg.ts"/>

class VHtmlLineView extends VHtmlSvg {

    protected fLine: SVGLineElement;

    constructor(parent: VHtmlView) {
		super(parent);
        this.fLine = document.createElementNS('http://www.w3.org/2000/svg','line'); 
    	this.getHtml().className = "inscore-line";
    	this.fSVG.appendChild(this.fLine)
    }

	updateView	( obj: IObject) : void {
		let line = <ILine>obj;
		let scale = line.fPosition.getScale();
		let p = line.getPoint();
		let x = this.relative2SceneWidth(  p.getX() ) * scale;
		let y = this.relative2SceneHeight( p.getY() ) * scale;
		let strokeWidth = obj.fPenControl.getPenWidth();
		//if (!x) x = 1;
		//if (!y) y = 1;
		//this.fLine.setAttribute('transform', super.getTranslate());
		this.fLine.style.strokeWidth = strokeWidth + "px";

		if ( x < 0 || y < 0 ) {
			this.fLine.setAttribute('x1', this.fSVG.style.width);
			this.fLine.setAttribute('y1', (0 + strokeWidth/2).toString());
			this.fLine.setAttribute('x2', (0).toString());
        	this.fLine.setAttribute('y2', (this.fSVG.style.height + strokeWidth/2).toString());
		}
		else {
			this.fLine.setAttribute('x1', (0).toString());
			this.fLine.setAttribute('y1', (0 + strokeWidth/2).toString());
			this.fLine.setAttribute('x2', (x).toString());
			this.fLine.setAttribute('y2', (y + strokeWidth/2).toString());
		}
        this.fLine.style.stroke = obj.fColor.getRGBString();
		this.updateSvgSize (x , y + strokeWidth);

		console.log("VHtmlLineView updateView x y test : " + x + "," + y + " obj size : " + obj.getSize().h + "," + obj.getSize().w);

		this.updatePos(obj);
	}

	updatePos (obj: IObject): void {


		let pos 	= obj.getPosition();
		let size 	= obj.getSize();
		let scale 	= this.getScale(obj);
		let penWidth = obj.fPenControl.getPenWidth()? obj.fPenControl.getPenWidth() : 0;

		let line = <ILine>obj;
		let p = line.getPoint();
		let x = this.relative2SceneWidth ( p.getX() ) * scale;
		let y = this.relative2SceneHeight( p.getY() ) * scale;

		let z		= obj.fPosition.getZOrder();
		let w  		= this.relative2SceneWidth  (size.w)* scale + penWidth;
		let h 		= this.relative2SceneHeight (size.h)* scale + penWidth;
		let left  	= this.relative2SceneX (pos.x) - w/2.0 - (w * obj.fPosition.getXOrigin() / 2.0);
		let top 	= this.relative2SceneY (pos.y) - h/2.0 - (h * obj.fPosition.getYOrigin() / 2.0);

		let elt = this.getHtml();
		elt.style.width  = w +"px";
		elt.style.height = h +"px";
		elt.style.left 	=  left + "px";
		elt.style.top 	=  top + "px";
		elt.style.zIndex = z.toString();
		elt.style.transform  = this.getTransform(obj);
		elt.style.visibility  = obj.fPosition.getVisible() ? "inherit" : "hidden";

		this.setPos( top, left, w, h);
		console.log("VHtmlLineView updatePos test w h : " + w + "," + h);
	}
/*
	getTransform (obj: IObject): string {
		let hw = this.fPixWidth/2;
		let hh = this.fPixHeight/2;
		let dx = -(this.fPixWidth/2)  * (1 + obj.fPosition.getXOrigin());
		let dy = -(this.fPixHeight/2) * (1 + obj.fPosition.getYOrigin());
       return super.getTransform(obj) + ` translate(${dx}px, ${dy}px)`;
	}
	
	updateSvgSize (w: number, h: number): void {
    	w = Math.abs(w);
		h = Math.abs(h);
		let elt = this.getHtml();
		this.fPixWidth = w ? w : 1;
		this.fPixHeight = h ? h : 1; 		
		elt.style.height = this.fPixHeight + "px";
        elt.style.width  = this.fPixWidth  + "px";
		this.fSVG.style.height = this.fPixHeight + "px";
        this.fSVG.style.width  = this.fPixWidth  + "px";
	}*/
}