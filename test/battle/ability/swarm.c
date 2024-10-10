#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Swarm boosts Bug-type moves in a pinch", s16 damage)
{
    u16 hp;
    u16 ability;
    PARAMETRIZE { ability = ABILITY_SHIELD_DUST; hp = 99; }
    PARAMETRIZE { ability = ABILITY_SWARM; hp = 33; }
    GIVEN {
        ASSUME(gMovesInfo[MOVE_BUG_BITE].type == TYPE_BUG);
        ASSUME(gMovesInfo[MOVE_BUG_BITE].power == 60);
        ASSUME(gMovesInfo[MOVE_BUG_BITE].category == DAMAGE_CATEGORY_PHYSICAL);
        ASSUME(gSpeciesInfo[SPECIES_LEDYBA].types[0] == TYPE_BUG);
        ASSUME(gSpeciesInfo[SPECIES_WOBBUFFET].types[0] == TYPE_PSYCHIC);
        ASSUME(gSpeciesInfo[SPECIES_WOBBUFFET].types[1] == TYPE_PSYCHIC);
        PLAYER(SPECIES_LEDYBA) { Ability(ability); MaxHP(99); HP(hp); Attack(45); }
        OPPONENT(SPECIES_WOBBUFFET) { Defense(121); }
    } WHEN {
        TURN { MOVE(player, MOVE_BUG_BITE); }
    } SCENE {
        HP_BAR(opponent, .captureDamage =  &results[i].damage);
    } FINALLY {
        // Due to numerics related to rounding on each applied multiplier,
        // the 50% move power increase doesn't manifest as a 50% damage increase, but as a 44% damage increase in this case.
        // Values obtained from https://calc.pokemonshowdown.com (Neutral nature and 0 IVs on both sides)
        EXPECT_EQ(results[0].damage, 50);
        EXPECT_EQ(results[1].damage, 72);
    }
}

SINGLE_BATTLE_TEST("Swarm boosts Bug-type moves outside of pinch", s16 damage)
{
    u16 hp;
    u16 ability;
    PARAMETRIZE { ability = ABILITY_SHIELD_DUST; hp = 99; }
    PARAMETRIZE { ability = ABILITY_SWARM; hp = 99; }
    GIVEN {
        ASSUME(gMovesInfo[MOVE_BUG_BITE].type == TYPE_BUG);
        ASSUME(gMovesInfo[MOVE_BUG_BITE].power == 60);
        ASSUME(gMovesInfo[MOVE_BUG_BITE].category == DAMAGE_CATEGORY_PHYSICAL);
        ASSUME(gSpeciesInfo[SPECIES_LEDYBA].types[0] == TYPE_BUG);
        ASSUME(gSpeciesInfo[SPECIES_WOBBUFFET].types[0] == TYPE_PSYCHIC);
        ASSUME(gSpeciesInfo[SPECIES_WOBBUFFET].types[1] == TYPE_PSYCHIC);
        PLAYER(SPECIES_LEDYBA) { Ability(ability); MaxHP(99); HP(hp); Attack(45); }
        OPPONENT(SPECIES_WOBBUFFET) { Defense(121); }
    } WHEN {
        TURN { MOVE(player, MOVE_BUG_BITE); }
    } SCENE {
        HP_BAR(opponent, .captureDamage =  &results[i].damage);
    } FINALLY {
    // Due to numerics related to rounding on each applied multiplier,
    // the 50% move power increase doesn't manifest as a 50% damage increase, but as a 44% damage increase in this case.
    // Values obtained from https://calc.pokemonshowdown.com (Neutral nature and 0 IVs on both sides)
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.2), results[1].damage);
    }
}
