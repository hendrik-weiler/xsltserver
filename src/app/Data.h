//
// Created by Hendrik Weiler on 31.05.21.
//

#pragma once

#include <unordered_map>
#include <string>
#include <libxml/parser.h>
#include <vector>
#include <iostream>

using std::unordered_map;
using std::string;
using std::vector;
using std::cout;
using std::endl;

typedef unordered_map<string, string> DataContainer;

class Data {
    typedef vector<Data> DataList;
    typedef unordered_map<string, DataList> ListsMap;

private:
    DataContainer data {};
    ListsMap lists {};
    void BuildList(DataList list, xmlNodePtr parentNode, string nodeName);
public:
    void Set(string key, string value);
    void SetList(string key, DataList value);
    DataContainer getData();
    ListsMap getLists();
    string ToXML();
    static string EmptyXML();
};