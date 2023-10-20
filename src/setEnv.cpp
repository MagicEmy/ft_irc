/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setEnv.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ohengelm <ohengelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 15:46:37 by ohengelm      #+#    #+#                 */
/*   Updated: 2023/09/29 19:08:56 by emlicame      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "colors.hpp"

#include <iostream>
// std::cout
// std::string
// std::exception
#include <fstream>
// std::ifstream
#include <cstdlib>
// int	setenv(const char *__name, const char *__value, int __overwrite)
#include <string.h>
// char *strerror(int errnum);
#include <sys/stat.h>
// struct stat
// time_t

static bool			newInfo(std::string file);
static void			readAndSet(std::string file);
static std::string	trimLine(std::string line, std::string trim);

bool	setEnv(void)
{
	try
	{
		if (newInfo(".env"))
			readAndSet(".env");
		else
			return (false);
	}
	catch(const std::exception& e)
	{
		std::cerr	<< C_RED	<< "Error: "	<< C_RESET
					<< e.what() << ' '	<< strerror(errno)
					<< std::endl;
		return (false);
	}
	return (true);
}

static bool	newInfo(std::string file)
{
	static time_t	last = 0;
	struct stat		fileInfo;

	if (stat(file.c_str(), &fileInfo) != 0)
		throw (std::runtime_error("Failed to read meta-data of " + file + "."));
	if (fileInfo.st_mtime > last)
	{
		last = fileInfo.st_mtime;
		return (true);
	}
	return (false);
}

static void	readAndSet(std::string file)
{
	std::ifstream	fd(file);

	std::cout	<< "Updating env by reading .env file..."	<< std::endl;
	if (!fd.is_open())
		throw (std::runtime_error("Failed to open " + file + "."));

	fd.seekg(0);
	std::string	line;
	while (std::getline(fd, line))
	{
		size_t	delimPos;

		delimPos = line.find('#');
		if (delimPos != std::string::npos)
		{
			line = line.substr(0, delimPos);
			if (line.empty())
				continue ;
		}
		delimPos = line.find('=');
		if (delimPos == std::string::npos)
		{
			std::cerr	<< "Invalid line in "	<< file	<< ": "	<< line	<< std::endl;
			continue;
		}
		std::string	variable = trimLine(line.substr(0, delimPos), " \t");
		std::string	value = trimLine(line.substr(delimPos + 1), " \t");
		if (setenv(variable.c_str(), value.c_str(), 1))
		{
			fd.close();
			throw (std::runtime_error("setenv(): "));
		}
	}
	fd.close();
}

static std::string	trimLine(std::string line, std::string trim)
{
	if (line.empty() || line.find_first_not_of(trim) == std::string::npos)
		return (line);
	line = line.substr(line.find_first_not_of(trim));
	line = line.substr(0, line.find_last_not_of(trim) + 1);
	return (line);
}
