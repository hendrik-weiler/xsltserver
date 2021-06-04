//
// Created by Hendrik Weiler on 01.06.21.
//

#pragma once

#include <string>
#include <civetweb.h>
#include <ctime>
#include <vector>
#include <cstring>

using std::string;
using std::vector;
using std::strlen;

typedef vector<string> CookieList;

class Cookie {
public:
    static CookieList Cookies;
    static void Set(mg_connection * conn, string key, string value);
    static void Set(mg_connection * conn, string key, string value, int duration);
    static string Get(mg_connection * conn, string key, int lengthOfValue);
    static void Delete(mg_connection * conn, string key);
    static void WriteOut(mg_connection * conn);
};