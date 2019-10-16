#include "main.h"

#include <boost/tokenizer.hpp>

struct scan_data_char{
    unsigned char time_stamp_char[4];
    unsigned char encoder_char[2];
    unsigned char adc_char[4980];
    unsigned char crc_char[4];
};

struct scan_data_struct{
    unsigned long time_stamp;
    uint16_t encoder;
    int16_t buffer[2490];
    unsigned crc[4];
};

const unsigned char marker[10] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
int i, j, marker_index;
bool marker_flag;
std::vector<int> marker_locations;
std::vector<scan_data_struct> scan_data;

std::vector<int> find_marker(std::vector<unsigned char> _file_bytes);


int main() {
    std::clock_t begin = clock();
    /* #################### DATA PROCESSING #################### */
    /* read binary file */
    std::ifstream inFile("/home/hanwen/CLionProjects/ultrasound_opengl/short2.txt", std::ios::in | std::ios::binary);
    /* convert file to bytes vector */
    /* DO NOT USE ISTREAM_ITERATOR*/
    std::vector<unsigned char> file_bytes(
            (std::istreambuf_iterator<char>(inFile)),
            (std::istreambuf_iterator<char>()));
    printf("Size of File: %lu\n", file_bytes.size());
    /* find all marker locations */
    marker_locations = find_marker(file_bytes);


    std::clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    printf("Time: %f\n", elapsed_secs);
    return 0;
}

std::vector<scan_data_struct> file_to_data(std::vector<unsigned char> _file_bytes, std::vector<int> _marker_locations){
    for (i = 0; i < (int)_marker_locations.size(); i++){
        marker_index = _marker_locations.at(i);

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