//
// Created by Hendrik Weiler on 31.05.21.
//

#include "XSLTransformer.h"

string XSLTransformer::Transform(string xml, string stylesheetxml) {

    const char *params[16 + 1];
    int nbparams = 0;
    xsltStylesheetPtr cur = NULL;
    xmlDocPtr doc, style, res;

    xmlSubstituteEntitiesDefault(1);
    xmlLoadExtDtdDefaultValue = 1;

    params[nbparams] = NULL;

    doc = xmlParseMemory(xml.c_str(), xml.size());
    style = xmlParseMemory(stylesheetxml.c_str(), stylesheetxml.size());

    cur = xsltParseStylesheetDoc(style);

    res = xsltApplyStylesheet(cur, doc, params);

    xmlChar * output = nullptr;
    int length = 0;

    xsltSaveResultToString(&output, &length, res, cur);

    xsltFreeStylesheet(cur);
    xmlFreeDoc(res);
    xmlFreeDoc(doc);

    xsltCleanupGlobals();
    xmlCleanupParser();

    string soutput {};

    soutput.append((const char *)output, length);
    xmlFree(output);

    return soutput;
}
