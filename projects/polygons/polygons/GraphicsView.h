//
//  GraphicsView.h
//  polygons
//
//  Created by Max Heartfield on 03.11.17.
//  Copyright © 2017 Roman Baygildin. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <OpenGL/gl.h>

@interface GraphicsView : NSOpenGLView{
    
}
- (void) drawRect:(NSRect)bounds;
@end
