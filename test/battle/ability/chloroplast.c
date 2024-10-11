#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Solar Beam and Solar Blade can be used instantly with Chloroplast in any weather")
{
    u32 move1, move2;
    PARAMETRIZE { move1 = MOVE_SPLASH; move2 = MOVE_SOLAR_BEAM; }
    PARAMETRIZE { move1 = MOVE_SUNNY_DAY; move2 = MOVE_SOLAR_BEAM; }
    PARAMETRIZE { move1 = MOVE_SPLASH; move2 = MOVE_SOLAR_BLADE; }
    PARAMETRIZE { move1 = MOVE_SUNNY_DAY; move2 = MOVE_SOLAR_BLADE; }
    PARAMETRIZE { move1 = MOVE_RAIN_DANCE; move2 = MOVE_SOLAR_BEAM; }
    PARAMETRIZE { move1 = MOVE_SANDSTORM; move2 = MOVE_SOLAR_BEAM; }
    PARAMETRIZE { move1 = MOVE_RAIN_DANCE; move2 = MOVE_SOLAR_BLADE; }
    PARAMETRIZE { move1 = MOVE_SANDSTORM; move2 = MOVE_SOLAR_BLADE; }
    PARAMETRIZE { move1 = MOVE_HAIL; move2 = MOVE_SOLAR_BEAM; }
    PARAMETRIZE { move1 = MOVE_SNOWSCAPE; move2 = MOVE_SOLAR_BEAM; }
    PARAMETRIZE { move1 = MOVE_HAIL; move2 = MOVE_SOLAR_BLADE; }
    PARAMETRIZE { move1 = MOVE_SNOWSCAPE; move2 = MOVE_SOLAR_BLADE; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_CHLOROPLAST);}
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, move1); MOVE(player, move2); }
    } SCENE {

        NOT MESSAGE("Wobbuffet took in sunlight!");

        if (move2 == MOVE_SOLAR_BEAM)
            MESSAGE("Wobbuffet used Solar Beam!");
        else
            MESSAGE("Wobbuffet used Solar Blade!");

        ANIMATION(ANIM_TYPE_MOVE, move2, player);
           HP_BAR(opponent);

    }
}

SINGLE_BATTLE_TEST("Solar Beam and Solar Blade's power are not halved in bad weather with Chloroplast", s16 damage)
{
    u32 move1, move2;
    PARAMETRIZE { move1 = MOVE_SPLASH; move2 = MOVE_SOLAR_BEAM; }
    PARAMETRIZE { move1 = MOVE_SUNNY_DAY; move2 = MOVE_SOLAR_BEAM; }
    PARAMETRIZE { move1 = MOVE_RAIN_DANCE; move2 = MOVE_SOLAR_BEAM; }
    PARAMETRIZE { move1 = MOVE_SANDSTORM; move2 = MOVE_SOLAR_BEAM; }
    PARAMETRIZE { move1 = MOVE_HAIL; move2 = MOVE_SOLAR_BEAM; }
    PARAMETRIZE { move1 = MOVE_SNOWSCAPE; move2 = MOVE_SOLAR_BEAM; }
    PARAMETRIZE { move1 = MOVE_SPLASH; move2 = MOVE_SOLAR_BLADE; }
    PARAMETRIZE { move1 = MOVE_SUNNY_DAY; move2 = MOVE_SOLAR_BLADE; }
    PARAMETRIZE { move1 = MOVE_RAIN_DANCE; move2 = MOVE_SOLAR_BLADE; }
    PARAMETRIZE { move1 = MOVE_SANDSTORM; move2 = MOVE_SOLAR_BLADE; }
    PARAMETRIZE { move1 = MOVE_HAIL; move2 = MOVE_SOLAR_BLADE; }
    PARAMETRIZE { move1 = MOVE_SNOWSCAPE; move2 = MOVE_SOLAR_BLADE; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_CHLOROPLAST);}
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, move1); MOVE(player, move2); }
    } SCENE {
        HP_BAR(opponent, .captureDamage =  &results[i].damage);
    } FINALLY {
        EXPECT_EQ(results[0].damage, results[1].damage);
        EXPECT_EQ(results[0].damage, results[2].damage);
        EXPECT_EQ(results[0].damage, results[3].damage);
        EXPECT_EQ(results[0].damage, results[4].damage);
        EXPECT_EQ(results[0].damage, results[5].damage);
        EXPECT_EQ(results[6].damage, results[7].damage);
        EXPECT_EQ(results[6].damage, results[8].damage);
        EXPECT_EQ(results[6].damage, results[9].damage);
        EXPECT_EQ(results[6].damage, results[10].damage);
        EXPECT_EQ(results[6].damage, results[11].damage);
    }
}

SINGLE_BATTLE_TEST("Growth sharply raises stats in any weather with Chloroplast")
{
    u32 move1, move2;
    PARAMETRIZE { move1 = MOVE_SPLASH; move2 = MOVE_GROWTH; }
    PARAMETRIZE { move1 = MOVE_SUNNY_DAY; move2 = MOVE_GROWTH; }
    PARAMETRIZE { move1 = MOVE_RAIN_DANCE; move2 = MOVE_GROWTH; }
    PARAMETRIZE { move1 = MOVE_SANDSTORM; move2 = MOVE_GROWTH; }
    PARAMETRIZE { move1 = MOVE_HAIL; move2 = MOVE_GROWTH; }
    PARAMETRIZE { move1 = MOVE_SNOWSCAPE; move2 = MOVE_GROWTH; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_CHLOROPLAST);}
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, move1); MOVE(player, move2); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_GROWTH, player);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, player);
        MESSAGE("Wobbuffet's Attack sharply rose!");
        MESSAGE("Wobbuffet's Sp. Atk sharply rose!");
    }
}

//TODO - version of this test that isn't reliant on Safety Goggles for weather chip
SINGLE_BATTLE_TEST("Chloroplast results in 2/3 max HP recovery, weather-agnostic from sun-dependent healing moves")
{
    u32 move1, move2;
    PARAMETRIZE { move1 = MOVE_SPLASH; move2 = MOVE_SYNTHESIS; }
    PARAMETRIZE { move1 = MOVE_SUNNY_DAY; move2 = MOVE_SYNTHESIS; }
    PARAMETRIZE { move1 = MOVE_RAIN_DANCE; move2 = MOVE_SYNTHESIS; }
    PARAMETRIZE { move1 = MOVE_SANDSTORM; move2 = MOVE_SYNTHESIS; }
    PARAMETRIZE { move1 = MOVE_HAIL; move2 = MOVE_SYNTHESIS; }
    PARAMETRIZE { move1 = MOVE_SNOWSCAPE; move2 = MOVE_SYNTHESIS; }
    PARAMETRIZE { move1 = MOVE_SPLASH; move2 = MOVE_MORNING_SUN; }
    PARAMETRIZE { move1 = MOVE_SUNNY_DAY; move2 = MOVE_MORNING_SUN; }
    PARAMETRIZE { move1 = MOVE_RAIN_DANCE; move2 = MOVE_MORNING_SUN; }
    PARAMETRIZE { move1 = MOVE_SANDSTORM; move2 = MOVE_MORNING_SUN; }
    PARAMETRIZE { move1 = MOVE_HAIL; move2 = MOVE_MORNING_SUN; }
    PARAMETRIZE { move1 = MOVE_SNOWSCAPE; move2 = MOVE_MORNING_SUN; }
    PARAMETRIZE { move1 = MOVE_SPLASH; move2 = MOVE_MOONLIGHT; }
    PARAMETRIZE { move1 = MOVE_SUNNY_DAY; move2 = MOVE_MOONLIGHT; }
    PARAMETRIZE { move1 = MOVE_RAIN_DANCE; move2 = MOVE_MOONLIGHT; }
    PARAMETRIZE { move1 = MOVE_SANDSTORM; move2 = MOVE_MOONLIGHT; }
    PARAMETRIZE { move1 = MOVE_HAIL; move2 = MOVE_MOONLIGHT; }
    PARAMETRIZE { move1 = MOVE_SNOWSCAPE; move2 = MOVE_MOONLIGHT; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_CHLOROPLAST); HP(1); MaxHP(300); Item(ITEM_SAFETY_GOGGLES);}
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, move1); MOVE(player, move2); }
    } SCENE {
        HP_BAR(player, .damage = -(300 / 1.5));
    }
}
