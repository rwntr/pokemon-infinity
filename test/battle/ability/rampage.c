#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Rampage skips recharge turn if a Pokemon was KO'd on the last turn")
{
    u32 ability = 0;
    PARAMETRIZE { ability = ABILITY_BLAZE; }
    PARAMETRIZE { ability = ABILITY_RAMPAGE; }
    GIVEN {
        ASSUME(MoveHasAdditionalEffectSelf(MOVE_HYPER_BEAM, MOVE_EFFECT_RECHARGE) == TRUE);
        PLAYER(SPECIES_TYPHLOSION) { Ability(ability); Speed(100); }
        OPPONENT(SPECIES_GLALIE) { HP(1); Speed(1);}
        OPPONENT(SPECIES_BLISSEY) { HP(10); SpDefense(1); Speed(1); Ability(ABILITY_STURDY);}
    } WHEN {
        TURN { MOVE(player, MOVE_HYPER_BEAM); SEND_OUT(opponent, 1);  }
        TURN { MOVE(player, MOVE_HYPER_BEAM); MOVE(opponent, MOVE_ENDURE); }
        TURN { MOVE(player, MOVE_HYPER_BEAM); MOVE(opponent, MOVE_CELEBRATE); }
    } SCENE {
        MESSAGE("Typhlosion used Hyper Beam!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_HYPER_BEAM, player);
        MESSAGE("Foe Glalie fainted!");
        MESSAGE("Typhlosion used Hyper Beam!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_HYPER_BEAM, player);
        }
}

SINGLE_BATTLE_TEST("Rampage does not remove recharge turns if foe isn't KO'd")
{
    u16 move;
    PARAMETRIZE { move = MOVE_HYPER_BEAM; }

    GIVEN {
        ASSUME(MoveHasAdditionalEffectSelf(MOVE_HYPER_BEAM, MOVE_EFFECT_RECHARGE) == TRUE);
        PLAYER(SPECIES_TYPHLOSION) { Ability(ABILITY_RAMPAGE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, move); }
        if (move == MOVE_HYPER_BEAM) {
            TURN { SKIP_TURN(player); } //will do no damage, therefore not KO
        }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, move, player);
        HP_BAR(opponent);
        MESSAGE("Typhlosion must recharge!");
    }
}
