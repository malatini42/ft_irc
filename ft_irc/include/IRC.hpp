/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahautlatinis <mahautlatinis@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:09:48 by mahautlatin       #+#    #+#             */
/*   Updated: 2023/10/13 19:37:34 by mahautlatin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <Headers.hpp>
#include <User.hpp>
#include <Bot.hpp>
#include <Channel.hpp>
#include <Command.hpp>

class	IRC
{
	private:
		time_t const						_startupTime;
		std::string const					_svPassword;
		std::string const					_prefix;
		std::map<int, User *>				_users;
		std::map<std::string, Channel *>	_channels;
		int									_killing;
		Bot									*_bot;

		Channel								*newChannel(std::string const &name,
												User *creator);
		
		std::set<User *>					getCommonUsers(User *user) const;

		
		bool								passwordNotOK(User *user,
												std::vector<t_clientCmd> &responseQueue);

		std::string							getNoticeMsg(std::string const &senderPrefix,
												User *user, 
												std::string const &msg) const;

		std::string							getErrorResponse(User *user,
												std::string const &msg) const;

		std::string							getResponseFromCode(User *user,
												int code,
												std::string params[]) const;

		std::string							appendUserNotif(User *user,
												std::string params[],
												std::set<User *> const &dest,
												std::vector<t_clientCmd> &responseQueue,
												bool excludeUser=false) const;

		void								unknownCmd(Command const &cmd,
												std::vector<t_clientCmd> &responseQueue) const;

		void								pushToQueue(int fd,
												std::string const &msg,
												std::vector<t_clientCmd> &responseQueue) const;

		void								execCmd(Command const &cmd,
												std::vector<t_clientCmd> &responseQueue);
		
		void								admin(Command const &cmd,
												std::vector<t_clientCmd> &responseQueue);

		void								away(Command const &cmd,
												std::vector<t_clientCmd> &responseQueue);

		void								die(Command const &cmd,
												std::vector<t_clientCmd> &responseQueue);

		void								invite(Command const &cmd,
												std::vector<t_clientCmd> &responseQueue);

		void								join(Command const &cmd,
												std::vector<t_clientCmd> &responseQueue);

		void								kick(Command const &cmd,
												std::vector<t_clientCmd> &responseQueue);

		void								kill(Command const &cmd,
												std::vector<t_clientCmd> &responseQueue);

		void								list(Command const &cmd,
												std::vector<t_clientCmd> &responseQueue);

		void								mode(Command const &cmd,
												std::vector<t_clientCmd> &responseQueue);

		void								motd(Command const &cmd,
												std::vector<t_clientCmd> &responseQueue);

		void								names(Command const &cmd,
												std::vector<t_clientCmd> &responseQueue);

		void								nick(Command const &cmd,
												std::vector<t_clientCmd> &responseQueue);

		void								notice(Command const &cmd,
												std::vector<t_clientCmd> &responseQueue);

		void								oper(Command const &cmd,
												std::vector<t_clientCmd> &responseQueue);

		void								part(Command const &cmd,
												std::vector<t_clientCmd> &responseQueue);

		void								pass(Command const &cmd,
												std::vector<t_clientCmd> &responseQueue);

		void								ping(Command const &cmd,
												std::vector<t_clientCmd> &responseQueue);

		void								privmsg(Command const &cmd,
												std::vector<t_clientCmd> &responseQueue);

		void								quit(Command const &cmd,
												std::vector<t_clientCmd> &responseQueue);

		void								time(Command const &cmd,
												std::vector<t_clientCmd> &responseQueue);

		void								topic(Command const &cmd,
												std::vector<t_clientCmd> &responseQueue);

		void								user(Command const &cmd,
												std::vector<t_clientCmd> &responseQueue);

		void								version(Command const &cmd,
												std::vector<t_clientCmd> &responseQueue);

		void								who(Command const &cmd,
												std::vector<t_clientCmd> &responseQueue);

		void								chanPrivmsg(User *user,
												std::string const &name,
												std::string const &msg,
												std::vector<t_clientCmd> &responseQueue);

		void								userPrivmsg(User *user,
												std::string const &name,
												std::string const &msg,
												std::vector<t_clientCmd> &responseQueue);

		void								chanMode(User *user,
												std::string const &chanName,
												std::string const &modes,
												std::string const &params,
												std::vector<t_clientCmd> &responseQueue);
	
		void								userMode(User *user, 
												std::string const &nick,
												std::string const &modes,
												std::vector<t_clientCmd> &responseQueue);

		void								chanWho(User *user, 
												std::string const &mask,
												bool o,
												std::vector<t_clientCmd> &responseQueue) const;

		void								userWho(User *user,
												std::string mask,
												bool o,
												std::vector<t_clientCmd> &responseQueue) const;

		void								userLeaveChannel(User *user,
												Channel *chan);

		void								removeFromAllChannel(User *user);

		void								sendWelcomeMessage(User *user,
												std::vector<t_clientCmd> &responseQueue);

		std::string							kickTarget(User *user,
												std::string const &nick,
												Channel *chan,
												std::string const &comment,
												std::vector<t_clientCmd> &responseQueue);

	public:
		// Functions implemented here were added just to respect the canonical convention
		IRC(void):
			_startupTime(::time(NULL)),
			_svPassword("PASSWORD"),
			_prefix(std::string(":") + IRC_HOST),
			_killing(-1)
		{
			return ;
		};

		IRC(std::string const &password = "PASSWORD");

		IRC(IRC const &src): _startupTime(::time(NULL))
		{
			*this = src;
			return ;
		};

		virtual ~IRC(void);

		IRC &operator=(IRC const &rhs)
		{
			(void)rhs;
			return (*this); 
		};

		User									*getUserByNick(std::string const &nick) const;
		Channel									*getChannelByName(std::string const &name) const;

		bool									processClientCommand(t_clientCmd const &command,
													std::vector<t_clientCmd> &responseQueue);

		void									clientDisconnect(int fd);
		int										getVictim(void);
};