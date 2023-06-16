#include "DFRobotDFPlayerMini.h"

void printDFPDetail(int type, int value)
{
    switch (type)
    {
    case TimeOut:
        Serial.println(F("Time Out!"));
        break;
    case WrongStack:
        Serial.println(F("Stack Wrong!"));
        break;
    case DFPlayerCardInserted:
        Serial.println(F("Card Inserted!"));
        break;
    case DFPlayerCardRemoved:
        Serial.println(F("Card Removed!"));
        break;
    case DFPlayerCardOnline:
        Serial.println(F("Card Online!"));
        break;
    case DFPlayerPlayFinished:
        Serial.print(F("Number:"));
        Serial.print(value);
        Serial.println(F(" Play Finished!"));
        break;
    case DFPlayerError:
        Serial.print(F("DFPlayerError:"));
        switch (value)
        {
        case Busy:
            Serial.println(F("Card not found"));
            break;
        case Sleeping:
            Serial.println(F("Sleeping"));
            break;
        case SerialWrongStack:
            Serial.println(F("Get Wrong Stack"));
            break;
        case CheckSumNotMatch:
            Serial.println(F("Check Sum Not Match"));
            break;
        case FileIndexOut:
            Serial.println(F("File Index Out of Bound"));
            break;
        case FileMismatch:
            Serial.println(F("Cannot Find File"));
            break;
        case Advertise:
            Serial.println(F("In Advertise"));
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}

ColorDictionary getColor(char *name)
{
    for (int i = 0; i < (sizeof(colors) / sizeof(colors[0])); i++)
    {
        if (strcmp(name, colors[i].name) == 0)
        {
            return colors[i];
        }
    }

    return {(char *)"", -1};
}

RfidCardDictionary getCard(char *UID)
{
    for (int i = 0; i < (sizeof(cards) / sizeof(cards[0])); i++)
    {
        if (strcmp(UID, cards[i].RFIDUID) == 0)
        {
            return cards[i];
        }
    }

    return {(char *)"", -1, (char *)"", (char *)""};
}