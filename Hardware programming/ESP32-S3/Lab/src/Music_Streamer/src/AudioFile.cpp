#include "AudioFile.h"

void AudioFile::init(void){
    stream.seek(4);
    stream.read((uint8_t*)&file_size, 4);
    file_size+=8;

    stream.seek(24);
    stream.read((uint8_t*)&sample_rate, 4);

    stream.seek(40);
    for(int i = 40; 1; i++){
        if(stream.read() == 'd' && stream.read() == 'a' && stream.read() == 't' && stream.read() == 'a'){
            stream.seek(i+4);
            stream.read((uint8_t*)&data_size, 4);
            header_size = file_size - data_size;
            break;
        }
    }
    stream.seek(0);
}