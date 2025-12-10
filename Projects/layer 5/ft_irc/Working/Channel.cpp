#include "Channel.hpp"

// CONSTRUCTORS

// For the first user :
Channel::Channel(std::string name, User& usr):
    i_mode(false), k_mode(false), l_mode(false), t_mode(false),
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

void Channel::channel_mode(std::vector<std::string> mode_params, std::string user_name, std::string& returned_info)
{
    // "mode_params" begins with "+ikl..."
    std::cout << "channel_mode() called\n";
    
    if (mode_params.empty())
    {
        // Every channel's user can see Channel's modes.
        print_channel_modes(user_name, returned_info);
        return ;
    }

    if (this->chanop_list.find(user_name) == this->chanop_list.end())
    {
        // ERR_CHANOPRIVSNEEDED (482)
        returned_info = "482 " + user_name + " " + this->channel_name + " :You're not channel operator";
        return ;
    }

    std::string modes = *(mode_params.begin());
    if (!modes.empty() && modes.size() > 1)
    {
        std::string sign = modes.substr(0, 1);
        std::cout << "sign " << sign << "\n";
        if (sign == "+")
            add_mode(modes, mode_params);
        else if (sign == "-")
            cancel_mode(modes);
        print_channel_modes(user_name, returned_info);
    }
    return ;
}

void Channel::add_mode(std::string modes, std::vector<std::string> mode_params)
{
    bool error = false;
    std::cout << "=> add_mode func\n";
    bool tmp_k_mode = false, tmp_l_mode = false, tmp_t_mode = false;

    std::string::iterator the_mode = modes.begin();
    size_t counter = 1; //is for k,l,o,t : they need other parameters
    size_t total_prms = mode_params.size();

    the_mode++;
    while (the_mode != modes.end() && !error)
    {
        int mode_letter = *the_mode;
        // std::cout << "mode_letter " << mode_letter << "\n";
        // std::cout << "counter " << counter << "\n";
        // std::cout << "total_prms " << total_prms << "\n";
        // size_t i = -1;
        // while (++i < total_prms)
        //     std::cout << mode_params[i] << " "; 
        // std::cout << std::endl;
        
        switch (mode_letter)
        {
            case INVITE:
                this->i_mode = true;
                std::cout << this->channel_name << " : mode +i "
                                << std::endl;
                break;
            case KEY:
                if (tmp_k_mode == false && counter < total_prms)
                {
                    tmp_k_mode = true;
                    this->k_mode = true;
                    //"key" syntax is quite permissive
                    std::stringstream ss;
                    ss << mode_params[counter];
                    this->key = ss.str(); 
                    counter++;
                    
                    std::cout << this->channel_name << " : mode +k "
                                << this->key << std::endl;
                }
                break;
            case LENGTH:
                if (tmp_l_mode == false && counter < total_prms)
                {
                    this->max_length = std::atoi((mode_params[counter]).c_str());
                    if (this->max_length)
                    {
                        tmp_l_mode = true;
                        this->l_mode = true;
                        counter++;
                        std::cout << this->channel_name << " : mode +l "
                                    << this->max_length << std::endl;
                    }
                    else
                        error = true;
                }
                break;
            case OPER:
                // not yet
                break;
            case TOPIC:
                if (tmp_t_mode == false && counter < total_prms)
                {
                    tmp_t_mode = true;
                    this->t_mode = true;
                    this->topic = mode_params[counter];
                    counter++;

                    std::cout << this->channel_name << " : mode +t "
                                << this->topic << std::endl;
                }
                break;
        }
        the_mode++;
    }
    // std::stringstream ss;
    // ss << "RESULT : +";
    // if (i_mode)
    //     ss << "i";
    // if (k_mode)
    //     ss << "k";
    // if (l_mode)
    //     ss << "l";
    // if (t_mode)
    //     ss << "t";

    // if (key != "")
    //     ss << " " << key;
    // if (max_length != 0)
    //     ss << " " << max_length;
    // std::cout << ss.str() << std::endl; 
    return ;
}

void Channel::cancel_mode(std::string modes)
{
    std::cout << "=> cancel_mode func MODES : " << modes << "\n";

    std::string::iterator the_mode = modes.begin();

    the_mode++;
    while (the_mode != modes.end())
    {
        int mode_letter = *the_mode;

        std::cout << "mode_letter " << mode_letter << "\n";

        // size_t i = -1;
        // while (++i < total_prms)
        //     std::cout << mode_params[i] << " "; 
        // std::cout << std::endl;

        switch (mode_letter)
        {
            case INVITE:
                this->i_mode = false;
                break;
            case KEY:
                this->k_mode = false;
                break;
            case LENGTH:
                this->l_mode = false;
                this->max_length = 0;
                break;
            case OPER:
                // not yet
                break;
            case TOPIC:
                this->t_mode = false;
                break;
        }
        the_mode++;
    }

    std::cout << this->channel_name << " : mode -";
    if (!this->i_mode)
        std::cout << "i";
    if (!this->k_mode)
        std::cout << "k";
    if (!this->l_mode)
        std::cout << "l";
    // if (!this->o_mode)
    //     std::cout << "o";
    if (!this->t_mode)
        std::cout << "t";
    std::cout << "\n";

    return ; //temp
}

void Channel::print_channel_modes(std::string user_name, std::string& returned_info)
{
    std::stringstream ss;
    ss <<  "324 " + user_name + " " + this->channel_name + " +";
    if (this->i_mode)
        ss << "i";
    if (this->k_mode) 
        ss << "k";
    if (this->l_mode) 
        ss << "l";
    if (this->t_mode) 
        ss << "t";

    if (this->k_mode)
        ss << " " + this->key;
    if (this->l_mode)
    {
        ss << " " ; ss << this->max_length;
    }
    
    returned_info = ss.str();
    return ;
}