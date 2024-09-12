#include "global.h"
#include "test/battle.h"
#include "battle_ai_util.h"

SINGLE_BATTLE_TEST("Blitz Boxer grants priority at any HP")
{
    u16 hp;
    PARAMETRIZE { hp = 100; }
    PARAMETRIZE { hp = 99; }
    GIVEN {
        ASSUME(gMovesInfo[MOVE_FIRE_PUNCH].punchingMove);
        PLAYER(SPECIES_HITMONCHAN) { Ability(ABILITY_BLITZ_BOXER); HP(hp); MaxHP(100); Speed(1);}
        OPPONENT(SPECIES_WOBBUFFET) { Speed(100);};
    } WHEN {
        TURN { MOVE(player, MOVE_FIRE_PUNCH); }
    } SCENE {
        if (hp == 100) {
            MESSAGE("Hitmonchan used Fire Punch!");
            MESSAGE("Foe Wobbuffet used Celebrate!");
        }
        else {
            MESSAGE("Hitmonchan used Fire Punch!");
            MESSAGE("Foe Wobbuffet used Celebrate!");
        }
    }
}

SINGLE_BATTLE_TEST("Blitz Boxer only grants priority to Punching moves")
{
    u32 move;
    PARAMETRIZE { move = MOVE_THUNDERPUNCH; }
    PARAMETRIZE { move = MOVE_CLOSE_COMBAT; }
    GIVEN {
        ASSUME(IsPunchingMove(MOVE_THUNDERPUNCH));
        ASSUME(!IsPunchingMove(MOVE_CLOSE_COMBAT));
        PLAYER(SPECIES_HITMONCHAN) { Ability(ABILITY_BLITZ_BOXER); HP(100); MaxHP(100); Speed(1);}
        OPPONENT(SPECIES_CHARMANDER) { Speed(100);};
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        if (move == MOVE_THUNDERPUNCH) {
            MESSAGE("Hitmonchan used Thunder Punch!");
            MESSAGE("Foe Charmander used Celebrate!");
        }
        else {
            MESSAGE("Foe Charmander used Celebrate!");
            MESSAGE("Hitmonchan used Close Combat!");
        }
    }
}


