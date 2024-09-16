//
// DO NOT MODIFY THIS FILE! It is auto-generated from test/battle/trainer_control.party
//
// If you want to modify this file set COMPETITIVE_PARTY_SYNTAX to FALSE
// in include/config/general.h and remove this notice.
// Use sed -i '/^#line/d' 'test/battle/trainer_control.h' to remove #line markers.
//

#line 1 "test/battle/trainer_control.party"

#line 1
    [0] =
    {
#line 2
        .trainerName = _("Test1"),
#line 3
        .trainerClass = TRAINER_CLASS_PKMN_TRAINER_1,
#line 4
        .trainerPic = TRAINER_PIC_RED,
        .encounterMusic_gender = 
#line 6
            TRAINER_ENCOUNTER_MUSIC_MALE,
#line 7
        .doubleBattle = FALSE,
        .partySize = 3,
        .party = (const struct TrainerMon[])
        {
            {
#line 9
            .nickname = COMPOUND_STRING("Bubbles"),
#line 9
            .species = SPECIES_WOBBUFFET,
#line 9
            .gender = TRAINER_MON_FEMALE,
#line 9
            .heldItem = ITEM_ASSAULT_VEST,
#line 14
            .ev = TRAINER_PARTY_EVS(252, 0, 0, 252, 4, 0),
#line 13
            .iv = TRAINER_PARTY_IVS(25, 26, 27, 28, 29, 30),
#line 15
            .spread = SPREAD_TEST_TRAINER_CTL_BUBBLES,
#line 12
            .ability = ABILITY_TELEPATHY,
#line 11
            .lvl = 67,
#line 18
            .ball = ITEM_MASTER_BALL,
#line 16
            .friendship = 42,
#line 10
            .nature = NATURE_HASTY,
#line 17
            .isShiny = TRUE,
#line 19
            .dynamaxLevel = 5,
            .shouldUseDynamax = TRUE,
            .moves = {
#line 20
                MOVE_AIR_SLASH,
                MOVE_BARRIER,
                MOVE_SOLAR_BEAM,
                MOVE_EXPLOSION,
            },
            },
            {
#line 25
            .species = SPECIES_WOBBUFFET,
            .gender = TRAINER_MON_RANDOM_GENDER,
#line 28
            .iv = TRAINER_PARTY_IVS(0, 0, 0, 0, 0, 0),
#line 29
            .spread = SPREAD_TEST_TRAINER_CTL_WOB,
#line 27
            .ability = ABILITY_SHADOW_TAG,
#line 26
            .lvl = 5,
            .nature = NATURE_HARDY,
            .dynamaxLevel = MAX_DYNAMAX_LEVEL,
            },
            {
#line 31
            .species = SPECIES_WYNAUT,
            .gender = TRAINER_MON_RANDOM_GENDER,
#line 33
            .iv = TRAINER_PARTY_IVS(0, 0, 0, 0, 0, 0),
#line 34
            .spread = SPREAD_TEST_TRAINER_CTL_WY,
#line 32
            .lvl = 5,
            .nature = NATURE_HARDY,
            .dynamaxLevel = MAX_DYNAMAX_LEVEL,
            },
        },
    },
