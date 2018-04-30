#include "shapes.hpp"

void Triangle::draw()
{
	triangle (gfx_screen, x1 + GFX_X_OFFSET, y1 + GFX_Y_OFFSET, x2 + GFX_X_OFFSET, y2 + GFX_Y_OFFSET,
				   x3 + GFX_X_OFFSET, y3 + GFX_Y_OFFSET, col);
}

void Rectangle::draw()
{
	rectfill (gfx_screen, tx + GFX_X_OFFSET, ty + GFX_Y_OFFSET,
				   bx + GFX_X_OFFSET, by + GFX_Y_OFFSET, col);
}

void Circle::draw_aa_circle()
{
	int x,y;
	int s;
	int sx, sy;

	cx += GFX_X_OFFSET;
	cy += GFX_Y_OFFSET;

	radius >>= (16 - AA_BITS);

	x = radius;
	s = -radius;
	y = 0;

	while (y <= x)
	{
		//wide pixels
		sx = cx + (x >> AA_BITS); sy = cy + (y >> AA_BITS);

		plot(sx,	sy,	AA_AND - (x&AA_AND));
		plot(sx + 1,	sy,	x&AA_AND);

		sy = cy - (y >> AA_BITS);

		plot(sx,	sy,	AA_AND - (x&AA_AND));
		plot(sx + 1,	sy,	x&AA_AND);

		sx = cx - (x >> AA_BITS);

		plot(sx,	sy,	AA_AND - (x&AA_AND));
		plot(sx - 1,	sy,	x&AA_AND);

		sy = cy + (y >> AA_BITS);

		plot(sx,	sy,	AA_AND - (x&AA_AND));
		plot(sx - 1,	sy,	x&AA_AND);

		//tall pixels
		sx = cx + (y >> AA_BITS); sy = cy + (x >> AA_BITS);

		plot(sx,	sy,	AA_AND - (x&AA_AND));
		plot(sx,	sy + 1,	x&AA_AND);

		sy = cy - (x >> AA_BITS);

		plot(sx,	sy,	AA_AND - (x&AA_AND));
		plot(sx,	sy - 1,	x&AA_AND);

		sx = cx - (y >> AA_BITS);

		plot(sx,	sy,	AA_AND - (x&AA_AND));
		plot(sx,	sy - 1,	x&AA_AND);

		sy = cy + (x >> AA_BITS);

		plot(sx,	sy,	AA_AND - (x&AA_AND));
		plot(sx,	sy + 1,	x&AA_AND);

		s +=	AA_AND+1 + (y << (AA_BITS+1)) + ((1 << (AA_BITS+2))-2);
		y +=	AA_AND+1;

		while(s >= 0)
		{
			s -= (x << 1) + 2;
			x --;
		}
	}
}

void Circle::draw()
{
	// if (anti_alias_gfx && (circle_colour == GFX_COL_WHITE))
	// 	gfx_draw_aa_circle (cx, cy, itofix(radius));
	// else	
	// 	circle (gfx_screen, cx + GFX_X_OFFSET, cy + GFX_Y_OFFSET, radius, circle_colour);
}

void Circle::draw_filled()
{
	circlefill (gfx_screen, cx + GFX_X_OFFSET, cy + GFX_Y_OFFSET, radius, col);
}