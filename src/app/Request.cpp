//
// Created by Hendrik Weiler on 02.06.21.
//

#include "Request.h"

QueryParamsMap Request::GetParams() {
    return QueryParams;
}

string Request::GetPostVar(string key) {
    char input[PostDataLen];

    mg_get_var(PostData, PostDataLen, key.c_str(), input, sizeof(input));
    return string{input};
}

void Request::SetPostDataLen(char *data, int len) {
    PostData = data;
    PostDataLen = len;
}

void Request::ParseQuery(string query) {
    bool inValue = false;
    bool inKey = true;
    string key{};
    string value{};
    for (auto i = query.begin(); i < query.end(); ++i) {
        char ch = *i;
        auto atEnd = i == query.end() - 1;
        if(ch == '&' || atEnd) {
            inKey = true;
            inValue = false;
            if(atEnd) value += ch;
            QueryParams.insert({key,value});
            key = "";
            value = "";
        } else if(ch == '=') {
            inValue = true;
            inKey = false;
        } else if(inValue) {
            value += ch;
        } else if(inKey) {
            key += ch;
        }
    }
}

string Request::GetParam(string key) {
    if(QueryParams.find(key) == QueryParams.end()) {
        return "";
    } else {
        return QueryParams.at(key);
    }
}
