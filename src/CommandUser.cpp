/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandUser.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 19:40:13 by emlicame          #+#    #+#             */
/*   Updated: 2023/09/14 14:17:45 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include "colors.hpp"

void Command::user(Client &user, const std::string& cmd, const std::vector<std::string> &args) {
	
	if (user.getIsRegistered()){
		user.sendMsg("462 client " + user.getBestName() + " " + cmd + ERR_ALREADYREGISTERED);
		return ;
	}

	if (args.size() < 4){
		user.sendMsg("461 client " + user.getBestName() + " " + cmd + ERR_NEEDMOREPARAMS);
		std::cerr << C_RED << "Error" << C_RESET << ": format required: USER <user name> * <host> <realname>" << std::endl;
		return ;
	}

	user.setIdentName(args[0]);
	if (args[1] != "*"){
		std::cerr << C_RED << "Error" << C_RESET << ": format required: USER <user name> * <host> <realname>" << std::endl;
		return ;
	}
	user.setServer(args[2]);
	
	std::string temp = args[3].substr(0);
	if (args.size() > 4){
		for (int i = 4; i < args.size(); i++)
			temp.append(" " + args[i]);
	}
	user.setRealName(temp);
	
	user.userRegistration();
}
