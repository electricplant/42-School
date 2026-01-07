/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   todo.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:16:15 by dgerhard          #+#    #+#             */
/*   Updated: 2025/12/29 14:25:36 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//TODO LIST

/*

2026 goals :

-> Code Architecture, better practice

    • use if/else to detect errors in main.cpp (instead of try/catch) 
      =>
    • in MiniIRCd.cpp , MiniIRCd::run() : put try/catch in the server loop
      to detect sudden changes (ex: a client is disconnecting)
      =>
    • in main.cpp, parseArgs() function : ports must be > 1024 : [1-1024] are reserved
      =>
    • in MiniIRCd.cpp : all fcntl() function calls must follow the subject requirements
      =>
    • in MiniIRCd.cpp, for all sendLine() calls : use std::ostringstream instead of const strings
      => 
    • in MiniIRCd.cpp, in handle_ ...join(), ...mode(), ...quit(), ...kick() etc.
      we use a loop to send a msg to all group members when one of them
      made a change : we should make a common function for it -> more readable
      => 
    • for homogeneity in MiniIRCd.* : in member functions, should we use "const int& fd"
      or "int fd"? -> in handle_quit(), using a reference caused a valgrind problem
      => Jeanne (and ... ?)
    • should we verify all the lib C/C++ functions' returned values ?
      => Jeanne (and ... ?)   
    /?\ should we use a certain norm in all of our code, for homogeneity ?

-> Add functionnalities

    • in MiniIRCd.cpp, we should allow handle_join to be performed for
      several channels at once + some channels will require keys (set with /mode)
      (ex : /join #channel1,#channel2 key1,key2 )
      https://modern.ircdocs.horse/#join-message
    => Jeanne
    • in MiniIRCd.cpp, handle_join() should show users' list at each connection
    => Jeanne
    • find out, why IRSSI suddenly disconnects clients, then
      reconnects them, and sometimes renames them by adding "_",
      and often after that, their previous nickname is already taken by
      a "ghost" user
    => Jeanne (and ... ?)
    • in MiniIRCd.cpp, in run() and handle_use(): we can
      add each user's real IP address (instead of writing "localhost" automatically)
    => Jeanne (and ... ?)

-> Bonus Part  => Jeanne (and ... ?)

    • Implement an IRC bot (what does it need to do? ...)
    • How to share files with IRC? (test on DALnet/liberachat first)

-> Tests in Python  => Jeanne



2025 :

Tasks from Subject File:
DONE - Executable requires port and password
DONE - Choose reference client (IRSSI)
DONE - Reference client connects without error
DONE - Communication is done with TCP/IP
DONE - Regular users
DONE - Can handle partial data input
DONE - Send/recv private messages
DONE - Message from client to channel appear in every client
DONE - Set nick
DONE - Can handle multiple clients without hanging
DONE - Set user
DONE - Join channel (ROOM)

DONE - Operators

DONE - Kick
DONE - Invite
DONE - Topic
DONE - Mode - i t k o l-

File transfer
A bot





1. Connect to a real IRC server (RFC 1459 or other) and test commands
with IRSSI on it /both ?

3.a. Create Basic_user + Operator classes with functions that
correspond to all the useful commands:
    - KICK
    - MODE
    - INVITE
    - TOPIC
    - JOIN
    ...     /Jeanne
3.b. Create a Channel class that has a container of users, and some booleans like :
    - is channel in +t mode?
    - is channel in +i mode? ...
    As well as :
    - users'list length
    - an std::string containing channel's topic
    ...
    /Jeanne

4.a. Inside the Server class, create a dynamic list of all users and channels /Dean?
4.b. the server must send parsing errors / unknown cmd errors to users
     or forward errors detected by channels to users /Dean? :))




//BONUS

//File transfer
1. How is it implemented? /Dean /


//Bot
1. What does the bot need to do? /Together




















*/