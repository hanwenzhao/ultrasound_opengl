#include "main.h"

int main(int argc,char* argv[]) {
    //std::clock_t begin = clock();
    /* #################### DATA PROCESSING #################### */
    /* read binary file */
    std::ifstream inFile("/home/hanwen/ultrasound_opengl/short2.txt", std::ios::in | std::ios::binary);
    /* convert file to bytes vector */
    /* DO NOT USE ISTREAM_ITERATOR*/
    std::vector<unsigned char> file_bytes(
            (std::istreambuf_iterator<char>(inFile)),
            (std::istreambuf_iterator<char>()));
    /* find all marker locations */
    marker_locations = find_marker(file_bytes);
    /* convert file bytes to data struct */
    file_to_data(file_bytes, marker_locations, scan_data);
    /* convert data to vertex on screen */
    data_to_pixel(scan_data, screen_data);

    srand((unsigned)time(0));
    glutInit(&argc, argv);
    glWindowPos2i =  (PFNGLWINDOWPOS2IPROC) glutGetProcAddress("glWindowPos2i");
    glutInitWindowSize(1300, 1000);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutCreateWindow("ultrasound");
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    gluOrtho2D((GLdouble) -1250, (GLdouble) 1250, (GLdouble) -2500, (GLdouble) 100);
    glutMainLoop();
    return 0;
}

void idle() {
    random_scans.clear();
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dis(0, screen_data.size()-1);
    for (i = 0; i < 500000; i++){
        //printf("%d\n",screen_data.size());
        random_scans.push_back(dis(gen));
    }
    glutPostRedisplay();   // Post a re-paint request to activate display()
}

void display(){
    Frames++;
    GLint t = glutGet(GLUT_ELAPSED_TIME);
    if (t - T0 >= 5000) {
        GLfloat seconds = (t - T0) / 1000.0;
        fps = Frames / seconds;
        printf("%d frames in %6.3f seconds = %6.3f FPS\n", Frames, seconds, fps);
        T0 = t;
        Frames = 0;
    }
    glColor3f(1,1,1);
    glWindowPos2i(5,5);
    if (fps>0) Print("FPS %.3f", fps);

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
    glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer (background)
    glPointSize(1);
    glBegin(GL_POINTS);
    /* random draw */
    for (i = 0; i < (int)random_scans.size(); i++){
        double intensity = screen_data.at(random_scans.at(i)).I * 1.2;
        glColor3f(intensity, intensity, intensity);
        glVertex2d(screen_data.at(random_scans.at(i)).X,screen_data.at(random_scans.at(i)).Y);
    }

    /* draw all */
    /*
    for (i = 0; i < (int)screen_data.size(); i++){
        double intensity = screen_data.at(i).I;

        glColor3f(intensity, intensity, intensity);
        glVertex2d(screen_data.at(i).X,screen_data.at(i).Y);
    }
     */
    glEnd();
    glFlush();
    glutSwapBuffers();
}


void data_to_pixel(std::vector<scan_data_struct> _scan_data, std::vector<screen_data_struct> & _screen_data){
    //printf("%d\n", (int)_scan_data.size());
    for (i = 0; i < (int)_scan_data.size(); i++){
        double angle = _scan_data.at(i).encoder * 360.0 / 4096.0;
        if (angle <= 115){
            angle = 295 + (360+angle-295)/6.0;
        }
        else if (angle >= 295){
            angle = 295 + (angle-295)/6.0;
        }
        else{
            angle = 295 - (295-angle)/6.0;
        }
        angle = angle - 25;
        for (j = 0; j < 2490; j++){
            screen_data_struct temp_data = {(j+1) * Cos(angle), (j+1) * Sin(angle), 0, (double)_scan_data.at(i).buffer[j]};
            _screen_data.push_back(temp_data);
        }
    }
}

void file_to_data(std::vector<unsigned char> _file_bytes, std::vector<int> _marker_locations, std::vector<scan_data_struct> & _scan_data){
    for (i = 0; i < (int)_marker_locations.size()-1; i++){
        marker_index = _marker_locations.at(i);
        marker_index_next = _marker_locations.at(i+1);
        /* time stamp */
        for (j = 0; j < (int)sizeof(time_stamp_char); j++){
            time_stamp_char[j] = _file_bytes.at(marker_index + sizeof(marker) + j);
        }
        std::memcpy(&time_stamp, time_stamp_char, sizeof(time_stamp));
        time_stamp = changed_endian_4Bytes(time_stamp);
        /* encoder */
        for (j = 0; j < (int) sizeof(encoder_char); j++){
            encoder_char[j] = _file_bytes.at(marker_index + sizeof(marker) + sizeof(time_stamp_char) + j);
        }
        std::memcpy(&encoder, encoder_char, sizeof(encoder));
        encoder = changed_endian_2Bytes(encoder);
        /* adc */
        /* determine the length of buffer */
        buffer_length = (int)(_marker_locations.at(i+1) - _marker_locations.at(i) - sizeof(marker) - sizeof(time_stamp_char) - sizeof(encoder_char) - sizeof(crc_char))/2;
        for (j = 0; j < buffer_length; j++){
            for (k = 0; k < (int)sizeof(adc_temp); k++){
                adc_temp[k] = _file_bytes.at(marker_index + sizeof(marker) + sizeof(time_stamp_char) + sizeof(encoder_char) + j * 2 + k);
                adc_char[2*j+k] = adc_temp[k];
            }
            std::memcpy(&adc, adc_temp, sizeof(adc));
            adc = changed_endian_2Bytes(adc);
            buffer[j] = adc;
        }
        /* checksum */
        for (j = 0; j < (int)sizeof(crc_char); j++){
            crc_char[j] = _file_bytes.at(marker_index_next-(int)sizeof(crc_char)+j);
        }
        /* calculate crc locally */
        mempcpy(crc_input, marker, sizeof(marker));
        memcpy(crc_input+sizeof(marker), time_stamp_char, sizeof(time_stamp_char));
        memcpy(crc_input+sizeof(marker)+sizeof(time_stamp_char), encoder_char, sizeof(encoder_char));
        memcpy(crc_input+sizeof(marker)+sizeof(time_stamp_char)+sizeof(encoder_char), adc_char, sizeof(adc_char));
        crc_result = crc32c(0, crc_input, sizeof(crc_input));
        crc_result = changed_endian_4Bytes(crc_result);
        memcpy(crc_result_char, (unsigned char *)&crc_result, sizeof (crc_result));
        /* if two crc matches */
        if (compare_crc(crc_char, crc_result_char, sizeof(crc_char))){
            scan_data_struct temp_struct;
            temp_struct.time_stamp = time_stamp;
            temp_struct.encoder = encoder;
            /* find min and max */
            for (j = 0; j < buffer_length; j++){
                adc_max = std::max(adc_max, buffer[j]);
                adc_min = std::min(adc_min, buffer[j]);
            }
            /* normalize on the go */
            for (j = 0; j < buffer_length; j++){
                temp_struct.buffer[j] = ((double)buffer[j] - adc_min)/(adc_max-adc_min);
                //printf("Intensity:%f\n", temp_struct.buffer[j]);
            }
            adc_max = 0; adc_min = 0;
            _scan_data.push_back(temp_struct);
        }
    }
}

int compare_crc(unsigned char a[], unsigned char b[], size_t len){
    int ii;
    for (ii = 0; ii < (int)len; ii++){
        if (a[ii] != b[ii]){
            return 0;
        }
    }
    return 1;
}


std::vector<int> find_marker(std::vector<unsigned char> _file_bytes){
    std::vector<int> _marker_locations;
    for (i = 0; i < (int)_file_bytes.size(); i++){
        if (_file_bytes.at(i) == marker[0]){
            for (j = 0; j < (int)sizeof(marker); j++) {
                if ((i + j) < _file_bytes.size()){
                    if (_file_bytes.at(i + j) != marker[j]) {
                        marker_flag = false;
                        break;
                    } else {
                        marker_flag = true;
                    }
                }
            }
            if (marker_flag) {
                _marker_locations.push_back(i);
                i += (int)sizeof(marker);
            }
        }
        marker_flag = false;
    }
    return _marker_locations;
}

unsigned long changed_endian_4Bytes(unsigned long num){
    int byte0, byte1, byte2, byte3;
    byte0 = (num & 0x000000FF) >> 0 ;
    byte1 = (num & 0x0000FF00) >> 8 ;
    byte2 = (num & 0x00FF0000) >> 16 ;
    byte3 = (num & 0xFF000000) >> 24 ;
    return((byte0 << 24) | (byte1 << 16) | (byte2 << 8) | (byte3 << 0));
}

int16_t changed_endian_2Bytes(int16_t value){
    return ((value >> 8) & 0x00ff) | ((value & 0x00ff) << 8);
}

uint32_t crc32c(uint32_t crc, const unsigned char *buf, size_t len)
{
    int k;

    crc = ~crc;
    while (len--) {
        crc ^= *buf++;
        for (k = 0; k < 8; k++)
            crc = crc & 1 ? (crc >> 1) ^ 0xedb88320 : crc >> 1;
    }
    return ~crc;
}

static void Print(const char* format , ...){
    char    buf[LEN];
    char*   ch=buf;
    va_list args;
    //  Turn the parameters into a character string
    va_start(args,format);
    vsnprintf(buf,LEN,format,args);
    va_end(args);
    //  Display the characters one at a time at the current raster position
    while (*ch)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*ch++);
}

static void reshape(int width, int height){
    GLfloat h = (GLfloat) height / (GLfloat) width;

    glViewport(0, 0, (GLint) width, (GLint) height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0, 1.0, -h, h, 5.0, 60.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -40.0);
}