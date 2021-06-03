//
// Created by Hendrik Weiler on 01.06.21.
//

#include "index.h"

void page_app_index::index(mg_connection *conn, Data &data, Request& request) {
    const struct mg_request_info *ri = mg_get_request_info(conn);

    string session = Cookie::Get(conn, "session", 20);
    if(session.size() == 0) {
        request.RedirectPath = "/login.xslhtml";
        return;
    }

    if(Tools::IsPost(ri->request_method)
        && request.GetPostVar("doLogout").size() > 0) {
        Cookie::Delete(conn, "session");
        request.RedirectPath = "/login.xslhtml";
    }

    if(request.GetParam("page") == "table") {
        vector<Data> list {};
        vector<string> names = {"Hans","Paul","Peter","Nadine","Rolf","Natascha"};
        vector<string> age = {"20","23","44","24","21","44"};
        for (int i = 0; i < 6; ++i) {
            Data d{};
            d.Set("Name", names.at(i));
            d.Set("Age", age.at(i));
            list.push_back(d);
        }
        data.SetList("Person", list);
    }
}

void page_app_index::register_route() {
    Routing::AddRoute("/app/index", index);
}
