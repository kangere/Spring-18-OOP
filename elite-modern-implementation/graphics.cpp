#include "graphics.hpp"
#include "alg_data.h"
#include "options.hpp"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <ctype.h>
#include <iostream>



volatile int frame_count = 0;

void frame_timer()
{
	frame_count++;
}
END_OF_FUNCTION(frame_timer);


int Graphics::startup()
{
	PALETTE the_palette;
	int rv;

#ifdef ALLEGRO_WINDOWS	

#ifdef RES_512_512
	rv = set_gfx_mode(GFX_DIRECTX_OVL, 512, 512, 0, 0);
	
	if (rv != 0)
		rv = set_gfx_mode(GFX_DIRECTX_WIN, 512, 512, 0, 0);

	if (rv != 0)
		rv = set_gfx_mode(GFX_GDI, 512, 512, 0, 0);

	if (rv == 0)
		set_display_switch_mode (SWITCH_BACKGROUND);
#else
 	rv = set_gfx_mode(GFX_DIRECTX, 800, 600, 0, 0);
	
	if (rv != 0)
		rv = set_gfx_mode(GFX_GDI, 800, 600, 0, 0);
#endif

#else
	rv = set_gfx_mode(GFX_AUTODETECT, 800, 600, 0, 0);
#endif

	if (rv != 0)
	{
		set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
      	allegro_message("Unable to set graphics mode.");
      	
      	return 1;
	}
	
	/*datafile = load_datafile("elite.dat");*/
	if (!datafile)
	{
		set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
      	allegro_message("Error loading %s!\n", "elite.dat");
      	return 1;
	}

	scanner_image = load_bitmap("scanner.bmp", the_palette);
	if (!scanner_image)
	{
		set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
		allegro_message("Error reading scanner bitmap file.\n");
		return 1;
	}

	/* select the scanner palette */
	set_palette(the_palette);

	/* Create the screen buffer bitmap */
	gfx_screen = create_bitmap (SCREEN_W, SCREEN_H);

	clear (gfx_screen);

	blit (scanner_image, gfx_screen, 0, 0, GFX_X_OFFSET, 385+GFX_Y_OFFSET, scanner_image->w, scanner_image->h);
	Renderer ren;
	ren.draw_line (0, 0, 0, 384);
	ren.draw_line (0, 0, 511, 0);
	ren.draw_line (511, 0, 511, 384);

	/* Install a timer to regulate the speed of the game... */

	LOCK_VARIABLE(frame_count);
	LOCK_FUNCTION(frame_timer);
	frame_count = 0;
	install_int (frame_timer, Options::instance().get_speed());
	
	return 0;

}

void Renderer::draw_line(int x1, int y1, int x2, int y2)
{
	if (y1 == y2)
	{
		hline (gfx_screen, x1 + GFX_X_OFFSET, y1 + GFX_Y_OFFSET, x2 + GFX_X_OFFSET, GFX_COL_WHITE);
		return;
	}

	if (x1 == x2)
	{
		vline (gfx_screen, x1 + GFX_X_OFFSET, y1 + GFX_Y_OFFSET, y2 + GFX_Y_OFFSET, GFX_COL_WHITE);
		return;
	}

	if (Options::instance().get_anti_alias())
		draw_aa_line (itofix(x1), itofix(y1), itofix(x2), itofix(y2));
	else
		line (gfx_screen, x1 + GFX_X_OFFSET, y1 + GFX_Y_OFFSET, x2 + GFX_X_OFFSET, y2 + GFX_Y_OFFSET, GFX_COL_WHITE);
}

void Renderer::draw_aa_line(int x1, int y1, int x2, int y2)
{
	fixed grad, xd, yd;
	fixed xgap, ygap, xend, yend, xf, yf;
	fixed brightness1, brightness2, swap;

	int x, y, ix1, ix2, iy1, iy2;

	x1 += itofix(GFX_X_OFFSET);
	x2 += itofix(GFX_X_OFFSET);
	y1 += itofix(GFX_Y_OFFSET);
	y2 += itofix(GFX_Y_OFFSET);

	xd = x2 - x1;
	yd = y2 - y1;

	if (abs(xd) > abs(yd))
	{
		if(x1 > x2)
		{
			swap = x1; x1 = x2; x2 = swap;
			swap = y1; y1 = y2; y2 = swap;
			xd   = -xd;
			yd   = -yd;
		}

		grad = fdiv(yd, xd);

		//end point 1

		xend = trunc(x1 + 32768);
		yend = y1 + fmul(grad, xend-x1);

		xgap = invfrac(x1+32768);

		ix1  = xend >> 16;
		iy1  = yend >> 16;

		brightness1 = fmul(invfrac(yend), xgap);
		brightness2 = fmul(frac(yend), xgap);

		plot(ix1, iy1, brightness1 >> (16-AA_BITS));
		plot(ix1, iy1+1, brightness2 >> (16-AA_BITS));

		yf = yend+grad;

		//end point 2;

		xend = trunc(x2 + 32768);
		yend = y2 + fmul(grad, xend-x2);

		xgap = invfrac(x2 - 32768);

		ix2 = xend >> 16;
		iy2 = yend >> 16;

		brightness1 = fmul(invfrac(yend), xgap);
		brightness2 = fmul(frac(yend), xgap);
      
		plot(ix2, iy2, brightness1 >> (16-AA_BITS));
		plot(ix2, iy2+1, brightness2 >> (16-AA_BITS));

		for(x = ix1+1; x <= ix2-1; x++)
		{
			brightness1 = invfrac(yf);
			brightness2 = frac(yf);

			plot(x, (yf >> 16), brightness1 >> (16-AA_BITS));
			plot(x, 1+(yf >> 16), brightness2 >> (16-AA_BITS));

			yf += grad;
		}
	}
	else
	{
		if(y1 > y2)
		{
			swap = x1; x1 = x2; x2 = swap;
			swap = y1; y1 = y2; y2 = swap;
			xd   = -xd;
			yd   = -yd;
		}

		grad = fdiv(xd, yd);

		//end point 1

		yend = trunc(y1 + 32768);
		xend = x1 + fmul(grad, yend-y1);

		ygap = invfrac(y1+32768);

		iy1  = yend >> 16;
		ix1  = xend >> 16;

		brightness1 = fmul(invfrac(xend), ygap);
		brightness2 = fmul(frac(xend), ygap);

		plot(ix1, iy1, brightness1 >> (16-AA_BITS));
		plot(ix1+1, iy1, brightness2 >> (16-AA_BITS));

		xf = xend+grad;

		//end point 2;

		yend = trunc(y2 + 32768);
		xend = x2 + fmul(grad, yend-y2);

		ygap = invfrac(y2 - 32768);

		ix2 = xend >> 16;
		iy2 = yend >> 16;

		brightness1 = fmul(invfrac(xend), ygap);
		brightness2 = fmul(frac(xend), ygap);
      
		plot(ix2, iy2, brightness1 >> (16-AA_BITS));
		plot(ix2+1, iy2, brightness2 >> (16-AA_BITS));

		for(y = iy1+1; y <= iy2-1; y++)
		{
			brightness1 = invfrac(xf);
			brightness2 = frac(xf);

			plot((xf >> 16), y, brightness1 >> (16-AA_BITS));
			plot(1+(xf >> 16), y, brightness2 >> (16-AA_BITS));

			xf += grad;
		}
	}

}

void Graphics::shutdown()
{
	destroy_bitmap(scanner_image);
	destroy_bitmap(gfx_screen);
	unload_datafile(datafile);
}

Graphics& Graphics::instance()
{
	static Graphics g;
	return g;
}

void Graphics::update_screen()
{
	while (frame_count < 1)
		rest (10);
	frame_count = 0;
	
	acquire_screen();
 	blit (gfx_screen, screen, GFX_X_OFFSET, GFX_Y_OFFSET, GFX_X_OFFSET, GFX_Y_OFFSET, 512, 512);
	release_screen();
}

void Renderer::display_text(int x, int y, char *txt)
{
	display_colour_text(x,y,txt,GFX_COL_WHITE);
}

void Renderer::display_colour_text(int x, int y, std::string txt, int col)
{
	
	text_mode (-1);
	if(datafile)
		textout (gfx_screen, font/*datafile[ELITE_1].dat*/, txt.c_str(), (x / (2 / GFX_SCALE)) + GFX_X_OFFSET, (y / (2 / GFX_SCALE)) + GFX_Y_OFFSET, col);
	else
		allegro_message("Datafile not set");
}

void Renderer::display_centre_text(int y, std::string str, int psize, int col)
{
	int txt_size;
	int txt_colour;
	
	if (psize == 140)
	{
		txt_size = ELITE_2;
		txt_colour = -1;
	}
	else
	{
		txt_size = ELITE_1;
		txt_colour = col;
	}

	text_mode (-1);
	if(datafile)
		textout_centre (gfx_screen,  font/*datafile[txt_size].dat*/, str.c_str(), (128 * GFX_SCALE) + GFX_X_OFFSET, (y / (2 / GFX_SCALE)) + GFX_Y_OFFSET, txt_colour);
	else
		allegro_message("Datafile not loaded");
}

void Renderer::clear_display()
{
	rectfill (gfx_screen, GFX_X_OFFSET + 1, GFX_Y_OFFSET + 1, 510 + GFX_X_OFFSET, 383 + GFX_Y_OFFSET, GFX_COL_BLACK);
}

void Renderer::clear_text_area()
{
	rectfill (gfx_screen, GFX_X_OFFSET + 1, GFX_Y_OFFSET + 340, 510 + GFX_X_OFFSET, 383 + GFX_Y_OFFSET, GFX_COL_BLACK);
}

void Renderer::clear_area(int tx, int ty, int bx, int by)
{
	rectfill (gfx_screen, tx + GFX_X_OFFSET, ty + GFX_Y_OFFSET,
				   bx + GFX_X_OFFSET, by + GFX_Y_OFFSET, GFX_COL_BLACK);
}

void Renderer::pretty_text(int tx, int ty, int bx, int by, char *txt)
{
	char strbuf[100];
	char *str;
	char *bptr;
	int len;
	int pos;
	int maxlen;
	
	maxlen = (bx - tx) / 8;

	str = txt;	
	len = strlen(txt);
	
	while (len > 0)
	{
		pos = maxlen;
		if (pos > len)
			pos = len;

		while ((str[pos] != ' ') && (str[pos] != ',') &&
			   (str[pos] != '.') && (str[pos] != '\0'))
		{
			pos--;
		}

		len = len - pos - 1;
	
		for (bptr = strbuf; pos >= 0; pos--)
			*bptr++ = *str++;

		*bptr = '\0';

		text_mode (-1);
		textout (gfx_screen, font/*datafile[ELITE_1].dat*/, strbuf, tx + GFX_X_OFFSET, ty + GFX_Y_OFFSET, GFX_COL_WHITE);
		ty += (8 * GFX_SCALE);
	}
}

void Renderer::r_draw_sprite(int sprite_no, int x, int y)
{
	BITMAP *sprite_bmp;
	PALETTE palette;
	
	switch (sprite_no)
	{
		case IMG_GREEN_DOT:
			sprite_bmp = load_bitmap("greendot.bmp",palette);
			break;
		
		case IMG_RED_DOT:
			sprite_bmp = load_bitmap("reddot.bmp",palette);
			break;
			
		case IMG_BIG_S:
			sprite_bmp = load_bitmap("safe.bmp",palette);
			break;
		
		case IMG_ELITE_TXT:
			sprite_bmp = load_bitmap("elitetx3.bmp",palette);
			break;
			
		case IMG_BIG_E:
			sprite_bmp = load_bitmap("ecm.bmp",palette);
			break;
			
		case IMG_BLAKE:
			sprite_bmp = load_bitmap("blake.bmp",palette);
			break;
		
		case IMG_MISSILE_GREEN:
			sprite_bmp = load_bitmap("missgrn.bmp",palette);
			break;

		case IMG_MISSILE_YELLOW:
			sprite_bmp = load_bitmap("missyell.bmp",palette);
			break;

		case IMG_MISSILE_RED:
			sprite_bmp = load_bitmap("missred.bmp",palette);
			break;

		default:
			return;
	}
	 set_palette(palette);

	if (x == -1)
		x = ((256 * GFX_SCALE) - sprite_bmp->w) / 2;
	
	draw_sprite (gfx_screen, sprite_bmp, x + GFX_X_OFFSET, y + GFX_Y_OFFSET);
}


void Graphics::draw_scanner()
{
	blit (scanner_image, gfx_screen, 0, 0, GFX_X_OFFSET, 385+GFX_Y_OFFSET, scanner_image->w, scanner_image->h);
}

void Renderer::plot_fast_pixel(int x, int y, int col)
{
	gfx_screen->line[y][x] = col;
}

void Renderer::plot_pixel (int x, int y, int col)
{
	putpixel (gfx_screen, x + GFX_X_OFFSET, y + GFX_Y_OFFSET, col);
}