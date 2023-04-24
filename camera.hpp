#pragma once
#include <GL/glut.h>
#include <math.h>

class Camera{
    private:



    public:
        GLfloat rho, phi, tht;
        GLfloat drho, dphi, dtht;

        Camera();

        GLfloat get_x();
        GLfloat get_y();
        GLfloat get_z();

        void inc_rho();
        void dec_rho();

        void inc_phi();
        void dec_phi();

        void inc_tht();
        void dec_tht();

        void stop_mov();
        void initial_state();



        void update();
};
