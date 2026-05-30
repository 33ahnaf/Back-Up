#include "AudioFile.h"

void AudioFile::init(void){
    fseek(stream, 4, SEEK_SET);
    fread((uint8_t*)&file_size, 1, 4, stream);
    file_size+=8;

    fseek(stream, 24, SEEK_SET);
    fread((uint8_t*)&sample_rate, 1, 4, stream);

    fseek(stream, 40, SEEK_SET);
    for(int i = 40; 1; i++){
        if(fgetc(stream) == 'd' && fgetc(stream) == 'a' && fgetc(stream) == 't' && fgetc(stream) == 'a'){
            fseek(stream, i+4, SEEK_SET);
            fread((uint8_t*)&data_size, 1, 4, stream);
            header_size = file_size - data_size;
	        break;
        }
    }
    fseek(stream, 0, SEEK_SET);
}