//
//  main.cpp
//  opengl_start
//
//  Created by Roman Yarnykh on 12.11.17.
//  Copyright © 2017 Roman Yarnykh. All rights reserved.
//

#include "Window.h"

/**
 * Entry point for application
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char **argv) {
    auto * wnd = new Window();
    wnd->run();
    delete wnd;
    exit(EXIT_SUCCESS);
}
