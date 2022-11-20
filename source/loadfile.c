#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <nds.h>
#include <nf_lib.h>
#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"

#include "define.h"
#include "structs.h"
#include "vars.h"
#include "functions.h"

FILE* mpfile;

char buf[24];

int num = 0;

map m_map;
sprite m_spr[16];
str_link m_pal[16];
str_link m_mlk[10];
obj m_obj[16];

static void readnextline(){
    fgets(buf, 24, mpfile);
    buf[strcspn(buf, "\n")] = 0;
}

static void charsetvalue(char (*dest)[24]){
    if(strcmp(buf, ".NOA") != 0){
        //*dest = buf;
        strcpy(*dest, buf);
    }
}

static void intsetvalue(int* dest){
    if(strcmp(buf, ".NOA") != 0){
        *dest = atoi(buf);
    }
}

static void u8setvalue(u8_f* dest){
    if(strcmp(buf, ".NOA") != 0){
        *dest = atoi(buf);
    }
}

static void sprload(){
    readnextline();
    charsetvalue(&m_spr[num].name);
    readnextline();
    intsetvalue(&m_spr[num].size_x);
    readnextline();
    intsetvalue(&m_spr[num].size_y);
    readnextline();
    if(strcmp(buf, ":END") != 0){
        m_spr[num].next = &m_spr[num+1];
        num++;
        sprload();
    }
}

static void palload(){
    readnextline();
    charsetvalue(&m_pal[num].str);
    readnextline();
    if(strcmp(buf, ":END") != 0){
        m_pal[num].next = &m_pal[num+1];
        num++;
        palload();
    }
}

static void mlkload(){
    readnextline();
    charsetvalue(&m_mlk[num].str);
    readnextline();
    if(strcmp(buf, ":END") != 0){
        m_mlk[num].next = &m_mlk[num+1];
        num++;
        mlkload();
    }
}

static void objload(){
    readnextline();
    intsetvalue(&m_obj[num].x);
    readnextline();
    intsetvalue(&m_obj[num].y);
    /*readnextline();
    intsetvalue(&m_obj[num].sprx);
    readnextline();
    intsetvalue(&m_obj[num].spry);*/
    readnextline();
    u8setvalue(&m_obj[num].id);
    readnextline();
    u8setvalue(&m_obj[num].sprid);
    readnextline();
    u8setvalue(&m_obj[num].palid);
    readnextline();
    u8setvalue(&m_obj[num].type);
    readnextline();
    charsetvalue(&m_obj[num].valc1);
    readnextline();
    intsetvalue(&m_obj[num].defx);
    readnextline();
    intsetvalue(&m_obj[num].defy);
    readnextline();
    intsetvalue(&m_obj[num].radius);
    readnextline();
    u8setvalue(&m_obj[num].sound[0]);
    readnextline();
    u8setvalue(&m_obj[num].sound[1]);
    readnextline();
    u8setvalue(&m_obj[num].sound[2]);
    readnextline();
    u8setvalue(&m_obj[num].sound[3]);
    readnextline();
    u8setvalue(&m_obj[num].sound[4]);
    readnextline();
    u8setvalue(&m_obj[num].state);
    readnextline();
    u8setvalue(&m_obj[num].life);
    readnextline();
    if(strcmp(buf, ":END") != 0){
        m_obj[num].next = &m_obj[num+1];
        num++;
        objload();
    }
}

static void mapload(){
    readnextline();
    charsetvalue(&m_map.bg_map);
    readnextline();
    charsetvalue(&m_map.bg_obj);
    readnextline();
    charsetvalue(&m_map.cmap);
    readnextline();
    intsetvalue(&m_map.song);
    readnextline();
    intsetvalue(&m_map.bgsize_x);
    readnextline();
    intsetvalue(&m_map.bgsize_y);

    readnextline();
    m_map.firstspr = &m_spr[0];
    if(strcmp(buf, "_SPR") != 0) NF_Error(229, "caca", 2);
    else sprload();
    num = 0;
    readnextline();
    m_map.pal_link = &m_pal[0];
    if(strcmp(buf, "_PAL") != 0) NF_Error(230, "caca", 2);
    else palload();
    num = 0;
    readnextline();
    m_map.map_link = &m_mlk[0];
    if(strcmp(buf, "_MLK") != 0) NF_Error(231, "caca", 2);
    else mlkload();
    num = 0;
    readnextline();
    m_map.firstobj = &m_obj[0];
    if(strcmp(buf, "_OBJ") != 0) NF_Error(232, "caca", 2);
    else objload();
}

void loadmapfile(char* filename){

    mpfile = fopen(filename, "r");

    fgets(buf, 24, mpfile);

    if(strcmp(buf, "_MAP\n") == 0) mapload();
    else NF_Error(228, "caca", 2);

    fclose(mpfile);
}