CC=gcc
CFLAGS=-c -g -m32 $(INCDIRS)
LDFLAGS=-m32
INCDIRS=-Irott

#ROTTOBJ=isr.o  w_wad.o rt_scale.o engine.o \
	rt_dr_a.o rt_fc_a.o rt_floor.o rt_util.o \
	rt_stat.o  rt_state.o rt_ted.o rt_playr.o \
	rt_rand.o rt_door.o rt_menu.o rt_vid.o rt_vh_a.o \
	rt_str.o rt_in.o rt_sc_a.o  rt_map.o \
	rt_debug.o rt_sound.o  f_scale.o \
	rt_swift.o rt_build.o rt_com.o \
	rt_view.o rt_cfg.o rt_spbal.o sbconfig.o rt_err.o \
	rt_crc.o rt_msg.o modexlib.o rt_battl.o \
	usrhooks.o rt_error.o rt_net.o  \
	fli_util.o fli_main.o rt_dmand.o \

ROTTOBJ=out/cin_actr.o out/cin_util.o out/compat_conio.o out/cin_evnt.o \
	out/cin_efct.o out/cin_glob.o out/cin_main.o out/scriplib.o \
    out/z_zone.o out/rt_main.o out/rt_draw.o out/compat_stdlib.o \
	out/rt_game.o out/rt_actor.o

out/compat_conio.o: rott/compat_conio.c
	@$(CC) $(CFLAGS) -o $@ $<

out/compat_stdlib.o: rott/compat_stdlib.c
	@$(CC) $(CFLAGS) -o $@ $<

out/isr.o: rott/isr.c
	@$(CC) $(CFLAGS) -o $@ $<

out/z_zone.o: rott/z_zone.c
	@$(CC) $(CFLAGS) -o $@ $<

out/w_wad.o: rott/w_wad.c
	@$(CC) $(CFLAGS) -o $@ $<

out/rt_scale.o: rott/rt_scale.c
	@$(CC) $(CFLAGS) -o $@ $<

out/rt_view.o: rott/rt_view.c
	@$(CC) $(CFLAGS) -o $@ $<

out/rt_draw.o: rott/rt_draw.c
	@$(CC) $(CFLAGS) -o $@ $<

out/engine.o: rott/engine.c
	@$(CC) $(CFLAGS) -o $@ $<
#
#rt_eng.obj:     rt_eng.asm rt_eng.h
#
out/rt_fc_a.o:  rott/rt_fc_a.asm
	@$(CC) $(CFLAGS) -o $@ $<

out/rt_floor.o: rott/rt_floor.c
	@$(CC) $(CFLAGS) -o $@ $<

out/rt_dr_a.o:  rott/rt_dr_a.asm
	@$(CC) $(CFLAGS) -o $@ $<

out/rt_main.o: rott/rt_main.c
	@$(CC) $(CFLAGS) -o $@ $<

#\\JIM

out/rt_util.o: rott/rt_util.c
	@$(CC) $(CFLAGS) -o $@ $<

out/rt_stat.o: rott/rt_stat.c
	@$(CC) $(CFLAGS) -o $@ $<

out/rt_actor.o: rott/rt_actor.c
	@$(CC) $(CFLAGS) -o $@ $<

out/rt_state.o: rott/rt_state.c
	@$(CC) $(CFLAGS) -o $@ $<

out/rt_ted.o: rott/rt_ted.c
	@$(CC) $(CFLAGS) -o $@ $<

out/rt_playr.o: rott/rt_playr.c 
	@$(CC) $(CFLAGS) -o $@ $<

out/rt_net.o: rott/rt_net.c
	@$(CC) $(CFLAGS) -o $@ $<

out/rt_rand.o:  rott/rt_rand.c
	@$(CC) $(CFLAGS) -o $@ $<

out/rt_door.o: rott/rt_door.c
	@$(CC) $(CFLAGS) -o $@ $<

out/rt_vh_a.o: rott/rt_vh_a.asm
	@$(CC) $(CFLAGS) -o $@ $<

out/rt_sc_a.o: rott/rt_sc_a.asm
	@$(CC) $(CFLAGS) -o $@ $<

out/rt_menu.o: rott/rt_menu.c
	@$(CC) $(CFLAGS) -o $@ $<

out/rt_str.o: rott/rt_str.c
	@$(CC) $(CFLAGS) -o $@ $<

out/rt_vid.o: rott/rt_vid.c
	@$(CC) $(CFLAGS) -o $@ $<

out/rt_in.o: rott/rt_in.c
	@$(CC) $(CFLAGS) -o $@ $<

out/rt_game.o: rott/rt_game.c
	@$(CC) $(CFLAGS) -o $@ $<

out/rt_map.o: rott/rt_map.c
	@$(CC) $(CFLAGS) -o $@ $<

out/rt_debug.o: rott/rt_debug.c
	@$(CC) $(CFLAGS) -o $@ $<

out/scriplib.o: rott/scriplib.c
	@$(CC) $(CFLAGS) -o $@ $<

out/lookups.o: rott/lookups.c
	@$(CC) $(CFLAGS) -o $@ $<

out/rt_sound.o: rott/rt_sound.c
	@$(CC) $(CFLAGS) -o $@ $<

out/rt_dmand.o: rott/rt_dmand.c
	@$(CC) $(CFLAGS) -o $@ $<

out/rt_swift.o: rott/rt_swift.c
	@$(CC) $(CFLAGS) -o $@ $<

out/rt_build.o: rott/rt_build.c
	@$(CC) $(CFLAGS) -o $@ $<

out/rt_com.o: rott/rt_com.c
	@$(CC) $(CFLAGS) -o $@ $<

#rt_ser.obj   : rt_ser.c rt_ser.h _rt_ser.h
#
out/rt_spbal.o: rott/rt_spbal.c
	@$(CC) $(CFLAGS) -o $@ $<

out/rt_cfg.o: rott/rt_cfg.c
	@$(CC) $(CFLAGS) -o $@ $<

out/rt_crc.o: rott/rt_crc.c
	@$(CC) $(CFLAGS) -o $@ $<

out/rt_msg.o: rott/rt_msg.c
	@$(CC) $(CFLAGS) -o $@ $<

out/rt_error.o: rott/rt_error.c
	@$(CC) $(CFLAGS) -o $@ $<

out/usrhooks.o: rott/usrhooks.c
	@$(CC) $(CFLAGS) -o $@ $<

out/modexlib.o: rott/modexlib.c
	@$(CC) $(CFLAGS) -o $@ $<

out/rt_battl.o: rott/rt_battle.c
	@$(CC) $(CFLAGS) -o $@ $<

out/f_scale.o: rott/f_scale.asm 
	@$(CC) $(CFLAGS) -o $@ $<

out/cin_util.o: rott/cin_util.c
	@$(CC) $(CFLAGS) -o $@ $<

out/cin_main.o: rott/cin_main.c
	@$(CC) $(CFLAGS) -o $@ $<

out/cin_actr.o: rott/cin_actr.c
	@$(CC) $(CFLAGS) -o $@ $<

out/cin_evnt.o: rott/cin_evnt.c
	@$(CC) $(CFLAGS) -o $@ $<

out/cin_efct.o: rott/cin_efct.c
	@$(CC) $(CFLAGS) -o $@ $<

out/cin_glob.o: rott/cin_glob.c
	@$(CC) $(CFLAGS) -o $@ $<

out/fli_util.o: rott/fli_util.c
	@$(CC) $(CFLAGS) -o $@ $<

out/fli_main.o: rott/fli_main.c
	@$(CC) $(CFLAGS) -o $@ $<

out/rott: $(ROTTOBJ)
	$(CC) $(LDFLAGS) $(ROTTOBJ) -o out/rott

#lookups : out/lookups.o
#	$(CC) $(LDFLAGS) lookups.o -o lookups

all: out/rott #lookups

clean:
	rm -rf out/*
