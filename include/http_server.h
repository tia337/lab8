/** @file
@brief - defines Server
*/
#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include <iostream>
#include <vector>
#include <singer.h>
using namespace std;
/**
@brief - HTTP server
*/
void http_server(void);
/**
@brief - HTTP server
@param message data from client
@param singers
@return string response from server
*/
string createResponse(string message, vector<Singer *> singers);
/**
@brief creates information about server
@return response to "/"
*/
string serverInformation(void);
/**
@brief creates information about favorite singers
@param singers my favorite singers
@return response on "/favorites"
*/
string myFavouriteSingers(vector<Singer *> singers);
/**
@brief creates information about some singers, by field key = value
@param singers my favorite singers
@param key name of field
@param value value of field
@return response on /favorites?somefield=value and /favorites/id
*/
string keySingers(vector<Singer *> singers, string key, string value);
/**
@brief creates information about file "data.txt"
@return response to /file
*/
string fileInformation(void);
/**
@brief creates information about numbers in file "data.txt"
@return response to /file/data
*/
string fileNumber(void);
/**
@brief reads file
@param filePath path to the file and its name
@return information from file
*/
string readFile(const char *filePath);

#endif // HTTP_SERVER_H
