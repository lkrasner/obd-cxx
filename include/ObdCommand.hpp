/*
 * Luke Krasner (luke@lukekrasner.com)
 *
 * Represents an instance of an obdCommand
 */
#ifndef OBDCOMMAND_HPP
#define OBDCOMMAND_HPP

#include <muParser.h>
#include "ObdSerial.hpp"

using namespace std;

class ObdCommand
{
public:
	ObdCommand(ObdSerial *serial, string n, string c, string function);


	double run();

	string getName();

	string getCommand();

private:
	string name;

	string command;

	mu::Parser parser;

	ObdSerial *obd;

	double A, B, C, D;
};

#endif
