//
//  GraphicsView.m
//  polygons
//
//  Created by Max Heartfield on 03.11.17.
//  Copyright © 2017 Roman Baygildin. All rights reserved.
//

#import "GraphicsView.h"

@implementation GraphicsView

- (void)drawRect:(NSRect)bounds {
    [super drawRect:bounds];
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex3f(  0.0,  0.6, 0.0);
    glVertex3f( -0.2, -0.3, 0.0);
    glVertex3f(  0.2, -0.3 ,0.0);
    glEnd();
    glFlush();
}

@end
