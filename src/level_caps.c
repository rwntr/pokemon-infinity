#include "global.h"
#include "battle.h"
#include "event_data.h"
#include "level_caps.h"
#include "strings.h"
#include "pokemon.h"



u32 GetCurrentLevelCap(u16 levelCapSetting)
{

    u8 currentLevelCap;
    u32 i;
    static const u32 sDefaultCapsFlagMap[][2] =
    {
        {FLAG_BADGE01_GET, 16},
        {FLAG_BADGE02_GET, 25},
        {FLAG_BADGE03_GET, 38},
        {FLAG_BADGE04_GET, 50},
        {FLAG_BADGE05_GET, 101},
        {FLAG_BADGE06_GET, 101},
        {FLAG_BADGE07_GET, 101},
        {FLAG_BADGE08_GET, 101},
        {FLAG_IS_CHAMPION, 101},
    };

     static const u32 sMoreCapsFlagMap[][2] =
    {
        {FLAG_BADGE01_GET, 16},
        {FLAG_BADGE02_GET, 25},
        {FLAG_BADGE03_GET, 38},
        {FLAG_BADGE04_GET, 50},
        {FLAG_BADGE05_GET, 54},
        {FLAG_BADGE06_GET, 70},
        {FLAG_BADGE07_GET, 85},
        {FLAG_BADGE08_GET, 92},
        {FLAG_IS_CHAMPION, 95},
    };

     static const u32 sStrictCapsFlagMap[][2] =
    {
        {FLAG_BADGE01_GET, 14},
        {FLAG_BADGE02_GET, 20},
        {FLAG_BADGE03_GET, 30},
        {FLAG_BADGE04_GET, 40},
        {FLAG_BADGE05_GET, 45},
        {FLAG_BADGE06_GET, 55},
        {FLAG_BADGE07_GET, 60},
        {FLAG_BADGE08_GET, 70},
        {FLAG_IS_CHAMPION, 80},
    };

    for (i = 0; i < ARRAY_COUNT(sDefaultCapsFlagMap); i++)
    {
        if (!FlagGet(sDefaultCapsFlagMap[i][0])) {
            break;
        }
    }

     switch (levelCapSetting) {
        case LEVEL_CAPS_DEFAULT:
            currentLevelCap = sDefaultCapsFlagMap[i][1];
            break;
        case LEVEL_CAPS_MORE:
            currentLevelCap = sMoreCapsFlagMap[i][1];
            break;
        case LEVEL_CAPS_STRICT:
            currentLevelCap = sStrictCapsFlagMap[i][1];
            break;
        case LEVEL_CAPS_OFF:
        default:
            currentLevelCap = MAX_LEVEL;
            break;
            }
    return currentLevelCap;
}

u32 GetSoftLevelCapExpValue(u32 level, u32 expValue)
{
    static const u32 sExpScalingDown[5] = { 4, 8, 16, 32, 64 };
    static const u32 sExpScalingUp[5]   = { 16, 8, 4, 2, 1 };

    u32 levelDifference;
    u32 currentLevelCap = GetCurrentLevelCap(gSaveBlock2Ptr->levelCaps);

    if (level < currentLevelCap)
    {
        if (B_LEVEL_CAP_EXP_UP) //should always be true with default settings
        {
            levelDifference = currentLevelCap - level;
            if (levelDifference > ARRAY_COUNT(sExpScalingUp))
                return expValue + (expValue / sExpScalingUp[ARRAY_COUNT(sExpScalingUp) - 1]);
            else
                return expValue + (expValue / sExpScalingUp[levelDifference]);

            //simplified this because I was getting annoyed by the "potential out of bounds" warnings lol
        }
        else
        {
            return expValue;
        }
    }
    else if (B_EXP_CAP_TYPE == EXP_CAP_HARD)
    {
        return 0;
    }
    else if (B_EXP_CAP_TYPE == EXP_CAP_SOFT)
    {
        levelDifference = level - currentLevelCap;
        if (levelDifference > ARRAY_COUNT(sExpScalingDown))
            return expValue / sExpScalingDown[ARRAY_COUNT(sExpScalingDown) - 1];
        else
            return expValue / sExpScalingDown[levelDifference];
    }
    else
    {
        return expValue;
    }
    return 0; //default to be safe
}
