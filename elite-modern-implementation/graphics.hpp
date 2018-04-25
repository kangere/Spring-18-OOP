#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP
#include <cassert>

/*constants used for graphics rendering*/
#ifdef RES_512_512

const int GFX_SCALE	= 2;
const int GFX_X_OFFSET = 0;
const int GFX_Y_OFFSET = 0;
const int GFX_X_CENTRE = 256;
const int GFX_Y_CENTRE = 192;

const int GFX_VIEW_TX = 1;
const int GFX_VIEW_TY = 1;
const int GFX_VIEW_BX = 509;
const int GFX_VIEW_BY = 381;

#endif

#ifdef RES_800_600

const int GFX_SCALE	= 2;
const int GFX_X_OFFSET = 144;
const int GFX_Y_OFFSET = 44;
const int GFX_X_CENTRE = 256;
const int GFX_Y_CENTRE = 192;

const int GFX_VIEW_TX = 1;
const int GFX_VIEW_TY = 1;
const int GFX_VIEW_BX =	509;
const int GFX_VIEW_BY = 381;

#endif

#ifndef GFX_SCALE

const int GFX_SCALE	 = 1;
const int GFX_X_OFFSET = 0;
const int GFX_Y_OFFSET = 0;
const int GFX_X_CENTRE = 128;
const int GFX_Y_CENTRE = 96;

const int GFX_VIEW_TX = 1;
const int GFX_VIEW_TY = 1;
const int GFX_VIEW_BX = 253;
const int GFX_VIEW_BY = 191;

#endif
 


const int GFX_COL_BLACK	= 0;
const int GFX_COL_DARK_RED = 28;
const int GFX_COL_WHITE	= 255;
const int GFX_COL_GOLD	= 39;
const int GFX_COL_RED = 49;
const int GFX_COL_CYAN = 11;

const int GFX_COL_GREY_1 = 248;
const int GFX_COL_GREY_2 = 235;
const int GFX_COL_GREY_3 = 234;
const int GFX_COL_GREY_4 = 237;

const int GFX_COL_BLUE_1 = 45;
const int GFX_COL_BLUE_2 = 46;
const int GFX_COL_BLUE_3 = 133;
const int GFX_COL_BLUE_4 = 4;

const int GFX_COL_RED_3	 = 1; 
const int GFX_COL_RED_4	 = 71;

const int GFX_COL_WHITE_2 = 242;

const int GFX_COL_YELLOW_1 = 37;
const int GFX_COL_YELLOW_2 = 39;
const int GFX_COL_YELLOW_3 = 89;
const int GFX_COL_YELLOW_4 = 160;
const int GFX_COL_YELLOW_5 = 251;

const int GFX_ORANGE_1	= 76;
const int GFX_ORANGE_2	= 77;
const int GFX_ORANGE_3	= 122;

const int GFX_COL_GREEN_1 = 2;
const int GFX_COL_GREEN_2 = 17;
const int GFX_COL_GREEN_3 = 86;

const int GFX_COL_PINK_1 = 183;

const int IMG_GREEN_DOT	 = 1;
const int IMG_RED_DOT = 2;
const int IMG_BIG_S	 = 3;
const int IMG_ELITE_TXT	= 4;
const int IMG_BIG_E	= 5;
const int IMG_DICE	= 6;
const int IMG_MISSILE_GREEN	 = 7;
const int IMG_MISSILE_YELLOW = 8;
const int IMG_MISSILE_RED = 9;
const int IMG_BLAKE	 = 10;

#include "allegro.h"

/*This class will handle rendering of objects and decouple graphics
rendering from the entities*/
class Graphics{
private:
	BITMAP *gfx_screen;
	DATAFILE *datafile;
	BITMAP *scanner_image;
	 
	void draw_aa_line(int,int,int,int);
	
	
	/*This two variables were formerly found in elite.c/.h files
	defined here to allow for decoupling of graphics operations*/
	
	char scanner_filename[256]; // not used - constant filename that never changes
	int speed_cap = 75;
	int anti_alias_gfx = 0;
public:
	Graphics(){}
	int startup();
	void draw_line(int,int,int,int);
	void shutdown();
	/*use singleton pattern*/
	static Graphics& instance();
	void update_screen();
	
	BITMAP* get_screen () const
	{ return gfx_screen;}

	DATAFILE* get_datafile() const
	{ return datafile;}


	
};

class renderer{
private:
	BITMAP* gfx_screen = Graphics::instance().get_screen();
	DATAFILE* datafile = Graphics::instance().get_datafile();
	

public:
	void display_text(int x, int y, char *txt);
	void display_colour_text(int x, int y, char *txt, int col);
	void display_centre_text(int y, char *str, int psize, int col);
	void clear_display();
	void clear_text_area();
	void clear_area(int tx, int ty, int bx, int by);
};


#endif