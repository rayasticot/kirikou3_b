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

int sw_x = 0;
int sw_y = 0;
bool sw_touch = false;

void ennemy_start(obj* objbuf){
    NF_CreateSprite(1, objbuf->id, objbuf->sprid, objbuf->palid, objbuf->x, objbuf->y);
    NF_ShowSprite(1, objbuf->id, true);
    NF_HflipSprite(1, objbuf->id, false);

    objbuf->acc_x = 0;
    objbuf->acc_y = 0;
    objbuf->spe_x = 0;
    objbuf->spe_y = 0;
    objbuf->tru_x = objbuf->x;
    objbuf->tru_y = objbuf->y;
}

static bool swordcollision(obj* objbuf){
    if(sdir <= 1){
        if(checkCollision(objbuf->x, objbuf->y, 16, 8, player->x+sw_x, player->y+sw_y, 16, 4) == true){
            if(sdir == 0) objbuf->spe_x = 6;
            else objbuf->spe_x = -6;
            objbuf->life--;
            return true;
        }
    }
    else{
        if(checkCollision(objbuf->x, objbuf->y, 16, 8, player->x+sw_x, player->y+sw_y, 4, 16) == true){
            if(sdir == 2) objbuf->spe_y = 6;
            else objbuf->spe_y = -6;
            objbuf->life--;
            return true;
        }
    }
    return false;
}

static void enemy_update_action(obj* objbuf){
    if(objbuf->spe_x < 0) objbuf->spe_x += 0.1;
    if(objbuf->spe_x > 0) objbuf->spe_x -= 0.1;
    if(objbuf->spe_y < 0) objbuf->spe_y += 0.1;
    if(objbuf->spe_y > 0) objbuf->spe_y -= 0.1;

    if(objbuf->spe_x <= 0.1 && objbuf->spe_x >= -0.1) objbuf->spe_x = 0;
    if(objbuf->spe_y <= 0.1 && objbuf->spe_y >= -0.1) objbuf->spe_y = 0;

    objbuf->acc_x = 0;
    objbuf->acc_y = 0;
    
    if(checkCollision(objbuf->x, objbuf->y, 16, 8, player->x, player->y, 16, 32) == true){
        gameover();
    }

    sw_x = 0;
    sw_y = 0;
    switch(sdir){
        case 0:
            sw_x = 8;
            sw_y = 14;
            break;
        case 1:
            sw_x = -8;
            sw_y = 14;
            break;
        case 2:
            sw_x = 6;
            sw_y = 32;
            break;
        case 3:
            sw_x = 6;
            sw_y = -16;
            break;
    }
    
    if(swordtimer == -1){
        sw_touch = false;
    }

    if(swordtimer != -1){
        sw_touch = swordcollision(objbuf);
    }

    switch(objbuf->state){
        case 0:
            if(NF_GetTile(0, objbuf->x+17, objbuf->y) != 1 && NF_GetTile(0, objbuf->x+17, objbuf->y+8) != 1){
                objbuf->acc_x = 1;
            }
            else{
                objbuf->state = 1;
                objbuf->spe_x = -objbuf->spe_x;
                NF_HflipSprite(1, objbuf->id, true);
            }
            break;
        case 1:
            if(NF_GetTile(0, objbuf->x-1, objbuf->y) != 1 && NF_GetTile(0, objbuf->x-1, objbuf->y+8) != 1){
                objbuf->acc_x = -1;
            }
            else{
                objbuf->state = 0;
                objbuf->spe_x = -objbuf->spe_x;
                NF_HflipSprite(1, objbuf->id, false);
            }
            break;
        case 2:
            if(NF_GetTile(0, objbuf->x, objbuf->y+7) != 1 && NF_GetTile(0, objbuf->x+14, objbuf->y+7) != 1){
                objbuf->acc_y = 1;
            }
            else{
                objbuf->state = 3;
                objbuf->spe_y = -objbuf->spe_y;
            }
            break;
        case 3:
            if(NF_GetTile(0, objbuf->x, objbuf->y-1) != 1 && NF_GetTile(0, objbuf->x+14, objbuf->y-1) != 1){
                objbuf->acc_y = -1;
            }
            else{
                objbuf->state = 2;
                objbuf->spe_y = -objbuf->spe_y;
            }
            break;
    }

    if(sw_touch == false){
        objbuf->spe_x += objbuf->acc_x;
        objbuf->spe_y += objbuf->acc_y;
    }

    if(sw_touch == false){
        if(objbuf->spe_x > 1) objbuf->spe_x = 1;
        if(objbuf->spe_x < -1) objbuf->spe_x = -1;
        if(objbuf->spe_y > 1) objbuf->spe_y = 1;
        if(objbuf->spe_y < -1) objbuf->spe_y = -1;
    }

    objbuf->tru_x += objbuf->spe_x;
    objbuf->tru_y += objbuf->spe_y;

    objbuf->x = objbuf->tru_x;
    objbuf->y = objbuf->tru_y;

    if(objbuf->life == 0) NF_ShowSprite(1, objbuf->id, false);

    //NF_MoveSprite(1, objbuf->id, objbuf->sprx, objbuf->spry);
}

void enemy_update(obj* objbuf){
    if(objbuf->life > 0) enemy_update_action(objbuf);
}