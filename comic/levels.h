#ifndef LEVELS_H
#define LEVELS_H

#include "data.h"

level LEVEL_DATA_LAKE =
  {
    .tt2_filename = "LAKE.TT2",
    .pt0_filename = "LAKE0.PT",
    .pt1_filename = "LAKE1.PT",
    .pt2_filename = "LAKE2.PT",
    .door_tile_ul = 16, 
    .door_tile_ur = 17,
    .door_tile_ll = 16,
    .door_tile_lr = 17,
    .shps =
    {
      {
	.num_distinct_frames = 3,
	.horizontal = ENEMY_HORIZONTAL_DUPLICATED,
	.animation = ENEMY_ANIMATION_ALTERNATE,
	.filename = "FB.SHP",
      },
      {
	.num_distinct_frames = 3,
	.horizontal = ENEMY_HORIZONTAL_DUPLICATED,
	.animation = ENEMY_ANIMATION_ALTERNATE,
	.filename = "BUG.SHP",
      },
      {
	.num_distinct_frames = SHP_UNUSED,
      },
      {
	.num_distinct_frames = SHP_UNUSED,
      },
    },
    .stages =
    {
      { // LAKE0
	.item_type = ITEM_BLASTOLA_COLA,
	.item_y = 12,
	.item_x = 112,
	.exit_l = EXIT_UNUSED,
	.exit_r = 1,
	.doors =
	{
	  {
	    .y = 10,
	    .x = 118,
	    .target_level = 1,
	    .target_stage = 2,
	  },
	  {
	    .y = 14,
	    .x = 248,
	    .target_level = 5,
	    .target_stage = 0,
	  },
	  {
	    .y = DOOR_UNUSED,
	    .x = DOOR_UNUSED,
	  },
	},
	.enemies =
	{
	  {
	    .behavior = ENEMY_BEHAVIOR_UNUSED,
	  },
	  {
	    .behavior = ENEMY_BEHAVIOR_UNUSED,
	  },
	  {
	    .shp_index = 1,
	    .behavior = ENEMY_BEHAVIOR_LEAP,
	  },
	  {
	    .shp_index = 1,
	    .behavior = ENEMY_BEHAVIOR_LEAP,
	  },
	},
      },
      { // LAKE1
	.item_type = ITEM_SHIELD,
	.item_y = 10,
	.item_x = 178,
	.exit_l = 2,
	.exit_r = 0,
	.doors =
	{
	  {
	    .y = DOOR_UNUSED,
	    .x = DOOR_UNUSED,
	  },
	  {
	    .y = DOOR_UNUSED,
	    .x = DOOR_UNUSED,
	  },
	  {
	    .y = DOOR_UNUSED,
	    .x = DOOR_UNUSED,
	  },
	},
	.enemies =
	{
	  {
	    .shp_index = 0,
	    .behavior = ENEMY_BEHAVIOR_BOUNCE,
	  },
	  {
	    .shp_index = 0,
	    .behavior = ENEMY_BEHAVIOR_BOUNCE,
	  },
	  {
	    .shp_index = 1,
	    .behavior = ENEMY_BEHAVIOR_LEAP,
	  },
	  {
	    .shp_index = 1,
	    .behavior = ENEMY_BEHAVIOR_LEAP,
	  },
	},
      },
      { // LAKE2
	.item_type = ITEM_BLASTOLA_COLA,
	.item_y = 4,
	.item_x = 124,
	.exit_l = EXIT_UNUSED,
	.exit_r = 1,
	.doors =
	{
	  {
	    .y = 14,
	    .x = 10,
	    .target_level = 4,
	    .target_stage = 0,
	  },
	  {
	    .y = 6,
	    .x = 110,
	    .target_level = 2,
	    .target_stage = 0,
	  },
	  {
	    .y = 8,
	    .x = 74,
	    .target_level = 3,
	    .target_stage = 1,
	  },
	},
	.enemies =
	{
	  {
	    .shp_index = 0,
	    .behavior = ENEMY_BEHAVIOR_BOUNCE,
	  },
	  {
	    .shp_index = 0,
	    .behavior = ENEMY_BEHAVIOR_BOUNCE,
	  },
	  {
	    .shp_index = 1,
	    .behavior = ENEMY_BEHAVIOR_LEAP,
	  },
	  {
	    .shp_index = 1,
	    .behavior = ENEMY_BEHAVIOR_LEAP,
	  },
	},
      },
    },
  };


level LEVEL_DATA_FOREST =
  {
    .tt2_filename = "FOREST.TT2",
    .pt0_filename = "FOREST0.PT",
    .pt1_filename = "FOREST1.PT",
    .pt2_filename = "FOREST2.PT",
    .door_tile_ul = 48, 
    .door_tile_ur = 49,
    .door_tile_ll = 48,
    .door_tile_lr = 49,
    .shps =
    {
      {
	.num_distinct_frames = 3,
	.horizontal = ENEMY_HORIZONTAL_SEPARATE,
	.animation = ENEMY_ANIMATION_ALTERNATE,
	.filename = "BIRD.SHP",
      },
      {
	.num_distinct_frames = 3,
	.horizontal = ENEMY_HORIZONTAL_SEPARATE,
	.animation = ENEMY_ANIMATION_ALTERNATE,
	.filename = "BIRD2.SHP",
      },
      {
	.num_distinct_frames = SHP_UNUSED,
      },
      {
	.num_distinct_frames = SHP_UNUSED,
      },
    },
    .stages =
    {
      { // FOREST0
	.item_type = ITEM_BLASTOLA_COLA,
	.item_y = 14,
	.item_x = 12,
	.exit_l = EXIT_UNUSED,
	.exit_r = 1,
	.doors =
	{
	  {
	    .y = 12,
	    .x = 12,
	    .target_level = 6,
	    .target_stage = 0,
	  },
	  {
	    .y = DOOR_UNUSED,
	    .x = DOOR_UNUSED,
	  },
	  {
	    .y = DOOR_UNUSED,
	    .x = DOOR_UNUSED,
	  },
	},
	.enemies =
	{
	  {
	    .shp_index = 0,
	    .behavior = ENEMY_BEHAVIOR_BOUNCE,
	  },
	  {
	    .shp_index = 0,
	    .behavior = ENEMY_BEHAVIOR_BOUNCE,
	  },
	  {
	    .behavior = ENEMY_BEHAVIOR_UNUSED,
	  },
	  {
	    .behavior = ENEMY_BEHAVIOR_UNUSED,
	  },
	},
      },
      { // FOREST1
	.item_type = ITEM_SHIELD,
	.item_y = 10,
	.item_x = 118,
	.exit_l = 0,
	.exit_r = 2,
	.doors =
	{
	  {
	    .y = DOOR_UNUSED,
	    .x = DOOR_UNUSED,
	  },
	  {
	    .y = DOOR_UNUSED,
	    .x = DOOR_UNUSED,
	  },
	  {
	    .y = DOOR_UNUSED,
	    .x = DOOR_UNUSED,
	  },
	},
	.enemies =
	{
	  {
	    .shp_index = 0,
	    .behavior = ENEMY_BEHAVIOR_BOUNCE,
	  },
	  {
	    .shp_index = 0,
	    .behavior = ENEMY_BEHAVIOR_BOUNCE,
	  },
	  {
	    .behavior = ENEMY_BEHAVIOR_UNUSED,
	  },
	  {
	    .shp_index = 1,
	    .behavior = ENEMY_BEHAVIOR_SHY,
	  },
	},
      },
      { // FOREST2
	.item_type = ITEM_DOOR_KEY,
	.item_y = 2,
	.item_x = 160,
	.exit_l = 1,
	.exit_r = EXIT_UNUSED,
	.doors =
	{
	  {
	    .y = 12,
	    .x = 238,
	    .target_level = 0,
	    .target_stage = 0,
	  },
	  {
	    .y = 14,
	    .x = 160,
	    .target_level = 7,
	    .target_stage = 2,
	  },
	  {
	    .y = DOOR_UNUSED,
	    .x = DOOR_UNUSED,
	  },
	},
	.enemies =
	{
	  {
	    .shp_index = 0,
	    .behavior = ENEMY_BEHAVIOR_BOUNCE,
	  },
	  {
	    .shp_index = 1,
	    .behavior = ENEMY_BEHAVIOR_SHY,
	  },
	  {
	    .shp_index = 0,
	    .behavior = ENEMY_BEHAVIOR_BOUNCE,
	  },
	  {
	    .shp_index = 1,
	    .behavior = ENEMY_BEHAVIOR_SHY,
	  },
	},
      },
    },
  };
level LEVEL_DATA_SPACE =
  {
    .tt2_filename = "SPACE.TT2",
    .pt0_filename = "SPACE0.PT",
    .pt1_filename = "SPACE1.PT",
    .pt2_filename = "SPACE2.PT",
    .door_tile_ul = 51,
    .door_tile_ur = 52,
    .door_tile_ll = 51,
    .door_tile_lr = 52,
    .shps =
    {
      {
	.num_distinct_frames = 4,
	.horizontal = ENEMY_HORIZONTAL_DUPLICATED,
	.animation = ENEMY_ANIMATION_LOOP,
	.filename = "ROCK.SHP",
      },
      {
	.num_distinct_frames = 4,
	.horizontal = ENEMY_HORIZONTAL_DUPLICATED,
	.animation = ENEMY_ANIMATION_LOOP,
	.filename = "SAUCER.SHP",
      },
      {
	.num_distinct_frames = SHP_UNUSED,
      },
      {
	.num_distinct_frames = SHP_UNUSED,
      },
    },
    .stages =
    {
      { // SPACE0
	.item_type = ITEM_BLASTOLA_COLA,
	.item_y = 16,
	.item_x = 10,
	.exit_l = EXIT_UNUSED,
	.exit_r = 1,
	.doors =
	{
	  {
	    .y = 12,
	    .x = 2,
	    .target_level = 0,
	    .target_stage = 2,
	  },
	  {
	    .y = DOOR_UNUSED,
	    .x = DOOR_UNUSED,
	  },
	  {
	    .y = DOOR_UNUSED,
	    .x = DOOR_UNUSED,
	  },
	},
	.enemies =
	{
	  {
	    .shp_index = 0,
	    .behavior = ENEMY_BEHAVIOR_BOUNCE,
	  },
	  {
	    .shp_index = 0,
	    .behavior = ENEMY_BEHAVIOR_BOUNCE,
	  },
	  {
	    .shp_index = 0,
	    .behavior = ENEMY_BEHAVIOR_BOUNCE,
	  },
	  {
	    .shp_index = 0,
	    .behavior = ENEMY_BEHAVIOR_BOUNCE,
	  },
	},
      },
      { // SPACE1
	.item_type = ITEM_SHIELD,
	.item_y = 8,
	.item_x = 114,
	.exit_l = 0,
	.exit_r = 2,
	.doors =
	{
	  {
	    .y = DOOR_UNUSED,
	    .x = DOOR_UNUSED,
	  },
	  {
	    .y = DOOR_UNUSED,
	    .x = DOOR_UNUSED,
	  },
	  {
	    .y = DOOR_UNUSED,
	    .x = DOOR_UNUSED,
	  },
	},
	.enemies =
	{
	  {
	    .shp_index = 0,
	    .behavior = ENEMY_BEHAVIOR_BOUNCE,
	  },
	  {
	    .shp_index = 0,
	    .behavior = ENEMY_BEHAVIOR_BOUNCE,
	  },
	  {
	    .shp_index = 0,
	    .behavior = ENEMY_BEHAVIOR_BOUNCE,
	  },
	  {
	    .shp_index = 1,
	    .behavior = ENEMY_BEHAVIOR_BOUNCE,
	  },
	},
      },
      { // SPACE2
	.item_type = ITEM_GEMS,
	.item_y = 6,
	.item_x = 198,
	.exit_l = 1,
	.exit_r = EXIT_UNUSED,
	.doors =
	{
	  {
	    .y = 12,
	    .x = 228,
	    .target_level = 3,
	    .target_stage = 0,
	  },
	  {
	    .y = DOOR_UNUSED,
	    .x = DOOR_UNUSED,
	  },
	  {
	    .y = DOOR_UNUSED,
	    .x = DOOR_UNUSED,
	  },
	},
	.enemies =
	{
	  {
	    .shp_index = 0,
	    .behavior = ENEMY_BEHAVIOR_BOUNCE,
	  },
	  {
	    .shp_index = 0,
	    .behavior = ENEMY_BEHAVIOR_BOUNCE,
	  },
	  {
	    .shp_index = 1,
	    .behavior = ENEMY_BEHAVIOR_BOUNCE,
	  },
	  {
	    .shp_index = 1,
	    .behavior = ENEMY_BEHAVIOR_BOUNCE | ENEMY_BEHAVIOR_FAST,
	  },
	},
      },
    },
  };

level LEVEL_DATA_BASE =
  {
    .tt2_filename = "BASE.TT2",
    .pt0_filename = "BASE0.PT",
    .pt1_filename = "BASE1.PT",
    .pt2_filename = "BASE2.PT",
    .door_tile_ul = 9, 
    .door_tile_ur = 10,
    .door_tile_ll = 11,
    .door_tile_lr = 12,
    .shps =
    {
      {
	.num_distinct_frames = 3,
	.horizontal = ENEMY_HORIZONTAL_DUPLICATED,
	.animation = ENEMY_ANIMATION_ALTERNATE,
	.filename = "BUG.SHP",
      },
      {
	.num_distinct_frames = 4,
	.horizontal = ENEMY_HORIZONTAL_DUPLICATED,
	.animation = ENEMY_ANIMATION_LOOP,
	.filename = "GLOBE.SHP",
      },
      {
	.num_distinct_frames = SHP_UNUSED,
      },
      {
	.num_distinct_frames = SHP_UNUSED,
      },
    },
    .stages =
    {
      { // BASE0
	.item_type = ITEM_SHIELD,
	.item_y = 4,
	.item_x = 252,
	.exit_l = 1,
	.exit_r = 2,
	.doors =
	{
	  {
	    .y = 14,
	    .x = 240,
	    .target_level = 3,
	    .target_stage = 2,
	  },
	  {
	    .y = 14,
	    .x = 114,
	    .target_level = 3,
	    .target_stage = 1,
	  },
	  {
	    .y = 8,
	    .x = 138,
	    .target_level = 2,
	    .target_stage = 2,
	  },
	},
	.enemies =
	{
	  {
	    .shp_index = 0,
	    .behavior = ENEMY_BEHAVIOR_LEAP,
	  },
	  {
	    .shp_index = 0,
	    .behavior = ENEMY_BEHAVIOR_LEAP,
	  },
	  {
	    .shp_index = 0,
	    .behavior = ENEMY_BEHAVIOR_LEAP,
	  },
	  {
	    .shp_index = 1,
	    .behavior = ENEMY_BEHAVIOR_ROLL,
	  },
	},
      },
      { // BASE1
	.item_type = ITEM_CORKSCREW,
	.item_y = 16,
	.item_x = 0,
	.exit_l = EXIT_UNUSED,
	.exit_r = 0,
	.doors =
	{
	  {
	    .y = 6,
	    .x = 0,
	    .target_level = 0,
	    .target_stage = 2,
	  },
	  {
	    .y = 14,
	    .x = 112,
	    .target_level = 3,
	    .target_stage = 0,
	  },
	  {
	    .y = 0,
	    .x = 0,
	    .target_level = 3,
	    .target_stage = 2,
	  },
	},
	.enemies =
	{
	  {
	    .shp_index = 0,
	    .behavior = ENEMY_BEHAVIOR_LEAP,
	  },
	  {
	    .shp_index = 0,
	    .behavior = ENEMY_BEHAVIOR_LEAP,
	  },
	  {
	    .shp_index = 0,
	    .behavior = ENEMY_BEHAVIOR_LEAP,
	  },
	  {
	    .shp_index = 1,
	    .behavior = ENEMY_BEHAVIOR_ROLL,
	  },
	},
      },
      { // BASE2
	.item_type = ITEM_BOOTS,
	.item_y = 16,
	.item_x = 230,
	.exit_l = 0,
	.exit_r = EXIT_UNUSED,
	.doors =
	{
	  {
	    .y = 2,
	    .x = 36,
	    .target_level = 3,
	    .target_stage = 0,
	  },
	  {
	    .y = 14,
	    .x = 218,
	    .target_level = 3,
	    .target_stage = 1,
	  },
	  {
	    .y = DOOR_UNUSED,
	    .x = DOOR_UNUSED,
	  },
	},
	.enemies =
	{
	  {
	    .shp_index = 0,
	    .behavior = ENEMY_BEHAVIOR_LEAP,
	  },
	  {
	    .shp_index = 0,
	    .behavior = ENEMY_BEHAVIOR_LEAP,
	  },
	  {
	    .shp_index = 0,
	    .behavior = ENEMY_BEHAVIOR_LEAP,
	  },
	  {
	    .shp_index = 1,
	    .behavior = ENEMY_BEHAVIOR_ROLL | ENEMY_BEHAVIOR_FAST,
	  },
	},
      },
    },
  };

level LEVEL_DATA_CAVE =
  {
    .tt2_filename = "CAVE.TT2",
    .pt0_filename = "CAVE0.PT",
    .pt1_filename = "CAVE1.PT",
    .pt2_filename = "CAVE2.PT",
    .door_tile_ul = 5, 
    .door_tile_ur = 5,
    .door_tile_ll = 5,
    .door_tile_lr = 5,
    .shps =
    {
      {
	.num_distinct_frames = 3,
	.horizontal = ENEMY_HORIZONTAL_DUPLICATED,
	.animation = ENEMY_ANIMATION_ALTERNATE,
	.filename = "FROG.SHP",
      },
      {
	.num_distinct_frames = 3,
	.horizontal = ENEMY_HORIZONTAL_SEPARATE,
	.animation = ENEMY_ANIMATION_ALTERNATE,
	.filename = "BEE.SHP",
      },
      {
	.num_distinct_frames = SHP_UNUSED,
      },
      {
	.num_distinct_frames = SHP_UNUSED,
      },
    },
    .stages =
    {
      { // CAVE0
	.item_type = ITEM_SHIELD,
	.item_y = 6,
	.item_x = 41,
	.exit_l = EXIT_UNUSED,
	.exit_r = 1,
	.doors =
	{
	  {
	    .y = 12,
	    .x = 8,
	    .target_level = 0,
	    .target_stage = 2,
	  },
	  {
	    .y = 4,
	    .x = 40,
	    .target_level = 4,
	    .target_stage = 1,
	  },
	  {
	    .y = 2,
	    .x = 154,
	    .target_level = 4,
	    .target_stage = 2,
	  },
	},
	.enemies =
	{
	  {
	    .shp_index = 0,
	    .behavior = ENEMY_BEHAVIOR_LEAP,
	  },
	  {
	    .shp_index = 0,
	    .behavior = ENEMY_BEHAVIOR_LEAP,
	  },
	  {
	    .shp_index = 0,
	    .behavior = ENEMY_BEHAVIOR_LEAP,
	  },
	  {
	    .shp_index = 1,
	    .behavior = ENEMY_BEHAVIOR_SEEK,
	  },
	},
      },
      { // CAVE1
	.item_type = ITEM_GOLD,
	.item_y = 4,
	.item_x = 228,
	.exit_l = 0,
	.exit_r = 2,
	.doors =
	{
	  {
	    .y = 14,
	    .x = 236,
	    .target_level = 4,
	    .target_stage = 0,
	  },
	  {
	    .y = DOOR_UNUSED,
	    .x = DOOR_UNUSED,
	  },
	  {
	    .y = DOOR_UNUSED,
	    .x = DOOR_UNUSED,
	  },
	},
	.enemies =
	{
	  {
	    .shp_index = 0,
	    .behavior = ENEMY_BEHAVIOR_LEAP,
	  },
	  {
	    .shp_index = 0,
	    .behavior = ENEMY_BEHAVIOR_LEAP,
	  },
	  {
	    .shp_index = 1,
	    .behavior = ENEMY_BEHAVIOR_SEEK,
	  },
	  {
	    .shp_index = 1,
	    .behavior = ENEMY_BEHAVIOR_SEEK,
	  },
	},
      },
      { // CAVE2
	.item_type = ITEM_TELEPORT_WAND,
	.item_y = 10,
	.item_x = 64,
	.exit_l = 1,
	.exit_r = EXIT_UNUSED,
	.doors =
	{
	  {
	    .y = 14,
	    .x = 236,
	    .target_level = 4,
	    .target_stage = 0,
	  },
	  {
	    .y = DOOR_UNUSED,
	    .x = DOOR_UNUSED,
	  },
	  {
	    .y = DOOR_UNUSED,
	    .x = DOOR_UNUSED,
	  },
	},
	.enemies =
	{
	  {
	    .shp_index = 0,
	    .behavior = ENEMY_BEHAVIOR_LEAP,
	  },
	  {
	    .shp_index = 0,
	    .behavior = ENEMY_BEHAVIOR_LEAP | ENEMY_BEHAVIOR_FAST,
	  },
	  {
	    .shp_index = 1,
	    .behavior = ENEMY_BEHAVIOR_SEEK,
	  },
	  {
	    .shp_index = 1,
	    .behavior = ENEMY_BEHAVIOR_SEEK,
	  },
	},
      },
    },
  };
level LEVEL_DATA_SHED =
  {
    .tt2_filename = "SHED.TT2",
    .pt0_filename = "SHED0.PT",
    .pt1_filename = "SHED1.PT",
    .pt2_filename = "SHED2.PT",
    .door_tile_ul = 10, 
    .door_tile_ur = 11,
    .door_tile_ll = 10,
    .door_tile_lr = 11,
    .shps =
    {
      {
	.num_distinct_frames = 3,
	.horizontal = ENEMY_HORIZONTAL_SEPARATE,
	.animation = ENEMY_ANIMATION_ALTERNATE,
	.filename = "BIRD.SHP",
      },
      {
	.num_distinct_frames = 3,
	.horizontal = ENEMY_HORIZONTAL_SEPARATE,
	.animation = ENEMY_ANIMATION_ALTERNATE,
	.filename = "BEE.SHP",
      },
      {
	.num_distinct_frames = 4,
	.horizontal = ENEMY_HORIZONTAL_DUPLICATED,
	.animation = ENEMY_ANIMATION_LOOP,
	.filename = "BALL.SHP",
      },
      {
	.num_distinct_frames = SHP_UNUSED,
      },
    },
    .stages =
    {
      { // SHED0
	.item_type = ITEM_SHIELD,
	.item_y = 16,
	.item_x = 164,
	.exit_l = EXIT_UNUSED,
	.exit_r = 1,
	.doors =
	{
	  {
	    .y = 12,
	    .x = 4,
	    .target_level = 0,
	    .target_stage = 0,
	  },
	  {
	    .y = DOOR_UNUSED,
	    .x = DOOR_UNUSED,
	  },
	  {
	    .y = DOOR_UNUSED,
	    .x = DOOR_UNUSED,
	  },
	},
	.enemies =
	{
	  {
	    .shp_index = 0,
	    .behavior = ENEMY_BEHAVIOR_BOUNCE,
	  },
	  {
	    .shp_index = 0,
	    .behavior = ENEMY_BEHAVIOR_BOUNCE,
	  },
	  {
	    .shp_index = 1,
	    .behavior = ENEMY_BEHAVIOR_SEEK,
	  },
	  {
	    .shp_index = 2,
	    .behavior = ENEMY_BEHAVIOR_LEAP,
	  },
	},
      },
      { // SHED1
	.item_type = ITEM_BLASTOLA_COLA,
	.item_y = 4,
	.item_x = 250,
	.exit_l = 0,
	.exit_r = EXIT_UNUSED,
	.doors =
	{
	  {
	    .y = 4,
	    .x = 240,
	    .target_level = 5,
	    .target_stage = 2,
	  },
	  {
	    .y = DOOR_UNUSED,
	    .x = DOOR_UNUSED,
	  },
	  {
	    .y = DOOR_UNUSED,
	    .x = DOOR_UNUSED,
	  },
	},
	.enemies =
	{
	  {
	    .shp_index = 0,
	    .behavior = ENEMY_BEHAVIOR_BOUNCE,
	  },
	  {
	    .shp_index = 1,
	    .behavior = ENEMY_BEHAVIOR_SEEK,
	  },
	  {
	    .shp_index = 2,
	    .behavior = ENEMY_BEHAVIOR_LEAP,
	  },
	  {
	    .shp_index = 2,
	    .behavior = ENEMY_BEHAVIOR_LEAP,
	  },
	},
      },
      { // SHED2
	.item_type = ITEM_SHIELD,
	.item_y = 10,
	.item_x = 246,
	.exit_l = EXIT_UNUSED,
	.exit_r = EXIT_UNUSED,
	.doors =
	{
	  {
	    .y = 14,
	    .x = 4,
	    .target_level = 5,
	    .target_stage = 1,
	  },
	  {
	    .y = 8,
	    .x = 242,
	    .target_level = 7,
	    .target_stage = 0,
	  },
	  {
	    .y = DOOR_UNUSED,
	    .x = DOOR_UNUSED,
	  },
	},
	.enemies =
	{
	  {
	    .shp_index = 0,
	    .behavior = ENEMY_BEHAVIOR_BOUNCE,
	  },
	  {
	    .shp_index = 1,
	    .behavior = ENEMY_BEHAVIOR_SEEK,
	  },
	  {
	    .shp_index = 2,
	    .behavior = ENEMY_BEHAVIOR_LEAP,
	  },
	  {
	    .shp_index = 2,
	    .behavior = ENEMY_BEHAVIOR_LEAP | ENEMY_BEHAVIOR_FAST,
	  },
	},
      },
    },
  };

level LEVEL_DATA_CASTLE =
  {
    .tt2_filename = "CASTLE.TT2",
    .pt0_filename = "CASTLE0.PT",
    .pt1_filename = "CASTLE1.PT",
    .pt2_filename = "CASTLE2.PT",
    .door_tile_ul = 26, 
    .door_tile_ur = 27,
    .door_tile_ll = 26,
    .door_tile_lr = 27,
    .shps =
    {
      {
	.num_distinct_frames = 3,
	.horizontal = ENEMY_HORIZONTAL_SEPARATE,
	.animation = ENEMY_ANIMATION_ALTERNATE,
	.filename = "BIRD.SHP",
      },
      {
	.num_distinct_frames = 4,
	.horizontal = ENEMY_HORIZONTAL_DUPLICATED,
	.animation = ENEMY_ANIMATION_LOOP,
	.filename = "BALL.SHP",
      },
      {
	.num_distinct_frames = 4,
	.horizontal = ENEMY_HORIZONTAL_DUPLICATED,
	.animation = ENEMY_ANIMATION_LOOP,
	.filename = "CUBE.SHP",
      },
      {
	.num_distinct_frames = 3,
	.horizontal = ENEMY_HORIZONTAL_SEPARATE,
	.animation = ENEMY_ANIMATION_ALTERNATE,
	.filename = "BEE.SHP",
      },
    },
    .stages =
    {
      { // CASTLE0
	.item_type = ITEM_CROWN,
	.item_y = 2,
	.item_x = 244,
	.exit_l = EXIT_UNUSED,
	.exit_r = EXIT_UNUSED,
	.doors =
	{
	  {
	    .y = 14,
	    .x = 246,
	    .target_level = 1,
	    .target_stage = 0,
	  },
	  {
	    .y = 4,
	    .x = 228,
	    .target_level = 6,
	    .target_stage = 2,
	  },
	  {
	    .y = 8,
	    .x = 8,
	    .target_level = 6,
	    .target_stage = 1,
	  },
	},
	.enemies =
	{
	  {
	    .shp_index = 0,
	    .behavior = ENEMY_BEHAVIOR_BOUNCE | ENEMY_BEHAVIOR_FAST,
	  },
	  {
	    .shp_index = 1,
	    .behavior = ENEMY_BEHAVIOR_LEAP,
	  },
	  {
	    .shp_index = 1,
	    .behavior = ENEMY_BEHAVIOR_LEAP,
	  },
	  {
	    .shp_index = 3,
	    .behavior = ENEMY_BEHAVIOR_SEEK,
	  },
	},
      },
      { // CASTLE1
	.item_type = ITEM_SHIELD,
	.item_y = 14,
	.item_x = 66,
	.exit_l = EXIT_UNUSED,
	.exit_r = EXIT_UNUSED,
	.doors =
	{
	  {
	    .y = 14,
	    .x = 8,
	    .target_level = 6,
	    .target_stage = 0,
	  },
	  {
	    .y = 2,
	    .x = 8,
	    .target_level = 6,
	    .target_stage = 2,
	  },
	  {
	    .y = DOOR_UNUSED,
	    .x = DOOR_UNUSED,
	  },
	},
	.enemies =
	{
	  {
	    .shp_index = 0,
	    .behavior = ENEMY_BEHAVIOR_BOUNCE | ENEMY_BEHAVIOR_FAST,
	  },
	  {
	    .shp_index = 1,
	    .behavior = ENEMY_BEHAVIOR_LEAP,
	  },
	  {
	    .shp_index = 1,
	    .behavior = ENEMY_BEHAVIOR_LEAP | ENEMY_BEHAVIOR_FAST,
	  },
	  {
	    .shp_index = 2,
	    .behavior = ENEMY_BEHAVIOR_SHY,
	  },
	},
      },
      { // CASTLE2
	.item_type = ITEM_SHIELD,
	.item_y = 8,
	.item_x = 44,
	.exit_l = EXIT_UNUSED,
	.exit_r = EXIT_UNUSED,
	.doors =
	{
	  {
	    .y = 8,
	    .x = 8,
	    .target_level = 6,
	    .target_stage = 1,
	  },
	  {
	    .y = 4,
	    .x = 246,
	    .target_level = 6,
	    .target_stage = 0,
	  },
	  {
	    .y = DOOR_UNUSED,
	    .x = DOOR_UNUSED,
	  },
	},
	.enemies =
	{
	  {
	    .shp_index = 1,
	    .behavior = ENEMY_BEHAVIOR_LEAP,
	  },
	  {
	    .shp_index = 2,
	    .behavior = ENEMY_BEHAVIOR_SHY | ENEMY_BEHAVIOR_FAST,
	  },
	  {
	    .shp_index = 3,
	    .behavior = ENEMY_BEHAVIOR_SEEK,
	  },
	  {
	    .shp_index = 3,
	    .behavior = ENEMY_BEHAVIOR_SEEK | ENEMY_BEHAVIOR_FAST,
	  },
	},
      },
    },
  };
level LEVEL_DATA_COMP =
  {
    .tt2_filename = "COMP.TT2",
    .pt0_filename = "COMP0.PT",
    .pt1_filename = "COMP1.PT",
    .pt2_filename = "COMP2.PT",
    .door_tile_ul = 2, 
    .door_tile_ur = 3,
    .door_tile_ll = 4,
    .door_tile_lr = 5,
    .shps =
    {
      {
	.num_distinct_frames = 4,
	.horizontal = ENEMY_HORIZONTAL_DUPLICATED,
	.animation = ENEMY_ANIMATION_LOOP,
	.filename = "STAR1.SHP",
      },
      {
	.num_distinct_frames = 4,
	.horizontal = ENEMY_HORIZONTAL_DUPLICATED,
	.animation = ENEMY_ANIMATION_LOOP,
	.filename = "STAR2.SHP",
      },
      {
	.num_distinct_frames = 4,
	.horizontal = ENEMY_HORIZONTAL_DUPLICATED,
	.animation = ENEMY_ANIMATION_ALTERNATE,
	.filename = "STAR3.SHP",
      },
      {
	.num_distinct_frames = SHP_UNUSED,
      },
    },
    .stages =
    {
      { // COMP0
	.item_type = ITEM_SHIELD,
	.item_y = 2,
	.item_x = 140,
	.exit_l = EXIT_UNUSED,
	.exit_r = 1,
	.doors =
	{
	  {
	    .y = 8,
	    .x = 6,
	    .target_level = 5,
	    .target_stage = 2,
	  },
	  {
	    .y = DOOR_UNUSED,
	    .x = DOOR_UNUSED,
	  },
	  {
	    .y = DOOR_UNUSED,
	    .x = DOOR_UNUSED,
	  },
	},
	.enemies =
	{
	  {
	    .shp_index = 0,
	    .behavior = ENEMY_BEHAVIOR_BOUNCE,
	  },
	  {
	    .shp_index = 0,
	    .behavior = ENEMY_BEHAVIOR_BOUNCE,
	  },
	  {
	    .shp_index = 0,
	    .behavior = ENEMY_BEHAVIOR_BOUNCE,
	  },
	  {
	    .behavior = ENEMY_BEHAVIOR_UNUSED,
	  },
	},
      },
      { // COMP1
	.item_type = ITEM_SHIELD,
	.item_y = 10,
	.item_x = 70,
	.exit_l = 0,
	.exit_r = 2,
	.doors =
	{
	  {
	    .y = DOOR_UNUSED,
	    .x = DOOR_UNUSED,
	  },
	  {
	    .y = DOOR_UNUSED,
	    .x = DOOR_UNUSED,
	  },
	  {
	    .y = DOOR_UNUSED,
	    .x = DOOR_UNUSED,
	  },
	},
	.enemies =
	{
	  {
	    .shp_index = 0,
	    .behavior = ENEMY_BEHAVIOR_BOUNCE | ENEMY_BEHAVIOR_FAST,
	  },
	  {
	    .shp_index = 0,
	    .behavior = ENEMY_BEHAVIOR_BOUNCE | ENEMY_BEHAVIOR_FAST,
	  },
	  {
	    .shp_index = 0,
	    .behavior = ENEMY_BEHAVIOR_BOUNCE | ENEMY_BEHAVIOR_FAST,
	  },
	  {
	    .behavior = ENEMY_BEHAVIOR_UNUSED,
	  },
	},
      },
      { // COMP2
	.item_type = ITEM_LANTERN,
	.item_y = 2,
	.item_x = 166,
	.exit_l = 1,
	.exit_r = EXIT_UNUSED,
	.doors =
	{
	  {
	    .y = 14,
	    .x = 244,
	    .target_level = 1,
	    .target_stage = 2,
	  },
	  {
	    .y = DOOR_UNUSED,
	    .x = DOOR_UNUSED,
	  },
	  {
	    .y = DOOR_UNUSED,
	    .x = DOOR_UNUSED,
	  },
	},
	.enemies =
	{
	  {
	    .shp_index = 0,
	    .behavior = ENEMY_BEHAVIOR_BOUNCE | ENEMY_BEHAVIOR_FAST,
	  },
	  {
	    .shp_index = 0,
	    .behavior = ENEMY_BEHAVIOR_BOUNCE | ENEMY_BEHAVIOR_FAST,
	  },
	  {
	    .shp_index = 0,
	    .behavior = ENEMY_BEHAVIOR_BOUNCE | ENEMY_BEHAVIOR_FAST,
	  },
	  {
	    .behavior = ENEMY_BEHAVIOR_UNUSED,
	  },
	},
      },
    },
  };
#endif
