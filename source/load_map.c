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


static void load_sprites(map* mape){
    int index = 0;
    sprite* spr = mape->firstspr;
    while(1){
        NF_LoadSpriteGfx(spr->name, index, spr->size_x, spr->size_y);
        NF_VramSpriteGfx(1, index, index, false);
        if(spr->next != NULL){
            spr = spr->next;
        }
        else break;
        index++;
    }
    str_link* pal = mape->pal_link;
    index = 0;
    while(1){
        NF_LoadSpritePal(pal->str, index);
        NF_VramSpritePal(1, index, index);
        if(pal->next != NULL){
            pal = pal->next;
        }
        else break;
        index++;
    }
}

void load_map(map* mape){
    NF_LoadTiledBg("bg/loading", "load", 256, 256);
  	NF_CreateTiledBg(0, 3, "load");

    curmap = mape;
    obj* objbuf;
    NF_ResetCmapBuffers();
    NF_ResetTiledBgBuffers();
    NF_LoadTiledBg(mape->bg_map, "bgmap", mape->bgsize_x, mape->bgsize_y);
    /*if(mape->bg_obj != NULL)*/ NF_LoadTiledBg(mape->bg_obj, "bgobj", mape->bgsize_x, mape->bgsize_y);
    NF_CreateTiledBg(1, 3, "bgmap");
    /*if(mape->bg_obj != NULL)*/ NF_CreateTiledBg(1, 2, "bgobj");
    //else NF_DeleteTiledBg(1, 2);
    NF_LoadColisionBg(mape->cmap, 0, 768, 768);

    load_sprites(mape);

    objbuf = mape->firstobj;
	mmLoad(1);
    while(1){
        switch(objbuf->type){
            case 0:
                kirikou_start(objbuf);
                break;
            case 1:
                npc_start(objbuf);
                break;
            case 3:
            case 4:
                NF_CreateSprite(1, 2, 2, 1, objbuf->x, objbuf->y);
                break;
        }
        if(objbuf->next == NULL) break;
        objbuf = objbuf->next;
    }
    mmStart(mape->song, MM_PLAY_LOOP);
    NF_DeleteTiledBg(0, 3);
}