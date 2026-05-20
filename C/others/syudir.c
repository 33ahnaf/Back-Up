/*      SYUDIR v2.0     */
#include <stdio.h>
#include <unistd.h>
#include <libgen.h>
#include <string.h>
#include <stdlib.h>

#define INI_PATH        "../../platformio.ini"
#define MAX_BUFFER      1024
#define MAX_TOTAL_SIZE  4096

int main(){
    char *cwd = getcwd(NULL, 0);
    if(!cwd){
        fprintf(stderr, "Error: Cannot get the current working directory path name.\n");
        return -1;
    }

    char *base = basename(cwd);

    char folder[MAX_BUFFER];
    strncpy(folder, base, sizeof(folder) - 1);
    folder[sizeof(folder) - 1] = '\0';
    
    free(cwd);

    FILE *in = fopen(INI_PATH, "r");
    if(!in){
        fprintf(stderr, "Error: Cannot find the platformIO file.\n");
        return -1;
    }

    char buffer[MAX_BUFFER];
    char output[MAX_TOTAL_SIZE] = {0};

    while(fgets(buffer, sizeof(buffer), in)){
        if(strstr(buffer, "build_src_filter"))
            snprintf(buffer, sizeof(buffer), "build_src_filter = -<*> +<%s>\n", folder);
        strcat(output, buffer);
    }
    fclose(in);

    FILE *out = fopen(INI_PATH, "w");
    if(!out){
        fprintf(stderr, "Error: Cannot find the platformIO file.\n");
        return -1;
    }

    fputs(output, out);
    fclose(out);

    printf("Active source set to: %s\n", folder);
    return 0;
}



/*      SYUDIR v1.0     */
// #include <stdio.h>
// #include <unistd.h>
// #include <libgen.h>

// int main(){
//     FILE *PlatformIO_ini = fopen("/home/ahnaf/CODER'S PARADISE/Hardware programming/ESP32/Lab/platformio.ini", "w");
//     char *cwd = basename(getcwd(NULL, 0));
//     fprintf(PlatformIO_ini, "[env:esp32]\nplatform = espressif32\nboard = esp32dev\nframework = arduino\nbuild_flags = -O2\nbuild_src_filter = +<%s>", cwd);
//     return 0;
// }
