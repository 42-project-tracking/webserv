#ifndef CGI_HPP
#define CGI_HPP

#include <string>
#include <map>
#include "LocationInfo.hpp"

class CGI
{
    public:

        std::string                             get_cmd();
        void                                    set_arguments(const std::string& args);
        std::string                             execute_cgi();

        CGI(const std::map<std::string, std::string>& env, const std::string& body, LocationInfo* location);
        ~CGI();

    private:

        std::string                             _cmd;
        char**                                  _env;
        LocationInfo*                           _location;
        char**                                  _arguments;
        std::string                             _request_body;
        std::string                             _response_body;
        std::map <std::string, std::string>     _environment_map;
};

#endif