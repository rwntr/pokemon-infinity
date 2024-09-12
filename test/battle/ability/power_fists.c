#include "global.h"
#include "test/battle.h"


SINGLE_BATTLE_TEST("Power Fists causes 20% increased punching move damage", s16 damage)
{
    u16 ability;
    PARAMETRIZE { ability = ABILITY_ANTICIPATION; }
    PARAMETRIZE { ability = ABILITY_POWER_FISTS; }
    ASSUME(gMovesInfo[MOVE_ICE_PUNCH].type == TYPE_ICE);
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ability);}
        OPPONENT(SPECIES_WOBBUFFET) {Defense(50); SpDefense(50);}
    } WHEN {
        TURN { MOVE(opponent, MOVE_SPLASH); MOVE(player, MOVE_ICE_PUNCH); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.2), results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Power Fists calculates damage based on opponent SpDef", s16 damage)
{
    u16 ability;
    PARAMETRIZE { ability = ABILITY_ANTICIPATION; }
    PARAMETRIZE { ability = ABILITY_POWER_FISTS; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ability);}
        OPPONENT(SPECIES_WOBBUFFET) {Defense(50); SpDefense(25);}
    } WHEN {
        TURN { MOVE(opponent, MOVE_SPLASH); MOVE(player, MOVE_ICE_PUNCH); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        //stacking base 1.2x damage buff with expected 2x damage due to enemy SpDef being 1/2 of enemy Def, results in 2.4x
        EXPECT_MUL_EQ(results[0].damage, Q_4_12((2*1.2)), results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Power Fists is unaffected by Ice Scales", s16 damage)
{
    u16 ability;
    PARAMETRIZE { ability = ABILITY_ANTICIPATION; }
    PARAMETRIZE { ability = ABILITY_ICE_SCALES; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_POWER_FISTS);}
        OPPONENT(SPECIES_WOBBUFFET) { Ability(ability);}
    } WHEN {
        TURN { MOVE(opponent, MOVE_SPLASH); MOVE(player, MOVE_ICE_PUNCH); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_EQ(results[0].damage, results[1].damage);
    }
}

