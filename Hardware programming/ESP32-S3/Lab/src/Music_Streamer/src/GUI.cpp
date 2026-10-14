#include "GUI.h"
#include "globals.h"
#include "LGFX_Helper.h"
#include <Arduino.h>
#include <string.h>
#include <SD_MMC.h>

#define TFT_VISIBLE_ITEMS 12

#define MODULE_NAME "GUI"

bool dirty = true;

MenuItem settingsMenu[] = {
    { "Brightness",         NULL, 0, NULL },
    { "Themes",             NULL, 0, NULL },
    { "Scroll Wrapping",    NULL, 0, NULL }
};

MenuItem mainMenu[] = {
    { "Songs",      NULL, 0, OpenSongs },
    { "Settings",   settingsMenu, sizeof(settingsMenu) / sizeof(settingsMenu[0]), NULL },
    { "Search",     NULL, 0, NULL }
};

UIState ui = {
    .currentMenu = mainMenu,
    .itemCount = sizeof(mainMenu) / sizeof(mainMenu[0]),
    .selected = 0,
    .scroll = 0,
    .parentIndex = 0,
};

SongBrowser songBrowser;
AudioPlayer audioPlayer;


void UIState::Enter(void){
    MenuItem *item = &currentMenu[selected];

    if(item->children){
        parentStack[parentIndex++] = (MenuState){
            currentMenu,
            itemCount,
            selected,
            scroll
        };

        currentMenu = item->children;
        itemCount = item->childCount;
        selected = 0;
        scroll = 0;
    }else if(item->action){
        item->action();
    }
}

void UIState::Back(void){
    if(parentIndex > 0){
        MenuState prev = parentStack[--parentIndex];

        currentMenu = prev.menu;
        itemCount = prev.count;
        selected = prev.selected;
        scroll = prev.scroll;
    }
}

void UIState::DrawMenu(void){
    tft.fillScreen(TFT_BLACK);
    tft.setTextSize(2);
    tft.setTextDatum(TL_DATUM);
    for(int i = 0; i < TFT_VISIBLE_ITEMS; i++){
        int idx = i + scroll;
        if(idx >= itemCount) break;

        int y = i * 20;

        if(idx == selected){
            tft.drawRect(0, y - 2, TFT_W, 18, TFT_DARKGRAY);
            tft.setTextColor(TFT_YELLOW);
            tft.drawString("> ", 2, y);
            tft.drawString(currentMenu[idx].name, 13, y);
        }else{
            tft.setTextColor(TFT_GREEN);
            tft.drawString(currentMenu[idx].name, 13, y);
        }
    }
}

void UIState::HandleInput(bool up, bool down, bool enter, bool back){
    
    if(down){
        selected++;
        dirty = true;
        if(selected >= itemCount)
            selected = itemCount - 1;
    }else if(up){
        selected--;
        dirty = true;
        if(selected < 0)
            selected = 0;
    }

    if(selected >= scroll + TFT_VISIBLE_ITEMS)
        scroll = selected - TFT_VISIBLE_ITEMS + 1;

    if(selected < scroll)
        scroll = selected;

    if(enter){
        dirty = true; Enter();
    }else if(back){
        dirty = true; Back();
    }
}

void OpenSongs(void){
    songBrowser.LoadSongs(MUSICS_DIRECTORY);
    app.currentScreen = SCREEN_SONG_BROWSER;
}

void SongBrowser::LoadSongs(const std::string path){
    songs.clear();

    File muDirec = SD_MMC.open(path.c_str());
    if(!muDirec || !muDirec.isDirectory()){
        Serial.printf("Error: Could not open musics directory! [%s]\n", MODULE_NAME);
        while(1) delay(1000);
    }

    File file = muDirec.openNextFile();
    std::string filename;
    while(file){
        if(!file.isDirectory())
            if(std::string(file.name()).find_last_of(".") != std::string::npos)
                songs.push_back(std::string(file.name()).substr(0, std::string(file.name()).find_last_of(".")));
        file = muDirec.openNextFile();
    }
    file.close();
    muDirec.close();
    selected = 0;
    scroll = 0;
}

void SongBrowser::HandleInput(bool up, bool down, bool enter, bool back){
    
    if(down){
        selected++;
        dirty = true;
        if(selected >= (int)songs.size())
            selected = songs.size() - 1;
    }

    if(up){
        selected--;
        dirty = true;
        if(selected < 0)
            selected = 0;
    }

    if(selected >= scroll + TFT_VISIBLE_ITEMS)
        scroll = selected - TFT_VISIBLE_ITEMS + 1;
    
    if(selected < scroll)
        scroll = selected;
    
    if(enter){
        if(songs.empty())return;
        app.selectedSong = songs[selected];
        app.currentScreen = SCREEN_AUDIO_PLAYER;
        app.isPlaying = true;
        dirty = true;
    }

    if(back){
        dirty = true;
        app.currentScreen = SCREEN_MENU;
    }
}

void SongBrowser::DrawSongs(void){
    tft.fillScreen(TFT_BLACK);
    tft.setTextSize(2);
    tft.setTextDatum(TL_DATUM);

    for(int i = 0; i < TFT_VISIBLE_ITEMS; i++){
        int idx = i + scroll;
        if(idx >= (int)songs.size()) break;

        int y = i * 20;

        if(idx == selected){
            tft.drawRect(0, y - 2, TFT_W, 18, TFT_DARKGRAY);
            tft.setTextColor(TFT_YELLOW);
            tft.drawString("> ", 2, y);
            tft.drawString(songs[idx].c_str(), 13, y);
        }else{
            tft.setTextColor(TFT_GREEN);
            tft.drawString(songs[idx].c_str(), 13, y);
        }
    }
}

void AudioPlayer::DrawPlayer(void){
    tft.fillScreen(TFT_BLACK);
    tft.setTextSize(2);
    tft.setTextDatum(MC_DATUM);

    tft.setTextColor(TFT_SKYBLUE);
    tft.drawString("NOW PLAYING", TFT_W / 2, (TFT_H / 2) - 20);
    tft.setTextColor(TFT_GREEN);
    tft.drawString(app.selectedSong.c_str(), TFT_W / 2, TFT_H / 2);
}

void AudioPlayer::HandleInput(bool back){
    app.currentScreen = SCREEN_SONG_BROWSER;
    app.isPlaying = false;
    dirty = true;
}


void UpdateGUI(void){
    if(dirty){

        switch(app.currentScreen){

            case SCREEN_MENU:
                ui.DrawMenu();
                break;
        
            case SCREEN_SONG_BROWSER:
                songBrowser.DrawSongs();
                break;
        
            case SCREEN_AUDIO_PLAYER:
                audioPlayer.DrawPlayer();
                break;
        }

        dirty = false;
    }
}