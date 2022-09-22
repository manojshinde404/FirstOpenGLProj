#include<GL/glut.h>
#include <time.h>
double w=1280,h=720;
//ouble view[3]={15,4,19};
//double look[3]={2,2,2};
double view[3]={1,3,19};
double look[3]={2,2,2};
//declarating quadric objects
GLUquadricObj *Cylinder;
GLUquadricObj *Disk;
struct tm *newtime;
time_t ltime;
GLfloat angle1;

//initialisation
void myinit(void)
{
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glFrustum(-1.0,1.0,-1*w/h,1*w/h,1,200.0);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();


//defining new quadric object

Cylinder = gluNewQuadric();

//to set drawing style
gluQuadricDrawStyle( Cylinder, GLU_FILL);

//to set automatic normals
gluQuadricNormals( Cylinder,GLU_SMOOTH);
Disk = gluNewQuadric();
gluQuadricDrawStyle( Disk, GLU_FILL);
gluQuadricNormals( Disk, GLU_SMOOTH);
GLfloat gam[]={0.2,.2,.2,1};
glLightModelfv(GL_LIGHT_MODEL_AMBIENT,gam);
}



//set material property
void matprop(GLfloat amb[],GLfloat dif[],GLfloat spec[],GLfloat shi[])
{
glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,amb);
glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,dif);
glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,spec);
glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shi);
}

//to create earth
void earth(void)
{
GLfloat ambient[]={0.0,0.05,0.0,1};
GLfloat specular[]={0.04,0.7,0.04,1};
GLfloat diffuse[]={.4,.5,0.4,1};
GLfloat shininess[]={0.078125};
matprop(ambient,diffuse,specular,shininess);
GLfloat lightIntensity[]={.7,.7,.7,1};
GLfloat light_position[]={2,5,3,0};
glLightfv(GL_LIGHT0,GL_POSITION,light_position);
glLightfv(GL_LIGHT0,GL_DIFFUSE,lightIntensity);

glPushMatrix();
glTranslated(0,-.25,0);
glScaled(10000,.5,1000000);
glutSolidCube(1.0);
glPopMatrix();
glFlush();
}

//to create wall
void wall(double thickness)
{
glPushMatrix();
glTranslated(2,.5*thickness,2);
glScaled(4.0,thickness,4.0);
glutSolidCube(1.0);
glPopMatrix();
}

void myclock()
{
GLfloat mat_ambient[]={.4,.8,.4,1};
GLfloat mat_specular[]={1,1,1,1};
GLfloat mat_diffuse[]={0.4,.8,.4,1};
GLfloat mat_shininess[]={50};
matprop(mat_ambient,mat_diffuse,mat_specular,mat_shininess);
int hour_ticks , sec_ticks;

glPushMatrix();
glTranslated(3,6.5,10);
glScaled(.03,.06,.03);
glPushMatrix(); // Draw clock face
glTranslatef( 0, 0, 1.0);
gluDisk(Disk, 0, 7, 32, 16);
glPopMatrix();

GLfloat mat_ambien[]={1,0,0,1};
matprop(mat_ambien,mat_diffuse,mat_specular,mat_shininess);
glPushMatrix();
glTranslatef( 0, 0, 1.95);
gluDisk(Disk, 0, .8, 32, 16);
glPopMatrix();

GLfloat ambient[]={0,0,0,1};
GLfloat specular[]={1,1,1,1};
GLfloat diffuse[]={0,0,0,1};
matprop(ambient,diffuse,specular,mat_shininess);
// Draw hour hand
glPushMatrix();
glColor3f(1.0, 0.5, 0.5);
glTranslatef( 0, 0, 1.5);
glRotatef( -(360/12) * (newtime->tm_hour+newtime->tm_min/60.0), 0.0,
0.0, 1.0);
glRotatef( -90, 1.0, 0.0, 0.0);
gluCylinder(Cylinder, 0.45, 0, 4, 16, 16);
glPopMatrix();
GLfloat
ambient1[]={0,0,1,1};
GLfloat specular1[]={1,1,1,1};
GLfloat diffuse1[]={0,0,1,1};
matprop(ambient1,diffuse1,specular1,mat_shininess);
// Draw minute hand
glPushMatrix();
glColor3f(1.0, 0.5, 1.0);
glTranslatef( 0, 0, 1.25);
glRotatef( -(360/60) * newtime->tm_min, 0.0, 0.0, 1.0);
glRotatef(-90, 1.0, 0.0, 0.0);
gluCylinder(Cylinder, 0.4, 0, 6, 16, 16);
glPopMatrix();
GLfloat
ambient2[]={1,0,0,1};
GLfloat specular2[]={1,1,1,1};
GLfloat diffuse2[]={1,0,0,1};
matprop(ambient2,diffuse2,specular2,mat_shininess);
// Draw second hand
glPushMatrix();
glTranslatef( 0, 0, 1);
glRotatef(-(360/60) * newtime->tm_sec, 0.0, 0.0, 1.0);
glRotatef( -90, 1.0, 0.0, 0.0);
gluCylinder(Cylinder, 0.3, 0, 6, 16, 16);glPopMatrix();
GLfloat
ambient3[]={1,1,1,1};
GLfloat specular3[]={1,1,1,1};
GLfloat diffuse3[]={1,0,1,1};
matprop(ambient3,diffuse3,specular3,mat_shininess);
for(hour_ticks = 0; hour_ticks < 12; hour_ticks++)
{
glPushMatrix();// Draw next arm axis.
glTranslatef(0.0, 0.0, 1);
glRotatef( (360/12) * hour_ticks, 0.0, 0.0, 1.0);
glTranslatef( 6.0, 0.0, 0.0);
glutSolidCube(.8);
glPopMatrix();
}
for(sec_ticks = 0; sec_ticks < 60; sec_ticks++)
{
glPushMatrix();
glTranslatef(0.0, 0.0, 1.1);
glRotatef( (360/60) * sec_ticks, 0.0, 0.0, 1.0);
glTranslatef(6.0, 0.0, 0.0);
glutSolidCube(0.25);
glPopMatrix();
}
glPopMatrix();
}

void college(void)
{
GLfloat mat_ambient[]={1,0,0,1};
GLfloat mat_specular[]={1,1,1,1};
GLfloat mat_diffuse[]={1,1,.7,1};
GLfloat mat_shininess[]={50};
matprop(mat_ambient,mat_diffuse,mat_specular,mat_shininess);
GLfloat lightIntensity4[]={.7,.7,.7,.7};
GLfloat light_position4[]={3,1,.5,1};
glLightfv(GL_LIGHT6,GL_POSITION,light_position4);
glLightfv(GL_LIGHT6,GL_DIFFUSE,lightIntensity4);
glEnable(GL_LIGHT6);
glPushMatrix();
glTranslated(0,.15,0);

GLfloat ambient2[]={1,0,0,1};
GLfloat specular2[]={1,1,1,0};
GLfloat diffuse2[]={.7,1,0.8,1};
GLfloat shininess[]={50};
matprop(ambient2,diffuse2,specular2,shininess);

//floor
glPushMatrix();
glTranslated(-6,0,0);
glScaled(5,0.2,4);
glRotated(45,0,0,0);
wall(0.08);
glPopMatrix();

GLfloat ambient1[]={1,0,0,1};
GLfloat specular1[]={1,1,1,0};
GLfloat diffuse1[]={1,1,.7,1};
GLfloat shininess1[]={50};
matprop(ambient1,diffuse1,specular1,shininess1);

//left wall
glPushMatrix();
glTranslated(-4,0,1);
glScaled(3,1.5,3.01);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();


//right wall near front
glPushMatrix();
glTranslated(11,0.0,8.6);
glScaled(1,1,1.1);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();

//right wall in back
glPushMatrix();
glTranslated(11,0.0,1);
glScaled(1,1,1);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();

//back wall
glPushMatrix();
glTranslated(-4,0,1);
glScaled(3.75,1.5,1);
glRotated(-90.0,1,0,0);
wall(0.08);
glPopMatrix();

//front left wall of college
glPushMatrix();
glTranslated(-1.5,.8,13);
glRotated(-90,1,0,0);
glScaled(5,0.03,4);
glutSolidCube(1.0);
glPopMatrix();


//front left wall(middle) of college
glPushMatrix();
glTranslated(-2,3,13);
glRotated(-90,2,0,0);
glScaled(4,0.135,2);
glutSolidCube(1.0);
glPopMatrix();

//front right wall(middle) of college
glPushMatrix();
glTranslated(8.425,3,13);
glRotated(-90,2,0,0);
glScaled(5.05,0.135,2);
glutSolidCube(1.0);
glPopMatrix();

//front left room
//front left inside(back) wall of college
glPushMatrix();
glTranslated(-1,.8,10);
glRotated(-90,1,0,0);
glScaled(2,0.03,19.5);
glutSolidCube(1.0);
glPopMatrix();

//front left(inside room) wall of college
glPushMatrix();
glTranslated(-1.5,.8,12);
glRotated(-90,1,0,0);
glScaled(1,0.03,19.5);
glutSolidCube(1.0);
glPopMatrix();

//front left(inside right room) wall of college
glPushMatrix();
glTranslated(-0.2,.8,12);
glRotated(-90,1,0,0);
glScaled(0.4,0.03,19.5);
glutSolidCube(1.0);
glPopMatrix();

 //left wall inside room
glPushMatrix();
glTranslated(-2,0,10);
glScaled(0.5,2.65,0.5);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();

 //right wall inside room
glPushMatrix();
glTranslated(0,0,10);
glScaled(0.5,2.65,0.5);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();

//watchman room
//front right(inside) wall of room
glPushMatrix();
glTranslated(-2.5,.8,12.5);
glRotated(-90,1,0,0);
glScaled(3,0.03,19.5);
glutSolidCube(1.0);
glPopMatrix();

// princi room front right(inside) wall of room
glPushMatrix();
glTranslated(0,.8,12.5);
glRotated(-90,1,0,0);
glScaled(1,0.03,19.5);
glutSolidCube(1.0);
glPopMatrix();


//left wall
glPushMatrix();
glTranslated(0.5,0,12.5);
glScaled(0.1,2.65,0.1);
glRotated(90.0,0,0,1);
wall(0.08);
glPopMatrix();

/// Right side portion

//front right wall of college
glPushMatrix();
glTranslated(8.5,.8,13);
glRotated(-90,1,0,0);
glScaled(5,0.03,19.5);
glutSolidCube(1.0);
glPopMatrix();


//front right(inside) wall of room
glPushMatrix();
glTranslated(9.2,.8,12.5);
glRotated(-90,1,0,0);
glScaled(3.6,0.03,19.5);
glutSolidCube(1.0);
glPopMatrix();

// princi room front right(inside) wall of room
glPushMatrix();
glTranslated(6.5,.8,12.5);
glRotated(-90,1,0,0);
glScaled(1,0.03,19.5);
glutSolidCube(1.0);
glPopMatrix();


//left wall
glPushMatrix();
glTranslated(6,0,12.5);
glScaled(0.1,2.65,0.1);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();

//strong room

//backside wall of college
glPushMatrix();
glTranslated(7,.8,10);
glRotated(-90,1,0,0);
glScaled(2,0.03,19.5);
glutSolidCube(1.0);
glPopMatrix();

//left wall inside room
glPushMatrix();
glTranslated(6,0,10);
glScaled(0.5,2.65,0.5);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();

 //right wall inside room
glPushMatrix();
glTranslated(8,0,10);
glScaled(0.5,2.65,0.5);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();


//front left(inside room) wall of college
glPushMatrix();
glTranslated(7.5,.8,12);
glRotated(-90,1,0,0);
glScaled(1,0.03,19.5);
glutSolidCube(1.0);
glPopMatrix();

//front left(inside right room) wall of college
glPushMatrix();
glTranslated(6.25,.8,12);
glRotated(-90,1,0,0);
glScaled(0.5,0.03,19.5);
glutSolidCube(1.0);
glPopMatrix();


//internal square

//left wall
glPushMatrix();
glTranslated(1,0,10);
glScaled(0.5,2.65,0.5);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();

//right wall
glPushMatrix();
glTranslated(5,0,10);
glScaled(0.5,2.65,0.5);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();

//back wall(left)
glPushMatrix();
glTranslated(1,0,10);
glScaled(0.35,2.65,1);
glRotated(-90.0,1,0,0);
wall(0.08);
glPopMatrix();

//back wall(right)
glPushMatrix();
glTranslated(3.6,0,10);
glScaled(0.35,2.65,1);
glRotated(-90.0,1,0,0);
wall(0.08);
glPopMatrix();

//in hall
//left wall
glPushMatrix();
glTranslated(2.4,0,9.15);
glScaled(0.5,0.45,0.2);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();

//right wall
glPushMatrix();
glTranslated(3.6,0,9.15);
glScaled(0.5,0.45,0.2);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();

//left wall of corridor
glPushMatrix();
glTranslated(-2.5,0,9.15);
glScaled(1,0.45,0.2);
glRotated(90.0,0,0,1);
wall(0.08);
glPopMatrix();

//right wall of corridor
glPushMatrix();
glTranslated(8.6,0,9.15);
glScaled(1,0.45,0.2);
glRotated(90.0,0,0,1);
wall(0.08);
glPopMatrix();

glPushMatrix();
glTranslated(-0.1,.8,9.15);
glRotated(-90,1,0,0);
glScaled(5,0.03,2);
glutSolidCube(1.0);
glPopMatrix();

glPushMatrix();
glTranslated(-0.1,.8,8.15);
glRotated(-90,1,0,0);
glScaled(5,0.03,2);
glutSolidCube(1.0);
glPopMatrix();

glPushMatrix();
glTranslated(6.1,.8,9.15);
glRotated(-90,1,0,0);
glScaled(5,0.03,2);
glutSolidCube(1.0);
glPopMatrix();

glPushMatrix();
glTranslated(6.1,.8,8.15);
glRotated(-90,1,0,0);
glScaled(5,0.03,2);
glutSolidCube(1.0);
glPopMatrix();

//front left corridor wall
glPushMatrix();
glTranslated(-2.25,.8,9.95);
glRotated(-90,1,0,0);
glScaled(0.6,0.03,3);
glutSolidCube(1.0);
glPopMatrix();

//front right corridor wall
glPushMatrix();
glTranslated(8.3,.8,9.95);
glRotated(-90,1,0,0);
glScaled(0.65,0.03,2);
glutSolidCube(1.0);
glPopMatrix();

//left wall
glPushMatrix();
glTranslated(2.4,0,7.35);
glScaled(0.5,0.45,0.2);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();

//right wall
glPushMatrix();
glTranslated(3.6,0,7.37);
glScaled(0.5,0.45,0.2);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();


//mech dept left
glPushMatrix();
glTranslated(-0.1,.8,7.35);
glRotated(-90,1,0,0);
glScaled(5,0.03,19.5);
glutSolidCube(1.0);
glPopMatrix();

//mech dept right
glPushMatrix();
glTranslated(6.1,.8,7.35);
glRotated(-90,1,0,0);
glScaled(5,0.03,19.5);
glutSolidCube(1.0);
glPopMatrix();

//lib dept right back
glPushMatrix();
glTranslated(-1,.8,3);
glRotated(-90,1,0,0);
glScaled(2,0.03,19.5);
glutSolidCube(1.0);
glPopMatrix();

//lib dept right back
glPushMatrix();
glTranslated(2,.8,3);
glRotated(-90,1,0,0);
glScaled(2,0.03,19.5);
glutSolidCube(1.0);
glPopMatrix();

//lib dept door up
glPushMatrix();
glTranslated(0,8,3);
glRotated(-90,1,0,0);
glScaled(2,0.03,5);
glutSolidCube(1.0);
glPopMatrix();

// lib left wall
glPushMatrix();
glTranslated(-2,0,1);
glScaled(0.5,2.65,0.5);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();

//lib right wall
glPushMatrix();
glTranslated(3,0,1);
glScaled(0.5,2.65,0.5);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();

//audi right back
glPushMatrix();
glTranslated(5.25,.8,5.5);
glRotated(-90,1,0,0);
glScaled(3,0.03,19.5);
glutSolidCube(1.0);
glPopMatrix();

//audi dept right back
glPushMatrix();
glTranslated(8,.8,5.5);
glRotated(-90,1,0,0);
glScaled(1,0.03,19.5);
glutSolidCube(1.0);
glPopMatrix();

//audi dept door up
glPushMatrix();
glTranslated(7,7.5,5.5);
glRotated(-90,1,0,0);
glScaled(1,0.03,6.3);
glutSolidCube(1.0);
glPopMatrix();

//audi right back
glPushMatrix();
glTranslated(5.25,.8,2.5);
glRotated(-90,1,0,0);
glScaled(3,0.03,19.5);
glutSolidCube(1.0);
glPopMatrix();

//audi dept right back
glPushMatrix();
glTranslated(8,.8,2.5);
glRotated(-90,1,0,0);
glScaled(1,0.03,19.5);
glutSolidCube(1.0);
glPopMatrix();

// lib left wall
glPushMatrix();
glTranslated(3.75,0,2.5);
glScaled(1,2.65,0.75);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();

//lib right wall
glPushMatrix();
glTranslated(8.5,0,2.5);
glScaled(1,2.65,0.75);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();

// infosis left end wall
glPushMatrix();
glTranslated(-3.2,0,3);
glScaled(0.25,2.65,0.2);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();

// infosis door up
glPushMatrix();
glTranslated(-3.2,6,3.8);
glScaled(0.25,1.13,0.2);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();

// infosis left begin wall
glPushMatrix();
glTranslated(-3.2,0,4.5);
glScaled(0.25,2.65,0.2);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();

//infosis back  wall
glPushMatrix();
glTranslated(-3.6,.8,3);
glRotated(-90,1,0,0);
glScaled(0.8,0.03,19.5);
glutSolidCube(1.0);
glPopMatrix();

//infosis front  wall
glPushMatrix();
glTranslated(-3.6,.8,5.3);
glRotated(-90,1,0,0);
glScaled(0.8,0.03,19.5);
glutSolidCube(1.0);
glPopMatrix();

// washroom left end wall
glPushMatrix();
glTranslated(-3.2,0,6);
glScaled(0.25,2.65,0.2);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();

// washroom door up
glPushMatrix();
glTranslated(-3.2,6,6.7);
glScaled(0.25,1.13,0.2);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();

// washroom left begin wall
glPushMatrix();
glTranslated(-3.2,0,7.5);
glScaled(0.25,2.65,0.2);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();

//washroom front  wall
glPushMatrix();
glTranslated(-3.6,.8,8.3);
glRotated(-90,1,0,0);
glScaled(0.8,0.03,19.5);
glutSolidCube(1.0);
glPopMatrix();

//washroom back wall
glPushMatrix();
glTranslated(-3.6,.8,6);
glRotated(-90,1,0,0);
glScaled(0.8,0.03,19.5);
glutSolidCube(1.0);
glPopMatrix();

//exam section left behid wall
glPushMatrix();
glTranslated(10,0.0,9);
glScaled(1,2.65,0.3);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();

//exam section door up
glPushMatrix();
glTranslated(10,6,9.7);
glScaled(1,1.13,0.3);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();

//exam section left begin wall
glPushMatrix();
glTranslated(10,0.0,10.8);
glScaled(1,2.65,0.3);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();

//exam section front wall
glPushMatrix();
glTranslated(10.5,.8,12);
glRotated(-90,1,0,0);
glScaled(1,0.03,19.5);
glutSolidCube(1.0);
glPopMatrix();

//exam section back wall
glPushMatrix();
glTranslated(10.5,.8,9);
glRotated(-90,1,0,0);
glScaled(1,0.03,19.5);
glutSolidCube(1.0);
glPopMatrix();

//chem lab left end wall
glPushMatrix();
glTranslated(10,0.0,2.3);
glScaled(1,2.65,0.3);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();

//chem door wall
glPushMatrix();
glTranslated(10,6,3);
glScaled(1,1.13,0.3);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();

//chem lab left begin wall
glPushMatrix();
glTranslated(10,0.0,4);
glScaled(0.8,2.65,0.25);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();

//chem front wall
glPushMatrix();
glTranslated(10.5,.8,5);
glRotated(-90,1,0,0);
glScaled(1,0.03,19.5);
glutSolidCube(1.0);
glPopMatrix();

//chem back wall
glPushMatrix();
glTranslated(10.5,.8,2.3);
glRotated(-90,1,0,0);
glScaled(1,0.03,19.5);
glutSolidCube(1.0);
glPopMatrix();




//front left wall 1
glPushMatrix();
glTranslated(-3.9,0,13.05);
glRotated(-90,1,0,0);
glScaled(0.4,0.03,12);
glutSolidCube(1.0);
glPopMatrix();

//front left wall 1
glPushMatrix();
glTranslated(-3.25,0,13.05);
glRotated(-90,1,0,0);
glScaled(0.1,0.03,12);
glutSolidCube(1.0);
glPopMatrix();


//front left wall 3
glPushMatrix();
glTranslated(-2.7,0,13.05);
glRotated(-90,1,0,0);
glScaled(0.6,0.03,12);
glutSolidCube(1.0);
glPopMatrix();

//front left wall 4
glPushMatrix();
glTranslated(-1.95,0,13.05);
glRotated(-90,1,0,0);
glScaled(0.1,0.03,12);
glutSolidCube(1.0);
glPopMatrix();

//front left wall 5
glPushMatrix();
glTranslated(-1.45,0,13.05);
glRotated(-90,1,0,0);
glScaled(0.1,0.03,12);
glutSolidCube(1.0);
glPopMatrix();

//front left wall 6
glPushMatrix();
glTranslated(-0.7,0,13.05);
glRotated(-90,1,0,0);
glScaled(0.6,0.03,12);
glutSolidCube(1.0);
glPopMatrix();

//front left wall 7
glPushMatrix();
glTranslated(0.25,0,13.05);
glRotated(-90,1,0,0);
glScaled(0.5,0.03,12);
glutSolidCube(1.0);
glPopMatrix();

//front right wall 1
glPushMatrix();
glTranslated(6.15,0,13.05);
glRotated(-90,1,0,0);
glScaled(0.5,0.03,12);
glutSolidCube(1.0);
glPopMatrix();

//front right wall 2
glPushMatrix();
glTranslated(7.1,0,13.05);
glRotated(-90,1,0,0);
glScaled(0.6,0.03,12);
glutSolidCube(1.0);
glPopMatrix();

//front right wall 3
glPushMatrix();
glTranslated(7.85,0,13.05);
glRotated(-90,1,0,0);
glScaled(0.1,0.03,12);
glutSolidCube(1.0);
glPopMatrix();

//front right wall 3
glPushMatrix();
glTranslated(8.35,0,13.05);
glRotated(-90,1,0,0);
glScaled(0.1,0.03,12);
glutSolidCube(1.0);
glPopMatrix();

//front right wall 4
glPushMatrix();
glTranslated(9.1,0,13.05);
glRotated(-90,1,0,0);
glScaled(0.6,0.03,12);
glutSolidCube(1.0);
glPopMatrix();

//front right wall 3
glPushMatrix();
glTranslated(9.65,0,13.05);
glRotated(-90,1,0,0);
glScaled(0.1,0.03,12);
glutSolidCube(1.0);
glPopMatrix();

//front right wall 3
glPushMatrix();
glTranslated(10.15,0,13.05);
glRotated(-90,1,0,0);
glScaled(0.1,0.03,12);
glutSolidCube(1.0);
glPopMatrix();

//front right wall 3
glPushMatrix();
glTranslated(10.68,0,13.05);
glRotated(-90,1,0,0);
glScaled(0.6,0.03,12);
glutSolidCube(1.0);
glPopMatrix();

//right wall in back
glPushMatrix();
glTranslated(11,0.0,8.6);
glScaled(1,2,0.1);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();

//right wall in back
glPushMatrix();
glTranslated(11,0.0,8.6);
glScaled(1,2,0.4);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();

//right wall in back
glPushMatrix();
glTranslated(11,0.0,10.5);
glScaled(1,2,0.05);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();

//right wall in back
glPushMatrix();
glTranslated(11,0.0,11.02);
glScaled(1,2,0.05);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();

//right wall in back
glPushMatrix();
glTranslated(11,0.0,11.6);
glScaled(1,2,0.15);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();

//right wall in back
glPushMatrix();
glTranslated(11,0.0,12.6);
glScaled(1,1.5,0.12);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();

//right wall in back
glPushMatrix();
glTranslated(11.0125,2,8.967);
glScaled(1,0.5,0.91);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();

//right wall in back
glPushMatrix();
glTranslated(11.005,0.0,4.5);
glScaled(1,1.5,0.12);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();

glPushMatrix();
glTranslated(11.005,0.0,3.4);
glScaled(1,1.5,0.18);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();

//right wall in back
glPushMatrix();
glTranslated(11,0.0,2.8);
glScaled(1,2,0.05);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();

//right wall in back
glPushMatrix();
glTranslated(11,0.0,2.2);
glScaled(1,2,0.05);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();

//right wall in back
glPushMatrix();
glTranslated(11,0.0,1);
glScaled(1,1.5,0.2);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();

//right wall in back
glPushMatrix();
glTranslated(11.015,2,1);
glScaled(1,0.5,1);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();

GLfloat mat_ambient2[]={0.25,0.20725,0.20725,0};
GLfloat mat_specular2[]={0.296648,0.296648,1};
GLfloat mat_diffuse2[]={1,0.829,0.829,0};
GLfloat mat_shininess2[]={0.088};

matprop(mat_ambient2,mat_diffuse2,mat_specular2,mat_shininess2);


//front left wall of college
glPushMatrix();
glTranslated(1.5,.8,13);
glRotated(-90,1,0,0);
glScaled(2,0.1,8);
glutSolidCube(1.0);
glPopMatrix();



//front right wall of college
glPushMatrix();
glTranslated(5,.8,13);
glRotated(-90,1,0,0);
glScaled(2,0.1,8);
glutSolidCube(1.0);
glPopMatrix();

//right wall near front
glPushMatrix();
glTranslated(11,0.0,7.4);
glScaled(1,1.5,0.3);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();

//right wall in back
glPushMatrix();
glTranslated(11,0.0,5);
glScaled(1,1.5,0.4);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();

//front left glass 1
glPushMatrix();
glTranslated(-3.5,0,13.05);
glRotated(-90,1,0,0);
glScaled(0.4,0.03,16);
glutSolidCube(1.0);
glPopMatrix();

//front left glass 2
glPushMatrix();
glTranslated(-3.1,0,13.05);
glRotated(-90,1,0,0);
glScaled(0.2,0.03,16);
glutSolidCube(1.0);
glPopMatrix();

//front left glass 2
glPushMatrix();
glTranslated(-2.2,0,13.05);
glRotated(-90,1,0,0);
glScaled(0.4,0.03,16);
glutSolidCube(1.0);
glPopMatrix();

//front left glass 4
glPushMatrix();
glTranslated(-1.7,0,13.05);
glRotated(-90,1,0,0);
glScaled(0.4,0.03,16);
glutSolidCube(1.0);
glPopMatrix();

//front left glass 5
glPushMatrix();
glTranslated(-1.2,0,13.05);
glRotated(-90,1,0,0);
glScaled(0.4,0.03,16);
glutSolidCube(1.0);
glPopMatrix();

//front left glass 6
glPushMatrix();
glTranslated(-0.2,0,13.05);
glRotated(-90,1,0,0);
glScaled(0.4,0.03,16);
glutSolidCube(1.0);
glPopMatrix();

//front right glass 1
glPushMatrix();
glTranslated(6.6,0,13.05);
glRotated(-90,1,0,0);
glScaled(0.4,0.03,16);
glutSolidCube(1.0);
glPopMatrix();

//front right glass 2
glPushMatrix();
glTranslated(7.6,0,13.05);
glRotated(-90,1,0,0);
glScaled(0.4,0.03,16);
glutSolidCube(1.0);
glPopMatrix();

//front right glass 3
glPushMatrix();
glTranslated(8.1,0,13.05);
glRotated(-90,1,0,0);
glScaled(0.4,0.03,16);
glutSolidCube(1.0);
glPopMatrix();

//front right glass 3
glPushMatrix();
glTranslated(8.6,0,13.05);
glRotated(-90,1,0,0);
glScaled(0.4,0.03,16);
glutSolidCube(1.0);
glPopMatrix();

//front right glass 3
glPushMatrix();
glTranslated(9.5,0,13.05);
glRotated(-90,1,0,0);
glScaled(0.2,0.03,16);
glutSolidCube(1.0);
glPopMatrix();

//front right glass 3
glPushMatrix();
glTranslated(9.9,0,13.05);
glRotated(-90,1,0,0);
glScaled(0.4,0.03,16);
glutSolidCube(1.0);
glPopMatrix();

//front right glass 3
glPushMatrix();
glTranslated(10.3,0,13.05);
glRotated(-90,1,0,0);
glScaled(0.2,0.03,16);
glutSolidCube(1.0);
glPopMatrix();

//right side walls

//right wall in back
glPushMatrix();
glTranslated(11.012,0.0,9);
glScaled(1,2,0.1);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();

//right wall in back
glPushMatrix();
glTranslated(11.012,0.0,10.2);
glScaled(1,2,0.1);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();

//right wall in back
glPushMatrix();
glTranslated(11.012,0.0,10.7);
glScaled(1,2,0.1);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();

//right wall in back
glPushMatrix();
glTranslated(11.012,0.0,11.2);
glScaled(1,2,0.1);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();

//right wall in back
glPushMatrix();
glTranslated(11.012,0.0,12.2);
glScaled(1,2,0.1);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();

//right wall in back
glPushMatrix();
glTranslated(11.012,0.0,4.1);
glScaled(1,2,0.1);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();

//right wall in back
glPushMatrix();
glTranslated(11.012,0.0,3);
glScaled(1,2,0.1);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();

//right wall in back
glPushMatrix();
glTranslated(11.012,0.0,2.4);
glScaled(1,2,0.1);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();

//right wall in back
glPushMatrix();
glTranslated(11.012,0.0,1.8);
glScaled(1,2,0.1);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();

//top walls white
GLfloat mat_ambient9[]={0.0,0.0,0.0,0};
GLfloat mat_specular9[]={0.70,0.70,0.70,1};
GLfloat mat_diffuse9[]={0.55,0.55,0.55,0};
GLfloat mat_shininess9[]={0.25};

matprop(mat_ambient9,mat_diffuse9,mat_specular9,mat_shininess9);

//code for roof
glPushMatrix();
glTranslated(-4,10.5,0.9);
glScaled(3.75,2.1,3.03);
glRotated(45,0,0,0);
wall(0.08);
glPopMatrix();



//front left glass 6
glPushMatrix();
glTranslated(3.45,8,13.05);
glRotated(-90,1,0,0);
glScaled(15.05,0.01,5.15);
glutSolidCube(1.0);
glPopMatrix();

//right wall in back
glPushMatrix();
glTranslated(11.01,6,1.05);
glScaled(2,1.13,3);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();

//extra wall in back
glPushMatrix();
glTranslated(11.01,6,0.85);
glScaled(0.05,1.13,3);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();

//c
glPushMatrix();
glTranslated(5.6,-2,25.7);
glScaled(3.09,1.13,1);
glRotated(-90.0,1,0,0);
wall(0.08);
glPopMatrix();

//r

glPushMatrix();
glTranslated(-10,-2,25.7);
glScaled(3.09,1.13,1);
glRotated(-90.0,1,0,0);
wall(0.08);
glPopMatrix();




//xy
glPushMatrix();
glTranslated(17.94,-1,-10.02);
glScaled(16.2,1.1,3.6);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();


//abc
glPushMatrix();
glTranslated(17.94,-1,8.02);
glScaled(12.2,1.1,4.5);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();


//left side gate
glPushMatrix();
glTranslated(-9.90,-1.5,-10);
glScaled(19.1,1.13,9.6);
glRotated(90.0,0,0,2);
wall(0.02);
glPopMatrix();


	

//back gate
glPushMatrix();
glTranslated(-10,-1.5,-10);
glScaled(7.0,1.13,8.9);
glRotated(-90.0,1,0,0);
wall(0.02);
glPopMatrix();




//gumaz(dom)
glPushMatrix();
glTranslatef(3,11.5,7.5);
glScaled(4,4.0,2.8);
glutSolidSphere(0.9,80,120);
glPopMatrix();
/*glPushMatrix();
glTranslatef(2.9,13,7.5);
glScaled(4,4.0,2.8);
glutSolidSphere(0.8,80,120);
glPopMatrix();
*/




GLfloat ambient15[]={0,0,0,0};
GLfloat specular15[]={0.70,0.70,0.70,1};
GLfloat diffuse15[]={0.55,0.55,0.55,0};
GLfloat shininess15[]={0.25};
matprop(ambient15,diffuse15,specular15,shininess15);
GLfloat lightIntensity15[]={.7,.7,.7,1};
GLfloat light_position15[]={0,0,0,0};
glLightfv(GL_LIGHT0,GL_POSITION,light_position15);
glLightfv(GL_LIGHT0,GL_DIFFUSE,lightIntensity15);


/*//dome
glPushMatrix();
glTranslated(3,10.5,10.5);
glRotated(-90,1,0,0);
glScaled(1,1,1);
glutSolidSphere(2.5,250,25);
glPopMatrix();
*/





// white back wall
glPushMatrix();
glTranslated(-4,6,1);
glScaled(3.75,1.13,1.5);
glRotated(-90.0,1,0,0);
wall(0.08);
glPopMatrix();

//left wall
glPushMatrix();
glTranslated(-3.94,6,1.0);
glScaled(3.2,1.13,3.01);
glRotated(90.0,0,0,1);
wall(0.02);
glPopMatrix();

//slege walls odisidion
GLfloat mat_ambient5[]={0.05,0.05,0.05,0};
GLfloat mat_specular5[]={0.70,0.70,0.70,1};
GLfloat mat_diffuse5[]={0.05,0.05,0.05,0};
GLfloat mat_shininess5[]={0.078125};

matprop(mat_ambient5,mat_diffuse5,mat_specular5,mat_shininess5);

//clock wall
glPushMatrix();
glTranslated(3,6.5,10);
glRotated(-90,1,0,0);
glScaled(1.2,0.03,1.5);
glutSolidCube(1.0);
glPopMatrix();

//pole1
glPushMatrix();
glTranslated(1,0.2,14);
glRotated(-90,1,0,0);
glScaled(0.15,0.15,9.2);
glutSolidCube(1.0);
glPopMatrix();

//square for pole1
glPushMatrix();
glTranslated(1,4.6,14);
glRotated(-90,1,0,0);
glScaled(0.2,0.2,0.2);
glutSolidCube(1.0);
glPopMatrix();

//square for pole1
glPushMatrix();
glTranslated(1,0.2,14);
glRotated(-90,1,0,0);
glScaled(0.2,0.2,0.2);
glutSolidCube(1.0);
glPopMatrix();

//pole2
glPushMatrix();
glTranslated(0.75,0.2,14);
glRotated(-90,1,0,0);
glScaled(0.15,0.15,9.2);
glutSolidCube(1.0);
glPopMatrix();

//square for pole2
glPushMatrix();
glTranslated(0.75,4.6,14);
glRotated(-90,1,0,0);
glScaled(0.2,0.2,0.2);
glutSolidCube(1.0);
glPopMatrix();

//square for pole2
glPushMatrix();
glTranslated(0.75,0.2,14);
glRotated(-90,1,0,0);
glScaled(0.2,0.2,0.2);
glutSolidCube(1.0);
glPopMatrix();

//pole3
glPushMatrix();
glTranslated(5.45,0.2,14);
glRotated(-90,1,0,0);
glScaled(0.15,0.15,9.2);
glutSolidCube(1.0);
glPopMatrix();

//square for pole2
glPushMatrix();
glTranslated(5.45,4.6,14);
glRotated(-90,1,0,0);
glScaled(0.2,0.2,0.2);
glutSolidCube(1.0);
glPopMatrix();

//square for pole2
glPushMatrix();
glTranslated(5.45,0.2,14);
glRotated(-90,1,0,0);
glScaled(0.2,0.2,0.2);
glutSolidCube(1.0);
glPopMatrix();
//pole4
glPushMatrix();
glTranslated(5.7,0.2,14);
glRotated(-90,1,0,0);
glScaled(0.15,0.15,9.2);
glutSolidCube(1.0);
glPopMatrix();

//square for pole2
glPushMatrix();
glTranslated(5.7,4.6,14);
glRotated(-90,1,0,0);
glScaled(0.2,0.2,0.2);
glutSolidCube(1.0);
glPopMatrix();

//square for pole2
glPushMatrix();
glTranslated(5.7,0.2,14);
glRotated(-90,1,0,0);
glScaled(0.2,0.2,0.2);
glutSolidCube(1.0);
glPopMatrix();

//slege left glass 6
glPushMatrix();
glTranslated(3.2,5,13.5);
glRotated(-90,1,0,0);
glScaled(5.4,1,0.5);
glutSolidCube(1.0);
glPopMatrix();

//slege left glass 6
glPushMatrix();
glTranslated(3.2,5.5,13.7);
glRotated(-90,1,0,0);
glScaled(5.4,1,0.5);
glutSolidCube(1.0);
glPopMatrix();

//slege left glass 6
glPushMatrix();
glTranslated(3.2,6,13.9);
glRotated(-90,1,0,0);
glScaled(5.4,1,0.5);
glutSolidCube(1.0);
glPopMatrix();


//slege left glass 6
glPushMatrix();
glTranslated(3.2,0.2,13.4);
glRotated(-90,1,0,0);
glScaled(5.4,1,0.5);
glutSolidCube(1.0);
glPopMatrix();

//slege left glass 6
glPushMatrix();
glTranslated(3.2,0.4,13.2);
glRotated(-90,1,0,0);
glScaled(5.4,1,0.5);
glutSolidCube(1.0);
glPopMatrix();

//slege left glass 6
glPushMatrix();
glTranslated(3.2,0.6,13.0);
glRotated(-90,1,0,0);
glScaled(5.4,1,0.5);
glutSolidCube(1.0);
glPopMatrix();

//right sleges
glPushMatrix();
glTranslated(11,6,5);
glScaled(0.45,5,0.9);
glRotated(45,0,0,0);
wall(0.08);
glPopMatrix();

//right sleges
glPushMatrix();
glTranslated(11,5.6,5);
glScaled(0.4,5,0.9);
glRotated(45,0,0,0);
wall(0.08);
glPopMatrix();

//right sleges
glPushMatrix();
glTranslated(11,5.2,5);
glScaled(0.35,5,0.9);
glRotated(45,0,0,0);
wall(0.08);
glPopMatrix();

//right down sleges
glPushMatrix();
glTranslated(11,0,5);
glScaled(0.3,5,0.9);
glRotated(45,0,0,0);
wall(0.08);
glPopMatrix();

//right sleges
glPushMatrix();
glTranslated(10.8,0.4,5);
glScaled(0.3,5,0.9);
glRotated(45,0,0,0);
wall(0.08);
glPopMatrix();

//right sleges
glPushMatrix();
glTranslated(10.6,0.8,5);
glScaled(0.3,5,0.9);
glRotated(45,0,0,0);
wall(0.08);
glPopMatrix();

//right pole1
glPushMatrix();
glTranslated(12,0.2,5.1);
glScaled(0.04,65,0.04);
glRotated(45,0,0,0);
wall(0.08);
glPopMatrix();

glPushMatrix();
glTranslated(12,5,5.075);
glScaled(0.05,4,0.05);
glRotated(45,0,0,0);
wall(0.08);
glPopMatrix();

//right pole2
glPushMatrix();
glTranslated(12,0.2,5.35);
glScaled(0.04,65,0.04);
glRotated(45,0,0,0);
wall(0.08);
glPopMatrix();

glPushMatrix();
glTranslated(12,5,5.325);
glScaled(0.05,4,0.05);
glRotated(45,0,0,0);
wall(0.08);
glPopMatrix();

//right pole3
glPushMatrix();
glTranslated(12,0.2,8.35);
glScaled(0.04,65,0.04);
glRotated(45,0,0,0);
wall(0.08);
glPopMatrix();

glPushMatrix();
glTranslated(12,5,8.325);
glScaled(0.05,4,0.05);
glRotated(45,0,0,0);
wall(0.08);
glPopMatrix();

//right pole4
glPushMatrix();
glTranslated(12,0.2,8.135);
glScaled(0.04,65,0.04);
glRotated(45,0,0,0);
wall(0.08);
glPopMatrix();

glPushMatrix();
glTranslated(12,5,8.1);
glScaled(0.05,4,0.05);
glRotated(45,0,0,0);
wall(0.08);
glPopMatrix();



//label
GLfloat mat_ambient21[]={0.2,0.2,0.2,0};
GLfloat mat_specular21[]={0.5,0.5,0.5,1};
GLfloat mat_diffuse21[]={0.01,0.01,0.01,0};
GLfloat mat_shininess21[]={0.25};
matprop(mat_ambient21,mat_diffuse21,mat_specular21,mat_shininess21);

//front left wall of college
glPushMatrix();
glTranslated(1.5,9,13.1);
glRotated(-90,1,0,0);
glScaled(0.1,0.05,2);
glutSolidCube(1.0);
glPopMatrix();

glPushMatrix();
glTranslated(1.7,9.9,13.1);
glRotated(-90,1,0,0);
glScaled(0.45,0.05,0.15);
glutSolidCube(1.0);
glPopMatrix();

glPushMatrix();
glTranslated(1.7,8.05,13.1);
glRotated(-90,1,0,0);
glScaled(0.4,0.05,0.18);
glutSolidCube(1.0);
glPopMatrix();

glPushMatrix();
glTranslated(1.85,8.6,13.1);
glRotated(-90,1,0,0);
glScaled(0.1,0.05,1);
glutSolidCube(1.0);
glPopMatrix();

glPushMatrix();
glTranslated(1.9,9,13.1);
glRotated(-90,1,0,0);
glScaled(0.2,0.05,0.15);
glutSolidCube(1.0);
glPopMatrix();

glPushMatrix();
glTranslated(2,8.4,13.1);
glRotated(-90,1,0,0);
glScaled(0.1,0.05,1.2);
glutSolidCube(1.0);
glPopMatrix();

//E
glPushMatrix();
glTranslated(2.6,8.9,13.1);
glRotated(-90,1,0,0);
glScaled(0.1,0.05,2);
glutSolidCube(1.0);
glPopMatrix();

glPushMatrix();
glTranslated(2.7,9.8,13.1);
glRotated(-90,1,0,0);
glScaled(0.3,0.05,0.15);
glutSolidCube(1.0);
glPopMatrix();

glPushMatrix();
glTranslated(2.7,9,13.1);
glRotated(-90,1,0,0);
glScaled(0.3,0.05,0.15);
glutSolidCube(1.0);
glPopMatrix();

glPushMatrix();
glTranslated(2.7,8,13.1);
glRotated(-90,1,0,0);
glScaled(0.3,0.05,0.15);
glutSolidCube(1.0);
glPopMatrix();

//C
glPushMatrix();
glTranslated(3.4,8.9,13.1);
glRotated(-90,1,0,0);
glScaled(0.1,0.05,2);
glutSolidCube(1.0);
glPopMatrix();

glPushMatrix();
glTranslated(3.5,9.8,13.1);
glRotated(-90,1,0,0);
glScaled(0.3,0.05,0.15);
glutSolidCube(1.0);
glPopMatrix();


glPushMatrix();
glTranslated(3.5,8,13.1);
glRotated(-90,1,0,0);
glScaled(0.3,0.05,0.15);
glutSolidCube(1.0);
glPopMatrix();

//H
glPushMatrix();
glTranslated(4.2,8.9,13.1);
glRotated(-90,1,0,0);
glScaled(0.1,0.05,2);
glutSolidCube(1.0);
glPopMatrix();

glPushMatrix();
glTranslated(4.3,9,13.1);
glRotated(-90,1,0,0);
glScaled(0.3,0.05,0.15);
glutSolidCube(1.0);
glPopMatrix();

glPushMatrix();
glTranslated(4.5,8.9,13.1);
glRotated(-90,1,0,0);
glScaled(0.1,0.05,2);
glutSolidCube(1.0);
glPopMatrix();

}


void display(void)
{
time(&ltime); // Get time
newtime = localtime(&ltime); // Convert to local time
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
gluLookAt(view[0],view[1],view[2],look[0],look[1],look[2],0.0,1.0,0.0);earth();
college();
myclock();
glFlush();
glutSwapBuffers();
glutPostRedisplay();
}

void Keyboard(unsigned char key,int x,int y)
{
switch(key)
{
//to move the camera along -ve x axis
case '4':
view[0]-=.1;
glutPostRedisplay();
break;
//to move the camera along +ve x axis
case '6':
view[0]+=.1;
glutPostRedisplay();
break;
//to move the camera along +ve y axis
case '7':
view[1]+=.1;
glutPostRedisplay();
break;
//to move the camera along -ve y axis
case '1':
if(view[1]>1.9)
view[1]-=.1;
glutPostRedisplay();
break;
//to move the camera along -ve z axis
case '8':view[2]-=.1;
glutPostRedisplay();
break;
//to move the camera along +ve z axis
case '2':
view[2]+=.1;
glutPostRedisplay();
break;

//inside view
case 'i':
case 'I':
view[0]=3;
view[1]=3;
view[2]=13;
look[0]=2.8;
look[1]=2;
look[2]=1;
break;

//top view
case 'T':
case 't':
view[0]=9;
view[1]=19;
view[2]=19;
look[0]=2;
look[1]=4;
look[2]=4;
break;

//front view
case 'j':
case 'J':
view[0]=3;
view[1]=3;
view[2]=19;
look[0]=3;
look[1]=2;
look[2]=3;
break;

//back view
case 'k':
case 'K':
view[0]=0;
view[1]=5.5;
view[2]=-7;
look[0]=2;
look[1]=4;
look[2]=2;
break;

//right view
case 's':
case 'S':
view[0]=17;
view[1]=5;
view[2]=10;
look[0]=2;
look[1]=4;
look[2]=2;
break;

}
}

void main(int argc,char**argv)
{
glutInit(&argc,argv);//to initialize the glut library
glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
glutInitWindowSize(w,h);
glutInitWindowPosition(0,0);
glutCreateWindow("GECH 3D MODEL");
myinit();
glutDisplayFunc(display);
glutKeyboardFunc(Keyboard);
glutFullScreen();//to see o/p in full screen on monitor
glEnable(GL_LIGHTING);
glEnable(GL_LIGHT0);
glShadeModel(GL_SMOOTH);//smooth shaded
glEnable(GL_DEPTH_TEST);//to remove hidden surface
glEnable(GL_NORMALIZE);//to make normal vector to unit vector
glClearColor(0,.3,.8,0);
glViewport(0,0,w,h);
glutMainLoop();
}
