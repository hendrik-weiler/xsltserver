//
// Created by Hendrik Weiler on 02.06.21.
//

#pragma once

#include <iostream>
#include <civetweb.h>
#include "../app/Routing.h"
#include "../app/Data.h"
#include "../app/Tools.h"
#include "../app/Cookie.h"

namespace page_login {

    using std::cout;
    using std::endl;

    void login(mg_connection * conn, Data& data, Request& request);

    void register_route();

}