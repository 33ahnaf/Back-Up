#ifndef _AUDIOFILE__H
#define _AUDIOFILE__H

#include <stdio.h>
#include <stdint.h>

typedef struct {
    // char path[MAX_FILENAME_SIZE];   /*  Path to the file. */
    FILE *stream;           /*  Audio file stream.           */
    uint32_t sample_rate;   /*  Sample rate in hertz.        */
    uint32_t file_size;     /*  Total file size in bytes.    */
    uint32_t data_size;     /*  Raw data size in bytes.      */
    uint8_t  header_size;   /*  Length of header in bytes.   */

    void init(void);
} AudioFile;

#endif