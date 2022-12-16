#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <nds.h>
#include <nf_lib.h>
#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"

#include "define.h"
#include "structs.h"

const u16_f SOUNDFILE[SOUNDFILESIZE] = {SFX_BH00, SFX_BH01, SFX_BH02, SFX_BH03, SFX_BH04, SFX_BH10, SFX_BH11, SFX_BH12, SFX_BH13, SFX_BH14, SFX_BH20, SFX_BH21, SFX_BH22, SFX_BH23, SFX_BH24, SFX_BH30, SFX_BH31, SFX_BH32, SFX_BH33, SFX_BH34};
const u16_f MUSICFILE[MUSICFILESIZE] = {MOD_GANIOU, MOD_REIMP, MOD_BAISE, MOD_CAVE};

int cam_x;
int cam_y;

map* curmap;
obj* player;

u16_f timer;

int scol = 0;

bool checkCollision(int x1, int y1, int sx1, int sy1, int x2, int y2, int sx2, int sy2){
	if(x1+sx1 > x2 && x1 < x2+sx2){
		if(y1+sy1 > y2 && y1 < y2+sy2){
			return true;
		}
	}
	return false;
}

void crashgame(char* msg){
    mmStop();
	mmLoad(MOD_CRASH);
	mmStart(MOD_CRASH, MM_PLAY_ONCE);

	NF_LoadTiledBg("bg/pirate", "pirate", 256, 256);
    NF_CreateTiledBg(0, 2, "pirate");

	consoleDemoInit();
	consoleClear();
	setBrightness(3, 0);
	iprintf(msg);
	
	while(1){
		swiWaitForVBlank();
	}
}

//#include "teststruct.h"
#include "vars.h"
#include "functions.h"


int main(int argc, char **argv){

	NF_Set2D(0, 0);
	NF_Set2D(1, 0);
	NF_SetRootFolder("NITROFS");
	NF_InitSpriteBuffers();
	NF_InitSpriteSys(0);
	NF_InitSpriteSys(1);
	NF_InitTiledBgBuffers();
	NF_InitTiledBgSys(0);
	NF_InitTiledBgSys(1);
	mmInitDefault("nitro:/soundbank.bin");
	NF_InitCmapBuffers();

	/*NF_LoadTiledBg("bg/pli", "plui", 256, 256);
  	NF_CreateTiledBg(1, 1, "plui");*/

	loadmapfile("k2bj1/info.ddjim");

    load_map(&m_map);

    while(1){

        NF_SpriteOamSet(0);
		NF_SpriteOamSet(1);

		swiWaitForVBlank();

		oamUpdate(&oamMain);
		oamUpdate(&oamSub);

		scanKeys();
		u8_f point = updateobj();
		
        if(point != 0){
			str_link* link_map = curmap->map_link;
			str_link* link_cin = curmap->cin_link;
			for(int i = 2; i < point; i++){
				link_map = link_map->next;
				link_cin = link_cin->next;
			}
			if(strcmp(link_cin->str, "") != 0){
				start_cinematic(link_cin->str);
			}
			loadmapfile(link_map->str);
			load_map(&m_map);
		}

		if(curmap->song == 1){
			scol = scol+4;
			if(scol == 256) scol = 0;
			NF_ScrollBg(1, 3, scol, scol);
		}
		if(timer != 0) timer--;
    }
}