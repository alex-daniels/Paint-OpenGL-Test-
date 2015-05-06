/*
Alex Daniels
CS 456
Assignment 2

View Readme

*/

#include <math.h>
#include <iostream>
#include <GLUT/glut.h>
#include <OpenGl/glu.h>
#include <OpenGL/gl.h>
#include <vector>
#include <string>
#include <cstdlib>
#include "DisplayClass.h"

//glut functions
void initDisplay();
void displayFunc();
void reshapeFunc(int w, int h);
void keyboardFunc(unsigned char key, int x, int y);
void keyboardSpecFunc(int key, int x, int y);
void mouseFunc(int button, int state, int x, int y);
void createMenu();
void shapeMenu(int choice);
void colorMenu(int choice);
void exitMenu(int choice);
void rightMenu(int choice);
void clearMenu(int choice);

//class
Display* newDisplay = new Display();

std::string tempText;

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(newDisplay->getWidth(), newDisplay->getHeight());
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Assignment_2");
    createMenu();
    initDisplay();
    glutDisplayFunc(displayFunc);
    glutKeyboardFunc(keyboardFunc);
    glutReshapeFunc(reshapeFunc);
    glutMouseFunc(mouseFunc);
    glutMainLoop();

    return 0;
}

void initDisplay()
{
    newDisplay->initDisplay();
}

void displayFunc()
{
    newDisplay->displayFunction();
}

void reshapeFunc(int w, int h)
{
    newDisplay->reshapeFunction(w, h);
}

void keyboardFunc(unsigned char key, int x, int y)
{
    newDisplay->keyboardFunction(key, x, y);
}

void mouseFunc(int button, int state, int x, int y)
{
    newDisplay->mouseFunction(button, state, x, y);
}

//creates the menu and attaches it to the right moust click
void createMenu()
{
    int sMenu, cMenu, clearM;
    //creating menus
    sMenu = glutCreateMenu(shapeMenu);
    glutAddMenuEntry("XY", 1);
    glutAddMenuEntry("YX", 2);
    glutAddMenuEntry("XYX", 3);
    glutAddMenuEntry("YXY", 4);
    //glutAddMenuEntry("None", 5);
    cMenu = glutCreateMenu(colorMenu);
    glutAddMenuEntry("Red", 1);
    glutAddMenuEntry("Green", 2);
    glutAddMenuEntry("Blue", 3);
    glutAddMenuEntry("Cyan", 4);
    glutAddMenuEntry("Magenta", 5);
    glutAddMenuEntry("Yellow", 6);
    glutAddMenuEntry("White", 7);
    glutAddMenuEntry("Black", 8);

    clearM = glutCreateMenu(clearMenu);
    glutAddMenuEntry("Clear All", 1);
    glutAddMenuEntry("Clear Wires", 2);

    glutCreateMenu(rightMenu);
    glutAddSubMenu("Wires", sMenu);
    glutAddSubMenu("Colors", cMenu);
    glutAddMenuEntry("Clear", 1);
    glutAddMenuEntry("Exit", 2);

    //glutAddMenuEntry("Clear", clearM);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

//pick wire type state
//1 XY 2 YX 3 XYX 4 YXY
void shapeMenu(int choice)
{
    switch(choice)
    {
        case 1:
            newDisplay->setShapeChoice(1);
            break;
        case 2:
            newDisplay->setShapeChoice(2);
            break;
        case 3:
            newDisplay->setShapeChoice(3);
            break;
        case 0:
            newDisplay->setShapeChoice(0);
            break;
    }
}

//chose desired color state
void colorMenu(int choice)
{
    switch(choice)
    {
        case 1:
            //red
            newDisplay->setColors(1);
            break;
        case 2:
            //green
            newDisplay->setColors(2);
            break;
        case 3:
            //blue
            newDisplay->setColors(3);
            break;
        case 4: 
            //cyan
            newDisplay->setColors(4);
            break;
        case 5: 
            //magenta
            newDisplay->setColors(5);
            break;
        case 6:
            //Yellow
            newDisplay->setColors(6);
            break;
        case 7:
            //white
            newDisplay->setColors(7);
            break;
        case 8:
            //black
            newDisplay->setColors(8);
            break;
    }
}

//1 is clear
//2 is exit
void rightMenu(int choice)
{
    if(choice == 1)
        newDisplay->clearScreen(1);
    if(choice == 2)
    {
        delete newDisplay;
        exit(0);
    }
}

void clearMenu(int choice)
{
    if (choice == 1)
        newDisplay->clearScreen(1);
        
    if(choice == 2)
        newDisplay->clearScreen(3);
}
//silencing OSX 10.9 depreciated warnings
//#pragma GCC diagnostic pop