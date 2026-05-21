#include "AudioStreamer.h"

bool AudioStreamer::load(std::string path){
    src = path;

    junoR.phase1 = 3.141592f;
    junoR.phase2 = 0.0f;
    junoL.phase1 = 0.0f;
    junoL.phase2 = 3.141592f;

    string audioPath = "assets/Musics/" + src + ".wav";
    string lyricsPath = "assets/Lyrics/" + src + ".lrc";

    isLyricsAvailable = lyricsFile.load(lyricsPath);
    audioFile.stream = fopen(audioPath.c_str(), "rb");

    if(!audioFile.stream){
        printf("Cannot open source file!\n");
        return 1;
    }

    audioFile.init();
    Reverb_Juno_allocate_all(audioFile.sample_rate, &revL, &revR, &junoL, &junoR);

    int rv = snd_pcm_open(&pcm, "pulse", SND_PCM_STREAM_PLAYBACK, 0);
    if(rv < 0){
        fprintf(stderr, "Error >> %s\n", snd_strerror(rv));
        return 1;
    }

    snd_pcm_set_params(
        pcm, SND_PCM_FORMAT_U8,
        SND_PCM_ACCESS_RW_INTERLEAVED,
        2,
        audioFile.sample_rate,
        0,
        500000
    );

    printf("Now playing: %s\tSample rate: %u\n", src.c_str(), audioFile.sample_rate);
    fseek(audioFile.stream, audioFile.header_size, SEEK_SET);
}

void AudioStreamer::unload(void){
    snd_pcm_drain(pcm);
    snd_pcm_close(pcm);
    fclose(audioFile.stream);
    lyricsFile.unload();
    Reverb_Juno_release_all(&revL, &revR, &junoL, &junoR);
    printf("Exiting...\n");
}

void AudioStreamer::update(void){
    int key = GetKeyPressed();
    while(key != 0){
        switch(key){
            case KEY_Q:
                bassGain = bassGain >= HIGH_LIMIT ? HIGH_LIMIT : bassGain + DELTA; showINFO(); break;

            case KEY_A:
                bassGain = bassGain <= LOW_LIMIT ? LOW_LIMIT : bassGain - DELTA; showINFO(); break;

            case KEY_W:
                midGain = midGain >= HIGH_LIMIT ? HIGH_LIMIT : midGain + DELTA; showINFO(); break;

            case KEY_S:
                midGain = midGain <= LOW_LIMIT ? LOW_LIMIT : midGain - DELTA; showINFO(); break;

            case KEY_E:
                treGain = treGain >= HIGH_LIMIT ? HIGH_LIMIT : treGain + DELTA; showINFO(); break;

            case KEY_D:
                treGain = treGain <= LOW_LIMIT ? LOW_LIMIT : treGain - DELTA; showINFO(); break;

            case KEY_R:
                junoRate = junoRate >= HIGH_LIMIT ? HIGH_LIMIT : junoRate + 0.05f; showINFO(); break;

            case KEY_F:
                junoRate = junoRate <= LOW_LIMIT ? LOW_LIMIT : junoRate - 0.05f; showINFO(); break;

            case KEY_T:
                junoDepth = junoDepth >= 10000 ? 10000 : junoDepth + 100.0f; showINFO(); break;

            case KEY_G:
                junoDepth = junoDepth <= 0 ? 0 : junoDepth - 100.0f; showINFO(); break;

            case KEY_Y:
                junoMix = junoMix >= HIGH_LIMIT ? HIGH_LIMIT : junoMix + 0.05f; showINFO(); break;

            case KEY_H:
                junoMix = junoMix <= LOW_LIMIT ? LOW_LIMIT : junoMix - 0.05f; showINFO(); break;

            case KEY_U:
                reverbMix = reverbMix >= HIGH_LIMIT ? HIGH_LIMIT : reverbMix + 0.05f; showINFO(); break;

            case KEY_J:
                reverbMix = reverbMix <= LOW_LIMIT ? LOW_LIMIT : reverbMix - 0.05f; showINFO(); break;

            case KEY_I:
                reverbFeedback = reverbFeedback >= HIGH_LIMIT ? HIGH_LIMIT : reverbFeedback + 0.05f; showINFO(); break;

            case KEY_K:
                reverbFeedback = reverbFeedback <= LOW_LIMIT ? LOW_LIMIT : reverbFeedback - 0.05f; showINFO(); break;

            case KEY_SPACE:
                pauseAudio = !pauseAudio; printf("%s\n", pauseAudio ? "Streaming paused!" : "Resumed!"); break;

            case KEY_X:
                audioShouldStop = TRUE; break;

            case KEY_COMMA:
                rewindAudio(&audioFile); progressBar(&audioFile); break;

            case KEY_PERIOD:
                fastForwardAudio(&audioFile); progressBar(&audioFile); break;

        }
        key = GetKeyPressed();
    }
    
    if(pauseAudio || audioShouldStop){
        usleep(10000);
        return;
    }
    
    bytesRead = fread(inBuf, 1, BUFF_SIZE, audioFile.stream);
    if(bytesRead == 0){
        if(feof(audioFile.stream))
            return;
        return;
    }

    outIndex = 0;
    for(size_t i = 0; i+1 < bytesRead; i+=2){
        left.applyEQ(&inBuf[i], &revL, &junoL);
        right.applyEQ(&inBuf[i+1], &revR, &junoR);
        outBuf[outIndex++] = inBuf[i];
        outBuf[outIndex++] = inBuf[i+1];
    }
    if(snd_pcm_writei(pcm, outBuf, outIndex / 2) == -EPIPE)
        snd_pcm_prepare(pcm);
    
    currentTime = time(NULL);
    if(currentTime - previousTime >= 1 && !isLyricsAvailable)
        progressBar(&audioFile); previousTime = currentTime;
    if(isLyricsAvailable)
        lyricsFile.render(&audioFile);
}