/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 14:45:40 by emlicame          #+#    #+#             */
/*   Updated: 2023/09/18 19:08:41 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
# define COMMAND_HPP

#include "Client.hpp"
#include "Server.hpp"
#include "IRCReplyCodes.hpp"
#include <string>

namespace Command
{
	void parseCmd(Client &user, const std::string& cmd, const std::vector<std::string>& args, Server *server);
	
	namespace PrivCommand
	{
		void password(Client &user, const std::string &cmd, const std::vector<std::string> &args, Server *server);
		void user(Client &user, const std::string &cmd, const std::vector<std::string> &args);
		void nick(Client &user, const std::string &cmd, const std::vector<std::string> &args, std::vector<Client*> clients);
		void ping(Client &user, const std::string &cmd, const std::vector<std::string> &args, Server *server);
		void quit(Client &user, const std::string &cmd, const std::vector<std::string> &args, Server *server);
		void oper(Client &user, const std::string &cmd, const std::vector<std::string> &args, Server *server);
		
	}

}

#endif