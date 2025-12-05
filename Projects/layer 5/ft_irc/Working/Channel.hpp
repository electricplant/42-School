#ifndef CHANOP_H
#define CHANOP_H

#include <string>
#include <set>
#include <map>
#include <vector>
#include <iomanip>
#include <sstream>
#include <algorithm>

class User;
class Server;

#include "MiniIRCd.hpp"

class Channel
{
    private:
    
    std::map<std::string, User*> users_;

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



    // CONSTRUCTOR
    Channel(std::string name): channel_name(name),
            i_mode(false), k_mode(false), l_mode(false), t_mode(false),
            topic(""), key("")
    {

    };

	// void sendLine(int fd, const std::string& line);

    bool channel_join(std::string cl_nick, int fd, User* usr, std::string error_msg, std::string key);
    void add_user(std::string cl_nick, int fd, User* usr);
    // int add_user(User* usr)
    // {
        
    // }
    // OR channel_join(User* usr); 
    // possible errors:
    // ERR_CHANNELISFULL (471)
    // ERR_INVITEONLYCHAN (473)

};

#include "User.hpp"

#endif