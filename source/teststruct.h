obj player ={
    .x = 384,
    .y = 478,
    .id = 0,
    .sprid = 0,
    .palid = 0,
    .type = 0
};

sprite sprtest ={
    .name = "spr/nada",
    .size_x = 16,
    .size_y = 32
};

str_link pal_l ={
    .str = "spr/nada"
};

map benin ={
    .pal_link = &pal_l,

    .bg_map = "bg/benin_map",
    .bg_obj = "bg/benin_obj",

    .firstspr = &sprtest,

    .bgsize_x = 768,
    .bgsize_y = 768,

    .firstobj = &player
};