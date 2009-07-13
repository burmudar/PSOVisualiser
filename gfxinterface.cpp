#include <iostream>
#include <iomanip>
#include "gfxmath.h"
#include "PSOStructures.h"
#include "../ChartPlotter/Chart2DPlotter.cpp"
#include <sstream>
#include <vector>
#include <cmath>
#include <GL/gl.h>
#include <GL/glu.h>
#include "SDL.h"

#define SCREEN_BPP 16
#define TRUE 1
#define FALSE 0

using namespace std;
//Global variables

bool draw = true;

float xrot = 0.0f;
float yrot = 0.0f;
float zrot = 0.0f;
float xtrans = 0.0f;
float ytrans = 0.0f;
float dist = 40.0f;
float tick = 0.05f;
const int PARTICLES = 15000;
const bool FULLSCREEN = false;
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;
const int TOTALFUNCTIONCOUNT = 17;
enum movement{STOP=0,LEFT=1,RIGHT=2,UP=3,DOWN=4};
Chart2DPlotter chart(SCREEN_WIDTH*0.70,SCREEN_HEIGHT*0.70,SCREEN_WIDTH,SCREEN_HEIGHT,20);
movement KEY;
int shape =1;
int FUNCTION = 17;
GraphicalPSO pso = GraphicalPSO(PARTICLES,FUNCTION,0.41,0.52); 

GLuint base;
GLuint texture[1];

SDL_Surface *surface;

GLvoid KillFont()
{
	glDeleteLists(base,256);
}

void Quit(int returnCode)
{
	SDL_Quit();

	exit(returnCode);
}

void ReSizeGLScene(int width,int height)
{
	if (height == 0)
		height = 1;
	GLfloat ratio = static_cast<GLfloat>(width) / static_cast<GLfloat>(height);
	glViewport(0,0, width,height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f,ratio,0.1f,100.0f);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

bool LoadFontTexture()
{
	SDL_Surface *TextureImage[1];
	bool status = false;
	TextureImage[0] = SDL_LoadBMP("font/font.bmp");
	if (TextureImage[0] != NULL)
	{
		status = true;
		glGenTextures(1,&texture[0]);

		glBindTexture(GL_TEXTURE_2D, texture[0]);

	    glTexImage2D( GL_TEXTURE_2D, 0, 3, TextureImage[0]->w,
			  TextureImage[0]->h, 0, GL_BGR,
			  GL_UNSIGNED_BYTE, TextureImage[0]->pixels );


		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	}
	if (TextureImage[0]!=NULL)
		SDL_FreeSurface(TextureImage[0]);
	return status;
}

GLvoid BuildFont()
{
	float cx;
	float cy;

	base = glGenLists(256);

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	for(unsigned int i=0; i < 256; i++)
	{
		//We move from bottom right to left, since the BMP data is RAW loaded
		cx = 1 - (float)(i % 16) / 16.0f;
		cy = 1 - (float)(i / 16) / 16.0f;

		glNewList(base + (255 - i), GL_COMPILE);
		/* Use A Quad for each character 1/16 (1 character of 16x16 pixels) = 0.0625 */
		glBegin(GL_QUADS);
			//Texture coorid bottom left
			glTexCoord2d(cx - 0.0625, cy);
			//Vertex coord bottom left
			glVertex2i(0,0);
			//Texture coord bottom right
			glTexCoord2d(cx,cy);
			//Vertex coord bottom right
			glVertex2i(16,0);
			//Texture coord Top right
			glTexCoord2d(cx,cy - 0.0625);
			//Vertex coord Top right
			glVertex2i(16,16);
			//Texture coord Top Left
			glTexCoord2d(cx - 0.0625, cy - 0.0625);
			//Vertex coord Top left
			glVertex2i(0,16);
		glEnd();
		glTranslatef(10,0,0);
		glEndList();
	}
}

void setPerspective(const int FUNCTION)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	switch(FUNCTION)
	{
		case 1:
			{
				gluPerspective(45.0f,(GLfloat)SCREEN_WIDTH/(GLfloat)SCREEN_HEIGHT,0.1f,100.0f);
				dist =40;
				tick = 0.05;
			}
			break;
		case 2:
			{
				gluPerspective(45.0f,(GLfloat)SCREEN_WIDTH/(GLfloat)SCREEN_HEIGHT,0.1f,8000.0f);
				dist = 200;
				tick = 20;
			}
			break;
		case 3:
			{
				gluPerspective(45.0f,(GLfloat)SCREEN_WIDTH/(GLfloat)SCREEN_HEIGHT,0.1f,8000.0f);
				dist = 100;
				tick = 1;
			}
			break;
		case 4:
			{
				gluPerspective(45.0f,(GLfloat)SCREEN_WIDTH/(GLfloat)SCREEN_HEIGHT,0.1f,100.0f);
				dist = 40;
				tick = 0.05;
			}
			break;
		case 5:
			{
				gluPerspective(45.0f,(GLfloat)SCREEN_WIDTH/(GLfloat)SCREEN_HEIGHT,0.1f,5000.0f);
				dist = 1000;
				tick = 20;
			}
			break;
		case 6:
			{
				gluPerspective(45.0f,(GLfloat)SCREEN_WIDTH/(GLfloat)SCREEN_HEIGHT,0.1f,5000.0f);
				dist = 1000;
				tick = 20;
			}
			break;
		case 7:
			{
				gluPerspective(45.0f,(GLfloat)SCREEN_WIDTH/(GLfloat)SCREEN_HEIGHT,0.1f,5000.0f);
				dist = 1000;
				tick = 20;
			}
			break;
		case 8:
			{
				gluPerspective(45.0f,(GLfloat)SCREEN_WIDTH/(GLfloat)SCREEN_HEIGHT,0.1f,5000.0f);
				dist = 1000;
				tick = 20;
			}
			break;
		case 9:
			{
				gluPerspective(45.0f,(GLfloat)SCREEN_WIDTH/(GLfloat)SCREEN_HEIGHT,0.1f,100.0f);
				dist = 15;
				tick = 0.05;
			}
			break;
		case 10:
			{
				gluPerspective(45.0f,(GLfloat)SCREEN_WIDTH/(GLfloat)SCREEN_HEIGHT,0.1f,100.0f);
				dist = 45;
				tick = 15;
			}
			break;
		case 11:
			{
				gluPerspective(45.0f,(GLfloat)SCREEN_WIDTH/(GLfloat)SCREEN_HEIGHT,0.1f,100.0f);
				dist = 45;
				tick = 15;
			}
			break;
		case 12:
			{
				gluPerspective(45.0f,(GLfloat)SCREEN_WIDTH/(GLfloat)SCREEN_HEIGHT,0.1f,100.0f);
				dist = 15;
				tick = 0.05;
			}
			break;
		case 13:
			{
				gluPerspective(45.0f,(GLfloat)SCREEN_WIDTH/(GLfloat)SCREEN_HEIGHT,0.1f,200.0f);
				dist = 85;
				tick = 0.05;
			}
			break;
		case 14:
			{
				gluPerspective(45.0f,(GLfloat)SCREEN_WIDTH/(GLfloat)SCREEN_HEIGHT,0.1f,200.0f);
				dist = 85;
				tick = 0.05;
			}
			break;
		case 15:
			{
				gluPerspective(45.0f,(GLfloat)SCREEN_WIDTH/(GLfloat)SCREEN_HEIGHT,0.1f,5000.0f);
				dist = 1000;
				tick = 20;
			}
			break;
		case 16:
			{
				gluPerspective(45.0f,(GLfloat)SCREEN_WIDTH/(GLfloat)SCREEN_HEIGHT,0.1f,200.0f);
				dist = 15;
				tick = 0.05;
			}
			break;
		case 17:
			{
				gluPerspective(45.0f,(GLfloat)SCREEN_WIDTH/(GLfloat)SCREEN_HEIGHT,0.1f,800.0f);
				dist = 75;
				tick = 1.05;
			}
			break;
	}
	
	glMatrixMode(GL_MODELVIEW);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

int InitGL(const int FUNCTION)
{
	if (!LoadFontTexture()) return -1;

	BuildFont();
	glClearColor(0.0f,0.0f,0.0f,0.0f);

	glClearDepth(1.0f);

	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);

    glBlendFunc( GL_SRC_ALPHA, GL_ONE );
	glShadeModel(GL_SMOOTH);
	
	setPerspective(FUNCTION);

	return TRUE;
}

void keyPressed(SDL_keysym *keysym)
{
	switch(keysym->sym)
	{
		case SDLK_ESCAPE:
			Quit(0);
			break;
		case SDLK_F1:
			draw = !draw;	
			chart.Clear();
			break;
		case SDLK_F2:
			pso.draw_best = !pso.draw_best;
			break;
		case SDLK_F3:
			pso.draw_normal = !pso.draw_normal;
			break;
		case SDLK_F4:
			{
				FUNCTION++;
				if(FUNCTION > TOTALFUNCTIONCOUNT) FUNCTION = 1;
				setPerspective(FUNCTION);
				pso.setFunction(FUNCTION);
			}
			break;
		case SDLK_F12:
			{
				if (shape == 3) shape = 1;
				else shape++;
			}
			break;
		case SDLK_a:
			{
				KEY = LEFT;
			}
			break;
		case SDLK_d:
			{
				KEY = RIGHT;
			}
			break;
		case SDLK_w:
			{
				KEY = UP;
			}
			break;
		case SDLK_s:
			{
				KEY = DOWN;
			}
			break;
		default:
			break;
	}
	return;
}


void HUDMode(bool flag)
{
	if (flag)
	{
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(0,SCREEN_WIDTH,0,SCREEN_HEIGHT);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glDisable(GL_DEPTH_TEST);
	}
	else
	{
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
		glEnable(GL_DEPTH_TEST);
	}
}

void glPrintHUDInfo(GLint xbound, GLint ybound,int fps)
{
	glColor3f(1.0,1.0,1.0);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glListBase(base -32 + (128 * 0));
	glTranslated(0,ybound-2-16,0);
	ostringstream out;
	string msg;
	out << "FPS:";
	msg = out.str();
	glCallLists(strlen(msg.c_str()), GL_BYTE, msg.c_str());
	out.str("");
	out << fps;
	msg = out.str();
	glColor3f(0.0,0.0,1.0);
	glCallLists(strlen(msg.c_str()), GL_BYTE, msg.c_str());
	glLoadIdentity();
	glTranslated(5*16,ybound-2-16,0);//*16 -> each character is 16 pixels, so multiply the size of hte string with the pixel amount to get the next draw pos
	out.str("");
	out << "Particles:";
	msg = out.str();
	glColor3f(1.0,1.0,1.0);
	glCallLists(strlen(msg.c_str()), GL_BYTE, msg.c_str());
	out.str("");
	out << PARTICLES;
	msg = out.str();
	glColor3f(0.0,0.0,1.0);
	glCallLists(strlen(msg.c_str()), GL_BYTE, msg.c_str());
	glLoadIdentity();
	glTranslated(15*16,ybound-2-16,0);//*16 -> each character is 16 pixels, so multiply the size of hte string with the pixel amount to get the next draw pos
	out.str("");
	out << "Swarm Best Fitness:";
	msg = out.str();
	glColor3f(1.0,1.0,1.0);
	glCallLists(strlen(msg.c_str()), GL_BYTE, msg.c_str());
	out.str("");
	out <<setprecision(5) <<pso.global_best.fitness;
	msg = out.str();
	glColor3f(0.0,0.0,1.0);
	glCallLists(strlen(msg.c_str()), GL_BYTE, msg.c_str());
	glLoadIdentity();
	glTranslated(33.5*16,ybound-2-(16),0);//*16 -> each character is 16 pixels, so multiply the size of hte string with the pixel amount to get the next draw pos
	out.str("");
	out << "Swarm Best Position:";
	msg = out.str();
	glColor3f(1.0,1.0,1.0);
	glCallLists(strlen(msg.c_str()), GL_BYTE, msg.c_str());
	out.str("");
	out << pso.global_best.pos;
	msg = out.str();
	glColor3f(0.0,0.0,1.0);
	glCallLists(strlen(msg.c_str()), GL_BYTE, msg.c_str());
	glLoadIdentity();
	glTranslated(0*16,ybound-2-(16*2),0);//*16 -> each character is 16 pixels, so multiply the size of hte string with the pixel amount to get the next draw pos
	out.str("");
	gfxParticle particle = pso.getSelectedParticle();
	out << "Particle ID:";
	msg = out.str();
	glColor3f(1.0,1.0,1.0);
	glCallLists(strlen(msg.c_str()), GL_BYTE, msg.c_str());
	out.str("");
	out << particle.getUID();
	msg = out.str();
	glColor3f(0.0,1.0,0.0);
	glCallLists(strlen(msg.c_str()), GL_BYTE, msg.c_str());
	glLoadIdentity();
	glTranslated(15*16,ybound-2-(16*2),0);//*16 -> each character is 16 pixels, so multiply the size of hte string with the pixel amount to get the next draw pos
	out.str("");
	out << "Best Fitness:";
	msg = out.str();
	glColor3f(1.0,1.0,1.0);
	glCallLists(strlen(msg.c_str()), GL_BYTE, msg.c_str());
	out.str("");
	out <<setprecision(5)<< particle.getBestFitness();
	msg = out.str();
	glColor3f(0.0,1.0,0.0);
	glCallLists(strlen(msg.c_str()), GL_BYTE, msg.c_str());
	glLoadIdentity();
	glTranslated(33.5*16,ybound-2-(16*2),0);//*16 -> each character is 16 pixels, so multiply the size of hte string with the pixel amount to get the next draw pos
	out.str("");
	out << "Best Position:";
	msg = out.str();
	glColor3f(1.0,1.0,1.0);
	glCallLists(strlen(msg.c_str()), GL_BYTE, msg.c_str());
	out.str("");
	out << particle.getBestPosition();
	msg = out.str();
	glColor3f(0.0,1.0,0.0);
	glCallLists(strlen(msg.c_str()), GL_BYTE, msg.c_str());
	glLoadIdentity();
	glTranslated(0*16,ybound-2-(16*3),0);
	out.str("");
	out.str("STATE:");
	msg = out.str();
	glColor3f(1.0,1.0,1.0);
	glCallLists(strlen(msg.c_str()), GL_BYTE, msg.c_str());
	out.str("");
	if(draw == true) out << "PAUSED (Press <F1> to RUN)";
	else out << "RUNNING (Press <F1> to PAUSE)";
	msg = out.str();
	glColor3f(1.0,1.0,0.0);
	glCallLists(strlen(msg.c_str()), GL_BYTE, msg.c_str());
	out.str("");
	out << "Show Best(F2):";
	msg = out.str();
	glColor3f(1.0,1.0,1.0);
	glCallLists(strlen(msg.c_str()), GL_BYTE, msg.c_str());
	out.str("");
	if(pso.draw_best == true) out << "Yes";
	else out << "No";
	msg = out.str();
	glColor3f(1.0,1.0,0.0);
	glCallLists(strlen(msg.c_str()), GL_BYTE, msg.c_str());
	out.str("");
	out << " Show Normal(F3):";
	msg = out.str();
	glColor3f(1.0,1.0,1.0);
	glCallLists(strlen(msg.c_str()), GL_BYTE, msg.c_str());
	out.str("");
	if(pso.draw_normal == true) out << "Yes";
	else out << "No";
	msg = out.str();
	glColor3f(1.0,1.0,0.0);
	glCallLists(strlen(msg.c_str()), GL_BYTE, msg.c_str());
	glLoadIdentity();
	glTranslated(0,ybound-2-(16*4),0);
	out.str("");
	out<< "Optimzing Function:";
	msg = out.str();
	glColor3f(1.0,1.0,1.0);
	glCallLists(strlen(msg.c_str()), GL_BYTE, msg.c_str());
	out.str("");
	out << pso.functionName();
	msg = out.str();
	glColor3f(1.0,0.0,0.0);
	glCallLists(strlen(msg.c_str()), GL_BYTE, msg.c_str());
}

void DrawGLScene()
{
	static GLint Frames;
	static GLint T0;
	static GLfloat fps;
	GLint mode;
	GLfloat sizes[2];
	GLfloat step;

	glGetIntegerv(GL_RENDER_MODE,&mode);
	glGetFloatv(GL_POINT_SIZE_RANGE,sizes);
	glGetFloatv(GL_POINT_SIZE_GRANULARITY,&step);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_BLEND);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	switch(KEY)
	{
		case LEFT:
			xtrans += tick;
		break;
		case RIGHT:
			xtrans -= tick;
		break;
		case UP:
			ytrans -= tick;
		break;
		case DOWN:
			ytrans += tick;
		break;
		case STOP: break;
	}
	gluLookAt(xtrans,ytrans,dist,xtrans,ytrans,0.0,0.0,1.0,0.0);
	glRotatef(xrot,1.0,0.0,0.0);
	glRotatef(yrot,0.0,1.0,0.0);
	//Set point size
	//curSize = sizes[0]+5;
	//glPointSize(curSize);
	//Draw the particles
	pso.draw(mode,shape);	
	//draw HUD
	if (mode == GL_RENDER)
	{
		HUDMode(true);
		chart.DrawChart();
		glColor3f(1.0,1.0,1.0);
		//Top right box
		/*glBegin(GL_QUADS);
			glVertex2f(SCREEN_WIDTH*0.70,SCREEN_HEIGHT*0.70);
			glVertex2f(SCREEN_WIDTH,SCREEN_HEIGHT*0.70);
			glVertex2f(SCREEN_WIDTH,SCREEN_HEIGHT);
			glVertex2f(SCREEN_WIDTH*0.70,SCREEN_HEIGHT);
		glEnd();
		*/
		glColor3f(0,0,1);
		glBegin(GL_QUADS);
			glVertex2f(0,SCREEN_HEIGHT*0.10);
			glVertex2f(SCREEN_WIDTH,SCREEN_HEIGHT*0.10);
			glVertex2f(SCREEN_WIDTH,0);
			glVertex2f(0,0);
		glEnd();
		glColor3f(0,0,0);
		int boundaryThickness = 4;
		glBegin(GL_QUADS);
			glVertex2f(boundaryThickness,SCREEN_HEIGHT*0.10-boundaryThickness);
			glVertex2f(SCREEN_WIDTH-boundaryThickness,SCREEN_HEIGHT*0.10-boundaryThickness);
			glVertex2f(SCREEN_WIDTH-boundaryThickness,boundaryThickness);
			glVertex2f(boundaryThickness,boundaryThickness);
		glEnd();
		glEnable(GL_BLEND);
		glEnable(GL_TEXTURE_2D);
		glPrintHUDInfo(SCREEN_WIDTH - boundaryThickness, SCREEN_HEIGHT*0.10 - boundaryThickness,fps);
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
		HUDMode(false);
	}
	SDL_GL_SwapBuffers();
    /* Gather our frames per second */
    Frames++;
    {
		GLint t = SDL_GetTicks();
		if (t - T0 >= 5000)
			{
				GLfloat seconds = (t - T0) / 1000.0;
				fps = Frames / seconds;
				T0 = t;
				Frames = 0;
			}
    }
}

int doSelect(const double &x,const double &y)
{
	GLuint buff[64] = {0};
	GLint hits,view[4];
	
	glSelectBuffer(64,buff);

	glRenderMode(GL_SELECT);

	glInitNames();
	glPushName(0);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
		glLoadIdentity();

		glGetIntegerv(GL_VIEWPORT,view);
		gluPickMatrix(x,view[3] - y,5.0,5.0,view);//gl (0,0) bottom left, window (0,0) top left, that is why view[3] -y
		gluPerspective(45.0f,(GLfloat)SCREEN_WIDTH /(GLfloat) SCREEN_HEIGHT,0.1f,10000.0f);

		DrawGLScene();
		glMatrixMode(GL_PROJECTION);
	glPopMatrix();
    hits = glRenderMode(GL_RENDER);	
	//get nearest hit
	float minz = buff[0*4+1];	
	int ruid = buff[0*4+3];   
	for(int i = 0; i < hits;i++)
	{
		if (minz > buff[i*4+1])
		{
			minz = buff[i*4+1];
			ruid = buff[i*4+3];
		}
	}
	return ruid;
}

int main(int argc, char** argv)
{
	cout << "Before setupPSO" << endl;
	int videoFlags;
	bool done=false;
	bool calcRotation = false;
	SDL_Event event;
	const SDL_VideoInfo *videoInfo;
	chart.Plot(0,0);
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "Video initialization failed: " << SDL_GetError();
		Quit(1);
	}
	videoInfo = SDL_GetVideoInfo();

	if(!videoInfo)
	{
		cout << "Video query failed:" << SDL_GetError();
		Quit(1);
	}
	// Flags to pass to SDL_SetVideoMode
	videoFlags = SDL_OPENGL;
	videoFlags |= SDL_GL_DOUBLEBUFFER;
	videoFlags |= SDL_HWPALETTE;
	//Check to see if the surfaces can be stored in memory
	if(videoInfo->hw_available)
	{
		videoFlags |= SDL_HWSURFACE;
	}
	else
	{
		videoFlags |= SDL_SWSURFACE;
	}

	if(videoInfo->blit_hw)
	{
		videoFlags |= SDL_HWACCEL;
	}
	SDL_WM_SetCaption("William Bezuidenhout Particle Swarm 2009","William PSO 2009");
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
	if(FULLSCREEN)
	{
		//Define a pointer to get the list of supported modes
		SDL_Rect** modes;
		//If Modes == (SDL_Rect**)-1 All modes supported | If Modes == (SDL_Rect**)0 No modes supported
		modes = SDL_ListModes(NULL,SDL_FULLSCREEN | SDL_HWSURFACE);
		surface = SDL_SetVideoMode(modes[0]->w,modes[0]->h,SCREEN_BPP,videoFlags);
		//Toggle Fullscreen
		SDL_WM_ToggleFullScreen(surface);
		//delete modes[];
	}
	else surface = SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,SCREEN_BPP,videoFlags);
	if(InitGL(FUNCTION) != TRUE)
	{
		cout << "Error initializing OpenGL" << endl;
		Quit(1);
	}
	int i = 1;	
	chart.Plot(1,1);
	while(!done)
	{
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_ACTIVEEVENT:
					//ACTIVEEVENT = Lose and gain focus
					break;
				case SDL_KEYDOWN:
					keyPressed(&event.key.keysym);
					break;
				case SDL_KEYUP:
					KEY = STOP;
				case SDL_MOUSEBUTTONDOWN:
					if(event.button.button == SDL_BUTTON_RIGHT)
					{
						int temp = doSelect(event.button.x,event.button.y);
						if (temp > -1)
						{
							pso.selectParticle(temp);
						}
					}
					if(event.button.button == SDL_BUTTON_LEFT)
						calcRotation=true;
					if(event.button.button == SDL_BUTTON_WHEELUP)
						dist -= tick;
					if(event.button.button == SDL_BUTTON_WHEELDOWN)
						dist += tick;
					break;
				case SDL_MOUSEBUTTONUP:
					if (event.button.button == SDL_BUTTON_LEFT)
						calcRotation=false;
					break;
				case SDL_MOUSEMOTION:
					if (calcRotation==true)
					{
						xrot += event.motion.yrel;
						yrot += event.motion.xrel;
					}
					break;
				case SDL_QUIT:
					done = true;
					break;
				default:
					break;
			}
		}
		DrawGLScene();
		if (draw == false)
		{
			pso.updateSwarmMovement();
			chart.Plot(i++,pso.global_best.fitness);
		}
	}
	delete surface;
	return(0);
}
