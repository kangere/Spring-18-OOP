#ifndef SOUND_HPP
#define SOUND_HPP

#include <allegro.h>
#include <string>
#include <vector>

class Sound{
private:
	SAMPLE *sample;
	std::string filename;
	int runtime;
	int timeleft;
	bool sound_on;

public:
	Sound() {}
	Sound(SAMPLE* sample,std::string filename,int runtime, int timeleft):
	sample(sample), filename(filename), runtime(runtime), timeleft(timeleft)
	{}
	void start();
};

void sound_startup(std::vector<Sound*>);
#endif