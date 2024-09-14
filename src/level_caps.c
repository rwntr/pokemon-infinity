#include "global.h"
#include "battle.h"
#include "event_data.h"
#include "level_caps.h"
#include "strings.h"
#include "pokemon.h"



u32 GetCurrentLevelCap(u16 levelCapSetting)
{

    u8 currentLevelCap;
    u16 currentBadge = getHighestBadge();

    static const u8 levelCapsStandard[] = {16, 25, 38, 50, 101, 101, 101, 101, 101, 101};
    static const u8 levelCapsMore[] =     {16, 25, 38, 50,  54,  70,  85,  92,  95, 101};
    static const u8 levelCapsStrict[] =   {14, 20, 30, 40,  45,  55,  60,  70,  80, 101};

    switch (levelCapSetting) {
        case LEVEL_CAPS_DEFAULT:
            currentLevelCap = levelCapsStandard[currentBadge];
            break;
        case LEVEL_CAPS_MORE:
            currentLevelCap = levelCapsMore[currentBadge];
            break;
        case LEVEL_CAPS_STRICT:
            currentLevelCap = levelCapsStrict[currentBadge];
            break;
        default:
            currentLevelCap = levelCapsStandard[currentBadge];
            break;

    }
    /*  Unused from RHH fork
    static const u32 sLevelCapFlagMap[][2] =
    {
        {FLAG_BADGE01_GET, 15},
        {FLAG_BADGE02_GET, 19},
        {FLAG_BADGE03_GET, 24},
        {FLAG_BADGE04_GET, 29},
        {FLAG_BADGE05_GET, 31},
        {FLAG_BADGE06_GET, 33},
        {FLAG_BADGE07_GET, 42},
        {FLAG_BADGE08_GET, 46},
        {FLAG_IS_CHAMPION, 58},
    };

    u32 i;

    if (B_LEVEL_CAP_TYPE == LEVEL_CAP_FLAG_LIST)
    {
        for (i = 0; i < ARRAY_COUNT(sLevelCapFlagMap); i++)
        {
            if (!FlagGet(sLevelCapFlagMap[i][0]))
                return sLevelCapFlagMap[i][1];
        }
    }
    else if (B_LEVEL_CAP_TYPE == LEVEL_CAP_VARIABLE)
    {
        return VarGet(B_LEVEL_CAP_VARIABLE);
    }

    return MAX_LEVEL;
    End unused from RHH fork*/
    return currentLevelCap;
}

u32 GetSoftLevelCapExpValue(u32 level, u32 expValue)
{
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
    else
    {
        return 0;
    }
    return 0; //default to be safe
}
