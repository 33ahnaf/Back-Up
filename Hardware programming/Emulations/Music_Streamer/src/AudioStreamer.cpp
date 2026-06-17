#include "AudioStreamer.h"
#include "globals.h"
#include "MISC.h"

#define MODULE_NAME "AudioStreamer"

AudioStreamer audio;

void AudioStreamer::load(std::string src){

    junoR.phase1 = 3.141592f;
    junoR.phase2 = 0.0f;
    junoL.phase1 = 0.0f;
    junoL.phase2 = 3.141592f;

    std::string audioPath = MUSICS_DIRECTORY + src;
    std::string lyricsPath = LYRICS_DIRECTORY + src.replace(src.size() - 3, 3, "lrc");
    // printf("\n\n%s\n\n", audioPath.c_str());
    // printf("\n\n%s\n\n", lyricsPath.c_str());

    isLyricsAvailable = lyricsFile.load(lyricsPath);
    audioFile.stream = fopen(audioPath.c_str(), "rb");

    if(!audioFile.stream){
        printf("Error: Cannot open source file! [%s]\n", MODULE_NAME);
        return;
    }

    audioFile.init();
    Reverb_Juno_allocate_all(audioFile.sample_rate, &revL, &revR, &junoL, &junoR);

    int rv = snd_pcm_open(&pcm, "pulse", SND_PCM_STREAM_PLAYBACK, 0);
    if(rv < 0){
        printf("Error: %s [%s]\n", snd_strerror(rv), MODULE_NAME);
        return;
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
    isLoaded = true;
    isUnloaded = false;
}

void AudioStreamer::unload(void){
    snd_pcm_drain(pcm);
    snd_pcm_close(pcm);
    fclose(audioFile.stream);
    lyricsFile.unload();
    Reverb_Juno_release_all(&revL, &revR, &junoL, &junoR);
    printf("\nExiting from Streamer...\n");
    isLoaded = false;
    isUnloaded = true;
    app.isPlaying = false;
}

void AudioStreamer::update(void){
    if(app.isPlaying && !isLoaded)
        load(app.selectedSong);

    if(!app.isPlaying){
        if(isLoaded && !isUnloaded)
            unload();
    }

    if(!app.isPlaying)
        return;
    
    if(pauseAudio){
        usleep(10000);
        return;
    }
    
    bytesRead = fread(inBuf, 1, BUFF_SIZE, audioFile.stream);
    if(bytesRead == 0){
        if(feof(audioFile.stream))
            app.isPlaying = false;
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
    if(currentTime - previousTime >= 1 && !isLyricsAvailable){
        progressBar();
        previousTime = currentTime;
    }
    
    if(isLyricsAvailable)
        lyricsFile.render(&audioFile);
}

void AudioStreamer::fastForwardAudio(size_t milliseconds){
    if(ftell(audioFile.stream) + audioFile.sample_rate*2*(milliseconds / 1000.0) > audioFile.file_size){
        fseek(audioFile.stream, audioFile.file_size-1, SEEK_SET);
        // printf("\nCurrent position: %dth byte\n", ftell(audioFile->stream));
    }else{
        fseek(audioFile.stream, audioFile.sample_rate*2*(milliseconds / 1000.0), SEEK_CUR);
        // printf("\nCurrent position: %dth byte\n", ftell(audioFile->stream));
    }
}

void AudioStreamer::rewindAudio(size_t milliseconds){
    if(ftell(audioFile.stream) - audioFile.sample_rate*2*(milliseconds / 1000.0) > 0){
        fseek(audioFile.stream, ftell(audioFile.stream) - audioFile.sample_rate*2*(milliseconds / 1000.0), SEEK_SET);
        // printf("\nCurrent position: %dth byte\n", ftell(audioFile->stream));
    }else{
        fseek(audioFile.stream, audioFile.header_size, SEEK_SET);
        // printf("\nCurrent position: %dth byte\n", ftell(audioFile->stream));
    }
}

void AudioStreamer::progressBar(void){
    int progress = (int)((double)ftell(audioFile.stream) / audioFile.data_size * 100.0f);
    int totalSeconds = audioFile.data_size / (audioFile.sample_rate*2);
    int currentSecond = (ftell(audioFile.stream) - audioFile.header_size) / (audioFile.sample_rate*2);
    printf("\r%3d%%", progress);
    printf(" [");
    for(int i = 0; i < 50; i++){
        if(i < progress/2)
            printf("+");
        else
            printf(" ");
    }
    printf("]\t%02d:%02d / %02d:%02d", currentSecond/60, currentSecond%60, totalSeconds/60, totalSeconds%60);
    fflush(stdout);
}

void showINFO(void){
    // printf("bass: %1.1f  mid: %1.1f  tre: %1.1f     lowCut: %1.3f  highCut: %1.3f     reverbMix: %1.2f  reverbFeedback: %1.2f\n", bassGain, midGain, treGain, lowCut, highCut, reverbMix, reverbFeedback);
    printf("\nbass: %1.1f  mid: %1.1f  tre: %1.1f     junoRate: %1.2f  junoDepth: %4.1f  junoMix: %1.2f     reverbMix: %1.2f  reverbFB: %1.2f\n", bassGain, midGain, treGain, junoRate, junoDepth, junoMix, reverbMix, reverbFeedback);
}