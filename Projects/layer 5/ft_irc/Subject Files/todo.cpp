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

Operators

Kick
Invite
Topic
Mode - i t k o l-

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