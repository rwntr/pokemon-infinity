#include "global.h"
#include "test/battle.h"


SINGLE_BATTLE_TEST("Whiteout increases Ice move damage by 50% in hail", s16 damage)
{
    u32 move1, move2;
    PARAMETRIZE { move1 = MOVE_SPLASH; move2 = MOVE_ICE_PUNCH; }
    PARAMETRIZE { move1 = MOVE_HAIL; move2 = MOVE_ICE_PUNCH; }
    ASSUME(gMovesInfo[MOVE_ICE_PUNCH].type == TYPE_ICE);
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_WHITEOUT);}
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, move1); MOVE(player, move2); }
    } SCENE {
        HP_BAR(opponent, .captureDamage =  &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.5), results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Whiteout increases Ice move damage by 30% in snow", s16 damage)
{
    u32 move1, move2;
    PARAMETRIZE { move1 = MOVE_SPLASH; move2 = MOVE_ICE_PUNCH; }
    PARAMETRIZE { move1 = MOVE_SNOWSCAPE; move2 = MOVE_ICE_PUNCH; }
    ASSUME(gMovesInfo[MOVE_ICE_PUNCH].type == TYPE_ICE);
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_WHITEOUT);}
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, move1); MOVE(player, move2); }
    } SCENE {
        HP_BAR(opponent, .captureDamage =  &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.3), results[1].damage);
    }
}
