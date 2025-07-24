#include "global.h"
#include "battle.h"
#include "event_data.h"
#include "caps.h"
#include "script.h"
#include "pokemon.h"
#include "difficulty.h"


u32 GetCurrentLevelCap(void)
{
    static const u32 sLevelCapFlagMap[][4] =
        {
            {FLAG_BADGE01_GET, 16,  16, 14},
            {FLAG_BADGE02_GET, 25,  25, 20},
            {FLAG_BADGE03_GET, 38,  38, 30},
            {FLAG_BADGE04_GET, 50,  50, 40},
            {FLAG_BADGE05_GET, 101, 54, 45},
            {FLAG_BADGE06_GET, 101, 70, 55},
            {FLAG_BADGE07_GET, 101, 85, 60},
            {FLAG_BADGE08_GET, 101, 92, 70},
            {FLAG_IS_CHAMPION, 101, 95, 80},
        };

    u32 i;
    u16 capType = GetCurrentIECaps();
    u16 capTypeFlagVal = 0;
    switch (capType)
    {
        case LEVEL_CAPS_DEFAULT:
            capTypeFlagVal = 1;
        break;
        case LEVEL_CAPS_MORE:
            capTypeFlagVal = 2;
        break;
        case LEVEL_CAPS_STRICT:
            capTypeFlagVal = 3;
        break;
    }
    for (i = 0; i < ARRAY_COUNT(sLevelCapFlagMap); i++)
    {
        if (!FlagGet(sLevelCapFlagMap[i][0]))
            return sLevelCapFlagMap[i][capTypeFlagVal];
    }

    return MAX_LEVEL;
}

u32 GetSoftLevelCapExpValue(u32 level, u32 expValue)
{
    static const u32 sExpScalingDown[5] = { 4, 8, 16, 32, 64 };
    static const u32 sExpScalingUp[5]   = { 16, 8, 4, 2, 1 };

    u32 levelDifference;
    u32 currentLevelCap = GetCurrentLevelCap();

    if (B_EXP_CAP_TYPE == EXP_CAP_NONE)
        return expValue;

    if (level < currentLevelCap)
    {
        if (B_LEVEL_CAP_EXP_UP)
        {
            levelDifference = currentLevelCap - level;
            if (levelDifference > ARRAY_COUNT(sExpScalingUp) - 1)
                return expValue + (expValue / sExpScalingUp[ARRAY_COUNT(sExpScalingUp) - 1]);
            else
                return expValue + (expValue / sExpScalingUp[levelDifference]);
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
        if (levelDifference > ARRAY_COUNT(sExpScalingDown) - 1)
            return expValue / sExpScalingDown[ARRAY_COUNT(sExpScalingDown) - 1];
        else
            return expValue / sExpScalingDown[levelDifference];
    }
    else
    {
       return expValue;
    }
}

u32 GetCurrentEVCap(void)
{
    static const u16 sEvCapFlagMap[][2] = {
        // Define EV caps for each milestone
        {FLAG_BADGE01_GET, MAX_TOTAL_EVS *  1 / 17},
        {FLAG_BADGE02_GET, MAX_TOTAL_EVS *  3 / 17},
        {FLAG_BADGE03_GET, MAX_TOTAL_EVS *  5 / 17},
        {FLAG_BADGE04_GET, MAX_TOTAL_EVS *  7 / 17},
        {FLAG_BADGE05_GET, MAX_TOTAL_EVS *  9 / 17},
        {FLAG_BADGE06_GET, MAX_TOTAL_EVS * 11 / 17},
        {FLAG_BADGE07_GET, MAX_TOTAL_EVS * 13 / 17},
        {FLAG_BADGE08_GET, MAX_TOTAL_EVS * 15 / 17},
        {FLAG_IS_CHAMPION, MAX_TOTAL_EVS},
    };

    if (B_EV_CAP_TYPE == EV_CAP_FLAG_LIST)
    {
        for (u32 evCap = 0; evCap < ARRAY_COUNT(sEvCapFlagMap); evCap++)
        {
            if (!FlagGet(sEvCapFlagMap[evCap][0]))
                return sEvCapFlagMap[evCap][1];
        }
    }
    else if (B_EV_CAP_TYPE == EV_CAP_VARIABLE)
    {
        return VarGet(B_EV_CAP_VARIABLE);
    }
    else if (B_EV_CAP_TYPE == EV_CAP_NO_GAIN)
    {
        return 0;
    }

    return MAX_TOTAL_EVS;
}

u16 GetCurrentIECaps(void) {
    return gSaveBlock2Ptr->levelCapTypeIE;
}

void SetCurrentIECaps(u16 capSetting) {
    gSaveBlock2Ptr->levelCapTypeIE = capSetting;
}