@ Interact with cuttable tree
EventScript_CutTree::
	lockall
	goto_if_unset FLAG_BADGE01_GET, EventScript_CheckTreeCantCut
	checkpartymove MOVE_CUT
	compare VAR_RESULT, PARTY_SIZE
    goto_if_eq EventScript_AnorithCut
	setfieldeffectargument 0, VAR_RESULT
	bufferpartymonnick STR_VAR_1, VAR_RESULT
	buffermovename STR_VAR_2, MOVE_CUT
	msgbox Text_WantToCut, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, EventScript_CancelCut
	msgbox Text_MonUsedFieldMove, MSGBOX_DEFAULT
	closemessage

EventScript_CutTreeCommon:
	isfollowerfieldmoveuser VAR_0x8004
	setfieldeffectargument 3, VAR_0x8004 @ skip pose if so
	dofieldeffect FLDEFF_USE_CUT_ON_TREE
	waitstate

EventScript_AnorithCut::
   	compare VAR_RUSTBORO_CITY_STATE, 9
   	goto_if_lt EventScript_CheckTreeCantCut
   	setvar VAR_0x8004, SPECIES_ANORITH
   	setvar VAR_0x8008, MOVE_CUT
   	setvar VAR_0x8009, 1
   	bufferspeciesname 0, VAR_0x8004
   	buffermovename 1, VAR_0x8008
   	msgbox Text_AnorithToCut, MSGBOX_YESNO
   	compare VAR_RESULT, NO
   	goto_if_eq EventScript_CancelCut
   	msgbox Text_MonUsedFieldMove, MSGBOX_DEFAULT
   	closemessage
   	dofieldeffect FLDEFF_USE_CUT_ON_TREE
   	waitstate
   	goto EventScript_CutTreeDown
   	end

@ Use cut from party menu
EventScript_UseCut::
	lockall
	goto EventScript_CutTreeCommon

EventScript_CutTreeDown:
	applymovement VAR_LAST_TALKED, Movement_CutTreeDown
	waitmovement 0
	removeobject VAR_LAST_TALKED
	random 3
	switch VAR_RESULT
	case 0, EventScript_CutTreeEncounter
	case 1, EventScript_CutTreeItem
	case 2, EventScript_CancelCut
	releaseall
	end

EventScript_CutTreeEncounter::
	compare VAR_REPEL_STEP_COUNT, 0
	goto_if_gt EventScript_CancelCut
	special RockSmashWildEncounter
	compare VAR_RESULT, 0
	goto_if_eq EventScript_CancelCut
	waitstate
	releaseall
	end

EventScript_CutTreeItem::
	random 14
	switch VAR_RESULT
	case 0, EventScript_CutTreeMiracleSeed
	case 1, EventScript_CutTreeCharcoal
	case 2, EventScript_CutTreeMentalHerb
	case 3, EventScript_CutTreePowerHerb
	case 4, EventScript_CutTreeWhiteHerb
	case 5, EventScript_CutTreeRevivalHerb
	case 6, EventScript_CutTreeEnergyRoot
	case 7, EventScript_CutTreeTerrainSeed
	case 8, EventScript_CutTreeTinyMushroom
	case 9, EventScript_CutTreeBigMushroom
	case 10, EventScript_CutTreeTypeBerry
	case 11, EventScript_CutTreeEVBerry
	case 12, EventScript_CutTreeStick
	case 13, EventScript_CutTreeBigRoot
	releaseall
	end

EventScript_CutTreeMiracleSeed::
	finditem ITEM_MIRACLE_SEED
	releaseall
	end

EventScript_CutTreeCharcoal::
	finditem ITEM_CHARCOAL
	releaseall
	end

EventScript_CutTreeMentalHerb::
	finditem ITEM_MENTAL_HERB
	releaseall
	end

EventScript_CutTreePowerHerb::
	finditem ITEM_POWER_HERB
	releaseall
	end

EventScript_CutTreeWhiteHerb::
	finditem ITEM_WHITE_HERB
	releaseall
	end

EventScript_CutTreeRevivalHerb::
	finditem ITEM_REVIVAL_HERB
	releaseall
	end

EventScript_CutTreeEnergyRoot::
	finditem ITEM_ENERGY_ROOT
	releaseall
	end

EventScript_CutTreeTerrainSeed::
	random 4
	addvar VAR_RESULT, ITEM_ELECTRIC_SEED
	finditem VAR_RESULT
	releaseall
	end

EventScript_CutTreeTinyMushroom::
	finditem ITEM_TINY_MUSHROOM
	releaseall
	end

EventScript_CutTreeBigMushroom::
	finditem ITEM_BIG_MUSHROOM
	releaseall
	end

EventScript_CutTreeTypeBerry::
	random 18
	addvar VAR_RESULT, ITEM_OCCA_BERRY
	finditem VAR_RESULT
	releaseall
	end

EventScript_CutTreeEVBerry::
	random 6
	addvar VAR_RESULT, ITEM_POMEG_BERRY
	finditem VAR_RESULT
	releaseall
	end

EventScript_CutTreeStick::
	finditem ITEM_LEEK
	releaseall
	end

EventScript_CutTreeBigRoot::
	finditem ITEM_BIG_ROOT
	releaseall
	end

Movement_CutTreeDown: @ 829071F
	cut_tree
	step_end

EventScript_CheckTreeCantCut:: @ 8290721
	msgbox Text_CantCut, MSGBOX_DEFAULT
	releaseall
	end

EventScript_CancelCut::
	closemessage
	releaseall
	end

Text_WantToCut:
	.string "This tree looks like it can be\n"
	.string "cut down!\p"
	.string "Would you like to Cut it?$"

Text_AnorithToCut:
	.string "This tree looks like it can be Cut down!\n"
	.string "Call Roxanne's Anorith to Cut it?$"

Text_MonUsedFieldMove: @ 8290771
	.string "{STR_VAR_1} used {STR_VAR_2}!$"

Text_CantCut:
	.string "This tree looks like it can be\n"
	.string "cut down!$"

@ Use rock smash from party menu
EventScript_UseRockSmash::
	lockall
	goto EventScript_RockSmashCommon

@ Interact with smashable rock
EventScript_RockSmash::
	lockall
	goto_if_unset FLAG_BADGE03_GET, EventScript_CantSmashRock
	checkpartymove MOVE_ROCK_SMASH
	compare VAR_RESULT, PARTY_SIZE
	goto_if_eq EventScript_RaichuSmash
	setfieldeffectargument 0, VAR_RESULT
	bufferpartymonnick STR_VAR_1, VAR_RESULT
	buffermovename STR_VAR_2, MOVE_ROCK_SMASH
	msgbox Text_WantToSmash, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, EventScript_CancelSmash
	msgbox Text_MonUsedFieldMove, MSGBOX_DEFAULT
	closemessage
EventScript_RockSmashCommon:
	@ check if follower should use the field move
	isfollowerfieldmoveuser VAR_0x8004
	setfieldeffectargument 3, VAR_0x8004 @ skip pose if so
	dofieldeffect FLDEFF_USE_ROCK_SMASH
	waitstate
EventScript_SmashRock:: @ fallthrough
	setflag FLAG_SAFE_FOLLOWER_MOVEMENT
	call_if_eq VAR_0x8004, TRUE, EventScript_FollowerFieldMove
	applymovement VAR_LAST_TALKED, Movement_SmashRock
	waitmovement 0
	removeobject VAR_LAST_TALKED
	specialvar VAR_RESULT, TryUpdateRusturfTunnelState
	goto_if_eq VAR_RESULT, TRUE, EventScript_EndSmash
	special RockSmashWildEncounter
	goto_if_eq VAR_RESULT, FALSE, EventScript_EndSmash
	waitstate
	releaseall
	end

EventScript_RaichuSmash::
   	setvar VAR_0x8004, SPECIES_RAICHU_ALOLAN
   	setvar VAR_0x8008, MOVE_ROCK_SMASH
   	setvar VAR_0x8009, 1
   	bufferspeciesname 0, VAR_0x8004
   	buffermovename 1, VAR_0x8008
   	msgbox Text_RaichuSmash, MSGBOX_YESNO
   	compare VAR_RESULT, NO
   	goto_if_eq EventScript_CancelSmash
   	msgbox Text_MonUsedFieldMove, MSGBOX_DEFAULT
   	closemessage
    dofieldeffect FLDEFF_USE_ROCK_SMASH
    waitstate
    goto EventScript_SmashRock
    end

EventScript_FollowerFieldMove:
	getdirectiontoface VAR_0x8005, OBJ_EVENT_ID_FOLLOWER, OBJ_EVENT_ID_PLAYER
	specialvar VAR_0x8006, GetPlayerFacingDirection
	goto_if_eq VAR_0x8005, DIR_NONE, EventScript_FollowerFieldMoveEnd
	@ Swap follower and player
	call EventScript_FollowerSwap
	@ Face follower in direction and jump
	switch VAR_0x8006
	case DIR_NORTH, EventScript_FollowerJumpNorth
	case DIR_EAST, EventScript_FollowerJumpEast
	case DIR_SOUTH, EventScript_FollowerJumpSouth
	case DIR_WEST, EventScript_FollowerJumpWest
EventScript_FollowerFieldMoveEnd:
	return

EventScript_FollowerSwap:
	switch VAR_0x8005
	case DIR_NORTH, EventScript_FollowerMoveNorth
	case DIR_EAST, EventScript_FollowerMoveEast
	case DIR_SOUTH, EventScript_FollowerMoveSouth
	case DIR_WEST, EventScript_FollowerMoveWest
	return

EventScript_FollowerMoveNorth:
	applymovement OBJ_EVENT_ID_FOLLOWER, Movement_WalkUp
	applymovement OBJ_EVENT_ID_PLAYER, Movement_WalkDown
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	return

EventScript_FollowerMoveEast:
	applymovement OBJ_EVENT_ID_FOLLOWER, Movement_WalkRight
	applymovement OBJ_EVENT_ID_PLAYER, Movement_WalkLeft
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceRight
	waitmovement 0
	return

EventScript_FollowerMoveSouth:
	applymovement OBJ_EVENT_ID_FOLLOWER, Movement_WalkDown
	applymovement OBJ_EVENT_ID_PLAYER, Movement_WalkUp
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceDown
	waitmovement 0
	return

EventScript_FollowerMoveWest:
	applymovement OBJ_EVENT_ID_FOLLOWER, Movement_WalkLeft
	applymovement OBJ_EVENT_ID_PLAYER, Movement_WalkRight
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceLeft
	waitmovement 0
	return

EventScript_FollowerJumpNorth:
	applymovement OBJ_EVENT_ID_FOLLOWER, Movement_JumpUp
	waitmovement 0
	return

EventScript_FollowerJumpEast:
	applymovement OBJ_EVENT_ID_FOLLOWER, Movement_JumpRight
	waitmovement 0
	return

EventScript_FollowerJumpSouth:
	applymovement OBJ_EVENT_ID_FOLLOWER, Movement_JumpDown
	waitmovement 0
	return

EventScript_FollowerJumpWest:
	applymovement OBJ_EVENT_ID_FOLLOWER, Movement_JumpLeft
	waitmovement 0
	return

EventScript_RockSmashItem::
	random 12
	switch VAR_RESULT
	case 0, EventScript_RockSmashPearl
	case 1, EventScript_RockSmashBigPearl
	case 2, EventScript_RockSmashEther
	case 3, EventScript_RockSmashMaxEther
	case 4, EventScript_RockSmashSoftSand
	case 5, EventScript_RockSmashHardStone
	case 6, EventScript_RockSmashRevive
	case 7, EventScript_RockSmashMaxRevive
	case 8, EventScript_RockSmashStarPiece
	case 9, EventScript_RockSmashGem
	case 10, EventScript_RockSmashFossil
	case 11, EventScript_RockSmashBottleCap
	releaseall
	end

EventScript_RockSmashPearl::
	finditem ITEM_PEARL
	releaseall
	end

EventScript_RockSmashBigPearl::
	finditem ITEM_BIG_PEARL
	releaseall
	end

EventScript_RockSmashEther::
	finditem ITEM_ETHER
	releaseall
	end

EventScript_RockSmashMaxEther::
	finditem ITEM_MAX_ETHER
	releaseall
	end

EventScript_RockSmashSoftSand::
	finditem ITEM_SOFT_SAND
	releaseall
	end

EventScript_RockSmashHardStone::
	finditem ITEM_HARD_STONE
	releaseall
	end

EventScript_RockSmashRevive::
	finditem ITEM_REVIVE
	releaseall
	end

EventScript_RockSmashMaxRevive::
	finditem ITEM_MAX_REVIVE
	releaseall
	end

EventScript_RockSmashStarPiece::
	finditem ITEM_STAR_PIECE
	releaseall
	end

EventScript_RockSmashGem::
	random 19
	addvar VAR_RESULT, ITEM_BUG_GEM
	finditem VAR_RESULT
	releaseall
	end

EventScript_RockSmashFossil::
	random 12
	compare VAR_RESULT, 11
	goto_if_eq EventScript_RockSmashOldAmber
	addvar VAR_RESULT, ITEM_ARMOR_FOSSIL
	finditem VAR_RESULT
	releaseall
	end

EventScript_RockSmashBottleCap::
	finditem ITEM_BOTTLE_CAP
	releaseall
	end

EventScript_RockSmashOldAmber::
	finditem ITEM_OLD_AMBER
	releaseall
	end

EventScript_EndSmash::
	releaseall
	end

Movement_WalkUp:
	walk_up
	step_end

Movement_JumpUp:
	jump_in_place_up
	step_end

Movement_WalkRight:
	walk_right
	step_end

Movement_JumpRight:
	jump_in_place_right
	step_end

Movement_WalkDown:
	walk_down
	step_end

Movement_JumpDown:
	jump_in_place_down
	step_end

Movement_WalkLeft:
	walk_left
	step_end

Movement_JumpLeft:
	jump_in_place_left
	step_end

Movement_SmashRock:
	rock_smash_break
	step_end

EventScript_CantSmashRock::
	msgbox Text_CantSmash, MSGBOX_DEFAULT
	releaseall
	end

EventScript_CancelSmash::
	closemessage
	releaseall
	end

Text_RaichuSmash:
  	.string "This rock appears to be breakable.\n"
   	.string "Call Wattson's Raichu to smash it?$"

Text_WantToSmash:
	.string "This rock appears to be breakable.\n"
	.string "Would you like to use Rock Smash?$"

Text_CantSmash:
	.string "It's a rugged rock, but a Pokémon\n"
	.string "may be able to smash it.$"

EventScript_StrengthBoulder::
	lockall
	goto_if_unset FLAG_BADGE04_GET, EventScript_CantStrength
	goto_if_set FLAG_SYS_USE_STRENGTH, EventScript_CheckActivatedBoulder
	checkpartymove MOVE_STRENGTH
	compare VAR_RESULT, PARTY_SIZE
	goto_if_eq EventScript_ArcanineStrength
	setfieldeffectargument 0, VAR_RESULT
	msgbox Text_WantToStrength, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq EventScript_CancelStrength
	closemessage
	dofieldeffect FLDEFF_USE_STRENGTH
	waitstate
	goto EventScript_ActivateStrength
	end

EventScript_ArcanineStrength::
	setvar VAR_0x8004, SPECIES_ARCANINE
	setvar VAR_0x8008, MOVE_STRENGTH
	setvar VAR_0x8009, 1
	msgbox Text_ArcanineStrength, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq EventScript_CancelStrength
	closemessage
	dofieldeffect FLDEFF_USE_STRENGTH
	waitstate
	goto EventScript_ActivateArcanineStrength
	end

EventScript_UseStrength::
	lockall
	dofieldeffect FLDEFF_USE_STRENGTH
	waitstate
	goto EventScript_ActivateStrength
	end

EventScript_ActivateStrength::
	setflag FLAG_SYS_USE_STRENGTH
	msgbox Text_MonUsedStrength, MSGBOX_DEFAULT
	releaseall
	end

EventScript_ActivateArcanineStrength::
   	setflag FLAG_SYS_USE_STRENGTH
   	msgbox Text_ArcanineUsedStrength, MSGBOX_DEFAULT
   	releaseall
   	end

EventScript_CantStrength::
	msgbox Text_CantStrength, MSGBOX_DEFAULT
	releaseall
	end

EventScript_CheckActivatedBoulder::
	msgbox Text_StrengthActivated, MSGBOX_DEFAULT
	releaseall
	end

EventScript_CancelStrength::
	closemessage
	releaseall
	end

Text_WantToStrength:
	.string "It's a big boulder, but a Pokémon\n"
	.string "may be able to push it aside.\p"
	.string "Would you like to use Strength?$"

Text_ArcanineStrength: @ 829092C
	.string "It's a big boulder, but a Pokémon\n"
	.string "may be able to push it aside.\p"
	.string "Call Flannery's Arcanine to push it?$"

Text_MonUsedStrength:
	.string "{STR_VAR_1} used Strength!\p"
	.string "{STR_VAR_1}'s Strength made it\n"
	.string "possible to move boulders around!$"

Text_ArcanineUsedStrength:
	.string "Arcanine used Strength!\p"
	.string "Arcanine 's Strength made it\n"
	.string "possible to move boulders around!$"

Text_CantStrength:
	.string "It's a big boulder, but a Pokémon\n"
	.string "may be able to push it aside.$"

Text_StrengthActivated:
	.string "Strength made it possible to move\n"
	.string "boulders around.$"


EventScript_UseWaterfall:: @ 8290A49
	lockall
	goto_if_unset FLAG_BADGE08_GET, EventScript_CannotUseWaterfall
	checkpartymove MOVE_WATERFALL
	compare VAR_RESULT, PARTY_SIZE
	goto_if_eq EventScript_KabutopsWaterfall
	bufferpartymonnick 0, VAR_RESULT
	setfieldeffectargument 0, VAR_RESULT
	msgbox Text_WantToWaterfall, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq EventScript_EndWaterfall
	msgbox Text_MonUsedWaterfall, MSGBOX_DEFAULT
	dofieldeffect FLDEFF_USE_WATERFALL
	goto EventScript_EndWaterfall

EventScript_CannotUseWaterfall::
	lockall

EventScript_KabutopsWaterfall::
	setvar VAR_0x8004, SPECIES_KABUTOPS
	setvar VAR_0x8008, MOVE_WATERFALL
	setvar VAR_0x8009, 1
	bufferspeciesname 0, VAR_0x8004
	buffermovename 1, VAR_0x8008
	setfieldeffectargument 0, VAR_RESULT
	msgbox Text_KabutopsWaterfall, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq EventScript_EndWaterfall
	msgbox Text_MonUsedWaterfall, MSGBOX_DEFAULT
	dofieldeffect FLDEFF_USE_WATERFALL
	goto EventScript_EndWaterfall

EventScript_CantWaterfall::
	msgbox Text_CantWaterfall, MSGBOX_DEFAULT

EventScript_EndWaterfall::
	releaseall
	end

Text_CantWaterfall:
	.string "A wall of water is crashing down with\n"
	.string "a mighty roar.$"

Text_WantToWaterfall:
	.string "It's a large waterfall.\n"
	.string "Would you like to use Waterfall?$"

Text_KabutopsWaterfall:
	.string "It's a large waterfall.\n"
	.string "Call Juan's Kabutops to climb it?$"

Text_MonUsedWaterfall:
	.string "{STR_VAR_1} used Waterfall.$"

EventScript_UseDive::
	lockall
	goto_if_unset FLAG_BADGE07_GET, EventScript_CantDive
	checkpartymove MOVE_DIVE
	compare VAR_RESULT, PARTY_SIZE
	goto_if_eq EventScript_SlowbroDive
	bufferpartymonnick 0, VAR_RESULT
	setfieldeffectargument 0, VAR_RESULT
	setfieldeffectargument 1, 1
	msgbox Text_WantToDive, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq EventScript_EndDive
	msgbox Text_MonUsedDive, MSGBOX_DEFAULT
	dofieldeffect FLDEFF_USE_DIVE
	goto EventScript_EndDive
	end

EventScript_SlowbroDive::
	setvar VAR_0x8004, SPECIES_SLOWBRO
	setvar VAR_0x8008, MOVE_DIVE
	setvar VAR_0x8009, 1
	bufferspeciesname 0, VAR_0x8004
	buffermovename 1, VAR_0x8008
	msgbox Text_SlowbroDive, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq EventScript_EndDive
	msgbox Text_MonUsedDive, MSGBOX_DEFAULT
	dofieldeffect FLDEFF_USE_DIVE
	goto EventScript_EndDive
	end

EventScript_CantDive::
	msgbox Text_CantDive, MSGBOX_DEFAULT
	releaseall
	end

EventScript_EndDive::
	releaseall
	end

EventScript_UseDiveUnderwater:: @ 8290B5A
	lockall
	checkpartymove MOVE_DIVE
	compare VAR_RESULT, PARTY_SIZE
	goto_if_eq EventScript_SlowbroSurface
	bufferpartymonnick 0, VAR_RESULT
	setfieldeffectargument 0, VAR_RESULT
	setfieldeffectargument 1, 1
	msgbox Text_WantToSurface, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq EventScript_EndSurface
	msgbox Text_MonUsedDive, MSGBOX_DEFAULT
	dofieldeffect FLDEFF_USE_DIVE
	goto EventScript_EndSurface
	end

EventScript_SlowbroSurface::
	setvar VAR_0x8004, SPECIES_SLOWBRO
	setvar VAR_0x8008, MOVE_DIVE
	setvar VAR_0x8009, 1
	bufferspeciesname 0, VAR_0x8004
	buffermovename 1, VAR_0x8008
	msgbox Text_WantToSurface, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq EventScript_EndSurface
	msgbox Text_MonUsedDive, MSGBOX_DEFAULT
	dofieldeffect FLDEFF_USE_DIVE
	goto EventScript_EndSurface
	end

EventScript_CantSurface::
	lockall
	msgbox Text_CantSurface, MSGBOX_DEFAULT
	goto EventScript_EndSurface
	end

EventScript_EndSurface::
	releaseall
	end

Text_CantDive:
	.string "The sea is deep here. A Pokémon\n"
	.string "may be able to go underwater.$"

Text_WantToDive:
	.string "The sea is deep here.\n"
	.string "Would you like to use Dive?$"

Text_SlowbroDive:
	.string "The sea is deep here.\n"
	.string "Call Tate & Liza's Slowbro to Dive?$"

Text_MonUsedDive:
	.string "{STR_VAR_1} used Dive.$"

Text_CantSurface:
	.string "Light is filtering down from above.\n"
	.string "A Pokémon may be able to surface.$"

Text_WantToSurface:
	.string "Light is filtering down from above.\n"
	.string "Would you like to use Dive?$"

EventScript_FailSweetScent::
	msgbox Text_FailSweetScent, MSGBOX_SIGN
	end

Text_FailSweetScent:
	.string "Looks like there's nothing here…$"

EventScript_DisableAutoRun::
    msgbox AutoRunDisabled MSGBOX_SIGN
    end
AutoRunDisabled:
    .string "Auto Run {COLOR RED}Disabled{COLOR DARK_GRAY}.$"

EventScript_EnableAutoRun::
    msgbox AutoRunEnabled MSGBOX_SIGN
    end
AutoRunEnabled:
    .string "Auto Run {COLOR GREEN}Enabled{COLOR DARK_GRAY}.$"
