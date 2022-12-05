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

void tper_start(obj* objbuf){
    NF_CreateSprite(1, objbuf->id, objbuf->sprid, objbuf->palid, objbuf->x, objbuf->y);
}

void tper_end(obj* objbuf){
    NF_DeleteSprite(1, objbuf->id);
}

void tper_update(obj* objbuf){
    if(checkCollision(objbuf->x, objbuf->y, objbuf->defx, objbuf->defy, player->x, player->y, 16, 32) == true){
        loadmapfile(objbuf->valc1);
        load_map(&m_map);
    }
}