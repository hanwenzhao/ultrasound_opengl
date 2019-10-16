#include "main.h"

void normalize_adc(std::vector<screen_data_struct> & _screen_data){
    for (i = 0; i < (int)_screen_data.size(); i++){
        _screen_data.at(i).I = (_screen_data.at(i).I - adc_min)/adc_max;
    }
}

int main(int argc,char* argv[]) {
    //std::clock_t begin = clock();
    /* #################### DATA PROCESSING #################### */
    /* read binary file */
    std::ifstream inFile("/home/hanwen/CLionProjects/ultrasound_opengl/short2.txt", std::ios::in | std::ios::binary);
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
    /* normalize adc value */
    normalize_adc(screen_data);


    // Initialize GLUT and process user parameters
    glutInit(&argc, argv);
    glWindowPos2i =  (PFNGLWINDOWPOS2IPROC) glutGetProcAddress("glWindowPos2i");
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    // create the window
    glutCreateWindow("ultrasound");
    //  Tell GLUT to call "display" when the scene should be drawn
    glutDisplayFunc(display);
    //  Pass control to GLUT so it can interact with the user
    glutMainLoop();
    return 0;
}

void data_to_pixel(std::vector<scan_data_struct> _scan_data, std::vector<screen_data_struct> & _screen_data){
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
        for (j = 0; j < (int)sizeof(_scan_data.at(i).buffer); j++){
            adc_max = std::max(adc_max, (int)_scan_data.at(i).buffer[j]);
            adc_min = std::min(adc_min, (int)_scan_data.at(i).buffer[j]);
            screen_data_struct temp_data = {(j+1) * Cos(angle), (j+1) * Sin(angle), 0, (double)_scan_data.at(i).buffer[j]};
            _screen_data.push_back(temp_data);
        }
    }
}

void file_to_data(std::vector<unsigned char> _file_bytes, std::vector<int> _marker_locations, std::vector<scan_data_struct> & _scan_data){
    for (i = 0; i < (int)_marker_locations.size()-1; i++){
        marker_index = _marker_locations.at(i);
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
        buffer_length = (int)(_marker_locations.at(1) - _marker_locations.at(0) - sizeof(marker) - sizeof(time_stamp_char) - sizeof(encoder_char) - sizeof(crc_char))/2;
        for (j = 0; j < buffer_length; j++){
            for (k = 0; k < (int)sizeof(adc_temp); k++){
                adc_temp[k] = _file_bytes.at(marker_index + sizeof(marker) + sizeof(time_stamp_char) + sizeof(encoder_char) + j * 2 + k);
            }
            std::memcpy(&adc, adc_temp, sizeof(adc));
            adc = changed_endian_2Bytes(adc);
            buffer[j] = adc;
        }
        scan_data_struct temp_struct;
        temp_struct.time_stamp = time_stamp;
        temp_struct.encoder = encoder;
        for (j = 0; j < buffer_length; j++){
            temp_struct.buffer[j] = buffer[j];
        }
        _scan_data.push_back(temp_struct);
    }
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

void display()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
    glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer (background)
    glPointSize(1);
    glBegin(GL_POINTS);
    for (i = 0; i < screen_data.size(); i++){
        double intensity = screen_data.at(i).I * 0.3;
        glColor3f(intensity, intensity, intensity);
        glVertex2d(screen_data.at(i).X*0.0003,screen_data.at(i).Y*0.0003+0.8);
    }
    glEnd();
    glFlush();
    glutSwapBuffers();
}
