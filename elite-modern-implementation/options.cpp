#include "options.hpp"
#include "graphics.hpp"
#include <libconfig.h++>
#include <string>
#include "shapes.hpp"

const int  NUM_OPTIONS =  4;
const int  NUM_SETTINGS = 6;

const int OPTION_BAR_WIDTH = 400;
const int OPTION_BAR_HEIGHT = 15;

struct option
{
	std::string text;
	int docked_only;
};

option option_list[NUM_OPTIONS] =
{
	{"Save Commander",	1},
	{"Load Commander",	1},
	{"Game Settings",	0},
	{"Quit",			0}	
};

struct setting
{
	std::string name;
	std::string value[5];
};

setting setting_list[NUM_SETTINGS] =
{
	{"Graphics:",		{"Solid", "Wireframe", "", "", ""}},
	{"Anti Alias:",		{"Off", "On", "", "", ""}},		
	{"Planet Style:",	{"Wireframe", "Green", "SNES", "Fractal", ""}},
	{"Planet Desc.:",	{"BBC", "MSX", "", "", ""}},
	{"Instant Dock:",	{"Off", "On", "", "", ""}},	
	{"Save Settings",	{"", "", "", "", ""}}
};

void Options::read_config_file()
{

	libconfig::Config cfg;

	cfg.readFile("newkind.cfg");

	speed_cap = cfg.lookup("speed_cap");
	wireframe = cfg.lookup("wireframe");
	anti_alias_gfx = cfg.lookup("anti_alias_gfx");
	hoopy_casinos = cfg.lookup("hoopy_casinos");
	instant_dock = cfg.lookup("instant_dock");
	planet_render_style = cfg.lookup("planet_render_style");
}

Options& Options::instance()
{
	static Options op;
	return op;
}

void Options::write_config_file()
{

	libconfig::Config cfg;
	cfg.readFile("newkind.cfg");

	libconfig::Setting &wire_set = cfg.lookup("wireframe");
	libconfig::Setting &speed_set = cfg.lookup("speed_cap");
	libconfig::Setting &anit_alis_set = cfg.lookup("anti_alias_gfx");
	libconfig::Setting &hoopy_set = cfg.lookup("hoopy_casinos");
	libconfig::Setting &dock_set = cfg.lookup("instant_dock");
	libconfig::Setting &planet_set = cfg.lookup("planet_render_style");
	
	speed_set = speed_cap;
	wire_set = wireframe;
	anit_alis_set = anti_alias_gfx;
	hoopy_set = hoopy_casinos;
	dock_set = instant_dock;
	planet_set = planet_render_style;

	cfg.writeFile("newkind.cfg");

}
void Options::display_option_item (int i)
{
	Renderer ren;
	
	int y;
	int col;
	
	y = (384 - (30 * NUM_OPTIONS)) / 2;
	y += i * 30;
	col = (/*(!docked) && */option_list[i].docked_only) ? GFX_COL_GREY_1 : GFX_COL_WHITE;

	ren.display_centre_text(y, option_list[i].text, 120, col);
	
}
void Options::display_options()
{
	Renderer ren;
	int i;

	Graphics::instance().set_screen(options);
	
	ren.clear_display();
	ren.display_centre_text (10, "GAME OPTIONS", 140, GFX_COL_GOLD);
	ren.draw_line (0, 36, 511, 36);
	ren.display_centre_text (300, "Version: Release 1.0", 120, GFX_COL_WHITE);
	ren.display_centre_text (320, "www.newkind.co.uk", 120, GFX_COL_WHITE);
	ren.display_centre_text (340, "Written by Christian Pinder 1999-2001", 120, GFX_COL_WHITE);
	ren.display_centre_text (360, "Based on original code by Ian Bell & David Braben", 120, GFX_COL_WHITE);
	
	for (i = 0; i < NUM_OPTIONS; i++)
		display_option_item (i);

	hilite_item = -1;
	highlight_option (0);
}

void Options::display_setting_item(int item)
{
	Renderer ren;

	int x,y;
	int v;

	if (item == (NUM_SETTINGS - 1))
	{
		y = ((NUM_SETTINGS + 1) / 2) * 30 + 96 + 32;
		ren.display_centre_text (y, setting_list[item].name, 120, GFX_COL_WHITE);
		return;
	}
	
	switch (item)
	{
		case 0:
			v = wireframe;
			break;
		
		case 1:
			v = anti_alias_gfx;
			break;
		
		case 2:
			v = planet_render_style;
			break;
		
		case 3:
			v = hoopy_casinos;
			break;
		
		case 4:
			v = instant_dock;
			break;

		default:
			v = 0;
			break;
	}
	
	x = (item & 1) * 250 + 32; 
	y = (item / 2) * 30 + 96;
	
	ren.display_colour_text (x, y, setting_list[item].name, GFX_COL_WHITE);
	ren.display_colour_text (x + 120, y, setting_list[item].value[v], GFX_COL_WHITE);
}
void Options::highlight_setting(int item)
{
	BITMAP *gfx_screen = Graphics::instance().get_screen();
	Renderer ren;
	int x,y;
	int width;
	
	if ((hilite_item != -1) && (hilite_item != item))
	{
		if (hilite_item == (NUM_SETTINGS - 1))
		{
			x = GFX_X_CENTRE - (OPTION_BAR_WIDTH / 2);
			y = ((NUM_SETTINGS + 1) / 2) * 30 + 96 + 32;
			width = OPTION_BAR_WIDTH;
		}
		else
		{
			x = (hilite_item & 1) * 250 + 32 + 120; 
			y = (hilite_item / 2) * 30 + 96;
			width = 100;
		}

		ren.clear_area (x, y, x + width, y + OPTION_BAR_HEIGHT);
		display_setting_item (hilite_item);		
	}

	if (item == (NUM_SETTINGS - 1))
	{
		x = GFX_X_CENTRE - (OPTION_BAR_WIDTH / 2);
		y = ((NUM_SETTINGS + 1) / 2) * 30 + 96 + 32;
		width = OPTION_BAR_WIDTH;
	}
	else
	{
		x = (item & 1) * 250 + 32 + 120; 
		y = (item / 2) * 30 + 96;
		width = 100;
	}
	
	Rectangle rect(x, y, x + width, y + OPTION_BAR_HEIGHT, GFX_COL_DARK_RED,gfx_screen);
	rect.draw();
	display_setting_item (item);		
	hilite_item = item;
}

void Options::highlight_option(int i)
{
	BITMAP *gfx_screen = Graphics::instance().get_screen();
	Renderer ren;
	int y;
	int x;
	
	if ((hilite_item != -1) && (hilite_item != i))
	{
		x = GFX_X_CENTRE - (OPTION_BAR_WIDTH / 2);
		y = (384 - (30 * NUM_OPTIONS)) / 2;
		y += hilite_item * 30;
		ren.clear_area (x, y, x + OPTION_BAR_WIDTH, y + OPTION_BAR_HEIGHT);
		display_option_item (hilite_item);		
	}

	x = GFX_X_CENTRE - (OPTION_BAR_WIDTH / 2);
	y = (384 - (30 * NUM_OPTIONS)) / 2;
	y += i * 30;
	
	Rectangle rect(x, y, x + OPTION_BAR_WIDTH, y + OPTION_BAR_HEIGHT,
						GFX_COL_DARK_RED,gfx_screen);
	rect.draw();
	display_option_item (i);		

	hilite_item = i;

}

void Options::select_prev_option()
{
	if (hilite_item > 0)
		highlight_option (hilite_item - 1);
}

void Options::select_next_option()
{
	if (hilite_item < (NUM_OPTIONS - 1))
		highlight_option (hilite_item + 1);
}