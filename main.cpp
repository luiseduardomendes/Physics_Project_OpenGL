#include <GL/glut.h>
#include <cmath>
#include <ctime>
#include <cstdio>
#define n_particles 100

GLfloat rho = 25;
GLfloat phi = 3.14/3;
GLfloat tht = 3.14/4;

GLfloat drho = 0;
GLfloat dphi = 0;
GLfloat dtht = 0;

class Pos{
public:
  GLfloat x, y, z;
  Pos(GLfloat x, GLfloat y, GLfloat z){
    this->x = x;
    this->y = y;
    this->z = z;
  }
  Pos(){
    this->x = 0;
    this->y = 0;
    this->z = 0;
  }
};

Pos particles[n_particles];

void special(int key, int, int) {
  switch (key) {
    case GLUT_KEY_LEFT:
      dtht = 0.01;
      break;
    case GLUT_KEY_RIGHT:
      dtht = -0.01;
      break;
    case GLUT_KEY_UP:
      dphi = -0.01;
      break;
    case GLUT_KEY_DOWN:
      dphi = 0.01;
      break;
    case GLUT_KEY_PAGE_DOWN:
      drho = -0.01;
      break;
    case GLUT_KEY_PAGE_UP:
      drho = 0.01;
      break;
    case GLUT_KEY_END:
      drho = 0;
      dphi = 0;
      dtht = 0;
      break;
    case GLUT_KEY_HOME:
      rho = 25;
      phi = 3.14/3;
      tht = 3.14/4;
      drho = 0;
      dphi = 0;
      dtht = 0;
      break;
    default: return;
  }
  glutPostRedisplay();
}

void mySphere(GLfloat radius, int slices, int stacks) {
  glPushMatrix();
  glRotatef(-90.0, 1.0, 0.0, 0.0);
  glutSolidSphere(radius, slices, stacks);
  glPopMatrix();
}
void myWireSphere(GLfloat radius, int slices, int stacks) {
  glPushMatrix();
  glRotatef(-90.0, 1.0, 0.0, 0.0);
  glutWireSphere(radius, slices, stacks);
  glPopMatrix();
}


void drawParticle(GLfloat px, GLfloat py, GLfloat pz){
  glTranslatef (px, py, pz);
  glColor3f(0.0, 0.0, 1.0);
  mySphere(0.5, 15., 15.);
  glTranslatef (-px, -py, -pz);
}

void drawBoundarie(GLfloat rad){
  myWireSphere(rad, 10,10);
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPushMatrix();

  drawBoundarie(10.);
  for (int i = 0; i < n_particles; i ++)
    drawParticle(particles[i].x, particles[i].y, particles[i].z);

  glBegin(GL_LINES);
    glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(25, 0, 0);
    glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 25, 0);
    glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 25);
  glEnd();

  glPopMatrix();
  glFlush();
  glutSwapBuffers();
}

// Viewing routines.  Basically the camera is sitting on a comet orbiting
// the sun with a "year" 8 times that of the planet.  To animate we have
// the function nextAnimationFrame() registered as the idle function.  It
// increments the value of u (to "move" the camera), ticks off another
// portion of a day and portion of a year, then reorients the camera and
// refreshes the display.



GLfloat t = 0, dt = 1./60.;
static GLfloat fps = 60;


void timer(int v) {
  glLoadIdentity();
  t += dt;

  rho += drho;
  phi += dphi;
  tht += dtht;

  gluLookAt(rho*sin(phi)*cos(tht),rho*cos(phi),rho*sin(phi)*sin(tht), 0,0,0, 0,1,0);
  glutPostRedisplay();
  glutTimerFunc(1000/fps, timer, v);
}

void reshape(GLint w, GLint h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, (GLfloat)w/(GLfloat)h, 1.0, 40.0);
  glMatrixMode(GL_MODELVIEW);
}

void initParticles(){
  for (int i = 0; i < n_particles; i ++){
    GLfloat prho = 20.*((double)rand()/(double)RAND_MAX)-10.;
    GLfloat pphi = 3.14/2.*((double)rand()/(double)RAND_MAX);
    GLfloat ptht = 2.*3.14*((double)rand()/(double)RAND_MAX);

    GLfloat px = prho*sin(pphi)*cos(ptht);
    GLfloat py = prho*sin(pphi)*sin(ptht);
    GLfloat pz = prho*cos(pphi);

    particles[i].x = px;
    particles[i].y = py;
    particles[i].z = pz;
  }
}

void init() {
  glEnable(GL_LIGHTING);                // so the renderer considers light
  glEnable(GL_LIGHT0);                  // turn LIGHT0 on
}
// The usual main() for a GLUT application.
int main(int argc, char** argv) {
  srand(time(NULL));
  initParticles();
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(1360, 768);
  glutCreateWindow("Particle Simulation");
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutTimerFunc(100, timer, 0);
  glEnable(GL_DEPTH_TEST);
  glutSpecialFunc(special);
  init();
  glutMainLoop();
}
