#define _CRT_SECURE_NO_WARNINGS

#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>
#include <stdint.h>
#include <stdio.h>
#include "data.h"
#include "constants.h"

SDL_AudioDeviceID dev = {0};
SDL_Window * win = NULL;
SDL_Renderer * renderer = NULL;
SDL_Texture * texture = NULL;
SDL_Palette * palette = NULL;

uint8_t screen_buffer[SCREEN_WIDTH*SCREEN_HEIGHT*4];
uint8_t ega_buffer[SCREEN_WIDTH*SCREEN_HEIGHT/2];
Uint16 audio_buffer[SOUND_MAX_LENGTH * SAMPLE_RATE * sizeof(Uint16)];
void award_extra_life(uint8_t sound);
void load_new_stage();
void load_new_level();
size_t file_size(FILE * f)
{
  fseek (f , 0 , SEEK_END);
  size_t size = ftell(f);
  rewind (f);
  return size;
}

void draw()
{
  if(graphics_enabled)
    {
      SDL_UpdateTexture(texture, NULL, screen_buffer, SCREEN_WIDTH * 4);
      SDL_RenderCopy(renderer, texture, NULL, NULL);
      SDL_RenderPresent(renderer);
    }
}

#define PLAY_SOUND(sound) play_sound(sound,sizeof(sound))
void play_sound(uint16_t sound[][2], size_t sound_size)
{
  if(sound_enabled)
    {
      size_t sound_length = sound_size / 4;
      size_t buffer_length = sound_length * SAMPLE_RATE;
      size_t note = 0;
      size_t i = 0;
      for (size_t note_counter = sound[note][1] * SAMPLE_RATE / 18; i < buffer_length; i++, note_counter--)
	{
	  double frequency = (double)SOUND_MAX_FREQ / (double)sound[note][0];
	  audio_buffer[i] = ((size_t)(i * frequency * 2.0 / SAMPLE_RATE) % 2)*8196;
	  if (note_counter == 0)
	    {
	      note++;
	      note_counter = (size_t)((size_t)sound[note][1] * SAMPLE_RATE / IRQ_0);
	    }
	}
      SDL_ClearQueuedAudio(dev);
      SDL_QueueAudio(dev, audio_buffer, sizeof(Uint16) * i);
    }
}

void wait_keypress()
{
  SDL_Event event = {0};
  uint8_t quit = 0;
  while(!quit) // wait for keypress
    {
      SDL_WaitEvent(&event);
      if(event.type == SDL_KEYDOWN) break;
    }
}

void wait_n_ticks(uint16_t ticks)
{
  SDL_Delay((2*1000*ticks/IRQ_0)); // wait for every second IRQ
}

void init_sound()
{
  SDL_Init(SDL_INIT_AUDIO);
  SDL_AudioSpec audio_want =
    {
      .freq = SAMPLE_RATE, // number of samples per second
      .format = AUDIO_U16, // sample type (here: unsigned short 16 bit)
      .channels = 1,
      .samples = SAMPLE_RATE / 12, // buffer-size (1/12s)
      .callback = NULL,	// function SDL calls periodically to refill the buffer
      .userdata = NULL,
    };
  SDL_AudioSpec audio_have;
  dev = SDL_OpenAudioDevice(NULL, 0, &audio_want, &audio_have, SDL_AUDIO_ALLOW_ANY_CHANGE);
  SDL_PauseAudioDevice(dev, 0);
}

void EGA_to_32(size_t size_ega, size_t planes, uint8_t * buf_ega, uint8_t * buf_32)
{
  size_t ega_plane_size = size_ega / planes; // in bytes
  for(size_t pixel_index = 0; pixel_index < (ega_plane_size * 8); pixel_index++)
    { // red green blue intensity transparent
      uint8_t * color =
	colors[
	       (((buf_ega[(pixel_index / 8) + ega_plane_size * 0] >> (7 - pixel_index % 8)) & 1) << 0) +
	       (((buf_ega[(pixel_index / 8) + ega_plane_size * 1] >> (7 - pixel_index % 8)) & 1) << 1) +
	       (((buf_ega[(pixel_index / 8) + ega_plane_size * 2] >> (7 - pixel_index % 8)) & 1) << 2) +
	       (((buf_ega[(pixel_index / 8) + ega_plane_size * 3] >> (7 - pixel_index % 8)) & 1) << 3)];
      uint8_t a = 1;
      if(planes == 5) a = !((buf_ega[(pixel_index / 8) + ega_plane_size * 4] >> (7 - pixel_index % 8)) & 1);
      buf_32[pixel_index*4 + 0] = color[0];
      buf_32[pixel_index*4 + 1] = color[1];
      buf_32[pixel_index*4 + 2] = color[2];
      buf_32[pixel_index*4 + 3] = a;
    }
}

void load_EGA(uint8_t * filename_and_buffer, size_t rgb_size) // loads and converts a imagefile
{
  size_t plane_size = 5;
  if (rgb_size == SCREEN_WIDTH * SCREEN_HEIGHT * 4) plane_size = 4;
  FILE * f = fopen((char*)filename_and_buffer, "rb");
  size_t ega_size = rgb_size * plane_size / 32; // TODO: check for rounding errors
  fread(ega_buffer, 1, ega_size, f);
  fclose(f);
  // now convert ega to RGB32
  EGA_to_32(ega_size, plane_size, ega_buffer, filename_and_buffer);
}

#define INIT_GRAPHIC(graphic) load_EGA(graphic, sizeof(graphic))
#define INIT_GRAPHICS(graphics) for(size_t i = 0; i < sizeof(graphics) / sizeof(graphics[0]); i++) INIT_GRAPHIC(graphics[i]);
void init_graphics() // fills every GRAPHIC* structure with pixel values
{
  // fill single graphics
  INIT_GRAPHIC(GRAPHIC_FIREBALL_0);
  INIT_GRAPHIC(GRAPHIC_FIREBALL_1);
  INIT_GRAPHIC(GRAPHIC_WHITE_SPARK_0);
  INIT_GRAPHIC(GRAPHIC_WHITE_SPARK_1);
  INIT_GRAPHIC(GRAPHIC_WHITE_SPARK_2);
  INIT_GRAPHIC(GRAPHIC_RED_SPARK_0);
  INIT_GRAPHIC(GRAPHIC_RED_SPARK_1);
  INIT_GRAPHIC(GRAPHIC_RED_SPARK_2);
  INIT_GRAPHIC(GRAPHIC_TELEPORT_0);
  INIT_GRAPHIC(GRAPHIC_TELEPORT_1);
  INIT_GRAPHIC(GRAPHIC_TELEPORT_2);
  INIT_GRAPHIC(GRAPHIC_CORKSCREW_EVEN);
  INIT_GRAPHIC(GRAPHIC_DOOR_KEY_EVEN);
  INIT_GRAPHIC(GRAPHIC_BOOTS_EVEN);
  INIT_GRAPHIC(GRAPHIC_LANTERN_EVEN);
  INIT_GRAPHIC(GRAPHIC_TELEPORT_WAND_EVEN);
  INIT_GRAPHIC(GRAPHIC_GEMS_EVEN);
  INIT_GRAPHIC(GRAPHIC_CROWN_EVEN);
  INIT_GRAPHIC(GRAPHIC_GOLD_EVEN);
  INIT_GRAPHIC(GRAPHIC_LIFE_ICON_EVEN);
  INIT_GRAPHIC(GRAPHIC_CORKSCREW_ODD);
  INIT_GRAPHIC(GRAPHIC_DOOR_KEY_ODD);
  INIT_GRAPHIC(GRAPHIC_BOOTS_ODD);
  INIT_GRAPHIC(GRAPHIC_LANTERN_ODD);
  INIT_GRAPHIC(GRAPHIC_TELEPORT_WAND_ODD);
  INIT_GRAPHIC(GRAPHIC_GEMS_ODD);
  INIT_GRAPHIC(GRAPHIC_CROWN_ODD);
  INIT_GRAPHIC(GRAPHIC_GOLD_ODD);
  INIT_GRAPHIC(GRAPHIC_LIFE_ICON_ODD);
  INIT_GRAPHIC(GRAPHIC_METER_EMPTY);
  INIT_GRAPHIC(GRAPHIC_METER_HALF);
  INIT_GRAPHIC(GRAPHIC_METER_FULL);
  INIT_GRAPHIC(GRAPHIC_PAUSE);
  INIT_GRAPHIC(GRAPHIC_GAME_OVER);
  INIT_GRAPHIC(TITLE_GRAPHIC);
  INIT_GRAPHIC(UI_GRAPHIC);
  INIT_GRAPHIC(STORY_GRAPHIC);
  INIT_GRAPHIC(ITEMS_GRAPHIC);
  INIT_GRAPHIC(WIN_GRAPHIC);
  // fill graphic arrays
  INIT_GRAPHICS(GRAPHICS_COMIC);
  INIT_GRAPHICS(ANIMATION_MATERIALIZE);
  INIT_GRAPHICS(ANIMATION_COMIC_DEATH);
  INIT_GRAPHICS(GRAPHIC_BLASTOLA_COLA_EVEN);
  INIT_GRAPHICS(GRAPHIC_BLASTOLA_COLA_ODD);
  INIT_GRAPHICS(GRAPHICS_SCORE_DIGITS);
}

// assumes RGBA32
void blit(uint16_t width, uint16_t height, // dimensions to blit
	  uint16_t src_x, uint16_t src_y, // source offset
	  uint16_t dest_x, uint16_t dest_y, // destiantion offset
	  size_t src_width, uint8_t * src_pixels, // source image
	  size_t dest_width, uint8_t * dest_pixels) // destination image
{
  for(size_t x = 0; x < width; x++)
    for(size_t y = 0; y < height; y++)
      {
	size_t src_index = (y+src_y)*src_width+x+src_x;
	if (src_pixels[src_index*4 + 3])
	  {
	    size_t dest_index = (dest_y+y)*dest_width +dest_x+x;
	    ((uint32_t*)dest_pixels)[dest_index] = ((uint32_t*)src_pixels)[src_index];
	  }
      }
}

// since it is impossible to Update a texture with alpha channel -> manual loop
void blit_to_screen(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t * src_pixels)
{
  blit(w, h, 0, 0, x, y, w, src_pixels, SCREEN_WIDTH, screen_buffer);
}

void init_UI()
{
  SDL_Init(SDL_INIT_VIDEO);
  win = SDL_CreateWindow(STARTUP_NOTICE_TEXT,
			 SDL_WINDOWPOS_UNDEFINED,
			 SDL_WINDOWPOS_UNDEFINED,
			 SCREEN_WIDTH*4,
			 200*4,
			 SDL_WINDOW_RESIZABLE);
  renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_SOFTWARE);
  SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
  texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, 200);
  init_graphics();
}

// Award the player al*100 points. al must be in the range 0..99. Increment
// score_10000_counter if the score_10000_counter overflows. When
// score_10000_counter reaches 5, call award_extra_life and reset
// score_10000_counter to 0.
// Output:
//   score = increased by al*100 points
//   score_10000_counter = (score_10000_counter + 1) % 5 if adding the points carried into the third digit
//   comic_num_lives = max(comic_num_lives + 1, MAX_NUM_LIVES) if score_10000_counter overflowed to 0
void award_points(uint8_t points)
{
  uint16_t score_x = 272;
  uint16_t score_y = 24;
  uint8_t index = 0;
  do
    {
      score[index] += points;
      points = 0;
      if (score[index] >= 100)
	{
	  score[index] %= 100;
	  points = 1; // carry a 1 into the next digit
	}
      // blit score digit
      // low decimal digit:
      blit_to_screen(score_x, score_y, 8, 16, GRAPHICS_SCORE_DIGITS[score[index] % 10]);
      score_x -= 8;
      // high decimal digit:
      blit_to_screen(score_x, score_y, 8, 16, GRAPHICS_SCORE_DIGITS[score[index] / 10]);
      score_x -= 8;
      index++;
    }
  while(points > 0); // is there any carry for the next digit?
  // The player earns an extra life every 50000 points. We track this by
  // counting the number of times a score increment causes a carry into
  // the third digit, which is the number of times the ten thousands digit
  // has increased. When it happens 5 times, we award a life and reset the
  // counter.
  if(index > 1)
    {
      score_10000_counter++;
    }
  if(score_10000_counter == 5) // have we reached 50000?
    {
      score_10000_counter = 0;
      award_extra_life(1);
    }
}

// Subtract a life if comic_num_lives is greater than 0.
// Output:
//   comic_num_lives = decremented by 1 unless already at 0
void lose_a_life()
{
  if(comic_num_lives > 0)
    {
      blit_to_screen(24 + 24 * comic_num_lives, 180, 16, 16, GRAPHIC_LIFE_ICON_ODD);
      comic_num_lives--;
    }
}

// Award the player an extra life and play the extra life sound. If the player
// already has MAX_NUM_LIVES lives, refill HP and award 22500 points.
// Output:
//   comic_num_lives = incremented by 1 unless already at MAX_NUM_LIVES
//   comic_hp_pending_increase = MAX_HP if comic_num_lives was MAX_NUM_LIVES
//   score = increased by 22500 points if comic_num_lives was MAX_NUM_LIVES
void award_extra_life(uint8_t sound)
{
  if(sound) PLAY_SOUND(SOUND_EXTRA_LIFE);
  if(comic_num_lives == 5) // already the maximum number of lives?
    {
      comic_hp_pending_increase = MAX_HP;
      award_points(75);
      award_points(75);
      award_points(75);
    }
  else
    {
      comic_num_lives++; // add a life
      //Brighten the life icon
      blit_to_screen(24 + 24 * comic_num_lives, 180, 16, 16, GRAPHIC_LIFE_ICON_EVEN);
    }
}

// Play the animation of awarding the player their initial lives, first counting
// up to MAX_NUM_LIVES, then subtracting one to represent the life in use at the
// start of the game. Jump to load_new_level when done, using the default
// current_level_number value of LEVEL_NUMBER_FOREST and default
// current_stage_number value of 0.
// Output:
//   comic_num_lives = MAX_NUM_LIVES - 1
void initialize_lives_sequence()
{
  for(size_t i = 1; i < MAX_HP; i++)
    {
      wait_n_ticks(1);
      award_extra_life(0);
      draw();
    }
  wait_n_ticks(3);
  lose_a_life();
  PLAY_SOUND(SOUND_TITLE_RECAP);
  draw();
}

void title_sequence()
{
  PLAY_SOUND(SOUND_TITLE);
  blit_to_screen(0,0,SCREEN_WIDTH, SCREEN_HEIGHT, TITLE_GRAPHIC);
  draw();
  wait_n_ticks(10+5);
  blit_to_screen(0,0,SCREEN_WIDTH, SCREEN_HEIGHT, STORY_GRAPHIC);
  draw();
  wait_keypress();
  blit_to_screen(0,0,SCREEN_WIDTH, SCREEN_HEIGHT, ITEMS_GRAPHIC);
  draw();
  wait_keypress();
  SDL_ClearQueuedAudio(dev);
  blit_to_screen(0,0,SCREEN_WIDTH, SCREEN_HEIGHT, UI_GRAPHIC);
  draw();
}

// Return the address of the map tile at the given coordinates.
// Input:
//   ah = x-coordinate in game units
//   al = y-coordinate in game units
// Output:
//   bx = address of map tile
// note: we return the index, used to check if the tile is solid
uint16_t index_of_tile_at_coordinates(pt current_pt, uint8_t x, uint8_t y)
{
  // Tiles measure 2 game units in both directions: divide coordinates by 2.
  // multiply by 128 (MAP_WIDTH_TILES)
  return current_pt.tiles[(y/2)*MAP_WIDTH_TILES + x/2];
}

// checks if a given tile coordinate is solid
uint8_t is_solid(uint8_t x, uint8_t y)
{
    pt current_pt;
    switch(current_stage_number)
      {
      case 0:
	current_pt = pt0;
	break;
      case 1:
	current_pt = pt1;
	break;
      default:
	current_pt = pt2;
	break;
    }
    return index_of_tile_at_coordinates(current_pt, x, y) > tileset_buffer.last_passable;
}

void wait_1_tick_and_swap_video_buffers()
{
  wait_n_ticks(1);
  draw();
}

// Blit Comic at his current position, relative to the camera, to the offscreen
// video buffer.
// Input:
//   comic_x, comic_y = coordinates of Comic
//   comic_facing = COMIC_FACING_RIGHT or COMIC_FACING_LEFT
//   comic_animation = COMIC_STANDING, COMIC_RUNNING_1, COMIC_RUNNING_2, COMIC_RUNNING_3, or COMIC_JUMPING
//   camera_x = x-coordinate of left edge of playfield
//   offscreen_video_buffer_ptr = whichever of video buffers 0x0000 or 0x2000 is not on screen at the moment
void blit_comic_playfield_offscreen()
{
  // Index GRAPHICS_COMIC by comic_facing and comic_animation.
  // (comic_facing is 0 or 5 and comic_animation is 0..4.)
  uint8_t index = comic_facing + comic_animation;
  blit(16, 32, // width and height
       0, 0, // source x and y
       8+(comic_x-camera_x)*8, 8+comic_y*8, // target x and y 
       16, GRAPHICS_COMIC[index], // source buffer
       SCREEN_WIDTH, screen_buffer); // target buffer
}

// Blit the currently visible portion of the map to the offscreen video buffer.
// Input:
//   camera_x = x-coordinate of left edge of playfield
//   offscreen_video_buffer_ptr = whichever of video buffers 0x0000 or 0x2000 is not on screen at the moment // NOTE: unused
void blit_map_playfield_offscreen()
{
  blit(PLAYFIELD_WIDTH * 8, PLAYFIELD_HEIGHT * 8, // width and height
       camera_x * 8, 0, // source x and y
       8, 8, // target x and y 
       MAP_WIDTH_TILES * 16, rendered_map_buffer, // source buffer
       SCREEN_WIDTH, screen_buffer); // target buffer
}

// Draw a half-open door to the offscreen video buffer. The half-open effect is
// achieved by only drawing the left or right half of each door tile, and
// filling in the rest with black.
// Input:
//   door_blit_offset = offset within the offscreen video segment at which to blit
//   current_level.door_tile_ul = upper-left door tile
//   current_level.door_tile_ur = upper-right door tile
//   current_level.door_tile_ll = lower-left door tile
//   current_level.door_tile_lr = lower-right door tile
void blit_door_halfopen_offscreen(uint8_t x, uint8_t y)
{
  // upper left
  blit(8, 16,
       0, 0,
       8+x*8, 8+y*8,
       16, &tileset_buffer.graphics[current_level.door_tile_ul*16*16*4],
       SCREEN_WIDTH, screen_buffer);
  // upper right
  blit(8, 16,
       8, 0,
       8+(x+3)*8, 8+y*8,
       16, &tileset_buffer.graphics[current_level.door_tile_ur*16*16*4],
       SCREEN_WIDTH, screen_buffer);
  // lower left
  blit(8, 16,
       0, 0,
       8+x*8, 8+(y+2)*8,
       16, &tileset_buffer.graphics[current_level.door_tile_ll*16*16*4],
       SCREEN_WIDTH, screen_buffer);
  // lower right
  blit(8, 16,
       8, 0,
       8+(x+3)*8, 8+(y+2)*8,
       16, &tileset_buffer.graphics[current_level.door_tile_lr*16*16*4],
       SCREEN_WIDTH, screen_buffer);
}

// Black out a 32×32 pixel region starting at door_blit_offset in the offscreen
// video buffer.
// Input:
//   door_blit_offset = offset within the offscreen video segment at which to blit
//   offscreen_video_buffer_ptr = whichever of video buffers 0x0000 or 0x2000 is not on screen at the moment
void blank_door_offscreen(uint8_t x, uint8_t y)
{
  uint32_t blank[32*32*4];
  for(size_t i = 0; i < 32*32*4; i++) blank[i] = 0xFF000000;
  blit(32, 32, // width and height
       0, 0, // source x and y
       8+x*8, 8+y*8, // target x and y 
       32, (uint8_t*)blank, // source buffer
       SCREEN_WIDTH, screen_buffer); // target buffer
}

void handle_item()
{ // TODO: finish
  
}

// Play the beam-in animation.
// Input:
//   comic_x, comic_y = coordinates of Comic
//   camera_x = x-coordinate of left edge of playfield
void beam_in()
{
  // Initially idle for 15 ticks.
  for(size_t i = 0; i < 64; i++)
    {
      blit_map_playfield_offscreen();
      handle_item();
      draw();
      wait_n_ticks(1);
    }
  PLAY_SOUND(SOUND_MATERIALIZE);
  for(int i = 0; i < 12; i++) // 12 frames of animation
    {
      blit_map_playfield_offscreen();
      if(i >= 6) // start drawing Comic after 6 frames of animation
	blit_comic_playfield_offscreen();
      blit(16, 32, // width and height
	   0, 0, // source x and y
	   8+(comic_x-camera_x)*8, 8+comic_y*8, // target x and y 
	   16, ANIMATION_MATERIALIZE[i], // source buffer
	   SCREEN_WIDTH, screen_buffer); // target buffer
      handle_item();
      draw();
      wait_n_ticks(1);
    }
  blit_map_playfield_offscreen();
  blit_comic_playfield_offscreen();
  handle_item();
  draw();
  wait_n_ticks(1); // Wait an additional tick at the end.
}

// Play the beam-out animation.
// Input:
//   comic_x, comic_y = coordinates of Comic
//   camera_x = x-coordinate of left edge of playfield
void beam_out()
{
  PLAY_SOUND(SOUND_MATERIALIZE);
  blit_map_playfield_offscreen();
  blit_comic_playfield_offscreen();
  draw();
  for(size_t i = 0; i < 12; i++) // 12 frames of animation
    {
      blit_map_playfield_offscreen();
      if(i < 6) // draw Comic under the animation for the first 6 frames of the animation
	blit_comic_playfield_offscreen();
      blit(16, 32, // width and height
	   0, 0, // source x and y
	   8+(comic_x-camera_x)*8, 8+comic_y*8, // target x and y 
	   16, ANIMATION_MATERIALIZE[i], // source buffer
	   SCREEN_WIDTH, screen_buffer); // target buffer
      wait_n_ticks(1);
      draw();
    }
  blit_map_playfield_offscreen();
  draw();
  wait_n_ticks(6); // Wait an additional 6 ticks at the end.
}

void do_high_scores()
{ // TODO: finish
  
}

// Display the game over graphic, play SOUND_GAME_OVER, and wait for a keypress.
// Call do_high_scores and then jump to terminate_program.
void game_over()
{
  blit_map_playfield_offscreen();
  blit(128, 48, // width and height
       0, 0, // source x and y
       40, 64, // target x and y 
       128, GRAPHIC_GAME_OVER, // source buffer
       SCREEN_WIDTH, screen_buffer); // target buffer
  wait_1_tick_and_swap_video_buffers();
  wait_keypress();
  do_high_scores();
}

// Run the sequence for when Comic has collected all three treasures and won the
// game.
// Output:
//   score = increased by 20000 points, plus 10000 points for each remaining life (including lives gained while adding points)
void game_end_sequence() // TODO: finish
{
  blit_to_screen(0, 0, 320, 200, WIN_GRAPHIC);
  draw();
}

// Pause the game. Display the pause graphic and wait for a keypress. If the
// keypress is 'q' or 'Q', jump to terminate_program.
void pause()
{
  blit_map_playfield_offscreen();
  blit(128, 48, // width and height
       0, 0, // source x and y
       40, 64, // target x and y 
       128, GRAPHIC_PAUSE, // source buffer
       SCREEN_WIDTH, screen_buffer); // target buffer
  wait_1_tick_and_swap_video_buffers();
  SDL_Event event = {0};
  uint8_t quit = 0;
  while(!quit) // wait for keypress
    {
      SDL_WaitEvent(&event);
      if(event.type == SDL_KEYDOWN)
	{
	  if(event.key.keysym.scancode == SDL_SCANCODE_Q)
	    {
	      exit(0);
	    }
	  else
	    {
	      return;
	    }
	}
    }
}

void handle_enemies()
{
  
}

// Do one tick of the teleport process. Render the map within the playfield and
// blit Comic and the current frames of the teleport animation.
// Input:
//   teleport_camera_counter = how many more ticks the camera should move teleport_camera_vel per tick
//   teleport_camera_vel = how far to move the camera per tick while teleport_camera_counter is nonzero
//   teleport_source_x, teleport_source_y = coordinates of source of teleport
//   teleport_destination_x, teleport_destination_y = coordinates of destination of teleport
// Output:
//   camera_x = increased/decreased by teleport_camera_vel, if teleport_camera_counter not already 0
//   comic_x, comic_y = set to (teleport_destination_x, teleport_destination_y) starting at teleport_animation == 3
//   teleport_camera_counter = decremented by 1 if not already 0
//   teleport_animation = incremented by 1
//   comic_is_teleporting = 1 if the teleport is still in progress, 0 if finished
void handle_teleport()
{
  if(teleport_camera_counter != 0) // are we still scheduled to move the camera during this teleport?
    { // Move the camera to keep up with the motion of the teleport.
      camera_x += teleport_camera_vel;
      teleport_camera_counter--;
    }
  // render the map
  blit_map_playfield_offscreen();
  // Comic's own position actually changes (for the purposes of collision
  // with enemies, etc.) at frame 3 of the 6-frame teleport animation.
  if(teleport_animation == 3)
    {
      comic_y = teleport_destination_y;
      comic_x = teleport_destination_x;
    }
  // We draw the teleport animation at both the source and destination//
  // the animation at the destination is delayed by 1 frame. There are 5
  // frames of animation defined in ANIMATION_TABLE_TELEPORT. We draw at
  // the source during frames 0..4 and draw at the destination during
  // frames 1..5.
  blit_comic_playfield_offscreen(); // blit Comic, whether currently at the teleport source or destination
  if(teleport_animation != 5) // done animating at the source?
    { // blit at source
      blit(16, 32, // width and height
	   0, 0, // source x and y
	   8+(teleport_source_x-camera_x)*8, 8+teleport_source_y*8, // target x and y 
	   16, ANIMATION_TABLE_TELEPORT[teleport_animation], // source buffer
	   SCREEN_WIDTH, screen_buffer); // target buffer
    }
  
   // blit at destination
  if(teleport_animation - 1 >= 0)
    {
      blit(16, 32, // width and height
	   0, 0, // source x and y
	   8+(teleport_destination_x-camera_x)*8, 8+teleport_destination_y*8, // target x and y 
	   16, ANIMATION_TABLE_TELEPORT[teleport_animation - 1], // source buffer
	   SCREEN_WIDTH, screen_buffer); // target buffer
    }
  teleport_animation++; // next frame of animation
  if(teleport_animation == 6) comic_is_teleporting = 0; // are we all done with the teleport?
}


// Find a teleport destination and enter the teleport state.
// Input:
//   comic_x, comic_y = coordinates of Comic
//   comic_facing = COMIC_FACING_RIGHT or COMIC_FACING_LEFT
//   camera_x = x-coordinate of left edge of playfield
// Output:
//   teleport_camera_vel = how far to move the camera per tick in upcoming ticks
//   teleport_camera_counter = how many upcoming ticks during which the camera will move
//   teleport_source_x, teleport_source_y = comic_x, comic_y
//   teleport_destination_x, teleport_destination_y = coordinates of teleport destination
//   teleport_animation = 0
//   comic_is_teleporting = 1
void begin_teleport()
{
  teleport_camera_counter = 0;
  int8_t camera_rel_comic = comic_x-camera_x;
  uint8_t camera_x_mod = camera_x;
  uint8_t destination_x = comic_x;
  uint8_t destination_y = comic_y;
  if(comic_facing == COMIC_FACING_LEFT)
    {
      teleport_camera_vel = -1;
      camera_rel_comic -= TELEPORT_DISTANCE;
      if(camera_rel_comic < 0) // is Comic close to the left edge of the playfield?
	{
	  goto remain_in_place;
	}
      destination_x = comic_x - TELEPORT_DISTANCE; // teleport destination column is 6 units to the left
      // Figure out how to set teleport_camera_counter, which is the number of
      // ticks during which the camera should move during the teleport. It may
      // be less than the animation duration of 6 ticks.
      camera_rel_comic -= PLAYFIELD_WIDTH/2 - 2; // is the destination on the right side of the screen?
      if(camera_rel_comic >= 0)
	{ // .find_a_safe_landing	// if so, then don't move the camera at all
	  goto find_a_safe_landing;
	}
      else
	{ // The destination of the teleport is on the left side of the screen.
	  // We'll need to move the camera during the teleport in order to put
	  // Comic in the center of the playfield when the teleport is over. (The
	  // logic here doesn't take into the account that ah will be rounded down
	  // later, which is a bug.)
	  camera_rel_comic *= -1; // camera_rel_comic = PLAYFIELD_WIDTH/2 - 2 - comic_x // how far the destination is to the left of center
	  camera_x_mod -= camera_rel_comic;
	  if(camera_x_mod < 0) // would moving that far take the camera off the left edge of the stage?
	    { // if so, move the camera only far enough to take the camera all the way to the left edge
	      camera_x_mod += camera_rel_comic;
	    }
	}
    }
  else // facing right
    {
      teleport_camera_vel = +1;
      if(camera_rel_comic >= PLAYFIELD_WIDTH - TELEPORT_DISTANCE - 1) // is Comic close to the right edge of the playfield?
	{
	  goto remain_in_place;
	}
      destination_x = comic_x + TELEPORT_DISTANCE; // teleport destination column is 6 units to the right
      // Figure out how to set teleport_camera_counter, which is the number of
      // ticks during which the camera should move during the teleport. It may
      // be less than the animation duration of 6 ticks.
      camera_rel_comic += TELEPORT_DISTANCE - PLAYFIELD_WIDTH/2; // is the destination on the left side of the screen?
      if(camera_rel_comic <= 0)
	{ // .find_a_safe_landing	// if so, then don't move the camera at all
	  goto find_a_safe_landing;
	}
      else
	{ // The destination of the teleport is on the right side of the screen.
	  // We'll need to move the camera during the teleport in order to put
	  // Comic in the center of the playfield when the teleport is over. (The
	  // logic here doesn't take into the account that ah will be rounded down
	  // later, which is a bug.)
	  camera_x_mod += camera_rel_comic;
	  if(camera_x_mod > MAP_WIDTH - PLAYFIELD_WIDTH) // would moving that far take the camera off the left edge of the stage?
	    { // if so, move the camera only far enough to take the camera all the way to the right edge
	      camera_x_mod -= camera_rel_comic;
	    }
	}
    }
  // set_teleport_camera_counter:
  teleport_camera_counter = camera_x_mod;
  
 find_a_safe_landing:
  // Now ah(destination_x) contains the column column we're trying to teleport to. Search
  // that column for a landing zone, starting from the bottom. A landing
  // zone is a solid tile with two non-solid tiles above it.
  destination_y = PLAYFIELD_HEIGHT - 2; // start looking at the bottom row of tiles
  destination_x = destination_x & 0xFE; // round destination x-coordinate down to an even tile boundary
  for(; destination_y > 0; destination_y-- )
    {
      if(!is_solid(destination_x, destination_y-2) &&
	 !is_solid(destination_x, destination_y) &&
	 is_solid(destination_x, destination_y+2))
	{
	  destination_y-=3;
	  goto finish;
	}
    }
 remain_in_place:
  destination_x = comic_x;
  destination_y = comic_y;
  
 finish:
  teleport_animation = 0; // teleport animation begins
  teleport_destination_x = destination_x;
  teleport_destination_y = destination_y;
  teleport_source_x = comic_x; // set the source coordinates to Comic's current coordinates
  teleport_source_y = comic_y;
  comic_is_teleporting = 1;
  PLAY_SOUND(SOUND_TELEPORT);
  //printf("%i %i -> %i %i\n", teleport_source_x, teleport_source_y, teleport_destination_x, teleport_destination_y);
} 

// Play the animation of Comic dying from taking damage.
// Input:
//   comic_x, comic_y = coordinates of Comic
//   camera_x = x-coordinate of left edge of playfield
void comic_death_animations()
{
  PLAY_SOUND(SOUND_DEATH);
  for(size_t i = 0; i < 8; i++) // 8 frames of animation
    {
      blit_map_playfield_offscreen();
      /*if(i < 4) // draw Comic under the d1eath animation for the first 4 frames
	blit_comic_playfield_offscreen();*/
      handle_enemies();
      blit(16, 32, // width and height
	   0, 0, // source x and y
	   8+(comic_x-camera_x)*8, 8+comic_y*8, // target x and y 
	   16, ANIMATION_COMIC_DEATH[i], // source buffer
	   SCREEN_WIDTH, screen_buffer); // target buffer
      handle_item();
      draw();
      wait_n_ticks(1);
    }
}

// Play the animation for Comic entering a door.
// Input:
//   ah = x-coordinate of door
//   al = y-coordinate of door
//   camera_x = x-coordinate of left edge of playfield
void enter_door()
{
  uint8_t door_x = comic_x - camera_x - 1;
  uint8_t door_y = comic_y;
  wait_n_ticks(3);
  PLAY_SOUND(SOUND_DOOR);
  
  // Door halfway open.
  blit_map_playfield_offscreen();
  blank_door_offscreen(door_x, door_y);
  blit_door_halfopen_offscreen(door_x, door_y);
  blit_comic_playfield_offscreen();	// Comic is in front of door
  wait_1_tick_and_swap_video_buffers();

  // Door fully open.
  blit_map_playfield_offscreen();
  blank_door_offscreen(door_x, door_y);
  blit_comic_playfield_offscreen();
  wait_1_tick_and_swap_video_buffers();

  // Door halfway closed.
  blit_map_playfield_offscreen();
  blit_door_halfopen_offscreen(door_x, door_y);	// useless instruction// the next one blanks what this one blits
  blank_door_offscreen(door_x, door_y);
  blit_comic_playfield_offscreen();	// Comic is behind door
  blit_door_halfopen_offscreen(door_x, door_y);
  wait_1_tick_and_swap_video_buffers();

  // Door fully closed.
  blit_map_playfield_offscreen();
  wait_1_tick_and_swap_video_buffers();
}

// Play the animation for Comic exiting a door.
// Input:
//   comic_x, comic_y = door is placed at (comic_x - 1, comic_y)
//   camera_x = x-coordinate of left edge of playfield
void exit_door()
{
  uint8_t door_x = comic_x - camera_x - 1;
  uint8_t door_y = comic_y;
  wait_n_ticks(3);
  PLAY_SOUND(SOUND_DOOR);
  
  // Door fully closed
  blit_map_playfield_offscreen();
  wait_1_tick_and_swap_video_buffers();
  
  // Door halfway open
  blit_map_playfield_offscreen();
  blank_door_offscreen(door_x, door_y);
  blit_comic_playfield_offscreen(); // Comic is behind door
  blit_door_halfopen_offscreen(door_x, door_y);
  wait_1_tick_and_swap_video_buffers();
  
  // Door fully open.
  blit_map_playfield_offscreen();
  blank_door_offscreen(door_x, door_y);
  blit_comic_playfield_offscreen();
  wait_1_tick_and_swap_video_buffers();

  // Door halfway closed.
  blit_map_playfield_offscreen();
  blit_door_halfopen_offscreen(door_x, door_y);	// useless instruction// the next one blanks what this one blits
  blank_door_offscreen(door_x, door_y);
  blit_door_halfopen_offscreen(door_x, door_y);
  blit_comic_playfield_offscreen();	// Comic is in front of door
  wait_1_tick_and_swap_video_buffers();

  // Door fully closed.();
  blit_map_playfield_offscreen();
  blit_comic_playfield_offscreen();
  wait_1_tick_and_swap_video_buffers();
}

// Blit the entire map into the 40 KB buffer of video memory starting at
// a000:4000.
// Input:
//   current_tiles_ptr = tiles of the map to render
//   actually we use current_level and current_stage_number
void render_map()
{
  pt current_pt;
  switch(current_stage_number)
    {
    case 0:
      current_pt = pt0;
      break;
    case 1:
      current_pt = pt1;
      break;
    default:
      current_pt = pt2;
      break;
    }
  for(size_t x = 0; x < current_pt.width; x++)
    for(size_t y = 0; y < current_pt.height; y++)
      {
	size_t pt_offset = y*current_pt.width + x;
	size_t rendered_x = x * 16;
	size_t rendered_y = y * 16;
	blit(16, 16, // width and height
	     0, 0, // source x and y
	     rendered_x, rendered_y, // target x and y 
	     16, tileset_buffer.graphics + (size_t)current_pt.tiles[pt_offset]*16*16*4, // source buffer
	     current_pt.width*16, rendered_map_buffer); // target buffer
      }
}

// Check for map collision of an enemy-sized box at the given coordinates,
// presumed to be moving vertically. If the x-coordinate is even, check only the
// map tile that contains the given coordinates; if the x-coordinate is odd,
// check that tile and also the one to its right.
// Input:
//   ah = x-coordinate in game units
//   al = y-coordinate in game units
// Output:
//   cf = 1 if collision, 0 if no collision
uint8_t check_vertical_enemy_map_collision(pt current_pt, uint8_t x, uint8_t y)
{
  // Tiles measure 2 game units in both directions: divide coordinates by 2.
  // multiply by 128 (MAP_WIDTH_TILES)
  if(index_of_tile_at_coordinates(current_pt, x ,y) > tileset_buffer.last_passable) // is the tile solid?
    { // if so, return
      return 1;
    }
  else
    { // Is the x-coordinate odd (in the middle of a tile)? I.e., does a
      // 2-unit-wide enemy also touch the next tile to the right?
      if(x % 2 == 0)
	{ // we're on an even tile boundary, no need to test another tile
	  return 0;
	}
      else
	{
	  if(index_of_tile_at_coordinates(current_pt, x+1 ,y) > tileset_buffer.last_passable)
	    {
	      return 1;
	    }
	  else
	    {
	      return 0;
	    }
	}
    }
}

// Check for map collision of an enemy-sized box at the given coordinates,
// presumed to be moving horizontally. If the y-coordinate is even, check only
// the map tile that contains the given coordinates; if the y-coordinate is odd,
// check that tile and also the next one down.
// Input:
//   ah = x-coordinate in game units
//   al = y-coordinate in game units
// Output:
//   cf = 1 if collision, 0 if no collision
uint8_t check_horizontal_enemy_map_collision(pt current_pt, uint8_t x, uint8_t y)
{
  // Tiles measure 2 game units in both directions: divide coordinates by 2.
  // multiply by 128 (MAP_WIDTH_TILES)
  if(index_of_tile_at_coordinates(current_pt, x ,y) > tileset_buffer.last_passable) // is the tile solid?
    {// if so, return
      return 1;
    }
  else
    { // Is the y-coordinate odd (in the middle of a tile)? I.e., does a
      // 2-unit-tail enemy also touch the next tile down?
      if(y % 2 == 0)
	{ // we're on an even tile boundary, no need to test another tile
	  return 0;
	}
      else
	{
	  if(index_of_tile_at_coordinates(current_pt, x ,y+1) > tileset_buffer.last_passable)
	    {
	      return 1;
	    }
	  else
	    {
	      return 0;
	    }
	}
    }
}
// Play SOUND_DAMAGE and subtract 1 unit from comic_hp, unless already at 0.
// Output:
//   comic_hp = decremented by 1 unless already at 0
void decrement_comic_hp()
{
  PLAY_SOUND(SOUND_DAMAGE);
  if(comic_hp != 0)
    {
      comic_hp--;
      blit(8, 16, // width and height
	   0, 0, // source x and y
	   240+comic_hp*8+1, 82, // target x and y 
	   8, GRAPHIC_METER_EMPTY, // source buffer
	   SCREEN_WIDTH, screen_buffer); // target buffer
    }
}

// Add 1 unit to comic_hp, unless comic_hp is already at MAX_HP, in which case
// award 1800 points.
// Output:
//   comic_hp = incremented by 1 unless already at MAX_HP
//   score = increased by 1800 point if comic_hp was MAX_HP
void increment_comic_hp()
{
  if(comic_hp == MAX_HP)
    { // overcharge, award 1800 points
      award_points(18);
    }
  else
    { // Add a unit to the HP meter in the UI.
      comic_hp++;
      blit(8, 16, // width and height
	   0, 0, // source x and y
	   240+comic_hp*8, 82, // target x and y 
	   8, GRAPHIC_METER_FULL, // source buffer
	   SCREEN_WIDTH, screen_buffer); // target buffer
    }
}

// Enter a new stage via a stage edge transition. Play
// SOUND_STAGE_EDGE_TRANSITION and jump to load_new_stage.
// Input:
//   ah = x-coordinate of Comic
//   al = y-coordinate of Comic
//   bl = new stage number
// Output:
//   comic_x_checkpoint = ah
//   comic_y_checkpoint = al
//   comic_y_vel = 0
//   source_door_level_number = -1
//   current_stage_number = bl
void stage_edge_transition(uint8_t stage_index)
{
  comic_x_checkpoint = comic_x;
  comic_y_checkpoint = comic_y;
  comic_y_vel = 0;
  source_door_level_number = -1; // we are not entering the new stage via a door
  current_stage_number = stage_index;
  PLAY_SOUND(SOUND_STAGE_EDGE_TRANSITION);
  load_new_stage();
}

void handle_fireballs()
{ // TODO: finish
}


// Go through the door pointed to by bx. Call enter_door, then load_new_level or
// load_new_level as appropriate.
// Input:
//   bx = pointer to door struct
//   current_level_number, current_stage_number = where the door is located
// Output:
//   current_level_number, current_stage_number = target of the door
//   source_door_level_number = former current_level_number
//   source_door_stage_number = former current_stage_number
void activate_door(door source_door)
{
  comic_x = source_door.x+1;
  comic_y = source_door.y;
  enter_door();
  // Mark that we're entering the new level/stage via a door.
  source_door_level_number = current_level_number;
  source_door_stage_number = current_stage_number;
  // Set the current level/stage to wherever the door leads.
  current_stage_number = source_door.target_stage;
  current_level_number = source_door.target_level;
  // it it another stage in the same level?
  if(current_level_number == source_door_level_number)
    {
      load_new_stage();
    }
  else
    {
      load_new_level();
    }
}

void comic_dies()
{ // TODO: finish
}

// Handle Comic movement when comic_is_falling_or_jumping == 1. Apply upward
// acceleration due to jumping, apply downward acceleration due to gravity,
// check for solid ground, and handle midair left/right movement.
// Input:
//   si = coordinates of Comic
//   key_state_left, key_state_right, key_state_jump = state of inputs
//   current_level_number = if LEVEL_NUMBER_SPACE, use lower gravity
//   comic_jump_counter = how many ticks Comic can continue moving upward
//   comic_x_momentum = Comic's current x momentum
//   comic_y_vel = Comic's current y velocity, in units of 1/8 game units per tick
//   comic_facing = COMIC_FACING_RIGHT or COMIC_FACING_LEFT
// Output:
//   si = updated coordinates of Comic
//   comic_is_falling_or_jumping = updated
//   comic_jump_counter = decremented by 1 unless already at 1
//   comic_x_momentum = updated
//   comic_y_vel = updated
//   comic_facing = updated
void handle_fall_or_jump(uint8_t jump_key_pressed, uint8_t left_key_pressed, uint8_t right_key_pressed)
{
  // Are we still in the state where a jump can continue accelerating
  // upward? When comic_jump_counter is 1, the upward part of the jump is
  // over.
  comic_jump_counter--;
  if(comic_jump_counter == 0)
    { // when it hits bottom, this jump can no longer accelerate upward
      // The upward part of the jump is over (comic_jump_counter was 1 when
      // the function was called, and just became 0). Clamp it to a minimum
      // value of 1.
      comic_jump_counter++;
    }
  else
    { // We're still able to accelerate upward in this jump. Is the jump key
      // still being pressed?
      if(jump_key_pressed)
	{ // We're still accelerating upward in this jump. Subtract a fixed value
	  // from the vertical velocity.
	  comic_y_vel -= 7;
	}
    }
  comic_y += comic_y_vel / 8;
  if(comic_y < 0) // did comic_y just become negative (above the top of the screen)?
    {
      comic_y = 0; //  clip to the top of the screen
    }
  // Is the top of Comic's head within 3 units of the bottom of the screen
  // (i.e., his feet are below the bottom of the screen)?
  if(comic_y < PLAYFIELD_HEIGHT - 3)
    { // if so, it's a death by falling
      comic_dies();
    }
  // apply gravity
  if(current_level_number == LEVEL_NUMBER_SPACE)
    { // if so, low gravity.
      comic_y_vel -= COMIC_GRAVITY - COMIC_GRAVITY_SPACE;
    }
  comic_y_vel += COMIC_GRAVITY;
  // Clip downward velocity.
  if(comic_y_vel > TERMINAL_VELOCITY)
    comic_y_vel = TERMINAL_VELOCITY;
  // Adjust comic_x_momentum based on left/right inputs.
  // TODO: finish

  // check solidity_upward
  // While moving upward, we check the solidity of the tile Comic's head
  // is in. While moving downward, we instead check the solidity of the
  // tile under his feet.
  if(is_solid(comic_x, comic_y))
    {
      if(comic_x % 2 == 1) // is Comic halfway between two tiles (comic_x is odd)?
	{ // if so, also check the solidity of the tile 1 to right
	  if(is_solid(comic_x+1, comic_y))
	    { // bounce downward off the ceiling
	      comic_y_vel = 8;
	    }
	}
      else
	{
	  comic_y_vel = 8;
	}
    }
  // check_solidity_downward:
  // Are we even moving downward?
  if(comic_y_vel > 0)
    {
      if(is_solid(comic_x, comic_y + 5))
	{
	  if(comic_x % 2 == 1) // is Comic halfway between two tiles (comic_x is odd)?
	    { // if so, also check the solidity of the tile 1 to right
	      if(is_solid(comic_x+1, comic_y + 5))
		{ // bounce downward off the ceiling
		  goto hit_the_ground;
		}
	    }
	  else
	    {
	      goto hit_the_ground;
	    }
	}
    }
 still_falling_or_jumping:
  comic_animation = COMIC_JUMPING;
  return;
 hit_the_ground:
  // Above, under .check_solidity_downward, we checked the tile at
  // (comic_x, comic_y + 5) and found it to be solid. But if comic_y is 15
  // or greater (i.e., comic_y + 5 is 20 or greater), that tile lookup
  // actually looked at garbage data outside the map. Override the earlier
  // decision and act as if the tile had not been solid, because there can
  // be nothing solid below the bottom of the map.
  if(comic_y < PLAYFIELD_HEIGHT - 5)
    { // Now we actually are about to hit the ground. Clamp Comic's feet to an
      // even tile boundary and reset his vertical velocity to 0.
      comic_y++;
      comic_y = comic_y & 0xFE;
      comic_is_falling_or_jumping = 0;
      comic_y_vel = 0;
    }
  else
    {
      goto still_falling_or_jumping;
    }
}

void increment_fireball_meter()
{ // TODO: finish
}

void decrement_fireball_meter()
{ // TODO: finish
}

void try_to_fire()
{ // TODO: finish
  
}

// Move Comic to the left if possible. If hitting a stage edge, jump to
// stage_edge_transition.
// Input:
//   si = coordinates of Comic
// Output:
//   si = updated coordinates of Comic
//   camera_x = moved left if appropriate
//   comic_animation = comic_run_cycle if now moving left
void move_left()
{
  stage current_stage = current_level.stages[current_stage_number];
  if(comic_x == 0) // at far left edge of a stage
    { // We're at the left edge of a stage. Check for a stage transition here.
      if(current_stage.exit_l != EXIT_UNUSED)
	{// There is a stage transition here. Load the new stage.
	  comic_x = MAP_WIDTH-2;
	  stage_edge_transition(current_stage.exit_l);
	}
      else
	{
	  return;
	}
    }
  else
    { // try moving left 1 half-tile
      // did we try to walk into a solid tile?
      if(is_solid(comic_x-1, comic_y+3))
	{ // if so, stop moving and return
	  return;
	}
      else
	{
	  comic_x--;
	  // Comic is now moving; enter a run animation. comic_run_cycle is
	  // COMIC_RUNNING_1, COMIC_RUNNING_2, or COMIC_RUNNING_3.
	  comic_animation = comic_run_cycle;
	  // Move the camera left too, unless the camera is already at the far
	  // left edge, or Comic is on the right half of the screen (keep the
	  // camera still until he reaches the center).
	  if(camera_x == 0)
	    { // camera is already at far left edge
	      return;
	    }
	  else
	    {
	      if(comic_x - camera_x < PLAYFIELD_WIDTH / 2 - 2)
		{
		  camera_x--;
		}
	      else
		{ // Comic is on the right half of the screen
		  return;
		}
	    }
	}
    }
}

// If Comic is not already facing left, face left. If already facing left, jump
// to move_left.
// Input:
//   si = coordinates of Comic
//   comic_facing = COMIC_FACING_RIGHT or COMIC_FACING_LEFT
// Output:
//   si = updated coordinates of Comic
//   comic_facing = COMIC_FACING_LEFT
//   comic_facing = updated
//   camera_x = moved left if appropriate
//   comic_animation = comic_run_cycle if now moving left
void face_or_move_left()
{
    if(comic_facing == COMIC_FACING_LEFT) // already facing right?
    {
      move_left();
    }
  else
    {
      comic_facing = COMIC_FACING_LEFT;
    }
}


// Move Comic to the right if possible. If hitting a stage edge, jump to
// stage_edge_transition.
// Input:
//   si = coordinates of Comic
// Output:
//   si = updated coordinates of Comic
//   camera_x = moved left if appropriate
//   comic_animation = comic_run_cycle if now moving right
void move_right()
{
  stage current_stage = current_level.stages[current_stage_number];
  if(comic_x == MAP_WIDTH - 2) //at the far right edge of a stage?
    { // We're at the right edge of a stage. Check for a stage transition
      // here.
      if(current_stage.exit_r != EXIT_UNUSED)
	{// There is a stage transition here. Load the new stage.
	  comic_x = 0;
	  stage_edge_transition(current_stage.exit_r);
	}
      else
	{
	  return;
	}
    }
  else
    { // try moving right 1 half-tile
      // did we try to walk into a solid tile?
      if(is_solid(comic_x-1, comic_y+3))
	{ // if so, stop moving and return
	  return;
	}
      else
	{
	  comic_x++;
	  // Comic is now moving; enter a run animation. comic_run_cycle is
	  // COMIC_RUNNING_1, COMIC_RUNNING_2, or COMIC_RUNNING_3.
	  comic_animation = comic_run_cycle;
	  // Move the camera right too, unless the camera is already at the far
	  // left edge, or Comic is on the right half of the screen (keep the
	  // camera still until he reaches the center).
	  if(camera_x >= MAP_WIDTH - PLAYFIELD_WIDTH)
	    { // camera is already at far left edge
	      return;
	    }
	  else
	    {
	      if(comic_x - camera_x < PLAYFIELD_WIDTH / 2)
		{ // Comic is on the left half of the screen
		  return;
		}
	      else
		{ 
		  camera_x++;
		}
	    }
	}
    }
}

// If Comic is not already facing right, face right. If already facing right,
// jump to move_right.
// Input:
//   si = coordinates of Comic
//   comic_facing = COMIC_FACING_RIGHT or COMIC_FACING_LEFT
// Output:
//   si = updated coordinates of Comic
//   comic_facing = COMIC_FACING_RIGHT
//   camera_x = moved left if appropriate
//   comic_animation = comic_run_cycle if now moving left
void face_or_move_right()
{
  if(comic_facing == COMIC_FACING_RIGHT) // already facing right?
    {
      move_right();
    }
  else
    {
      comic_facing = COMIC_FACING_RIGHT;
    }
}

// Main game loop. Block until it's time for a game tick, do one tick's worth of
// game logic, then repeat. When win_counter reaches 1, jump to
// game_end_sequence.
//
// Input:
//   game_tick_flag = game_loop blocks until int8_handler sets this variable to 1
//   win_counter = 0 if the win condition is not activated yet// otherwise counter until game end
//   key_state_jump, key_state_fire, key_state_left, key_state_right,
//     key_state_open, key_state_teleport, key_state_esc = state of inputs
// Output:
//   game_tick_flag = 0
//   win_counter = decremented by 1 if not already 0
//
// Reads and writes many other global variables, either directly in game_loop or
// in subroutines.
void game_loop()
{
  SDL_Event event;
  while(1)
    {
      wait_n_ticks(1);
      // poll keyboard events
      uint8_t jump_key_pressed = 0;
      uint8_t open_key_pressed = 0;
      uint8_t teleport_key_pressed = 0;
      uint8_t left_key_pressed = 0;
      uint8_t right_key_pressed = 0;
      uint8_t pause_key_pressed = 0;
      uint8_t fire_key_pressed = 0;
      while(SDL_PollEvent(&event))
	{
	  
	  if(event.type == SDL_KEYDOWN)
	    {
	      switch(event.key.keysym.scancode)
		{
		case SDL_SCANCODE_SPACE:
		case SDL_SCANCODE_W:
		case SDL_SCANCODE_UP:
		  jump_key_pressed = 1;
		  break;
		case SDL_SCANCODE_RALT:
		case SDL_SCANCODE_LALT:
		  open_key_pressed = 1;
		  break;
		case SDL_SCANCODE_RSHIFT:
		case SDL_SCANCODE_LSHIFT:
		  teleport_key_pressed = 1;
		  break;
		case SDL_SCANCODE_A:
		case SDL_SCANCODE_LEFT:
		  left_key_pressed = 1;
		  break;
		case SDL_SCANCODE_D:
		case SDL_SCANCODE_RIGHT:
		  right_key_pressed = 1;
		  break;
		case SDL_SCANCODE_PAUSE:
		case SDL_SCANCODE_ESCAPE:
		  pause_key_pressed = 1;
		  break;
		case SDL_SCANCODE_0:
		case SDL_SCANCODE_INSERT:
		  fire_key_pressed = 1;
		  break;
		default: break;
		}
	    }
	}
      
      // tick
      // If win_counter is nonzero, we are waiting out the clock to start the
      // game end sequence. The game ends when win_counter decrements to 1.
      if(win_counter != 0)
	{
	  win_counter--;
	  if(win_counter == 1)
	    {
	      game_end_sequence();
	    }
	}
      // Advance comic_run_cycle in the cycle COMIC_RUNNING_1,
      // COMIC_RUNNING_2, COMIC_RUNNING_3.
      comic_run_cycle++;
      if(comic_run_cycle == COMIC_RUNNING_3 + 1) comic_run_cycle = COMIC_RUNNING_1;
      
      // Put Comic in the standing state by default for this tick; it may be
      // set otherwise according to input or other factors.
      comic_animation = COMIC_STANDING;

      // Is there HP pending to award?
      if(comic_hp_pending_increase != 0)
	{ // If so, award 1 unit of it.
	  comic_hp_pending_increase--;
	  increment_comic_hp();
	}
      
      // check teleport are we teleporting?
      if(comic_is_teleporting != 0)
	{
	  handle_teleport(); // skip blitting the map and Comic, because handle_teleport does it
	  goto handle_nonplayer_actors;
	}

      // are we jumping or falling?
      if(comic_is_falling_or_jumping != 0)
	handle_fall_or_jump(jump_key_pressed, left_key_pressed, right_key_pressed); // handle_fall_or_jump jumps back into game_loop.check_pause_input
      else
	{
	  // is the jump key being pressed?
	  if(jump_key_pressed != 0)
	    { // And is comic_jump_counter not exhausted? (I don't see how it could
	      // be, seeing as we've checked that comic_is_falling_or_jumping == 0
	      // already above.)
	      if(comic_jump_counter != 0)
		{ // Initiate a new jump
		  comic_is_falling_or_jumping = 1;
		  handle_fall_or_jump(jump_key_pressed, left_key_pressed, right_key_pressed);
		}
	    }
	  else
	    { // recharge jump counter
	      comic_jump_counter = comic_jump_power;
	    }
	  // check open input // Is the open key being pressed?
	  if(open_key_pressed != 0)
	    { // The open key is being pressed, now let's see if we're actually in
	      // front of a door.
	      stage current_stage = current_level.stages[current_stage_number];
	      for(size_t door_id = 0; door_id < MAX_NUM_DOORS; door_id++)
		{
		  uint8_t door_x = current_stage.doors[door_id].x;
		  uint8_t door_y = current_stage.doors[door_id].y;
		  if(door_y == comic_y && // require exact match in y-coordinate
		     comic_x - door_x >= 0 && // require comic_x - door.x to be 0, 1, or 2
		     comic_x - door_x <= 2 &&
		     comic_has_door_key) // Pressing the open key, in front of a door, but do we have the Door Key?
		    {
		      activate_door(current_stage.doors[door_id]); //tail call; activate_door calls load_new_level or load_new_stage, which jump back into game_loop
		      //return; // TODO: check if ok
		    }
		}
	    }
	  // check teleport input
	  if(teleport_key_pressed != 0)
	    { // The teleport key is being pressed. Do we have the Teleport Wand?
	      //if(comic_has_teleport_wand != 0)
		begin_teleport();
	    }
	  // check left input
	  comic_x_momentum = 0;
	  if(left_key_pressed != 0)
	    {
	      comic_x_momentum = -5;
	      face_or_move_left();
	    }
	  // check right input
	  if(right_key_pressed != 0)
	    {
	      comic_x_momentum = +5;
	      face_or_move_right();
	    }
	  // check for floor
	  if(!is_solid(comic_x, comic_y + 4)) // comic_y + 4 is the y-coordinate just below Comic's feet
	    { // is Comic halfway between two tiles (comic_x is odd)?
	      if(comic_x % 2 == 1)
		{
		  // if so, also check the solidity of the tile 1 to the right
		  if(!is_solid(comic_x+1, comic_y + 4))
		    { // We're not standing on solid ground (just walked off an edge). Start
		      // falling. The gravity when just starting to fall is 8 (i.e., 1 unit
		      // per tick for the first tick), but later in handle_fall_or_jump
		      // gravity will become 5 (0.625 units per tick per tick), or 3 in the
		      // space level (0.375 units per tick per tick).
		      comic_y_vel = 8;
		      // After walking off an edge, Comic has 2 units of momentum (will keep
		      // moving in that direction for 2 ticks, even if a direction button is
		      // not pressed).
		      if(comic_x_momentum < 0)
			comic_x_momentum = -2;
		      else if(comic_x_momentum > 0)
			comic_x_momentum = +2;
		      // now start falling, as if with a fully depleted jump
		      comic_is_falling_or_jumping = 1;
		      comic_jump_counter = 1;
		    }
		}
	    }
	}
      // check pause input
      if(pause_key_pressed != 0)
	pause();
      // check fire input
      if(fire_key_pressed != 0)
	{
	  if(fireball_meter != 0) // The fire key is being pressed. Is the fireball meter depleted?
	    { // Shoot a fireball.
	      try_to_fire();
	      // fireball_meter increases/decreases at a rate of 1 unit per 2 ticks.
	      // fireball_meter_counter alternates 2, 1, 2, 1, ... to let us know when
	      // we should adjust the meter. We decrement fireball_meter when
	      // fireball_meter_counter is 2 (and the fire key is being pressed), and
	      // increment fireball_meter when fireball_meter_counter is 1 (and the
	      // fire key is not being pressed).
	      if(fireball_meter_counter != 1)
		{ // fireball_meter_counter is 2; decrement fireball_meter and decrement
		  // fireball_meter_counter.
		  decrement_fireball_meter();
		  fireball_meter_counter = 2;
		}
	    }
	}
      else
	{
	  fireball_meter_counter--;
	  if(fireball_meter_counter == 0) // TODO: check
	    { // fireball_meter_counter was 1; increment fireball_meter and wrap
	      // fireball_meter_counter.
	      increment_fireball_meter();
	      fireball_meter_counter = 2;
	    }
	}
      // blit_map_and_comic
      blit_map_playfield_offscreen();
      blit_comic_playfield_offscreen();

    handle_nonplayer_actors:
      handle_enemies();
      handle_fireballs();
      handle_item();
      draw();
    }
}


// Initialize global data structures as appropriate for the value of
// current_stage_number. Render the map into RENDERED_MAP_BUFFER. Despawn all
// fireballs. Initialize enemy data structures. Jump to game_loop when done.
// Input:
//   current_level = filled-out level struct
//   current_stage_number = stage number to load
//   source_door_level_number = level number we came from, if via a door
//     -2 = beam in at the start of game
//     -1 = not entering this stage via a door
//     other = level number containing the door we came through
//   source_door_stage_number = stage number we came from, if via a door
// Output:
//   current_tiles_ptr = address of the map tiles for this stage
//   current_stage_ptr = address of the stage struct for this stage
//   RENDERED_MAP_BUFFER = filled in with the current map
//   comic_y, comic_x = Comic's initial coordinates in the stage
//   comic_y_checkpoint, comic_x_checkpoint = Comic's initial position in the stage
//   camera_x = camera position appropriate for Comic's position
//   fireballs = despawned
//   enemies = initialized
void load_new_stage()
 {
   stage current_stage = (LEVEL_DATA_POINTERS[current_level_number])->stages[current_stage_number];
   render_map();
   // Are we entering this stage via a door? If so, we need to find the
   // door in this stage that links back to the stage we came from. Comic
   // will be located in front of that door.
   if(source_door_level_number >= 0) // negative means we didn't arrive via a door
     { // Search for a door in this stage that points back to the level and
       // stage we came from.
       for(size_t i = 0; i < MAX_NUM_DOORS; i++)
	 if(current_stage.doors[i].target_level == source_door_level_number
	    && current_stage.doors[i].target_stage == source_door_stage_number)
	   {
	     comic_x_checkpoint = current_stage.doors[i].x + 1;
	     comic_y_checkpoint = current_stage.doors[i].y;
	   }
     }
   // End any teleport that may be in progress on entering the stage. Comic
   // may have died mid-teleport and is now respawning.
   comic_is_teleporting = 0;

   // Despawn all fireballs.
   for(size_t i = 0; i < MAX_NUM_FIREBALLS; i++)
     {
       fireballs[i].x = FIREBALL_DEAD;
       fireballs[i].x = FIREBALL_DEAD;
     }
   comic_x = comic_x_checkpoint;
   comic_y = comic_y_checkpoint;

   // Set camera_x = clamp(comic_x - 1 - PLAYFIELD_WIDTH/2, 0, MAP_WIDTH - PLAYFIELD_WIDTH)
   camera_x = comic_x - 1 - PLAYFIELD_WIDTH/2;
   if(camera_x < 0) camera_x = 0;
   else if(camera_x > MAP_WIDTH - PLAYFIELD_WIDTH) camera_x = MAP_WIDTH - PLAYFIELD_WIDTH;

   // Initialize enemies.
   for(size_t i = 0; i < MAX_NUM_ENEMIES; i++)
     { // Skip initializing this enemy if its shp_index is 0xff. This code is
       // never actually used, as unused enemy slots are actually marked with
       // enemy_record.behavior == ENEMY_BEHAVIOR_UNUSED and have
       // enemy_record.shp_index == 0.
       if(current_stage.enemies[i].shp_index == 0xFF)
	 { //It's not clear what this next instruction is supposed to do. An
	   // enemy.restraint of 0xff would just overflow to
	   // ENEMY_RESTRAINT_MOVE_THIS_TICK in the next tick.
	   enemies[0].restraint = 0xFF; // TODO: investigate
	 }
       else // TODO: finish
	 {
	 }
     }
   if(source_door_level_number == -2)
     { // beginning of the game, play beam_in animation
       source_door_level_number = -1; // unset the "first spawn" flag
       beam_in();
     }
   else if(source_door_level_number >= 0)
     {
       exit_door(); // arriving via a door, play door animation
       source_door_level_number = -1; // unset the "came through a door" flag
     }
   game_loop();
 }

// Load a .SHP file. Store the graphics data and an animation cycle pointing
// into graphics, possibly by duplicates depending on whether the enemy has
// distinct left/right facing graphics, and its animation mode.
// Input:
//   ds:si = address of initialized shp struct
//   es:di = array[10] of 16×16 masked graphics
//   ds:dx = animation cycle, array[10] of pointers into es:di array
void load_shp_file(shp ship, uint8_t ship_index)
{
  uint8_t num_frames = ship.num_distinct_frames;
  // If horizontal != ENEMY_HORIZONTAL_DUPLICATED, assume
  // horizontal == ENEMY_HORIZONTAL_SEPARATE. Double the number of frames
  // to account for separate left-facing and right-facing graphics.
  if(ship.horizontal == ENEMY_HORIZONTAL_SEPARATE)
    {
      num_frames *= 2;
    }
  // Each frame is 160 bytes long: 128 bytes for the four EGA planes, and
  // 32 bytes for the mask. Compute the total number of bytes to read.
  size_t ega_size = num_frames*16*16*5/8;
  FILE * f = fopen(ship.filename, "rb");
  fread(enemy_raw, 1, ega_size, f);
  fclose(f);
  // convert to RGB32
  size_t rgb_offset = 0;
  size_t planes = 5;
  for(size_t ega_offset = 0; 
      ega_offset < ega_size / 2; // ega_length = ega_size / 2 (4bbp)
      ega_offset+=16*16*planes/8, rgb_offset+=16*16*4)
    {
      EGA_to_32(16*16*planes/8, planes, enemy_raw + ega_offset, enemy_graphics[ship_index] + rgb_offset);
    }
  //left facing; Reference the left-facing frames.
  rgb_offset = 0;
  uint8_t animation_index = 0;
  for(; animation_index < ship.num_distinct_frames; animation_index++)
    {
      // store the current graphic in the output array
      enemy_animation_frames[ship_index][animation_index] = enemy_graphics[ship_index] + rgb_offset;
      rgb_offset += 16*16*4; // advance to the next graphic
    }
  rgb_offset += 16*16*4;
  animation_index++;
  // does this animation loop or alternate?
  // If animation != ENEMY_ANIMATION_LOOP, assume
  // animation == ENEMY_ANIMATION_ALTERNATE. Make frame n a copy of
  // frame n-2.
  if(ship.animation == ENEMY_ANIMATION_ALTERNATE)
    {
      rgb_offset -= 16*16*4*2; // seek backward 2 frames
      enemy_animation_frames[ship_index][animation_index] = enemy_graphics[ship_index] + rgb_offset; // store a duplicate reference for this frame
      rgb_offset += 16*16*4*2; // return to where we were
    }
  // right facing
  // Read the right-facing frames. Depending on the value of horizontal,
  // these may be duplicates of the left-facing frames or may be separate
  // graphics.

  // If horizontal != ENEMY_HORIZONTAL_SEPARATE, assume
  // horizontal == ENEMY_HORIZONTAL_DUPLICATED. Reset dx to the beginning
  // of the graphics data.
  if(ship.horizontal == ENEMY_HORIZONTAL_DUPLICATED)
    {
      rgb_offset = 0;
    }
  animation_index = 0;
  for(; animation_index < ship.num_distinct_frames; animation_index++)
    {
      // store the current graphic in the output array
      enemy_animation_frames[ship_index][animation_index + ENEMY_FACING_RIGHT] = enemy_graphics[ship_index] + rgb_offset;
      rgb_offset += 16*16*4; // advance to the next graphic
    }
  rgb_offset += 16*16*4;
  animation_index++;
  // does this animation loop or alternate?
  if(ship.animation == ENEMY_ANIMATION_ALTERNATE)
    {
      rgb_offset -= 16*16*4*2; // seek backward 2 frames
      enemy_animation_frames[ship_index][animation_index+ENEMY_FACING_RIGHT] = enemy_graphics[ship_index] + rgb_offset; // store a duplicate reference for this frame
      rgb_offset += 16*16*4*2; // return to where we were
    }
}



// Load the four .SHP files named in the current_level struct
// Input:
//   current_level = level struct with initialized .shp member
// Output:
//   enemy_graphics = array[4][10] of 16×16 masked graphics
//   enemy_animation_frames = array[4][10] of pointers into enemy_graphics (possibly with duplicates)
//   enemy_num_animation_frames = array[4] of animation frame counts
void load_shp_files()
{
  for(size_t i = 0; i < MAX_NUM_ENEMIES; i++)
    {
      shp ship = current_level.shps[i];
      if(ship.num_distinct_frames == SHP_UNUSED) break;
      enemy_num_animation_frames[i] = ship.num_distinct_frames + ship.animation;
      load_shp_file(ship, i);
    }
  load_new_stage();
}
// Initialize global data structures as appropriate for the value of
// current_level_number. Jump to load_shp_files when done.

// A "level" is a group of three stages sharing the same tileset, like CASTLE,
// FOREST, etc. A "stage" is a single 128×10 map, corresponding to a .PT file.

// Input:
//   current_level_number = level number to load
//   comic_has_lantern = if != 1, and current_level_number == LEVEL_NUMBER_CASTLE, black out tile graphics
// Output:
//   current_level = filled-out level struct, copied from level_data
//   tileset_buffer = array of tile graphics
void load_new_level()
 {
   current_level = *(LEVEL_DATA_POINTERS[current_level_number]);
   // Load the .TT2 file (tileset graphics)
   size_t header_size = 4;
   FILE * f = fopen(current_level.tt2_filename, "rb");
   size_t ega_size = fread(tileset_buffer_raw, 1, file_size(f), f);
   fclose(f);
   tileset_buffer.last_passable = *tileset_buffer_raw;
   tileset_buffer.flags = tileset_buffer_raw[4];
   // tileset_buffer.graphics ; each plane contains 16*16 pixels
   size_t rgb_offset = 0;
   for(size_t ega_offset = header_size; 
       ega_offset < ega_size * 8 / 2 && rgb_offset < sizeof(tileset_buffer.graphics); // ega_length = ega_size / 2 (4bbp)
       ega_offset+=16*16/2, rgb_offset+=16*16*4)
     {
       EGA_to_32(16*16/2, 4, tileset_buffer_raw + ega_offset, tileset_buffer.graphics + rgb_offset);
     }
   // lantern check
   if(current_level_number == LEVEL_NUMBER_CASTLE && !comic_has_lantern)
     { // in castle, without lantern
       memset(tileset_buffer.graphics, 0, rgb_offset);// override all tileset graphics with zeroes
     }
   // load pt files ; Load the three .PT files for this level.
   f = fopen(current_level.pt0_filename, "rb"); // PT0
   fread(pt0_raw, 1, file_size(f), f);
   fclose(f);
   pt0.width = *(((uint16_t*)pt0_raw) + 0);
   pt0.height = *(((uint16_t*)pt0_raw) + 1);
   pt0.tiles = pt0_raw + 2*2;
   f = fopen(current_level.pt1_filename, "rb"); // PT1
   fread(pt1_raw, 1, file_size(f), f);
   fclose(f);
   pt1.width = *(((uint16_t*)pt1_raw) + 0);
   pt1.height = *(((uint16_t*)pt1_raw) + 1);
   pt1.tiles = pt1_raw + 2*2;
   f = fopen(current_level.pt2_filename, "rb"); // PT2
   fread(pt2_raw, 1, file_size(f), f);
   fclose(f);
   pt2.width = *(((uint16_t*)pt2_raw) + 0);
   pt2.height = *(((uint16_t*)pt2_raw) + 1);
   pt2.tiles = pt2_raw + 2*2;
   // load shp files
   load_shp_files();
 }

int main(int argc, char * argv[])
{
  // parse args
  
  if(graphics_enabled) init_UI();
  if(sound_enabled) init_sound();
  if(graphics_enabled || sound_enabled) title_sequence();
  initialize_lives_sequence();
  load_new_level();
  wait_keypress();
  return 0;
}
