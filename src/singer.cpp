#include "singer.h"
using namespace std;
Singer::Singer() {}

Singer::Singer(string name, string genre, string song, float duration, int id)
{
    _name = name;
    _genre = genre;
    _song = song;
    _duration = duration;
    _id = id;
}

Singer::~Singer() {}

void Singer::setName(string name)
{
    _name = name;
}

void Singer::setGenre(string genre)
{
    _genre = genre;
}

void Singer::setSong(string song)
{
    _song = song;
}

void Singer::setDuration(float duration)
{
    _duration = duration;
}

void Singer::setId(int id)
{
    _id = id;
}

string Singer::getName()
{
    return _name;
}

string Singer::getGenre()
{
    return _genre;
}

string Singer::getSong()
{
    return _song;
}

float Singer::getDuration()
{
    return _duration;
}

int Singer::getId()
{
    return _id;
}

string Singer::getField(string field)
{
    if (field == "name") return _name;
    if (field == "genre") return _genre;
    if (field == "song") return _song;
    if (field == "duration") return to_string(_duration);
    if (field == "id") return to_string(_id);
    return NULL;
}

void singersInit(vector<Singer*> &singers)
{
    singers.push_back(new Singer("Scorpions", "Rock","Lorelie", 4.47, 1));
    singers.push_back(new Singer("Ozzy Osbourne", "rock","I just want you", 4.56, 2));
    singers.push_back(new Singer("Imagine Dragons", "indie rock","Shots", 2.46, 3));
    singers.push_back(new Singer("Tim McMorris", "pop","It`s a beautiul day", 1.59, 4));
    singers.push_back(new Singer("Jessie J", "pop","Flashlight", 3.03, 5));
    singers.push_back(new Singer("Alessia Cara", "Alternative R&B","Wild things", 3.08, 6));
    singers.push_back(new Singer("Carla`s Dreams", "pop","Unde", 4.13, 7));
    singers.push_back(new Singer("Cyrus Reynolds", "trance","Intriguing", 1.59, 8));
    singers.push_back(new Singer("Kygo & Ellie Goulding  ", "pop rock","First Time", 3.11, 9));
    singers.push_back(new Singer("DATA", "pop"," Dont Sing (Feat. Benny Sings)", 4.10, 10));
}
