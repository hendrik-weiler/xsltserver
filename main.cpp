#include <iostream>
#include <civetweb.h>
#include <libc.h>
#include <string>
#include <fstream>
#include <streambuf>

#include "src/app/XSLTransformer.h"
#include "src/app/Tools.h"
#include "src/app/Data.h"
#include "src/app/Cookie.h"
#include "src/app/Routing.h"
#include "src/routes.h"
#include "src/app/Request.h"

using std::string;
using std::cout;
using std::endl;

int allHandler(struct mg_connection *conn, void *ignored)
{
    const struct mg_request_info *ri = mg_get_request_info(conn);

    string path = Tools::ResolvePath("www" + string{ri->request_uri});
    std::ifstream t(path);
    if(t.good() && !Tools::IsDirectory(path)) {
        mg_send_file(conn, path.c_str());

        return 200;
    } else {

        // check for /index.xsl
        char lastCharOfPath = *(path.end());
        if(lastCharOfPath!='/') path += '/';
        path += "index.xsl";

        std::ifstream t2(path);
        if(t2.good()) {
            string redirectPath {};
            for(int i = 4; i < path.size(); ++i) {
                redirectPath += path[i];
            }
            redirectPath += "html";
            mg_send_http_redirect(conn,redirectPath.c_str(),302);

            return 200;
        } else {
            string msg{"404 File not found."};
            size_t len = msg.size();

            mg_send_http_ok(conn, "text/html", len);

            mg_write(conn, msg.c_str(), len);

            return 404;
        }
    }
}

int xslHandler(struct mg_connection *conn, void *ignored)
{
    string msg{"404 File not found."};
    size_t len = msg.size();

    mg_send_http_ok(conn, "text/html", len);

    mg_write(conn, msg.c_str(), len);

    return 404;
}

int handler(struct mg_connection *conn, void *ignored)
{
    const struct mg_request_info *ri = mg_get_request_info(conn);

    string query = "";
    if(ri->query_string != nullptr) {
        query = ri->query_string;
    }

    Request request {};
    request.ParseQuery(query);
    request.Conn = conn;

    //int size = std::numeric_limits<int>::max();
    char post_data[1024];
    int post_len = mg_read(conn, post_data, sizeof(post_data));
    request.SetPostDataLen(post_data, post_len);

    ReqPath rp = Tools::GetPathFromRequestUri(string{ri->request_uri});

    // open file
    std::ifstream t("www/" + rp.path + ".xsl");
    if(t.good()) {
        // read file content
        std::string stylexml((std::istreambuf_iterator<char>(t)),
                             std::istreambuf_iterator<char>());

        Data data {};

        vector<Data> list {};
        for(auto entry : request.GetParams()) {
            Data d {};
            d.Set(entry.first, entry.second);
            list.push_back(d);
        }
        data.SetList("QueryParams", list);

        Cookie::Cookies.clear();

        if(!Routing::Call(rp.path, conn, data, request)) {
            cout << "Couldnt call to function " << rp.path << endl;

            string msg{"404 File not found."};
            size_t len = msg.size();

            mg_send_http_ok(conn, "text/html", len);

            mg_write(conn, msg.c_str(), len);

            return 404;
        }

        if(request.RedirectPath.size() > 0) {

            Cookie::WriteOut(conn);

            string refresh {"<meta http-equiv=\"refresh\" content=\"0; URL=" + request.RedirectPath + "\">"};

            mg_write(conn, refresh.c_str(), refresh.size());

            return 200;
        }

        // transform
        string transformed = XSLTransformer::Transform(data.ToXML(), stylexml);

        string msg = transformed;
        size_t len = transformed.size();

        //mg_send_http_ok(conn, "text/html", len);

        Cookie::WriteOut(conn);

        mg_write(conn, msg.c_str(), len);

        return 200;
    } else {
        cout << "File " << rp.path + ".xsl Status=" << (t.good() ? "OK" : "NOT FOUND") << endl;

        string msg{"404 File not found."};
        size_t len = msg.size();

        mg_send_http_ok(conn, "text/html", len);

        mg_write(conn, msg.c_str(), len);

        return 404;
    }
}

int log_message(const struct mg_connection *conn, const char *message)
{
    puts(message);
    return 1;
}

int main() {

    /* Server context handle */
    struct mg_context *ctx;
    struct mg_callbacks callbacks;

    memset(&callbacks, 0, sizeof(callbacks));

    callbacks.log_message = log_message;

    /* Initialize the library */
    mg_init_library(0);

    const char *options[] = {
            "document_root",
            "./www",
            "listening_ports",
            "8000",
            "enable_directory_listing",
            "no",
            NULL
    };

    /* Start the server */
    ctx = mg_start(&callbacks, 0, options);

    /* Add some handler */
    mg_set_request_handler(ctx, "/**.xslhtml$", handler, 0);

    mg_set_request_handler(ctx, "/**.xsl$", xslHandler, 0);

    mg_set_request_handler(ctx, "**", allHandler, 0);

    registerAllRoutes();

    while(true) {
        sleep(1);
        std::string str;
        std::getline(std::cin, str);
        if(str == "exit") {
            /* Stop the server */
            mg_stop(ctx);

            /* Un-initialize the library */
            mg_exit_library();

            exit(0);
        }
    }

    /* Stop the server */
    mg_stop(ctx);

    /* Un-initialize the library */
    mg_exit_library();

    return 0;
}
