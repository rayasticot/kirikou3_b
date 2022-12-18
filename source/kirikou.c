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

bool attacking = false;
int swordtimer = 0;
u8_f sdir = 0;
u16_f angle[4] = {0, 256, 128, 384};
int swbuf = 0;

void kirikou_start(obj* kirikou){
    NF_CreateSprite(1, kirikou->id, kirikou->sprid, kirikou->palid, kirikou->x, kirikou->y);
    NF_CreateSprite(1, 50, kirikou->sprid+1, kirikou->palid, kirikou->x, kirikou->y);
    NF_EnableSpriteRotScale(1, 50, 0, false);
    NF_ShowSprite(1, 50, false);
    player = kirikou;

    kirikou->acc_x = 0;
    kirikou->acc_y = 0;
    kirikou->spe_x = 0;
    kirikou->spe_y = 0;
    kirikou->tru_x = kirikou->x;
    kirikou->tru_y = kirikou->y;
}

void kirikou_end(obj* kirikou){
    NF_DeleteSprite(1, kirikou->id);
}

static int get_both_side(int x, int y){
    u8_f point_a = NF_GetTile(0, x, y);
    u8_f point_b = NF_GetTile(0, x+16, y+32);
    if(point_a > 1 || point_b > 1){
        if(point_a > point_b) return point_a;
        else return point_b;
    }
    else return 0;
}

void gameover(){
    mmStop();
    NF_LoadTiledBg("bg/gameover", "gameover", 256, 256);
    NF_CreateTiledBg(0, 2, "gameover");
    while(!(KEY_A & keysDown())){
        NF_SpriteOamSet(0);
		NF_SpriteOamSet(1);

		swiWaitForVBlank();

		oamUpdate(&oamMain);
		oamUpdate(&oamSub);

		scanKeys();
    }
    NF_DeleteTiledBg(0, 2);
    NF_UnloadTiledBg("gameover");
    full_load_map(curmap->name);
}

u8_f kirikou_update(obj* kirikou){
    bool x_flag = false;
    bool y_flag = false;

    if(kirikou->spe_x < 0) kirikou->spe_x += 0.1;
    if(kirikou->spe_x > 0) kirikou->spe_x -= 0.1;
    if(kirikou->spe_y < 0) kirikou->spe_y += 0.1;
    if(kirikou->spe_y > 0) kirikou->spe_y -= 0.1;

    if(kirikou->spe_x <= 0.1 && kirikou->spe_x >= -0.1) kirikou->spe_x = 0;
    if(kirikou->spe_y <= 0.1 && kirikou->spe_y >= -0.1) kirikou->spe_y = 0;

    kirikou->acc_x = 0;
    kirikou->acc_y = 0;

    if(swordtimer == -1){
        if(KEY_RIGHT & keysHeld()){
            //sdir = 0;
            NF_HflipSprite(1, kirikou->id, false);
            if(NF_GetTile(0, kirikou->x+17, kirikou->y) != 1 && NF_GetTile(0, kirikou->x+17, kirikou->y+30) != 1){
                kirikou->acc_x = 0.2;
            }
            else kirikou->spe_x = -kirikou->spe_x;
        }
        if(KEY_LEFT & keysHeld()){
            //sdir = 1;
            NF_HflipSprite(1, kirikou->id, true);
            if(NF_GetTile(0, kirikou->x-1, kirikou->y) != 1 && NF_GetTile(0, kirikou->x-1, kirikou->y+30) != 1){
                kirikou->acc_x = -0.2;
            }
            else kirikou->spe_x = -kirikou->spe_x;
        }
        if(KEY_DOWN & keysHeld()){
            //sdir = 2;
            if(NF_GetTile(0, kirikou->x, kirikou->y+31) != 1 && NF_GetTile(0, kirikou->x+14, kirikou->y+31) != 1){
                kirikou->acc_y = 0.2;
            }
            else kirikou->spe_y = -kirikou->spe_y;
        }
        if(KEY_UP & keysHeld()){
            //sdir = 3;
            if(NF_GetTile(0, kirikou->x, kirikou->y-1) != 1 && NF_GetTile(0, kirikou->x+14, kirikou->y-1) != 1){
                kirikou->acc_y = -0.2;
            }
            else kirikou->spe_y = -kirikou->spe_y;
        }
    }

    kirikou->spe_x += kirikou->acc_x;
    kirikou->spe_y += kirikou->acc_y;

    if(kirikou->spe_x > 1) kirikou->spe_x = 1;
    if(kirikou->spe_x < -1) kirikou->spe_x = -1;
    if(kirikou->spe_y > 1) kirikou->spe_y = 1;
    if(kirikou->spe_y < -1) kirikou->spe_y = -1;

    kirikou->tru_x += kirikou->spe_x;
    kirikou->tru_y += kirikou->spe_y;

    kirikou->x = kirikou->tru_x;
    kirikou->y = kirikou->tru_y;

    if(kirikou->x < 0){
        kirikou->x = 0;
    }
    if(kirikou->x > curmap->bgsize_x){
        kirikou->x = curmap->bgsize_x;
    }
    if(kirikou->y < 0){
        kirikou->y = 0;
    }
    if(kirikou->y > curmap->bgsize_y){
        kirikou->y = curmap->bgsize_y;
    }
    kirikou->sprx = 120;
    kirikou->spry = 80;
    if(kirikou->x < 120){
        kirikou->sprx = kirikou->x;
        x_flag = true;
    }
    if(kirikou->y < 80){
        kirikou->spry = kirikou->y;
        y_flag = true;
    }
    if(kirikou->x > curmap->bgsize_x-136){
        kirikou->sprx = kirikou->x-(curmap->bgsize_x-256);
        x_flag = true;
    }
    if(kirikou->y > curmap->bgsize_y-112){
        kirikou->spry = kirikou->y-(curmap->bgsize_x-192);
        y_flag = true;
    }

    if(x_flag == false){
        cam_x = kirikou->x-120;
    }
    else{
        if(kirikou->x < 120){
            cam_x = 0;
        }
        if(kirikou->x > curmap->bgsize_x-136){
            cam_x = curmap->bgsize_x-256;
        }
    }

    if(y_flag == false){
        cam_y = kirikou->y-80;
    }
    else{
        if(kirikou->y < 80){
            cam_y = 0;
        }
        if(kirikou->y > curmap->bgsize_y-80){
            cam_y = curmap->bgsize_y-192;
        }
    }

    attacking = false;

    if(swordtimer == -1){
        if(KEY_A & keysDown()){
            sdir = 0;
            attacking = true;
        }
        if(KEY_Y & keysDown()){
            sdir = 1;
            attacking = true;
        }
        if(KEY_B & keysDown()){
            sdir = 2;
            attacking = true;
        }
        if(KEY_X & keysDown()){
            sdir = 3;
            attacking = true;
        }
        if(attacking == true){
            swordtimer = 30;
            NF_ShowSprite(1, 50, true);
            NF_SpriteRotScale(1, 0, angle[sdir], 256, 256);
        }
    }

    switch(sdir){
        case 0:
        case 1:
            swbuf = 0;
            break;
        case 2:
            swbuf = 16;
            break;
        case 3:
            swbuf = -16;
            break;
    }

    if(swordtimer == 0){
        NF_ShowSprite(1, 50, false);
        swordtimer = -1;
    }

	if(swordtimer > 0) swordtimer--;

    NF_MoveSprite(1, kirikou->id, kirikou->sprx, kirikou->spry);
    NF_MoveSprite(1, 50, kirikou->sprx-8, kirikou->spry+swbuf);

    NF_ScrollBg(1, 3, cam_x, cam_y);
    NF_ScrollBg(1, 2, cam_x, cam_y);

    u8_f point = get_both_side(kirikou->x, kirikou->y);
    return point;
    /*if(point != 0){
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
    }*/
}