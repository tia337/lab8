#include <progbase-cpp/net.h>
#include <iostream>
#include <ctime>
#include <fstream>
#include <climits>
#include <cmath>
#include "http_server.h"
#include "request.h"
#include "singer.h"
#include <jansson.h>

using namespace progbase::net;
using namespace std;

const string filePath = "/home/ilya/projects/progbase2/labs/lab8/data/data.txt";

void http_server(void) {
  vector<Singer*> singers;
  singersInit(singers);
  const int serverPort = 3005;
  TcpListener listener;
  NetMessage message(10240);
  try {
    listener.bind(IpAddress("127.0.0.1", serverPort));
    listener.start();
    while (true) {
      cout << ">> Waiting for clients at " << serverPort << "..." << endl;
      TcpClient* client = listener.accept();
      client->receive(message);
      cout << ">> Received: " << endl << message.dataAsString() << endl;
      string data = message.dataAsString();
      string response = createResponse(data, singers);
      message.setDataString(response);
      client->send(message);
      cout << ">> Response sent." << endl;
      delete client;
    }
  } catch (NetException const& exc) {
    cerr << exc.what() << endl;
  }
  for (int i = 0; i < (int)singers.size(); i++) delete singers[i];
}

string createResponse(string message, vector<Singer*> singers) {
  Request request;
  string msg;
  string response =
      "HTTP/1.1 400 Bad Request\r\n"
      "Server: nginx/1.11.5\r\n"
      "Connection: close\r\n\r\n";
  if (request.parseString(message)) {
    bool failRequest = false;
    if (request.getURL() == "/")
      msg = serverInformation();
    else if (request.getURL() == "/favorites")
      msg = myFavouriteSingers(singers);
    else if (request.getURL().find("/favorites?") != string::npos)
      msg = keySingers(singers, request.getKey(), request.getValue());
    else if (request.getURL().find("/favorites/") != string::npos)
      msg = keySingers(singers, "id", request.getValue());
    else if (request.getURL() == "/file")
      msg = fileInformation();
    else if (request.getURL() == "/file/data")
      msg = fileNumber();
    else
      failRequest = true;
    if (msg == "No such singers") {
      response =
          "HTTP/1.1 404 Not Found\r\n"
          "Server: nginx/1.11.5\r\n"
          "Date: Sun, 07 May 201 23:28:13 GMT\r\n"
          "Connection: close\r\n\r\n";
    } else if (!failRequest) {
      response =
          "HTTP/1.1 200 OK\r\n"
          "Server: nginx/1.11.5\r\n"
          "Date: Sun, 07 May 2017 23:28:13 GMT\r\n"
          "Content-Type: application/json; charset=utf-8\r\n"
          "Content-Length: " +
          to_string(msg.size()) +
          "\r\n"
          "Connection: close\r\n\r\n" +
          msg;
    }
  }
  return response;
}

string serverInformation(void)
{
    json_t * json = json_object();
    json_object_set_new(json, "title", json_string( "LAB_8"));
    json_object_set_new(json, "developer",json_string( "tia"));
    time_t seconds = time(NULL);
    tm* timeinfo = localtime(&seconds);
    json_object_set_new(json, "time", json_string(asctime(timeinfo)));
    char * jsonString = json_dumps(json, JSON_INDENT(2) | JSON_PRESERVE_ORDER);
    string toReturn(jsonString);
    free(jsonString);
    json_decref(json);
    return toReturn;
}


string myFavouriteSingers(vector<Singer*> singers)
{
    json_t * array = json_array();
    for (int i = 0; i < (int)singers.size(); i++) {
        json_t * json = json_object();
        json_object_set_new(json, "Name", json_string(singers[i]->getName().c_str()));
        json_object_set_new(json, "genre", json_string(singers[i]->getGenre().c_str()));
        json_object_set_new(json, "song", json_string(singers[i]->getSong().c_str()));
        json_object_set_new(json, "duration", json_real(singers[i]->getDuration()));
        json_object_set_new(json, "id", json_integer(singers[i]->getId()));
        json_array_append(array, json);
        json_decref(json);
    }
    char * jsonString = json_dumps(array, JSON_INDENT(2) | JSON_PRESERVE_ORDER);
    string toReturn(jsonString);
    free(jsonString);
    json_decref(array);
    return toReturn;
}

string keySingers(vector<Singer *> singers, string key, string value)
{
    json_t * array = json_array();
    bool check = false;
    for (int i = 0; i < (int)singers.size(); i++) {
        if (singers[i]->getField(key) == value) {
            check = true;
            json_t * json = json_object();
            json_object_set_new(json, "Name", json_string(singers[i]->getName().c_str()));
            json_object_set_new(json, "genre", json_string(singers[i]->getGenre().c_str()));
            json_object_set_new(json, "song", json_string(singers[i]->getSong().c_str()));
            json_object_set_new(json, "duration", json_real(singers[i]->getDuration()));
            json_object_set_new(json, "id", json_integer(singers[i]->getId()));
            json_array_append(array, json);
            json_decref(json);
        }
    }
    if (check == false) return "No such singers";
    char * jsonString = json_dumps(array, JSON_INDENT(2) | JSON_PRESERVE_ORDER);
    string toReturn(jsonString);
    free(jsonString);
//    json_decref(array);
    return toReturn;
}

string fileInformation()
{
    string fileContent = readFile(filePath.c_str());
    if (fileContent == "Can't open file") {
        cerr << "Can't open file" << endl;
        return "Can't open file";
    }
    json_t * json = json_object();
    json_object_set_new(json, "filename", json_string( "data.txt"));
    json_object_set_new(json, "file size(byte)",json_integer(fileContent.size()));
    json_object_set_new(json, "file content",  json_string(fileContent.c_str()));
    char * jsonString = json_dumps(json, JSON_INDENT(2) | JSON_PRESERVE_ORDER);
    string toReturn(jsonString);
    free(jsonString);
    json_decref(json);
    return toReturn;
}

string fileNumber()
{
    string str = readFile(filePath.c_str());
    double min = INT_MAX, count = 0;
    double num = min;
    int index = str.find_first_of("1234567890");
    while (index != (int)string::npos)
    {
        bool dot = false;
        bool m = false;
        string buffer;
        while (isdigit(str[index]) || (str[index] == '.' && !dot) || (str[index] == '-' && !m)) {
            if (str[index] == '.' && !dot) dot = true;
            if (str[index] == '-' && !m) m = true;
            buffer += str[index];
            index++;
        }
        if (buffer.find_first_of("1234567890") != string::npos) num = stod(buffer);
        if (min-num > -0.0001) min = num;
        count++;
        index = str.find_first_of("-.1234567890",index+1);
    }
    json_t * json = json_object();
    json_object_set_new(json, "count of numbers",json_integer(count));
    json_object_set_new(json, "smallest number",json_real(min));
    char * jsonString = json_dumps(json, JSON_INDENT(2) | JSON_PRESERVE_ORDER);
    string toReturn(jsonString);
    free(jsonString);
    json_decref(json);
    return toReturn;
}

string readFile(const char * filePath) {
    string line;
    string toReturn;
    ifstream myfile (filePath);
    if (!myfile.is_open()){
        return "Can't open file";
    }
    while (! myfile.eof() ){
        getline (myfile,line);
        toReturn += line;
    }
    myfile.close();
    return toReturn;
}   