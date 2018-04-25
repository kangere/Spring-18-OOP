#include "file.hpp"
#include <fstream>

void File::write_config_file()
{
	file.open("newkind.cfg",std::ifstream::out);

	if(!file.is_open())
		return;

	
}