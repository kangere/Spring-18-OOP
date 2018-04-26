#ifndef SOUND_HPP
#define SOUND_HPP

#include <allegro.h>
#include <string>
#include <vector>

#define SND_ELITE_THEME 0
#define SND_BLUE_DANUBE 1

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
	void shutdown();
	void play();
	void update();
	bool is_sound_on()
	{return sound_on;}
};

/*DATAFILE *datafile;*/

/*util functions*/
void sound_startup(std::vector<Sound*>);
void sound_shutdown(std::vector<Sound*>);
void sound_play(std::vector<Sound*>);
void sound_update(std::vector<Sound*>);
void play_midi_d(int,int);
void stop_midi();

#endif