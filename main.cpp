#pragma comment(lib,"glaux.lib")
#pragma comment(lib,"legacy_stdio_definitions.lib")
//BGM
#include <stdlib.h>
#include <gl/glut.h>
#include <stdio.h>
#include <windows.h>
#include <math.h>
#include <gl/glaux.h>
#include <time.h>

#include<MMSystem.h> // 배경음악 때문에 사용
#include "Digitalv.h"
#pragma comment(lib,"Winmm.lib") // 배경음악
MCI_OPEN_PARMS m_mciOpenParms;
MCI_PLAY_PARMS m_mciPlayParms;
DWORD m_dwDeviceID;
MCI_OPEN_PARMS mciOpen1;
MCI_PLAY_PARMS mciPlay1;
MCI_OPEN_PARMS mciOpen2;
MCI_PLAY_PARMS mciPlay2;
MCI_OPEN_PARMS mciOpen3;
MCI_PLAY_PARMS mciPlay3;
int dwID1;
int dwID2;
int dwID3;

#define PI 3.141592 //파이 설정
//카메라변수
float xpos = 0, ypos = 0, zpos = 50, xrot = 100000, yrot = -120000, angle = 0.0;
float Height=-3;
float lastx, lasty;
double upy = 1;
double azimuth = 90;//방위각
double azimuth_2 = 90;
double azimuth2 = 90;
double azimuth_sun = 90;
double t_azimuth = 0;//clipping plane의 방위각
double t_elevation = 0;//clipping plane의 위도
double elevation = 0;//위도
double elevation_2 = 0;//위도
double elevation2 = 0;//위도
double elevation_sun = 0;//위도
double distance = 30;//조명거리
double distance_2 = 5;
double distance2 = 100;
double distance_sun = 80;
double eyex, eyey, eyez;//조명 위 위치
double eyex2, eyey2, eyez2;//조명 아래 위치
double eyex_2, eyey_2, eyez_2;//2층 카메라 위치
double eyex_sun, eyey_sun, eyez_sun;//태양 위치
double eyexx, eyeyy, eyezz;//clipping plane 위치
double color_change=0.1;
//색상변수
double colorR = 0.9; //등대 몸통 색
double colorG = 0.9;
double colorB = 0.9;
double colorR2 = 1.0;//발판/지붕 색
double colorG2 = 0.0;
double colorB2 = 0.0;
double colorR3 = 1.0;//조명 색
double colorG3 = 1.0;
double colorB3 = 0.0;
//오브젝트변수
int f_num = 0;
float vx[255][20000];
float vy[255][20000];
float vz[255][20000];
float nvx[255][20000];
float nvy[255][20000];
float nvz[255][20000];
int f1[255][20000];
int f2[255][20000];
int f3[255][20000];
int f4[255][20000];
int f5[255][20000];
int object_count = 0;
//움직임변수
float angle0 = 0;
float angle1 = 0;//물 회전
float addangle = 0.2;
float addangle1 = 0.05;
float addangle2 = 0;
float addangle3 = 0;
float addangle4 = 0;
float addangle5 = 0;
float cullangle = 0.3;
float fire_time = 0;
float angle_star1=0;
float angle_star2 = 0;
float angle_star3 = 0;
float angle_star4 = 0;
float angle_star5 = 0;
float angle_star6 = 0;
float angle_star7 = 0;
float angle_star8 = 0;
float angle_star9 = 0;
//상태
int state_floor = 1;
int state_help = 1;//도움말
int state_fog = 0;
int state_night = 0;
int state_water = 0;
int state_aurora = 0;
int state_aurora_on = 0;
int state_fire = 0;
int state_view = 0;
int state_fire_on = 0;
int state_bird = 0;//새 on/off
int state_star_on = 1;
int state_song = 1;
int star_num = 0;
int color_state = 10;
int color2_state = 10;
int color3_state = 10;
boolean state1 = false;//0은 회전
//quadric
#define SPACEBAR 32
GLUquadricObj*m_pQuadric1;
GLUquadricObj*m_pQuadric2;
GLUquadricObj*m_pQuadric3;
GLUquadricObj*m_pQuadric4;
GLUquadricObj*m_pQuadric5;
GLUquadricObj*m_pQuadric6;
GLUquadricObj*m_pQuadric7;
GLUquadricObj*m_pQuadric8;
GLUquadricObj*m_pQuadric9;
GLUquadricObj*m_pQuadric10;
GLUquadricObj*m_pQuadric11;
GLUquadricObj*m_pQuadric12;
GLUquadricObj*m_pQuadric12_1;
GLUquadricObj*m_pQuadric12_2;
GLUquadricObj*m_pQuadric13;
GLUquadricObj*m_pQuadric13_1;
GLUquadricObj*m_pQuadric13_2;
GLUquadricObj*m_pQuadric14;
GLUquadricObj*m_pQuadric14_1;
GLUquadricObj*m_pQuadric14_2;
GLUquadricObj*m_pQuadric15;
GLUquadricObj*m_pQuadric15_1;
GLUquadricObj*m_pQuadric15_2;
GLUquadricObj*m_pQuadric16;
GLUquadricObj*m_pQuadric17;
GLUquadricObj*m_pQuadric18;
GLUquadricObj*m_pQuadric19;
GLUquadricObj*m_pQuadric20;
//GLUquadricObj*m_pQuadric21;
//함수들
void draw_lighthouse(void);
void draw_land(void);
void draw_stone(void);
void draw_manystone(void);
void draw_sea(void);
void mouseMovement(int x, int y);
void draw_obj(int object_count);
void draw_obj2(int object_count);
void draw_obj3(int object_count);
void file_load(char *fname);
void file_load2(char *fname);
void draw_string(void *font, const char*str, float x_position, float y_position, float red, float green, float blue);
void draw_text();
void draw_text_door();
void draw_door();
void draw_sky(void);
void draw_sky_polygon(void);
void draw_night(void);
void draw_bird(void);
void draw_seagull(void);
void fire1(void);
void fire2(void);
void camera(void);
void main_menu_function(int option);
void sub_menu_function1(int option);
void sub_menu_function2(int option);
void sub_menu_function3(int option);
void sub_menu_function4(int option);
void falling_star1(void);
void falling_star2(void);
void falling_star3(void);
void falling_star4(void);
void falling_star5(void);
void falling_star6(void);
void falling_star7(void);
void falling_star8(void);
void falling_star9(void);
void falling_star10(void);
void falling_star11(void);
void falling_star12(void);
void sound(void);
void aurora(void);

void draw_axis(void)
{
	glLineWidth(3);
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);//빨강은 x
	glVertex3f(0, 0, 0);
	glVertex3f(30, 0, 0);

	glColor3f(0, 1, 0); //초록은 y
	glVertex3f(0, 0, 0);
	glVertex3f(0, 30, 0);

	glColor3f(0, 0, 1);//파랑은 z
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 30);

	glEnd();
	glLineWidth(1);
}

void idle(void)
{
	angle0 = angle0 + addangle;
	if (angle0 > 360) angle0 -= 360;

	angle1 = angle1 + addangle1;
	if (angle1 > 360) angle1 -= 360;

	azimuth = azimuth + addangle;
	if (azimuth > 360)azimuth -= 360;

	azimuth2 = azimuth2 + addangle;
	if (azimuth2 > 360)azimuth2 -= 360;

	if (state_water == 0) {
		addangle2 = addangle2 + 0.002;
		addangle3 = addangle3 + 0.01;
		if (addangle2 > 1)state_water = 1;
	}
	if (state_water == 1) {
		addangle2 = addangle2 - 0.002;
		addangle3 = addangle3 - 0.01;
		if (addangle2 < 0)state_water = 0;
	}

	if (state_aurora == 0) {
		addangle4 = addangle4 + 0.05;
		addangle5 = addangle5 + 0.03;
		if (addangle4 > 5)state_aurora = 1;
	}
	if (state_aurora == 1) {
		addangle4 = addangle4 - 0.05;
		addangle5 = addangle5 - 0.03;
		if (addangle4 < 0)state_aurora = 0;
	}
	if (state_fire_on == 1) {
		fire_time = fire_time + 0.002;
		if (fire_time > 1.5) {
			state_fire_on = 0;
			fire_time = 0;
		}
	}
	if (state_star_on == 1) {
		if (star_num > 0) {
			angle_star1 = angle_star1 + 0.2;
			if (angle_star1 > 120) {
				//state_star_on = 0;
				angle_star1 = 0;
			}
		}
		if (star_num > 1) {
			angle_star2 = angle_star2 + 0.2;
			if (angle_star2 > 120) {
				//state_star_on = 0;
				angle_star2 = 0;
			}
		}
		if (star_num > 2) {
			angle_star3 = angle_star3 + 0.2;
			if (angle_star3 > 120) {
				//state_star_on = 0;
				angle_star3 = 0;
			}
		}
		if (star_num > 3) {
			angle_star4 = angle_star4 + 0.2;
			if (angle_star4 > 120) {
				//state_star_on = 0;
				angle_star4 = 0;
			}
		}
		if (star_num > 4) {
			angle_star5 = angle_star5 + 0.2;
			if (angle_star5 > 120) {
				//state_star_on = 0;
				angle_star5 = 0;
			}
		}
		if (star_num > 5) {
			angle_star6 = angle_star6 + 0.2;
			if (angle_star6 > 120) {
				//state_star_on = 0;
				angle_star6 = 0;
			}
		}
		if (star_num > 6) {
			angle_star7 = angle_star7 + 0.2;
			if (angle_star7 > 120) {
				//state_star_on = 0;
				angle_star7 = 0;
			}
		}
		if (star_num > 7) {
			angle_star8 = angle_star8 + 0.2;
			if (angle_star8 > 120) {
				//state_star_on = 0;
				angle_star8 = 0;
			}
		}
		if (star_num > 8) {
			angle_star9 = angle_star9 + 0.2;
			if (angle_star9 > 120) {
				//state_star_on = 0;
				angle_star9 = 0;
			}
		}
		glutPostRedisplay();
	}
	if (color_state == 0) {//하얀
		colorR = colorR + 0.02;
		colorG = colorG - 0.02;
		colorB = colorB - 0.02;
		if (colorG < 0.1) {
			color_state = 1;
		}
	}
	if (color_state == 1) {//빨강
		colorG = colorG + 0.02;
		if (colorG > 0.95) {
			color_state = 2;
		}
	}
	if (color_state == 2) {//노
		colorR = colorR - 0.02;
		if (colorR < 0.1) {
			color_state = 3;
		}
	}
	if (color_state == 3) {//초
		colorG = colorG - 0.02;
		colorB = colorB + 0.02;
		if (colorB > 0.95) {
			color_state = 4;
		}
	}
	if (color_state == 4) {//파
		colorB = colorB - 0.02;
		if (colorB < 0.5) {
			color_state = 5;
		}
	}
	if (color_state == 5) {//남
		colorR = colorR + 0.02;
		colorB = colorB + 0.02;
		if (colorB > 0.95) {
			color_state = 0;
		}
	}


	if (color3_state == 0) {//하얀
		colorR3 = colorR3 + 0.02;
		colorG3 = colorG3 - 0.02;
		colorB3 = colorB3 - 0.02;
		if (colorG3 < 0.1) {
			color3_state = 1;
		}
	}
	if (color3_state == 1) {//빨강
		colorG3 = colorG3 + 0.02;
		if (colorG3 > 0.95) {
			color3_state = 2;
		}
	}
	if (color3_state == 2) {//노
		colorR3 = colorR3 - 0.02;
		if (colorR3 < 0.1) {
			color3_state = 3;
		}
	}
	if (color3_state == 3) {//초
		colorG3 = colorG3 - 0.02;
		colorB3 = colorB3 + 0.02;
		if (colorB3 > 0.95) {
			color3_state = 4;
		}
	}
	if (color3_state == 4) {//파
		colorB3 = colorB3 - 0.02;
		if (colorB3 < 0.5) {
			color3_state = 5;
		}
	}
	if (color3_state == 5) {//남
		colorR3 = colorR3 + 0.02;
		colorB3 = colorB3 + 0.02;
		if (colorB3 > 0.95) {
			color3_state = 0;
		}
	}

	if (color2_state == 0) {//하얀
		colorR2 = colorR2 + 0.02;
		colorG2 = colorG2 - 0.02;
		colorB2 = colorB2 - 0.02;
		if (colorG2 < 0.1) {
			color2_state = 1;
		}
	}
	if (color2_state == 1) {//빨강
		colorG2 = colorG2 + 0.02;
		if (colorG2 > 0.95) {
			color2_state = 2;
		}
	}
	if (color2_state == 2) {//노
		colorR2 = colorR2 - 0.02;
		if (colorR2 < 0.1) {
			color2_state = 3;
		}
	}
	if (color2_state == 3) {//초
		colorG2 = colorG2 - 0.02;
		colorB2 = colorB2 + 0.02;
		if (colorB2 > 0.95) {
			color2_state = 4;
		}
	}
	if (color2_state == 4) {//파
		colorB2 = colorB2 - 0.02;
		if (colorB2 < 0.5) {
			color2_state = 5;
		}
	}
	if (color2_state == 5) {//남
		colorR2 = colorR2 + 0.02;
		colorB2 = colorB2 + 0.02;
		if (colorB2 > 0.95) {
			color2_state = 0;
		}
	}
	glutPostRedisplay();
}

void resize(int width, int height)//공간을 어떻게 쓸지 설정. 기존에 쓰던 init안의 유사 코드를 삭제할 것.
{
	glViewport(0, 0, width, height);//그림공간을 설정
	glMatrixMode(GL_PROJECTION);//카메라의 평행 투사 등 projection 특성 반영
	glLoadIdentity(); //단위행렬로 초기화
	gluPerspective(45, (float)width / (float)height, 1, 500);
	//수직방향의 field of view=45. clipping window의 가로:세로 비율은 (float)width / (float)height
	//Near plane까지의 거리는 1, far plane 까지의 거리는 500
	glMatrixMode(GL_MODELVIEW); //좌표계에서 물체의 변한,시점의 이동 등 반영
}

GLuint texName[40];
void sound(void) {
	mciOpen1.lpstrElementName = "song.mp3"; // 파일 경로 입력
	mciOpen1.lpstrDeviceType = "mpegvideo";

	mciOpen2.lpstrElementName = "song2.mp3"; // 파일 경로 입력
	mciOpen2.lpstrDeviceType = "mpegvideo";

	mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE,
		(DWORD)(LPVOID)&mciOpen1);
	mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE,
		(DWORD)(LPVOID)&mciOpen2);


	dwID1 = mciOpen1.wDeviceID;
	dwID2 = mciOpen2.wDeviceID;

	if (state_song==1&&state_night == 0) {
		mciSendCommand(dwID1, MCI_PLAY, MCI_DGV_PLAY_REPEAT, // play & repeat
			(DWORD)(LPVOID)&m_mciPlayParms);
		mciSendCommandW(dwID2, MCI_CLOSE, 0, NULL);//2번곡 정지
	}
	else if (state_song == 1&&state_night == 1) {
		mciSendCommand(dwID2, MCI_PLAY, MCI_DGV_PLAY_REPEAT, // play & repeat
			(DWORD)(LPVOID)&m_mciPlayParms);
		mciSendCommandW(dwID1, MCI_CLOSE, 0, NULL);//2번곡 정지
	}
	if (state_song == 0) {
		mciSendCommandW(dwID1, MCI_CLOSE, 0, (DWORD)(LPVOID)NULL);//1번곡 정지
		mciSendCommandW(dwID2, MCI_CLOSE, 0, (DWORD)(LPVOID)NULL);//2번곡 정지
	}
}
void init(void)
{	
	//glClearColor(0.27,0.4784,0.847, 0.0f);
	glClearColor(1, 1, 1, 1);
	//antialiasing
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	
	//glEnable(GL_POLYGON_SMOOTH);
	//glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	
	
	/////////텍스처////////////////////////////////
	glGenTextures(40, texName);
	AUX_RGBImageRec * pRGBImage;

	glBindTexture(GL_TEXTURE_2D, texName[0]);//지붕
	pRGBImage = auxDIBImageLoadA("roof1.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3, pRGBImage->sizeX, pRGBImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, pRGBImage->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, texName[1]);
	pRGBImage = auxDIBImageLoadA("land3.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3, pRGBImage->sizeX, pRGBImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, pRGBImage->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, texName[2]);
	pRGBImage = auxDIBImageLoadA("sea8.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3, pRGBImage->sizeX, pRGBImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, pRGBImage->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, texName[3]);
	pRGBImage = auxDIBImageLoadA("door3.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3, pRGBImage->sizeX, pRGBImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, pRGBImage->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, texName[4]);
	pRGBImage = auxDIBImageLoadA("land1.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3, pRGBImage->sizeX, pRGBImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, pRGBImage->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, texName[5]);
	pRGBImage = auxDIBImageLoadA("wood4.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3, pRGBImage->sizeX, pRGBImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, pRGBImage->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, texName[6]);//등대 외벽
	pRGBImage = auxDIBImageLoadA("stone1.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3, pRGBImage->sizeX, pRGBImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, pRGBImage->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, texName[7]);
	pRGBImage = auxDIBImageLoadA("stone4.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3, pRGBImage->sizeX, pRGBImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, pRGBImage->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, texName[8]);
	pRGBImage = auxDIBImageLoadA("steel1.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3, pRGBImage->sizeX, pRGBImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, pRGBImage->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, texName[9]);
	pRGBImage = auxDIBImageLoadA("steel2.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3, pRGBImage->sizeX, pRGBImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, pRGBImage->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, texName[10]);
	pRGBImage = auxDIBImageLoadA("cloud.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3, pRGBImage->sizeX, pRGBImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, pRGBImage->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, texName[11]);
	pRGBImage = auxDIBImageLoadA("upsky.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3, pRGBImage->sizeX, pRGBImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, pRGBImage->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, texName[12]);
	pRGBImage = auxDIBImageLoadA("stone5.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3, pRGBImage->sizeX, pRGBImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, pRGBImage->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, texName[13]);
	pRGBImage = auxDIBImageLoadA("space2.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3, pRGBImage->sizeX, pRGBImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, pRGBImage->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, texName[14]);
	pRGBImage = auxDIBImageLoadA("space1.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3, pRGBImage->sizeX, pRGBImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, pRGBImage->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, texName[15]);
	pRGBImage = auxDIBImageLoadA("space4.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3, pRGBImage->sizeX, pRGBImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, pRGBImage->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	glBindTexture(GL_TEXTURE_2D, texName[16]);
	pRGBImage = auxDIBImageLoadA("aurora1.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3, pRGBImage->sizeX, pRGBImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, pRGBImage->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, texName[17]);
	pRGBImage = auxDIBImageLoadA("space6.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3, pRGBImage->sizeX, pRGBImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, pRGBImage->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


	
	glBindTexture(GL_TEXTURE_2D, texName[19]);
	pRGBImage = auxDIBImageLoadA("space22.bmp");//지구
	glTexImage2D(GL_TEXTURE_2D, 0, 3, pRGBImage->sizeX, pRGBImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, pRGBImage->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	
	glBindTexture(GL_TEXTURE_2D, texName[21]);
	pRGBImage = auxDIBImageLoadA("space19.bmp");//별무리
	glTexImage2D(GL_TEXTURE_2D, 0, 3, pRGBImage->sizeX, pRGBImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, pRGBImage->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	
	glBindTexture(GL_TEXTURE_2D, texName[22]);
	pRGBImage = auxDIBImageLoadA("space5.bmp");//블루성운
	glTexImage2D(GL_TEXTURE_2D, 0, 3, pRGBImage->sizeX, pRGBImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, pRGBImage->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	

	glBindTexture(GL_TEXTURE_2D, texName[23]);
	pRGBImage = auxDIBImageLoadA("space20.bmp");//보라성운
	glTexImage2D(GL_TEXTURE_2D, 0, 3, pRGBImage->sizeX, pRGBImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, pRGBImage->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	
	glBindTexture(GL_TEXTURE_2D, texName[24]);
	pRGBImage = auxDIBImageLoadA("fire1.bmp");//보라성운
	glTexImage2D(GL_TEXTURE_2D, 0, 3, pRGBImage->sizeX, pRGBImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, pRGBImage->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	
	glBindTexture(GL_TEXTURE_2D, texName[25]);
	pRGBImage = auxDIBImageLoadA("fire2.bmp");//보라성운
	glTexImage2D(GL_TEXTURE_2D, 0, 3, pRGBImage->sizeX, pRGBImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, pRGBImage->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	glBindTexture(GL_TEXTURE_2D, texName[26]);
	pRGBImage = auxDIBImageLoadA("fallingstar1.bmp");//보라성운
	glTexImage2D(GL_TEXTURE_2D, 0, 3, pRGBImage->sizeX, pRGBImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, pRGBImage->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


	/////////////////////////////////////////////////////////////////////////////////
	GLfloat specularMaterial[] = { 1.0f,1.0f,1.0f,1.0f };


	GLfloat diffuse_Sun[] = { 1.0f,0.0f,0.0f,1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_Sun);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularMaterial);
	glMateriali(GL_FRONT, GL_SHININESS, 20);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	m_pQuadric1 = gluNewQuadric();
	gluQuadricTexture(m_pQuadric1, GL_TRUE);
	m_pQuadric2 = gluNewQuadric();
	gluQuadricTexture(m_pQuadric2, GL_TRUE);
	m_pQuadric3 = gluNewQuadric();
	gluQuadricTexture(m_pQuadric3, GL_TRUE);
	m_pQuadric4 = gluNewQuadric();
	gluQuadricTexture(m_pQuadric4, GL_TRUE);
	m_pQuadric5 = gluNewQuadric();
	m_pQuadric6 = gluNewQuadric();
	gluQuadricTexture(m_pQuadric6, GL_TRUE);
	m_pQuadric7 = gluNewQuadric();
	gluQuadricTexture(m_pQuadric7, GL_TRUE);
	m_pQuadric8 = gluNewQuadric();
	gluQuadricTexture(m_pQuadric8, GL_TRUE);
	m_pQuadric9 = gluNewQuadric();
	m_pQuadric10 = gluNewQuadric();
	m_pQuadric11 = gluNewQuadric();
	m_pQuadric12 = gluNewQuadric();
	gluQuadricTexture(m_pQuadric12, GL_TRUE);
	m_pQuadric12_1 = gluNewQuadric();
	gluQuadricTexture(m_pQuadric12_1, GL_TRUE);
	m_pQuadric12_2 = gluNewQuadric();
	gluQuadricTexture(m_pQuadric12_2, GL_TRUE);
	m_pQuadric13 = gluNewQuadric();
	gluQuadricTexture(m_pQuadric13, GL_TRUE);
	m_pQuadric13_1 = gluNewQuadric();
	gluQuadricTexture(m_pQuadric13_1, GL_TRUE);
	m_pQuadric13_2 = gluNewQuadric();
	gluQuadricTexture(m_pQuadric13_2, GL_TRUE);
	m_pQuadric14 = gluNewQuadric();
	gluQuadricTexture(m_pQuadric14, GL_TRUE);
	m_pQuadric14_1 = gluNewQuadric();
	gluQuadricTexture(m_pQuadric14_1, GL_TRUE);
	m_pQuadric14_2 = gluNewQuadric();
	gluQuadricTexture(m_pQuadric14_2, GL_TRUE);
	m_pQuadric15 = gluNewQuadric();
	gluQuadricTexture(m_pQuadric15, GL_TRUE);
	m_pQuadric15_1 = gluNewQuadric();
	gluQuadricTexture(m_pQuadric15_1, GL_TRUE);
	m_pQuadric15_2 = gluNewQuadric();
	gluQuadricTexture(m_pQuadric15_2, GL_TRUE);
	m_pQuadric16 = gluNewQuadric();
	m_pQuadric17 = gluNewQuadric();
	m_pQuadric18 = gluNewQuadric();
	m_pQuadric19 = gluNewQuadric();
	m_pQuadric20 = gluNewQuadric();
	//m_pQuadric21 = gluNewQuadric();
	//gluQuadricTexture(m_pQuadric21, GL_TRUE);
	glFrontFace(GL_CW);	//teapot 은 cw로 정의 ccw를 하면 반대이다.

	///////////////////////////////////////////////////////////////////
	char fname1[255] = "escalierColimacon2.obj";//0은 계단
	file_load(fname1);
	object_count++;
	char fname2[255] = "ship.obj";//1은 배
	file_load2(fname2);
	object_count++;

	char fname3[255] = "house2.obj";//2는 전망대
	file_load(fname3);
	object_count++;
	
	char fname4[255] = "seabird1.obj";//3은 새
	file_load2(fname4);
	object_count++;

	char fname5[255] = "seabird2.obj";//3은 새
	file_load2(fname5);
	object_count++;

	char fname6[255] = "test1.obj";//3은 새
	file_load2(fname6);
	object_count++;
	
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_TEXTURE_2D);

	GLfloat lmodel_ambient[] = { 0.0,0.0,0.0,1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	glEnable(GL_DEPTH_TEST);
}

bool gluInvertMatrix(GLfloat m[16], GLfloat invOut[16])//시선행렬의 역행렬을 곱해줌
{
	int i;
	double inv[16], det;
	inv[0] = m[5] * m[10] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15] +
		m[9] * m[7] * m[14] + m[13] * m[6] * m[11] - m[13] * m[7] * m[10];

	inv[1] = -m[1] * m[10] * m[15] + m[1] * m[11] * m[14] + m[9] * m[2] * m[15] -
		m[9] * m[3] * m[14] - m[13] * m[2] * m[11] + m[13] * m[3] * m[10];

	inv[2] = m[1] * m[6] * m[15] - m[1] * m[7] * m[14] - m[5] * m[2] * m[15] +
		m[5] * m[3] * m[14] + m[13] * m[2] * m[7] - m[13] * m[3] * m[6];

	inv[3] = -m[1] * m[6] * m[11] + m[1] * m[7] * m[10] + m[5] * m[2] * m[11] -
		m[5] * m[3] * m[10] - m[9] * m[2] * m[7] + m[9] * m[3] * m[6];

	inv[4] = -m[4] * m[10] * m[15] + m[4] * m[11] * m[14] + m[8] * m[6] * m[15] -
		m[8] * m[7] * m[14] - m[12] * m[6] * m[11] + m[12] * m[7] * m[10];

	inv[5] = m[0] * m[10] * m[15] - m[0] * m[11] * m[14] - m[8] * m[2] * m[15] +
		m[8] * m[3] * m[14] + m[12] * m[2] * m[11] - m[12] * m[3] * m[10];

	inv[6] = -m[0] * m[6] * m[15] + m[0] * m[7] * m[14] + m[4] * m[2] * m[15] -
		m[4] * m[3] * m[14] - m[12] * m[2] * m[7] + m[12] * m[3] * m[6];

	inv[7] = m[0] * m[6] * m[11] - m[0] * m[7] * m[10] - m[4] * m[2] * m[11] +
		m[4] * m[3] * m[10] + m[8] * m[2] * m[7] - m[8] * m[3] * m[6];

	inv[8] = m[4] * m[9] * m[15] - m[4] * m[11] * m[13] - m[8] * m[5] * m[15] +
		m[8] * m[7] * m[13] + m[12] * m[5] * m[11] - m[12] * m[7] * m[9];

	inv[9] = -m[0] * m[9] * m[15] + m[0] * m[11] * m[13] + m[8] * m[1] * m[15] -
		m[8] * m[3] * m[13] - m[12] * m[1] * m[11] + m[12] * m[3] * m[9];

	inv[10] = m[0] * m[5] * m[15] - m[0] * m[7] * m[13] - m[4] * m[1] * m[15] +
		m[4] * m[3] * m[13] + m[12] * m[1] * m[7] - m[12] * m[3] * m[5];

	inv[11] = -m[0] * m[5] * m[11] + m[0] * m[7] * m[9] + m[4] * m[1] * m[11] -
		m[4] * m[3] * m[9] - m[8] * m[1] * m[7] + m[8] * m[3] * m[5];

	inv[12] = -m[4] * m[9] * m[14] + m[4] * m[10] * m[13] + m[8] * m[5] * m[14] -
		m[8] * m[6] * m[13] - m[12] * m[5] * m[10] + m[12] * m[6] * m[9];

	inv[13] = m[0] * m[9] * m[14] - m[0] * m[10] * m[13] - m[8] * m[1] * m[14] +
		m[8] * m[2] * m[13] + m[12] * m[1] * m[10] - m[12] * m[2] * m[9];

	inv[14] = -m[0] * m[5] * m[14] + m[0] * m[6] * m[13] + m[4] * m[1] * m[14] -
		m[4] * m[2] * m[13] - m[12] * m[1] * m[6] + m[12] * m[2] * m[5];

	inv[15] = m[0] * m[5] * m[10] - m[0] * m[6] * m[9] - m[4] * m[1] * m[10] +
		m[4] * m[2] * m[9] + m[8] * m[1] * m[6] - m[8] * m[2] * m[5];

	det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

	if (det == 0)
		return false;

	det = 1.0 / det;

	for (i = 0; i < 16; i++)
		invOut[i] = inv[i] * det;

	return true;
}


void draw(void)//그리기
{
	if (state_night == 1) {//밤일때
		//glClearColor(0.0f, 0.1f, 0.1f, 0.0f);
	}
	if (state_night == 0) {//낮일때
		//glClearColor(0.27, 0.4784, 0.847, 0.0f);//하늘색

	}

	//////////안개///////////////////////////////
	glFogi(GL_FOG_MODE, GL_LINEAR);
	if (state_night == 0)//낮
	{
		GLfloat fogColor2[4] = { 1.0, 1.00, 1.00,1.0f }; //안개
		glFogfv(GL_FOG_COLOR, fogColor2);
	}
	else if (state_night == 1) {
		GLfloat fogColor1[4] = { 0.0f, 0.1f, 0.2f, 1.0f }; //안개
		glFogfv(GL_FOG_COLOR, fogColor1);
	}
	glHint(GL_FOG_HINT, GL_NICEST);
	glFogf(GL_FOG_START, 0.0f);
	glFogf(GL_FOG_END, 50.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //컬러 사용, 깊이감 사용
	eyex = distance * cos(elevation*PI / 180)*sin(azimuth*PI / 180);
	eyey = distance * sin(elevation*PI / 180)+10;
	eyez = distance * cos(elevation*PI / 180)*cos(azimuth*PI / 180);
	if (elevation > 90 && elevation <= 270) upy = -1; // 위도(Elevation)의 값이 90도와 270도 사이일 때 업벡터의 방향을 뒤집어줌.
	else upy = 1;
	eyex_2 = distance * cos(elevation_2*PI / 180)*sin(azimuth_2*PI / 180);
	eyey_2 = distance * sin(elevation_2*PI / 180);
	eyez_2 = distance * cos(elevation_2*PI / 180)*cos(azimuth_2*PI / 180);
	if (elevation_2 > 90 && elevation_2 <= 270) upy = -1; // 위도(Elevation)의 값이 90도와 270도 사이일 때 업벡터의 방향을 뒤집어줌.
	else upy = 1;

	eyex2 = distance2 * cos(elevation*PI / 180)*sin(azimuth*PI / 180);
	eyey2 = distance2 * sin(elevation*PI / 180)+10;
	eyez2 = distance2 * cos(elevation*PI / 180)*cos(azimuth*PI / 180);
	if (elevation > 90 && elevation <= 270) upy = -1; // 위도(Elevation)의 값이 90도와 270도 사이일 때 업벡터의 방향을 뒤집어줌.
	else upy = 1;

	eyex_sun = distance_sun * cos(elevation_sun*PI / 180)*sin(azimuth_sun*PI / 180);
	eyey_sun = distance_sun * sin(elevation_sun*PI / 180) + 10;
	eyez_sun = distance_sun * cos(elevation_sun*PI / 180)*cos(azimuth_sun*PI / 180);
	if (elevation_sun > 90 && elevation_sun <= 270) upy = -1; // 위도(Elevation)의 값이 90도와 270도 사이일 때 업벡터의 방향을 뒤집어줌.
	else upy = 1;

	eyexx = distance * cos(t_elevation*PI / 180)*sin(t_azimuth*PI / 180);
	eyeyy = distance * sin(t_elevation*PI / 180);
	eyezz = distance * cos(t_elevation*PI / 180)*cos(t_azimuth*PI / 180);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);//깊이감 사용
	if (state_floor == 1)
	{
		Height = -3;
	}
	else if(state_floor==2)
	{
		Height = -12.7;
	}
	camera();
	if (state_fog == 1) { //1일때 안개
		glEnable(GL_FOG);
	}
	else if (state_fog == 0)
	{
		glDisable(GL_FOG);
	}
	glPushMatrix();
	glTranslatef(eyex2, eyey2, eyez2);
	glPopMatrix();

	glEnable(GL_LIGHTING);
	GLfloat light_bim1[] = { eyex,eyey,eyez,1.0f };//등대 조명의 위치
	GLfloat ambient_bim1[] = { 0.2f,0.2f,0.2f,1.0f };
	GLfloat diffuse_bim1[] = { 1.0f,1.0f,1.0f,1.0f };
	GLfloat specular_bim1[] = { 1.0f,1.0f,1.0f,1.0f };
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_POSITION, light_bim1);//sun
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_bim1);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_bim1);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, specular_bim1);
	//glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 2.0);
	//glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 1.0);
	//glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.01);


	GLfloat light_ship[] = { -50,40,-50,0.3f };//배를 위한 조명의 위치
	GLfloat ambient_ship[] = { 0.1f,0.1f,0.1f,0.1f };
	GLfloat diffuse_ship[] = { 0.02f,0.02f,0.02f,1.0f };
	glLightfv(GL_LIGHT1, GL_POSITION, light_ship);//sun
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient_ship);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse_ship);


	GLfloat light_bim2[] = { eyex2,eyey2,eyez2,1.0f };//등대 조명2의 위치
	GLfloat ambient_bim2[] = { 0.2f,0.2f,0.2f,1.0f };
	GLfloat diffuse_bim2[] = { 1.0f,1.0f,1.0f,1.0f };
	GLfloat specular_bim2[] = { 1.0f,1.0f,1.0f,1.0f };

	glLightfv(GL_LIGHT2, GL_POSITION, light_bim2);
	glLightfv(GL_LIGHT2, GL_AMBIENT, ambient_bim2);
	//glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse_bim2);
	//glLightfv(GL_LIGHT2, GL_SPECULAR, specular_bim2);

	GLfloat light_Sun[] = { 20,100,20,1.0f };//등대 조명의 위치
	GLfloat ambient_Sun[] = { 0.7f,0.7f,0.7f,1.0f };
	GLfloat diffuse_Sun[] = { 1.0f,1.0f,1.0f,1.0f };
	GLfloat specular_Sun[] = { 1.0f,1.0f,1.0f,1.0f };

	glLightfv(GL_LIGHT3, GL_POSITION, light_Sun);//sun
	glLightfv(GL_LIGHT3, GL_AMBIENT, ambient_Sun);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuse_Sun);
	glLightfv(GL_LIGHT3, GL_SPECULAR, specular_Sun);


	//태양
	GLfloat light_sun[] = { eyex_sun,0.5*eyey_sun,eyez_sun,1.0f };//등대 조명의 위치
	glPushMatrix();
	glTranslatef(eyex_sun, 0.5*eyey_sun, eyez_sun);
	//draw_axis();
	glPopMatrix();
	GLfloat ambient_sun[] = { 0.7f,0.7f,0.7f,1.0f };
	GLfloat diffuse_sun[] = { 1.0f,1.0f,1.0f,1.0f };
	GLfloat specular_sun[] = { 1.0f,1.0f,1.0f,1.0f };

	glLightfv(GL_LIGHT5, GL_POSITION, light_sun);//sun
	glLightfv(GL_LIGHT5, GL_AMBIENT, ambient_sun);
	glLightfv(GL_LIGHT5, GL_DIFFUSE, diffuse_sun);
	glLightfv(GL_LIGHT5, GL_SPECULAR, specular_sun);

	if (state_night == 0) {		//낮일때
		glEnable(GL_LIGHT3);
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHT2);
		if (state_help == 1)
		{
			draw_text();
		}
	}
	else if (state_night == 1) {
		glClearColor(0,0,0,0);
		glDisable(GL_LIGHT3);
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT2);
	}

	draw_land();
	draw_manystone();
	draw_door();
	if (state_bird == 1) {
		draw_bird();
	}

	draw_lighthouse();
	draw_sea();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glRotatef(90,0,0,1);
	glRotatef(90, 1, 0, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(4.2,4.2,10.2);
	glColor4f(1.0, 1.0, 1.0, 1.0f);
	draw_obj(0);//계단
	glPopMatrix();

	glPushMatrix();
	glColor4f(1.0, 1.0, 1.0, 1.0f);
	glTranslatef(-70, -3+ addangle2, -70);
	glPushMatrix();//배위에 등불 만들기
//	gluSphere();
	GLfloat light_ship2[] = { 0,5,0,1.0f };//등대 조명의 위치
	GLfloat ambient_ship2[] = { 0.02f,0.02f,0.02f,1.0f };
	GLfloat diffuse_ship2[] = { 1.0f,1.0f,1.0f,1.0f };
	GLfloat specular_ship2[] = { 1.0f,1.0f,1.0f,1.0f };
	GLfloat emission_off[] = { 0.0, 0.0, 0.0, 1.0 };
	glEnable(GL_LIGHT4);

	glLightfv(GL_LIGHT4, GL_POSITION, light_ship2);//sun
	glLightfv(GL_LIGHT4, GL_AMBIENT, ambient_ship2);
	//glLightfv(GL_LIGHT4, GL_DIFFUSE, diffuse_ship2);
	//glLightfv(GL_LIGHT4, GL_SPECULAR, specular_ship2);

	glPopMatrix();
	glScalef(0.2, 0.2, 0.2);
	glDisable(GL_LIGHT0);
	glDisable(GL_COLOR_MATERIAL);
	draw_obj(1);//배
	glEnable(GL_LIGHT1);
	glEnable(GL_COLOR_MATERIAL);
	glPopMatrix();


	if (state_night == 0) {
		draw_sky();
	}
	if (state_night == 1) {
		//불꽃놀이
		draw_night();
		if (state_fire_on == 1) {
			if (state_fire < 10) fire1();
			if (state_fire >= 10 && state_fire < 20)fire2();
			state_fire = state_fire + 2;
			if (state_fire >= 20) state_fire -= 20;
		}
		if (state_star_on == 1) {
			if (star_num > 0) falling_star1();
			if (star_num > 1) falling_star2();
			if (star_num > 2) falling_star3();
			if (star_num > 3) falling_star4();
			if (star_num > 4) falling_star5();
			if (star_num > 5) falling_star6();
			if (star_num > 6) falling_star7();
			if (star_num > 7) falling_star8();
			if (star_num > 8) falling_star9();
			if (star_num > 8) falling_star10();
			if (star_num > 8) falling_star11();
			if (star_num > 8) falling_star12();
		}
		if(state_aurora_on==1) aurora();
	}

	if (xpos > 1000000000)
	{
		draw_text_door();
	}
		sound();
	glFlush();				//화면 출력
	glutSwapBuffers();
}

void specialkeyboard(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		azimuth_sun += 6; //방위각 증가
		break;
	case GLUT_KEY_RIGHT:
		azimuth_sun -= 6; //방위각 감소
		break;
	case GLUT_KEY_UP:
		elevation_sun += 6; //위도 증가
		if (elevation_sun > 360)elevation_sun = 0;
		break;
	case GLUT_KEY_DOWN:
		elevation_sun -= 6;//위도 감소
		if (elevation_sun < 0)elevation_sun = 360;
		break;
	}
	glutPostRedisplay();
}
void controlkey(unsigned char key, int x, int y)//key는 키의 ASCII코드, x,y는 키가 눌렸을때의 마우스의 위치
{
	switch (key)
	{
	case SPACEBAR:
		if (state1 == false) {
			addangle = 0;
			state1 = true;
			glutPostRedisplay();
		}
		else if (state1 == true) {
			addangle = 0.2;
			state1 = false;
			glutPostRedisplay();
		}
		break;
	case 'z':
		distance = distance + 5;
		break;
	case 'x':
		distance = distance - 5;
		break;
	case 'w':
		float xrotrad, yrotrad;
		//if (state_floor = 1) {
		yrotrad = (yrot / 180 * 3.141592654f);
		xrotrad = (xrot / 180 * 3.141592654f);
		xpos += 2 * float(sin(yrotrad));
		zpos -= 2 * float(cos(yrotrad));
		ypos -= 2 * float(sin(xrotrad));
		//}
		/*
		else if (state_floor = 2)
		{
			azimuth += 3;
			if (azimuth > 360)azimuth -= 360;
		}
		*/
		if (state_view == 0) PlaySound(TEXT("footstep1.wav"), NULL, SND_FILENAME | SND_ASYNC);
		break;
	case 's':
		yrotrad = (yrot / 180 * 3.141592654f);
		xrotrad = (xrot / 180 * 3.141592654f);
		xpos -= 2 * float(sin(yrotrad));
		zpos += 2 * float(cos(yrotrad));
		ypos += 2 * float(sin(xrotrad));
		if (state_view == 0) PlaySound(TEXT("footstep1.wav"), NULL, SND_FILENAME | SND_ASYNC);
		break;
	case 'a':
		yrotrad = (yrot / 180 * 3.141592654f);
		xpos -= 2 * float(cos(yrotrad)) * 0.2;
		zpos -= 2 * float(sin(yrotrad)) * 0.2;
		if (state_view == 0) PlaySound(TEXT("footstep1.wav"), NULL, SND_FILENAME | SND_ASYNC);
		break;
	case 'd':
		yrotrad = (yrot / 180 * 3.141592654f);
		xpos += 2 * float(cos(yrotrad)) * 0.2;
		zpos += 2 * float(sin(yrotrad)) * 0.2;
		if (state_view == 0) PlaySound(TEXT("footstep1.wav"), NULL, SND_FILENAME | SND_ASYNC);
		break;
	case 'r':
		xrot = 0;
		yrot = 0;
		break;
	case 'p':
		if (state_floor == 1)//2층으로 감
		{
			xpos = 2;
			zpos = 4;
			//	ypos = 4;
			state_floor = 2;
		}
		printf("state_floor=%d \n", state_floor);
		break;
	case'l':
		if (state_floor == 2)//1층으로 내려감
		{
			xpos = 0;
			zpos = 10;
			//	ypos = 0;
			state_floor = 1;
		}
		printf("state_floor=%d \n", state_floor);
		break;
	case'c':
		t_azimuth += 6; //방위각 증가
		break;
	case'o':
		t_azimuth -= 6; //방위각 감소
		break;
	case'f':
		state_star_on = 1;
		star_num = star_num + 1;
		break;
	case'1':
		state_song = 1;
		break;
	case'0':
		state_song = 0;
		break;
	case'2':
		state_song = 2;
		break;
	case'm':
		color_state = 0;
		break;
	case'n':
		color_state = 10;
		break;
	}
}
void mouseMovement(int x, int y) {
	int diffx = x - lastx; //check the difference between the current x and the last x position
	int diffy = y - lasty; //check the difference between the current y and the last y position
	lastx = x; //set lastx to the current x position
	lasty = y; //set lasty to the current y position
	xrot += (0.6)*(float)diffy; //set the xrot to xrot with the addition of the difference in the y position
	yrot += (0.6)*(float)diffx;    //set the xrot to yrot with the addition of the difference in the x position
}
void draw_door(void) {
	glPushMatrix();//13
		glRotatef(90, 1, 0, 0);
		glPushMatrix();//5
			glRotatef(90, 0, 0, 1);
			glTranslatef(3.5, 0, 0);
			glRotatef(180, 1, 0, 0);

			glPushMatrix();//1
				glBindTexture(GL_TEXTURE_2D, texName[3]);//문 텍스처
				glColor3f(0.4, 0.4, 0.4);
				glBegin(GL_QUADS);//입구
				glTexCoord2f(0, 0); glVertex3f(0, -1.3, 0);
				glTexCoord2f(1, 0); glVertex3f(0, 1.3, 0);
				glTexCoord2f(1, 1); glVertex3f(0, 1.3, 4);
				glTexCoord2f(0, 1); glVertex3f(0, -1.3, 4);
				glEnd();
				glPopMatrix();//1
			glPushMatrix();//2
			glBindTexture(GL_TEXTURE_2D, texName[6]);
				glColor3f(colorR, colorG, colorB);
				glBegin(GL_QUADS);//입구 오른쪽 벽
				glTexCoord2f(0, 0); glVertex3f(0, 1.3, 0);
				glTexCoord2f(0, 0.36); glVertex3f(0, 1.3, 4);
				glTexCoord2f(0.06, 0.36); glVertex3f(-1, 1.3, 4);
				glTexCoord2f(0.06, 0); glVertex3f(-1, 1.3, 0);
				glEnd();
				glPopMatrix();//2

			glPushMatrix();//3
			glBindTexture(GL_TEXTURE_2D, texName[6]);
				glColor3f(colorR, colorG, colorB);
				glBegin(GL_QUADS);//입구 왼쪽 벽
				glTexCoord2f(0, 0);	glVertex3f(-1, -1.3, 0);
				glTexCoord2f(0, 0.36);	glVertex3f(-1, -1.3, 4);
				glTexCoord2f(0.06, 0.36);	glVertex3f(0, -1.3, 4);
				glTexCoord2f(0.06, 0);	glVertex3f(0, -1.3, 0);
				glEnd();
				glPopMatrix();//3

			glPushMatrix();//4
			glBindTexture(GL_TEXTURE_2D, texName[6]);
				glColor3f(colorR, colorG, colorB);
				glBegin(GL_QUADS);//입구 위 벽
				glTexCoord2f(0, 0);	glVertex3f(0, -1.3, 4);
				glTexCoord2f(0, 1);	glVertex3f(0, 1.3, 4);
				glTexCoord2f(1, 1);	glVertex3f(-1, 1.3, 4);
				glTexCoord2f(1, 0);	glVertex3f(-1, -1.3, 4);
				glEnd();
				glPopMatrix();//4
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

void draw_lighthouse(void)
{
	glPushMatrix();//13
		glRotatef(90, 1, 0, 0);
		glPushMatrix();//5
			glRotatef(90, 0, 0, 1);
			glTranslatef(3.5,0,0);
			glRotatef(180, 1, 0, 0);
			glPopMatrix();//5

		glPushMatrix();//6
			glRotatef(180,0,0,0);
			glBindTexture(GL_TEXTURE_2D, texName[6]);
			glColor3f(colorR, colorG, colorB);
			gluCylinder(m_pQuadric1, 3, 2.2, 10, 30,5);//등대 몸통(p, 아래반지름, 위반지름,높이,둘레분할갯수,높이분할갯수)
			glPopMatrix();//6
		glColor3f(colorR2, colorG2, colorB2);
		glTranslatef(0,0,-10);
		glBindTexture(GL_TEXTURE_2D, texName[8]);
		glColor3f(colorR2-0.15, colorG2, colorB2);
		gluDisk(m_pQuadric2, 2, 2.5, 30, 8);//골무바닥(p,안쪽반지름,바깥반지름,둘레분할,동심원분할)
		glTranslatef(0, 0, -1);
		//gluDisk(m_pQuadric2, 2.2, 2.5, 30, 6);//골무 위(p,안쪽반지름,바깥반지름,둘레분할,동심원분할)
		glPushMatrix();
			glRotatef(180, 1, 0, 0);
			glPushMatrix();
				glRotatef(180,1,0,0);
				glColor3f(colorR2 - 0.15, colorG2, colorB2);
				gluDisk(m_pQuadric3,1.8,4, 30, 2);//전망대바닥(p,안쪽반지름,바깥반지름,둘레분할,동심원분할)
				glPushMatrix();
				glTranslatef(0, 0, 0.65);
				gluPartialDisk(m_pQuadric3, 0, 1.8,30,30, 330, 180);//계단발판
				glPopMatrix();
				glPopMatrix();
			glPopMatrix();
			glBindTexture(GL_TEXTURE_2D, texName[9]);
		gluCylinder(m_pQuadric4, 2.5, 2.5, 1, 30,5);//골무	
		gluCylinder(m_pQuadric4, 1.8, 1.8, 1, 30, 5);
		glRotatef(180, 1, 0, 0);
		gluCylinder(m_pQuadric5, 4,4, 1, 30, 5);//전망대 창살
		gluQuadricDrawStyle(m_pQuadric5,GLU_SILHOUETTE);
		glBindTexture(GL_TEXTURE_2D, texName[6]);
		glColor3f(colorR, colorG, colorB);
		//전망대
		glPushMatrix();
		glRotatef(90, 1.2, 0, 0);
		glTranslatef(-0.05,-0.095,0.03);
		glScalef(2.0, 1.25, 2.0);
		draw_obj2(2);//전망대
		glPopMatrix();

		glTranslatef(0, 0, 2.5);
		glPushMatrix();//9
			glColor3f(0.3, 0.3, 0.3);
			gluDisk(m_pQuadric7, 2, 2.5, 30, 3);//원뿔밑면(p,안쪽반지름,바깥반지름,둘레분할,동심원분할)
			glBindTexture(GL_TEXTURE_2D, texName[0]);
			glColor3f(colorR2, colorG2, colorB2);
			gluCylinder(m_pQuadric8, 2.5, 0, 2.8, 30, 5);//원뿔지붕
			glPopMatrix();//10
		glTranslatef(0, 0, 2.7);
		gluSphere(m_pQuadric9, 0.4, 20, 20);//원
		gluCylinder(m_pQuadric10, 0.1, 0.1, 2, 30, 5);//피뢰침
	//조명
		if (state_night == 1) {
			glPushMatrix();
			glRotatef(angle0, 0, 0, 1);
			//glTranslatef(-1, 0, 0);
			glRotatef(110, 0, 60, 0);
			GLfloat emission[] = { colorR3, colorG3, colorB3, 1.0 };
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
			glColor4f(1.0, 1.0, 1.0, 0.001);
			gluCylinder(m_pQuadric11, 0, 8, 160, 9, 10000);//빛경로
			GLfloat emission_off[] = { 0.0, 0.0, 0.0, 1.0 };
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission_off);
			glPopMatrix();//12
		}
		glPopMatrix();//13
	glFlush();
}

void draw_land(void) 
{
	glPushMatrix();

	glRotatef(90,0,1,0);
	glPushMatrix();
	glColor3f(1,1,1);
	glBindTexture(GL_TEXTURE_2D, texName[1]);
	glBegin(GL_QUADS);//바닥
	glTexCoord2f(0, 0); glVertex3f(10, 0, -10);
	glTexCoord2f(0, 3); glVertex3f(10, 0, 10);
	glTexCoord2f(9, 3); glVertex3f(-60, 0, 10);
	glTexCoord2f(9, 0); glVertex3f(-60, 0, -10);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texName[12]);
	glBegin(GL_QUADS);//바닥 앞쪽 면
	glColor3f(0.7, 0.7, 0.7);
	glTexCoord2f(0, 0); glVertex3f(10, -10, -10);
	glTexCoord2f(0, 6); glVertex3f(10, -10, 10);
	glTexCoord2f(6, 6); glVertex3f(10, 0, 10);
	glTexCoord2f(6, 0); glVertex3f(10, 0, -10);
	glEnd();
	glPopMatrix();
	
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texName[12]);
	glBegin(GL_QUADS);//바닥 왼쪽
	glColor3f(0.7, 0.7, 0.7);
	glTexCoord2f(0, 0); glVertex3f(10, -10, -10);
	glTexCoord2f(0, 6); glVertex3f(10, 0, -10);
	glTexCoord2f(18, 6); glVertex3f(-60, 0, -10);
	glTexCoord2f(18, 0); glVertex3f(-60, -10, -10);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texName[12]);
	glBegin(GL_QUADS);//바닥 오른쪽
	glColor3f(0.7, 0.7, 0.7);
	glTexCoord2f(0, 0); glVertex3f(10, -10, 10);
	glTexCoord2f(0, 6); glVertex3f(10, 0, 10);
	glTexCoord2f(18, 6); glVertex3f(-60, 0, 10);
	glTexCoord2f(18, 0); glVertex3f(-60, -10, 10);
	glEnd();
	glPopMatrix();
	
	glPopMatrix();
	glFlush();
}

void draw_stone(void) {
	glPushMatrix();
	glRotatef(270, 1, 0, 0);
	glColor3f(0.9, 0.9, 0.9);//하양
	glBindTexture(GL_TEXTURE_2D, texName[7]);
	gluCylinder(m_pQuadric12, 2, 1.6, 5, 9, 6);
	glPushMatrix();
	glTranslatef(0,0,5);
	gluCylinder(m_pQuadric12_1, 1.6, 1.3, 0.2, 9, 6);
	glTranslatef(0, 0, 0.2);
	gluDisk(m_pQuadric12_2, 0, 1.3, 9, 10);
	glPopMatrix();
	glRotatef(109, 0, 1, 0);
	glPushMatrix();
	gluCylinder(m_pQuadric13, 2, 1.6, 5, 9, 6);
	glPushMatrix();
	glTranslatef(0, 0, 5);
	gluCylinder(m_pQuadric13_1, 1.6, 1.3, 0.2, 9, 6);
	glTranslatef(0, 0, 0.2);
	gluDisk(m_pQuadric13_2, 0, 1.3, 9, 10);
	glPopMatrix();
	glRotatef(-109, 0, 1, 0);
	glRotatef(120, 0, 0, 1);
	glRotatef(109, 0, 1, 0);
	gluCylinder(m_pQuadric14, 2, 1.6, 5, 9, 6);
	glPushMatrix();
	glTranslatef(0, 0, 5);

	gluCylinder(m_pQuadric14_1, 1.6, 1.3, 0.2, 9, 6);
	glTranslatef(0, 0, 0.2);
	gluDisk(m_pQuadric14_2, 0, 1.3, 9, 10);
	glPopMatrix();

	glRotatef(-109, 0, 1, 0);
	glRotatef(120, 0, 0, 1);
	glRotatef(109, 0, 1, 0);
	gluCylinder(m_pQuadric15, 2, 1.6, 5, 9, 6);
	glPushMatrix();
	glTranslatef(0, 0, 5);

	gluCylinder(m_pQuadric15_1, 1.6, 1.3, 0.2, 9, 6);
	glTranslatef(0, 0, 0.2);
	gluDisk(m_pQuadric15_2, 0, 1.3, 9, 10);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glFlush();
}

void draw_manystone(void) {
	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslatef(14, -5, -10);//중심인 원점에서 벗어난 지점으로 이동
	draw_stone();
	//2번째  
	glTranslatef(0, -3, 5);//x는 땅에서의 거리, y는 높이, z는 계속 양수
	glPushMatrix();			//x는 -3~3			y는 -5~5	z는 5씩
	glRotatef(106, 1, 1, 1);
	draw_stone();
	glPopMatrix();
	//3번째
	glTranslatef(2, 3, 5);
	glPushMatrix();
	glRotatef(91, 0, 1, 1);
	draw_stone();
	glPopMatrix();

	glTranslatef(2, -3, 5);
	glPushMatrix();
	glRotatef(91, 0, 0, 1);
	draw_stone();
	glPopMatrix();

	glTranslatef(-6, -3, 5);
	glPushMatrix();
	glRotatef(47, 1, 0, 1);
	draw_stone();
	glPopMatrix();

	glTranslatef(2, 7, -2);
	glPushMatrix();
	glRotatef(91, 0, 1, 1);
	draw_stone();
	glPopMatrix();

	glTranslatef(3, -3, 6);
	glPushMatrix();
	glRotatef(91, 1, 1, 0);
	draw_stone();
	glPopMatrix();

	glTranslatef(-3, 3.5, 5);
	glPushMatrix();
	glRotatef(91, 1, 0, 1);
	draw_stone();
	glPopMatrix();

	glTranslatef(3, -3.5, 5);
	glPushMatrix();
	glRotatef(91, 1, 0, 0);
	draw_stone();
	glPopMatrix();

	glTranslatef(-3, 3.5, 5);
	glPushMatrix();
	glRotatef(22, 0, 0, 1);
	draw_stone();
	glPopMatrix();

	glTranslatef(3, -3.5, 5);
	glPushMatrix();
	glRotatef(91, 0, 1, 0);
	draw_stone();
	glPopMatrix();

	glTranslatef(-3, 3.5, 5);
	glPushMatrix();
	glRotatef(172, 0, 0, 1);
	draw_stone();
	glPopMatrix();

	glTranslatef(3, -3.5, 5);
	glPushMatrix();
	glRotatef(91, 1, 0, 0);
	draw_stone();
	glPopMatrix();

	glTranslatef(-3, 3.5, 5);
	glPushMatrix();
	glRotatef(198, 0, 0, 1);
	draw_stone();
	glPopMatrix();

	glPopMatrix();
	////////////오른쪽 끝///////////////////////////////
	glPushMatrix();
	glTranslatef(-15, -3, -5);
	draw_stone();

	glTranslatef(0, -3, 5);//x는 땅에서의 거리, y는 높이, z는 계속 양수
	glPushMatrix();			//x는 -3~3			y는 -5~5	z는 5씩
	glRotatef(106, 1, 1, 1);
	draw_stone();
	glPopMatrix();
	//3번째
	glTranslatef(2, 3, 5);
	glPushMatrix();
	glRotatef(91, 0, 1, 1);
	draw_stone();
	glPopMatrix();

	glTranslatef(2, -3, 5);
	glPushMatrix();
	glRotatef(91, 0, 0, 1);
	draw_stone();
	glPopMatrix();

	glTranslatef(-6, -3, 5);
	glPushMatrix();
	glRotatef(47, 1, 0, 1);
	draw_stone();
	glPopMatrix();

	glTranslatef(2, 7, -2);
	glPushMatrix();
	glRotatef(91, 0, 1, 1);
	draw_stone();
	glPopMatrix();

	glTranslatef(3, -3, 6);
	glPushMatrix();
	glRotatef(91, 1, 1, 0);
	draw_stone();
	glPopMatrix();

	glTranslatef(-3, 3.5, 5);
	glPushMatrix();
	glRotatef(91, 1, 0, 1);
	draw_stone();
	glPopMatrix();

	glTranslatef(3, -3.5, 5);
	glPushMatrix();
	glRotatef(91, 1, 0, 0);
	draw_stone();
	glPopMatrix();

	glTranslatef(-3, 3.5, 5);
	glPushMatrix();
	glRotatef(22, 0, 0, 1);
	draw_stone();
	glPopMatrix();

	glTranslatef(3, -3.5, 5);
	glPushMatrix();
	glRotatef(91, 0, 1, 0);
	draw_stone();
	glPopMatrix();

	glTranslatef(-3, 3.5, 5);
	glPushMatrix();
	glRotatef(172, 0, 0, 1);
	draw_stone();
	glPopMatrix();

	glTranslatef(3, -3.5, 5);
	glPushMatrix();
	glRotatef(91, 1, 0, 0);
	draw_stone();
	glPopMatrix();
	glPopMatrix();
	///////////왼쪽 끝////////////////////////////////

	glPushMatrix();
	glTranslatef(-14, -5, -13);
	draw_stone();

	glTranslatef(5, 3, -3);
	glPushMatrix();
	glRotatef(42, 1, 0, 0);
	draw_stone();
	glPopMatrix();

	glTranslatef(5,-4, 3);
	glPushMatrix();
	glRotatef(242, 0, 0, 1);
	draw_stone();
	glPopMatrix();

	glTranslatef(5, 2.5, -3);
	glPushMatrix();
	glRotatef(82, 0, 1, 0);
	draw_stone();
	glPopMatrix();

	glTranslatef(5, -4, 3);
	glPushMatrix();
	glRotatef(72, 0, 0, 1);
	draw_stone();
	glPopMatrix();

	glTranslatef(5, 4.3, -3);
	glPushMatrix();
	glRotatef(42, 1, 0, 0);
	draw_stone();
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();

	glPopMatrix();
}

void draw_sea(void) {
	GLfloat emission[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat emission_off[] = { 0.0, 0.0, 0.0, 1.0 };
	glPushMatrix();//검은바닥
	glTranslatef(0, -7.5 + addangle2, 0);
	glRotatef(90, 0, 1, 0);
	glColor3f(0.0, 0.1, 0.1);
	glBegin(GL_QUADS);//바닥
	glVertex3f(230, 0, -230);
	glVertex3f(230, 0, 230);
	glVertex3f(-230, 0, 230);
	glVertex3f(-230, 0, -230);
	glEnd();
	glPopMatrix();

	glPushMatrix();//검은바닥테두리
	glTranslatef(0, -7.5 + addangle2, 0);
	glRotatef(90, 0, 1, 0);
	glColor3f(0.0, 0.1, 0.1);
	glBegin(GL_QUADS);//바닥
	glVertex3f(-250, 0, 230);
	glVertex3f(250, 0, 230);
	glVertex3f(250, 2.5, 250);
	glVertex3f(-250, 2.5, 250);
	glEnd();
	glPopMatrix();

	glPushMatrix();//검은바닥테두리
	glTranslatef(0, -7.5 + addangle2, 0);
	glRotatef(90, 0, 1, 0);
	glColor3f(0.0, 0.1, 0.1);
	glBegin(GL_QUADS);//바닥
	glVertex3f(230, 0, 250);
	glVertex3f(230, 0, -250);
	glVertex3f(250, 2.5, -250);
	glVertex3f(250, 2.5, 250);
	glEnd();
	glPopMatrix();

	glPushMatrix();//검은바닥테두리
	glTranslatef(0, -7.5 + addangle2, 0);
	glRotatef(90, 0, 1, 0);
	glColor3f(0.0, 0.1, 0.1);
	glBegin(GL_QUADS);//바닥
	glVertex3f(-230, 0, 250);
	glVertex3f(-230, 0, -250);
	glVertex3f(-250, 2.5, -250);
	glVertex3f(-250, 2.5, 250);
	glEnd();
	glPopMatrix();

	glPushMatrix();//검은바닥테두리
	glTranslatef(0, -7.5 + addangle2, 0);
	glRotatef(90, 0, 1, 0);
	glColor3f(0.0, 0.1, 0.1);
	glBegin(GL_QUADS);//바닥
	glVertex3f(-250, 0, -230);
	glVertex3f(250, 0, -230);
	glVertex3f(250, 2.5, -250);
	glVertex3f(-250, 2.5, -250);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -5 + addangle2, 0);
	glTranslatef(0, 0, addangle3);
	glRotatef(90, 0, 1, 0);
	if (state_night == 1) { //밤일때
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
		glColor4f(0.3, 0.3, 0.3, 1.0);
		glBindTexture(GL_TEXTURE_2D, texName[13]);
		glBegin(GL_QUADS);//윗물
		glTexCoord2f(0, 0); glVertex3f(250, 0, -250);
		glTexCoord2f(0, 10); glVertex3f(250, 0, 250);
		glTexCoord2f(10, 10); glVertex3f(-250, 0, 250);
		glTexCoord2f(10, 0); glVertex3f(-250, 0, -250);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission_off);
		glEnd();
	}
	else if (state_night == 0)
	{
		glColor4f(0.4, 0.4, 0.8, 0.5);
		glBindTexture(GL_TEXTURE_2D, texName[2]);
		glBegin(GL_QUADS);//윗물
		glTexCoord2f(0, 0); glVertex3f(250, 0, -250);
		glTexCoord2f(0, 10); glVertex3f(250, 0, 250);
		glTexCoord2f(10, 10); glVertex3f(-250, 0, 250);
		glTexCoord2f(10, 0); glVertex3f(-250, 0, -250);
		glEnd();
	}


	glPopMatrix();
	
	/*
	glPushMatrix();
		glTranslatef(0, 0, -150);
		glTranslatef(0, -5.01 + addangle2, 0);
		glRotatef(90, 0, 1, 0);
		glColor3f(0.0, 0.1, 0.1);
		glBegin(GL_QUADS);//바닥
		glVertex3f(220, 0, -30);
		glVertex3f(220, 0, 30);
		glVertex3f(-220, 0, 30);
		glVertex3f(-220, 0, -30);
		glEnd();
	glPopMatrix();
	*/
}

void draw_sky(void) {
	glPushMatrix();
	draw_sky_polygon();
	glRotatef(90, 0, 1, 0);
	draw_sky_polygon();
	glRotatef(90, 0, 1, 0);
	draw_sky_polygon();
	glRotatef(90, 0, 1, 0);
	draw_sky_polygon();

	
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texName[11]);
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glTexCoord2f(0, 0); glVertex3f(250, 75, -250);
	glTexCoord2f(0, 1); glVertex3f(250, 75, 250);
	glTexCoord2f(1, 1); glVertex3f(-250, 75, 250);
	glTexCoord2f(1, 0); glVertex3f(-250, 75, -250);
	glEnd();
	glPopMatrix();

	glPopMatrix();
}

void draw_night(void) {
	//오른쪽 면
	GLfloat emission[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat emission_off[] = { 0.0, 0.0, 0.0, 1.0 };

	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
	glBindTexture(GL_TEXTURE_2D, texName[13]);
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glTexCoord2f(0, 3); glVertex3f(250, 130, -250);
	glTexCoord2f(3, 3); glVertex3f(250, 130, 250);
	glTexCoord2f(3, 0); glVertex3f(250, -5, 250);
	glTexCoord2f(0, 0); glVertex3f(250, -5, -250);
	glEnd();
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission_off);
	glPopMatrix();
	//왼쪽 면
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
	glBindTexture(GL_TEXTURE_2D, texName[13]);
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glTexCoord2f(0, 3); glVertex3f(-250, 130, -250);
	glTexCoord2f(3, 3); glVertex3f(-250, 130, 250);
	glTexCoord2f(3, 0); glVertex3f(-250, -5, 250);
	glTexCoord2f(0, 0); glVertex3f(-250, -5, -250);
	glEnd();
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission_off);
	glPopMatrix();
	//앞쪽
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
	glBindTexture(GL_TEXTURE_2D, texName[13]);
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glTexCoord2f(0, 3); glVertex3f(-270, 140, -250);
	glTexCoord2f(3, 3); glVertex3f(270, 135, -250);
	glTexCoord2f(3, 0); glVertex3f(270, -9, -250);
	glTexCoord2f(0, 0); glVertex3f(-270, -9, -250);
	glEnd();
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission_off);
	glPopMatrix();
	//뒤쪽
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
	glBindTexture(GL_TEXTURE_2D, texName[13]);
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glTexCoord2f(0, 3); glVertex3f(-270, 140, 250);
	glTexCoord2f(3, 3); glVertex3f(270, 135, 250);
	glTexCoord2f(3, 0); glVertex3f(270, -9, 250);
	glTexCoord2f(0, 0); glVertex3f(-270, -9, 250);
	glEnd();
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission_off);
	glPopMatrix();
	//천장 높이 135
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
	glBindTexture(GL_TEXTURE_2D, texName[13]);
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glTexCoord2f(0, 5); glVertex3f(-560, 135, -250);
	glTexCoord2f(5, 5); glVertex3f(560, 135, -250);
	glTexCoord2f(5, 0); glVertex3f(560, 135, 250);
	glTexCoord2f(0, 0); glVertex3f(-560, 135, 250);
	glEnd();
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission_off);
	glPopMatrix();

	//블랙홀
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
	glBindTexture(GL_TEXTURE_2D, texName[14]);
	glBegin(GL_QUADS);
	glColor4f(1, 1, 1,0.05);
	glTexCoord2f(0, 1); glVertex3f(240, 120, -80);
	glTexCoord2f(1, 1); glVertex3f(240, 120, 80);
	glTexCoord2f(1, 0); glVertex3f(240, 0, 80);
	glTexCoord2f(0, 0); glVertex3f(240, 0, -80);
	glEnd();
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission_off);
	glPopMatrix();

	//행성
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
	glBindTexture(GL_TEXTURE_2D, texName[15]);
	glBegin(GL_QUADS);
	glColor4f(1, 1, 1, 0.1);
	glTexCoord2f(0, 1); glVertex3f(0, 120, -249);
	glTexCoord2f(1, 1); glVertex3f(160, 120, -249);
	glTexCoord2f(1, 0); glVertex3f(160, 0, -249);
	glTexCoord2f(0, 0); glVertex3f(0, 0, -249);
	glEnd();
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission_off);
	glPopMatrix();
	
	//은하수
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
	glBindTexture(GL_TEXTURE_2D, texName[17]);
	glBegin(GL_QUADS);
	glColor4f(1, 1, 1, 0.1);
	glTexCoord2f(0, 0); glVertex3f(-65, 134, -120);
	glTexCoord2f(0, 1); glVertex3f(25, 134, -120);
	glTexCoord2f(1, 1); glVertex3f(25, 134, 120);
	glTexCoord2f(1, 0); glVertex3f(-65, 134, 120);
	glEnd();
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission_off);
	glPopMatrix();

	//성운
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
	glBindTexture(GL_TEXTURE_2D, texName[23]);
	glBegin(GL_QUADS);
	glColor4f(1, 1, 1, 0.1);
	glTexCoord2f(0, 0); glVertex3f(-200, 134, -250);
	glTexCoord2f(0, 1); glVertex3f(-200, 30, -250);
	glTexCoord2f(1, 1); glVertex3f(-250, 30, 50);
	glTexCoord2f(1, 0); glVertex3f(-250, 134, 50);
	glEnd();
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission_off);
	glPopMatrix();
}

void aurora(void) {
	GLfloat emission[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat emission_off[] = { 0.0, 0.0, 0.0, 1.0 };
	//오로라1
	glPushMatrix();
	glTranslatef(addangle4, 0, 0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
	glBindTexture(GL_TEXTURE_2D, texName[16]);
	glBegin(GL_QUADS);
	glColor4f(1, 1, 1, 0.1);
	glTexCoord2f(0, 1); glVertex3f(60, 125, -200);
	glTexCoord2f(1, 1); glVertex3f(60, 125, 130);
	glTexCoord2f(1, 0); glVertex3f(65, 0, 130);
	glTexCoord2f(0, 0); glVertex3f(65, 0, -220);
	glEnd();
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission_off);
	glPopMatrix();

	//오로라2
	glPushMatrix();
	glTranslatef(-addangle5, 0, 0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
	glBindTexture(GL_TEXTURE_2D, texName[16]);
	glBegin(GL_QUADS);
	glColor4f(1, 1, 1, 0.2);
	glTexCoord2f(0, 1); glVertex3f(55, 115, 130);
	glTexCoord2f(1, 1); glVertex3f(55, 115, -150);
	glTexCoord2f(1, 0); glVertex3f(64, 10, -150);
	glTexCoord2f(0, 0); glVertex3f(64, 10, 130);
	glEnd();
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission_off);
	glPopMatrix();
}

void draw_sky_polygon(void) {
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texName[10]);
	glBegin(GL_QUADS);//바닥 앞쪽 면
	glColor3f(1, 1, 1);
	glTexCoord2f(0, 1); glVertex3f(-828, 85, -250);
	glTexCoord2f(3, 1); glVertex3f(828, 85, -250);
	glTexCoord2f(3, 0); glVertex3f(828, -45, -250);
	glTexCoord2f(0, 0); glVertex3f(-828, -45, -250);
	glEnd();
	glPopMatrix();
}

void draw_text()
{
	//glLoadIdentity();//이전까지 설정들을 초기화
	if (state_night == 0) {
		draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "                   - tip -", -4.8, 4, 3, 0, 0);
		draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "[space bar]      : stop light/bird", -4.8, 3.6, 1, 3, 0);
		draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "[w] [a] [s] [d]  : move", -4.8, 3.3, 1, 3, 0);
		draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "[r]                    : reset view", -4.8, 3, 1, 3, 0);
		draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "[p]                   : go to 2nd floor", -4.8, 2.7, 1, 3, 0);
		draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "[l]                    : go to 1st floor", -4.8, 2.4, 1, 3, 0);
		draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "[0]                   : turn off BGM", -4.8, 2.1, 1, 3, 0);
	}
	glFlush();
}

void draw_text_door()
{
	draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "Push [H] button", -4, 3, 0.0f, 1.0f, 1.0f);
	draw_string(GLUT_BITMAP_HELVETICA_18, "if you want to come int", -4, 2, 1.0f, 0.0f, 1.0f);
	glFlush();
}

void draw_seagull(void) {
	glPushMatrix();
	glColor3f(1, 1, 1);

	draw_obj3(3);
	glColor3f(1, 1, 0);
	draw_obj3(4);

	glColor3f(0, 0, 0);
	glScalef(0.45, 0.45, 0.45);
	draw_obj3(5);

	glPopMatrix();
}
void draw_bird(void)
{
	glPushMatrix();
	glRotatef(angle0, 0, -1, 0);
	glRotatef(addangle2, 1, 0, 0);
	glTranslatef(30, 50, 0);
	draw_seagull();
	glPopMatrix();

	glPushMatrix();
	glRotatef(angle0-0.2, 0, -1, 0);
	glRotatef(20, 1, 0, 0);
	glTranslatef(40, 30, 0);
	draw_seagull();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(40, 30, 20);
	glRotatef(angle0 - 0.2, 0, -1, 0);
	glRotatef(40,0, 0, 1);
	glTranslatef(40, 20, 10);
	draw_seagull();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(40, 30, 20);
	glRotatef(angle0 +2, 0, 1, 0);
	glTranslatef(-30, 0, 0);
	draw_seagull();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10, 20, -10);
	glRotatef(90, -0.2, 1, 0);
	glRotatef(angle0 + 3, 0, -1, 0);
	glTranslatef(10, 0, 0);
	draw_seagull();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-20, 20, -50);
	glRotatef(90, 0.1, 1, 0);
	glRotatef(angle0 + 1.2, 0, -1, 0);
	glTranslatef(30, 0, 0);
	draw_seagull();
	glPopMatrix();
}

void fire1(void) {
	glPushAttrib(GL_LIGHTING_BIT);
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(-5, 5, -5, 5);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	GLfloat emission[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat emission_off[] = { 0.0, 0.0, 0.0, 1.0 };

	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
	glBindTexture(GL_TEXTURE_2D, texName[24]);
	glBegin(GL_QUADS);
	glColor4f(1, 1, 1, 0.05);
	glTexCoord2f(0, 1); glVertex2f(-1.14, -3 - fire_time);
	glTexCoord2f(1, 1); glVertex2f(-1.14, 1.5 - fire_time);
	glTexCoord2f(1, 0); glVertex2f(1.46, 1.5 - fire_time);
	glTexCoord2f(0, 0); glVertex2f(1.46, -3 - fire_time);
	glEnd();


	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission_off);
	glPopMatrix();

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopAttrib();
}

void fire2(void) {
	glPushAttrib(GL_LIGHTING_BIT);
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(-5, 5, -5, 5);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	GLfloat emission[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat emission_off[] = { 0.0, 0.0, 0.0, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
	glBindTexture(GL_TEXTURE_2D, texName[25]);
	glBegin(GL_QUADS);
	glColor4f(1, 1, 1, 0.05);
	glTexCoord2f(0, 1); glVertex2f(-1.14, -3 - fire_time);
	glTexCoord2f(1, 1); glVertex2f(-1.14, 1.5 - fire_time);
	glTexCoord2f(1, 0); glVertex2f(1.46, 1.5 - fire_time);
	glTexCoord2f(0, 0); glVertex2f(1.46, -3 - fire_time);
	glEnd();
	glPopMatrix();

	
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission_off);

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopAttrib();
}

int main(int argc, char** argv)
{
	int submenu1;
	int submenu2;
	int submenu3;
	int submenu4;
	/*Window 초기화 */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(1200, 800);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("My First GL Program");

	//callback
	init();
	submenu1 = glutCreateMenu(sub_menu_function1);  //서브메뉴
	glutAddMenuEntry("자유시점", 1);
	glutAddMenuEntry("안개on/off", 2);
	glutAddMenuEntry("낮/밤", 3);
	glutAddMenuEntry("불꽃on/off", 4);
	glutAddMenuEntry("갈매기 on/off", 5);
	glutAddMenuEntry("별똥별 off", 6);
	glutAddMenuEntry("오로라 on/off", 7);

	submenu2 = glutCreateMenu(sub_menu_function2);  //서브메뉴
	glutAddMenuEntry("빨강", 1);
	glutAddMenuEntry("노랑", 2);
	glutAddMenuEntry("초록", 3);
	glutAddMenuEntry("파랑", 4);
	glutAddMenuEntry("보라", 5);
	glutAddMenuEntry("무지개", 6);
	glutAddMenuEntry("하양", 7);

	submenu3 = glutCreateMenu(sub_menu_function3);  //서브메뉴
	glutAddMenuEntry("빨강", 1);
	glutAddMenuEntry("노랑", 2);
	glutAddMenuEntry("초록", 3);
	glutAddMenuEntry("파랑", 4);
	glutAddMenuEntry("보라", 5);
	glutAddMenuEntry("무지개", 6);
	glutAddMenuEntry("하양", 7);

	submenu4 = glutCreateMenu(sub_menu_function4);  //서브메뉴
	glutAddMenuEntry("빨강", 1);
	glutAddMenuEntry("노랑", 2);
	glutAddMenuEntry("초록", 3);
	glutAddMenuEntry("파랑", 4);
	glutAddMenuEntry("보라", 5);
	glutAddMenuEntry("무지개", 6);
	glutAddMenuEntry("하양", 7);

	glutCreateMenu(main_menu_function);				//메인메뉴
	glutAddMenuEntry("도움말 on/off",111);
	glutAddSubMenu("Sub menu", submenu1);			//메인메뉴에서 submenu누르면 서브메뉴로 넘어감
	glutAddSubMenu("등대색깔", submenu2);			//메인메뉴에서 submenu누르면 서브메뉴로 넘어감
	glutAddSubMenu("지붕색깔", submenu3);			//메인메뉴에서 submenu누르면 서브메뉴로 넘어감
	glutAddSubMenu("조명색깔", submenu4);			//메인메뉴에서 submenu누르면 서브메뉴로 넘어감
	glutAddMenuEntry("종료", 999);

	glutAttachMenu(GLUT_RIGHT_BUTTON);				//마우스 오른쪽버튼 누르면 메뉴활성화

	glutIdleFunc(idle);
	glutReshapeFunc(resize);
	glutSpecialFunc(specialkeyboard);//키보드 이벤트
	glutKeyboardFunc(controlkey); //키보드의 일반키를 처리
	glutPassiveMotionFunc(mouseMovement);
	glutDisplayFunc(draw);
	glutMainLoop(); //무한루프. 값을 반환하지 않고 어플리케이션이 실행됨.

	return 0;
}

void file_load(char *fname) {
	FILE *fp;
	int read;
	char ch[5];
	float x0;
	float y0;
	float z0;
	int i, j, k;
	i = 0; j = 0; k = 0;

	fp = fopen(fname, "r");
	if (!fp) {
		printf("can't open file %s\n", fname);
		exit(1);
	}
	printf("%d %s \n", object_count, fname);
	while (!(feof(fp))) {
		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(fp, "%s", lineHeader);
		if (strcmp(lineHeader, "v") == 0) {
			i++;
			fscanf(fp, "%f", &x0);
			fscanf(fp, "%f", &y0);
			fscanf(fp, "%f", &z0);
			vx[object_count][i] = x0;
			vy[object_count][i] = y0;
			vz[object_count][i] = z0;
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			j++;
			fscanf(fp, "%f", &x0);
			fscanf(fp, "%f", &y0);
			fscanf(fp, "%f", &z0);
			nvx[object_count][j] = x0;
			nvy[object_count][j] = y0;
			nvz[object_count][j] = z0;
		}
		else if (strcmp(lineHeader, "f") == 0) {
			k++;
			f_num++;
			int a, b, c;
			fscanf(fp, "%d//%d", &a, &c);
			f1[object_count][k] = a;
			fscanf(fp, "%d//%d", &a, &c);
			f2[object_count][k] = a;
			fscanf(fp, "%d//%d", &a, &c);
			f3[object_count][k] = a;
			f5[object_count][k] = c;
		}
	}
}

void file_load2(char *fname) {//vt있는 삼각형
	FILE *fp;
	int read;
	char ch[5];
	float x0;
	float y0;
	float z0;
	int i, j, k;
	i = 0; j = 0; k = 0;

	fp = fopen(fname, "r");
	if (!fp) {
		printf("can't open file %s\n", fname);
		exit(1);
	}
	printf("%d %s \n", object_count, fname);
	while (!(feof(fp))) {
		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(fp, "%s", lineHeader);
		if (strcmp(lineHeader, "v") == 0) {
			i++;
			fscanf(fp, "%f", &x0);
			fscanf(fp, "%f", &y0);
			fscanf(fp, "%f", &z0);
			vx[object_count][i] = x0;
			vy[object_count][i] = y0;
			vz[object_count][i] = z0;
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			j++;
			fscanf(fp, "%f", &x0);
			fscanf(fp, "%f", &y0);
			fscanf(fp, "%f", &z0);
			nvx[object_count][j] = x0;
			nvy[object_count][j] = y0;
			nvz[object_count][j] = z0;
		}
		else if (strcmp(lineHeader, "f") == 0) {
			k++;
			f_num++;
			int a, b, c;
			fscanf(fp, "%d/%d/%d", &a, &b, &c);
			f1[object_count][k] = a;
			fscanf(fp, "%d/%d/%d", &a, &b, &c);
			f2[object_count][k] = a;
			fscanf(fp, "%d/%d/%d", &a, &b, &c);
			f3[object_count][k] = a;
			f5[object_count][k] = c;
		}
	}
}

void draw_obj(int object_count) {
	glBindTexture(GL_TEXTURE_2D, texName[5]);
	glBegin(GL_TRIANGLES);
	for (int n = 0; n < f_num; n++) {
		glNormal3f(nvx[object_count][f5[object_count][n]], nvy[object_count][f5[object_count][n]], nvz[object_count][f5[object_count][n]]);
		glTexCoord2f(0, 0); glVertex3f(vx[object_count][f1[object_count][n]], vy[object_count][f1[object_count][n]], vz[object_count][f1[object_count][n]]);
		glTexCoord2f(0, 0.1); glVertex3f(vx[object_count][f2[object_count][n]], vy[object_count][f2[object_count][n]], vz[object_count][f2[object_count][n]]);
		glTexCoord2f(0.1, 0); glVertex3f(vx[object_count][f3[object_count][n]], vy[object_count][f3[object_count][n]], vz[object_count][f3[object_count][n]]);
	}
	glEnd();
}
void draw_obj2(int object_count) {
	glBindTexture(GL_TEXTURE_2D, texName[6]);
	glBegin(GL_TRIANGLES);
	for (int n = 0; n < f_num; n++) {
		glNormal3f(nvx[object_count][f5[object_count][n]], nvy[object_count][f5[object_count][n]], nvz[object_count][f5[object_count][n]]);
		glTexCoord2f(0, 0); glVertex3f(vx[object_count][f1[object_count][n]], vy[object_count][f1[object_count][n]], vz[object_count][f1[object_count][n]]);
		glTexCoord2f(0, 1); glVertex3f(vx[object_count][f2[object_count][n]], vy[object_count][f2[object_count][n]], vz[object_count][f2[object_count][n]]);
		glTexCoord2f(1, 0); glVertex3f(vx[object_count][f3[object_count][n]], vy[object_count][f3[object_count][n]], vz[object_count][f3[object_count][n]]);
	}
	glEnd();
}

void draw_obj3(int object_count) {
	//glBindTexture(GL_TEXTURE_2D, texName[18]);
	glBegin(GL_TRIANGLES);
	for (int n = 0; n < f_num; n++) {
	glNormal3f(nvx[object_count][f5[object_count][n]], nvy[object_count][f5[object_count][n]], nvz[object_count][f5[object_count][n]]);
	glVertex3f(vx[object_count][f1[object_count][n]], vy[object_count][f1[object_count][n]], vz[object_count][f1[object_count][n]]);
	glVertex3f(vx[object_count][f2[object_count][n]], vy[object_count][f2[object_count][n]], vz[object_count][f2[object_count][n]]);
	glVertex3f(vx[object_count][f3[object_count][n]], vy[object_count][f3[object_count][n]], vz[object_count][f3[object_count][n]]);
	}
	glEnd();
}

void draw_string(void *font, const char*str, float x_position, float y_position, float red1, float green, float blue)
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	GLfloat emission[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat emission_off[] = { 0.0, 0.0, 0.0, 1.0 };

	gluOrtho2D(-5, 5, -5, 5);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);

	glColor3f(red1, green, blue);
	glRasterPos3f(x_position, y_position, 0);
	for (unsigned int i = 0; i < strlen(str); i++)
		glutBitmapCharacter(font, str[i]);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission_off);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopAttrib();
}

void camera(void) {
	glRotatef(xrot, 1.0, 0.0, 0.0);  //rotate our camera on the x-axis (left and right)
	glRotatef(yrot, 0.0, 1.0, 0.0);  //rotate our camera on the y-axis (up and down)
	if (state_view == 0) glTranslated(-xpos, Height, -zpos); //translate the screen to the position of our camera
	else if (state_view == 1) glTranslated(-xpos, -ypos, -zpos);
}

void main_menu_function(int option)				//메인메뉴
{
	printf("Main menu %d has been selected\n", option);
	if (option == 999) {
		exit(0);
	}
	if (option == 111) { //도움말 ON/OFF
		if (state_help == 1) {
			state_help = 0;
		}
		else if (state_help == 0) {
			state_help = 1;
		}
	}
}

void sub_menu_function1(int option)	//서브메뉴
{
	GLint index;
	printf("서브메뉴 %d 번 선택\n", option);
	if (option == 1) {				//자유시점
		if (state_view == 1) {
			state_view = 0;
		}
		else if (state_view == 0) {
			state_view = 1;
		}
	}
	if (option == 2) {				//안개on/off
		if (state_fog == 1) {
			state_fog = 0;
		}
		else if (state_fog == 0) {
			state_fog = 1;
		}
	}
	if (option == 3) {				//낮과 밤
		if (state_night == 1) {
			state_night = 0;
		}
		else if (state_night == 0) {
			state_night = 1;
		}
	}
	if (option == 4) {				//불꽃놀이 on.off
		if (state_fire_on == 1) {
			state_fire_on = 0;
		}
		else if (state_fire_on == 0) {
			state_fire_on = 1;
		}
	}
	if (option == 5) {				//갈매기 on/off
		if (state_bird == 1) {
			state_bird = 0;
		}
		else if (state_bird == 0) {
			state_bird = 1;
			PlaySound(TEXT("seagullsound.wav"), NULL, SND_FILENAME | SND_ASYNC );
		}
	}
	if (option == 6) {				//별똥별 off
		state_star_on = 0;
	}
	if (option == 7) {				//오로라 on/off
		if (state_aurora_on == 1) {
			state_aurora_on = 0;
		}
		else if (state_aurora_on == 0) {
			state_aurora_on = 1;
		}
	}
}

void sub_menu_function2(int option)	//서브메뉴
{
	GLint index;
	printf("등대색깔 선택 \n");
	if (option == 1) {				//빨강
		color_state = 10;
		colorR = 1;
		colorG = 0;
		colorB = 0;
	}
	if (option == 2) {				//노랑
		color_state = 10;
		colorR = 1;
		colorG = 1;
		colorB = 0;
	}
	if (option == 3) {				//초록
		color_state = 10;
		colorR = 0;
		colorG = 0.9;
		colorB = 0;
	}
	if (option == 4) {				//파랑
		color_state = 10;
		colorR = 0;
		colorG = 0;
		colorB = 0.9;
	}
	if (option == 5) {				//보라
		color_state = 10;
		colorR = 0.9;
		colorG = 0;
		colorB = 0.9;
	}
	if (option == 6) {				//무지개
		color_state = 0;
	}
	if (option == 7) {				//하양
		color_state = 10;
		colorR = 0.9;
		colorG = 0.9;
		colorB = 0.9;
	}
}

void sub_menu_function3(int option)	//서브메뉴
{
	GLint index;
	printf("지붕색깔 선택 \n");
	if (option == 1) {				//빨강
		color2_state = 10;
		colorR2 = 1;
		colorG2 = 0;
		colorB2 = 0;
	}
	if (option == 2) {				//노랑
		color2_state = 10;
		colorR2 = 1;
		colorG2 = 1;
		colorB2 = 0;
	}
	if (option == 3) {				//초록
		color2_state = 10;
		colorR2 = 0;
		colorG2 = 0.9;
		colorB2 = 0;
	}
	if (option == 4) {				//파랑
		color2_state = 10;
		colorR2 = 0;
		colorG2 = 0;
		colorB2 = 0.9;
	}
	if (option == 5) {				//보라
		color2_state = 10;
		colorR2 = 0.9;
		colorG2 = 0;
		colorB2 = 0.9;
	}
	if (option == 6) {				//무지개
		color2_state = 0;
	}
	if (option == 7) {				//하양
		color2_state = 10;
		colorR2 = 0.9;
		colorG2 = 0.9;
		colorB2 = 0.9;
	}
}


void sub_menu_function4(int option)	//서브메뉴
{
	GLint index;
	printf("조명색깔 선택 \n");
	if (option == 1) {				//빨강
		color3_state = 10;
		colorR3 = 1;
		colorG3 = 0;
		colorB3 = 0;
	}
	if (option == 2) {				//노랑
		color3_state = 10;
		colorR3 = 1;
		colorG3 = 1;
		colorB3 = 0;
	}
	if (option == 3) {				//초록
		color3_state = 10;
		colorR3 = 0;
		colorG3 = 0.9;
		colorB3 = 0;
	}
	if (option == 4) {				//파랑
		color3_state = 10;
		colorR3 = 0;
		colorG3 = 0;
		colorB3 = 0.9;
	}
	if (option == 5) {				//보라
		color3_state = 10;
		colorR3 = 0.9;
		colorG3 = 0;
		colorB3 = 0.9;
	}
	if (option == 6) {				//무지개
		color3_state = 0;
	}
	if (option == 7) {				//하양
		color3_state = 10;
		colorR3 = 1.0;
		colorG3 = 1.0;
		colorB3 = 1.0;
	}
}


void falling_star1(void) {
	GLfloat emission[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat emission_off[] = { 0.0, 0.0, 0.0, 1.0 };
	glPushMatrix();
	glRotatef(angle_star1, 0, 0, 1);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
	glBindTexture(GL_TEXTURE_2D, texName[26]);
	glBegin(GL_QUADS);
	glColor4f(1, 1, 1, 0.1);
	glTexCoord2f(0, 1); glVertex3f(-10, 134, 10);
	glTexCoord2f(1, 1); glVertex3f(10, 134, 10);
	glTexCoord2f(1, 0); glVertex3f(10, 134, -10);
	glTexCoord2f(0, 0); glVertex3f(-10, 134, -10);
	glEnd();
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission_off);
	glPopMatrix();
}

void falling_star2(void) {
	GLfloat emission[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat emission_off[] = { 0.0, 0.0, 0.0, 1.0 };
	glPushMatrix();
	glRotatef(30, 0, 1, 0);
	glRotatef(angle_star2, 0, 0, 1);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
	glBindTexture(GL_TEXTURE_2D, texName[26]);
	glBegin(GL_QUADS);
	glColor4f(1, 1, 1, 0.1);
	glTexCoord2f(0, 1); glVertex3f(-10, 134, 10);
	glTexCoord2f(1, 1); glVertex3f(10, 134, 10);
	glTexCoord2f(1, 0); glVertex3f(10, 134, -10);
	glTexCoord2f(0, 0); glVertex3f(-10, 134, -10);
	glEnd();
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission_off);
	glPopMatrix();
}

void falling_star3(void) {
	GLfloat emission[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat emission_off[] = { 0.0, 0.0, 0.0, 1.0 };
	glPushMatrix();
	glRotatef(60, 0, 1, 0);
	glRotatef(angle_star3, 0, 0, 1);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
	glBindTexture(GL_TEXTURE_2D, texName[26]);
	glBegin(GL_QUADS);
	glColor4f(1, 1, 1, 0.1);
	glTexCoord2f(0, 1); glVertex3f(-10, 134, 10);
	glTexCoord2f(1, 1); glVertex3f(10, 134, 10);
	glTexCoord2f(1, 0); glVertex3f(10, 134, -10);
	glTexCoord2f(0, 0); glVertex3f(-10, 134, -10);
	glEnd();
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission_off);
	glPopMatrix();
}

void falling_star4(void) {
	GLfloat emission[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat emission_off[] = { 0.0, 0.0, 0.0, 1.0 };
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glRotatef(angle_star4, 0, 0, 1);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
	glBindTexture(GL_TEXTURE_2D, texName[26]);
	glBegin(GL_QUADS);
	glColor4f(1, 1, 1, 0.1);
	glTexCoord2f(0, 1); glVertex3f(-10, 134, 10);
	glTexCoord2f(1, 1); glVertex3f(10, 134, 10);
	glTexCoord2f(1, 0); glVertex3f(10, 134, -10);
	glTexCoord2f(0, 0); glVertex3f(-10, 134, -10);
	glEnd();
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission_off);
	glPopMatrix();
}

void falling_star5(void) {
	GLfloat emission[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat emission_off[] = { 0.0, 0.0, 0.0, 1.0 };
	glPushMatrix();
	glRotatef(120, 0, 1, 0);
	glRotatef(angle_star5, 0, 0, 1);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
	glBindTexture(GL_TEXTURE_2D, texName[26]);
	glBegin(GL_QUADS);
	glColor4f(1, 1, 1, 0.1);
	glTexCoord2f(0, 1); glVertex3f(-10, 134, 10);
	glTexCoord2f(1, 1); glVertex3f(10, 134, 10);
	glTexCoord2f(1, 0); glVertex3f(10, 134, -10);
	glTexCoord2f(0, 0); glVertex3f(-10, 134, -10);
	glEnd();
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission_off);
	glPopMatrix();
}

void falling_star6(void) {
	GLfloat emission[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat emission_off[] = { 0.0, 0.0, 0.0, 1.0 };
	glPushMatrix();
	glRotatef(150, 0, 1, 0);
	glRotatef(angle_star6, 0, 0, 1);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
	glBindTexture(GL_TEXTURE_2D, texName[26]);
	glBegin(GL_QUADS);
	glColor4f(1, 1, 1, 0.1);
	glTexCoord2f(0, 1); glVertex3f(-10, 134, 10);
	glTexCoord2f(1, 1); glVertex3f(10, 134, 10);
	glTexCoord2f(1, 0); glVertex3f(10, 134, -10);
	glTexCoord2f(0, 0); glVertex3f(-10, 134, -10);
	glEnd();
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission_off);
	glPopMatrix();
}

void falling_star7(void) {
	GLfloat emission[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat emission_off[] = { 0.0, 0.0, 0.0, 1.0 };
	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glRotatef(angle_star7, 0, 0, 1);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
	glBindTexture(GL_TEXTURE_2D, texName[26]);
	glBegin(GL_QUADS);
	glColor4f(1, 1, 1, 0.1);
	glTexCoord2f(0, 1); glVertex3f(-10, 134, 10);
	glTexCoord2f(1, 1); glVertex3f(10, 134, 10);
	glTexCoord2f(1, 0); glVertex3f(10, 134, -10);
	glTexCoord2f(0, 0); glVertex3f(-10, 134, -10);
	glEnd();
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission_off);
	glPopMatrix();
}

void falling_star8(void) {
	GLfloat emission[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat emission_off[] = { 0.0, 0.0, 0.0, 1.0 };
	glPushMatrix();
	glRotatef(210, 0, 1, 0);
	glRotatef(angle_star8, 0, 0, 1);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
	glBindTexture(GL_TEXTURE_2D, texName[26]);
	glBegin(GL_QUADS);
	glColor4f(1, 1, 1, 0.1);
	glTexCoord2f(0, 1); glVertex3f(-10, 134, 10);
	glTexCoord2f(1, 1); glVertex3f(10, 134, 10);
	glTexCoord2f(1, 0); glVertex3f(10, 134, -10);
	glTexCoord2f(0, 0); glVertex3f(-10, 134, -10);
	glEnd();
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission_off);
	glPopMatrix();
}

void falling_star9(void) {
	GLfloat emission[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat emission_off[] = { 0.0, 0.0, 0.0, 1.0 };
	glPushMatrix();
	glRotatef(240, 0, 1, 0);
	glRotatef(angle_star9, 0, 0, 1);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
	glBindTexture(GL_TEXTURE_2D, texName[26]);
	glBegin(GL_QUADS);
	glColor4f(1, 1, 1, 0.1);
	glTexCoord2f(0, 1); glVertex3f(-10, 134, 10);
	glTexCoord2f(1, 1); glVertex3f(10, 134, 10);
	glTexCoord2f(1, 0); glVertex3f(10, 134, -10);
	glTexCoord2f(0, 0); glVertex3f(-10, 134, -10);
	glEnd();
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission_off);
	glPopMatrix();
}

void falling_star10(void) {
	GLfloat emission[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat emission_off[] = { 0.0, 0.0, 0.0, 1.0 };
	glPushMatrix();
	glRotatef(270, 0, 1, 0);
	glRotatef(angle_star9, 0, 0, 1);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
	glBindTexture(GL_TEXTURE_2D, texName[26]);
	glBegin(GL_QUADS);
	glColor4f(1, 1, 1, 0.1);
	glTexCoord2f(0, 1); glVertex3f(-10, 134, 10);
	glTexCoord2f(1, 1); glVertex3f(10, 134, 10);
	glTexCoord2f(1, 0); glVertex3f(10, 134, -10);
	glTexCoord2f(0, 0); glVertex3f(-10, 134, -10);
	glEnd();
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission_off);
	glPopMatrix();
}

void falling_star11(void) {
	GLfloat emission[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat emission_off[] = { 0.0, 0.0, 0.0, 1.0 };
	glPushMatrix();
	glRotatef(300, 0, 1, 0);
	glRotatef(angle_star9, 0, 0, 1);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
	glBindTexture(GL_TEXTURE_2D, texName[26]);
	glBegin(GL_QUADS);
	glColor4f(1, 1, 1, 0.1);
	glTexCoord2f(0, 1); glVertex3f(-10, 134, 10);
	glTexCoord2f(1, 1); glVertex3f(10, 134, 10);
	glTexCoord2f(1, 0); glVertex3f(10, 134, -10);
	glTexCoord2f(0, 0); glVertex3f(-10, 134, -10);
	glEnd();
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission_off);
	glPopMatrix();
}

void falling_star12(void) {
	GLfloat emission[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat emission_off[] = { 0.0, 0.0, 0.0, 1.0 };
	glPushMatrix();
	glRotatef(330, 0, 1, 0);
	glRotatef(angle_star9, 0, 0, 1);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
	glBindTexture(GL_TEXTURE_2D, texName[26]);
	glBegin(GL_QUADS);
	glColor4f(1, 1, 1, 0.1);
	glTexCoord2f(0, 1); glVertex3f(-10, 134, 10);
	glTexCoord2f(1, 1); glVertex3f(10, 134, 10);
	glTexCoord2f(1, 0); glVertex3f(10, 134, -10);
	glTexCoord2f(0, 0); glVertex3f(-10, 134, -10);
	glEnd();
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission_off);
	glPopMatrix();
}
