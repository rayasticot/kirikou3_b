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

void kirikou_start(obj* kirikou){
    NF_CreateSprite(1, kirikou->id, kirikou->sprid, kirikou->palid, kirikou->x, kirikou->y);
    player = kirikou;
}

void kirikou_update(obj* kirikou){
    bool x_flag = false;
    bool y_flag = false;

    if(KEY_RIGHT & keysHeld()){
        NF_HflipSprite(1, kirikou->id, false);
        if(NF_GetTile(0, kirikou->x+17, kirikou->y) == 0 && NF_GetTile(0, kirikou->x+17, kirikou->y+30) == 0){
            kirikou->x += 1;
        }
    }
    if(KEY_LEFT & keysHeld()){
        NF_HflipSprite(1, kirikou->id, true);
        if(NF_GetTile(0, kirikou->x-1, kirikou->y) == 0 && NF_GetTile(0, kirikou->x-1, kirikou->y+30) == 0){
            kirikou->x -= 1;
        }
    }
    if(KEY_DOWN & keysHeld()){
        if(NF_GetTile(0, kirikou->x, kirikou->y+31) == 0 && NF_GetTile(0, kirikou->x+14, kirikou->y+31) == 0){
            kirikou->y += 1;
        }
    }
    if(KEY_UP & keysHeld()){
        if(NF_GetTile(0, kirikou->x, kirikou->y-1) == 0 && NF_GetTile(0, kirikou->x+14, kirikou->y-1) == 0){
            kirikou->y -= 1;
        }
    }

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

    NF_MoveSprite(1, kirikou->id, kirikou->sprx, kirikou->spry);

    NF_ScrollBg(1, 3, cam_x, cam_y);
    NF_ScrollBg(1, 2, cam_x, cam_y);
}