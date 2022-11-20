#include <stdio.h>
#include <stdlib.h>
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

#include "teststruct.h"
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

	loadmapfile("bhcon/info.ddjim");

    load_map(&m_map);

    while(1){

        NF_SpriteOamSet(0);
		NF_SpriteOamSet(1);

		swiWaitForVBlank();

		oamUpdate(&oamMain);
		oamUpdate(&oamSub);

		scanKeys();
        kirikou_update(&player);
        
    }
}