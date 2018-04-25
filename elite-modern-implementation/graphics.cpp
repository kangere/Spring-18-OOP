#include "graphics.hpp"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <iostream>

#define AA_BITS 3
#define AA_AND  7
#define AA_BASE 235

#define trunc(x) ((x) & ~65535)
#define frac(x) ((x) & 65535)
#define invfrac(x) (65535-frac(x))
#define plot(x,y,c) putpixel(gfx_screen, (x), (y), (c)+AA_BASE)

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
	
	datafile = load_datafile("elite.dat");
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
	draw_line (0, 0, 0, 384);
	draw_line (0, 0, 511, 0);
	draw_line (511, 0, 511, 384);

	/* Install a timer to regulate the speed of the game... */

	LOCK_VARIABLE(frame_count);
	LOCK_FUNCTION(frame_timer);
	frame_count = 0;
	install_int (frame_timer, speed_cap);
	
	return 0;

}

void Graphics::draw_line(int x1, int y1, int x2, int y2)
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

	if (anti_alias_gfx)
		draw_aa_line (itofix(x1), itofix(y1), itofix(x2), itofix(y2));
	else
		line (gfx_screen, x1 + GFX_X_OFFSET, y1 + GFX_Y_OFFSET, x2 + GFX_X_OFFSET, y2 + GFX_Y_OFFSET, GFX_COL_WHITE);
}

void Graphics::draw_aa_line(int x1, int y1, int x2, int y2)
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

