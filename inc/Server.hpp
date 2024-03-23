#ifndef SERVER_HPP
#define SERVER_HPP

#include <ostream>
#include <string> 
#include <vector>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include "Node.hpp"
#include "Request.hpp"
#include "LocationInfo.hpp"

class LocationInfo;
class Director;
//purpose:	Data class for the parsed values (from the config file)
//			It is used fjor the initialization and the running of the servers.

class Server : public Node
{
	public:

											Server();
											~Server();
											Server(const Server& rhs);
											Server(int tfd, struct sockaddr_storage ss, size_t addr_len);
		Server&								operator=(const Server& rhs);

		// getters and setters
		int									get_port() const;
		void								set_port(int prt);
		int									get_sock_fd() const;
		void								set_sock_fd(int sfd);
		std::vector <std::string>			get_server_name() const;
		void								set_server_name(const std::vector <std::string>& tserver_name);
		bool								get_auto_index() const;
		void								set_auto_index(bool b);
		std::string							get_root() const;
		void								set_root(const std::string& rt);
		std::string							get_error_log() const;
		void								set_error_log(const std::string& rt);
		std::string							get_access_log() const;
		void								set_access_log(const std::string& rt);
		struct in_addr						get_host_address() const;
		void								set_host_address(struct in_addr& host);
		int									get_client_max_body_size() const;
		void								set_client_max_body_size(const int client_max_body_size);
		void								set_director(Director *d);
		Director*							get_director() const;
		LocationInfo&						get_location(int);
		void								add_locations(std::vector <LocationInfo *> locations);
		std::vector <LocationInfo *>		get_locations() const;
		bool								is_fd_in_clients(int fd) const;
// Server
		std::string							respond(Request& rq);
		int									get_error_code() const;
		void								set_error_code(int err);
		std::string							create_response(Request&);
		std::string							response;

	private:

		int									port;
		int									_client_max_body_size;
		std::vector <std::string>			server_name;
		struct in_addr						_host_address;
//		struct sockaddr_in					address;
		bool								autoindex;
		std::string							root;
		std::string							error_log;
		std::string							access_log;
		std::vector <LocationInfo*>			locations;
				void						init_status_strings();
		void								init_content_types();
		std::string							get_body(Request& rq);
		int									process(Request &rq);
		void								get_best_location_match(std::vector<LocationInfo*> locs, 
														Request& rq, std::string& best_match, 
														LocationInfo* locinfo);
		std::map<int, std::string>			status_string;
		std::map<std::string, std::string>	content_type;
		int									errcode;
		Director*							director;
};

std::ostream& operator<<(std::ostream& os, const Server& server_info);

#endif