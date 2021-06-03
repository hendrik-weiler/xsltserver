//
// Created by Hendrik Weiler on 02.06.21.
//

#include "todo.h"

void page_todo::todo(mg_connection *conn, Data &data, Request &request) {

    const struct mg_request_info *ri = mg_get_request_info(conn);

    string entriesLenGlobal = Cookie::Get(conn, "len", 10);

    string removeAllParam = request.GetParam("removeAll");
    if(removeAllParam.size() > 0) {
        Cookie::Set(conn, "len", "0");

        cout << "Remove all entries" << endl;
        request.RedirectPath = "todo.xslhtml";
        return;
    }

    string removeParam = request.GetParam("remove");
    if(removeParam.size() > 0) {

        int removeIndex = atoi(removeParam.c_str());
        int len = atoi(entriesLenGlobal.c_str());
        vector<string> entries {};
        for(int i = 0; i < len; ++i) {
            if(i != removeIndex) {
                string text = Cookie::Get(conn, string{"entry" + std::to_string(i)}, 120);
                entries.push_back(text);
            }
        }
        for(int i = 0; i < entries.size(); ++i) {
            Cookie::Set(conn, string{"entry" + std::to_string(i)}, entries.at(i));
        }
        Cookie::Set(conn, "len", std::to_string(entries.size()));

        cout << "Remove index " << removeIndex << endl;
        request.RedirectPath = "todo.xslhtml";
        return;
    }

    if(Tools::IsPost(ri->request_method)
        && request.GetPostVar("addButton").size() > 0) {

        string text = request.GetPostVar("text");

        cout << "Text=" << text << endl;

        if(text.empty()) {
            request.RedirectPath = "todo.xslhtml?error=1";
        } else {

            string entriesLen = Cookie::Get(conn, "len", 10);
            int len;
            if(entriesLen.empty()) {
                len = 1;
            } else {
                len = atoi(entriesLen.c_str()) + 1;
            }

            Cookie::Set(conn, string{"entry" + std::to_string(len-1)}, text);
            Cookie::Set(conn, "len", std::to_string(len));
            entriesLenGlobal = std::to_string(len);
            request.RedirectPath = "todo.xslhtml";
        }

    }


    int len = 0;
    if(entriesLenGlobal.size() > 0) len = atoi(entriesLenGlobal.c_str());

    vector<Data> entries {};
    for(int i = 0; i < len; ++i) {
        string text = Cookie::Get(conn, string{"entry" + std::to_string(i)}, 120);
        Data d{};
        d.Set("Text", text);
        entries.push_back(d);
    }
    data.SetList("Entry", entries);

}

void page_todo::register_route() {
    Routing::AddRoute("/todo", todo);
}
