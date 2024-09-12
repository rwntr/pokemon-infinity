#include "global.h"
#include "test/battle.h"

ASSUMPTIONS
{
ASSUME(gMovesInfo[MOVE_SOLAR_BEAM].effect == EFFECT_SOLAR_BEAM);
}

SINGLE_BATTLE_TEST("Solar Beam fires first turn with Chloroplast with non-sun weather", s16 damage)
{
u16 move;
PARAMETRIZE { move = MOVE_CELEBRATE; }
PARAMETRIZE { move = MOVE_RAIN_DANCE; }
GIVEN {
PLAYER(SPECIES_WOBBUFFET);
OPPONENT(SPECIES_SCEPTILE_MEGA) { Ability(ABILITY_BEADS_OF_RUIN); }
} WHEN {
TURN { MOVE(player, move); }
TURN { MOVE(player, MOVE_SOLAR_BEAM); }
} SCENE {
HP_BAR(opponent, captureDamage: &results[i].damage);
} FINALLY {
EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.0), results[1].damage); // opponent is damaged immediately
}
}