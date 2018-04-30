#ifndef OPTIONS_HPP
#define OPTIONS_HPP
 		
class Options{
private:
	int wireframe = 0, anti_alias_gfx = 0, hoopy_casinos = 0, speed_cap = 75,
	 instant_dock = 0, planet_render_style = 0;
	 void read_config_file();

public:
	static Options& instance();
	Options()
	{read_config_file();}

	int get_speed() const 
	{ return speed_cap;}

	int get_anti_alias() const
	{ return anti_alias_gfx;}

	void write_config_file();
	
};


#endif