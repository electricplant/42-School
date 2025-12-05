#include "Channel.hpp"

void Channel::add_user(User& usr)
{
    if (this->length == 0)
        this->chanop_list.insert(usr.nick);
    this->user_list.insert(usr.nick);
    this->length++;
    this->users_[usr.nick] = User(usr);
}
 
bool Channel::channel_join(User& usr, std::string key, std::string& returned_error)
{
    // Already exists : nothing happens
    if (user_list.find(usr.nick) != user_list.end())
        return true;

    if (this->k_mode == true && (key.empty() || key != this->key))
    {
        // ERR_BADCHANNELKEY (475)
        returned_error = "475 Cannot join to channel " + this->channel_name + " (+k)";
        return false;
    }
    if (this->i_mode == true)
    {
        // User must be invited
        if ((invited_users.find(usr.nick)) == invited_users.end())
        {
            // ERR_INVITEONLYCHAN (473)
            returned_error = "473 Cannot join to channel " + this->channel_name + " (+i)";
            return false;
        }
        invited_users.erase(usr.nick);
    }
    add_user(usr);
    return true;
}
