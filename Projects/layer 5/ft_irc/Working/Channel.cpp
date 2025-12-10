#include "Channel.hpp"

// CONSTRUCTORS

// For the first user :
Channel::Channel(std::string name, User& usr):
    i_mode(false), k_mode(false), l_mode(false), o_mode(false), t_mode(false),
    length(0), max_length(0), topic(""), key(""), channel_name(name)
{  add_user(usr);  }

// Default :
Channel::Channel()
{}
Channel::~Channel()
{}


// JOIN

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

// MODE

bool Channel::channel_mode(std::vector<std::string> mode_params, std::string user_name, std::string& returned_info)
{
    // "mode_params" begins with "+ikl..."
    std::cout << "channel_mode() called\n";
    
    if (mode_params.empty())
    {
        // Every channel's user can see Channel's modes.
        uint8_t all_modes = 0;
        if (this->i_mode) all_modes |= 1;
        if (this->k_mode) all_modes |= 2;
        if (this->l_mode) all_modes |= 4;
        if (this->o_mode) all_modes |= 8;
        if (this->t_mode) all_modes |= 16;
        
        print_channel_modes(false, all_modes, user_name, returned_info, "+");
        return (false);
    }

    if (this->chanop_list.find(user_name) == this->chanop_list.end())
    {
        // ERR_CHANOPRIVSNEEDED (482)
        returned_info = "482 " + user_name + " " + this->channel_name + " :You're not channel operator";
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
            return (cancel_mode(modes, user_name, returned_info));
    }
    returned_info = "";
    return (false);
}

bool Channel::add_mode(std::string modes, std::vector<std::string> mode_params, std::string user_name, std::string& returned_info)
{
    bool error = false;
    std::cout << "=> add_mode func\n";
    uint8_t all_modifs = 0;

    std::string::iterator the_mode = modes.begin();
    size_t param_counter = 1; //is for k,l,o,t : they need other parameters
    size_t total_prms = mode_params.size();

    the_mode++;
    while (the_mode != modes.end() && !error)
    {
        int mode_letter = *the_mode;
        switch (mode_letter)
        {
            case INVITE:
                if (!this->i_mode)
                {
                    all_modifs |= 1;
                    this->i_mode = true;
                    // std::cout << this->channel_name << " : mode +i "
                    //             << std::endl;
                }
                break;
            case KEY:
                if (param_counter < total_prms)
                {
                    this->k_mode = true;
                    all_modifs |= 2;
                    //"key" syntax is quite permissive
                    std::stringstream ss;
                    ss << mode_params[param_counter];
                    this->key = ss.str(); 
                    param_counter++;
                    // std::cout << this->channel_name << " : mode +k "
                    //             << this->key << std::endl;
                }
                break;
            case LENGTH:
                if (param_counter < total_prms)
                {
                    this->max_length = std::atoi((mode_params[param_counter]).c_str());
                    param_counter++;
                    if (this->max_length != 0)
                    {
                        this->l_mode = true;
                        all_modifs |= 4;
                        // std::cout << this->channel_name << " : mode +l "
                        //             << this->max_length << std::endl;
                    }
                }
                break;
            case OPER:
                // not yet
                break;
            case TOPIC:
                if (param_counter < total_prms)
                {
                    this->t_mode = true;
                    all_modifs |= 16;
                    this->topic = mode_params[param_counter];
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
        print_channel_modes(true, all_modifs, user_name, returned_info, "+");
        return (true);
    }
}

bool Channel::cancel_mode(std::string modes, std::string user_name, std::string& returned_info)
{
    std::cout << "=> cancel_mode func MODES : " << modes << "\n";

    bool error = false;
    uint8_t all_modifs = 0;
    std::string::iterator the_mode = modes.begin();

    the_mode++;
    while (the_mode != modes.end() && !error)
    {
        int mode_letter = *the_mode;
        // std::cout << "mode_letter " << mode_letter << "\n";

        switch (mode_letter)
        {
            case INVITE:
                if (this->i_mode)
                {
                    this->i_mode = false;
                    all_modifs |= 1;
                }
                break;
            case KEY:
                if (this->k_mode)
                {
                    this->k_mode = false;
                    all_modifs |= 2;
                }
                break;
            case LENGTH:
                if (this->l_mode)
                {
                    this->l_mode = false;
                    this->max_length = 0;
                    all_modifs |= 4;
                }
                break;
            case OPER:
                // not yet
                break;
            case TOPIC:
                if (this->t_mode)
                {
                    this->t_mode = false;
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
        print_channel_modes(true, all_modifs, user_name, returned_info, "-");
        return (true);
    }
}


void Channel::print_channel_modes(bool chanops_only, uint8_t all_modifs, std::string user_name, std::string& returned_info, std::string sign)
{
    //124 64 32 16 8 4 2 1
    std::stringstream ss;

    // TWO cases:
    if (!chanops_only) 
        ss <<  "324 " + user_name + " " + this->channel_name + " " + sign;
    else
        ss << ":" + user_name + "!~usr@host MODE " + this->channel_name + " " + sign;
    if (all_modifs & 1)
        ss << "i";
    if (all_modifs & 2) 
        ss << "k";
    if (all_modifs & 4) 
        ss << "l";
    if (all_modifs & 8) 
        ss << "o";
    if (all_modifs & 16) 
        ss << "t";

    if (all_modifs & 2)
        ss << " " + this->key;
    if (all_modifs & 4)
    {
        ss << " " ; ss << this->max_length;
    }
    
    returned_info = ss.str();
    return ;
}