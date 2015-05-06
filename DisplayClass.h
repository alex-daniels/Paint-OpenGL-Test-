//Apple's OSX 10.9 specific warning silencer
//Depreciated glut functions in the update
//helps to avoid having to search through 30+ warnings
//to get to any error that comes up
//pop at the bottom of the main.cpp
//#pragma GCC diagnostic push
//#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
//#define SCALEFACTOR 1.5

enum state {NONE, AND, OR, NOT};
enum choice {BLANK, XY, YX, XYX, YXY};
enum color {NoColor, Red, Green, Blue, Cyan, Magenta, Yellow, White, Black};

typedef struct 
{
	float x;
	float y;
}Point;

typedef struct 
{
	float x1;
	float y1;
	float x2; 
	float y2;
	float c1;
	float c2;
	float c3;
	float f;
}WirePoint;

typedef struct 
{
	float c1;
	float c2;
	float c3;
}Colors;

typedef struct 
{
	float x1;
	float y1;
	float x2;
	float y2;
	//in == false out == true;
	bool inorout;
	bool inputFilled;
}Terminal;


class Display
{
public:
	Display();
	~Display();
	int getWidth() { return width; }
	int getHeight() { return height; }
	void initDisplay();
	void displayFunction();
	void mouseFunction(int button, int state, int x, int y);
	void addTerminals(int x, int y);
	bool addTerminalLine(int x, int y);
	void drawText(std::string text, int x, int y, float c1, float c2, float c3);
	void screenText();
	void drawMenu();
	void keyboardFunction(unsigned char key, int x, int y);
	void setShapeChoice(int choice);
	void setItemChoice();
	void reshapeFunction(int width, int height);
	void clearScreen(int choice);
	void setInputText(std::string text);
	int getTextFlag() { return textFlag;}
	void setColors(int choice);
	private:
	int width;
	int height;
	int xPos;
	int yPos;
	int clearFlag;
	int count;
	int textFlag;
	int terminalOutCount;
	int terminalInCount;
	float stringTextVal;

	Point point;
	WirePoint wirept;

	std::vector<Point> pointCollectionAND;
	std::vector<Point> pointCollectionOR;
	std::vector<Point> pointCollectionNOT;
	std::vector<WirePoint> wirePointsXY;
	std::vector<WirePoint> wirePointsYX;
	std::vector<WirePoint> wirePointsXYX;
	std::vector<WirePoint> wirePointsYXY;
	std::vector<Terminal> Terminals;

	std::string andgateText;
	std::string orgateText;
	std::string notgateText;
	std::string textInput;

	state selectedState;
	state displayListState;
	choice rightMenuChoice;
	color currentColor;
	Colors colorChoice;
};

Display::Display()
{
	width = 700;
	height = 700;
	xPos = 0;
	yPos = 0;
	clearFlag = 0;
	count = 0;
	textFlag = 0;
	terminalOutCount = 0;
	terminalInCount = 0;
	stringTextVal = 0;
	andgateText = "AND";
	orgateText = "OR";
	notgateText = "NOT";
	selectedState = NONE;
	displayListState = NONE;
	rightMenuChoice = BLANK;
	currentColor = NoColor;
	colorChoice.c1 = 0.0;
	colorChoice.c2 = 0.0;
	colorChoice.c3 = 0.0;
}

Display::~Display()
{
	pointCollectionAND.clear();
	pointCollectionOR.clear();
	pointCollectionNOT.clear();
	wirePointsXY.clear();
	wirePointsYX.clear();
	wirePointsXYX.clear();
	wirePointsYXY.clear();
	Terminals.clear();	
	textInput.erase(textInput.begin(), textInput.end());
}

//create the display lists with each gate beginning at 0,0 coordinates
void Display::initDisplay()
{
	//AND GATE
	displayListState = AND;
	glNewList(displayListState, GL_COMPILE);
	  glColor3f(0.0, 0.0, 0.0);
	    glBegin(GL_LINE_LOOP);
		for(int i = 0; i < 30; i++)
		{
			float sinpt = sin(i / 30.0 * 2*M_PI) * 25;
			float cospt = cos(i / 30.0 * 2*M_PI) * 25;
			if(sinpt >= 0.0)
				glVertex2f(sinpt, cospt + 25);
		}
	    glEnd();
	    //connecting node 1
	    glBegin(GL_LINES);
	      glVertex2f(0.0, 15.0);
	      glVertex2f(-25.0, 15.0);
	    glEnd();
	    glRectf(-37.0, 8.0, -23.0, 22.0);
	    //connecting node 2
	    glBegin(GL_LINES);
	      glVertex2f(0.0, 35.0);
	      glVertex2f(-25.0, 35.0);
	    glEnd();
	    glRectf(-37.0, 28.0, -23.0, 42.0);

	    //exit node
	    glBegin(GL_LINES);
	      glVertex2f(25.0, 25.0);
	      glVertex2f(50.0, 25.0);
	    glEnd();
	    glRectf(43.0, 18.0, 57.0, 32.0);
	    //symbol
	    glBegin(GL_LINES);
	      glVertex2f(5.0, 15.0);
	      glVertex2f(10.0, 35.0);
	    glEnd();
	    glBegin(GL_LINES);
	      glVertex2f(15.0, 15.0);
	      glVertex2f(10.0, 35.0);
	    glEnd();
	glEndList();

	//OR GATE
	displayListState = OR;
	glNewList(displayListState, GL_COMPILE);
	glColor3f(0.0, 0.0, 0.0);
	  //draw hexagon
	  glBegin(GL_LINE_LOOP);
		for(int i = 0; i < 6; i++)
			glVertex2f((sin(i / 6.0 * 2*M_PI) *20) + 10, (cos(i / 6.0 * 2*M_PI) * 20) + 20);
	  glEnd();
	  //connecting node 1
	  	glBegin(GL_LINES);
	      glVertex2f(-5.0, 10.0);
	      glVertex2f(-30.0, 10.0);
	    glEnd();
	    glRectf(-37.0, 3.0, -23.0, 17.0);
	    //connecting node 2
	    glBegin(GL_LINES);
	      glVertex2f(-5.0, 30.0);
	      glVertex2f(-30.0, 30.0);
	    glEnd();
	    glRectf(-37.0, 23.0, -23.0, 37.0);
	    //exit node
	    glBegin(GL_LINES);
	      glVertex2f(27.0, 20.0);
	      glVertex2f(50.0, 20.0);
	    glEnd();
	    glRectf(43.0, 13.0, 57.0, 27.0);

	    //symbol
	    glBegin(GL_LINES);
	      glVertex2f(10.0, 15.0);
	      glVertex2f(15.0, 25.0);
	    glEnd();
	    glBegin(GL_LINES);
	      glVertex2f(10.0, 15.0);
	      glVertex2f(5.0, 25.0);
	    glEnd();
	glEndList();

	//NOT GATE
	displayListState = NOT;
	glNewList(displayListState, GL_COMPILE);
		glColor3f(0.0, 0.0, 0.0);
		//begin triangle
		glBegin(GL_LINE_LOOP);
		  glVertex2f(0.0, 0.0);
		  glVertex2f(25.0, 25.0);
		  glVertex2f(0.0, 50.0);
		glEnd();
		//end triangle
		//begin right node connector
		glBegin(GL_LINES);
		  glVertex2f(25.0, 25.0);
		  glVertex2f(50.0, 25.0);
		glEnd();
		//end right node connector
		//begin right node
	  	glRectf(43.0, 18.0, 57.0, 32.0);
	  	//end right node
	  	//begin left node connector
	  	glBegin(GL_LINES);
	  	  glVertex2f(-25.0, 25.0);
	  	  glVertex2f(0.0, 25.0);
	  	glEnd();
	  	//end left node connector
	  	//begin left node
	  	glRectf(-37.0, 18.0, -23.0, 32.0);
	  	//end left node

	  	//symbol
	  	glBegin(GL_LINES);
	  	  glVertex2f(15.0, 22.0);
	  	  glVertex2f(15.0, 27.0);
	  	glEnd();
	  	glBegin(GL_LINES);
	  	  glVertex2f(5.0, 27.0);
	  	  glVertex2f(15.0, 27.0);
	  	glEnd();
	glEndList();
}
//display callback
void Display::displayFunction()
{
	int i;
	glClearColor(0.5, 0.5, 0.5, 0.5);
	glClear(GL_COLOR_BUFFER_BIT);
	//draw the menu and text on screen
	drawMenu();
	//draw gates based on translations from location of left clicks
	if(!clearFlag)
	{
		for(i = 0; i < pointCollectionAND.size(); i++)
		{
			glPushMatrix();
			glLoadIdentity();
			glTranslatef(pointCollectionAND[i].x, pointCollectionAND[i].y, 0.0);
			//glScalef(SCALEFACTOR, SCALEFACTOR, 0);
			displayListState = AND;
			glCallList(displayListState);
			glPopMatrix();

		}

		for(i = 0; i < pointCollectionOR.size(); i++)
		{
			glPushMatrix();
			glLoadIdentity();
			glTranslatef(pointCollectionOR[i].x, pointCollectionOR[i].y, 0.0);
			//glScalef(SCALEFACTOR, SCALEFACTOR, 0);
			displayListState = OR;
			glCallList(displayListState);
			glPopMatrix();
		}

		for(i = 0; i < pointCollectionNOT.size(); i++)
		{
			glPushMatrix();
			glLoadIdentity();
			glTranslatef(pointCollectionNOT[i].x, pointCollectionNOT[i].y, 0.0);
			//glScalef(SCALEFACTOR, SCALEFACTOR, 0);
			displayListState = NOT;
			glCallList(displayListState);
			glPopMatrix();
		}
	}
	//xy wire list
	for(i = 0; i < wirePointsXY.size(); i++)
	{

		glColor3f(wirePointsXY[i].c1, wirePointsXY[i].c2, wirePointsXY[i].c3);
		glBegin(GL_LINES);
		  glVertex2f(wirePointsXY[i].x1, wirePointsXY[i].y1);
		  glVertex2f(wirePointsXY[i].x2, wirePointsXY[i].y1);
		glEnd();
		glBegin(GL_LINES);
		  glVertex2f(wirePointsXY[i].x2, wirePointsXY[i].y1);
		  glVertex2f(wirePointsXY[i].x2, wirePointsXY[i].y2);
		glEnd();
	}
	//yx wire list
	for(i = 0; i < wirePointsYX.size(); i++)
	{

		glColor3f(wirePointsYX[i].c1, wirePointsYX[i].c2, wirePointsYX[i].c3);
		glBegin(GL_LINES);
		  glVertex2f(wirePointsYX[i].x1, wirePointsYX[i].y1);
		  glVertex2f(wirePointsYX[i].x1, wirePointsYX[i].y2);
		glEnd();
		glBegin(GL_LINES);
		  glVertex2f(wirePointsYX[i].x1, wirePointsYX[i].y2);
		  glVertex2f(wirePointsYX[i].x2, wirePointsYX[i].y2);
		glEnd();
	}
	//xyx wire list
	for(i = 0; i < wirePointsXYX.size(); i++)
	{
		//check SE -> NW click
		if(wirePointsXYX[i].x2 > wirePointsXYX[i].x1)
		{
			glColor3f(wirePointsXYX[i].c1, wirePointsXYX[i].c2, wirePointsXYX[i].c3);
			glBegin(GL_LINES);
			  glVertex2f(wirePointsXYX[i].x1, wirePointsXYX[i].y1);
			  glVertex2f(wirePointsXYX[i].x1 + (wirePointsXYX[i].x1 * wirePointsXYX[i].f), wirePointsXYX[i].y1);
			  glVertex2f(wirePointsXYX[i].x1 + (wirePointsXYX[i].x1 * wirePointsXYX[i].f), wirePointsXYX[i].y2);
			  glVertex2f(wirePointsXYX[i].x2, wirePointsXYX[i].y2);
			glEnd();
			glBegin(GL_LINES);
			  glVertex2f(wirePointsXYX[i].x1 + (wirePointsXYX[i].x1 * wirePointsXYX[i].f), wirePointsXYX[i].y1);
			  glVertex2f(wirePointsXYX[i].x1 + (wirePointsXYX[i].x1 * wirePointsXYX[i].f), wirePointsXYX[i].y2);
			glEnd();
		}
		else 
		{
			glColor3f(wirePointsXYX[i].c1, wirePointsXYX[i].c2, wirePointsXYX[i].c3);
			glBegin(GL_LINES);
			  glVertex2f(wirePointsXYX[i].x2, wirePointsXYX[i].y2);
			  glVertex2f(wirePointsXYX[i].x2 + (wirePointsXYX[i].x2 * wirePointsXYX[i].f), wirePointsXYX[i].y2);
			  glVertex2f(wirePointsXYX[i].x2 + (wirePointsXYX[i].x2 * wirePointsXYX[i].f), wirePointsXYX[i].y1);
			  glVertex2f(wirePointsXYX[i].x1, wirePointsXYX[i].y1);
			glEnd();
			glBegin(GL_LINES);
			  glVertex2f(wirePointsXYX[i].x2 + (wirePointsXYX[i].x2 * wirePointsXYX[i].f), wirePointsXYX[i].y1);
			  glVertex2f(wirePointsXYX[i].x2 + (wirePointsXYX[i].x2 * wirePointsXYX[i].f), wirePointsXYX[i].y2);
			glEnd();
		}
	}
	//YXY wire list
	for(i = 0; i < wirePointsYXY.size(); i++)
	{
		//check SE -> NW clicks
		if(wirePointsYXY[i].x2 > wirePointsYXY[i].x1)
		{
			glColor3f(wirePointsYXY[i].c1, wirePointsYXY[i].c2, wirePointsYXY[i].c3);
			glBegin(GL_LINES);
			  glVertex2f(wirePointsYXY[i].x1, wirePointsYXY[i].y1);
			  glVertex2f(wirePointsYXY[i].x1, wirePointsYXY[i].y2 + (wirePointsYXY[i].y2 * wirePointsYXY[i].f));
			  glVertex2f(wirePointsYXY[i].x2, wirePointsYXY[i].y2 + (wirePointsYXY[i].y2 * wirePointsYXY[i].f));
			  glVertex2f(wirePointsYXY[i].x2, wirePointsYXY[i].y2);
			glEnd();
			glBegin(GL_LINES);
			  glVertex2f(wirePointsYXY[i].x1, wirePointsYXY[i].y2 + (wirePointsYXY[i].y2 * wirePointsYXY[i].f));
			  glVertex2f(wirePointsYXY[i].x2, wirePointsYXY[i].y2 + (wirePointsYXY[i].y2 * wirePointsYXY[i].f));
			glEnd();
		}
		else
		{
			glColor3f(wirePointsYXY[i].c1, wirePointsYXY[i].c2, wirePointsYXY[i].c3);
			glBegin(GL_LINES);
			  glVertex2f(wirePointsYXY[i].x2, wirePointsYXY[i].y2);
			  glVertex2f(wirePointsYXY[i].x2, wirePointsYXY[i].y1 + (wirePointsYXY[i].y1 * wirePointsYXY[i].f));
			  glVertex2f(wirePointsYXY[i].x1, wirePointsYXY[i].y1 + (wirePointsYXY[i].y1 * wirePointsYXY[i].f));
			  glVertex2f(wirePointsYXY[i].x1, wirePointsYXY[i].y1);
			glEnd();
			glBegin(GL_LINES);
			  glVertex2f(wirePointsYXY[i].x2, wirePointsYXY[i].y1 + (wirePointsYXY[i].y1 * wirePointsYXY[i].f));
			  glVertex2f(wirePointsYXY[i].x1, wirePointsYXY[i].y1 + (wirePointsYXY[i].y1 * wirePointsYXY[i].f));
			glEnd();	
		}
	}
	glutSwapBuffers();
	glutPostRedisplay();
}

//mouse callback
//placement logic happens here.
//add terminals adds the placement to the lists
//addTerminalLine() checks to see if it is a valid placement
void Display::mouseFunction(int button, int state, int x, int y)
{
	Point tempPoint;
	static Point tempPoint2;
	//flip the coordinates
	y = abs(y - 700);
	tempPoint.x = x;
	tempPoint.y = y;
	//gate placement
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if(rightMenuChoice == BLANK)
		{
			if((x >= 0 && x <= 75) && y >= 625)
				selectedState = AND;

			if((x >= 75 && x <= 150) && y >= 625)
				selectedState = OR;

			if((x >= 150 && x <= 225) && y >= 625)
				selectedState = NOT;

			if(selectedState == AND && y <= 625)
			{
				pointCollectionAND.push_back(tempPoint);
				addTerminals(x, y);
			}

			if(selectedState == OR && y <= 625)
			{
				pointCollectionOR.push_back(tempPoint);
				addTerminals(x, y);
			}

			if(selectedState == NOT && y <= 625)
			{
				pointCollectionNOT.push_back(tempPoint);
				addTerminals(x, y);
			}
		}
	}
	//wireplacement
	if(button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
	{
		if(currentColor!= NoColor)
		{
			switch(rightMenuChoice)
			{
				//XY wires
				case 1:
					if(count == 0)
					{
						if(addTerminalLine(x, y))
						{				
							count++;				
							tempPoint2.x = x;
							tempPoint2.y = y;
						}
						else
						{
							std::cout<<"ERROR" <<std::endl;
							std::cout << "\a";
							count = 0;
						}
					}
					else
					{
						if(addTerminalLine(x, y))
						{
							//std::cout <<"clicked inside terminal" <<std::endl;
							WirePoint tempWP;
							count = 0;
							tempWP.x1 = tempPoint2.x;
							tempWP.y1 = tempPoint2.y;
							tempWP.x2 = x;
							tempWP.y2 = y;
							tempWP.c1 = colorChoice.c1;
							tempWP.c2 = colorChoice.c2;
							tempWP.c3 = colorChoice.c3;
							wirePointsXY.push_back(tempWP);
						}
						else 
						{
							std::cout<<"ERROR" <<std::endl;
							std::cout<<"\a";
							count = 0;
						}
					}
					break;
				//YX wires
				case 2:
					if(count == 0)
					{
						if(addTerminalLine(x, y))
						{				
							count++;				
							tempPoint2.x = x;
							tempPoint2.y = y;
						}
						else
						{
							std::cout<<"ERROR" <<std::endl;
							std::cout << "\a";
							count = 0;
						}
					}
					else
					{
						if(addTerminalLine(x, y))
						{
							//std::cout <<"clicked inside terminal" <<std::endl;
							WirePoint tempWP;
							count = 0;
							tempWP.x1 = tempPoint2.x;
							tempWP.y1 = tempPoint2.y;
							tempWP.x2 = x;
							tempWP.y2 = y;
							tempWP.c1 = colorChoice.c1;
							tempWP.c2 = colorChoice.c2;
							tempWP.c3 = colorChoice.c3;
							wirePointsYX.push_back(tempWP);
						}
						else 
						{
							std::cout<<"ERROR" <<std::endl;
							std::cout<<"\a";
							count = 0;
						}
					}
					break;
				//XYX wires
				case 3:
					if(count == 0)
					{
						if(addTerminalLine(x, y))
						{
							std::cout <<"Enter floating point 0.0 ≤ x < 1.0" <<std::endl;
							textFlag = 1;
							count++;
							WirePoint tempWP;
							tempPoint2.x = x;
							tempPoint2.y = y;
						}
						else
						{
							std::cout<<"ERROR" <<std::endl;
							std::cout<<"\a";
							count = 0;
						}
					}
					else
					{
						if(addTerminalLine(x, y))
						{
							if(stringTextVal != -1)
							{
								WirePoint tempWP;
								count = 0;
								tempWP.x1 = tempPoint2.x;
								tempWP.y1 = tempPoint2.y;
								tempWP.x2 = x;
								tempWP.y2 = y;
								tempWP.c1 = colorChoice.c1;
								tempWP.c2 = colorChoice.c2;
								tempWP.c3 = colorChoice.c3;
								tempWP.f = stringTextVal;
								wirePointsXYX.push_back(tempWP);
								textFlag = 0;
								textInput.clear();
							}
						}
						else
						{
							std::cout<<"ERROR" <<std::endl;
							std::cout<<"\a";
							count = 0;
						}
					}
					break;
				//YXY wires
				case 4:
				{
					if(count == 0)
					{
						if(addTerminalLine(x, y))
						{
							std::cout <<"Enter floating point 0.0 ≤ x < 1.0" <<std::endl;
							textFlag = 1;
							count++;
							WirePoint tempWP;
							tempPoint2.x = x;
							tempPoint2.y = y;
						}
						else
						{
							std::cout<<"ERROR" <<std::endl;
							std::cout<<"\a";
						}
					}
					else
					{
						if(addTerminalLine(x, y))
						{
							if(stringTextVal != -1)
							{
								WirePoint tempWP;
								count = 0;
								tempWP.x1 = tempPoint2.x;
								tempWP.y1 = tempPoint2.y;
								tempWP.x2 = x;
								tempWP.y2 = y;
								tempWP.c1 = colorChoice.c1;
								tempWP.c2 = colorChoice.c2;
								tempWP.c3 = colorChoice.c3;
								tempWP.f = stringTextVal;
								wirePointsYXY.push_back(tempWP);
								textFlag = 0;
								textInput.clear();
							}
						}
						else
						{
							std::cout<<"ERROR" <<std::endl;
							std::cout<<"\a";
							count = 0;
						}
					}
				}
				break;
				//no case
				case 0:
					break;
			}
		}
	}
}

//adds the input/output terminals from the gates to a list
//based on where in the window the user clicks.
void Display::addTerminals(int x, int y)
{
	if(selectedState == AND)
	{
		Terminal terminals;

		terminals.x1 = (43.0 + x);
		terminals.y1 = (18.0 + y);
		terminals.x2 = (57.0 + x);
		terminals.y2 = (32.0 + y);
		terminals.inorout = true;
		terminals.inputFilled = false;
		Terminals.push_back(terminals);


		terminals.x1 = (-37.0 + x);
		terminals.y1 = (8.0 + y);
		terminals.x2 = (-23.0 + x);
		terminals.y2 = (22.0 + y);
		terminals.inorout = false;
		terminals.inputFilled = false;
		Terminals.push_back(terminals);
		
		terminals.x1 = (-37.0 + x);
		terminals.y1 = (28.0 + y);
		terminals.x2 = (-23.0 + x);
		terminals.y2 = (42.0 + y);
		terminals.inorout = false;
		terminals.inputFilled = false;
		Terminals.push_back(terminals);
	}

	else if(selectedState == OR)
	{
		Terminal terminals;

		terminals.x1 = -37.0 + x;
		terminals.y1 = 3.0 + y;
		terminals.x2 = -23.0 + x;
		terminals.y2 = 17.0 + y;
		terminals.inorout = false;
		terminals.inputFilled = false;
		Terminals.push_back(terminals);

		terminals.x1 = -37.0 + x;
		terminals.y1 = 23.0 + y;
		terminals.x2 = -23.0 + x;
		terminals.y2 = 37.0 + y;
		terminals.inorout = false;
		terminals.inputFilled = false;
		Terminals.push_back(terminals);

		terminals.x1 = 43.0 + x;
		terminals.y1 = 13.0 + y;
		terminals.x2 = 57.0 + x;
		terminals.y2 = 27.0 + y;
		terminals.inorout = true;
		terminals.inputFilled = false;
		Terminals.push_back(terminals);
	}

	else if(selectedState == NOT)
	{
		Terminal terminals;

		terminals.x1 = -37.0 + x;
		terminals.y1 = 18.0 + y;
		terminals.x2 = -23.0 + x;
		terminals.y2 = 32.0 + y;
		terminals.inorout = false;
		terminals.inputFilled = false;
		Terminals.push_back(terminals);

		terminals.x1 = 43.0 + x;
		terminals.y1 = 18.0 + y;
		terminals.x2 = 57.0 + x;
		terminals.y2 = 32.0 + y;
		terminals.inorout = true;
		terminals.inputFilled = false;
		Terminals.push_back(terminals);

	}
	/*
	for(int i = 0; i < Terminals.size(); i++)
	{
		std::cout << i << ": " << Terminals[i].x1 << ", " << Terminals[i].y1 << ", " 
			  	  << Terminals[i].x2 << ", " << Terminals[i].y2 << ", "
			  	  << Terminals[i].inorout <<std::endl;
	}
	std::cout<<std::endl;
	*/
}

//checks to see if it is a valid click and placement
//if the click is valid, it returns true
//if the click is invalid, either outside the bounding boxes or 
//clicking on an input terminal that has a wire
//it returns false
bool Display::addTerminalLine(int x, int y)
{
	//std::cout << x <<", " << y <<std::endl;
	//loop through the terminals
	for(int i = 0; i < Terminals.size(); i++)
	{
		if((x >= Terminals[i].x1 && y >= Terminals[i].y1) && (x <= Terminals[i].x2 && y <= Terminals[i].y2))
		{
			//if it is an output terminal.
			if(Terminals[i].inorout == true)
				terminalOutCount++;

			//if it is an imput terminal
			else if(Terminals[i].inorout == false)
			{
				//is it already connected to something?
				//if yes, return false (ERROR)
				if(Terminals[i].inputFilled)
					return false;
				//if first palcement was valid, 
				//it is connected to something
				else
				{	
					if(terminalInCount == 1)
						Terminals[i].inputFilled = true;
					terminalInCount++;
					//return true;
				}
			}
			//if input is connected already reset the counters and 
			//return false (error)
			if(terminalInCount == 2 || terminalOutCount == 1000)
			{
				terminalOutCount = 0;
				terminalInCount = 0;
				Terminals[i].inputFilled = false;
				return false;
			}
			else
				return true;
		}
	}
	return false;
}

//drawing text on the screen
void Display::drawText(std::string text, int x, int y, float c1, float c2, float c3)
{
	glColor3f(c1, c2, c3);
	glRasterPos2f(x, y);
	for(int i = 0; i < text.size(); i++)
    	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
}

//text on screen.
//color in corresponding color
//wire type
//gate type.
void Display::screenText()
{
	//text things
	if(selectedState == AND)
		drawText("AND Gate Selected - ESC to reset", 1, 2, 1.0, 1.0, 1.0);
	if(selectedState == OR)
		drawText("Or Gate Selected - ESC to reset", 1, 2, 1.0, 1.0, 1.0);
	if(selectedState == NOT)
		drawText("Not Gate Selected - ESC to reset", 1, 2, 1.0, 1.0, 1.0);
	else if(selectedState == NONE)
		drawText("No Gate Selected", 1, 2, 1.0, 1.0, 1.0);
	if(rightMenuChoice == XY)
		drawText("XY Wire", 1, 15, 1.0, 1.0, 1.0);
	if(rightMenuChoice == YX)
		drawText("YX Wire", 1, 15, 1.0, 1.0, 1.0);
	if(rightMenuChoice == XYX)
		drawText("XYX Wire", 1, 15, 1.0, 1.0, 1.0);
	if(rightMenuChoice == YXY)
		drawText("YXY Wire", 1, 15, 1.0, 1.0, 1.0);
	else if(rightMenuChoice == BLANK)
		drawText("No Wire Choice", 1, 15, 1.0, 1.0, 1.0);

	switch(currentColor)
	{
		case 1:
			drawText("Color: RED", 1, 30, 1.0, 0.0, 0.0);
			break;
		case 2:
			drawText("Color: GREEN", 1, 30, 0.0, 1.0, 0.0);
			break;
		case 3:
			drawText("Color: BLUE", 1, 30, 0.0, 0.0, 1.0);
			break;
		case 4:
			drawText("Color: CYAN", 1, 30, 0.0, 1.0, 1.0);
			break;
		case 5:
			drawText("Color: MAGENTA", 1, 30, 1.0, 0.0, 1.0);
			break;
		case 6:
			drawText("Color: YELLOW", 1, 30, 1.0, 1.0, 0.0);
			break;
		case 7:
			drawText("Color: WHITE", 1, 30, 1.0, 1.0, 1.0);
			break;
		case 8:
			drawText("Color: BLACK", 1, 30, 0.0, 0.0, 0.0);
			break;
		case 0:
			drawText("No Color Selected", 1, 30, 1.0, 1.0, 1.0);
			break;
	}
}

//draws the menu on screen
//gate 'buttons'
//and calls to draw the screen text
void Display::drawMenu()
{

	glColor3f(1.0, 1.0, 1.0);
	glRectf(0.0, 625.0, 75.0, 700.0);
	drawText(andgateText, 1.0, 627.0, 0.0, 0.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	  glVertex2f(75.0, 625.0);
	  glVertex2f(75.0, 700.0);
	 glEnd();

	glPushMatrix();
	glLoadIdentity();
	glTranslatef(30, 650, 0);
	glScalef(0.75, 0.75, 0);
	displayListState = AND;
	glCallList(displayListState);
	glPopMatrix();
		
	glColor3f(1.0, 1.0, 1.0);
	glRectf(75.0, 625.0, 150.0, 700.0);
	drawText(orgateText, 76.0, 626.0, 0.0, 0.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	  glVertex2f(150.0, 625.0);
	  glVertex2f(150.0, 700.0);
	glEnd();

	glPushMatrix();
	glLoadIdentity();
	glTranslatef(105, 650, 0);
	glScalef(0.75, 0.75, 0);
	displayListState = OR;
	glCallList(displayListState);
	glPopMatrix();

	glColor3f(1.0, 1.0, 1.0);
	glRectf(150.0, 625.0, 225.0, 700.0);
	drawText(notgateText, 151.0, 626.0, 0.0, 0.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	  glVertex2f(225.0, 625.0);
	  glVertex2f(225.0, 700.0);
	glEnd();

	glPushMatrix();
	glLoadIdentity();
	glTranslatef(180, 650, 0);
	glScalef(0.75, 0.75, 0);
	displayListState = NOT;
	glCallList(displayListState);
	glPopMatrix();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	  glVertex2f(0.0, 625.0);
	  glVertex2f(225.0, 625.0);
	glEnd();
	
	screenText();
}

//keyboard callback
//if key is 'esc' then reset go to resting state
//if XYX or YXY wires are chosen accept input
//and break if spacebar is hit
void Display::keyboardFunction(unsigned char key, int x, int y)
{
	if(key == 27)
	{
        selectedState = NONE;
        rightMenuChoice = BLANK;
        currentColor = NoColor;
    }

    if(textFlag == 1)
    {
        textInput += key;
        if(key == 32)
  	    {
  	    	//convert to floating point number
  	        stringTextVal = atof(textInput.c_str());
  	        //check for valid input and if not reset
  	        if(stringTextVal < 0.0 || stringTextVal > 1.0)
  	        {
  	        	std::cout <<"Error incorrect values" <<std::endl;
  	        	//stringTextVal = -1;
  	            selectedState = NONE;
        		rightMenuChoice = BLANK;
        		currentColor = NoColor;
  	        }
  	        
  	        //std::cout <<stringTextVal <<std::endl;
  	    }
    } 
}

//set which wire is currently being picked
//via the menu
void Display::setShapeChoice(int choice)
{
	selectedState = NONE;
	switch(choice)
	{
		case 1: 
			rightMenuChoice = XY;
			break;
		case 2:
			rightMenuChoice = YX;
			break;
		case 3:
			rightMenuChoice = XYX;
			break;
		case 4:
			rightMenuChoice = YXY;
			break;
		case 5:
			rightMenuChoice = BLANK;
			break;
	}
}

//reshape callback
void Display::reshapeFunction(int width, int height)
{
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); 
    glOrtho(0.0, (GLdouble)width, 0.0, (GLdouble)height, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); 
    glViewport(0,0,width,height);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

//empty the lists upon Clear selection
void Display::clearScreen(int choice)
{
	if(choice == 1)
	{
		//stop drawing
		clearFlag = 1;
		//empty the lists
		pointCollectionAND.clear();
		pointCollectionOR.clear();
		pointCollectionNOT.clear();
		wirePointsXY.clear();
		wirePointsYX.clear();
		wirePointsXYX.clear();
		wirePointsYXY.clear();
		Terminals.clear();
		//resets the pick
		selectedState = NONE;
		currentColor = NoColor;
		rightMenuChoice = BLANK;
		//resume drawing
		clearFlag = 0;
		//vectorCount = 0;
        textInput.erase(textInput.begin(), textInput.end());
	}
	//free up space before quitting!
	if(choice == 3)
	{
		wirePointsXY.clear();
		wirePointsXYX.clear();
		wirePointsYXY.clear();
	}
}

//set the desired color.
void Display::setColors(int choice)
{
	switch(choice)
	{
		case 1:
			currentColor = Red;
			colorChoice.c1 = 1.0;
			colorChoice.c2 = 0.0;
			colorChoice.c3 = 0.0;
			break;
		case 2:
			currentColor = Green;
			colorChoice.c1 = 0.0;
			colorChoice.c2 = 1.0;
			colorChoice.c3 = 0.0;
			break;
		case 3:
			currentColor = Blue;
			colorChoice.c1 = 0.0;
			colorChoice.c2 = 0.0;
			colorChoice.c3 = 1.0;
			break;
		case 4:
			currentColor = Cyan;
			colorChoice.c1 = 0.0;
			colorChoice.c2 = 1.0;
			colorChoice.c3 = 1.0;
			break;
		case 5:
			currentColor = Magenta;
			colorChoice.c1 = 1.0;
			colorChoice.c2 = 0.0;
			colorChoice.c3 = 1.0;
			break;
		case 6:
			currentColor = Yellow;
			colorChoice.c1 = 1.0;
			colorChoice.c2 = 1.0;
			colorChoice.c3 = 0.0;
			break;
		case 7:
			currentColor = White;
			colorChoice.c1 = 1.0;
			colorChoice.c2 = 1.0;
			colorChoice.c3 = 1.0;
			break;
		case 8:
			currentColor = Black;
			colorChoice.c1 = 0.0;
			colorChoice.c2 = 0.0;
			colorChoice.c3 = 0.0;
			break;
		case 0:
			break;
	}
}