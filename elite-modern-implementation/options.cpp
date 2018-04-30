#include "options.hpp"
#include <libconfig.h++>


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
