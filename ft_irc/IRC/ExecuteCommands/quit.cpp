/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QUIT.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahautlatinis <mahautlatinis@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 19:06:14 by mahautlatin       #+#    #+#             */
/*   Updated: 2023/10/06 19:07:16 by mahautlatin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../IRC.hpp"

void	IRC::quit(Command const &cmd, std::vector<t_clientCmd> &responseQueue)
{
	User	*user(cmd._user);
	string	msg = cmd._params.empty()
					? "Client exited"
					: ("Quit: " + cmd._params[0]);

	appendUserNotif(
		user,
		(string[]){ "QUIT", ":" + msg, "" },
		getCommonUsers(user), responseQueue
	);

	string	resp(getErrorResponse(user, msg));

	pushToQueue(user->_fd, resp, responseQueue);
	ClientDisconnect(user->_fd);
	return ;
}
