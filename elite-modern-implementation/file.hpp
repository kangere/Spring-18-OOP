#ifndef FILE_HPP
#define FILE_HPP

#include <fstream>
/*Class to handle file operations for config files*/
class File{
private:
	std::ifstream file;


public:
	void write_config_file();
};


#endif