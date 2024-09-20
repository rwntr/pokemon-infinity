#include "global.h"
#include "test/battle.h"

ASSUMPTIONS
{
    ASSUME(gMovesInfo[MOVE_LAST_RESPECTS].effect == EFFECT_LAST_RESPECTS);
}

SINGLE_BATTLE_TEST("Last Respects power is multiplied by the amount of fainted mon in the user's side - Player", s16 damage)
{
    u32 j = 0, faintCount = 0;
    PARAMETRIZE { faintCount = 0; }
    PARAMETRIZE { faintCount = 1; }
    PARAMETRIZE { faintCount = 2; }
    GIVEN {
        // Not Wobbuffet to omit type effectiveness.  Not Golem anymore either because 135 base attack
        // puts it into a threshold where the max power base attack will do 1 singular point more damage
        // than the parameters of MUL_EQ will allow for.  this is fine and not a problem
        PLAYER(SPECIES_HITMONLEE);
        PLAYER(SPECIES_GEODUDE);
        OPPONENT(SPECIES_WOBBUFFET) { Item(ITEM_LEPPA_BERRY); Moves(MOVE_RECYCLE, MOVE_NONE, MOVE_NONE, MOVE_NONE); }
    } WHEN {
        for (j = 0; j < faintCount; j++)
        {
            TURN { MOVE(opponent, MOVE_RECYCLE); SWITCH(player, 1); }
            TURN { MOVE(opponent, MOVE_RECYCLE); MOVE(player, MOVE_MEMENTO); SEND_OUT(player, 0); }
            TURN { MOVE(opponent, MOVE_RECYCLE); USE_ITEM(player, ITEM_REVIVE, partyIndex: 1); }
        }
        TURN {
            MOVE(opponent, MOVE_RECYCLE);
            MOVE(player, MOVE_LAST_RESPECTS);
        }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_LAST_RESPECTS, player);
        HP_BAR(opponent, captureDamage: &results[j].damage);
    } THEN {
        if (faintCount > 0)
            EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.0 + faintCount), results[faintCount].damage);
    }
}

SINGLE_BATTLE_TEST("Last Respects power is multiplied by the amount of fainted mon in the user's side - Opponent", s16 damage)
{
    u32 j = 0, faintCount = 0;
    PARAMETRIZE { faintCount = 0; }
    PARAMETRIZE { faintCount = 1; }
    PARAMETRIZE { faintCount = 2; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Item(ITEM_LEPPA_BERRY); Moves(MOVE_RECYCLE, MOVE_NONE, MOVE_NONE, MOVE_NONE); }
        // Not Wobbuffet to omit type effectiveness.  Not Golem anymore either because 135 base attack
        // puts it into a threshold where the max power base attack will do 1 singular point more damage
        // than the parameters of MUL_EQ will allow for.  this is fine and not a problem
        OPPONENT(SPECIES_HITMONLEE);
        OPPONENT(SPECIES_GEODUDE);
    } WHEN {
        for (j = 0; j < faintCount; j++)
        {
            TURN { MOVE(player, MOVE_RECYCLE); SWITCH(opponent, 1); }
            TURN { MOVE(player, MOVE_RECYCLE); MOVE(opponent, MOVE_MEMENTO); SEND_OUT(opponent, 0); }
            TURN { MOVE(player, MOVE_RECYCLE); USE_ITEM(opponent, ITEM_REVIVE, partyIndex: 1); }
        }
        TURN {
            MOVE(player, MOVE_RECYCLE);
            MOVE(opponent, MOVE_LAST_RESPECTS);
        }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_LAST_RESPECTS, opponent);
        HP_BAR(player, captureDamage: &results[j].damage);
    } THEN {
        if (faintCount > 0)
            EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.0 + faintCount), results[faintCount].damage);
    }
}
