#include "sound.hpp"
#include "alg_data.h"
#include "graphics.hpp"
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

void Sound::shutdown()
{
	if(!sound_on)
		return;

	/*if sample is not null*/
	if(!sample)
	{
		destroy_sample(sample);
		sample = nullptr;
	}
}

void Sound::play()
{
	if(!sound_on)
		return;

	if(timeleft != 0)
		return;

	timeleft = runtime;

	play_sample(sample,255,128,1000,0);
}

void Sound::update()
{
	if(timeleft > 0)
		timeleft-= 1;
}



/*
	Function loads and starts samples in a vector
	containing Sound objects(Pointers to Sound objects)
	the functionality that actually loads the sample is
	defined in the sound class	
*/
void sound_startup(std::vector<Sound*> v)
{
	for(size_t i = 0; i < v.size(); i++)
		v[i]->start();
}

void sound_shutdown(std::vector<Sound*> v)
{
	for(size_t i = 0; i < v.size(); i++)
		v[i]->shutdown();
}

void sound_play(std::vector<Sound*> v,int sample_no)
{
	v[sample_no]->play();
}

void sound_update(std::vector<Sound*> v)
{
	for(size_t i = 0; i < v.size(); i++)
		v[i]->update();
}


void play_midi(int midi_no, int repeat)
{
	
	DATAFILE* datafile = Graphics::instance().get_datafile();
	if(!sample_list[0]->is_sound_on())
		return;

	/*switch(midi_no)
	{
		case SND_ELITE_THEME:
			play_midi (datafile[THEME].dat, repeat);
			break;
		
		case SND_BLUE_DANUBE:
			play_midi (datafile[DANUBE].dat, repeat);
			break;
	}*/
}

void stop_midi()
{
	if(sample_list[0]->is_sound_on())
		play_midi(nullptr,0);
}