#ifndef GUARD_LEVEL_CAP_H
#define GUARD_LEVEL_CAP_H

/*#if B_EXP_CAP_TYPE != EXP_CAP_NONE && B_EXP_CAP_TYPE != EXP_CAP_HARD && B_EXP_CAP_TYPE != EXP_CAP_SOFT
#error "Invalid choice for B_EXP_CAP_TYPE, must be of [EXP_CAP_NONE, EXP_CAP_HARD, EXP_CAP_SOFT]"
#endif

#if B_EXP_CAP_TYPE == EXP_CAP_HARD || B_EXP_CAP_TYPE == EXP_CAP_SOFT
#if B_LEVEL_CAP_TYPE != LEVEL_CAP_FLAG_LIST && B_LEVEL_CAP_TYPE != LEVEL_CAP_VARIABLE
#error "Invalid choice for B_LEVEL_CAP_TYPE, must be of [LEVEL_CAP_FLAG_LIST, LEVEL_CAP_VARIABLE]"
#endif
#if B_LEVEL_CAP_TYPE == LEVEL_CAP_VARIABLE && B_LEVEL_CAP_VARIABLE == 0
#error "B_LEVEL_CAP_TYPE set to LEVEL_CAP_VARIABLE, but no variable chosen for B_LEVEL_CAP_VARIABLE, set B_LEVEL_CAP_VARIABLE to a valid event variable"
#endif
#endif*/

#define B_NUM_CAP_FLAGS 9
#define B_NUM_CAP_SETTINGS 3

extern const u32 sLevelCapsFlagMap[][4];
u16 GetActiveDifficultySetting(void);
void SetActiveDifficultySetting(u16 diffArg);
u16 GetActiveLevelCapType(void);
void SetActiveLevelCapType(u16 capArg);
u16 GetActiveLevelCapIndex(void);
u32 GetActiveLevelCap(void);
u32 GetLastLevelCap(u16 currCapIdx);
u32 GetSoftLevelCapExpValue(u32 level, u32 expValue);

#endif /* GUARD_LEVEL_CAP_H */
