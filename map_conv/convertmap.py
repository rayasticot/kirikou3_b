import yaml

map_infor = ("bg_map", "bg_obj", "cmap", "song", "bgsize_x", "bgsize_y")
spr_infor = ("name", "size_x", "size_y")
obj_infor = ("x", "y", "id", "sprid", "palid", "type", "valc1", "defx", "defy", "radius", "sound0", "sound1", "sound2", "sound3", "sound4", "state", "life")

with open("info.yaml", "r") as info:
    nig = yaml.safe_load(info)

with open("output.ddjim", "w") as final:
    final.write("_MAP\n")
    
    for i in range(6):
        final.write(nig["map"][map_infor[i]]+"\n")
    
    final.write("_SPR\n")
    
    a = False
    
    for i in range(16): #a agrandir
        try:
            nig["map"]["spr"][i][spr_infor[0]]
        except IndexError:
            final.write(":END\n")
            break
        if a == True:
            final.write(":NXT\n")
        for ib in range(3):
            a = True
            final.write(nig["map"]["spr"][i][spr_infor[ib]]+"\n")
        
    final.write("_PAL\n")
    a = False
    
    for i in range(16): #a agrandir
        try:
            nig["map"]["pal"][i]["str"]
        except IndexError:
            final.write(":END\n")
            break
        if a == True:
            final.write(":NXT\n")
        final.write(nig["map"]["pal"][i]["str"]+"\n")
        a = True
        
    final.write("_MLK\n")
    a = False
        
    for i in range(10): #a agrandir
        try:
            nig["map"]["mlk"][i]["str"]
        except IndexError:
            final.write(":END\n")
            break
        if a == True:
            final.write(":NXT\n")
        final.write(nig["map"]["mlk"][i]["str"]+"\n")

    final.write("_SCN\n")
    a = False

    for i in range(10): #a agrandir
        try:
            nig["map"]["scn"][i]["str"]
        except IndexError:
            final.write(":END\n")
            break
        if a == True:
            final.write(":NXT\n")
        final.write(nig["map"]["scn"][i]["str"]+"\n")
        
    final.write("_OBJ\n")
    a = False
    
    for i in range(48): #a agrandir
        try:
            nig["map"]["obj"][i][obj_infor[0]]
        except IndexError:
            final.write(":END\n")
            break
        if a == True:
            final.write(":NXT\n")
        for ib in range(17):
            a = True
            final.write(nig["map"]["obj"][i][obj_infor[ib]]+"\n")
        
