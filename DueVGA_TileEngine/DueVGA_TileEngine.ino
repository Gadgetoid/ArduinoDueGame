/*
  This is a basic tile based game engine using
  a 20x16 grid of tiles, of values 0 to 255,
  each of which can have a function-based fragment
  shader accepting x and y values.
  
  The engine determines the tile it's rendering and
  calls its fragment shader function with the x and y
  values of that tile.
  
  It will also supply that tiles global x/y coords
*/
#include <VGA.h>
#include <stdint.h>
#include "assets.h"
#include "shaders.h"


// An array of function pointers is cool, but slower
/*unsigned char (*tile_fragment_shader[4])(uint16_t x, uint16_t y, uint16_t p_x, uint16_t p_y, unsigned char fragment_col) = {
  &tile_empty,
  &tile_solid,
  &tile_shadow,
  &tile_bevel
};*/

boolean tile_opacity[4] = {
  1,
  1,
  1,
  0 
};

uint16_t player_x = 10,
    player_y = RESY-TILE_SIZE-TILE_SIZE;
    /*player_width = player[0],
    player_height = player[1],
    player_framesize = (player_width*player_height)/2;*/
    
unsigned char player_frame = 0;

unsigned char paint_sprite(unsigned char* sprite,unsigned char sprite_frame,uint16_t sprite_x, uint16_t sprite_y, uint16_t pixel_x, uint16_t pixel_y, uint16_t fragment_col){
      
  // Ensure the pixel is within the bounds of the player
  if(
       pixel_x >= sprite_x
    && pixel_y >= sprite_y
    && pixel_x < sprite_x + TILE_SIZE
    && pixel_y < sprite_y + TILE_SIZE
   ){  
     int p_x = (pixel_x - sprite_x),
         p_y = (pixel_y - sprite_y),
         p_i,
         p_frame_offset = SPRITE_HEADER_SIZE + (sprite_frame*SPRITE_FRAME_OFFSET);
         
     p_i = (TILE_SIZE * p_y) + p_x;
     
     //if(player_frame>0)  //player_framesize);
         
     unsigned char pixel = p_i % 2 
         ?  sprite[(uint16_t)(p_i/2)+p_frame_offset]       & 0xf
         : (sprite[(uint16_t)(p_i/2)+p_frame_offset] >> 4) & 0xf;
     
     return pixel==0 ? fragment_col : get_player_palette(pixel,fragment_col); //player_palette[pixel-1];
     
  }
  return fragment_col;
}

/*unsigned char get_tile_at(int x,int y,int z){
  int tile_x = floor(x/TILE_SIZE),
      tile_y = floor(y/TILE_SIZE);
  
  return level[z][(tile_y*LEVEL_WIDTH)+tile_x];
}*/

unsigned char get_tile_fragment(uint16_t x,uint16_t y){
  uint16_t tile_x = floor(x/TILE_SIZE),
      tile_y = floor(y/TILE_SIZE),
      tile_i = (tile_y*LEVEL_WIDTH)+tile_x,
      // Get our x/y coords within the tile
      f_x = x % TILE_SIZE,
      f_y = y % TILE_SIZE;

  // Build up our fragment from the background colour
  // TODO: Grab initial pixel from a bitmap backdrop
  unsigned char tile_id = 0,
                tile_fragment = BACKGROUND_COLOR;
  
  // unsigned char tile_id = get_tile_at(x,y,z);
  
  // Pass them to the correct fragment shader
  unsigned char fg_tile = fg[tile_i],
                mg_tile = mg[tile_i],
                bg_tile = bg[tile_i];
  
  if( fg_tile == 3 ){
    //return tile_fragment_shader[tile_id](f_x,f_y,tile_x,tile_y,tile_fragment);
    return call_fragment_shader(fg_tile,f_x,f_y,tile_x,tile_y,tile_fragment);
  }
  
  //for(int z = 0;z<LEVEL_DEPTH;z++){

    if( bg_tile > 0 ) tile_fragment = call_fragment_shader(bg_tile,f_x,f_y,tile_x,tile_y,tile_fragment);
    
    //unsigned char before = tile_fragment;

    if( mg_tile > 0 ) tile_fragment = call_fragment_shader(mg_tile,f_x,f_y,tile_x,tile_y,tile_fragment);

    // Paint player here
    tile_fragment = paint_sprite(player,player_frame,player_x,player_y,x,y,tile_fragment);
    // Paint an enemy
    tile_fragment = paint_sprite(enemy,enemy_frame,enemy_x,enemy_y,x,y,tile_fragment);
    
    if( fg_tile > 0 ) tile_fragment = call_fragment_shader(fg_tile,f_x,f_y,tile_x,tile_y,tile_fragment);
  //}
  
  return tile_fragment;
}
/*
void generate_collision_map(){
  for(uint16_t x=0;x<RESX;x++)
  {
    for(uint16_t y=0;y<RESY;y++)
    {
      uint16_t i = y*RESX + x,
              tile_x = floor(x/TILE_SIZE),
              tile_y = floor(y/TILE_SIZE),
              tile_i = (tile_y*LEVEL_WIDTH)+tile_x,
              // Get our x/y coords within the tile
              f_x = x % TILE_SIZE,
              f_y = y % TILE_SIZE;
      
      unsigned char mg_tile = mg[tile_i];
      
      collision[i] = 0;
      
      if( mg_tile > 0 && call_fragment_shader(mg_tile,f_x,f_y,tile_x,tile_y,255) != 255 ){
        collision[i] = 1;
      }
      
    }
  }
}*/

/*void display_collision_map(){
  for(uint16_t x=0;x<RESX;x++)
  {
    for(uint16_t y=0;y<RESY;y++)
    {
      uint16_t i = y*RESX + x;
      if(collision[i]) VGA.putCPixelFast(x,y,0xF3);
    }
  }
  delay(2000);
}*/

void redraw_rect(uint16_t rect_x,uint16_t rect_y,uint16_t width,uint16_t height){
  for(uint16_t x=0;x<width;x++)
  {
    for(uint16_t y=0;y<height;y++)
    {
      VGA.putCPixelFast(
        OFFSET_LEFT+x+rect_x,
        OFFSET_TOP+y+rect_y,
        get_tile_fragment(x+rect_x,y+rect_y)
      );
    }
  }
}

int s = 0;

void setup() {
  int fragment_col = BACKGROUND_COLOR;
  VGA.begin(320,240,VGA_COLOUR);
  
  redraw_rect(0,0,RESX,RESY);
  //generate_collision_map();
  //display_collision_map();
  
  /*
  for(int x = 0;x<RESX;x++){
    double h = map(x,0,319,0,360);
    for(int y = 0;y<RESY;y++){
      double v = map(y,0,239,0,100);
      VGA.putCPixelFast(
        x,
        y,
        hsv_to_rgb(h,100,v)
      );
    }
  }*/
}

void loop() {
  uint16_t last_x = player_x,
           last_y = player_y;
  player_x+=1;

  if(player_x + TILE_SIZE > RESX){
   player_x = 0; 
   redraw_rect(last_x,last_y,TILE_SIZE,TILE_SIZE);
  }
  
  //redraw_rect(last_x,last_y,player[0],player[1]);
  redraw_rect(player_x-1,player_y,1,TILE_SIZE);
  redraw_rect(player_x,player_y,TILE_SIZE,TILE_SIZE);
  
  // redraw part of the screen to simulate drawing enemy sprites
  redraw_rect(88,0,32,32);
  
  //redraw_rect(0,0,RESX,RESY);
  
  if( player_x % 8 == 0 ){
    player_frame++;
  }
  
  if(player_frame >= player[0]){
   player_frame = 0; 
  }
  
  //delay(500);
}

/*
  Converts HSV to RRRGGGBB
  Values:
    H: 0 to 360
    S: 0 to 100
    V: 0 to 100
*/
unsigned char hsv_to_rgb(int H, int S, int V) 
{
  int r, g, b;
  int f, w, q, t, i;
  
  if( S == 0 ) return (round(V*0.07)<<5) + (round(V*0.07)<<2) + round(V * 0.03);

  i = H/60;
  f = (((H * 100) / 60) - (i * 100));
  w = V * (100 - S) / 100;
  q = V * (100 * 100 - (S * f)) / 10000;
  t = V * (100 * 100 - (S * (100 - f))) / 10000;
  switch( i ) {
    case 0: case 6: r = V, g = t, b = w; break;
    case 1: r = q, g = V, b = w; break;
    case 2: r = w, g = V, b = t; break;
    case 3: r = w, g = q, b = V; break;
    case 4: r = t, g = w, b = V; break;
    case 5: r = V, g = w, b = q; break;
  }
  return (round(r*0.07)<<5) + (round(g*0.07)<<2) + round(b * 0.03);
}
