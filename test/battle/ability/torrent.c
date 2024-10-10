#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Torrent boosts Water-type moves in a pinch", s16 damage)
{
    u16 hp;
    u16 ability;
    PARAMETRIZE { ability = ABILITY_SHIELD_DUST; hp = 99; }
    PARAMETRIZE { ability = ABILITY_TORRENT; hp = 33; }
    GIVEN {
        ASSUME(gMovesInfo[MOVE_BUBBLE].type == TYPE_WATER);
        PLAYER(SPECIES_SQUIRTLE) { Ability(ability); MaxHP(99); HP(hp); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_BUBBLE); }
    } SCENE {
        HP_BAR(opponent, .captureDamage =  &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.5), results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Torrent boosts Water-type moves outside of pinch", s16 damage)
{
    u16 hp;
    u16 ability;
    PARAMETRIZE { ability = ABILITY_SHIELD_DUST; hp = 99; }
    PARAMETRIZE { ability = ABILITY_TORRENT; hp = 99; }
    GIVEN {
        ASSUME(gMovesInfo[MOVE_BUBBLE].type == TYPE_WATER);
        PLAYER(SPECIES_SQUIRTLE) { Ability(ability); MaxHP(99); HP(hp); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_BUBBLE); }
    } SCENE {
        HP_BAR(opponent, .captureDamage =  &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.2), results[1].damage);
    }
}
