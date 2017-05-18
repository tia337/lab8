/** 
@file
@class - describes a Request
*/

#ifndef REQUEST_H
#define REQUEST_H

#include <iostream>
using namespace std;
/**
@class Request
@brief defines a client request
*/
class Request
{
    string _command;
    string _URL;
    string _key;
    string _value;
public:
    /**
        @brief default public constructor for Request
    */  
    Request();
    /**
        @brief default public destructor for Request
    */
    ~Request();
    /** 
        @brief simple constructor 
    */ 
    bool parseString(string message);
    /**
        @brief set method from client Request
        @param command command of Request 
    */
    void setCommand(string command);
    /** 
        @brief sets URL from  client Request
        @param URL URL of client Request 
    */ 
    void setURL(string URL);
    /** 
        @brief sets key from client Request 
        @param key key of client Request 
    */ 
    void setKey(string key);
    /** 
        @brief sets value from client Request 
        @param value value of client Request
    */ 
    void setValue(string value);
    /**
        @brief gets command from client Request
        @return string that defines command of Request
    */
    string getCommand(void);
    /**
        @brief gets URL from client Request
        @return string that defines URL of Request
    */
    string getURL(void);
    /**
        @brief gets specified key from client Request
        @return string that defines specified key of Request
    */
    string getKey(void);
    /**
        @brief gets specified value from client Request
        @return string that defines specified value of Request
    */
    string getValue(void);
};

#endif // REQUEST_H
