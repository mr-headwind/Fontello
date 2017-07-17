show_pango_typefaces:	show_pango_typefaces.c
	cc -o $@ -Wall -g show_pango_typefaces.c \
	`pkg-config --cflags --libs gtk+-3.0` \
	`pkg-config --cflags --libs pango` \
	`pkg-config --cflags --libs cairo` \
	`pkg-config --cflags --libs pangocairo` \
	`pkg-config --cflags --libs glib-2.0`
