#include "main.hpp"

Pos particles[n_particles];
Pos part_spd[n_particles];

Camera camera;

void update_particles();

void special(int key, int, int) {
    switch (key) {
        case GLUT_KEY_LEFT:
            camera.inc_tht();
            break;
        case GLUT_KEY_RIGHT:
            camera.dec_tht();
            break;
        case GLUT_KEY_UP:
            camera.dec_phi();
            break;
        case GLUT_KEY_DOWN:
            camera.inc_phi();
            break;
        case GLUT_KEY_PAGE_DOWN:
            camera.dec_rho();
            break;
        case GLUT_KEY_PAGE_UP:
            camera.inc_rho();
            break;
        case GLUT_KEY_END:
            camera.stop_mov();
            break;
        case GLUT_KEY_HOME:
            camera.initial_state();
            break;
        default: return;
    }
    glutPostRedisplay();
}


void drawParticle(GLfloat px, GLfloat py, GLfloat pz){
    glTranslatef (px, py, pz);
    glColor3f(0.0, 0.0, 1.0);
    Sphere(0.5, 15., 15.);
    glTranslatef (-px, -py, -pz);
}

void drawBoundarie(GLfloat rad){
    WSphere(rad, 15,15);
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

GLfloat t = 0, dt = 1./60.;
static GLfloat fps = 60;


void timer(int v) {
    glLoadIdentity();
    t += dt;

    update_particles();
    camera.update();


    gluLookAt(camera.get_x(),camera.get_z(),camera.get_y(), 0,0,0, 0,1,0);
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

void update_particles(){
    for (int i = 0; i < n_particles; i ++){
        GLfloat d2x = (2.*ACC_MAX * ((double)rand()/(double)RAND_MAX)) - 1.*ACC_MAX;
        GLfloat d2y = (2.*ACC_MAX * ((double)rand()/(double)RAND_MAX)) - 1.*ACC_MAX;
        GLfloat d2z = (2.*ACC_MAX * ((double)rand()/(double)RAND_MAX)) - 1.*ACC_MAX;

        part_spd[i].x += d2x*dt;
        part_spd[i].y += d2y*dt;
        part_spd[i].z += d2z*dt;

        particles[i].x += part_spd[i].x*dt;
        particles[i].y += part_spd[i].y*dt;
        particles[i].z += part_spd[i].z*dt;

        GLfloat dist = sqrt(pow(particles[i].x, 2) + pow(particles[i].y, 2) + pow(particles[i].z, 2));

        if (dist > 10.){
            particles[i].x = -particles[i].x;
            particles[i].y = -particles[i].y;
            particles[i].z = -particles[i].z;
        }
    }
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
