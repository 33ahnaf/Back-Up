#ifndef _GUI__H
#define _GUI__H

#include <string>
#include <vector>
#include <raylib.h>

#define LCD_WIDTH 320
#define LCD_HEIGHT 240
#define LCD_TARGET_FPS 20
#define VISIBLE_ITEMS 12
#define MAX_VISIBLE_ITEM_LENGTH 50

typedef struct MenuItem {
    const char *name;

    struct MenuItem *children;
    int childCount;

    void (*action)();
} MenuItem;

typedef struct {
    MenuItem *menu;
    int count;
    int selected;
    int scroll;
} MenuState;

typedef struct {
    MenuItem *currentMenu;
    int itemCount;

    int selected;
    int scroll;

    MenuState parentStack[10];
    int parentIndex;

    void Enter(void);
    void Back(void);
    void HandleInput(void);
    void DrawMenu(void);
} UIState;

typedef struct {
    std::vector<std::string> songs;
    
    int selected = 0;
    int scroll = 0;

    void LoadSongs(const std::string path);
    void HandleInput(void);
    void DrawSongs(void);
} SongBrowser;

void GRAPHICS_INIT(void);
void GRAPHICS_END(void);
void UpdateGUI(void);
void OpenSongs(void);

#endif