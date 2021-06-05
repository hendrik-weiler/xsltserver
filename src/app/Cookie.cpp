//
// Created by Hendrik Weiler on 01.06.21.
//

#include "Cookie.h"

std::string rfc1123_datetime( time_t time )
{
    struct tm * timeinfo;
    char buffer [80];

    timeinfo = gmtime ( &time );
    strftime (buffer,80,"%a, %d %b %Y %H:%M:%S GMT",timeinfo);

    return buffer;
}

CookieList Cookie::Cookies {};

void Cookie::Set(mg_connection * conn, string key, string value) {
    time_t timer;
    time(&timer);
    struct tm* tm = localtime(&timer);
    tm->tm_year += 1;
    time_t next = mktime(tm);
    Set(conn, key,value, next);
}

void Cookie::WriteOut(mg_connection * conn) {
    mg_response_header_start(conn, 200);
    char * ct = (char *)"text/html";
    mg_response_header_add(conn, "Content-Type", ct, strlen(ct));
    for(auto cookie : Cookies) {
        mg_response_header_add(conn, "Set-Cookie", cookie.c_str(), cookie.size());
    }
    mg_response_header_send(conn);
}

void Cookie::Set(mg_connection *conn, string key, string value, int duration) {
    string dur = std::to_string(duration);
    string length {string{"expires="} + rfc1123_datetime(duration)};
    string definition {key + "=" + value};
    string combined {definition + ";Path=/;" + length};
    Cookies.push_back(combined);
}

void Cookie::Delete(mg_connection *conn, string key) {
    string value = Get(conn, key, 1024);
    Set(conn, key, value, 0);
}

string Cookie::Get(mg_connection * conn, string key, int lengthOfValue) {
    const char *cookie = mg_get_header(conn, "Cookie");
    char * value = (char *)calloc(lengthOfValue, sizeof(char));

    mg_get_cookie(cookie, key.c_str(), value, sizeof(value));
    return string{value};
}
