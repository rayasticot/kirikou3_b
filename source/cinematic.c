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
#include "vars.h"
#include "functions.h"

void start_cinematic(char* name){
    loadcinfile(name);
    scene* cine = &m_cin[0];
    mmSetModuleVolume(128);
    while(1){
        NF_LoadTiledBg(cine->bg, "back", 256, 256);
        NF_CreateTiledBg(0, 2, "back");
        mmLoadEffect(SOUNDFILE[cine->sound]);
        mm_sfxhand snd = mmEffect(SOUNDFILE[cine->sound]);
        mmEffectVolume(snd, 255);

        while(!(KEY_A & keysDown())){
            NF_SpriteOamSet(0);
	        NF_SpriteOamSet(1);

		    swiWaitForVBlank();

		    oamUpdate(&oamMain);
		    oamUpdate(&oamSub);

		    scanKeys();
        }

        mmEffectCancel(snd);
        mmUnloadEffect(SOUNDFILE[cine->sound]);
        NF_DeleteTiledBg(0, 2);
        NF_UnloadTiledBg("back");
        mmSetModuleVolume(1024);

        cine = cine->next;
        if(cine->next == NULL) break;
    }
}