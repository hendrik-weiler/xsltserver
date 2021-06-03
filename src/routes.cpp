//
// Created by Hendrik Weiler on 01.06.21.
//

#include "page/index.h"
#include "page/app/index.h"
#include "page/todo.h"
#include "page/login.h"

void registerAllRoutes() {
    page_index::register_route();
    page_todo::register_route();
    page_login::register_route();
    page_app_index::register_route();
}