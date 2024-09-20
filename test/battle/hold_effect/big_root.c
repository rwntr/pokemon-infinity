#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Big Root now causes absorb effect moves to recover 50% extra HP instead of 30%", s16 hp)
{
    u16 item;
    PARAMETRIZE { item = ITEM_BIG_ROOT; }
    PARAMETRIZE { item = ITEM_SILK_SCARF; }
    GIVEN {
        PLAYER(SPECIES_VICTREEBEL) { Item(item); SpAttack(999); HP(1);};
        OPPONENT(SPECIES_WOBBUFFET) { HP(101); SpDefense(1); Item(ITEM_FOCUS_SASH); };
    } WHEN {
        TURN { MOVE(player, MOVE_GIGA_DRAIN); MOVE(opponent, MOVE_SPLASH); }

    } SCENE {
        MESSAGE("Victreebel used Giga Drain!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_GIGA_DRAIN, player);
        HP_BAR(player, captureDamage: &results[i].hp);
        MESSAGE("Foe Wobbuffet had its energy drained!");
    } FINALLY {
        EXPECT_MUL_EQ(results[1].hp, UQ_4_12(1.5), results[0].hp);
    }
}