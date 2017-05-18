/** 
@file
@class - describes a htttpServer
*/
#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include <iostream>
#include <vector>
#include <singer.h>
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
std::string createResponse(std::string message, std::vector<Singer *> singers);
/**
@brief creates information about server
@return response to "/"
*/
std::string serverInformation(void);
/**
@brief creates information about favorite singers
@param singers my favorite singers
@return response on "/favorites"
*/
std::string myFavouriteSingers(std::vector<Singer *> singers);
/**
@brief creates information about some singers, by field key = value
@param singers my favorite singers
@param key name of field
@param value value of field
@return response on /favorites?somefield=value and /favorites/id
*/
std::string keySingers(std::vector<Singer *> singers, std::string key, std::string value);
/**
@brief creates information about file "data.txt"
@return response to /file
*/
std::string fileInformation(void);
/**
@brief creates information about numbers in file "data.txt"
@return response to /file/data
*/
std::string fileNumber(void);
/**
@brief reads file
@param filePath path to the file and its name
@return information from file
*/
std::string readFile(const char *filePath);

#endif // HTTP_SERVER_H
