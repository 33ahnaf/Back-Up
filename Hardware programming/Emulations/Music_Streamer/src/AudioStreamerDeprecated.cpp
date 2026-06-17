// #include "AudioStreamer.h"
// #include <alsa/asoundlib.h>
// #include <unistd.h>
// #include <termios.h>
// #include <fcntl.h>
// #include "AudioFile.h"
// #include "LyricsFile.h"
// #include "DSP_Effects.h"
// #include "globals.h"
// #include "MISC.h"
// #include "GUI.h"

// #define BUFF_SIZE 1024
// #define HIGH_LIMIT 1.0f
// #define LOW_LIMIT 0.0f
// #define DELTA 0.1f
// #define TRUE 1
// #define FALSE 0

// typedef std::string string;

// uint8_t inBuf[BUFF_SIZE];
// uint8_t outBuf[BUFF_SIZE]; // although ouBuf is unsed, could've done everything with using only inBuf but still it is present for future use
// AudioFile audioFile;
// LyricsFile lyricsFile;
// EQState left = {};
// EQState right = {};
// ReverbState revL = {};
// ReverbState revR = {};
// JunoState junoL = {};
// JunoState junoR = {};

// void streamAudio(std::string src){
//     junoR.phase1 = 3.141592f;
//     junoR.phase2 = 0.0f;
//     junoL.phase1 = 0.0f;
//     junoL.phase2 = 3.141592f;

//     string audioPath = "assets/Musics/" + src + ".wav";
//     string lyricsPath = "assets/Lyrics/" + src + ".lrc";

//     bool isLyricsAvailable = lyricsFile.load(lyricsPath);
//     audioFile.stream = fopen(audioPath.c_str(), "rb");
//     if(!audioFile.stream){
//         printf("Cannot open source file!\n");
//         return;
//     }
//     audioFile.init();
//     Reverb_Juno_allocate_all(audioFile.sample_rate, &revL, &revR, &junoL, &junoR);

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
//             audioFile.sample_rate,
//             0,
//             500000
//     );

//     size_t bytesRead;
//     size_t outIndex;
//     uint8_t pauseAudio = FALSE;
//     uint8_t exitFlag = FALSE;
//     time_t currentTime;
//     time_t previousTime;

//     printf("Now playing: %s\tSample rate: %u\n", src.c_str(), audioFile.sample_rate);

//     fseek(audioFile.stream, audioFile.header_size, SEEK_SET);

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

//             case 'i': reverbFeedback = reverbFeedback >= HIGH_LIMIT ? HIGH_LIMIT : reverbFeedback + 0.05f; showINFO(); break;
//             case 'k': reverbFeedback = reverbFeedback <= LOW_LIMIT ? LOW_LIMIT : reverbFeedback - 0.05f; showINFO(); break;

//             case ' ': pauseAudio = !pauseAudio; printf("%s\n", pauseAudio ? "Streaming paused!" : "Resumed!"); break;
//             case 'x': exitFlag = TRUE; break;
//             case ',': rewindAudio(&audioFile); progressBar(&audioFile); break;
//             case '.': fastForwardAudio(&audioFile); progressBar(&audioFile); break;
//         }
//         if(exitFlag){
//             break;
//         }if(pauseAudio){
//             usleep(10000);
//             continue;
//         }
//         bytesRead = fread(inBuf, 1, BUFF_SIZE, audioFile.stream);
//         if(bytesRead == 0){
//             if(feof(audioFile.stream))
//                 break;
//             continue;
//         }

//         outIndex = 0;
//         for(size_t i = 0; i+1 < bytesRead; i+=2){
//             left.applyEQ(&inBuf[i], &revL, &junoL);
//             right.applyEQ(&inBuf[i+1], &revR, &junoR);
//             outBuf[outIndex++] = inBuf[i];
//             outBuf[outIndex++] = inBuf[i+1];
//         }
//         if(snd_pcm_writei(pcm, outBuf, outIndex / 2) == -EPIPE)
//             snd_pcm_prepare(pcm);
//         currentTime = time(NULL);
//         if(currentTime - previousTime >= 1 && !isLyricsAvailable){
//             progressBar(&audioFile);
//             previousTime = currentTime;
//         }
//         if(isLyricsAvailable)
//             lyricsFile.render(&audioFile);
//     }
//     snd_pcm_drain(pcm);
//     snd_pcm_close(pcm);
//     fclose(audioFile.stream);
//     lyricsFile.unload();
//     tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
//     Reverb_Juno_release_all(&revL, &revR, &junoL, &junoR);
//     printf("Exiting...\n");
// }