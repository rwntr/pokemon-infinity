#include "global.h"
#include "test/battle.h"

ASSUMPTIONS
{
    ASSUME(B_PROTEAN_LIBERO == GEN_8);
}

SINGLE_BATTLE_TEST("Protean changes the type of the user every time they use a move")
{
    GIVEN {
        PLAYER(SPECIES_REGIROCK);
        OPPONENT(SPECIES_KECLEON) { Ability(ABILITY_PROTEAN); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_WATER_GUN); }
        TURN { MOVE(opponent, MOVE_SCRATCH); }
    } SCENE {
        ABILITY_POPUP(opponent, ABILITY_PROTEAN);
        MESSAGE("The opposing Kecleon transformed into the Water type!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_WATER_GUN, opponent);
        ABILITY_POPUP(opponent, ABILITY_PROTEAN);
        MESSAGE("The opposing Kecleon transformed into the Normal type!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, opponent);;
    }
}
