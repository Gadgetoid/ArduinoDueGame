#define RESX 320
#define RESY 240
#define LEVEL_WIDTH 20
#define LEVEL_HEIGHT 15
#define TILE_SIZE 16
#define TILE_BEVEL 2
#define BACKGROUND_COLOR 0x6E
#define SHADOW_COLOR 0x00
#define LEVEL_DEPTH 2
#define SPRITE_HEADER_SIZE 3

/*
  This is a colour palette, it should be
  addressed with a 1 based index of range
  1 to 15. Index 0 is reserved for transparent
*/
unsigned char player_palette[15] = {
  0x83,0x87,0x8B,0x8F,0x93,
  0x97,0x9B,0x9F,0x82,0x86,
  0x8A,0x8E,0x92,0x96,0x20
};

unsigned char get_player_palette(uint8_t color,unsigned char fragment_col){
 switch(color){
  case 1: return 0x83;
  case 2: return 0x87;
  case 3: return 0x8B;
  case 4: return 0x8F;
  case 5: return 0x93;
  case 6: return 0x97;
  case 7: return 0x9B;
  case 8: return 0x9F;
  case 9: return 0x82;
  case 10: return 0x86;
  case 11: return 0x8A;
  case 12: return 0x8E;
  case 13: return 0x92;
  case 14: return 0x96;
  case 15: return 0x20;
 } 
}

/* 
  This is a 15-colour, paletized, packed
  player sprite with 1 frame.
  
  Colour 0 = transparent.
*/
unsigned char player[259] = {
 16,  // Width
 16,  // Height
 2,   // Frame Count
 0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,
 0x00,0x00,0x0F,0xFF,0xFF,0xF0,0x00,0x00,
 0x00,0x00,0x0F,0xAF,0xFA,0xF0,0x00,0x00,
 0x00,0x00,0x0F,0xFF,0xFF,0xF0,0x00,0x00,
 0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,
 0x00,0x00,0x00,0x0F,0xF0,0x00,0x00,0x00,
 0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,
 0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,
 0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,
 0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,
 0x00,0x00,0x00,0xF0,0x0F,0x00,0x00,0x00,
 0x00,0x00,0x00,0xF0,0x0F,0x00,0x00,0x00,
 0x00,0x00,0x00,0xF0,0x0F,0x00,0x00,0x00,
 0x00,0x00,0x00,0xF0,0x0F,0x00,0x00,0x00,
 0x00,0x00,0x00,0xF0,0x0F,0x00,0x00,0x00,
 0x00,0x00,0x00,0xF0,0x0F,0x00,0x00,0x00,
 
 0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,
 0x00,0x00,0x0F,0xFF,0xFF,0xF0,0x00,0x00,
 0x00,0x00,0x0F,0xAF,0xFA,0xF0,0x00,0x00,
 0x00,0x00,0x0F,0xFF,0xFF,0xF0,0x00,0x00,
 0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,
 0x00,0x00,0x00,0x0F,0xF0,0x00,0x00,0x00,
 0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x00,0x00,
 0x00,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0x00,
 0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,
 0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,
 0x00,0x00,0x00,0xF0,0x0F,0x00,0x00,0x00,
 0x00,0x00,0x00,0xF0,0x0F,0x00,0x00,0x00,
 0x00,0x00,0x0F,0x00,0x0F,0x00,0x00,0x00,
 0x00,0x00,0xF0,0x00,0x0F,0x00,0x00,0x00,
 0x00,0x00,0xF0,0x00,0x0F,0x00,0x00,0x00,
 0x00,0x00,0xF0,0x00,0x0F,0x00,0x00,0x00
};

unsigned char bg[LEVEL_WIDTH*LEVEL_HEIGHT] = {
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x02,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,
  0x00,0x02,0x02,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};
unsigned char mg[LEVEL_WIDTH*LEVEL_HEIGHT] = {
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x03,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x03,0x03,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x00,
  0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03
};
unsigned char fg[LEVEL_WIDTH*LEVEL_HEIGHT] = {
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};