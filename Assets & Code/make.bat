/opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -c -o game.o game.c
/opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -c -o skies.o skies.c
/opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -c -o theme.o theme.c
/opt/gbdk/bin/lcc -Wa-l -Wf-ba0 -c -o savestate.o savestate.c
/opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -Wf-bo1 -c -o controls_data.o controls_data.c
/opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -Wf-bo1 -c -o controls_map.o controls_map.c
/opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -Wf-bo2 -c -o gameover_data.o gameover_data.c
/opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -Wf-bo2 -c -o gameover_map.o gameover_map.c
/opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -Wf-bo3 -c -o journey_data.o journey_data.c
/opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -Wf-bo3 -c -o journey_map.o journey_map.c
/opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -Wf-bo4 -c -o letter_data.o letter_data.c
/opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -Wf-bo4 -c -o letter_map.o letter_map.c
/opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -Wf-bo5 -c -o logo_data.o logo_data.c
/opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -Wf-bo5 -c -o logo_map.o logo_map.c
/opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -Wf-bo6 -c -o pause_data.o pause_data.c
/opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -Wf-bo6 -c -o pause_map.o pause_map.c
/opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -Wf-bo7 -c -o return_data.o return_data.c
/opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -Wf-bo7 -c -o return_map.o return_map.c
/opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -Wf-bo8 -c -o titlescreen_data.o titlescreen_data.c
/opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -Wf-bo8 -c -o titlescreen_map.o titlescreen_map.c
/opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -Wf-bo9 -c -o prntscore.o prntscore.c
/opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -Wf-bo10 -c -o ValerioSprites.o ValerioSprites.c
/opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -Wf-bo11 -c -o gbt_player.o gbt_player.s
/opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -Wf-bo12 -c -o gbt_player_bank1.o gbt_player_bank1.s
/opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -Wl-yt3 -Wl-yo16 -Wl-ya4 -o ../web/rom/game.gb game.o skies.o theme.o gbt_player.o gbt_player_bank1.o savestate.o controls_data.o controls_map.o gameover_data.o gameover_map.o journey_data.o journey_map.o letter_data.o letter_map.o logo_data.o logo_map.o pause_data.o pause_map.o return_data.o return_map.o titlescreen_data.o titlescreen_map.o prntscore.o ValerioSprites.o