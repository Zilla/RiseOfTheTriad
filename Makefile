CC=gcc
CFLAGS=-c -g $(INCDIRS)
INCDIRS=-Irott/

ROTTOBJ=isr.o z_zone.o w_wad.o rt_scale.o rt_draw.o engine.o \
        rt_dr_a.o rt_fc_a.o rt_floor.o rt_main.o rt_util.o \
        rt_stat.o rt_actor.o rt_state.o rt_ted.o rt_playr.o \
        rt_rand.o rt_door.o rt_menu.o rt_vid.o rt_vh_a.o \
        rt_str.o rt_in.o rt_sc_a.o rt_game.o rt_map.o \
        rt_debug.o rt_sound.o scriplib.o f_scale.o \
        rt_swift.o rt_build.o rt_com.o \
        rt_view.o rt_cfg.o rt_spbal.o sbconfig.o rt_err.o \
        rt_crc.o rt_msg.o modexlib.o rt_battl.o \
        usrhooks.o rt_error.o rt_net.o cin_util.o \
        cin_main.o cin_actr.o cin_evnt.o cin_efct.o cin_glob.o \
        fli_util.o fli_main.o rt_dmand.o \

out/isr.o: rott/isr.c
        @$(CC) $(CFLAGS) -o $@ $<

z_zone.o:     z_zone.c rt_def.h _z_zone.h z_zone.h rt_util.h develop.h rt_net.h

w_wad.o:      w_wad.c rt_def.h rt_util.h _w_wad.h w_wad.h z_zone.h isr.h &
                develop.h

rt_scale.o:   rt_scale.c rt_def.h watcom.h rt_util.h rt_draw.h rt_scale.h &
                _rt_scal.h rt_sc_a.h engine.h w_wad.h z_zone.h lumpy.h &
                rt_main.h rt_playr.h rt_ted.h rt_vid.h rt_view.h rt_cfg.h &
                modexlib.h

rt_view.o:    rt_view.c rt_def.h rt_view.h z_zone.h w_wad.h lumpy.h &
                rt_util.h rt_vid.h rt_game.h rt_draw.h rt_ted.h isr.h &
                modexlib.h rt_rand.h rt_sound.h rt_battl.h rt_floor.h &
                rt_str.h develop.h

rt_draw.o:    rt_draw.c profile.h rt_def.h watcom.h sprites.h rt_actor.h &
                rt_stat.h rt_draw.h _rt_draw.h rt_dr_a.h rt_fc_a.h rt_scale.h &
                rt_floor.h rt_playr.h rt_door.h rt_ted.h rt_main.h isr.h &
                rt_util.h engine.h z_zone.h w_wad.h lumpy.h rt_menu.h rt_game.h &
                rt_vid.h rt_view.h rt_cfg.h rt_str.h develop.h rt_sound.h &
                rt_msg.h modexlib.h rt_rand.h rt_net.h

engine.o:     engine.c rt_def.h engine.h _engine.h rt_eng.h rt_draw.h &
                rt_door.h rt_stat.h rt_ted.h rt_view.h
#
#rt_eng.obj:     rt_eng.asm rt_eng.h
#
rt_fc_a.o:    rt_fc_a.asm rt_fc_a.h

rt_floor.o:   rt_floor.c rt_def.h watcom.h rt_floor.h rt_fc_a.h _rt_floo.h &
                rt_draw.h rt_util.h engine.h rt_main.h w_wad.h z_zone.h &
                rt_view.h rt_ted.h rt_cfg.h rt_actor.h modexlib.h rt_playr.h &
                rt_sound.h rt_rand.h

rt_dr_a.o:    rt_dr_a.asm rt_dr_a.h

rt_main.o:    rt_main.c rt_def.h lumpy.h rt_actor.h rt_stat.h rt_vid.h &
                rt_menu.h rt_sound.h watcom.h scriplib.h rt_main.h &
                _rt_main.h rt_com.h rt_util.h z_zone.h w_wad.h rt_game.h &
                rt_floor.h rt_playr.h rt_draw.h rt_str.h rt_view.h &
                rt_door.h rt_ted.h rt_in.h rt_map.h rt_rand.h rt_debug.h &
                isr.h fx_man.h rt_cfg.h develop.h version.h rt_menu.h &
                rt_msg.h rt_dr_a.h rt_build.h rt_error.h modexlib.h &
                rt_net.h cin_main.h music.h fx_man.h rottnet.h
#\\JIM

rt_util.o:    rt_util.c rt_def.h watcom.h _rt_util.h rt_util.h isr.h &
                z_zone.h rt_dr_a.h rt_in.h rt_main.h scriplib.h rt_menu.h &
                rt_playr.h version.h develop.h rt_vid.h rt_view.h modexlib.h &
                rt_cfg.h

rt_stat.o:    rt_stat.c rt_def.h sprites.h rt_stat.h z_zone.h lumpy.h &
                rt_util.h rt_draw.h rt_ted.h rt_door.h w_wad.h &
                rt_main.h rt_rand.h _rt_stat.h rt_menu.h rt_net.h &
                isr.h develop.h

rt_actor.o:   rt_actor.c rt_def.h rt_sound.h states.h gmove.h rt_door.h &
                rt_ted.h rt_draw.h watcom.h z_zone.h lumpy.h rt_sqrt.h &
                rt_stat.h sprites.h rt_actor.h rt_game.h rt_playr.h rt_main.h &
                rt_util.h rt_rand.h rt_menu.h rt_swift.h _rt_acto.h rt_cfg.h &
                rt_floor.h develop.h rt_view.h isr.h rt_com.h rt_net.h

rt_state.o:   rt_state.c rt_def.h sprites.h states.h rt_actor.h develop.h

rt_ted.o:     rt_ted.c rt_def.h rt_sound.h states.h watcom.h rt_ted.h &
                _rt_ted.h w_wad.h z_zone.h rt_util.h lumpy.h rt_vid.h &
                rt_actor.h rt_stat.h rt_menu.h rt_draw.h rt_com.h &
                rt_main.h rt_door.h rt_playr.h rt_view.h rt_str.h isr.h &
                rt_floor.h rt_game.h rt_rand.h rt_cfg.h develop.h &
                modexlib.h engine.h rt_debug.h rt_scale.h rt_net.h

rt_playr.o:   rt_playr.c rt_def.h watcom.h rt_sound.h gmove.h &
                states.h rt_sqrt.h rt_actor.h rt_playr.h isr.h rt_main.h &
                rt_draw.h rt_ted.h rt_door.h rt_menu.h rt_view.h rt_com.h &
                rt_in.h rt_util.h rt_game.h rt_rand.h z_zone.h rt_swift.h &
                engine.h _rt_play.h rt_cfg.h rt_spbal.h rt_floor.h develop.h &
                rottnet.h rt_msg.h rt_stat.h rt_debug.h rt_dmand.h

rt_net.o:     rt_net.c rt_net.h _rt_net.h rt_def.h rt_actor.h rt_playr.h &
                isr.h z_zone.h develop.h rottnet.h rt_msg.h rt_sound.h &
                rt_main.h rt_menu.h rt_rand.h rt_util.h rt_game.h rt_draw.h &
                rt_debug.h myprint.h rt_com.h rt_view.h rt_dmand.h

rt_rand.o:    rt_rand.c rt_def.h rt_rand.h _rt_rand.h develop.h rt_util.h &
                develop.h

rt_door.o:    rt_door.c rt_def.h rt_sound.h rt_door.h rt_actor.h rt_stat.h &
                _rt_door.h z_zone.h w_wad.h rt_ted.h rt_draw.h rt_playr.h &
                rt_main.h rt_util.h rt_menu.h rt_msg.h rt_vid.h isr.h &
                develop.h rt_net.h engine.h

rt_vh_a.o:    rt_vh_a.asm rt_vh_a.h

rt_sc_a.o:    rt_sc_a.asm rt_sc_a.h

rt_menu.o:    rt_menu.c rt_def.h _rt_menu.h rt_menu.h rt_sound.h fx_man.h &
                rt_build.h rt_in.h isr.h z_zone.h w_wad.h rt_util.h &
                rt_playr.h rt_rand.h rt_main.h rt_game.h rt_floor.h rt_draw.h &
                rt_view.h rt_str.h rt_vid.h rt_ted.h lumpy.h rt_cfg.h version.h &
                modexlib.h rt_msg.h rt_battl.h rt_net.h rt_spbal.h develop.h

rt_str.o:     rt_str.c rt_def.h rt_menu.h rt_util.h rt_vid.h rt_build.h &
                lumpy.h rt_str.h _rt_str.h isr.h rt_in.h rt_menu.h rt_view.h &
                w_wad.h z_zone.h modexlib.h rt_msg.h rt_playr.h

rt_vid.o:     rt_vid.c rt_def.h rt_vid.h _rt_vid.h rt_menu.h rt_util.h &
                profile.h watcom.h rt_str.h rt_draw.h rt_in.h rt_main.h &
                z_zone.h lumpy.h rt_vh_a.h isr.h rt_view.h modexlib.h w_wad.h

rt_in.o:      rt_in.c rt_def.h rt_in.h _rt_in.h isr.h rt_util.h &
                rt_in.h rt_swift.h rt_vh_a.h rt_cfg.h rt_playr.h rt_msg.h &
                rt_net.h

rt_game.o:    rt_game.c rt_def.h rt_game.h _rt_game.h rt_menu.h z_zone.h &
                w_wad.h lumpy.h rt_playr.h rt_util.h rt_ted.h rt_draw.h &
                rt_view.h rt_main.h rt_vid.h rt_door.h rt_in.h rt_str.h &
                isr.h rt_build.h rt_rand.h rt_cfg.h version.h rt_crc.h &
                modexlib.h engine.h rt_net.h rt_floor.h develop.h

rt_map.o:     rt_map.c rt_def.h sprites.h rt_map.h rt_dr_a.h _rt_map.h &
                isr.h rt_util.h rt_draw.h rt_stat.h z_zone.h w_wad.h &
                rt_playr.h lumpy.h rt_door.h rt_scale.h rt_vid.h rt_in.h &
                rt_ted.h rt_game.h rt_main.h rt_view.h develop.h rt_map.h &
                engine.h rt_floor.h modexlib.h rt_menu.h rt_net.h watcom.h

rt_debug.o:   rt_debug.c rt_def.h isr.h rt_debug.h rt_game.h rt_menu.h &
                rt_str.h rt_vid.h rt_playr.h rt_main.h rt_util.h rt_draw.h &
                rt_in.h z_zone.h rt_ted.h rt_view.h develop.h rt_msg.h &
                rt_net.h rt_map.h

scriplib.o:   scriplib.c scriplib.h rt_def.h rt_util.h

lookups.o:    lookups.c rt_def.h

rt_sound.o : rt_sound.c rt_def.h rt_sound.h _rt_soun.h fx_man.h music.h &
               z_zone.h w_wad.h rt_main.h rt_ted.h rt_menu.h rt_actor.h &
               rt_util.h watcom.h rt_cfg.h isr.h develop.h rt_playr.h &
               rt_net.h snd_reg.h snd_shar.h

rt_dmand.o : rt_dmand.c rt_def.h rt_sound.h fx_man.h rt_dmand.h _rt_dman.h &
               rt_net.h rt_util.h
        $(CC) $^& $(CFLAGS) /zu /d2

rt_swift.o : rt_swift.c rt_def.h rt_swift.h _rt_swft.h

rt_build.o : rt_build.c rt_def.h rt_build.h _rt_build.h rt_draw.h rt_dr_a.h &
               rt_scale.h rt_menu.h rt_main.h isr.h rt_util.h engine.h lumpy.h &
               rt_fc_a.h z_zone.h w_wad.h rt_view.h rt_cfg.h modexlib.h rt_vid.h

rt_com.o   : rt_com.c rt_com.h rt_def.h _rt_com.h rt_util.h rt_in.h isr.h &
               rt_playr.h rt_crc.h rt_msg.h rt_net.h rt_draw.h rt_ser.h

#rt_ser.obj   : rt_ser.c rt_ser.h _rt_ser.h
#
rt_spbal.o : rt_spbal.c rt_def.h watcom.h rt_draw.h rt_playr.h rt_spbal.h &
               isr.h _rt_spba.h sbconfig.h develop.h

# (spaceball configuration file functions)
sbconfig.o : sbconfig.h

rt_cfg.o:    rt_cfg.c rt_def.h rt_cfg.h scriplib.h rt_playr.h rt_menu.h &
               rt_game.h rt_in.h z_zone.h rt_sound.h rt_util.h rt_main.h &
               rt_view.h version.h rt_net.h isr.h develop.h

rt_crc.o  :  rt_crc.c rt_crc.h

rt_msg.o  :  rt_msg.c rt_msg.h _rt_msg.h rt_playr.h z_zone.h rt_view.h lumpy.h &
               w_wad.h rt_util.h rt_vid.h rt_str.h rt_menu.h isr.h rt_net.h

rt_error.o  :  rt_error.c rt_error.h rt_str.h isr.h rt_def.h w_wad.h rt_menu.h &
                 z_zone.h rt_vid.h rt_util.h modexlib.h

usrhooks.o  :  usrhooks.c usrhooks.h z_zone.h rt_def.h

modexlib.o  :  modexlib.c modexlib.h rt_def.h

rt_battl.o  : rt_battle.c rt_def.h rottnet.h isr.h rt_battl.h &
                rt_actor.h rt_rand.h rt_playr.h rt_game.h rt_sound.h &
                rt_util.h rt_main.h rottnet.h develop.h

f_scale.o:    f_scale.asm f_scale.h

cin_util.o  :  cin_util.c cin_util.h

cin_main.o  :  cin_main.c cin_main.h

cin_actr.o  :  cin_actr.c cin_actr.h

cin_evnt.o  :  cin_evnt.c cin_evnt.h

cin_efct.o  :  cin_efct.c cin_efct.h modexlib.h

cin_glob.o  :  cin_glob.c cin_glob.h

fli_util.o  :  fli_util.c fli_def.h fli_util.h fli_main.h fli_type.h cin_glob.h

fli_main.o  :  fli_main.c fli_def.h fli_util.h fli_main.h fli_type.h cin_glob.h

rott: $(ROTTOBJ)
        $(CC) $(ROTTOBJ) -o rott

lookups : lookups.o
        $(CC) -o lookups

all: rott lookups

clean:
        rm -rf out/*









