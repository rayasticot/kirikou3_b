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


void updateobj(){
  obj* objbuf = curmap->firstobj;
  while(1){
    if(objbuf->type != 0){
        if(objbuf->x > cam_x-16 && objbuf->x - cam_x < 256){
            objbuf->sprx = objbuf->x - cam_x;
        }
        else{
            objbuf->sprx = 256;
        }
        if(objbuf->y > cam_y-32 && objbuf->y - cam_y < 192){
            objbuf->spry = objbuf->y - cam_y;
        }
        else{
            objbuf->spry = 192;
        }
        NF_MoveSprite(1, objbuf->id, objbuf->sprx, objbuf->spry);
    }
    switch(objbuf->type){
        case 0:
            kirikou_update(objbuf);
            break;
        case 1:
            npc_update(objbuf);
            break;
        /*case 3:
            EvilUpdate(objbuf);
            break;
        case 4:
            EvilUpdate(objbuf);
            break;*/
    }
    if(objbuf->next == NULL) break;
    objbuf = objbuf->next;
  }
}