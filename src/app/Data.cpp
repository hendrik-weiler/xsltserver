//
// Created by Hendrik Weiler on 31.05.21.
//

#include "Data.h"

void Data::Set(string key, string value) {
    data.insert({key,value});
}

void Data::SetList(string key, DataList value) {
    lists.insert({key, value});
    data.insert({key,":list"});
}

DataContainer Data::getData() {
    return this->data;
}

Data::ListsMap Data::getLists() {
    return this->lists;
}

void Data::BuildList(Data::DataList list, xmlNodePtr parentNode, string nodeName) {
    for(auto listEntry : list) {
        xmlNodePtr listNode = xmlNewNode(NULL, BAD_CAST nodeName.c_str());
        for(auto dataEntry : listEntry.getData()) {
            ListsMap listsMap = listEntry.getLists();
            if(listsMap.find(dataEntry.first) == listsMap.end()) {
                xmlNewChild(listNode, NULL, BAD_CAST dataEntry.first.c_str(), BAD_CAST dataEntry.second.c_str());
            } else {
                this->BuildList(listsMap.at(dataEntry.first), listNode, dataEntry.first);
            }
        }
        xmlAddChild(parentNode, listNode);
    }
}

string Data::EmptyXML() {
    Data d{};
    return d.ToXML();
}

string Data::ToXML() {
    xmlNodePtr n;
    xmlDocPtr doc;
    xmlChar *xmlbuff;
    int buffersize;


    doc = xmlNewDoc(BAD_CAST "1.0");
    n = xmlNewNode(NULL, BAD_CAST "Data");

    for(auto entry : data) {
        if(lists.find(entry.first) == lists.end()) {
            xmlNewChild(n, NULL, BAD_CAST entry.first.c_str(), BAD_CAST entry.second.c_str());
        } else {
            this->BuildList(lists.at(entry.first), n, entry.first);
        }
    }
    xmlDocSetRootElement(doc, n);

    xmlDocDumpFormatMemory(doc, &xmlbuff, &buffersize, 1);

    string output{(char *)xmlbuff};

    xmlFree(xmlbuff);
    xmlFreeDoc(doc);

    return output;
}
