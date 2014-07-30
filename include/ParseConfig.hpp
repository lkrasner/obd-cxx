/*
 * parses a simple config file of Commands
 */

#ifndef PARSECONFIG__HPP
#define PARSERCONFIG_HPP

#include <fstream>
#include <vector>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/trim.hpp>

std::vector<std::vector<std::string> > getPids(std::string file);

#endif
