#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Shell Bell restores a maximum of 1/3 of holder's missing HP")
{
    u16 hp;
    GIVEN {
        PLAYER(SPECIES_SCIZOR) { Item(ITEM_SHELL_BELL); MaxHP(100); HP(1); Attack(999); Ability(ABILITY_TECHNICIAN); }
        OPPONENT(SPECIES_WOBBUFFET) { Defense(1); HP(999); };
    } WHEN {
        TURN {MOVE(player, MOVE_FALSE_SWIPE);}
        TURN {MOVE(opponent, MOVE_CELEBRATE);}
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_FALSE_SWIPE, player);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_HELD_ITEM_EFFECT, player);
        HP_BAR(player, captureHP: &hp);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, opponent);
    }
     THEN {
        //Max HP - init HP == 100-1 == 99, /3 = 33, init hp + 33 = 34.
        EXPECT_EQ(hp, 34);
     }
}