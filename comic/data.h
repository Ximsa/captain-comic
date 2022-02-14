#ifndef DATA_H
#define DATA_H

#include <stdint.h>
#include "constants.h"

uint8_t colors[][3] =
  {
    {0x00, 0x00, 0x00}, /*  0 */
    {0x00, 0x00, 0xaa}, /*  1 */
    {0x00, 0xaa, 0x00}, /*  2 */
    {0x00, 0xaa, 0xaa}, /*  3 */
    {0xaa, 0x00, 0x00}, /*  4 */
    {0xaa, 0x00, 0xaa}, /*  5 */
    {0xaa, 0x55, 0x00}, /*  6 */
    {0xaa, 0xaa, 0xaa}, /*  7 */
    {0x55, 0x55, 0x55}, /*  8 */
    {0x55, 0x55, 0xff}, /*  9 */
    {0x55, 0xff, 0x55}, /* 10 */
    {0x55, 0xff, 0xff}, /* 11 */
    {0xff, 0x55, 0x55}, /* 12 */
    {0xff, 0x55, 0xff}, /* 13 */
    {0xff, 0xff, 0x55}, /* 14 */
    {0xff, 0xff, 0xff}, /* 15 */
  };

// source_door_level_number and source_door_stage_number are set to the
// level/stage we just came from, if we are entering the current stage via a
// door. The special value source_door_level_number == -1 means that we are
// entering this stage at a left/right boundary, not via a door. The special
// value source_door_level_number == -2 is set only at the start of the game and
// means we are entering the stage by beaming in to the planet's surface.

int8_t source_door_level_number	=	-2;
uint8_t source_door_stage_number	=	0;
uint8_t current_level_number	=	LEVEL_NUMBER_FOREST;
uint8_t current_stage_number	=	0;
int8_t comic_y			=	0;
uint8_t comic_x			=	0;
int16_t camera_x		=	0;
uint8_t comic_num_lives		=	0;
uint8_t comic_hp		=	0;
uint8_t comic_firepower		=	0;// how many Blastola Colas Comic has collected
uint8_t fireball_meter		=	0;
uint8_t comic_jump_power	=	4;
uint8_t comic_has_corkscrew	=	0;
uint8_t comic_has_door_key	=	0;
uint8_t comic_has_lantern	=	0;
uint8_t comic_has_teleport_wand	=	0;
uint8_t comic_has_gems		=	0;
uint8_t comic_has_gold		=	0;
uint8_t comic_has_crown		=	0;
uint8_t comic_num_treasures	=	0;
double fitness = 0;
// The score is an array of 3 bytes, stored in base-100 representation. score[0]
// is the least significant digit. The number stored here one one-hundredth of
// the score shown to the player, which always has a "00" appended to the end.
uint8_t score[]			=	{0, 0, 0};
uint8_t score_10000_counter	=	0;

// Array of booleans indicating whether the item in each stage has been
// collected. Index as: items_collected[stage*16 + level]. Only the first 8
// elements in each row are used.)
uint8_t items_collected[8][3]	=	{0};

#define STARTUP_NOTICE_TEXT "The Adventures of Captain Comic"/*\r\nCopyright (c) 1988 by Michael Denio\r\n"*/

#define TERMINATE_PROGRAM_TEXT ""


uint8_t graphics_enabled = 1;
uint8_t skip_intro = 0;
int32_t speed = 2;
// little trick: replace filename with image data later, autoconvert to 1 Byte per Pixel
uint8_t GRAPHICS_COMIC[][16*32*4] =
  {
    "graphics/comic_standing_right_16x32m.ega",
    "graphics/comic_running_1_right_16x32m.ega",
    "graphics/comic_running_2_right_16x32m.ega",
    "graphics/comic_running_3_right_16x32m.ega",
    "graphics/comic_jumping_right_16x32m.ega",
    "graphics/comic_standing_left_16x32m.ega",
    "graphics/comic_running_1_left_16x32m.ega",
    "graphics/comic_running_2_left_16x32m.ega",
    "graphics/comic_running_3_left_16x32m.ega",
    "graphics/comic_jumping_left_16x32m.ega",
  };


uint8_t GRAPHIC_FIREBALL_0[16*8*4] = "graphics/fireball_0_16x8m.ega";
uint8_t GRAPHIC_FIREBALL_1[16*8*4] = "graphics/fireball_1_16x8m.ega";

uint8_t GRAPHIC_WHITE_SPARK_0[16*16*4] = "graphics/white_spark_0_16x16m.ega";
uint8_t GRAPHIC_WHITE_SPARK_1[16*16*4] = "graphics/white_spark_1_16x16m.ega";
uint8_t GRAPHIC_WHITE_SPARK_2[16*16*4] = "graphics/white_spark_2_16x16m.ega";

uint8_t GRAPHIC_RED_SPARK_0[16*16*4] = "graphics/red_spark_0_16x16m.ega";
uint8_t GRAPHIC_RED_SPARK_1[16*16*4] = "graphics/red_spark_1_16x16m.ega";
uint8_t GRAPHIC_RED_SPARK_2[16*16*4] = "graphics/red_spark_2_16x16m.ega";

uint8_t ANIMATION_COMIC_DEATH[][16*32*4] =
  {
    "graphics/comic_death_0_16x32m.ega",
    "graphics/comic_death_1_16x32m.ega",
    "graphics/comic_death_2_16x32m.ega",
    "graphics/comic_death_3_16x32m.ega",
    "graphics/comic_death_4_16x32m.ega",
    "graphics/comic_death_5_16x32m.ega",
    "graphics/comic_death_6_16x32m.ega",
    "graphics/comic_death_7_16x32m.ega",
  };

uint8_t GRAPHIC_TELEPORT_0[16*32*4] = "graphics/teleport_0_16x32m.ega";
uint8_t GRAPHIC_TELEPORT_1[16*32*4] = "graphics/teleport_1_16x32m.ega";
uint8_t GRAPHIC_TELEPORT_2[16*32*4] = "graphics/teleport_2_16x32m.ega";

uint8_t ANIMATION_MATERIALIZE[][16*32*4] =
  {
    "graphics/materialize_0_16x32m.ega",
    "graphics/materialize_1_16x32m.ega",
    "graphics/materialize_2_16x32m.ega",
    "graphics/materialize_3_16x32m.ega",
    "graphics/materialize_4_16x32m.ega",
    "graphics/materialize_5_16x32m.ega",
    "graphics/materialize_6_16x32m.ega",
    "graphics/materialize_7_16x32m.ega",
    "graphics/materialize_8_16x32m.ega",
    "graphics/materialize_9_16x32m.ega",
    "graphics/materialize_10_16x32m.ega",
    "graphics/materialize_11_16x32m.ega",
  };

uint8_t* ANIMATION_TABLE_FIREBALL[] ={GRAPHIC_FIREBALL_0,GRAPHIC_FIREBALL_1};

// Entries 0..5 of this table describe the animation of the white spark caused
// by a fireball hitting an enemy. Entries 6..10 describe the animation of the
// red spark caused by an enemy hitting Comic. The tables are indexed by
// enemy.state - 2, when enemy.state >= 2.
uint8_t* ANIMATION_TABLE_SPARKS[] = 
  {
    GRAPHIC_WHITE_SPARK_0,
    GRAPHIC_WHITE_SPARK_1,
    GRAPHIC_WHITE_SPARK_2,
    GRAPHIC_WHITE_SPARK_1,
    GRAPHIC_WHITE_SPARK_0,
    GRAPHIC_WHITE_SPARK_0,	// not actually part of the animation; a dummy sentinel slot
    
    GRAPHIC_RED_SPARK_0,
    GRAPHIC_RED_SPARK_1,
    GRAPHIC_RED_SPARK_2,
    GRAPHIC_RED_SPARK_1,
    GRAPHIC_RED_SPARK_0,
    
    GRAPHIC_TELEPORT_0,
    GRAPHIC_TELEPORT_1,
    GRAPHIC_TELEPORT_2,
    GRAPHIC_TELEPORT_1,
    GRAPHIC_TELEPORT_0,
  };

uint8_t ** ANIMATION_TABLE_WHITE_SPARK = ANIMATION_TABLE_SPARKS;
uint8_t ** ANIMATION_TABLE_RED_SPARK = ANIMATION_TABLE_SPARKS + 6;
uint8_t ** ANIMATION_TABLE_TELEPORT = ANIMATION_TABLE_SPARKS + 11;

// Here starts a block of graphics that each have a counterpart graphic at a
// fixed offset. "Counterpart graphic" means, for example, the odd frame of an
// item animation, or the dark version of the life icon.
// NOTE: we don't do this

//GRAPHICS_ITEMS_EVEN_FRAMES:
uint8_t GRAPHIC_CORKSCREW_EVEN[16*16*4] = "graphics/corkscrew_even_16x16m.ega";
uint8_t GRAPHIC_DOOR_KEY_EVEN[16*16*4] = "graphics/door_key_even_16x16m.ega";
uint8_t GRAPHIC_BOOTS_EVEN[16*16*4] = "graphics/boots_even_16x16m.ega";
uint8_t GRAPHIC_LANTERN_EVEN[16*16*4] = "graphics/lantern_even_16x16m.ega";
uint8_t GRAPHIC_TELEPORT_WAND_EVEN[16*16*4] = "graphics/teleport_wand_even_16x16m.ega";
uint8_t GRAPHIC_GEMS_EVEN[16*16*4] = "graphics/gems_even_16x16m.ega";
uint8_t GRAPHIC_CROWN_EVEN[16*16*4] = "graphics/crown_even_16x16m.ega";
uint8_t GRAPHIC_GOLD_EVEN[16*16*4] = "graphics/gold_even_16x16m.ega";
uint8_t GRAPHIC_BLASTOLA_COLA_EVEN[][16*16*4] =
  {
    "graphics/blastola_cola_even_16x16m.ega",
    "graphics/blastola_cola_inventory_1_even_16x16m.ega",
    "graphics/blastola_cola_inventory_2_even_16x16m.ega",
    "graphics/blastola_cola_inventory_3_even_16x16m.ega",
    "graphics/blastola_cola_inventory_4_even_16x16m.ega",
    "graphics/blastola_cola_inventory_5_even_16x16m.ega",
    "graphics/shield_even_16x16m.ega", // TODO: investigate
  };
uint8_t GRAPHIC_LIFE_ICON_EVEN[16*16*4] = "graphics/life_icon_bright_16x16m.ega";


uint8_t GRAPHIC_CORKSCREW_ODD[16*16*4] = "graphics/corkscrew_odd_16x16m.ega";
uint8_t GRAPHIC_DOOR_KEY_ODD[16*16*4] = "graphics/door_key_odd_16x16m.ega";
uint8_t GRAPHIC_BOOTS_ODD[16*16*4] = "graphics/boots_odd_16x16m.ega";
uint8_t GRAPHIC_LANTERN_ODD[16*16*4] = "graphics/lantern_odd_16x16m.ega";
uint8_t GRAPHIC_TELEPORT_WAND_ODD[16*16*4] = "graphics/teleport_wand_odd_16x16m.ega";
uint8_t GRAPHIC_GEMS_ODD[16*16*4] = "graphics/gems_odd_16x16m.ega";
uint8_t GRAPHIC_CROWN_ODD[16*16*4] = "graphics/crown_odd_16x16m.ega";
uint8_t GRAPHIC_GOLD_ODD[16*16*4] = "graphics/gold_odd_16x16m.ega";
uint8_t GRAPHIC_BLASTOLA_COLA_ODD[][16*16*4] =
  {
    "graphics/blastola_cola_odd_16x16m.ega",
    "graphics/blastola_cola_inventory_1_odd_16x16m.ega",
    "graphics/blastola_cola_inventory_2_odd_16x16m.ega",
    "graphics/blastola_cola_inventory_3_odd_16x16m.ega",
    "graphics/blastola_cola_inventory_4_odd_16x16m.ega",
    "graphics/blastola_cola_inventory_5_odd_16x16m.ega",
    "graphics/shield_odd_16x16m.ega",
  };
uint8_t GRAPHIC_LIFE_ICON_ODD[16*16*4] = "graphics/life_icon_dark_16x16m.ega";

uint8_t GRAPHICS_SCORE_DIGITS[10][8*16*4] =
  {
    "graphics/score_digit_0_8x16.ega",
    "graphics/score_digit_1_8x16.ega",
    "graphics/score_digit_2_8x16.ega",
    "graphics/score_digit_3_8x16.ega",
    "graphics/score_digit_4_8x16.ega",
    "graphics/score_digit_5_8x16.ega",
    "graphics/score_digit_6_8x16.ega",
    "graphics/score_digit_7_8x16.ega",
    "graphics/score_digit_8_8x16.ega",
    "graphics/score_digit_9_8x16.ega",
  };

uint8_t GRAPHIC_METER_EMPTY[8*16*4] = "graphics/meter_empty_8x16.ega";
uint8_t GRAPHIC_METER_HALF[8*16*4] = "graphics/meter_half_8x16.ega";
uint8_t GRAPHIC_METER_FULL[8*16*4] = "graphics/meter_full_8x16.ega";

uint8_t GRAPHIC_PAUSE[128*48*4] = "graphics/pause_128x48.ega";

uint8_t GRAPHIC_GAME_OVER[128*48*4] = "graphics/game_over_128x48.ega";

uint8_t TITLE_GRAPHIC[320*200*4] = "SYS000.EGA";
uint8_t UI_GRAPHIC[320*200*4] = "SYS003.EGA";
uint8_t STORY_GRAPHIC[320*200*4] = "SYS001.EGA";
uint8_t ITEMS_GRAPHIC[320*200*4] = "SYS004.EGA";
uint8_t WIN_GRAPHIC[320*200*4] = "SYS002.EGA";

// puffer storing the entire rendered map
uint8_t rendered_map_buffer[16*16*4*MAP_WIDTH_TILES*MAP_HEIGHT_TILES];

#define TILESET_MAX_LENGTH (128*16*16)
uint8_t tileset_buffer_raw[4+TILESET_MAX_LENGTH/2];
struct
{
  uint8_t last_passable;
  uint8_t flags;
  uint8_t graphics[TILESET_MAX_LENGTH*4]; // space for up to 128 16×16 tile graphics
} tileset_buffer;

uint8_t pt0_raw[2*16+MAP_WIDTH_TILES * MAP_HEIGHT_TILES];
uint8_t pt1_raw[2*16+MAP_WIDTH_TILES * MAP_HEIGHT_TILES];
uint8_t pt2_raw[2*16+MAP_WIDTH_TILES * MAP_HEIGHT_TILES];
typedef struct
{
  uint16_t width;
  uint16_t height;
  uint8_t * tiles;
} pt;
pt pt0, pt1, pt2;

typedef struct
{
  uint8_t y;
  uint8_t x;
  uint8_t x_vel;
  uint8_t y_vel;
  uint8_t spawn_timer_and_animation;	// when the enemy is not spawned, the counter until it spawns; when spawned, the animation counter
  uint8_t num_animation_frames;
  uint8_t behavior;
  uint16_t animation_frames_ptr;
  uint8_t state; // 0 = despawned, 1 = spawned, 2..6 = white spark animation counter, 8..12 = red spark animation counter
  uint8_t facing;
  uint8_t restraint; // governs whether the enemy moves every tick or every other tick
} enemy;

enemy enemies[MAX_NUM_ENEMIES];

// The number of frames in each of the 4 enemies' animation cycles. The values
// are always 4 for the .SHP files that come with Captain Comic. (Either 4
// distinct frames for ENEMY_HORIZONTAL_SEPARATE, or 3 distinct + 1 duplicate
// for ENEMY_HORIZONTAL_DUPLICATED.) This number of frames only counts one
// facing direction (the number of frames facing left and facing right is the
// same).

uint8_t enemy_num_animation_frames[4];

// Buffers for raw graphics data from .SHP files. There is room for up to 5
// left-facing graphics and 5 right-facing graphics.
uint8_t enemy_raw[10*160];
uint8_t enemy_graphics[4][10*16*16*4];


// Pointers to graphics data for each enemy's animation cycle. These arrays
// contain pointers into enemy*_graphics.
uint8_t* enemy_animation_frames[4][10];


// http://www.shikadi.net/moddingwiki/Captain_Comic_Map_Format#Executable_file
typedef struct
{
  uint8_t num_distinct_frames; // the number of animation frames stored in the file (not counting automatically duplicated ones or right-facing ones)
  uint8_t horizontal; // ENEMY_HORIZONTAL_DUPLICATED or ENEMY_HORIZONTAL_SEPARATE
  uint8_t animation; // ENEMY_ANIMATION_LOOP or ENEMY_ANIMATION_ALTERNATE
  char filename[14];
} shp;

typedef struct
{
  uint8_t y, x, target_level, target_stage;
} door;

typedef struct
{
  uint8_t shp_index; // index into the level.shp array, indicating what graphics to use for this enemy, 0xff means this slot is unused
  uint8_t behavior; // ENEMY_BEHAVIOR_* or ENEMY_BEHAVIOR_UNUSED
} enemy_record;

typedef struct
{
  uint8_t item_type, item_y, item_x, exit_l, exit_r;
  door doors[3];
  enemy_record enemies[4];
} stage;
stage * current_stage_ptr = 0;

typedef struct
{
  char tt2_filename[14];
  char pt0_filename[14];
  char pt1_filename[14];
  char pt2_filename[14];
  uint8_t door_tile_ul, door_tile_ur, door_tile_ll, door_tile_lr;
  shp shps[4];
  stage stages[3];
} level;

#include "levels.h" // contains level information

// This data structure represents the currently loaded level. It is populated by
// copying from the static data structures referenced from LEVEL_DATA_POINTERS.

level current_level = {0};
level* LEVEL_DATA_POINTERS[] =
  {
    &LEVEL_DATA_LAKE,
    &LEVEL_DATA_FOREST,
    &LEVEL_DATA_SPACE,
    &LEVEL_DATA_BASE,
    &LEVEL_DATA_CAVE,
    &LEVEL_DATA_SHED,
    &LEVEL_DATA_CASTLE,
    &LEVEL_DATA_COMP,
  };

// Where to place Comic when entering a new stage or respawning after death. The
// initial value of (14, 12) is used at the start of the game.
uint8_t comic_y_checkpoint	=	12;
uint8_t comic_x_checkpoint	=	14;

uint16_t door_blit_offset = 0;

uint8_t teleport_animation = 0; 	// used as an extra pointer parameter by exit_door and enter_door
uint8_t teleport_destination_y = 0;
uint8_t teleport_destination_x = 0;
uint8_t teleport_source_y = 0;
uint8_t teleport_source_x = 0;
uint8_t teleport_camera_counter = 0;	// how long to move the camera during a teleport (may be less than the teleport duration of 6 ticks)
int16_t teleport_camera_vel = 0; // the camera moves by this much (signed) while teleport_camera_counter is positive

// Used as parameters to blit_WxH.
uint16_t blit_WxH_width		= 0;	// byte width, 1/8 of pixel width
uint16_t blit_WxH_height	= 0;

//sounds
uint8_t sound_enabled = 1;

#define SAMPLE_RATE 44100
#define SOUND_MAX_FREQ 1193182
#define SOUND_MAX_LENGTH 64

#define SOUND_UNMUTE	0
#define SOUND_PLAY	1
#define SOUND_MUTE	2
#define SOUND_STOP	3
#define SOUND_QUERY	4

// https://en.wikipedia.org/wiki/Piano_key_frequencies#List
// Convert a divisor D into a frequency as 1193182 / D.
#define SOUND_TERMINATOR	0x0000
#define NOTE_REST		0x0000	// 0x0028 29829.550 Hz
#define NOTE_C3			0x2394	// 131.004 Hz
#define NOTE_D3			0x1fb5	// 146.998 Hz
#define NOTE_E3			0x1c3f	// 165.009 Hz
#define NOTE_F3			0x1aa2	// 175.005 Hz
#define NOTE_G3			0x17c8	// 195.989 Hz
#define NOTE_A3			0x1530	// 219.982 Hz
#define NOTE_B3			0x12df	// 246.984 Hz
#define NOTE_C4			0x11ca	// 262.007 Hz
#define NOTE_B4			0x0974	// 493.050 Hz
#define NOTE_C5			0x08e9	// 523.096 Hz
#define NOTE_D5			0x07f1	// 586.907 Hz
#define NOTE_E5			0x0713	// 658.853 Hz
#define NOTE_F5			0x06ad	// 698.176 Hz
#define NOTE_G5			0x05f2	// 783.957 Hz
#define NOTE_A5			0x054b	// 880.577 Hz

uint16_t SOUND_TITLE[][2] =
  {
    {NOTE_E3, 3},
    {NOTE_F3, 3},
    {NOTE_G3, 4},
    {NOTE_REST, 1},
    {NOTE_G3, 4},
    {NOTE_REST, 1},
    {NOTE_G3, 4},
    {NOTE_REST, 1},
    {NOTE_G3, 4},
    {NOTE_REST, 1},
    {NOTE_G3, 7},
    {NOTE_C4, 3},
    {NOTE_G3, 5},
    {NOTE_E3, 3},
    {NOTE_F3, 3},
    {NOTE_G3, 4},
    {NOTE_REST, 1},
    {NOTE_G3, 5},
    {NOTE_F3, 3},
    {NOTE_D3, 8},
    {NOTE_C3, 10},
    {NOTE_REST, 3},
    {NOTE_C4, 3},
    {NOTE_B3, 3},
    {NOTE_A3, 7},
    {NOTE_F3, 3},
    {NOTE_A3, 6},
    {NOTE_C4, 5},
    {NOTE_G3, 8},
    {NOTE_A3, 3},
    {NOTE_G3, 6},
    {NOTE_C4, 3},
    {NOTE_B3, 3},
    {NOTE_A3, 6},
    {NOTE_F3, 5},
    {NOTE_A3, 3},
    {NOTE_C4, 10},
    {NOTE_G3, 10},
    {NOTE_REST, 3},
    {NOTE_E3, 3},
    {NOTE_F3, 3},
    {NOTE_G3, 4},
    {NOTE_REST, 1},
    {NOTE_G3, 4},
    {NOTE_REST, 1},
    {NOTE_G3, 4},
    {NOTE_REST, 1},
    {NOTE_G3, 4},
    {NOTE_REST, 1},
    {NOTE_G3, 7},
    {NOTE_C4, 3},
    {NOTE_G3, 5},
    {NOTE_E3, 3},
    {NOTE_F3, 3},
    {NOTE_G3, 4},
    {NOTE_REST, 1},
    {NOTE_G3, 5},
    {NOTE_A3, 3},
    {NOTE_B3, 8},
    {NOTE_C4, 10},
    {NOTE_REST, 3},
    {SOUND_TERMINATOR, 0},
  };

uint16_t SOUND_TITLE_RECAP[][2] =
  {
    {NOTE_E3, 6},
    {NOTE_F3, 6},
    {NOTE_G3, 9},
    {NOTE_REST, 1},
    {NOTE_G3, 9},
    {NOTE_REST, 1},
    {NOTE_G3, 9},
    {NOTE_REST, 1},
    {NOTE_G3, 9},
    {NOTE_REST, 1},
    {NOTE_G3, 14},
    {NOTE_C4, 7},
    {NOTE_G3, 18},
    {NOTE_B3, 20},
    {NOTE_C4, 20},
    {SOUND_TERMINATOR, 0},
  };

uint16_t SOUND_DOOR[][2] =
  {
    {0x0f00, 1},
    {0x0d00, 1},
    {0x0c00, 1},
    {0x0b00, 1},
    {0x0a00, 1},
    {0x0b00, 1},
    {0x0c00, 1},
    {0x0d00, 1},
    {0x0f00, 1},
    {SOUND_TERMINATOR, 0},
  };

uint16_t SOUND_DEATH[][2] =
  {    
    {0x3000, 1},	//  97.101 Hz
    {0x3800, 1},	//  83.230 Hz
    {0x4000, 1},	//  72.826 Hz
    {0x0800, 1},	// 582.608 Hz
    {0x1000, 1},	// 291.304 Hz
    {0x1800, 1},	// 194.203 Hz
    {0x2000, 1},	// 145.652 Hz
    {0x2800, 1},	// 116.522 Hz
    {0x3000, 1},	// 97.101 Hz
    {SOUND_TERMINATOR, 0},
  };

uint16_t SOUND_TELEPORT[][2] =
  {
    {0x2000, 2},	// 145.652 Hz
    {0x1e00, 2},	// 155.362 Hz
    {0x1c00, 2},	// 166.460 Hz
    {0x1a00, 2},	// 179.264 Hz
    {0x1c00, 2},	// 166.460 Hz
    {0x1e00, 2},	// 155.362 Hz
    {0x2000, 2},	// 145.652 Hz
    {SOUND_TERMINATOR, 0},
  };

uint16_t SOUND_SCORE_TALLY[][2] =
  {
    {0x1800, 1},	// 194.203 Hz
    {0x1600, 1},	// 211.858 Hz
    {SOUND_TERMINATOR, 0},
  };

// Convert a divisor D into a frequency as 1193182 / D.
#define SOUND_FREQ_94HZ		0x3195	//  94.003 Hz
#define SOUND_FREQ_95HZ		0x310f	//  95.006 Hz
#define SOUND_FREQ_96HZ		0x308c	//  96.008 Hz
#define SOUND_FREQ_97HZ		0x300c	//  97.007 Hz
#define SOUND_FREQ_98HZ		0x2f8f	//  98.003 Hz
#define SOUND_FREQ_99HZ		0x2f14	//  99.003 Hz
#define SOUND_FREQ_100HZ	0x2e9b	// 100.007 Hz
#define SOUND_FREQ_105HZ	0x2c63	// 105.006 Hz
#define SOUND_FREQ_110HZ	0x2a5f	// 110.001 Hz
#define SOUND_FREQ_125HZ	0x2549	// 125.006 Hz
#define SOUND_FREQ_130HZ	0x23da	// 130.005 Hz
#define SOUND_FREQ_146HZ	0x1fec	// 146.009 Hz
#define SOUND_FREQ_150HZ	0x1f12	// 150.010 Hz
#define SOUND_FREQ_160HZ	0x1d21	// 160.008 Hz
#define SOUND_FREQ_200HZ	0x174d	// 200.031 Hz
#define SOUND_FREQ_210HZ	0x1631	// 210.030 Hz
#define SOUND_FREQ_220HZ	0x152f	// 220.022 Hz
#define SOUND_FREQ_230HZ	0x1443	// 230.033 Hz
#define SOUND_FREQ_240HZ	0x136b	// 240.029 Hz
#define SOUND_FREQ_250HZ	0x12a4	// 250.038 Hz
#define SOUND_FREQ_300HZ	0x0f89	// 300.021 Hz
#define SOUND_FREQ_400HZ	0x0ba6	// 400.128 Hz
#define SOUND_FREQ_600HZ	0x07c4	// 600.192 Hz
#define SOUND_FREQ_900HZ	0x052d	// 900.515 Hz

uint16_t SOUND_MATERIALIZE[][2] =
  {
    {SOUND_FREQ_200HZ, 1},
    {SOUND_FREQ_220HZ, 1},
    {SOUND_FREQ_210HZ, 1},
    {SOUND_FREQ_230HZ, 1},
    {SOUND_FREQ_220HZ, 1},
    {SOUND_FREQ_240HZ, 1},
    {SOUND_FREQ_900HZ, 1},
    {SOUND_FREQ_600HZ, 1},
    {SOUND_FREQ_400HZ, 1},
    {SOUND_FREQ_300HZ, 1},
    {SOUND_FREQ_250HZ, 1},
    {SOUND_FREQ_200HZ, 1},
    {SOUND_FREQ_150HZ, 1},
    {SOUND_FREQ_125HZ, 1},
    {SOUND_FREQ_110HZ, 1},
    {SOUND_FREQ_105HZ, 1},
    {SOUND_FREQ_100HZ, 1},
    {SOUND_FREQ_99HZ, 1},
    {SOUND_FREQ_98HZ, 1},
    {SOUND_FREQ_97HZ, 1},
    {SOUND_FREQ_96HZ, 1},
    {SOUND_FREQ_95HZ, 1},
    {SOUND_FREQ_94HZ, 1},
    {SOUND_TERMINATOR, 0},
  };

uint16_t SOUND_GAME_OVER[][2] =
  {
    {NOTE_B3, 6},
    {NOTE_A3, 3},
    {NOTE_G3, 4},
    {NOTE_REST, 1},
    {NOTE_G3, 4},
    {NOTE_B3, 6},
    {NOTE_A3, 3},
    {NOTE_G3, 4},
    {NOTE_REST, 1},
    {NOTE_G3, 4},
    {NOTE_B3, 6},
    {NOTE_A3, 3},
    {NOTE_G3, 4},
    {NOTE_E3, 4},
    {NOTE_F3, 4},
    {NOTE_D3, 5},
    {NOTE_C3, 5},
    {SOUND_TERMINATOR, 0},
  };

uint16_t SOUND_STAGE_EDGE_TRANSITION[][2] =
  {
    {NOTE_F5, 3},
    {NOTE_A5, 3},
    {NOTE_G5, 5},
    {NOTE_F5, 5},
    {NOTE_E5, 5},
    {NOTE_F5, 5},
    {NOTE_G5, 5},
    {SOUND_TERMINATOR, 0},
  };
uint16_t SOUND_TOO_BAD[][2] =
  {
    {SOUND_FREQ_130HZ, 5},
    {SOUND_FREQ_146HZ, 5},
    {SOUND_FREQ_130HZ, 5},
    {SOUND_FREQ_160HZ, 10},
    {SOUND_TERMINATOR, 0},
  };

uint16_t SOUND_FIRE[][2] =
  {
    {0x2000, 1},	// 145.652 Hz
    {0x1e00, 1},	// 155.362 Hz
    {SOUND_TERMINATOR, 0},
  };

uint16_t SOUND_HIT_ENEMY[][2] =
  {
    {0x0800, 1},	//  582.608 Hz
    {0x0400, 1},	// 1165.217 Hz
    {SOUND_TERMINATOR, 0},
  };

uint16_t SOUND_DAMAGE[][2] =
  {
    {0x3000, 2},	// 97.101 Hz
    {0x3800, 2},	// 83.230 Hz
    {0x4000, 2},	// 72.826 Hz
    {SOUND_TERMINATOR, 0},
  };

// The frequencies of SOUND_COLLECT_ITEM don't correspond to any tuning system I
// recognize// the frequencies increase in ratios of roughly a major third (402.6
// cents), a minor third (299.6 cents), and a perfect fourth (481.7 cents),
// spanning just short of an octave from lowest to highest.
uint16_t SOUND_COLLECT_ITEM[][2] =
  {
    {0x0fda, 2},	// 294.032 Hz
    {0x0c90, 2},	// 371.014 Hz
    {0x0a91, 2},	// 441.102 Hz
    {0x0800, 2},	// 582.608 Hz
    {SOUND_TERMINATOR, 0},
  };

uint16_t SOUND_EXTRA_LIFE[][2] =
  {
    {NOTE_B4, 5},
    {NOTE_D5, 6},
    {NOTE_B4, 2},
    {NOTE_C5, 5},
    {NOTE_D5, 5},
    {SOUND_TERMINATOR, 0},
  };

//uint8_t * offscreen_video_buffer_ptr	=	0;	// points to the video buffer not currently onscreen; alternates between 0x0000 and 0x2000
// comic_run_cycle cycles through COMIC_RUNNING_1, COMIC_RUNNING_2,
// COMIC_RUNNING_3, advancing by one step every game tick.
uint8_t comic_run_cycle		= 0;
uint8_t comic_is_falling_or_jumping	= 0;	// 0 when Comic is on the ground, 1 when falling or jumping
uint8_t comic_is_teleporting	= 0;
int8_t comic_x_momentum	= 0;	// ranges from -5 to +5.
int8_t comic_y_vel		= 0;	// fixed-point fractional value in units of 1/8 game units (1/16 tile or 1 pixel) per tick
uint8_t comic_jump_counter	= 0;	// a jump stops moving upwards when this counter decrements to 1
uint8_t comic_facing		= COMIC_FACING_RIGHT;
uint8_t comic_animation		= COMIC_STANDING;

// How much HP is due to be given the player in the upcoming ticks.
uint8_t comic_hp_pending_increase	= MAX_HP;	// initially set to fill HP at the start of the game
// After this variable becomes nonzero, it decrements on each tick and the game
// ends when it reaches 1.
uint8_t win_counter		= 0;
// fireball_meter depletes by 1 unit every 2 ticks while the fire key is being
// pressed, and recovers at the same rate when the fire key is not being
// pressed. fireball_meter_counter alternates 2, 1, 2, 1, .... fireball_meter
// decrements when fireball_meter_counter is 2 and increments when
// fireball_meter_counter is 1.
uint8_t fireball_meter_counter	= 2;

// http://tasvideos.org/GameResources/DOS/CaptainComic.html#EnemyLogic
uint8_t enemy_respawn_counter_cycle	= 20;	// cycles 20, 40, 60, 80, 100, 20, ...
uint8_t enemy_respawn_position_cycle	= PLAYFIELD_WIDTH - 2;	// cycles 24, 26, 28, 30, 24, ...
uint8_t enemy_spawned_this_tick		= 0;	// flag to ensure no more than one enemy is spawned per tick
// When inhibit_death_by_enemy_collision is nonzero, Comic will take damage from
// collision with enemies, but will not die, not even when comic_hp is 0. This
// is set during comic_death_animation to prevent enemies from "over-killing"
// Comic while the death animation is playing.
uint8_t inhibit_death_by_enemy_collision	= 0;

typedef struct
{
  uint8_t y, x;
  int8_t vel, corkscrew_phase, animation, num_animation_frames;
} fireball;
fireball fireballs[MAX_NUM_FIREBALLS] = {{.y = FIREBALL_DEAD, .x = FIREBALL_DEAD, .num_animation_frames = 2}};

uint8_t item_animation_counter = 0;

#endif
