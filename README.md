# Intro
> Internet Relay Chat or IRC is a text-based communication protocol on the Internet.
> It offers real-time messaging that can be either public or private. Users can exchange direct messages and join group channels.
> IRC clients connect to IRC servers in order to join channels. IRC servers are connected together to form a network.

This program creates and runs an IRC server. It follows the IRC protocols when communicating with IRC clients and has several bots into its programming to interact with.

## Table of Contents
- [Usage](#Usage)
  - [Client](#Client)
  - [Bots](#Bots)
- [Information](#Information)
  - [Environment](#Environment)
  - [Sockets](#Sockets)
  - [Ports](#Ports)
  - [Classes](#Classes)
  - [Namespaces](#Namespaces)
- [Sources](#Sources)
- [Creators](#Creators)

# Usage
The server has been designed for Linux, but should compatible with MacOS too.
It can be compiled and run using the following terminal commands.

<table>
	<thead style="background-color: #C0C0C0;">
		<tr><th colspan="3">Terminal Commands</th></tr>
		<tr>
			<th>Command</th>
			<th>Arguments</th>
			<th>Functionality</th>
		</tr>
	</thead>
	<tbody>
		<tr>
			<td><a href="Makefile" target="_blank">make</a></td>
			<td></td>
			<td>Compiles the files into ircserv</td>
		</tr>
		<tr>
			<td>./ircserv</td>
			<td>[port] [password]</td>
			<td>Runs the binary</td>
		</tr>
		<tr>
			<td><a href="Makefile" target="_blank">make</a></td>
			<td>subject</td>
			<td>Compiles the files and runs the binary with port '6667' and password set to 'password'</td>
		</tr>
		<tr>
			<td><a href="nctest.sh" target="_blank">./nctest.sh</a></td>
			<td></td>
			<td>Runs a shell script that in turn runs nc. Automatically logs in into the server</td>
		</tr>
	</tbody>
</table>

## Client
While this server, in theory, is compatible with all IRC Clients that follow the IRC protocol. It has been tested using [Pidgin](https://pidgin.im/) and is fully compatible with it.
To connect with Pidgin make a new Account and set the following settings.
- Set Protocol to '**IRC**'
- Set Username to the desired Nickname
- Set Server to the **Local IP Address** provided by the IRC Server
- Set Password to the password passed to the server
- Set Port(Advanced) to the port passed to the server
- Set Ident name(Advanced) to the desired name
- Set Real name(Advanced) to the desired full name

Alternatively **nc** can be used to connect. This will however require the user to type in full IRC Protocol. The Shell Script [nctest.sh](nctest.sh) can be used to quickly connect to the IRC Server and will register the user and execute a few test commands.

## Bots
While the IRC Server is mainly for client to client communication. It also contains several bots for users to interact with.
| Bots |||
| --- | --- | --- |
| [ServerBot](hdr/ServerBot.hpp) | //info | A bot that only works through private messages. He can provide some general server information and shutdown the server. |
| [TicTacBot](hdr/BotTicTacToe.hpp) | //play | A bot that can play Tic Tac Toe. |
| [RockBot](hdr/RockBot.hpp) | //throw | A bot that can play Rock Paper Scissors |

# Information
## Environment
The project contains an [.env](.env) file which valuable information about the server.
This includes the server name, the password for admins and the level of verbose.
Whenever this file is changes, the server automatically updates accordingly.

The IRC_VERBOSE setting in .env can be set to adjust the types of output are sent to the standard output.
| Setting | enum | Message Type |
| --- | --- | --- |
| 0 | V_SILENT | Silent |
| 1 | V_ADMIN | Include Admin messages |
| 2 | V_DETAILS | Include Details on construction and deconstruction of users | 
| 3 | V_CHANNEL | Include Channel events |
| 4 | V_USER | Include User events |
| 5 | V_MSG | Include all messages sent to and from the Server |

## Sockets
Using the [int socket()](src/Server.cpp#L190) function, a socket is created for internet communication (**AF_INET**) over which bi-directional communication (**SOCK_STREAM**) is possible.
Using the [int setsockopt()](src/Server.cpp#L194) function, the socket is set to bind a socket, even if the address is already in use.
For MacOS systems the function [int fcntl()](src/Server.cpp#L201) is used to ensure the socket is non-blocking (**O_NONBLOCK**).

## Ports
Then using the [int bind()](https://man7.org/linux/man-pages/man2/bind.2.html) function, the socket is bound to the specified port and the function [int listen()](src/Server.cpp#L217) sets it to listen to the port for incoming streams and maintaining a backlog, which can store 128 (**SOMAXCONN**) incoming messages.
The accepted ports have been restricted to avoid usage ports that have predefined uses.

| Port | Usage |
| --- | --- |
| 0 ... 1023 | Well-Known Ports(0-1023) |
| 1433 | Microsoft SQL Server |
| 1521 | Oracle Database |
| 3306 | MySQL Database |
| 5000 | UPnP (Universal Plug and Play) control point |
| 5222 | XMPP (Extensible Messaging and Presence Protocol) |
| 5432 | PostgreSQL Database |
| 7070 | Real-Time Messaging Protocol (RTMP) |
| 8080 | Alternate HTTP (commonly used for web servers) |
| 8443 | HTTPS Alternate (often used for secure web traffic) |
| 9090 | Alternate Web Server (often used for web proxy servers) |

## Classes
The bulk of this program consists of classes. There are classes for the [Server](hdr/Server.hpp), [Channels](hdr/Channel.hpp) and the Clients.
The Clients are derived for the abstract class [AClient](hdr/AClient.hpp), from which the bots are also derived. Once a Bot or Client is added the IRC Server no longer differentiates between them.
The Server has been structured so that new Bots can easily be implemented.
They do require definitions for the following public member functions.

| Return | Public Member Function | Usage |
| --- | --- | --- |
| bool | stillActive(void) const | Whether an AClient is still active |
| void | closeFD(void) | Clean up function for any File Descriptors or alternatives used |
| std::string | getMsg(void) | Messages the AClient wants to send to the server |
| void | sendMsg(std::string msg) | Messages sent to the AClient |

## Namespaces
We made space for those too!

# Sources
- https://pidgin.im/
- https://modern.ircdocs.horse/#introduction

# Creators
Othello
- [LinkedIn]()
- [GitHub](https://github.com/OthelloPlusPlus)

MagicEmy
- [LinkedIn]()
- [GitHub]()
