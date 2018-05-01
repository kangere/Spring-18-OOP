#ifndef OPTIONS_HPP
#define OPTIONS_HPP
 		


class Options{
private:
	int wireframe = 0, anti_alias_gfx = 0, hoopy_casinos = 0, speed_cap = 75,
	 instant_dock = 0, planet_render_style = 0;
	 int hilite_item;
	 
	 void read_config_file();
	 void display_option_item(int);
	 void display_setting_item(int);
	 void highlight_option(int);

public:
	static Options& instance();
	Options()
	{read_config_file();}

	int get_speed() const 
	{ return speed_cap;}

	int get_anti_alias() const
	{ return anti_alias_gfx;}

	void write_config_file();

	void display_options();
	void highlight_setting(int);
	void select_prev_option();
	void select_next_option();
	
};


#endif