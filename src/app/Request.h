//
// Created by Hendrik Weiler on 02.06.21.
//

#pragma once

#include <string>
#include <unordered_map>
#include <civetweb.h>

using std::string;
using std::unordered_map;

typedef unordered_map<string, string> QueryParamsMap;

class Request {
private:
    QueryParamsMap QueryParams {};
    char *PostData = (char*)"";
    int PostDataLen = 0;
public:
    mg_connection * Conn;
    string RedirectPath {};
    void ParseQuery(string value);
    string GetParam(string key);
    string GetPostVar(string key);
    void SetPostDataLen(char * data, int len);
    QueryParamsMap GetParams();
};