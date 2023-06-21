#include <TFT_eSPI.h>

typedef struct
{
    char *RFIDUID;
    int songId;
    char *text;
    unsigned short color;
} RfidCard;

const RfidCard cards[20]{
    {(char *)" 76 03 23 D0", 1, (char *)"CUP OF WATER", TFT_RED},
    {(char *)" D3 82 23 D0", 2, (char *)"BOTTLE OF WATER", TFT_RED},
    {(char *)" 7D 86 23 D0", 3, (char *)"BOTTLE OF JUICE", TFT_RED},
    {(char *)" E1 97 22 D0", 4, (char *)"PLASTIC", TFT_RED},
    {(char *)" 37 D2 22 D0", 5, (char *)"APPLE", TFT_BROWN},
    {(char *)" 72 B9 23 D0", 6, (char *)"BANANA", TFT_BROWN},
    {(char *)" BA 32 2F 14", 7, (char *)"FOOD", TFT_BROWN},
    {(char *)" F5 CB 23 D0", 8, (char *)"ORANGE", TFT_BROWN},
    {(char *)" 3D 38 23 D0", 9, (char *)"CAN OF BEER", TFT_YELLOW},
    {(char *)" FA 88 22 D0", 10, (char *)"CAN OF SODA", TFT_YELLOW},
    {(char *)" 2A E5 6D CA", 11, (char *)"CAN OF JUICE", TFT_YELLOW},
    {(char *)" CE 20 23 D0", 12, (char *)"PICTURE FRAME", TFT_YELLOW},
    {(char *)" 79 7B 23 D0", 13, (char *)"GLASS", TFT_GREEN},
    {(char *)" 79 9F 22 D0", 14, (char *)"...", TFT_GREEN},
    {(char *)" 05 CD 23 D0", 15, (char *)"...", TFT_GREEN},
    {(char *)" EB 6F 23 D0", 16, (char *)"...", TFT_GREEN},
    {(char *)" 8C 8F 22 D0", 17, (char *)"...", TFT_BLUE},
    {(char *)" A2 30 23 D0", 18, (char *)"...", TFT_BLUE},
    {(char *)" AD F9 22 D0", 19, (char *)"...", TFT_BLUE},
    {(char *)" BA A0 EA 14", 20, (char *)"...", TFT_BLUE},
};
