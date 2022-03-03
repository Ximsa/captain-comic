#ifndef CONSTANTS_H
#define CONSTANTS_H

// Game Timer
#define IRQ_0 (1193181.81818181 / 65536.0)

// Keyboard scancodes
#define SCANCODE_ALT		56
#define SCANCODE_SPACE		57
#define SCANCODE_CAPSLOCK	58
#define SCANCODE_F1		59
#define SCANCODE_F2		60
#define SCANCODE_LEFT		75
#define SCANCODE_RIGHT		77
#define SCANCODE_INS		82

//These match the order of levels under level_data.
#define LEVEL_NUMBER_LAKE	0
#define LEVEL_NUMBER_FOREST	1
#define LEVEL_NUMBER_SPACE	2
#define LEVEL_NUMBER_BASE	3
#define LEVEL_NUMBER_CAVE	4
#define LEVEL_NUMBER_SHED	5
#define LEVEL_NUMBER_CASTLE	6
#define LEVEL_NUMBER_COMP	7

// Item codes.
#define ITEM_CORKSCREW		0
#define ITEM_DOOR_KEY		1
#define ITEM_BOOTS		2
#define ITEM_LANTERN		3
#define ITEM_TELEPORT_WAND	4
#define ITEM_GEMS		5
#define ITEM_CROWN		6
#define ITEM_GOLD		7
#define ITEM_BLASTOLA_COLA	8
#define ITEM_SHIELD		14

// Codes that indicate that a .SHP file slot, stage edge, or door is unused.
#define SHP_UNUSED		0x00
#define EXIT_UNUSED		0xff
#define DOOR_UNUSED		0xff
#define ITEM_UNUSED		0xff

// Values of shp.horizontal, which controls whether the sprite has separate
// left- and right-facing graphics.
#define ENEMY_HORIZONTAL_DUPLICATED	1	// make right-facing frames by copying the left-facing frames
#define ENEMY_HORIZONTAL_SEPARATE	2	// right-facing frames are stored separately

// Values of shp.animation, which controls whether sprite animation loops from
// the beginning or alternates forward and backward.
#define ENEMY_ANIMATION_LOOP		0	// animation goes 0, 1, 2, 3, 0, 1, 2, 3, ...
#define ENEMY_ANIMATION_ALTERNATE	1	// animation goes 0, 1, 2, 1, 0, 1, 2, 1, ...

#define MAP_WIDTH_TILES		128
#define MAP_HEIGHT_TILES	10
// A game unit is 8 pixels, half a tile.
#define MAP_WIDTH		(MAP_WIDTH_TILES * 2)	// in game units
#define MAP_HEIGHT		(MAP_HEIGHT_TILES * 2)	// in game units

// The size of the visible portion of the map during gameplay.
#define PLAYFIELD_WIDTH		24			// in game units
#define PLAYFIELD_HEIGHT	MAP_HEIGHT		// in game units

#define SCREEN_WIDTH		320	// in pixels
#define SCREEN_HEIGHT		200

// The offset of the 40 KB buffer of video memory (inside segment 0xa000) into
// which the entire map for the current stage is rendered.
// RENDERED_MAP_BUFFER	equ	0x4000
// note we globally allocate that buffer in data.h
// #define RENDERED_MAP_BUFFER = ((uint8_t*)0x4000);

// Possible values of comic_animation. Comic has 5 frames of animation in each
// direction (5 facing right, 5 facing left).
#define COMIC_STANDING		0
#define COMIC_RUNNING_1		1
#define COMIC_RUNNING_2		2
#define COMIC_RUNNING_3		3
#define COMIC_JUMPING		4

// Possible values of comic_facing. comic_facing is used, along with
// comic_animation, to index GRAPHICS_COMIC. The graphic used is
// GRAPHICS_COMIC[comic_facing + comic_animation].
#define COMIC_FACING_RIGHT	0
#define COMIC_FACING_LEFT	5

// Possible values of enemy.behavior. ENEMY_BEHAVIOR_FAST may be bitwise ORed
// with any of the other constants.
// http://www.shikadi.net/moddingwiki/Captain_Comic_Map_Format#Executable_file
#define ENEMY_BEHAVIOR_BOUNCE	1	// like Fire Ball, Brave Bird, Space Pollen, Saucer, Spark, Atom, F.W. Bros.
#define ENEMY_BEHAVIOR_LEAP	2	// like Bug-eyes, Blind Toad, Beach Ball
#define ENEMY_BEHAVIOR_ROLL	3	// like Glow Globe
#define ENEMY_BEHAVIOR_SEEK	4	// like Killer Bee
#define ENEMY_BEHAVIOR_SHY	5       // like Shy Bird, Spinner
#define ENEMY_BEHAVIOR_UNUSED	0x7f
#define ENEMY_BEHAVIOR_FAST	0x80	// move every tick, not every other tick

// Possible values of enemy.state. Values 2..6 and 8..12 are rather animation
// counters that mean the enemy is dying due to being hit by a fireball or
// colliding with Comic, respectively.
#define ENEMY_STATE_DESPAWNED	0
#define ENEMY_STATE_SPAWNED	1
#define ENEMY_STATE_WHITE_SPARK	2
#define ENEMY_STATE_RED_SPARK	8

// Possible values of enemy.restraint. This field governs whether an enemy is
// slow or fast. A slow enemy alternates between ENEMY_RESTRAINT_MOVE_THIS_TICK
// and ENEMY_RESTRAINT_SKIP_THIS_TICK, moving only on the "move" ticks. Fast
// enemies move every tick. There is a bug with fast enemies in some behavior
// types, however. Though they start in ENEMY_RESTRAINT_MOVE_EVERY_TICK, their
// enemy.restraint field increments on every tick, until it overflows to
// ENEMY_RESTRAINT_MOVE_THIS_TICK and they become a slow enemy. The bug affects
// ENEMY_BEHAVIOR_LEAP, ENEMY_BEHAVIOR_ROLL, and ENEMY_BEHAVIOR_SEEK, but not
// ENEMY_BEHAVIOR_BOUNCE and ENEMY_BEHAVIOR_SHY. Additionally,
// ENEMY_BEHAVIOR_ROLL enemies become slow if they pass a tick where Comic is
// directly above or below them and not moving left or right, and
// ENEMY_BEHAVIOR_SEEK enemies become slow if they bump into a solid map tile.
#define ENEMY_RESTRAINT_MOVE_THIS_TICK	0	// move this tick; transition to ENEMY_RESTRAINT_SKIP_THIS_TICK
#define ENEMY_RESTRAINT_SKIP_THIS_TICK	1	// don't move this tick; transition to ENEMY_RESTRAINT_MOVE_THIS_TICK
#define ENEMY_RESTRAINT_MOVE_EVERY_TICK	2	// values 2..255 all mean "move every tick"

// ENEMY_FACING_* constants are the opposite of COMIC_FACING_*.
#define ENEMY_FACING_RIGHT	5
#define ENEMY_FACING_LEFT	0

// Enemies despawn when they are this many horizontal units or more away from
// Comic.
#define ENEMY_DESPAWN_RADIUS	30

#define MAX_NUM_ENEMIES		4	// each stage may contain up to 4 enemies
#define MAX_NUM_DOORS		3	// each stage may contain up to 3 doors

#define MAX_HP			6	// the HP meter has 12 pips but increases/decreases 2 at a time
#define MAX_FIREBALL_METER	12	// the fireball meter uses all 12 pips
#define MAX_NUM_LIVES		5

#define FIREBALL_DEAD		0xff	// this constant in fireball.y and fireball.x means the fireball is not active
#define MAX_NUM_FIREBALLS	5	// Comic's maximum firepower and the maximum number of fireballs that can exist

#define NUM_HIGH_SCORES		10	// the number of entries in the high score list

#define TELEPORT_DISTANCE	6	// how many game units a teleport moves Comic horizontally

#define COMIC_GRAVITY		5	// gravity applied to Comic in all levels but space.
#define COMIC_GRAVITY_SPACE	3	// gravity applied to Comic in the space level.

// TERMINAL_VELOCITY is the maximum downward velocity when falling. It applies
// to Comic himself and to ENEMY_BEHAVIOR_LEAP enemies. (But not
// ENEMY_BEHAVIOR_ROLL; gravity works differently for them.)
#define TERMINAL_VELOCITY	23	// in units of 1/8 game units per tick, as in comic_y_vel

#endif
