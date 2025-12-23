#ifndef CHANNEL_H
#define CHANNEL_H

#include <string>
#include <set>
// #include <map>
#include <vector>
#include <iostream>
#include <sstream>

// #include <chrono>
#include <ctime>

#include <algorithm> // std::atoi
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
    std::string topic_whotime_; // <channel> <nick> <setat>
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
    std::string get_chnl_topic_time() const
    {
        return topic_whotime_ ;
    }
    
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
    
    // Topic
    bool channel_topic(const std::string user_nick, std::string new_topic, std::ostringstream& os)
    {
        std::set<std::string>::iterator s_it;
        s_it = chanop_list_.find(user_nick);
        if (t_mode_ == true && s_it == chanop_list_.end())
        {
            // ERR_CHANOPRIVSNEEDED (482)
            //  "<client> <channel> :You're not channel operator"
            os << ":miniircd 482 ";
            os << get_chnl_name();
            os << " :You're not channel operator";
            return false;
        }
        // can set new topic
        std::ostringstream new_t_whotime;
    
        // if (new_topic == ":")
        //     new_topic = "";
        this->topic_ = new_topic;
    
        std::time_t now = std::time(NULL);
        std::tm* local = std::localtime(&now);
        std::time_t actual_time = std::mktime(local);


        // for RPL_TOPICWHOTIME (333)
        // <channel> <nick> <setat>
        new_t_whotime << get_chnl_name() << " ";
        new_t_whotime << user_nick << " ";
        new_t_whotime << actual_time;
        this->topic_whotime_ = new_t_whotime.str();

        // std::cout << "Année   : " << (1900 + local->tm_year) << '\n';
        // std::cout << "Mois    : " << (1 + local->tm_mon)   << '\n';
        // std::cout << "Jour    : " << local->tm_mday        << '\n';
        // std::cout << "Heure   : " << local->tm_hour        << '\n';
        // std::cout << "Minute  : " << local->tm_min         << '\n';
        // std::cout << "Seconde : " << local->tm_sec         << '\n';

        os << ":miniircd 332 ";
        os << user_nick << " ";
        os << get_chnl_name();
        os << " :" << get_chnl_topic();
        return true ;
    }
};

// #include "User.hpp"
#endif