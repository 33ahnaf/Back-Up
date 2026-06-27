#include "GUI.h"
#include "globals.h"
#include "Arduino.h"
#include <string.h>
#include <SD.h>

#define LCD_HEIGHT 4

#define MODULE_NAME "GUI"

MenuItem settingsMenu[] = {
    { "Brightness",         NULL, 0, NULL },
    { "Themes",             NULL, 0, NULL },
    { "Scroll Wrapping",    NULL, 0, NULL }
};

MenuItem mainMenu[] = {
    { "Songs",      NULL, 0, OpenSongs },
    { "Settings",   settingsMenu, sizeof(settingsMenu)/sizeof(settingsMenu[0]), NULL },
    { "Search",     NULL, 0, NULL }
};

UIState ui = {
    .currentMenu = mainMenu,
    .itemCount = sizeof(mainMenu)/sizeof(mainMenu[0]),
    .selected = 0,
    .scroll = 0,
    .parentIndex = 0
};

SongBrowser songBrowser;


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
    lcd.clear();
    for(int i = 0; i < LCD_HEIGHT; i++){
        int idx = i + scroll;
        if(idx >= itemCount) break;

        if(idx == selected){
            lcd.setCursor(0, i);
            lcd.printf(">%s", currentMenu[idx].name);
        }else{
            lcd.setCursor(1, i);
            lcd.printf("%s", currentMenu[idx].name);
        }
    }
}

void UIState::HandleInput(bool up, bool down, bool enter, bool back){
    
    if(down){
        selected++;
        if(selected >= itemCount)
            selected = itemCount - 1;
    }else if(up){
        selected--;
        if(selected < 0)
            selected = 0;
    }

    if(selected >= scroll + LCD_HEIGHT)
        scroll = selected - LCD_HEIGHT + 1;

    if(selected < scroll)
        scroll = selected;

    if(enter)
        Enter();
    else if(back)
        Back();
}

void OpenSongs(void){
    songBrowser.LoadSongs(MUSICS_DIRECTORY);
    app.currentScreen = SCREEN_SONG_BROWSER;
}

void SongBrowser::LoadSongs(const std::string path){
    songs.clear();

    File muDirec = SD.open(path.c_str());
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
        if(selected >= (int)songs.size())
            selected = songs.size() - 1;
    }

    if(up){
        selected--;
        if(selected < 0)
            selected = 0;
    }

    if(selected >= scroll + LCD_HEIGHT)
        scroll = selected - LCD_HEIGHT + 1;
    
    if(selected < scroll)
        scroll = selected;
    
    if(enter){
        app.selectedSong = songs[selected];
        app.currentScreen = SCREEN_AUDIO_PLAYER;
        app.isPlaying = true;
    }

    if(back){
        app.currentScreen = SCREEN_MENU;
    }
}

void SongBrowser::DrawSongs(void){
    lcd.clear();
    for(int i = 0; i < LCD_HEIGHT; i++){
        int idx = i + scroll;
        if(idx >= (int)songs.size()) break;

        if(idx == selected){
            lcd.setCursor(0, i);
            lcd.printf(">%s", songs[idx].c_str());
        }else{
            lcd.setCursor(1, i);
            lcd.printf("%s", songs[idx].c_str());
        }
    }
}


void UpdateGUI(void){
    switch(app.currentScreen){
        case SCREEN_MENU:
            // ui.HandleInput();  not used/deprecated
            ui.DrawMenu();
            break;
        case SCREEN_SONG_BROWSER:
            // songBrowser.HandleInput();  not used/deprecated
            songBrowser.DrawSongs();
            break;
        case SCREEN_AUDIO_PLAYER:
            // not used/deprecated
            // if(c == ']'){
            //     app.currentScreen = SCREEN_SONG_BROWSER;
            //     app.isPlaying = false;
            // }
            lcd.clear();
            lcd.setCursor(5, 1);
            lcd.print("NOW PLAYING");
            lcd.setCursor(0, 2);
            lcd.print(app.selectedSong.c_str());
            break;
    }
}