//
// Created by 16182 on 1/1/2021.
//

#ifndef V8DEBUGGER_LOADHTTP_H
#define V8DEBUGGER_LOADHTTP_H

#include <v8Core/v8Runtime.h>
#include <string>

namespace LoadHttp {
    /*
     * loads javascript files from a url
     * expects a .html file with <script> tags that define which scripts to load
     * requires locks to be set
     */
    static void load_http(v8Runtime * runtime, std::string url, int port, std::string subdomain);
};


#endif //V8DEBUGGER_LOADHTTP_H
