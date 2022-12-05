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
        updateobj();
		/*scol = scol-1;
		if(scol == -256) scol = 0;
		NF_ScrollBg(1, 1, 0, scol);*/
		if(timer != 0) timer--;
    }
}