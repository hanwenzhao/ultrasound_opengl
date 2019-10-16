//
// Created by hanwen on 10/15/19.
//

#ifndef ULTRASOUND_OPENGL_MAIN_H
#define ULTRASOUND_OPENGL_MAIN_H

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <vector>
#include <stdarg.h>
#include <fstream>
#include "omp.h"
#include <algorithm>
#include <math.h>
#include <cmath>
#include <numeric>
#include <random>
#include <queue>
#include <ctime>
#include <chrono>
#include <string>
#include <cinttypes>
#include <stdint.h>
#include <boost/algorithm/string/split.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/classification.hpp>

struct scan_data_struct{
    unsigned long time_stamp;
    unsigned short encoder;
    short buffer[2490];
};

struct screen_data_struct{
    double X;
    double Y;
    double Z;
    double I;
};

/* Data Processing */
const unsigned char marker[10] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
int i, j, k, marker_index, buffer_length;
int adc_max = 0;
int adc_min = 0;
bool marker_flag;
bool skip_flag = false;
std::vector<int> marker_locations;
std::vector<scan_data_struct> scan_data;
std::vector<screen_data_struct> screen_data;
unsigned char time_stamp_char[4];
unsigned long time_stamp;
unsigned char encoder_char[2];
unsigned short encoder;
unsigned char adc_temp[2];
int16_t adc;
short buffer[2490];
unsigned char crc_char[4];

int16_t changed_endian_2Bytes(int16_t value);
unsigned long changed_endian_4Bytes(unsigned long num);
std::vector<int> find_marker(std::vector<unsigned char> _file_bytes);
void file_to_data(std::vector<unsigned char> _file_bytes, std::vector<int> _marker_locations, std::vector<scan_data_struct> & _scan_data);
void data_to_pixel(std::vector<scan_data_struct> _scan_data, std::vector<screen_data_struct> & _screen_data);
void normalize_adc(std::vector<screen_data_struct> & _screen_data);

std::vector<int> random_scans;

PFNGLWINDOWPOS2IPROC glWindowPos2i;

#define LEN 8192  //  Maximum length of text string

#define Cos(th) cos(M_PI/180*(th))
#define Sin(th) sin(M_PI/180*(th))

// OPENGL Variables
// Global Parameters
int th=0;       // Azimuth of view angle
int ph=0;       // Elevation of view angle
double z=0;     // Z variable
double dim=2;   // Dimension of orthogonal box
int mode=3;
const char* text[] = {"","2D","3D constant Z","3D","4D"};  // Dimension display text


static GLint Frames = 0;
static GLfloat fps = -1;
static GLint T0 = 0;

GLfloat worldRotation[16] = {1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1};

void display();


#endif //ULTRASOUND_OPENGL_MAIN_H
