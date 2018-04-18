#include "sound.hpp"
#include <vector>


std::vector<Sound*> sample_list 
{
	new Sound(NULL, "launch.wav",    32, 0),
	new Sound(NULL, "crash.wav",      7, 0),
	new Sound(NULL, "dock.wav",      36, 0),
	new Sound(NULL, "gameover.wav",  24, 0),
	new Sound(NULL, "pulse.wav",      4, 0),
	new Sound(NULL, "hitem.wav",	4, 0),
	new Sound(NULL, "explode.wav",	23, 0),
	new Sound(NULL, "ecm.wav",		23, 0),
	new Sound(NULL, "missile.wav",	25, 0),
	new Sound(NULL, "hyper.wav",	 37, 0),
	new Sound(NULL, "incom1.wav",	 4, 0),
	new Sound(NULL, "incom2.wav",	 5, 0),
	new Sound(NULL, "beep.wav",		 2, 0),
	new Sound(NULL, "boop.wav",		 7, 0),
};

/*loads sound sample*/
void  Sound::start()
{
	sound_on = true;

	if(install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT,".") != 0)
	{
		sound_on = false;
		return;
	}

	/*Load the sound sample*/
	sample = load_sample(filename.c_str());
}

void sound_startup(std::vector<Sound*> v)
{
	for(size_t i = 0; i < v.size(); i++)
		v[i]->start();
}