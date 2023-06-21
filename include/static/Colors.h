#include <TFT_eSPI.h>

typedef struct
{
    unsigned short *shades;
    char *name;
    char *type;
} ColorShade;

const ColorShade colors[5]{
    {new unsigned short[4]{TFT_GREEN, 0x77ee, 0xaff5, 0xe7fc}, (char *)"GREEN", (char *)"GLASS"},
    {new unsigned short[4]{TFT_RED, 0xfb8e, 0xfd55, 0xff1c}, (char *)"RED", (char *)"PLASTIC"},
    {new unsigned short[4]{TFT_BROWN, 0xfc00, 0xfdae, 0xff9c}, (char *)"BROWN", (char *)"ORGANIC"},
    {new unsigned short[4]{TFT_YELLOW, 0xffee, 0xfff5, 0xfffc}, (char *)"YELLOW", (char *)"METAL"},
    {new unsigned short[4]{TFT_BLUE, 0x739f, 0xad5f, 0xe71f}, (char *)"BLUE", (char *)"PAPER"},
};
