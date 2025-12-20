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

// class User;


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

    // std::map<std::string, User> users_;


    public:

    // CONSTRUCTORS

    // For the first user :
    Channel(const std::string name, const std::string usr);
    // Default :
    Channel();
    ~Channel();

    // Getters
    std::string get_chnl_name() const;
    std::string get_chnl_topic() const;
    
    // Verifications 
    bool is_chnl_op(const std::string usr_nick) const;
    bool is_chnl_usr(const std::string usr_nick) const;

    void show_chnl_users() const
    {
        std::set<std::string>::iterator it;
        it = this->user_list_.begin();

        std::cout << get_chnl_name() << "'s users (" << this->user_list_.size()
                    << ")\n";
        while (it != this->user_list_.end())
        {
            std::cout << *it << std::endl;
            ++it;
        }
    }
    
    // Join
    bool channel_join(std::string usr, std::string key, std::string& returned_error);
    void add_user(std::string usr);
    // Mode
    bool channel_mode(std::vector<std::string> mode_params, std::string user_name, std::string& returned_info);
    bool add_mode(std::string modes, std::vector<std::string> mode_params, std::string user_name, std::string& returned_info);
    bool cancel_mode(std::string modes, std::vector<std::string> mode_params, std::string user_name, std::string& returned_info);
    void print_channel_modes(bool for_chanops, uint8_t all_modifs, std::string user_name,
        std::string& returned_info, std::string sign, std::string new_chanop);
    // Part
    void channel_part(const std::string user_nick);
    // Invite
    void channel_invite(const std::string user_nick);

    // Problems when trying to connect to the same channel
    // with different IRSSI users :
    // The WHO and WHOIS commands seem necessary.
};

// #include "User.hpp"
#endif