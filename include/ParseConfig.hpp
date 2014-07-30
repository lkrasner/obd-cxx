//ParseConfig.hpp

/*
 * @author Luke Krasner (luke@lukekrasner.com)
 * @brief parses a simple config file of Commands
 * @details OBD-II command sould be detailed in a simple config file. each line
 * represents one command. each command shoud be a comma seperated list (with
 * or without spaces) of the name command and function in that order
 * @see the incuded example
 */

#ifndef PARSECONFIG_HPP
#define PARSECONFIG_HPP

#include <fstream>
#include <vector>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/trim.hpp>

/*
 * @brief parses a config file and returns a vector of vectors of commands
 * @details each outer element is one command containing inner elements
 * <name, command, function>
 * @param file path to config file
 * @return double vectore of commands
 */
std::vector<std::vector<std::string> > getPids(std::string file);

#endif
