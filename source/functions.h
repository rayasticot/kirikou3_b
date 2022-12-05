#ifndef FUNCTIONS_H
#define FUNCTIONS_H
void kirikou_start(obj* kirikou);
void kirikou_update(obj* kirikou);
void load_map(map* mape);
void loadmapfile(char* filename);
void updateobj();
void npc_start(obj* objbuf);
void npc_update(obj* objbuf);
void tper_start(obj* objbuf);
void tper_update(obj* objbuf);
void dialog(obj* objbuf);
void kirikou_end(obj* kirikou);
void npc_end(obj* objbuf);
void tper_end(obj* objbuf);
bool checkCollision(int x1, int y1, int sx1, int sy1, int x2, int y2, int sx2, int sy2);
#endif