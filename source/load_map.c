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

int spr_index = 0;
int pal_index = 0;

int oldsong;

bool first = false;


static void load_sprites(map* mape){
    int index = 0;
    sprite* spr = mape->firstspr;
    for(int i = 0; i < spr_index; i++){
        NF_UnloadSpriteGfx(i);
        NF_FreeSpriteGfx(1, i);
    }
    for(int i = 0; i < pal_index; i++){
        NF_UnloadSpritePal(i);
    }
    while(1){
        NF_LoadSpriteGfx(spr->name, index, spr->size_x, spr->size_y);
        NF_VramSpriteGfx(1, index, index, false);
        if(spr->next != NULL){
            spr = spr->next;
        }
        else break;
        index++;
    }
    spr_index = index+1;
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
    pal_index = index+1;
}

/*static void setdark(u8_f sc){
    u8 red;
    u8 green;
    u8 blue;
    for(int i = 0; i <= 255; i++){
        NF_BgGetPalColor(1, sc, i, &red, &green, &blue);
        if(red-6 < 0) red = 0;
        else red = red-6;
        if(green-6 < 0) green = 0;
        else green = green-6;
        if(blue-6 < 0) blue = 0;
        else blue = blue-6;
        NF_BgEditPalColor(1, sc, i, red, green, blue);
    }
    NF_BgUpdatePalette(1, sc);
}*/

void load_map(map* mape){
    NF_LoadTiledBg("bg/loading", "load", 256, 256);
  	NF_CreateTiledBg(0, 3, "load");
    obj* objbuf;

    if(first == true){
        mmStop();
        mmUnload(MUSICFILE[oldsong]);
    }

    /*if(first == true){
        while(1){
            objbuf = curmap->firstobj;
            switch(objbuf->type){
                case 0:
                    kirikou_end(objbuf);
                    break;
                case 1:
                    npc_end(objbuf);
                    break;
                case 3:
                case 4:
                    NF_CreateSprite(1, 2, 2, 1, objbuf->x, objbuf->y);
                    break;
                
            }
            if(objbuf->next == NULL) break;
            objbuf = objbuf->next;
        }
    }*/

    curmap = mape;
    NF_ResetCmapBuffers();
    NF_ResetTiledBgBuffers();
    if(first == true){
        NF_DeleteTiledBg(1, 3);
        NF_DeleteTiledBg(1, 2);
        /*NF_UnloadTiledBg("bgmap");
        NF_UnloadTiledBg("bgobj");*/
    }
    first = true;
    NF_LoadTiledBg(mape->bg_map, "bgmap", mape->bgsize_x, mape->bgsize_y);
    /*if(mape->bg_obj != NULL)*/ NF_LoadTiledBg(mape->bg_obj, "bgobj", mape->bgsize_x, mape->bgsize_y);
    NF_CreateTiledBg(1, 3, "bgmap");
    /*if(mape->bg_obj != NULL)*/ NF_CreateTiledBg(1, 2, "bgobj");
    //else NF_DeleteTiledBg(1, 2);
    NF_LoadColisionBg(mape->cmap, 0, 768, 768);

    load_sprites(mape);

    objbuf = mape->firstobj;
	mmLoad(MUSICFILE[mape->song]);
    oldsong = mape->song;
    while(1){
        switch(objbuf->type){
            case 0:
                kirikou_start(objbuf);
                break;
            case 1:
                npc_start(objbuf);
                break;
            case 2:
                ennemy_start(objbuf);
                break;
            /*case 3:
            case 4:
                NF_CreateSprite(1, 2, 2, 1, objbuf->x, objbuf->y);
                break;*/
        }
        if(objbuf->next == NULL) break;
        objbuf = objbuf->next;
    }
    mmStart(MUSICFILE[mape->song], MM_PLAY_LOOP);
    NF_DeleteTiledBg(0, 3);
    /*setdark(3);
    setdark(2);*/
}

void full_load_map(char* link){
    loadmapfile(link);
    load_map(&m_map);
}