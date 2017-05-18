/**
    @file
    @brief Data about favorite singers
*/
#ifndef SINGER_H
#define SINGER_H

#include <iostream>
#include <vector>
using namespace std;
/**
    @class Singer
    @brief defines a favorite singer
*/
class Singer
{
    string _name;
    string _genre;
    string _song;
    float _duration;
    int _id;
public:
 /**
    @brief default public constructor for Singer
 */
    Singer();
/**
    @brief public constructor for Singer that fill all fields in Singer
    @param name - unique name of singer
    @param genre - singer`s genre
    @param song - singer`s song
    @param duration - duration of singer`s song
    @param duration - unique singer`s id
*/
    Singer(
        string name,
        string genre,
        string song,
        float duration,
        int id
        );
 /**
    @brief default public destructor for Singer
*/
    ~Singer();
 /** 
    @brief sets name of singer 
    @param name name of singer 
*/
    void setName(string name);
/** 
    @brief sets genre of singer`s song 
    @param genre genre of singer`s song 
*/
    void setGenre(string genre);
/** 
    @brief sets name of singer`s song 
    @param song song of singer `s song
*/
    void setSong(string song);
 /** 
    @brief sets duration of singer`s song  
    @param duration duration of singer`s song 
*/    
    void setDuration(float duration);
/** 
    @brief sets id of singer`s song 
    @param id id of singer`s song  
*/
    void setId(int id);
/**
    @brief get name of singer
    @return string that represents name of singer
*/
    string getName(void);
/**
    @brief get genre of singer`s song
    @return string that represents genre of singer`s song
*/
    string getGenre(void);
 /**
    @brief get song of singer
    @return string that represents singer`s song
*/    
    string getSong(void);
/**
    @brief get duration of singer`s song
    @return string that represents duration of singer`s song
*/
    float getDuration(void);
/**
    @brief get singer`s id
    @return string that represents unique singer`s id
*/
    int getId(void);
/**
    @brief get value that contain specified filed of Singer
    @param field - string that defines field which value returns
    @return string that represents value at specified field
*/
    string getField(string field);
};
/**
    @brief sets some default Singer objects 
*/
void singersInit(vector<Singer*> &singers);

#endif // SINGER_H
