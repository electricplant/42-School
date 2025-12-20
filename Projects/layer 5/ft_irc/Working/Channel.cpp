#include "Channel.hpp"

// CONSTRUCTORS

// For the first user :
Channel::Channel(const std::string name, const std::string usr):
    i_mode_(false), k_mode_(false), l_mode_(false), o_mode_(false), t_mode_(false),
    length_(0), max_length_(0), topic_(""), key_(""), channel_name_(name)
{  add_user(usr);  }

// Default :
Channel::Channel(){}
Channel::~Channel(){}

// GETTERS
std::string Channel::get_chnl_name() const
{ return this->channel_name_; }

std::string Channel::get_chnl_topic() const
{ return this->topic_; }

// VERIFICATIONS 

bool Channel::is_chnl_op(const std::string usr_nick) const
{
    std::set<std::string>::iterator chanop_it = this->chanop_list_.find(usr_nick);
    if (chanop_it == this->chanop_list_.end())
        return (false);
    return (true);
}

bool Channel::is_chnl_usr(const std::string usr_nick) const
{
    std::set<std::string>::iterator usr_it = this->user_list_.find(usr_nick);
    if (usr_it == this->user_list_.end())
        return (false);
    return (true);
}


// JOIN

void Channel::add_user(std::string usr)
{
    if (length_ == 0)
        chanop_list_.insert(usr);
    this->user_list_.insert(usr);
    length_++;
    // users_[usr] = User(usr);
}

bool Channel::channel_join(std::string usr, std::string key, std::string& returned_error)
{
    std::cout << "=> join func\n";

    // Already exists : nothing happens
    if (user_list_.find(usr) != user_list_.end())
    {
        
        return true;
    }

    if (k_mode_ == true && (key.empty() || key != key_))
    {
        // ERR_BADCHANNELKEY (475)
        returned_error = ":miniircd 475 Cannot join to channel " + channel_name_ + " (+k)";
        return false;
    }
    if (i_mode_ == true)
    {
        // User must be invited
        if ((invited_users_.find(usr)) == invited_users_.end())
        {
            // ERR_INVITEONLYCHAN (473)
            returned_error = ":miniircd 473 " + usr + " " + channel_name_ + " :Cannot join channel (+i)\n";
            return false;
        }
        invited_users_.erase(usr);
    }
    add_user(usr);
    return true;
}

// MODE

bool Channel::channel_mode(std::vector<std::string> mode_params, std::string user_name, std::string& returned_info)
{
    // "mode_params" begins with "+ikl..."
    
    if (mode_params.empty())
    {
        // Every channel's user can see Channel's modes.
        uint8_t all_modes = 0;
        if (i_mode_) all_modes |= 1;
        if (k_mode_) all_modes |= 2;
        if (l_mode_) all_modes |= 4;
        // if (o_mode_) all_modes |= 8;
        if (t_mode_) all_modes |= 16;
        
        print_channel_modes(false, all_modes, user_name, returned_info, "+", "");
        return (false);
    }
    else if (mode_params.size() == 1
        && (*mode_params[0].begin() != '-' && *mode_params[0].begin() != '+') )
    {
        // Every channel's user can ask for banlist "#channel b"
        // Out of the scope for this project
        return (false);
    }

    if (chanop_list_.find(user_name) == chanop_list_.end())
    {
        // ERR_CHANOPRIVSNEEDED (482)
        returned_info = "482 " + user_name + " " + channel_name_ + " :You're not channel operator";
        return (false);
    }

    std::string modes = *(mode_params.begin());
    if (!modes.empty() && modes.size() > 1)
    {
        std::string sign = modes.substr(0, 1);
        std::cout << "sign " << sign << "\n";
        if (sign == "+")
            return (add_mode(modes, mode_params, user_name, returned_info));
        else if (sign == "-")
            return (cancel_mode(modes, mode_params, user_name, returned_info));
    }
    returned_info = "";
    return (false);
}


bool Channel::add_mode(std::string modes, std::vector<std::string> mode_params, std::string user_name, std::string& returned_info)
{
    bool error = false;
    std::cout << "=> add_mode func\n";
    
    uint8_t all_modifs = 0;
    std::string other_gr_mate = ""; // for +o

    std::string::iterator the_mode = modes.begin();
    size_t param_counter = 1; //is for k,l,o,t : they need other parameters
    size_t total_prms = mode_params.size();

    int j = 0;
    std::cout << "=> all params: \n";

    while ((size_t)j < total_prms)
    {
        std::cout << mode_params[j] << "\n";
        j++;
    }

    the_mode++;
    while (the_mode != modes.end() && !error)
    {
        int mode_letter = *the_mode;
        switch (mode_letter)
        {
            case INVITE:
            if (!i_mode_)
            {
                all_modifs |= 1;
                i_mode_ = true;
                // std::cout << this->channel_name << " : mode +i "
                //             << std::endl;
            }
            break;
            case KEY:
            if (param_counter < total_prms)
            {
                k_mode_ = true;
                all_modifs |= 2;
                //"key" syntax is quite permissive
                std::stringstream ss;
                ss << mode_params[param_counter];
                key_ = ss.str(); 
                param_counter++;
                // std::cout << this->channel_name << " : mode +k "
                //             << this->key << std::endl;
            }
            break;
            case LENGTH:
            if (param_counter < total_prms)
            {
                max_length_ = std::atoi((mode_params[param_counter]).c_str());
                param_counter++;
                if (max_length_ != 0)
                {
                    l_mode_ = true;
                    all_modifs |= 4;
                    // std::cout << this->channel_name << " : mode +l "
                    //             << this->max_length << std::endl;
                }
            }
            break;
            case OPER:
            if (param_counter < total_prms)
            {
                other_gr_mate = mode_params[param_counter];
                std::set<std::string>::iterator usrs_it;
                usrs_it = user_list_.find(other_gr_mate);
                if (usrs_it != user_list_.end())
                {
                    chanop_list_.insert(other_gr_mate);
                    // o_mode_ = true;
                    all_modifs |= 8;
                }
                // else
                //     std::cout << "Mode +o NOT ADDED\n" << other_gr_mate
                //             << " not in channel " << get_chnl_name()
                //             << "\n";
                param_counter++;
            } 
            break;
            case TOPIC:
            if (param_counter < total_prms)
            {
                t_mode_ = true;
                all_modifs |= 16;
                topic_ = mode_params[param_counter];
                param_counter++;

                // std::cout << this->channel_name << " : mode +t "
                //             << this->topic << std::endl;
            }
            break;
            default:
                error = true;
                break;
        }
        the_mode++;
    }
    
    // if smth changed
    if (all_modifs == 0)
    {
        returned_info = "";
        std::cout << "No mode added in " << this->get_chnl_name() << "\n";
        return (false);
    }
    else
    {
        std::cout << "Mode(s) added in " << this->get_chnl_name() << "\n";
        print_channel_modes(true, all_modifs, user_name, returned_info, "+", other_gr_mate);
        return (true);
    }
}



bool Channel::cancel_mode(std::string modes, std::vector<std::string> mode_params, std::string user_name, std::string& returned_info)
{
    std::cout << "=> cancel_mode func MODES : " << modes << "\n";

    size_t param_counter = 1; //is for -o : need other parameter
    size_t total_prms = mode_params.size();
    bool error = false;
    uint8_t all_modifs = 0;
    std::string other_gr_mate = ""; // for -o
    std::string::iterator the_mode = modes.begin();

    the_mode++;
    while (the_mode != modes.end() && !error)
    {
        int mode_letter = *the_mode;
        // std::cout << "mode_letter " << mode_letter << "\n";

        switch (mode_letter)
        {
            case INVITE:
            if (i_mode_)
            {
                i_mode_ = false;
                all_modifs |= 1;
            }
            break;
            case KEY:
            if (k_mode_)
            {
                k_mode_ = false;
                all_modifs |= 2;
            }
            break;
            case LENGTH:
            if (l_mode_)
            {
                l_mode_ = false;
                max_length_ = 0;
                all_modifs |= 4;
            }
            break;
            case OPER:
            // whether the other user was a chanop or not
            if (param_counter < total_prms)
            {
                other_gr_mate = mode_params[param_counter];
                std::set<std::string>::iterator usrs_it;
                usrs_it = user_list_.find(other_gr_mate);
                if (usrs_it != user_list_.end())
                {
                    all_modifs |= 8;
                    std::set<std::string>::iterator ch_lit = chanop_list_.find(other_gr_mate);
                    if (ch_lit != chanop_list_.end())
                        chanop_list_.erase(other_gr_mate);
                }
                param_counter++;
            } 
            break;
            case TOPIC:
            if (t_mode_)
            {
                t_mode_ = false;
                all_modifs |= 16;
            }
            break;
            default:
            error = true;
            break;
        }
        the_mode++;
    }

    // if nothing changed
    if (all_modifs == 0)
    {
        returned_info = "";
        std::cout << "No mode canceled in " << this->get_chnl_name() << "\n";
        return (false);
    }
    else
    {
        std::cout << "Mode(s) canceled in " << this->get_chnl_name() << "\n";
        print_channel_modes(true, all_modifs, user_name, returned_info, "-", other_gr_mate);
        return (true);
    }
}

void Channel::print_channel_modes(bool chanops_only, uint8_t all_modifs, std::string user_name,
    std::string& returned_info, std::string sign, std::string new_chanop)
{
    //124 64 32 16 8 4 2 1
    std::stringstream ss;

    // TWO cases:
    if (!chanops_only) 
        ss <<  "324 " + user_name + " " + channel_name_ + " " + sign;
    else
        ss << ":" + user_name + "!~usr@host MODE " + channel_name_ + " " + sign;
    if (all_modifs & 1)
        ss << "i";
    if (all_modifs & 2) 
        ss << "k";
    if (all_modifs & 4) 
        ss << "l";
    if (all_modifs & 8) 
        ss << "o " << new_chanop;
    if (all_modifs & 16) 
        ss << "t";

    if (all_modifs & 2)
        ss << " " + key_;
    if (all_modifs & 4)
    {
        ss << " " ; ss << max_length_;
    }
    
    returned_info = ss.str();
    return ;
}

// PART

void Channel::channel_part(const std::string user_nick)
{
    std::cout << "=> channel_part on " << user_nick << "\n";
    
    std::set<std::string>::iterator set_it;

    set_it = user_list_.find(user_nick);
    if (set_it != user_list_.end())
        user_list_.erase(user_nick);
    else
        return ;
    set_it = chanop_list_.find(user_nick);
    if (set_it != chanop_list_.end())
        chanop_list_.erase(user_nick);

    set_it = invited_users_.find(user_nick);
    if (set_it != invited_users_.end())
        invited_users_.erase(user_nick);
    
    --length_;
}

// INVITE

void Channel::channel_invite(const std::string user_nick)
{
    invited_users_.insert(user_nick);
}
