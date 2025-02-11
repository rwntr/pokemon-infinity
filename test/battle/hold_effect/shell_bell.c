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
        HP_BAR(player, .captureHP = &hp);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, opponent);
    }
    THEN {
        //Max HP - init HP == 100-1 == 99, /3 = 33, init hp + 33 = 34.
        EXPECT_EQ(hp, 34);
    }
}

SINGLE_BATTLE_TEST("Shell Bell doesn't restore HP for damage dealt by a foreseen move")
{
    GIVEN {
        ASSUME(gMovesInfo[MOVE_FUTURE_SIGHT].effect == EFFECT_FUTURE_SIGHT);
        PLAYER(SPECIES_WOBBUFFET) { Level(16); Item(ITEM_SHELL_BELL); HP(10); }
        OPPONENT(SPECIES_WOBBUFFET) { Level(16); };
    } WHEN {
        TURN { MOVE(player, MOVE_FUTURE_SIGHT); }
        TURN { }
        TURN { }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_FUTURE_SIGHT, player);
        MESSAGE("The opposing Wobbuffet took the Future Sight attack!");
        HP_BAR(opponent);
        NONE_OF {
            HP_BAR(player);
        }
    }
}

SINGLE_BATTLE_TEST("Shell Bell does not activate on Future Sight if the original user is on the field")
{
    s16 damage = 0;
    s16 healed = 0;

    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { HP(1); Item(ITEM_SHELL_BELL); }
        OPPONENT(SPECIES_WYNAUT);
    } WHEN {
        TURN { MOVE(player, MOVE_FUTURE_SIGHT); }
        TURN {}
        TURN {}
        TURN { MOVE(player, MOVE_DRAGON_RAGE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_FUTURE_SIGHT, player);
        MESSAGE("The opposing Wynaut took the Future Sight attack!");
        HP_BAR(opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_DRAGON_RAGE, player);
        HP_BAR(opponent, captureDamage: &damage);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_HELD_ITEM_EFFECT, player);
        HP_BAR(player, captureDamage: &healed);
    } THEN {
        EXPECT_MUL_EQ(damage, Q_4_12(-0.25), healed);
    }
}
