//
// Created by 16182 on 1/2/2021.
//

#ifndef V8DEBUGGER_HTTP_H
#define V8DEBUGGER_HTTP_H

#include <string>
#include "AndroidWebsocket/Socket.h>
#include <AndroidWebsocket/InputStream>

class Http {
public:
    static std::string get(std::string url, int port, std::string subdomain);
private:
    static std::string make_header(const char * url, int port, const char * subdomain);
};

#endif //V8DEBUGGER_HTTP_H
