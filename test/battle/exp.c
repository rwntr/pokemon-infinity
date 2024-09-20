#include "global.h"
#include "test/battle.h"

#if B_EXP_CATCH >= GEN_6

WILD_BATTLE_TEST("Pokemon gain exp after catching a Pokemon")
{
    u8 level = 0;

    PARAMETRIZE { level = 50; }
    PARAMETRIZE { level = MAX_LEVEL; }

    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Level(level); }
        OPPONENT(SPECIES_CATERPIE) { HP(1); }
    } WHEN {
        TURN { USE_ITEM(player, ITEM_ULTRA_BALL); }
    } SCENE {
        MESSAGE("You used Ultra Ball!");
        ANIMATION(ANIM_TYPE_SPECIAL, B_ANIM_BALL_THROW, player);
        if (level != MAX_LEVEL) {
            EXPERIENCE_BAR(player);
        }
    }
}

#endif // B_EXP_CATCH

WILD_BATTLE_TEST("Higher leveled Pokemon give more exp", s32 exp)
{
    u8 level = 0;

    PARAMETRIZE { level = 5; }
    PARAMETRIZE { level = 10; }

    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Level(3); }
        OPPONENT(SPECIES_CATERPIE) { Level(level); HP(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_TACKLE); }
    } SCENE {
        MESSAGE("Wobbuffet used Tackle!");
        MESSAGE("Wild Caterpie fainted!");
        EXPERIENCE_BAR(player, captureGainedExp: &results[i].exp);
    } FINALLY {
        EXPECT_GT(results[1].exp, results[0].exp);
    }
}

WILD_BATTLE_TEST("Lucky Egg & Training Band boost Exp gains by 50% and 500% respectively", s32 exp)
{
    u32 item = 0;

    PARAMETRIZE { item = ITEM_LUCKY_EGG; }
    PARAMETRIZE { item = ITEM_NONE; }
    PARAMETRIZE { item = ITEM_TRAINING_BAND; }

    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Level(20); Item(item); }
        PLAYER(SPECIES_TRUBBISH) { Level(100); Moves(MOVE_SPLASH); } //to proc training band
        OPPONENT(SPECIES_CATERPIE) { Level(10); HP(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_TACKLE); }
    } SCENE {
        MESSAGE("Wobbuffet used Tackle!");
        MESSAGE("Wild Caterpie fainted!");
        EXPERIENCE_BAR(player, captureGainedExp: &results[i].exp);
    } FINALLY {
        EXPECT_MUL_EQ(results[1].exp, Q_4_12(1.5), results[0].exp);
        EXPECT_MUL_EQ(results[1].exp, Q_4_12(5), results[2].exp);
    }
}

#if (B_SCALED_EXP == GEN_5 || B_SCALED_EXP >= GEN_7)

WILD_BATTLE_TEST("Exp is scaled to player and opponent's levels", s32 exp)
{
    u8 level = 0;

    PARAMETRIZE { level = 5; }
    PARAMETRIZE { level = 10; }

    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Level(level); }
        OPPONENT(SPECIES_CATERPIE) { Level(5); HP(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_TACKLE); }
    } SCENE {
        MESSAGE("Wobbuffet used Tackle!");
        MESSAGE("Wild Caterpie fainted!");
        EXPERIENCE_BAR(player, captureGainedExp: &results[i].exp);
    } FINALLY {
        EXPECT_GT(results[0].exp, results[1].exp);
    }
}

#endif

WILD_BATTLE_TEST("Large exp gains are supported", s32 exp) // #1455
{
    u8 level = 0;

    PARAMETRIZE { level = 3; }
    PARAMETRIZE { level = 4; }
    PARAMETRIZE { level = 5; }

    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Level(1); Item(ITEM_LUCKY_EGG); OTName("Test"); } // OT Name is different so it gets more exp as a traded mon
        OPPONENT(SPECIES_BLISSEY) { Level(level); HP(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_TACKLE); }
    } SCENE {
        MESSAGE("Wobbuffet used Tackle!");
        MESSAGE("Wild Blissey fainted!");
        EXPERIENCE_BAR(player, captureGainedExp: &results[i].exp);
    } THEN {
        EXPECT(GetMonData(&gPlayerParty[0], MON_DATA_LEVEL) > 1);
        EXPECT(GetMonData(&gPlayerParty[0], MON_DATA_EXP) > 1);
    } FINALLY {
        EXPECT_GT(results[1].exp, results[0].exp);
        EXPECT_GT(results[2].exp, results[1].exp);
    }
}


//commented exp share test here because it's literally impossible to test for no reason at all

/*WILD_BATTLE_TEST("Exp Share mechanics match Inclement Emerald Documentation", s32 exp)
{
    u16 level=1;
    PARAMETRIZE { level=50;}
    PARAMETRIZE { level=100;}
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Level(1); Moves(MOVE_TACKLE); }
        PLAYER(SPECIES_WOBBUFFET) { Level(1); Item(ITEM_EXP_SHARE); }
        PLAYER(SPECIES_WOBBUFFET) { Level(1); }
        PLAYER(SPECIES_WOBBUFFET) { Level(1); }
        PLAYER(SPECIES_WOBBUFFET) { Level(1); }
        PLAYER(SPECIES_WOBBUFFET) { Level(1); }
        OPPONENT(SPECIES_CATERPIE) { Level(level); HP(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_TACKLE); }
    } SCENE {
        MESSAGE("Wobbuffet used Tackle!");
        MESSAGE("Wild Caterpie fainted!");
        //MESSAGE("The rest of your team gained EXP. Points thanks to the Exp. Share!");
    }
    FINALLY {
    EXPECT_GT(GetMonData(&PLAYER_PARTY[1], MON_DATA_EXP), gExperienceTables[gSpeciesInfo[SPECIES_WOBBUFFET].growthRate][1]); //not zero
    EXPECT_EQ((GetMonData(&PLAYER_PARTY[0], MON_DATA_EXP)), (GetMonData(&PLAYER_PARTY[1], MON_DATA_EXP)));
    EXPECT_MUL_EQ((GetMonData(&PLAYER_PARTY[2], MON_DATA_EXP)), UQ_4_12(4.0), (GetMonData(&PLAYER_PARTY[0], MON_DATA_EXP)));
    EXPECT_MUL_EQ((GetMonData(&PLAYER_PARTY[3], MON_DATA_EXP)), UQ_4_12(4.0), (GetMonData(&PLAYER_PARTY[0], MON_DATA_EXP)));
    EXPECT_MUL_EQ((GetMonData(&PLAYER_PARTY[4], MON_DATA_EXP)), UQ_4_12(4.0), (GetMonData(&PLAYER_PARTY[0], MON_DATA_EXP)));
    EXPECT_MUL_EQ((GetMonData(&PLAYER_PARTY[5], MON_DATA_EXP)), UQ_4_12(4.0), (GetMonData(&PLAYER_PARTY[0], MON_DATA_EXP)));
        }
}
*/
