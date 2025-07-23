#include "global.h"
#include "test/battle.h"


SINGLE_BATTLE_TEST("Pyromancy increases secondary burn rate by 5x with fire type moves")
{
    PASSES_RANDOMLY(50, 100, RNG_SECONDARY_EFFECT); //Ember has base 10% burn rate
    GIVEN {
        ASSUME(MoveHasAdditionalEffect(MOVE_EMBER, MOVE_EFFECT_BURN) == TRUE);
        ASSUME(gMovesInfo[MOVE_EMBER].type == TYPE_FIRE);
        PLAYER(SPECIES_SCORBUNNY) { Speed(10); Ability(ABILITY_PYROMANCY); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(8); }
    } WHEN {
        TURN { MOVE(player, MOVE_EMBER); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_EMBER, player);
        MESSAGE("The opposing Wobbuffet was burned!");
    }
}