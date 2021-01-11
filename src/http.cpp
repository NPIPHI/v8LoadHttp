//
// Created by 16182 on 1/2/2021.
//

#include "http.h"

std::string Http::get(std::string url, int port, std::string subdomain) {
    Socket socket{url.c_str(), port};
    std::string msg = make_header(url.c_str(), port, subdomain.c_str());
    socket.write_bytes(msg.begin().base(), msg.end().base());
    InputStream is(&socket);
    char buff[1<<16];
    int len = is.read(buff, 1<<16);
    buff[len] = 0;
    auto content_length_ptr = strstr(buff, "Content-Length: ") + strlen("Content-Length: ");
    int content_length = atoi(content_length_ptr);
    auto content_begin = strstr(buff, "\r\n\r\n") + strlen("\r\n\r\n");
    std::string content = content_begin;
    content.reserve(content_length);
    while(content.length() < content_length){
        int len = is.read(buff, content_length - content.length());
        buff[len] = 0;
        content += buff;
    }
    return content;
}

std::string Http::make_header(const char * url, int port, const char * subdomain) {
    char buff[1<<16];
    sprintf(buff, "GET /%s HTTP/1.1\n"
                  "Host: %s:%d\n"
                  "Connection: close\n"
                  "Accept: */*\n\n",
                  subdomain, url, port);
    return buff;
}

