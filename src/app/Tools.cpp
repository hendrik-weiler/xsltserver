//
// Created by Hendrik Weiler on 31.05.21.
//

#include <regex>
#include <sys/stat.h>
#include "Tools.h"

bool IsAlphaNumeric(string input) {
    std::regex regex ("[a-zA-Z0-9]");
    return std::regex_match (input,regex);
}

bool Tools::IsPost(const char * method) {
    return strcmp(method,"POST") == 0;
}

bool Tools::IsDirectory(string path) {
    struct stat s;
    if( stat(path.c_str(),&s) == 0 )
    {
        if( s.st_mode & S_IFDIR )
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

string Tools::ResolvePath(string path) {
    string newPath {};
    for(auto i = path.begin(); i != path.end(); ++i) {
        char ch = *i;
        if(ch == '.' && i != path.end() - 1) {
            if(*(i + 1) != '.') {
                newPath += ch;
            }
        } else {
            newPath += ch;
        }
    }
    return newPath;
}

ReqPath Tools::GetPathFromRequestUri(string requesturi) {

    requesturi = ResolvePath(requesturi);

    string path {};
    string ext {};
    ReqPath rp;
    rp.afterPath = "";
    bool inDot = false;
    bool afterExt = false;
    for (int i = 0; i < requesturi.size(); ++i) {
        if(afterExt) {
            rp.afterPath += requesturi[i];
        } else if(inDot) {
            if(!IsAlphaNumeric(string{requesturi[i]})) {
                afterExt = true;
            }
            ext += requesturi[i];
            if(ext == "xslhtml") {
                rp.path = path;
            }
        } else if(requesturi[i] == '.') {
            inDot = true;
        } else {
            path += requesturi[i];
        }
    }

    return rp;
}
