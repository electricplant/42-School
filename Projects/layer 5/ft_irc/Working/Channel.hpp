#ifndef CHANNEL_H
#define CHANNEL_H

#include <string>
#include <set>
#include <map>
#include <vector>
#include <iomanip>
#include <sstream>
#include <algorithm>

class User;
// class Server;

// #include "MiniIRCd.hpp"

class Channel
{
    private:
    
    std::map<std::string, User> users_;

    public:

    bool i_mode;
    bool k_mode;
    bool l_mode;
    bool t_mode;

    int length;
    std::string topic;
    std::string key;
    std::string channel_name;
    std::set<std::string> chanop_list;
    std::set<std::string> user_list;
    std::set<std::string> invited_users;


    // CONSTRUCTORS
    // for the first user :
    Channel(std::string name, User& usr):
        i_mode(false), k_mode(false), l_mode(false), t_mode(false),
        topic(""), key(""), channel_name(name)
    {  add_user(usr);  }

    Channel()
    {}
    ~Channel()
    {}
	// void sendLine(int fd, const std::string& line);

    // for all the users 
    bool channel_join(User& usr, std::string key, std::string& returned_error);
    void add_user(User& usr);
};

#include "User.hpp"
#endif