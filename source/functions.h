#ifndef FUNCTIONS_H
#define FUNCTIONS_H
void kirikou_start(obj* kirikou);
u8_f kirikou_update(obj* kirikou);
void load_map(map* mape);
void loadmapfile(char* filename);
void loadcinfile(char* filename);
u8_f updateobj();
void npc_start(obj* objbuf);
void npc_update(obj* objbuf);
void dialog(obj* objbuf);
void kirikou_end(obj* kirikou);
void npc_end(obj* objbuf);
bool checkCollision(int x1, int y1, int sx1, int sy1, int x2, int y2, int sx2, int sy2);
void crashgame(char* msg);
void start_cinematic(char* name);
#endif