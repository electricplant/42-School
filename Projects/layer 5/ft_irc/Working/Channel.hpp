#ifndef CHANNEL_H
#define CHANNEL_H

#include <string>
#include <set>
#include <map>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <stdint.h>

#define INVITE  105
#define KEY     107
#define LENGTH  108
#define OPER    111
#define TOPIC   116

class User;
// class Server;

// #include "MiniIRCd.hpp"

class Channel
{
    private:
    
    bool i_mode;
    bool k_mode;
    bool l_mode;
    bool o_mode;
    bool t_mode;

    int length;
    int max_length;
    std::string topic;
    std::string key;
    std::string channel_name;
    std::set<std::string> chanop_list;
    std::set<std::string> user_list;
    std::set<std::string> invited_users;
    // Need to implement smth to forward messages
    // to all the users
    std::map<std::string, User> users_;


    public:

    // CONSTRUCTORS

    // For the first user :
    Channel(std::string name, User& usr);
    // Default :
    Channel();
    ~Channel();

    // For all the users
    std::string get_chnl_name()
    {
        return this->channel_name;
    }
    
    // Join
    bool channel_join(User& usr, std::string key, std::string& returned_error);
    void add_user(User& usr);
    // Mode
    bool channel_mode(std::vector<std::string> mode_params, std::string user_name, std::string& returned_info);
    bool add_mode(std::string modes, std::vector<std::string> mode_params, std::string user_name, std::string& returned_info);
    // bool add_mode(std::string modes, std::vector<std::string> mode_params);
    bool cancel_mode(std::string modes, std::string user_name, std::string& returned_info);
    void print_channel_modes(bool for_chanops, uint8_t all_modifs, std::string user_name, std::string& returned_info, std::string sign);

    // Problems when trying to connect to the same channel
    // with different IRSSI users :
    // The WHO and WHOIS commands seem necessary.
    // Also, reviewing PRIVMSG may be necessary.
};

#include "User.hpp"
#endif