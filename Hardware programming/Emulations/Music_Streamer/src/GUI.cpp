#include "GUI.h"
#include "globals.h"
#include <stdio.h>
#include <raylib.h>
#include <dirent.h>
#include <string.h>

char visible[VISIBLE_ITEMS][MAX_VISIBLE_ITEM_LENGTH];
Font font;

MenuItem settingsMenu[] = {
    { "Brightness", NULL, 0, NULL },
    { "Themes", NULL, 0, NULL },
    { "Scroll Wrapping", NULL, 0, NULL }
};

MenuItem mainMenu[] = {
    { "Songs", NULL, 0, OpenSongs },
    { "Settings", settingsMenu, sizeof(settingsMenu)/sizeof(settingsMenu[0]), NULL },
    { "Search", NULL, 0, NULL }
};

UIState ui = {
    .currentMenu = mainMenu,
    .itemCount = sizeof(mainMenu)/sizeof(mainMenu[0]),
    .selected = 0,
    .scroll = 0,
    .parentIndex = 0
};

SongBrowser songBrowser;

void GRAPHICS_INIT(void){
    InitWindow(LCD_WIDTH, LCD_HEIGHT, "TFT Display (emulation)");
    SetTargetFPS(LCD_TARGET_FPS);
    SetTextureFilter(font.texture, TEXTURE_FILTER_POINT);
    SetTextureFilter(font.texture, TEXTURE_FILTER_BILINEAR);
    font = LoadFontEx("./assets/Fonts/NotoSans-Medium.ttf", 16, 0, 0);
}

void GRAPHICS_END(void){
    UnloadFont(font);
    CloseWindow();
}

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
    BeginDrawing();
    ClearBackground(BLACK);

    for(int i = 0; i < VISIBLE_ITEMS; i++){
        int idx = i + scroll;
        if(idx >= itemCount) break;
        
        int y = i * 20;

        if(idx == selected){
            DrawRectangle(0, y - 2, LCD_WIDTH, 20, DARKGRAY);
            DrawTextEx(font, ">", (Vector2){2, y}, 16, 1, YELLOW);
            DrawTextEx(font, currentMenu[idx].name, (Vector2){11, y}, 16, 0.5, YELLOW);
        }else{
            DrawTextEx(font, currentMenu[idx].name, (Vector2){11, y}, 16, 0.5, GREEN);
        }
    }

    EndDrawing();
}

void UIState::HandleInput(void){
    if(IsKeyPressed(KEY_DOWN)){
        selected++;
        if(selected >= itemCount)
            selected = itemCount - 1;
    }else if(IsKeyPressed(KEY_UP)){
        selected--;
        if(selected < 0)
            selected = 0;
    }

    if(selected >= scroll + VISIBLE_ITEMS)
        scroll = selected - VISIBLE_ITEMS + 1;

    if(selected < scroll)
        scroll = selected;

    if(IsKeyPressed(KEY_ENTER))
        Enter();
    else if(IsKeyPressed(KEY_BACKSPACE))
        Back();
}

void OpenSongs(void){
    songBrowser.LoadSongs("./assets/Musics");
    app.currentScreen = SCREEN_SONG_BROWSER;
}

void SongBrowser::LoadSongs(const std::string path){
    songs.clear();

    struct dirent *entry;
    DIR *dir = opendir(path.c_str());
    if(dir == NULL){
        printf("Could not open directory!");
        while(1);
    }

    while((entry = readdir(dir))){
        if(!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
            continue;
        songs.push_back(entry->d_name);
    }
    selected = 0;
    scroll = 0;
}

void SongBrowser::HandleInput(void){
    if(IsKeyPressed(KEY_DOWN)){
        selected++;
        if(selected >= songs.size())
            selected = songs.size() - 1;
    }

    if(IsKeyPressed(KEY_UP)){
        selected--;
        if(selected < 0)
            selected = 0;
    }

    if(selected >= scroll + VISIBLE_ITEMS)
        scroll = selected - VISIBLE_ITEMS + 1;
    
    if(selected < scroll)
        scroll = selected;
    
    if(IsKeyPressed(KEY_ENTER)){
        app.selectedSong = songs[selected];
        app.currentScreen = SCREEN_AUDIO_PLAYER;
        app.isPlaying = true;
    }

    if(IsKeyPressed(KEY_BACKSPACE))
        app.currentScreen = SCREEN_MENU;
}

void SongBrowser::DrawSongs(void){
    BeginDrawing();
    ClearBackground(BLACK);

    for(int i = 0; i < VISIBLE_ITEMS; i++){
        int idx = i + scroll;
        if(idx >= songs.size()) break;
        
        int y = i * 20;

        if(idx == selected){
            DrawRectangle(0, y - 2, LCD_WIDTH, 20, DARKGRAY);
            DrawTextEx(font, ">", (Vector2){2, y}, 16, 1, YELLOW);
            DrawTextEx(font, songs[idx].c_str(), (Vector2){11, y}, 16, 0.5, YELLOW);
        }else{
            DrawTextEx(font, songs[idx].c_str(), (Vector2){11, y}, 16, 0.5, GREEN);
        }
    }

    EndDrawing();
}


void UpdateGUI(void){
    switch(app.currentScreen){
        case SCREEN_MENU:
            ui.HandleInput();
            ui.DrawMenu();
            break;
        case SCREEN_SONG_BROWSER:
            songBrowser.HandleInput();
            songBrowser.DrawSongs();
            break;
        case SCREEN_AUDIO_PLAYER:
            BeginDrawing();
            ClearBackground(BLACK);
            DrawTextEx(font, "NOW PLAYING", {10, 20}, 20, 1, SKYBLUE);
            DrawTextEx(font, app.selectedSong.c_str(), {10, 60}, 16, 1, GREEN);
            if(IsKeyPressed(KEY_BACKSPACE))
                app.currentScreen = SCREEN_SONG_BROWSER;
            EndDrawing();
            break;
    }
}