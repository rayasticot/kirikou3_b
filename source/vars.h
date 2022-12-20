#ifndef VARS_H
#define VARS_H
extern int cam_x;
extern int cam_y;
extern int new_x;
extern int new_y;
extern map* curmap;
extern obj* player;
extern map m_map;
extern u16_f timer;
extern sprite m_spr[16];
extern str_link m_pal[16];
extern map_lnk m_mlk[10];
extern str_link m_scn[10];
extern obj m_obj[48];
extern scene m_cin[16];

extern u8_f sdir;
extern int swordtimer;

extern const u16_f SOUNDFILE[SOUNDFILESIZE];
extern const u16_f MUSICFILE[MUSICFILESIZE];
#endif