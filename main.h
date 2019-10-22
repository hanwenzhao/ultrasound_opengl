//
// Created by hanwen on 10/15/19.
//

#ifndef ULTRASOUND_OPENGL_MAIN_H
#define ULTRASOUND_OPENGL_MAIN_H

#include <iostream>
#include <cstdio>
#include <cstring>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <vector>
#include <cstdarg>
#include <fstream>
#include "omp.h"
#include <algorithm>
#include <cmath>
#include <cmath>
#include <numeric>
#include <random>
#include <queue>
#include <ctime>
#include <chrono>
#include <string.h>
#include <cinttypes>
#include <cstdint>
#include <boost/crc.hpp>
#include <boost/cstdint.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/classification.hpp>

struct scan_data_struct{
    unsigned long time_stamp;
    unsigned short encoder;
    double buffer[2500];
};

struct screen_data_struct{
    double X;
    double Y;
    double Z;
    double I;
};

/* Data Processing */
const unsigned char marker[10] = {0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01};
int i, j, k, marker_index, marker_index_next, buffer_length, signal_draw_index;
int16_t adc_max = 0;
int16_t adc_min = 0;
bool marker_flag;
std::vector<int> marker_locations;
std::vector<scan_data_struct> scan_data;
std::vector<screen_data_struct> screen_data;
unsigned char time_stamp_char[4];
unsigned long time_stamp;
unsigned char probe_type_char;
unsigned char encoder_char[2];
unsigned short encoder;
unsigned char adc_char[2*2500];
unsigned char adc_temp[2];
unsigned char crc_char[4];
uint32_t crc_result;
unsigned char crc_result_char[4];
unsigned char crc_input[4+1+2+2*2500];
int16_t adc;
short buffer[2500];

int compare_crc(unsigned char a[], unsigned char b[], size_t len);
int16_t changed_endian_2Bytes(int16_t value);
unsigned long changed_endian_4Bytes(unsigned long num);
std::vector<int> find_marker(std::vector<unsigned char> _file_bytes);
void file_to_data(std::vector<unsigned char> _file_bytes, std::vector<int> _marker_locations, std::vector<scan_data_struct> & _scan_data);
void data_to_pixel(std::vector<scan_data_struct> _scan_data, std::vector<screen_data_struct> & _screen_data);
uint32_t crc32c(uint32_t crc, const unsigned char *buf, size_t len);

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
void idle();
static void Print(const char* format , ...);
static void reshape(int width, int height);
void special(int key,int x,int y);
void Project(double fov,double asp,double dim);

#endif //ULTRASOUND_OPENGL_MAIN_H
