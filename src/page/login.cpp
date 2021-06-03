//
// Created by Hendrik Weiler on 02.06.21.
//

#include "login.h"

void page_login::login(mg_connection *conn, Data& data, Request& request) {
    const struct mg_request_info *ri = mg_get_request_info(conn);

    if(Tools::IsPost(ri->request_method)) {
        string user = request.GetPostVar("user");
        string pwd = request.GetPostVar("password");
        cout << "user=" << user << endl;
        cout << "pwd=" << pwd << endl;
        if(user=="test" && pwd == "abc123") {
            Cookie::Set(conn, "session", "true");
            request.RedirectPath = "app";
        } else {
            request.RedirectPath = "login.xslhtml?error=true";
        }
    }

    string session = Cookie::Get(conn, "session", 20);
    if(session != "") {
        request.RedirectPath = "app";
    }

}

void page_login::register_route() {
    Routing::AddRoute("/login", login);
}