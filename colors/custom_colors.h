#include <stdio.h>
#include <stdlib.h>
#include <string>

class Gear {
public:
  std::string name;
  unsigned int offset;
  unsigned char R;
  unsigned char G;
  unsigned char B;
};

// Navi
class Navi {
public:
  unsigned char normal_R;    //  Normal
  unsigned char normal_G;
  unsigned char normal_B;
  unsigned char normal_a;
  unsigned int nor_addr;
  
  unsigned char npc_R;         //  NPC's
  unsigned char npc_G;
  unsigned char npc_B;
  unsigned char npc_a;
  unsigned int npc_addr;

  unsigned char enemy_R;       //  Enemies
  unsigned char enemy_G;
  unsigned char enemy_B;
  unsigned char enemy_a;
  unsigned int enemy_addr;
  
  unsigned char sign_gstone_R; //  Signs, Stones
  unsigned char sign_gstone_G;
  unsigned char sign_gstone_B;
  unsigned char sign_gstone_a;
  unsigned int sign_addr;
  
  unsigned char check_spots_R; //  Checkable spots
  unsigned char check_spots_G;
  unsigned char check_spots_B;
  unsigned char check_spots_a;
  unsigned int check_addr;
  
  unsigned char boss_R;        //  Bosses
  unsigned char boss_G;
  unsigned char boss_B;
  unsigned char boss_a;
  unsigned int boss_addr;
};

Navi* make_navi() {

  Navi *navi = new Navi;
  
  navi->normal_R = 0xff;
  navi->normal_G = 0xff;
  navi->normal_B = 0xff;
  navi->normal_a = 0xff;
  navi->nor_addr = 0xb5e184;
  
  navi->npc_R = 0x00;
  navi->npc_G = 0x00;
  navi->npc_B = 0xff;
  navi->npc_a = 0x00;
  navi->npc_addr = 0xb5e188;
  
  navi->enemy_R = 0x00;
  navi->enemy_G = 0xff;
  navi->enemy_B = 0x00;
  navi->enemy_a = 0xff;
  navi->enemy_addr = 0xb5e18c;
  
  navi->sign_gstone_R = 0x96; 
  navi->sign_gstone_G = 0x96;
  navi->sign_gstone_B = 0xff;
  navi->sign_gstone_a = 0xff;
  navi->sign_addr = 0xb5e194;
  
  navi->check_spots_R = 0xff; 
  navi->check_spots_G = 0xff;
  navi->check_spots_B = 0x00;
  navi->check_spots_a = 0xff;
  navi->check_addr = 0xb5e19c;
  
  navi->boss_R = 0x00;
  navi->boss_G = 0xff;
  navi->boss_B = 0x00;
  navi->boss_a = 0xff;
  navi->boss_addr = 0xb5e1ac;

  return navi;
}

Gear* make_color_list() {

  Gear *gear_list;
  gear_list = ( Gear* ) malloc( sizeof( Gear ) * 5 );

  // Kokiri Tunic
  gear_list[0].offset = 0xb6da38;
  gear_list[0].R = 0x1e; 
  gear_list[0].G = 0x69;
  gear_list[0].B = 0x1b;

  // Goron Tunic
  gear_list[1].offset = 0xb6da3b;
  gear_list[1].R = 0x64;
  gear_list[1].G = 0x14;
  gear_list[1].B = 0x00;
  
  // Zora Tunic
  gear_list[2].offset = 0xb6da3e;
  gear_list[2].R = 0x00;
  gear_list[2].G = 0x3c;
  gear_list[2].B = 0x64;
  
  // Silver Gauntlets
  gear_list[3].offset = 0xb6da44;
  gear_list[3].R = 0xff;
  gear_list[3].G = 0xff;
  gear_list[3].B = 0xff;
  
  // Golden Gauntlets
  gear_list[4].offset = 0xb6da47;
  gear_list[4].R = 0xfe;
  gear_list[4].G = 0xcf;
  gear_list[4].B = 0x0f;

  return gear_list;
}

// create lists and modify game data
void custom_colors( unsigned char** game_ptr ) {

  Gear *list;
  Navi *navi;
  int i;

  unsigned char *game;
  game = *game_ptr;

  list = make_color_list();
  navi = make_navi();

  for ( i = 0; i < 5; i++ ) {
	game[ list[i].offset ] = list[i].R; 
    game[ list[i].offset+1 ] = list[i].G; 
    game[ list[i].offset+2 ] = list[i].B; 
  }

  game[ navi->nor_addr   ] = navi->normal_R;
  game[ navi->nor_addr+1 ] = navi->normal_G;
  game[ navi->nor_addr+2 ] = navi->normal_B;
  game[ navi->nor_addr+3 ] = navi->normal_a;
  
  game[ navi->npc_addr   ] = navi->npc_R;
  game[ navi->npc_addr+1 ] = navi->npc_G;
  game[ navi->npc_addr+2 ] = navi->npc_B;
  game[ navi->npc_addr+3 ] = navi->npc_a;
  
  game[ navi->enemy_addr   ] = navi->enemy_R;
  game[ navi->enemy_addr+1 ] = navi->enemy_G;
  game[ navi->enemy_addr+2 ] = navi->enemy_B;
  game[ navi->enemy_addr+3 ] = navi->enemy_a;
  
  game[ navi->sign_addr   ] = navi->sign_gstone_R;
  game[ navi->sign_addr+1 ] = navi->sign_gstone_G;
  game[ navi->sign_addr+2 ] = navi->sign_gstone_B;
  game[ navi->sign_addr+3 ] = navi->sign_gstone_a;
  
  game[ navi->check_addr   ] = navi->check_spots_R;
  game[ navi->check_addr+1 ] = navi->check_spots_G;
  game[ navi->check_addr+2 ] = navi->check_spots_B;
  game[ navi->check_addr+3 ] = navi->check_spots_a;
  
  game[ navi->boss_addr   ] = navi->boss_R;
  game[ navi->boss_addr+1 ] = navi->boss_G;
  game[ navi->boss_addr+2 ] = navi->boss_B;
  game[ navi->boss_addr+3 ] = navi->boss_a;

  game_ptr = &game;

  free( list );
  free( navi );
}




