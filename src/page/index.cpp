//
// Created by Hendrik Weiler on 01.06.21.
//

#include "index.h"

void page_index::index(mg_connection *conn, Data& data, Request& request) {
    const struct mg_request_info *ri = mg_get_request_info(conn);
}

void page_index::register_route() {
    Routing::AddRoute("/index", index);
}
