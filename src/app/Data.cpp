//
// Created by Hendrik Weiler on 31.05.21.
//

#include "Data.h"

void Data::Set(string key, string value) {
    Set(key, value, false);
}

void Data::Set(string key, string value, bool cdata) {
    data.insert({key,value});
    cData.insert({key, cdata});
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

Data::CDataMap Data::getCDataMap() {
    return this->cData;
}

void Data::BuildList(Data::DataList list, xmlNodePtr parentNode, string nodeName, xmlDocPtr doc) {
    for(auto listEntry : list) {
        xmlNodePtr listNode = xmlNewNode(NULL, BAD_CAST nodeName.c_str());
        for(auto dataEntry : listEntry.getData()) {
            ListsMap listsMap = listEntry.getLists();
            if(listsMap.find(dataEntry.first) == listsMap.end()) {
                CDataMap cDataMap = listEntry.getCDataMap();
                if(cDataMap.find(dataEntry.first) == cDataMap.end()) {
                    xmlNewChild(listNode, NULL, BAD_CAST dataEntry.first.c_str(), BAD_CAST dataEntry.second.c_str());
                } else {
                    // only add cdata if its activated
                    if(cDataMap.at(dataEntry.first)) {
                        xmlNodePtr node = xmlNewNode(NULL, (xmlChar *)dataEntry.first.c_str());
                        xmlNodePtr cdataPtr = xmlNewCDataBlock(doc, (xmlChar *)dataEntry.second.c_str(), dataEntry.second.size());
                        xmlAddChild( node, cdataPtr );
                        xmlAddChild(listNode, node);
                    } else {
                        xmlNewChild(listNode, NULL, BAD_CAST dataEntry.first.c_str(), BAD_CAST dataEntry.second.c_str());
                    }
                }
            } else {
                this->BuildList(listsMap.at(dataEntry.first), listNode, dataEntry.first, doc);
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
            if(cData.find(entry.first) == cData.end()) {
                xmlNewChild(n, NULL, BAD_CAST entry.first.c_str(), BAD_CAST entry.second.c_str());
            } else {
                // only add cdata if its activated
                if(cData.at(entry.first)) {
                    xmlNodePtr node = xmlNewNode(NULL, (xmlChar *) entry.first.c_str());
                    xmlNodePtr cdataPtr = xmlNewCDataBlock(doc, (xmlChar *) entry.second.c_str(), entry.second.size());
                    xmlAddChild(node, cdataPtr);
                    xmlAddChild(n, node);
                } else {
                    xmlNewChild(n, NULL, BAD_CAST entry.first.c_str(), BAD_CAST entry.second.c_str());
                }
            }
        } else {
            this->BuildList(lists.at(entry.first), n, entry.first, doc);
        }
    }
    xmlDocSetRootElement(doc, n);

    xmlDocDumpFormatMemory(doc, &xmlbuff, &buffersize, 1);

    string output{(char *)xmlbuff};

    xmlFree(xmlbuff);
    xmlFreeDoc(doc);

    return output;
}
