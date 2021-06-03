//
// Created by Hendrik Weiler on 02.06.21.
//

#pragma once

#include <iostream>
#include <civetweb.h>
#include <fstream>
#include <streambuf>

#include "../app/Routing.h"
#include "../app/Data.h"
#include "../app/Tools.h"
#include "../app/Cookie.h"
#include "../app/Base64.h"

namespace page_todo {

    using std::cout;
    using std::endl;

    void todo(mg_connection * conn, Data& data, Request& request);

    void register_route();

}