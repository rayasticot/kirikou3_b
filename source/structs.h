#ifndef STRUCTS_H
#define STRUCTS_H
typedef struct str_link{
	char str[24];
	struct str_link* next;
} str_link;
typedef struct sprite{
	char name[24];
	int size_x;
	int size_y;
	struct sprite* next;
} sprite;
typedef struct scene{
	char bg[24];
	int sound;
	struct scene* next;
} scene;
typedef struct obj{
	float acc_x;
	float acc_y;
	float spe_x;
	float spe_y;
	float tru_x;
	float tru_y;
	
	int x;
	int y;
	int sprx;
	int spry;
	u8_f id;
    u8_f sprid;
    u8_f palid;
	u8_f type;

	char valc1[24];
	int defx;
	int defy;
	int radius;
	u8_f sound[5];
	u8_f state;
	u8_f life;

	struct obj* next;
} obj;
typedef struct map{
	char bg_map[24];
	char bg_obj[24];
	//char* bg_mini;
	char cmap[24];
	int song;
	int bgsize_x;
	int bgsize_y;
	sprite* firstspr;
	str_link* map_link;
	str_link* cin_link;
    str_link* pal_link;
	obj* firstobj;
	//u8_f spritenum;
} map;
#endif