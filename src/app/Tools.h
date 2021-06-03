//
// Created by Hendrik Weiler on 31.05.21.
//

#pragma once

#include <string>
#include <civetweb.h>
#include <limits>

using std::string;

typedef struct {
    string path;
    string afterPath;
} ReqPath;

class Tools {
public:
    static ReqPath GetPathFromRequestUri(string requesturi);
    static string ResolvePath(string path);
    static bool IsDirectory(string path);
    static bool IsPost(const char * method);
};