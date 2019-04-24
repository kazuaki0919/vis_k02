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

float dist = -20.0;  //視点の移動量
float theta = 0.0;  //ロケット回転
float speed = 0.0;  //打ち上げスピード

void display(void)
{
    int i;
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    glPushMatrix();  //8:全体
    gluLookAt(0.0, 1.0, dist, 0.0, 1.0, dist + 1.0, 0.0, 1.0, 0.0);
    
    glPushMatrix();  //6:ロケット
    glTranslatef(0.0, speed, 0.0);
    glRotatef(theta, 0.0, 10.0, 0.0);
    
    //三角錐テッペン
    glPushMatrix();  //1;三角錐テッペン
    glTranslatef(0.0, 2.0, 0.0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    glutWireCone(1.0, 2.0, 12.0, 3.0);
    glPopMatrix();  //1:三角錐テッペン
    
    //円柱上
    glPushMatrix();  //2:円柱上
    glTranslatef(0.0, 1.0, 0.0);
    myWireCylinder(1.0, 2.0, 12.0);
    glPopMatrix();  //2:円柱上
    
    //円柱下
    glPushMatrix();  //3:円柱下
    glTranslatef(0.0, -1.0, 0.0);
    myWireCylinder(1.0, 2.0, 12.0);
    glPopMatrix();  //3:円柱下
    
    //三角錐噴射口
    glPushMatrix();  //4:三角錐噴射口
    glTranslatef(0.0, -2.5, 0.0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    glutWireCone(0.5, 1.0, 12.0, 3.0);
    glPopMatrix();  //4:三角州噴射口
    
    //羽根生成
    for (i = 0; i < 4; i++) {
        glRotatef(90.0, 0.0, 1.0, 0.0);
        glPushMatrix();  //5:羽根
        glTranslatef(1.5, -1.0, 0.0);
        glScalef(1.0, 2.0, 0.2);
        glutWireCube(1.0);
        glPopMatrix();  //5:羽根
    }
    
    glPopMatrix();  //6:ロケット
    glFlush();
    
    glPushMatrix();  //7:地面
    
    //地面
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    for(i = -35; i < 36; i += 2){
        glVertex3f((float)i, 0.0, -35.0);
        glVertex3f((float)i, 0.0, 35.0);
        glVertex3f(-50.0, 0.0, (float)i);
        glVertex3f(50.0, 0.0, (float)i);
    }
    glEnd();
    glPopMatrix(); //7:地面
    
    glPopMatrix(); //8:全体
    glFlush();
}

void idle(void)
{
    printf("theta = %f\n", theta);
    theta = fmod(theta + 0.1, 360.0);
    speed += 0.05;  //自分のMacBook Proの場合は、0.05, 学内PCの場合は、0.001で動かす
    glutPostRedisplay();  //ディスプレイコールバックバック関数(display)を実行
}

void myKbd(unsigned char key, int x, int y)
{
    if(key==KEY_ESC) exit(0);
}
void myInit(char *progname)
{
    int width = 500,height = 500;
    float aspect = (float)width / (float)height;
    
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(width, height);
    glutInitDisplayMode(GLUT_RGBA);
    glutCreateWindow(progname);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glutKeyboardFunc(myKbd);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, aspect, 0.1, 40.0);
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
