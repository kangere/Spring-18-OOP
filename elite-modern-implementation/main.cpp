#include <iostream>
#include "vector.hpp"
#include "sound.hpp"
#include "graphics.hpp"
#include "options.hpp"
#include <allegro.h>


/*Function to initialise allegro*/
void init()
{
	allegro_init();
	install_keyboard();
	install_timer();
	install_mouse();

}

int main()
{
	/*init();

	if(Graphics::instance().startup() == 1)
		std::cout << "graphics not set up" << std::endl;*/

	Options op;
	op.write_config_file();

	

	std::cout << "Hello" << std::endl;

	return 0;
}

END_OF_MAIN()