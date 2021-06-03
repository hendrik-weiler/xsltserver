//
// Created by Hendrik Weiler on 01.06.21.
//

#pragma once

#include <unordered_map>
#include <civetweb.h>
#include <string>
#include "Data.h"
#include "Request.h"

using std::unordered_map;
using std::string;
using std::function;

typedef unordered_map<string,function<void(mg_connection*,Data&,Request&)>> RoutingMap;

class Routing {
public:
    static RoutingMap Routes;
    static void AddRoute(string key, function<void(mg_connection*,Data&,Request&)> function);
    static bool Call(string key, mg_connection * conn, Data& data, Request& request);

    void AddRoute(string key, function<string(mg_connection *, Data &,Request&)> function);
};