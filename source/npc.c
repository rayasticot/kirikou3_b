#include <stdio.h>
#include <stdlib.h>
#include <nds.h>
#include <nf_lib.h>
#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"

#include "define.h"
#include "structs.h"
#include "vars.h"
#include "functions.h"

#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4


static void dialog(obj* objbuf){
    NF_LoadTiledBg(objbuf->valc1, objbuf->valc1, 256, 256);
    NF_CreateTiledBg(0, 2, objbuf->valc1);
    mmSetModuleVolume(128);
    mmLoadEffect(objbuf->sound[objbuf->life]);
    mm_sfxhand snd = mmEffect(objbuf->sound[objbuf->life]);
    mmEffectVolume(snd, 255);
    while(KEY_A ^ keysDown()){
        NF_SpriteOamSet(0);
	    NF_SpriteOamSet(1);

		swiWaitForVBlank();

		oamUpdate(&oamMain);
		oamUpdate(&oamSub);

		scanKeys();
    }
    mmEffectCancel(snd);
    mmUnloadEffect(objbuf->sound[objbuf->life]);
    NF_DeleteTiledBg(0, 2);
    NF_UnloadTiledBg(objbuf->valc1);
    mmSetModuleVolume(1024);
    if(objbuf->life++ == 4) objbuf->life = 0;
}

static void move_npc(obj* objbuf, int* check, int* def, bool aug){
  if(*check > *def - objbuf->radius && *check < *def + objbuf->radius){
    /*if(rand() % 40 + 1 == 1){
      objbuf->state = 0;
      break;
    }*/
    if(aug == true){
      (*check)++;
    }
    else{
      (*check)--;
    }
  }
  else{
    if(aug == true){
      (*check)--;
    }
    else{
      (*check)++;
    }
    objbuf->state = 0;
  }
}

void npc_start(obj* objbuf){
  NF_CreateSprite(1, objbuf->id, objbuf->id, 1, objbuf->x, objbuf->y);
}

void npc_update(obj* objbuf){
    int randnum;
    switch(objbuf->state){
      case 0:
        randnum = rand() % 200 + 1;
        if(randnum < 4){
          objbuf->state = randnum;
        }
        break;
      case UP:
        move_npc(objbuf, &objbuf->y, &objbuf->defy, true);
        break;
      case DOWN:
        move_npc(objbuf, &objbuf->y, &objbuf->defy, false);
        break;
      case LEFT:
        move_npc(objbuf, &objbuf->x, &objbuf->defx, true);
        break;
      case RIGHT:
        move_npc(objbuf, &objbuf->x, &objbuf->defx, false);
        break;
    }
  if(checkCollision(objbuf->x, objbuf->y, 16, 32, player->x, player->y, 16, 32) == true && timer == 0){
    dialog(objbuf);
    timer = 180;
  }
}