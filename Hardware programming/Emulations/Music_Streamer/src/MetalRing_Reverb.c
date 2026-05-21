// #include <stddef.h>
// #include <stdio.h>
// #include <stdint.h>
// #include <alsa/asoundlib.h>
// #include <unistd.h>
// #include <termios.h>
// #include <fcntl.h>
// #include <math.h>

// // #define MAX_FILENAME_SIZE 300
// #define BUFF_SIZE 1024
// #define HIGH_LIMIT 1.0f
// #define LOW_LIMIT 0.0f
// #define DELTA 0.1f
// #define COMB1 25.30612245f
// #define COMB2 26.93877551f
// #define COMB3 28.9569161f
// #define COMB4 30.74829932f
// #define ALL1 12.60770975f
// #define ALL2 10.0f
// #define JUNO_BUF 50 // 50ms

// typedef struct {
//     // char path[MAX_FILENAME_SIZE];   /*  Path to the file. */
//     FILE *stream;           /*  Audio file stream.           */
//     uint32_t sample_rate;   /*  Sample rate in hertz.        */
//     uint32_t file_size;     /*  Total file size in bytes.    */
//     uint32_t data_size;     /*  Raw data size in bytes.      */
//     uint8_t  header_size;   /*  Length of header in bytes.   */
// } AudioFile;

// typedef struct {
//     float low;
//     float high;
// } EQState;

// typedef struct {
//     float *buffer;
//     int writePos;
//     int size;
//     float feedback;
//     float filterStore;
//     float damp;
// } Comb;

// typedef struct {
//     float *buffer;
//     int writePos;
//     int size;
//     float feedback;
// } Allpass;

// typedef struct {
//     float *buffer;
//     int writePos;
//     int size;
//     float phase1;
//     float phase2;
// } JunoState;

// EQState left = {0};
// EQState right = {0};
// Comb combs[4] = {0};
// Allpass all1 = {0}, all2 = {0};
// JunoState junoL = {0};
// JunoState junoR = {0};

// float bassGain = 100.0f / 100.0f;
// float midGain = 10.0f / 100.0f;
// float treGain = 100.0f / 100.0f;
// float reverbMix = 0.2f; //wet amount
// float junoRate = 0.15f; // 0.05f
// float junoDepth = 700.0f; // 800.0f
// float junoMix = 0.5f; // 0.4f

// // optimal DO NOT TOUCH
// float lowCut = 0.01;
// float highCut = 0.125;


// int constrain(int amt, int low, int high);
// void AudioFile_init(AudioFile *audioFile);
// void Reverb_varialbes_init(void);
// void Reverb_allocate(uint32_t sample_rate);
// void Reverb_release(void);
// void Juno_allocate(JunoState *st, uint32_t sample_rate);
// void Juno_release(JunoState *st);
// void Reverb_Juno_allocate_all(uint32_t sample_rate);
// void Reverb_Juno_release_all(void);

// void applyJuno(float *sample, JunoState *st);
// float comb_process(float sample, Comb *c);
// void allpass_process(float *sample, Allpass *a);
// void applyReverb(float *sample);
// void applyEQ(uint8_t *sample, EQState *st, float bassGain, float midGain, float treGain);
// void showINFO(void);
// void streamAudio(AudioFile *audioFile, char *path);
// void increaseCombsFB(void);
// void decreaseCombsFB(void);

// int main(int argc, char **argv){
//     AudioFile audioFile;
//     junoR.phase1 = 3.141592f;
//     junoR.phase2 = 0.0f;

//     // FILE* audioFile = fopen(argc > 1 ? argv[1] : NULL, "rb");
//     if(argc > 1){
//         audioFile.stream = fopen(argv[1], "rb");
//         AudioFile_init(&audioFile);
//     }else{
//         printf("Error: Argument not given!");
//         return -1;
//     }
    
//     if(!audioFile.stream){
//         printf("Cannot open file!");
//         return 1;
//     }
//     streamAudio(&audioFile, argv[1]);
//     return 0;
// }

// void streamAudio(AudioFile *audioFile, char *path){
//     Reverb_Juno_allocate_all(audioFile->sample_rate);
//     snd_pcm_t *pcm;
//     int rv = snd_pcm_open(&pcm, "pulse", SND_PCM_STREAM_PLAYBACK, 0);
//     if(rv < 0){
//         fprintf(stderr, "Error >> %s\n", snd_strerror(rv));
//         return;
//     }

//     struct termios oldt, newt;
//     tcgetattr(STDIN_FILENO, &oldt);
//     newt = oldt;
//     newt.c_lflag &= ~(ICANON | ECHO);
//     tcsetattr(STDIN_FILENO, TCSANOW, &newt);
//     fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);

//     snd_pcm_set_params(
//             pcm,
//             SND_PCM_FORMAT_U8,
//             SND_PCM_ACCESS_RW_INTERLEAVED,
//             2,
//             audioFile->sample_rate,
//             0,
//             500000
//     );

//     uint8_t inBuf[BUFF_SIZE] = {0};
//     uint8_t outBuf[BUFF_SIZE] = {0}; // although ouBuf is unsed, could've done everything with using only inBuf but still it is present for future use
//     size_t bytesRead;
//     size_t outIndex;

//     printf("Now playing: %s\tSample rate: %u\n", path, audioFile->sample_rate);

//     fseek(audioFile->stream, audioFile->header_size, SEEK_SET);

//     while(1){
//         int c = getchar();
//         switch(c){
//             case 'q': bassGain = bassGain >= HIGH_LIMIT ? HIGH_LIMIT : bassGain + DELTA; showINFO(); break;
//             case 'a': bassGain = bassGain <= LOW_LIMIT ? LOW_LIMIT : bassGain - DELTA; showINFO(); break;

//             case 'w': midGain = midGain >= HIGH_LIMIT ? HIGH_LIMIT : midGain + DELTA; showINFO(); break;
//             case 's': midGain = midGain <= LOW_LIMIT ? LOW_LIMIT : midGain - DELTA; showINFO(); break;

//             case 'e': treGain = treGain >= HIGH_LIMIT ? HIGH_LIMIT : treGain + DELTA; showINFO(); break;
//             case 'd': treGain = treGain <= LOW_LIMIT ? LOW_LIMIT : treGain - DELTA; showINFO(); break;

//             case 'r': junoRate = junoRate >= HIGH_LIMIT ? HIGH_LIMIT : junoRate + 0.05f; showINFO(); break;
//             case 'f': junoRate = junoRate <= LOW_LIMIT ? LOW_LIMIT : junoRate - 0.05f; showINFO(); break;

//             case 't': junoDepth = junoDepth >= 10000 ? 10000 : junoDepth + 100.0f; showINFO(); break;
//             case 'g': junoDepth = junoDepth <= 0 ? 0 : junoDepth - 100.0f; showINFO(); break;

//             case 'y': junoMix = junoMix >= HIGH_LIMIT ? HIGH_LIMIT : junoMix + 0.05f; showINFO(); break;
//             case 'h': junoMix = junoMix <= LOW_LIMIT ? LOW_LIMIT : junoMix - 0.05f; showINFO(); break;

//             case 'u': reverbMix = reverbMix >= HIGH_LIMIT ? HIGH_LIMIT : reverbMix + 0.05f; showINFO(); break;
//             case 'j': reverbMix = reverbMix <= LOW_LIMIT ? LOW_LIMIT : reverbMix - 0.05f; showINFO(); break;

//             case 'i': increaseCombsFB(); showINFO(); break;
//             case 'k': decreaseCombsFB(); showINFO(); break;
//         }
//         bytesRead = fread(inBuf, 1, BUFF_SIZE, audioFile->stream);
//         if(bytesRead == 0)  break;

//         outIndex = 0;
//         for(size_t i = 0; i+1 < bytesRead; i+=2){
//             applyEQ(&inBuf[i], &left, bassGain, midGain, treGain);
//             applyEQ(&inBuf[i+1], &right, bassGain, midGain, treGain);
//             outBuf[outIndex++] = inBuf[i];
//             outBuf[outIndex++] = inBuf[i+1];
//         }
//         snd_pcm_writei(pcm, outBuf, outIndex / 2);
//     }
//     snd_pcm_drain(pcm);
//     snd_pcm_close(pcm);
//     fclose(audioFile->stream);
//     tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
//     Reverb_Juno_release_all();
//     printf("Exiting...\n");
// }

// void showINFO(){
//     // printf("bass: %1.1f  mid: %1.1f  tre: %1.1f     lowCut: %1.3f  highCut: %1.3f     reverbMix: %1.2f  reverbFeedback: %1.2f\n", bassGain, midGain, treGain, lowCut, highCut, reverbMix, reverbFeedback);
//     // printf("bass: %1.1f  mid: %1.1f  tre: %1.1f     junoRate: %1.2f  junoDepth: %4.1f  junoMix: %1.2f     reverbMix: %1.2f  reverbFB: %1.2f\n", bassGain, midGain, treGain, junoRate, junoDepth, junoMix, reverbMix, reverbFeedback);
//     printf("bass: %1.1f  mid: %1.1f  tre: %1.1f     junoRate: %1.2f  junoDepth: %4.1f  junoMix: %1.2f     reverbMix: %1.2f\nComb[0].FB: %1.2f   Comb[1].FB: %1.2f   Comb[2].FB: %1.2f   Comb[3].FB: %1.2f\n", bassGain, midGain, treGain, junoRate, junoDepth, junoMix, reverbMix, combs[0].feedback, combs[1].feedback, combs[2].feedback, combs[3].feedback);
// }

// int constrain(int amt, int low, int high){
//     if(amt > high) return high;
//     if(amt < low) return low;
//     return amt;
// }

// void AudioFile_init(AudioFile *audioFile){
//     fseek(audioFile->stream, 4, SEEK_SET);
//     fread((uint8_t*)&audioFile->file_size, 1, 4, audioFile->stream);
//     audioFile->file_size+=8;

//     fseek(audioFile->stream, 24, SEEK_SET);
//     fread((uint8_t*)&audioFile->sample_rate, 1, 4, audioFile->stream);

//     fseek(audioFile->stream, 40, SEEK_SET);
//     for(int i = 40; i < 100; i++){
//         if(fgetc(audioFile->stream) == 'd' && fgetc(audioFile->stream) == 'a' && fgetc(audioFile->stream) == 't' && fgetc(audioFile->stream) == 'a'){
//             fseek(audioFile->stream, i+4, SEEK_SET);
//             fread((uint8_t*)&audioFile->data_size, 1, 4, audioFile->stream);
//             audioFile->header_size = audioFile->file_size - audioFile->data_size;
// 	    break;
//         }
//     }
//     fseek(audioFile->stream, 0, SEEK_SET);
// }

// void applyJuno(float *sample, JunoState *st){
//     st->buffer[st->writePos] = *sample;

//     float lfo1 = (sin(st->phase1) + 1.0f) * 0.5f;
//     float lfo2 = (sin(st->phase2) + 1.0f) * 0.5f;

//     float delay1 = 200 + lfo1 * junoDepth;
//     float delay2 = 200 + lfo2 * junoDepth;

//     int readPos1 = st->writePos - (int)delay1;
//     int readPos2 = st->writePos - (int)delay2;

//     if(readPos1 < 0) readPos1 += st->size;
//     if(readPos2 < 0) readPos2 += st->size;

//     float delayed1 = st->buffer[readPos1];
//     float delayed2 = st->buffer[readPos2];

//     float chor = (delayed1 + delayed2) * 0.5f;

//     *sample = *sample * (1.0f - junoMix) + chor * junoMix;
//     st->writePos++;
//     if(st->writePos >= st->size)
//         st->writePos = 0;
//     st->phase1 += junoRate * 0.001f;
//     st->phase2 += junoRate * 0.001f * 0.7f;
//     if(st->phase1 > 6.283185f)   st->phase1 -= 6.283185f;
//     if(st->phase2 > 6.283185f)   st->phase2 -= 6.283185f;
// }

// float comb_process(float sample, Comb *c){
//     float output = c->buffer[c->writePos];
//     c->filterStore = (output * (1.0f - c->damp)) + (c->filterStore*c->damp);
//     c->buffer[c->writePos] = sample + c->filterStore * c->feedback;
//     c->writePos++;
//     if(c->writePos >= c->size)
//         c->writePos = 0;
//     return output;
// }

// void allpass_process(float *sample, Allpass *a){
//     float bufout = a->buffer[a->writePos];
//     float output = -*sample + bufout;
//     a->buffer[a->writePos] = *sample + bufout * a->feedback;
//     a->writePos++;
//     if(a->writePos >= a->size)
//         a->writePos = 0;
//     *sample = output;
// }

// void applyReverb(float *sample){
//     float input = *sample;
//     float sum = 0;
//     sum += comb_process(input, &combs[0]);
//     sum += comb_process(input, &combs[1]);
//     sum += comb_process(input, &combs[2]);
//     sum += comb_process(input, &combs[3]);

//     sum *= 0.25f;

//     allpass_process(&sum, &all1);
//     allpass_process(&sum, &all2);

//     *sample = input*(1.0f - reverbMix) + sum*reverbMix;
// }

// void applyEQ(uint8_t *sample, EQState *st, float bassGain, float midGain, float treGain){
//     // Normalize
//     float s = (float)(*sample - 128);

//     // low band
//     st->low += lowCut * (s - st->low);

//     // high band
//     float hp = s - st->low;
//     st->high += highCut * (hp - st->high);

//     float low = st->low;
//     float high = st->high;
//     float mid = s - low - high;
//     float out = low * bassGain + mid * midGain + high * treGain;

//     applyReverb(&out);
//     applyJuno(&out, st == &left ? &junoL : &junoR);

//     *sample = constrain((int)(out + 128), 0, 255);
// }

// void Reverb_varialbes_init(void){
//     combs[0] = (Comb){NULL, 0, COMB1, 0.805, 0.0f, 0.2f};
//     combs[1] = (Comb){NULL, 0, COMB2, 0.827, 0.0f, 0.2f};
//     combs[2] = (Comb){NULL, 0, COMB3, 0.783, 0.0f, 0.2f};
//     combs[3] = (Comb){NULL, 0, COMB4, 0.764, 0.0f, 0.2f};
//     all1 = (Allpass){NULL, 0, ALL1, 0.7};
//     all2 = (Allpass){NULL, 0, ALL2, 0.7};
// }

// void Reverb_allocate(uint32_t sample_rate){
//     combs[0].size = (COMB1 / 1000.0f) * sample_rate;
//     combs[1].size = (COMB2 / 1000.0f) * sample_rate;
//     combs[2].size = (COMB3 / 1000.0f) * sample_rate;
//     combs[3].size = (COMB4 / 1000.0f) * sample_rate;
//     all1.size = (ALL1 / 1000.0f) * sample_rate;
//     all2.size = (ALL2 / 1000.0f) * sample_rate;
//     combs[0].buffer = (float*)malloc(combs[0].size * sizeof(float));
//     combs[1].buffer = (float*)malloc(combs[1].size * sizeof(float));
//     combs[2].buffer = (float*)malloc(combs[2].size * sizeof(float));
//     combs[3].buffer = (float*)malloc(combs[3].size * sizeof(float));
//     all1.buffer = (float*)malloc(all1.size * sizeof(float));
//     all2.buffer = (float*)malloc(all2.size * sizeof(float));
//     memset(combs[0].buffer, 0, combs[0].size * sizeof(float));
//     memset(combs[1].buffer, 0, combs[1].size * sizeof(float));
//     memset(combs[2].buffer, 0, combs[2].size * sizeof(float));
//     memset(combs[3].buffer, 0, combs[3].size * sizeof(float));
//     memset(all1.buffer, 0, all1.size * sizeof(float));
//     memset(all2.buffer, 0, all2.size * sizeof(float));
//     printf("combs[0] size: %lf\n", (COMB1 / 1000.0f) * sample_rate);
//     printf("combs[1] size: %lf\n", (COMB2 / 1000.0f) * sample_rate);
//     printf("combs[2] size: %lf\n", (COMB3 / 1000.0f) * sample_rate);
//     printf("combs[3] size: %lf\n", (COMB4 / 1000.0f) * sample_rate);
//     printf("all1 size: %lf\n", (ALL1 / 1000.0f) * sample_rate);
//     printf("all2 size: %lf\n", (ALL2 / 1000.0f) * sample_rate);
// }

// void Reverb_release(void){
//     free(combs[0].buffer);
//     free(combs[1].buffer);
//     free(combs[2].buffer);
//     free(combs[3].buffer);
//     free(all1.buffer);
//     free(all2.buffer);
//     combs[0].size = 0;
//     combs[1].size = 0;
//     combs[2].size = 0;
//     combs[3].size = 0;
//     all1.size = 0;
//     all2.size = 0;
// }

// void Juno_allocate(JunoState *st, uint32_t sample_rate){
//     st->size = (JUNO_BUF / 1000.0f) * sample_rate;
//     st->buffer = (float*)malloc(st->size * sizeof(float));
//     memset(st->buffer, 0, st->size * sizeof(float));
//     printf("Juno size: %u\n", st->size);
// }

// void Juno_release(JunoState *st){
//     free(st->buffer);
//     st->size = 0;
// }

// void Reverb_Juno_allocate_all(uint32_t sample_rate){
//     Reverb_allocate(sample_rate);
//     Juno_allocate(&junoL, sample_rate);
//     Juno_allocate(&junoR, sample_rate);
// }

// void Reverb_Juno_release_all(void){
//     Reverb_release();
//     Juno_release(&junoL);
//     Juno_release(&junoR);
// }

// void increaseCombsFB(){
//     for(int i = 0; i < 4; i++)
//         combs[i].feedback = combs[i].feedback >= HIGH_LIMIT ? HIGH_LIMIT : combs[i].feedback + 0.2f;
// }

// void decreaseCombsFB(){
//     for(int i = 0; i < 4; i++)
//         combs[i].feedback = combs[i].feedback <= LOW_LIMIT ? LOW_LIMIT : combs[i].feedback - 0.2f;
// }