#include "Channel.hpp"

void Channel::add_user(std::string cl_nick, int fd, User* usr)
{
    if (this->length == 0)
    {
        chanop_list.insert(cl_nick);
        user_list.insert(cl_nick);
    }
    else
        user_list.insert(cl_nick);
    this->length++;
    users_[cl_nick] = new User(cl_nick, fd);
}
 
bool Channel::channel_join(std::string cl_nick, int fd, User* usr, std::string error_msg, std::string key)
{
    //already exists : nothing happens
    if (user_list.find(usr->nick) != user_list.end())
        return true;

    if (this->k_mode == true)
    {
        if (key != this->key)
        {
            // ERR_BADCHANNELKEY (475)
            error_msg = "475 Cannot join to channel " + this->channel_name + " (+k)";
            return false;
        }
        else
        {
        
        }
    }
    if (this->i_mode == true)
    {
        // user should be invited
        if (invited_users.find(cl_nick) == invited_users.end())
        {
            // ERR_INVITEONLYCHAN (473)
            error_msg = "473 Cannot join to channel " + this->channel_name + " (+i)";
            return false;
        }
        invited_users.erase(cl_nick);
        
        return true;
    }
    else
    {
        
    }
    return 0;
}
