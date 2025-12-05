#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <set>
#include <map>
#include <vector>
#include <iomanip>
#include <sstream>
#include <algorithm>


// struct Client {
// 	int fd;
// 	std::string nick;
// 	std::string user;
// 	std::string real;
// 	bool registered;
// 	bool pass_ok;
// 	std::string inbuf;
// 	std::string outbuf;
// 	Client(): fd(-1), registered(false), pass_ok(false) {}
// };

class User
{
    public :

    int fd;
    bool registered;
	bool pass_ok;
    std::string nick;
	std::string user;
	std::string real;
	User(): fd(-1), registered(false), pass_ok(false) {}


    User(std::string new_nick, std::string new_user, std::string new_real, int new_fd):
        nick(new_nick), user(new_user), real(new_real), fd(new_fd)
    {};

    // chanop_mode
    // bool o_mode;
    // std::set<std::string> im_chanop_of;

    // invited
    std::set<std::string> im_invited_to;
};








#endif