
#ifndef game_header
#define game_header

void DrawGrid(void);

void DrawPlayedGrid(void);

void DrawScore(void);

unsigned int current_player = 0;


unsigned char GAME_GRID[3][3] = {
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}};

unsigned char SCORE[2] = {'0', '0'};

#endif
