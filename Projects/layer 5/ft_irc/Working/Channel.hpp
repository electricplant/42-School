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

// #include "MiniIRCd.hpp"

class Channel
{
    private:
    
    bool i_mode_;
    bool k_mode_;
    bool l_mode_;
    bool o_mode_;
    bool t_mode_;

    int length_;
    int max_length_;
    std::string topic_;
    std::string key_;
    std::string channel_name_;
    std::set<std::string> chanop_list_;
    std::set<std::string> user_list_;
    std::set<std::string> invited_users_;
    // Need to implement smth to forward messages
    // to all the users
    // std::map<std::string, User> users_;


    public:

    // CONSTRUCTORS

    // For the first user :
    Channel(std::string name, User& usr);
    // Default :
    Channel();
    ~Channel();

    // For all the users
    std::string get_chnl_name() const
    {
        return this->channel_name_;
    }

    std::string get_chnl_topic() const
    {
        return this->topic_;
    }

    bool is_chnl_op(std::string usr_nick) const
    {
        std::set<std::string>::iterator chanop_it = this->chanop_list_.find(usr_nick);
        if (chanop_it == this->chanop_list_.end())
            return (false);
        return (true);
    }
    
    // Join
    bool channel_join(User& usr, std::string key, std::string& returned_error);
    void add_user(User& usr);
    // Mode
    bool channel_mode(std::vector<std::string> mode_params, std::string user_name, std::string& returned_info);
    bool add_mode(std::string modes, std::vector<std::string> mode_params, std::string user_name, std::string& returned_info);
    bool cancel_mode(std::string modes, std::string user_name, std::string& returned_info);
    void print_channel_modes(bool for_chanops, uint8_t all_modifs, std::string user_name, std::string& returned_info, std::string sign);
    // Part
    void channel_part(const std::string user_nick);

    // Problems when trying to connect to the same channel
    // with different IRSSI users :
    // The WHO and WHOIS commands seem necessary.
    // Also, reviewing PRIVMSG may be necessary.
};

#include "User.hpp"
#endif