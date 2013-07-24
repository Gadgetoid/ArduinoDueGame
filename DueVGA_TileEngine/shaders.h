unsigned char tile_solid(uint16_t x, uint16_t y, uint16_t p_x, uint16_t p_y, unsigned char fragment_col){
  return 255;
}
unsigned char tile_shadow(uint16_t x, uint16_t y, uint16_t p_x, uint16_t p_y, unsigned char fragment_col){
  if(y%2){return x%2?SHADOW_COLOR:fragment_col;}
  else{return x%2?fragment_col:SHADOW_COLOR;}
}
unsigned char tile_bevel(uint16_t x, uint16_t y, uint16_t p_x, uint16_t p_y, unsigned char fragment_col){
 // Top highlight
 if(
   y < TILE_BEVEL &&
   (
     x>=y
   )
 ){
  return 0x7F;
 } 
 // Bottom shadow
 if(
   y > TILE_SIZE-TILE_BEVEL-1 &&
   (
     x<=y
   )
 ){
   return 0x6F;
 }
 // Left highlight
 if(x < TILE_BEVEL){
  return 0x7B; 
 }
 // Right shadow
 if(x > TILE_SIZE-TILE_BEVEL-1){
  return 0x73; 
 }
 return 0x77;
}
unsigned char tile_empty(uint16_t x, uint16_t y, uint16_t p_x, uint16_t p_y, unsigned char fragment_col){
  return fragment_col;
}

unsigned char call_fragment_shader(uint16_t tile_id,uint16_t x, uint16_t y, uint16_t p_x, uint16_t p_y, unsigned char fragment_col){
    switch(tile_id){
      case 0: return tile_empty(x,y,p_x,p_y,fragment_col);
      case 1: return tile_solid(x,y,p_x,p_y,fragment_col);
      case 2: return tile_shadow(x,y,p_x,p_y,fragment_col);
      case 3: return tile_bevel(x,y,p_x,p_y,fragment_col);
    }
    return fragment_col;
}
