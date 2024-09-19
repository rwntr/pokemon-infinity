#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Light Ball always gives Pikachu a 2.0x Atk/Sp. Atk boost")
{
    s16 boostedHitPhys;
    s16 normalHitPhys;
    s16 boostedHitSpec;
    s16 normalHitSpec;

    GIVEN {
        PLAYER(SPECIES_PIKACHU) { Item(ITEM_LIGHT_BALL); };
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_TACKLE); }
        TURN { MOVE(opponent, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_SWIFT); }
        TURN { MOVE(opponent, MOVE_THIEF); }
        TURN { MOVE(player, MOVE_TACKLE); }
        TURN { MOVE(opponent, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_SWIFT); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TACKLE, player);
        HP_BAR(opponent, captureDamage: &boostedHitPhys);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SWIFT, player);
        HP_BAR(opponent, captureDamage: &boostedHitSpec);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_THIEF, opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TACKLE, player);
        HP_BAR(opponent, captureDamage: &normalHitPhys);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SWIFT, player);
        HP_BAR(opponent, captureDamage: &normalHitSpec);

    } THEN {
        EXPECT_MUL_EQ(normalHitPhys, Q_4_12(2.0), boostedHitPhys);
        EXPECT_MUL_EQ(normalHitSpec, Q_4_12(2.0), boostedHitSpec);
    }
}

SINGLE_BATTLE_TEST("Light Ball always gives Raichu a 1.5x Atk/Sp. Atk boost")
{
    s16 boostedHitPhys;
    s16 normalHitPhys;
    s16 boostedHitSpec;
    s16 normalHitSpec;

    GIVEN {
        PLAYER(SPECIES_RAICHU) { Item(ITEM_LIGHT_BALL); };
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_TACKLE); }
        TURN { MOVE(opponent, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_SWIFT); }
        TURN { MOVE(opponent, MOVE_THIEF); }
        TURN { MOVE(player, MOVE_TACKLE); }
        TURN { MOVE(opponent, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_SWIFT); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TACKLE, player);
        HP_BAR(opponent, captureDamage: &boostedHitPhys);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SWIFT, player);
        HP_BAR(opponent, captureDamage: &boostedHitSpec);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_THIEF, opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TACKLE, player);
        HP_BAR(opponent, captureDamage: &normalHitPhys);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SWIFT, player);
        HP_BAR(opponent, captureDamage: &normalHitSpec);

    } THEN {
        EXPECT_MUL_EQ(normalHitPhys, Q_4_12(1.5), boostedHitPhys);
        EXPECT_MUL_EQ(normalHitSpec, Q_4_12(1.5), boostedHitSpec);
    }
}

SINGLE_BATTLE_TEST("Light Ball always gives Alolan Raichu a 1.5x Atk/Sp. Atk boost")
{
    s16 boostedHitPhys;
    s16 normalHitPhys;
    s16 boostedHitSpec;
    s16 normalHitSpec;

    GIVEN {
        ASSUME(P_ALOLAN_FORMS);
        PLAYER(SPECIES_RAICHU_ALOLAN) { Item(ITEM_LIGHT_BALL); };
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_TACKLE); }
        TURN { MOVE(opponent, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_SWIFT); }
        TURN { MOVE(opponent, MOVE_THIEF); }
        TURN { MOVE(player, MOVE_TACKLE); }
        TURN { MOVE(opponent, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_SWIFT); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TACKLE, player);
        HP_BAR(opponent, captureDamage: &boostedHitPhys);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SWIFT, player);
        HP_BAR(opponent, captureDamage: &boostedHitSpec);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_THIEF, opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TACKLE, player);
        HP_BAR(opponent, captureDamage: &normalHitPhys);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SWIFT, player);
        HP_BAR(opponent, captureDamage: &normalHitSpec);

    } THEN {
        EXPECT_MUL_EQ(normalHitPhys, Q_4_12(1.5), boostedHitPhys);
        EXPECT_MUL_EQ(normalHitSpec, Q_4_12(1.5), boostedHitSpec);
    }
}