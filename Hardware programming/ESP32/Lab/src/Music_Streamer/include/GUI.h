#ifndef _GUI__H
#define _GUI__H

#include <string>
#include <vector>

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

    void Enter      (void);
    void Back       (void);
    void DrawMenu   (void);
    void HandleInput(bool up, bool down, bool enter, bool back);
} UIState;

typedef struct {
    std::vector<std::string> songs;
    
    int selected = 0;
    int scroll = 0;

    void LoadSongs  (const std::string path);
    void DrawSongs  (void);
    void HandleInput(bool up, bool down, bool enter, bool back);
} SongBrowser;

typedef struct {
    void DrawPlayer(void);
    void HandleInput(bool back);
} AudioPlayer;

void UpdateGUI(void);
void OpenSongs(void);

extern UIState ui;
extern SongBrowser songBrowser;
extern AudioPlayer audioPlayer;

#endif