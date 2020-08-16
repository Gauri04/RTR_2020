#include<GL/freeglut.h>
#include<cmath>
#include<stdio.h>
#include<windows.h>
#include<mmsystem.h>
#pragma comment(lib, "winmm.lib")


//global variables declarations
bool bFullScreen = true;
const float pi = 3.142f;
float moveX = 3.70f;
float moveY = 1.8f;
int flagMoonMove = 0;
bool bDay = false;
float colorNight = 0.0f;
float colorGreen = 0.0f;
float colorRed = 0.0f;
float colorSun = 0.0f;
float moonSunY = -1.6f;
float colorLand = 0.0f;
float colorBlue = 0.0f;
bool bClouds = false; 
FILE *fp;
//GLuint textureMoon; 


int main(int argc, char **argv)
{
	// function prototypes
	void display(void);
	void resize(int, int);
	void keyboard(unsigned char, int, int);
	void mouse(int, int, int, int);
	void initialize(void);
	void uninitialize(void);
	void move(void);
	
	//code
	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	
	
	glutInitWindowSize(800, 600); // declare initial window position
	
	glutCreateWindow("Pract1");
	
	initialize();
	
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutIdleFunc(move);
	glutCloseFunc(uninitialize);
	
	glutMainLoop();
	
	return(0); // Process will never come here. This stmt just for understanding
}

void display(void)
{	
	
	if(bDay == false)
	{
		//code
		glClearColor(colorRed, colorGreen, colorBlue, 0.0f);
		//to clear all pixels
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Stars	
		glLoadIdentity();
		glTranslatef(-6.0f, -2.0f, -6.0f);
		glScalef(0.3f, 0.3f, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glLineWidth(3.0f);
		for(int i=0; i < 10000; i++)
		{
		
			glBegin(GL_LINES);
			int x = rand() % 1366;
			int y = rand() % 768;
			glVertex2f(x, y);
			glVertex2f(x -0.19f, y + 0.19f);
			
			glVertex2f(x - 0.19f, y);
			glVertex2f(x, y + 0.19f);
			glEnd();
			
		}
	
		// Moon
		glLoadIdentity();
		glTranslatef(3.0f, moonSunY, -6.0f);
		glScalef(0.3f, 0.3f, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_TRIANGLE_STRIP);

			for(float i = 0; i <= 2*pi*1; i = i + 0.01f)
			{
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f((1*cos(i)), (1*sin(i)), 0.0f);
			}
		glEnd();
		
		glLoadIdentity();
		glTranslatef(3.0f, moonSunY, -6.0f);
		glScalef(0.28f, 0.28f, 0.0f);
		glColor3f(0.8f, 0.8f, 0.8f);
		glBegin(GL_TRIANGLE_STRIP);

			for(float i = 0; i <= 2*pi*1; i = i + 0.01f)
			{
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f((1*cos(i)), (1*sin(i)), 0.0f);
			}
		glEnd();
		
		//Line covers 290 degree of moon's uncolored part

		glLineWidth(2.0f);
		glBegin(GL_LINES);
			glVertex2f(0.0f, 0.0f);
			glVertex2f(1.0f, 0.0f);
		glEnd();
			
			
			
		//Phases of moon
		/*
		glLoadIdentity();
		glTranslatef(moveX, moonSunY, -6.0f);
		glScalef(0.31f, 0.31f, 0.0f);
		glColor3f(0.0f, 0.0f, colorNight);
		glBegin(GL_TRIANGLE_STRIP);
			for(float i = 0; i <= 2*pi*1; i = i + 0.01f)
			{
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f((1*cos(i)), (1*sin(i)), 0.0f);
			}
		glEnd();
		//Line covers 290 degree of moon's uncolored part
		glColor3f(0.0f, 0.0f, colorNight);
		glLineWidth(2.0f);
		glBegin(GL_LINES);
			glVertex2f(0.0f, 0.0f);
			glVertex2f(1.0f, 0.0f);
		glEnd();
		
		*/
	
	}
	
	else if(bDay == true)
	{
		glClearColor(colorRed, colorGreen, colorBlue, 0.0f);
		//to clear all pixels
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// Sun3
		glLoadIdentity();
		glTranslatef(-2.8f, moonSunY, -6.0f);
		glScalef(0.3f, 0.3f, 0.0f);
		glColor3f(1.0f, 0.5f, 0.0f);
		glBegin(GL_TRIANGLE_STRIP);

			for(float i = 0; i <= 2*pi*1; i = i + 0.01f)
			{
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f((1*cos(i)), (1*sin(i)), 0.0f);
			}
		glEnd();
		
		glColor3f(1.0f, 1.0f, 0.0f);
		glBegin(GL_LINES);
			glVertex2f(0.0f, 0.0f);
			glVertex2f(1.0f, 0.0f);
		glEnd();
		
		
		// Sun2
		glLoadIdentity();
		glTranslatef(-2.8f, moonSunY, -6.0f);
		glScalef(0.28f, 0.28f, 0.0f);
		glColor3f(1.0f, 0.9f, 0.0f);
		glBegin(GL_TRIANGLE_STRIP);

			for(float i = 0; i <= 2*pi*1; i = i + 0.01f)
			{
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f((1*cos(i)), (1*sin(i)), 0.0f);
			}
		glEnd();
		
		//Sun1
		glLoadIdentity();
		glTranslatef(-2.8f, moonSunY, -6.0f);
		glScalef(0.27f, 0.27f, 0.0f);
		glColor3f(1.0f, 1.0f, 0.0f);
		glBegin(GL_TRIANGLE_STRIP);

			for(float i = 0; i <= 2*pi*1; i = i + 0.01f)
			{
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f((1*cos(i)), (1*sin(i)), 0.0f);
			}
		glEnd();
		
		if(bClouds == true)
		{
			// 1st cloud
			glColor4f(1.0f, 1.0f, 1.0f, 0.9f);
			
			glLoadIdentity();
			glTranslatef(0.4f, 1.5f, -6.0f);
			glScalef(0.27f, 0.27f, 0.0f);
			glBegin(GL_TRIANGLE_STRIP);
				for(float i = 0; i <= 2*pi*1; i = i + 0.01f)
				{
					glVertex3f(0.0f, 0.0f, 0.0f);
					glVertex3f((1*cos(i)), (1*sin(i)), 0.0f);
				}
			glEnd();
			
			glLoadIdentity();
			glTranslatef(0.8f, 1.5f, -6.0f);
			glScalef(0.27f, 0.27f, 0.0f);
			glBegin(GL_TRIANGLE_STRIP);
				for(float i = 0; i <= 2*pi*1; i = i + 0.01f)
				{
					glVertex3f(0.0f, 0.0f, 0.0f);
					glVertex3f((1*cos(i)), (1*sin(i)), 0.0f);
				}
			glEnd();
			
			glLoadIdentity();
			glTranslatef(1.1f, 1.4f, -6.0f);
			glScalef(0.25f, 0.27f, 0.0f);
			glBegin(GL_TRIANGLE_STRIP);
				for(float i = 0; i <= 2*pi*1; i = i + 0.01f)
				{
					glVertex3f(0.0f, 0.0f, 0.0f);
					glVertex3f((1*cos(i)), (1*sin(i)), 0.0f);
				}
			glEnd();
			
			glLoadIdentity();
			glTranslatef(0.75f, 1.35f, -6.0f);
			glScalef(0.25f, 0.27f, 0.0f);
			glBegin(GL_TRIANGLE_STRIP);
				for(float i = 0; i <= 2*pi*1; i = i + 0.01f)
				{
					glVertex3f(0.0f, 0.0f, 0.0f);
					glVertex3f((2.15*cos(i)), (1*sin(i)), 0.0f);
				}
			glEnd();
			
			glLineWidth(2.0f);
			glBegin(GL_LINES);
				glVertex2f(0.0f, 0.0f);
				glVertex2f(2.3f, 0.0f);
			glEnd();
			
			
			// 2nd cloud
			glColor3f(1.0f, 1.0f, 1.0f);
			
			glLoadIdentity();
			glTranslatef(2.4f, 1.7f, -6.0f);
			glScalef(0.23f, 0.23f, 0.0f);
			glBegin(GL_TRIANGLE_STRIP);
				for(float i = 0; i <= 2*pi*1; i = i + 0.01f)
				{
					glVertex3f(0.0f, 0.0f, 0.0f);
					glVertex3f((1*cos(i)), (1*sin(i)), 0.0f);
				}
			glEnd();
			
			glLoadIdentity();
			glTranslatef(2.7f, 1.6f, -6.0f);
			glScalef(0.23f, 0.23f, 0.0f);
			glBegin(GL_TRIANGLE_STRIP);
				for(float i = 0; i <= 2*pi*1; i = i + 0.01f)
				{
					glVertex3f(0.0f, 0.0f, 0.0f);
					glVertex3f((1*cos(i)), (1*sin(i)), 0.0f);
				}
			glEnd();
			
			glLoadIdentity();
			glTranslatef(3.0f, 1.55f, -6.0f);
			glScalef(0.21f, 0.21f, 0.0f);
			glBegin(GL_TRIANGLE_STRIP);
				for(float i = 0; i <= 2*pi*1; i = i + 0.01f)
				{
					glVertex3f(0.0f, 0.0f, 0.0f);
					glVertex3f((1*cos(i)), (1*sin(i)), 0.0f);
				}
			glEnd();
			
			glLoadIdentity();
			glTranslatef(2.7f, 1.53f, -6.0f);
			glScalef(0.21f, 0.23f, 0.0f);
			glBegin(GL_TRIANGLE_STRIP);
				for(float i = 0; i <= 2*pi*1; i = i + 0.01f)
				{
					glVertex3f(0.0f, 0.0f, 0.0f);
					glVertex3f((2.25*cos(i)), (1*sin(i)), 0.0f);
				}
			glEnd();
						
		}
		

	}
	
	//Land / grass hill
	//1 border
	glLoadIdentity();
	glTranslatef(-3.0f, -2.0f, -6.0f);
	glScalef(1.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 0.2f, 0.0f);
	glBegin(GL_TRIANGLE_STRIP);

			for(float i = 0; i <= 2*pi*1; i = i + 0.01f)
			{
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f((2.5*cos(i)), (1*sin(i)), 0.0f);
			}
	glEnd();
	
	//2 border
	glLoadIdentity();
	glTranslatef(2.6f, -2.0f, -6.0f);
	glScalef(1.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 0.2f, 0.0f);
	glBegin(GL_TRIANGLE_STRIP);

		for(float i = 0; i <= 2*pi*1; i = i + 0.01f)
		{
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f((4.0*cos(i)), (1*sin(i)), 0.0f);
		}
	glEnd();
	
	//3 border
	glLoadIdentity();
	glTranslatef(-1.0f, -2.0f, -6.0f);
	glScalef(1.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 0.2f, 0.0f);
	glBegin(GL_TRIANGLE_STRIP);

		for(float i = 0; i <= 2*pi*1; i = i + 0.01f)
		{
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f((3.0*cos(i)), (1.5*sin(i)), 0.0f);
		}
	glEnd();
	
	
	
	//1
	glLoadIdentity();
	glTranslatef(-3.0f, -2.0f, -6.0f);
	glColor3f(0.0f, colorLand, 0.0f);
	glScalef(0.99f, 0.99f, 0.0f);
	glBegin(GL_TRIANGLE_STRIP);

			for(float i = 0; i <= 2*pi*1; i = i + 0.01f)
			{
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f((2.5*cos(i)), (1*sin(i)), 0.0f);
			}
	glEnd();
	

	//2
	glLoadIdentity();
	glTranslatef(2.6f, -2.0f, -6.0f);
	glColor3f(0.0f, colorLand, 0.0f);
	glScalef(0.99f, 0.99f, 0.0f);
	glBegin(GL_TRIANGLE_STRIP);

		for(float i = 0; i <= 2*pi*1; i = i + 0.01f)
		{
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f((4.0*cos(i)), (1*sin(i)), 0.0f);
		}
	glEnd();
	
	
	//3
	glLoadIdentity();
	glTranslatef(-1.0f, -2.0f, -6.0f);
	glColor3f(0.0f, colorLand, 0.0f);
	glScalef(0.99f, 0.99f, 0.0f);
	glBegin(GL_TRIANGLE_STRIP);

		for(float i = 0; i <= 2*pi*1; i = i + 0.01f)
		{
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f((3.0*cos(i)), (1.5*sin(i)), 0.0f);
		}
	glEnd();
	
	
	glutSwapBuffers();
	//glutPostRedisplay();	
	
}	

void initialize(void)
{	
	fp = fopen("logs.txt", "w");
	//glutFullScreen();
	PlaySound("Finding_Nemo_Finding_Dory_Soundtrack.wav", NULL, SND_FILENAME | SND_ASYNC);
	// function declaration
	/*int LoadGLTextures(GLuint *, TCHAR[]);
	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	LoadGLTextures(&textureMoon, MAKEINTRESOURCE(IDBITMAP_MOON));
	fprintf(fp, "\n Loaded texture : %lu", textureMoon);
	glEnable(GL_TEXTURE_2D);
	*/
}

/*
int LoadGLTextures(GLuint *texture, TCHAR imageResourceId[])
{
	HBITMAP hBitmap;
	BITMAP bmp;
	int iStatus = FALSE;
	
	glGenTextures(1, texture);
	hBitmap = (HBITMAP)LoadImage(GetModuleHandle(NULL), imageResourceId, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	
	if(hBitmap)
	{
		iStatus = TRUE;
		GetObject(hBitmap, sizeof(bmp), &bmp);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		glBindTexture(GL_TEXTURE_2D, *texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, bmp.bmWidth, bmp.bmHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, bmp.bmBits);
		DeleteObject(hBitmap);
	}
	return(iStatus);
}
*/

void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 27:
			glutLeaveMainLoop();
			break;
			
		case 'F':
		case 'f':
			if(bFullScreen == false)
			{
				glutFullScreen();
				bFullScreen = true;
			}
			else
			{
				glutLeaveFullScreen();
				bFullScreen = false;
			}
			break;

		default:
			break;
	}
}

void mouse(int button, int state, int x, int y)
{
	switch(button)
	{
		case GLUT_LEFT_BUTTON:
			break;
			
		default:
			break;
	}
}

void resize(int width, int height)
{
	if(height == 0)
		height = 1;
	
	glViewport(0, 0, (GLsizei) width, (GLsizei)height);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluPerspective(45.0f, (GLfloat) width / (GLfloat) height, 0.1f, 100.0f);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
}

void uninitialize(void)
{
	//code
	fclose(fp);
}

void move(void)
{
	if(colorLand <= 1.0f)
		colorLand = colorLand + 0.00015f;
	
	// start day when color gets black 
	
	if(bDay == true)
	{
		if(moonSunY < 0.9f)
		{
			//colorBlue = colorBlue - 0.006f;
			colorRed = colorRed + 0.001f;
			colorGreen = colorGreen + 0.0004f;
			moonSunY = moonSunY + 0.003f;
		}
		else
		{
			
			if(colorBlue < 0.8f)
			{
				colorBlue = colorBlue + 0.0035f;
				colorRed = colorRed - 0.0035f;
				moonSunY = moonSunY + 0.003f;
			}
			else
			{
				bClouds = true;
			}
		}
	}
	else															// code for night
	{
		
		if(moonSunY < 2.8f)
		{
			colorRed = colorRed + 0.00005f;
			colorGreen = colorGreen + 0.00005f;
			colorBlue = colorBlue + 0.00005f;
			moonSunY = moonSunY + 0.003f;
		}
		else
		{
			bDay = true;
			moonSunY = -1.8f;
			fprintf(fp, "\n bDay became true");
		}
		/*
		if(flagMoonMove == 1)
		{
			if(moveX <= 3.7f)
				moveX = moveX + 0.0005f;
			//fprintf(fp, "\n In first if moveX : %f", moveX);
		}
	
		else if(moveX > 3.0f)
		{
			moveX = moveX - 0.0005f;
			//fprintf(fp, "\n In second if moveX : %f", moveX);
		}
		else
		{
			flagMoonMove = 1;
			fprintf(fp, "\n in else, moveX : %f", moveX);
		}
		*/
	
	}
	
	
	glutPostRedisplay();
}

/* comands :
cl.exe /c /EHsc /I C:\freeglut\include pract1.cpp

link.exe pract1.obj /LIBPATH:C:\freeglut\lib /SUBSYSTEM:CONSOLE

pract1.exe
*/


	
	