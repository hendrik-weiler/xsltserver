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
    typedef unordered_map<string,bool> CDataMap;

private:
    DataContainer data {};
    ListsMap lists {};
    CDataMap cData;
    void BuildList(DataList list, xmlNodePtr parentNode, string nodeName,xmlDocPtr doc);
public:
    void Set(string key, string value);
    void Set(string key, string value, bool cdata);
    void SetList(string key, DataList value);
    DataContainer getData();
    ListsMap getLists();
    CDataMap getCDataMap();
    string ToXML();
    static string EmptyXML();
};