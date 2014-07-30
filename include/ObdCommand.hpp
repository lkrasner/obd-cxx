/*
 * @author Luke Krasner (luke@lukekrasner.com)
 *
 * @class ObdCommand
 * @brief Class to represent a single runnable OBD-II command
 * @details the key to this class is the fact that the constructor takes a
 * pointer to an ObdSerial object.  this allows for very tight memory
 * management and keeps code clean.  An Obd command is runnable, so getting the
 * result is as simple as calling run() assuming the proper functio is given.
 * muparser should handle any function you need for custom commands.
 */
#ifndef OBDCOMMAND_HPP
#define OBDCOMMAND_HPP

#include <muParser.h>
#include "ObdSerial.hpp"

using namespace std;

class ObdCommand
{
public:
	/*
	 * @brief Constructor to initialize an ObdCommand
	 * @param *serial Ptr to an existing ObdSerial object for communication
	 * @param n Human readable name of command
	 * @param c String of command to send
	 * @param function String representation of command used to parse result
	 */
	ObdCommand(ObdSerial *serial, string n, string c, string function);

	/*
	 * @brief sends the command, parses the result and returns
	 * @return the parsed result
	 */
	double run();

	string getName();

	string getCommand();

private:
	string name;

	string command;

	mu::Parser parser;

	ObdSerial *obd;

	double A, B, C, D; //vars to hold response bytes
};

#endif
