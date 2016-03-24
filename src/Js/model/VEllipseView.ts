///<reference path="VObjectView.ts"/>
///<reference path="SvgFactory.ts"/>

class VEllipseView extends VObjectView {
    
    constructor(object: IObject, motherScene: HTMLDivElement) {
        var scene = SvgFactory.createSvg('ellipse'); 

        super(object, scene, motherScene);  
    }    
}