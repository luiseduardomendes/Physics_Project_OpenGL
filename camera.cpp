#include "camera.hpp"

Camera::Camera(){
    this->initial_state();
}

void Camera::initial_state(){
    this->rho = 25;
    this->phi = 3.14/3;
    this->tht = 3.14/4;

    this->drho = 0;
    this->dphi = 0;
    this->dtht = 0;
}

void Camera::stop_mov(){
    this->drho = 0;
    this->dphi = 0;
    this->dtht = 0;
}

void Camera::inc_rho(){
    this->drho += 0.01;
}
void Camera::dec_rho(){
    this->drho -= 0.01;
}

void Camera::inc_phi(){
    this->dphi += 0.01;
}
void Camera::dec_phi(){
    this->dphi -= 0.01;
}

void Camera::inc_tht(){
    this->dtht += 0.01;
}
void Camera::dec_tht(){
    this->dtht -= 0.01;
}
GLfloat Camera::get_x(){
    return rho*sin(phi)*cos(tht);
}
GLfloat Camera::get_y(){
    return rho*sin(phi)*sin(tht);
}
GLfloat Camera::get_z(){
    return rho*cos(phi);
}


void Camera::update(){
    this->tht += this->dtht;
    this->rho += this->drho;
    this->phi += this->dphi;
}
