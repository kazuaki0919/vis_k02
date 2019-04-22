//
//  main.c
//  k02
//
//  Created by 並木一晃 on 2019/04/18.
//  Copyright © 2019 並木一晃. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <GLUT/GLUT.h>
#include "myShape.h"
#define KEY_ESC 27

float dist=0.0;  //視点の移動量
float theta =0.0;

void display(void)
{
    int i;
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    glPushMatrix();
    gluLookAt(0.0,1.0,dist,0.0,1.0,dist+1.0,0.0,1.0,0.0);
//    glTranslatef(0.0,0.0,-20.0);
//    glRotatef(theta,0.0,10.0,0.0);
    
    //三角錐テッペン
    glPushMatrix();
    glTranslatef(0.0,2.0,10.0);
    glRotatef(-90.0,1.0,0.0,0.0);
    glutWireCone(0.5,1.0,12,3);
    glPopMatrix();
    
    //円柱上
    glPushMatrix();
    glColor3f(1.0,0.0,0.0);
    glTranslatef(0.0,1.5,10.0);
    myWireCylinder(0.5,1.0,12);
    glPopMatrix();
    
    //円柱下
    glPushMatrix();
    glColor3f(0.0,1.0,0.0);
    glTranslatef(0.0,0.5,10.0);
    myWireCylinder(0.5,1.0,12);
    glPopMatrix();
    
    //三角錐噴射口
    glPushMatrix();
    glColor3f(0.0,0.0,1.0);
    glTranslatef(0.0,-0.25,10.0);
    glRotatef(-90.0,1.0,0.0,0.0);
    glutWireCone(0.25,0.5,12,3);
    glPopMatrix();
    
    //羽根生成
    for (i = 0; i < 4; i++) {
//        glRotatef(90.,0.,1.,0.);
//        glColor3f(1.0,1.0,0.0);
//        glPushMatrix();
//        glTranslatef(1.5,-1.0,10.0);
//        glScalef(1.0, 2.0, 0.2);
//        glutWireCube(1.0);
//        glPopMatrix();
        
        glRotatef(90.,0.,1.,0.);
        glColor3f(1.0,1.0,0.0);
        glPushMatrix();
        glTranslatef(0.0,1.0,0.0);
        glScalef(0.2, 0.2, 0.2);
        glutWireCube(1.0);
        glPopMatrix();
    }
    
    //地面
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_LINES);
    for( i= -35;i<36;i+=2){
        glVertex3f((float)i,0,-35.0);
        glVertex3f((float)i,0,35.0);
        glVertex3f(-50.0,0,(float)i);
        glVertex3f(50.0,0,(float)i);
    }
    glEnd();
    
    glPopMatrix();
    glFlush();
}

void idle(void)
{
    printf("theta = %f\n", theta);
    theta=fmod(theta+0.1,360.0);
    glutPostRedisplay();  //ディスプレイコールバックバック関数(display)を実行
}

void myKbd(unsigned char key, int x, int y)
{
    if(key==KEY_ESC) exit(0);
}
void myInit(char *progname)
{
    int width=500,height=500;
    float aspect=(float)width/(float)height;
    
    glutInitWindowPosition(0,0);
    glutInitWindowSize(width,height);
    glutInitDisplayMode(GLUT_RGBA);
    glutCreateWindow(progname);
    glClearColor(0.0,0.0,0.0,1.0);
    glutKeyboardFunc(myKbd);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0,aspect,0.1,40.0);
    glMatrixMode(GL_MODELVIEW);
}
int main(int argc, char *argv[])
{
    glutInit(&argc,argv);
    myInit(argv[0]);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMainLoop();
    return(0);
}
