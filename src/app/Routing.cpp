//
// Created by Hendrik Weiler on 01.06.21.
//

#include "Routing.h"

RoutingMap Routing::Routes {};

void Routing::AddRoute(string key, function<void(mg_connection*,Data&,Request&)> function) {
    Routes.insert({key, function});
}

bool Routing::Call(string key, mg_connection * conn, Data& data, Request& request) {
    if(Routes.find(key) == Routes.end()) {
        return false;
    } else {
        Routes.at(key)(conn, data, request);
        return true;
    }
}
