/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Channel.hpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ohengelm <ohengelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/11 13:37:13 by ohengelm      #+#    #+#                 */
/*   Updated: 2023/03/11 13:39:19 by ohengelm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "Client.hpp"

# include <netinet/in.h>
// struct sockaddr_in
// socklen_t
# include <poll.h>
// struct pollfd
# include <iostream>
// std::
# include <vector>
// std::vector

class Channel
{
	struct ChannelUser
	{
		Client			*client;
		bool			admin;
		unsigned int	timestamp;
	};

	private:
		std::string	name;
		std::string	topic;
		bool		modeInvite;
		bool		modeTopic;
		std::string	key;
		int			userLimit;
		static int		verbose;

		std::vector<ChannelUser>	users;

		// std::vector<Client *>	operators;
		// std::vector<Client *>	clients;

		void	sendTopic(Client *client);
		void	sendNames(Client *client);
		void	sendPrivMsg(Client *sender, std::string msg);

		void	setTopic(ChannelUser user, const std::string newTopic);

		void	inviteClient(Client *client);
		// void	kickClient(Client *client);

		void	printClientList(void) const;
		
	protected:

	public:
		Channel(std::string name);
		Channel(const Channel &src);
		~Channel(void);

		void	addClient(Client *newClient, bool admin);
		void	sendToChannel(const std::string msg) const;
		void	sendToChannel(const Client *exclude, const std::string msg) const;
		// void	sendMsgToChannel(Client *sender, std::string msg);
		void	sendWho(Client *client);
		bool	userIsInChannel(const Client *client) const;
		void	removeUser(const Client *client);
		void	promoteOldestUser(void);

		static void		setVerbose(const int verbose);
		void	setAdmin(Client *target, bool status);

		std::string	getName(void) const;
		std::string	getTopic(void) const;
		size_t		getSize(void) const;
		size_t		getAdminSize(void) const;

		Channel	&operator=(const Channel &src);
};

#endif
