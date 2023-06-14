typedef struct
{
    int song;
    char *RFIDUID;
    char *text;
    int color;
} RFIDDictionary;

const RFIDDictionary cards[20]{
    {1, (char *)" 76 03 23 D0", (char *)"CUP OF WATER", 0xF800},
    {2, (char *)" D3 82 23 D0", (char *)"BOTTLE OF WATER", 0xF800},
    {3, (char *)" 7D 86 23 D0", (char *)"BOTTLE OF JUICE", 0xF800},
    {4, (char *)" E1 97 22 D0", (char *)"PLASTIC", 0xF800},
    {5, (char *)" 37 D2 22 D0", (char *)"APPLE", 0x9A60},
    {6, (char *)" 72 B9 23 D0", (char *)"BANANA", 0x9A60},
    {7, (char *)" BA 32 2F 14", (char *)"FOOD", 0x9A60},
    {8, (char *)" F5 CB 23 D0", (char *)"ORANGE", 0x9A60},
    {9, (char *)" 3D 38 23 D0", (char *)"CAN OF BEER", 0xFFE0},
    {10, (char *)" FA 88 22 D0", (char *)"CAN OF SODA", 0xFFE0},
    {11, (char *)" 2A E5 6D CA", (char *)"CAN OF JUICE", 0xFFE0},
    {12, (char *)" CE 20 23 D0", (char *)"PICTURE FRAME", 0xFFE0},
    {13, (char *)" 79 7B 23 D0", (char *)"GLASS", 0x07E0},
    {14, (char *)" 79 9F 22 D0", (char *)"...", 0x07E0},
    {15, (char *)" 05 CD 23 D0", (char *)"...", 0x07E0},
    {16, (char *)" EB 6F 23 D0", (char *)"...", 0x07E0},
    {17, (char *)" 8C 8F 22 D0", (char *)"...", 0x001F},
    {18, (char *)" A2 30 23 D0", (char *)"...", 0x001F},
    {19, (char *)" AD F9 22 D0", (char *)"...", 0x001F},
    {20, (char *)" BA A0 EA 14", (char *)"...", 0x001F},
};