typedef struct
{
    char *RFIDUID;
    int songId;
    char *text;
    char *color;
} RfidCardDictionary; 

const RfidCardDictionary cards[20]{
    {(char *)" 76 03 23 D0", 1, (char *)"CUP OF WATER", (char *)"RED"},
    {(char *)" D3 82 23 D0", 2, (char *)"BOTTLE OF WATER", (char *)"RED"},
    {(char *)" 7D 86 23 D0", 3, (char *)"BOTTLE OF JUICE", (char *)"RED"},
    {(char *)" E1 97 22 D0", 4, (char *)"PLASTIC", (char *)"RED"},
    {(char *)" 37 D2 22 D0", 5, (char *)"APPLE", (char *)"ORGANIC"},
    {(char *)" 72 B9 23 D0", 6, (char *)"BANANA", (char *)"ORGANIC"},
    {(char *)" BA 32 2F 14", 7, (char *)"FOOD", (char *)"ORGANIC"},
    {(char *)" F5 CB 23 D0", 8, (char *)"ORANGE", (char *)"ORGANIC"},
    {(char *)" 3D 38 23 D0", 9, (char *)"CAN OF BEER", (char *)"YELLOW"},
    {(char *)" FA 88 22 D0", 10, (char *)"CAN OF SODA", (char *)"YELLOW"},
    {(char *)" 2A E5 6D CA", 11, (char *)"CAN OF JUICE", (char *)"YELLOW"},
    {(char *)" CE 20 23 D0", 12, (char *)"PICTURE FRAME", (char *)"YELLOW"},
    {(char *)" 79 7B 23 D0", 13, (char *)"GLASS", (char *)"GREEN"},
    {(char *)" 79 9F 22 D0", 14, (char *)"... ", (char *)"GREEN"},
    {(char *)" 05 CD 23 D0", 15, (char *)"...", (char *)"GREEN"},
    {(char *)" EB 6F 23 D0", 16, (char *)"...", (char *)"GREEN"},
    {(char *)" 8C 8F 22 D0", 17, (char *)"...", (char *)"BLUE"},
    {(char *)" A2 30 23 D0", 18, (char *)"...", (char *)"BLUE"},
    {(char *)" AD F9 22 D0", 19, (char *)"...", (char *)"BLUE"},
    {(char *)" BA A0 EA 14", 20, (char *)"...", (char *)"BLUE"},
};
