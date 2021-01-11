//
// Created by 16182 on 1/1/2021.
//

#include "../include/v8LoadHttp/LoadHttp.h"
#include "http.h"
#include <regex>
#include <utility>

static void set_runtime_window(v8Runtime *runtime, std::string url, int port, std::string subdomain) {
    char script_src[1024];
    sprintf(script_src, "if(!globalThis.window) window = globalThis;"
                        "if(!window.location) window.location = {};"
                        "window.location.protocol='http:';"
                        "window.location.host='%s:%d';"
                        "window.location.pathname='/%s';", url.c_str(), port, subdomain.c_str());
    runtime->add_script(script_src, "");
}

void LiveServer::load_http(v8Runtime * runtime, std::string url, int port, std::string subdomain) {
    static std::regex script_regex(R"(< *script *src *= *\"(.+)\"> *< */ *script *>)");
    static std::regex inline_script_regex(R"(< *script *(?:type *= *\".+\" *)>((.*\n)+)< */ *script *>)");
    runtime->reset_global_context();
    set_runtime_window(runtime, url, port, subdomain);

    int inline_index = 0;
    auto index = Http::get(url, port, "");
    std::vector<std::pair<std::string, std::string>> scripts;
    for(auto i = std::sregex_iterator(index.begin(), index.end(), script_regex); i != std::sregex_iterator(); i++){
        auto match = *i;
        auto file = (match.begin()+1)->str();
        auto contents = Http::get(url, port, file);
        scripts.emplace_back(file, contents);
    }
    for(auto i = std::sregex_iterator(index.begin(), index.end(), inline_script_regex); i != std::sregex_iterator(); i++){
        auto match = *i;
        auto file = "__inline__" + std::to_string(inline_index++);
        auto contents = (match.begin() + 1)->str();
        scripts.emplace_back(file, contents);
    }
    for(auto & [file, script]: scripts){
        runtime->add_script(script, file);
    }
}
