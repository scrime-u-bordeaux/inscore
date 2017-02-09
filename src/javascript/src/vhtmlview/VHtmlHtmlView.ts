
///<reference path="VHtmlView.ts"/>
///<reference path="../model/IHtml.ts"/>
///<reference path="../model/IText.ts"/>

class VHtmlHtmlView extends VHtmlView {

    constructor(parent: VHtmlView) {
		super( document.createElement('div'), parent); 
        this.getHtml().className = "inscore-html";
    }    

	getText	( obj: IText) : string { return obj.getText(); }

	// scaling is applied as a transform only
	getScale (obj: IObject): number { return 1; }
	updateColor (obj: IObject): void {
        if (obj.fColor.modified())
	        this.getHtml().style.color = obj.fColor.getRGBString();
	}

	// CSS weight are used as numbers
	fontWeight2Num	( weight: string) : number {
		switch (weight) {
			case IText.kWeightNormal: 		return 400;
			case IText.kWeightLight:		return 200;
			case IText.kWeightDemiBold:		return 550;
			case IText.kWeightBold:			return 700;
			case IText.kWeightBlack:		return 900;
			default: return 400;
		}
	}

	setFont	( t: IText) : void {
    	let elt = this.getHtml();
        elt.style.fontSize 		= t.getFontSize()+"px";
        elt.style.fontFamily 	= t.getFontFamily();
        elt.style.fontStyle 	= t.getFontStyle();
        elt.style.fontWeight 	= this.fontWeight2Num(t.getFontWeight()).toString();
    }

	updateView	( obj: IObject) : void {
		let t = <IText>obj;
    	let elt = this.getHtml();
        elt.innerHTML  = this.getText(t);
        elt.style.height = "auto";
        elt.style.width = "auto";
		this.updateObjectSize (obj);
		if (t.fontModified()) this.setFont (t);
		super.updateView(obj);
	}

	getTransform (obj: IObject): string {
		let scale 	= this.autoScale(obj);
		return super.getTransform(obj) + ` scale(${scale})`;
	}

}