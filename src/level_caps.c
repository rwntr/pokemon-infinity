#include "global.h"
#include "battle.h"
#include "event_data.h"
#include "level_caps.h"
#include "strings.h"
#include "pokemon.h"

const u32 sLevelCapsFlagMap[][4] =
        {
                {FLAG_BADGE01_GET, 16,  16, 14},
                {FLAG_BADGE02_GET, 25,  25, 20},
                {FLAG_BADGE03_GET, 38,  38, 30},
                {FLAG_BADGE04_GET, 50,  50, 40},
                {FLAG_BADGE05_GET, 101, 54, 45},
                {FLAG_BADGE06_GET, 101, 70, 55},
                {FLAG_BADGE07_GET, 101, 85, 60},
                {FLAG_BADGE08_GET, 101, 92, 70},
                {FLAG_IS_CHAMPION, 101,  95, 80},
        };

u16 GetActiveDifficultySetting()
{
    return gSaveBlock2Ptr->gameDifficulty;
}

void SetActiveDifficultySetting(u16 diffArg)
{
    gSaveBlock2Ptr->gameDifficulty = diffArg;
}

u16 GetActiveLevelCapType()
{
    return gSaveBlock2Ptr->gameDifficulty;
}

void SetActiveLevelCapType(u16 capArg)
{
    gSaveBlock2Ptr->levelCaps = capArg;
}

u16 GetActiveLevelCapIndex()
{
    u32 index;

    for (index = 0; index < ARRAY_COUNT(sLevelCapsFlagMap); index++)
    {
        if (!FlagGet(sLevelCapsFlagMap[index][0])) {
            return index;
        }
    }
    //If you've beaten the champion
    return MAX_LEVEL;
}


u32 GetActiveLevelCap()
{
    u32 capFlag;
    u32 capType;
    capFlag = GetActiveLevelCapIndex();
    capType = GetActiveLevelCapType();

     if (capFlag == MAX_LEVEL)
         return MAX_LEVEL;

     switch (capType) {
        case LEVEL_CAPS_DEFAULT:
            return sLevelCapsFlagMap[capFlag][1];
        case LEVEL_CAPS_MORE:
            return sLevelCapsFlagMap[capFlag][2];
        case LEVEL_CAPS_STRICT:
            return sLevelCapsFlagMap[capFlag][3];
        case LEVEL_CAPS_OFF:
        default:
            return MAX_LEVEL;
     }

    //If you somehow miraculously break this, just return no level caps.
    return MAX_LEVEL;
}

//This function exists for more intelligent dynamic trainer mon level distribution
u32 GetLastLevelCap(u16 currCapIdx)
{
    u32 capType;
    capType = GetActiveLevelCapType();

    //If you haven't beaten Roxanne, return level you get your starter at
    if (currCapIdx <= 0)
    {
        return 5;
    }

    //Otherwise-unhandled logical error, maybe possible
    //to encounter if you skip Winona then beat T&L.
    //Just uses your current cap for lastCap calculations
    if (!FlagGet(sLevelCapsFlagMap[currCapIdx-1][0]))
        return GetActiveLevelCap();

    return sLevelCapsFlagMap[currCapIdx-1][capType];

}

u32 GetSoftLevelCapExpValue(u32 level, u32 expValue)
{
    static const u32 sExpScalingDown[5] = { 4, 8, 16, 32, 64 };
    static const u32 sExpScalingUp[5]   = { 16, 8, 4, 2, 1 };

    u32 levelDifference;
    u32 currentLevelCap = GetActiveLevelCap();

    if (level < currentLevelCap)
    {
        if (B_LEVEL_CAP_EXP_UP) //should always be true with default settings but just in case
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
