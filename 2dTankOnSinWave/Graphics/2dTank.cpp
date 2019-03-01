#include "GLUT.H"
#include <math.h>

// Sergei
// tank moving to the Right and shooting to the Left corner each tank location set to give A moving filling
// ask'd and show'd to Victor he told me it's Great ^^

const double PI = 3.14;
double offset = 0;
double offsetSin = 0;
//Bullet Attribute's
int Force = 2;  //10 N 
double bxStart, byStart, vx, vy, a = -0.35, t;
//on the Move Attribue's
double bulletx,bullety;
//Shooting proccess
boolean shootFired = false;
boolean colition = false;
// Save object Degree all the Time
double mainDegree;
// Save object Y location on Wave all the time
double sinYlocation;
// timer for Explosion
double timerExplosion = 0;
//tank Location on X
double tankLocationX = 0.3;

void init()
 {
	glClearColor(0.0,0.0,0.6,0); // sets baclground color 
	glOrtho(-1, 1, -1, 1, 1, -1);
}



void DrawWheel()
{
	double alpha, teta = PI/30;
	double x, y;

	glBegin(GL_LINE_LOOP);
	for (alpha = 0; alpha < 2 * PI; alpha += teta)
	{
		x = cos(alpha);
		y = sin(alpha);
		glVertex2d(x, y);
	}
	glEnd();

	teta = PI / 8;
	glBegin(GL_LINE_LOOP);
	for (alpha = 0; alpha < 2 * PI; alpha += teta)
	{
		x = cos(alpha);
		y = sin(alpha);
		glVertex2d(x, y);
		glVertex2d(0, 0);
	}
	glEnd();

}

void drawTank()
{
	double i;
	// front wheel
	for (i = -0.3; i <= 0.31; i += 0.2)
	{
		glPushMatrix();
		glTranslated(i, 0, 0);
		glScaled(0.1, 0.1, 1);
		glRotated(offset, 0, 0, 1); // offset is in dgrees
		DrawWheel();
		glPopMatrix();
	}
	// Second Wheel on the Side (1)
	glPushMatrix();
	glTranslated(0.41, 0.11, 0);
	glScaled(0.04, 0.04, 1);
	glRotated(offset, 0, 0, 1); // offset is in dgrees
	DrawWheel();
	glPopMatrix();
	// Second Wheel on the Side (2)
	glPushMatrix();
	glTranslated(-0.41, 0.11, 0);
	glScaled(0.04, 0.04, 1);
	glRotated(offset, 0, 0, 1); // offset is in dgrees
	DrawWheel();
	glPopMatrix();
	// Second Wheel on the Side (2)
	for (i = -0.2; i <= 0.2; i += 0.2)
	{
		glPushMatrix();
		glTranslated(i, 0.12, 0);
		glScaled(0.03, 0.03, 1);
		glRotated(offset, 0, 0, 1); // offset is in dgrees
		DrawWheel();
		glPopMatrix();
	}
	// shilda (TANK)
	glLineWidth(2);
	glColor3d(1, 1, 1);
	glBegin(GL_LINES);
		glVertex2d(-0.48,0.15);     //1
		glVertex2d(0.48, 0.15);     //1
		glVertex2d(0.48, 0.15);     //2
		glVertex2d(0.38, -0.08);    //2
		glVertex2d(-0.48, 0.15);    //3
		glVertex2d(-0.38, -0.08);   //3
		glVertex2d(-0.38, -0.08);   //4
		glVertex2d(0.38, -0.08);    //4
	glEnd();
	// Tank Head
	glLineWidth(1);
	glBegin(GL_LINES);
	glVertex2d(-0.20, 0.22);     //head
	glVertex2d(0.33, 0.22);     //head
	glVertex2d(-0.20, 0.22);     //left close head
	glVertex2d(-0.33, 0.15);     //left close head
	glVertex2d(0.33, 0.22);     //left close head
	glVertex2d(0.36, 0.15);     //left close head
	//tank Head second tower
	glVertex2d(-0.08, 0.33);     //head
	glVertex2d(0.28, 0.33);     //head
	glVertex2d(-0.08, 0.33);     //left close head
	glVertex2d(-0.18, 0.22);     //left close head
	glVertex2d(0.28, 0.33);     //left close head
	glVertex2d(0.31, 0.22);     //left close head
	glEnd();
	// Tank Gun (Cannon)
	glBegin(GL_LINES);
	glVertex2d(-0.22, 0.21);     //canon Bottom
	glVertex2d(-0.78, 0.28);     //canon Bottom
	glVertex2d(-0.15, 0.25);     //canon Top
	glVertex2d(-0.77, 0.32);     //canon Top
	glVertex2d(-0.78, 0.28);     //canon Close
	glVertex2d(-0.77, 0.32);     //canon Close

	glEnd();


}

void drawSinWave()
{
	double x, y;
	glColor3d(0, 0, 0.4);
	glLineWidth(2);
	glBegin(GL_LINE_STRIP);// GL_LINES);//GL_POINTS);
	for (x = -1; x <= 1; x += 0.01)
	{
		y = sin(4 * x + offsetSin)*0.15;
		glColor3d(1, 1, 1);
		glVertex2d(x, y);




	}
	glEnd();
}

void drawExplosion()
{
	//basic Circle .
	double alpha, teta = PI / 30;
	double x, y;
	glBegin(GL_POLYGON);
	for (alpha = 0; alpha < 2 * PI; alpha += teta)
	{
		x = cos(alpha);
		y = sin(alpha);
		glVertex2d(x, y);
	}
	glEnd();
}
void shootGo(double degree, double x, double y)
{
	double xx, yy, sinY;
	sinY = y - 0.034; // getting Y wave 
	xx = (-0.77*0.3*cos(degree)) - (0.30*0.3*sin(degree));  // Doing Algebra Rotation Location on Matrix (BIG) 0.77 Scale 0.3 = 0.77*0.3 -> Y 0.3 location (BIG) * scale (all compared to Degree)
	yy = (-0.77*0.3*sin(degree)) + (0.30*0.3*cos(degree));  // Doing Algebra Rotation Location on Matrix (BIG) 0.77 Scale 0.3 = 0.77*0.3 -> Y 0.3 location (BIG) * scale (all compared to Degree)
	xx = xx + x; // Getting X on matrix (Compared to 0) + adding Postion Start (Main Matrix 0.3)
	yy = yy + y;  // got yy on big matrix adding small y movment (WAVE)

	// shoot process setting Start + setting vector's and Timer
	bxStart = xx;
	byStart = yy;
	vx = Force* cos(degree);
	vy = Force* sin(degree);
	t = 0;

}
void explosion()
{
	double yy;
	// getting YY location of the Wave Important for Explosion Movment.
	// 3 Explosion's Red/Yellow/White
	//3
	yy = (sin(4 * bulletx + offsetSin)) *0.15;
	glPushMatrix();
	glColor3d(1 - timerExplosion, 0, 0);
	glTranslated(bulletx, yy, 0);
	glScaled(0.1 - (timerExplosion*0.1), 0.1 - (timerExplosion*0.1), 1);
	drawExplosion();
	glPopMatrix();
	//2
	glPushMatrix();
	glColor3d(1 - timerExplosion, 1 - timerExplosion, 0);
	glTranslated(bulletx, yy, 0);
	glScaled(0.07 - (timerExplosion*0.07), 0.07 - (timerExplosion*0.07), 1);
	drawExplosion();
	glPopMatrix();
	//1
	glPushMatrix();
	glColor3d(1 - timerExplosion, 1 - timerExplosion, 1 - timerExplosion);
	glTranslated(bulletx, yy, 0);
	glScaled(0.03 - (timerExplosion*0.03), 0.03 - (timerExplosion*0.03), 1);
	drawExplosion();
	glPopMatrix();
}
void keyBoard(unsigned char key, int x, int y)
{
	// able to Fire only When Object is Not flying already and colition is Over. (Letting the Fire finish!) 
	if (key == ' ' && shootFired ==false && colition == false)
	{
		shootFired = true;
		colition = false;
		//Enter the Shoot (give's vector and starting location and so on setting the Fire)
		shootGo(mainDegree*PI / 180, tankLocationX, sinYlocation); // degree (RADIAN) of the Object so we can know x y + added the main stat's. Tank location 0.3 sinYlocation his Y location.

	}
}

void display()
{
	double y,yOne,yTwo,degree,yy;
	glClear(GL_COLOR_BUFFER_BIT); // loads background color

	glLoadIdentity(); // start transformations matrix from the identity
	glColor3d(1, 1, 1);
	// have 2 points yOne yTwo (Changing) and xOne xTwo (xOne = 0.165 xTwo = 0.43)
	yOne =(sin(4 * 0.165 + offsetSin))*0.15;
	yTwo = (sin(4 * 0.43 + offsetSin))*0.15;
	// y for Sin wave.
	y = 0.034+ (sin(4 * 0.3 + offsetSin)) *0.15;
	sinYlocation = y;
	// degree of the tank on sin wave
	degree = asin((yOne - yTwo) / (0.165 - 0.43)) * 180 / PI;
	mainDegree = degree;
	glPushMatrix();
		glTranslated(0.3,y, 0);
		glScaled(0.3 ,0.3, 1);
		glRotated(degree, 0, 0, 1);
		drawTank();
	glPopMatrix();
	// SinWave
	drawSinWave();
	// Tank Shoot
	if (shootFired == true)
	{
		glPushMatrix();
		glTranslated(bulletx, bullety, 0);
		glScaled(0.01, 0.01, 1);
		DrawWheel(); // in small scale it's just a round object like Bullet 
		glPopMatrix();
	}
	// Bullet Collided with SinWave
	if (colition == true)
	{
		explosion();

		bulletx -= 0.01; // move X so Mov With Wave
		if (bulletx <= -1 || timerExplosion >= 1) // If Bullet Explosion whent out from screen Before Timer + Timer in side
		{
			colition = false;
		}
	}

	glutSwapBuffers();
}

void idle()
{
	double yBullerSinLocation;
	offset -= 1; // offset used for Wheels so can see moving faster 0.01 Sin is 2 slow for him to see (- to my move direction)
	if (shootFired == true)
	{
		//Main movement calculation
		t += 0.01;
		bulletx = bxStart - vx*t;
		bullety = byStart - vy*t + a*t*t;
		yBullerSinLocation = (sin(4 * bulletx + offsetSin)) *0.15;
		//know sin wave locaion (y) when bullet moving on x..
		if (bullety <= yBullerSinLocation) // if colision detected.
		{
			shootFired = false;
			colition = true;
			timerExplosion = 0;
		}
		else if (bulletx <= -1) // bullet fly wall.
		{
			shootFired = false;
		}
	}
	if (colition == true) // collition Timer.
	{
		timerExplosion += 0.02;
	}

	offsetSin += 0.01;
	glutPostRedisplay(); // indirect call to display
}
void main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(200, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Graphics example");

	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyBoard);
	init();
	glutMainLoop();
}