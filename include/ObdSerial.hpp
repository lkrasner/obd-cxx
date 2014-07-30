/*
 * Luke Krasner (luke@lukekrasner.com)
 *
 * A simple communication library for ELM 327 devices under linux.
 */

#ifndef OBDSERIAL_HPP
#define OBDSERIAL_HPP

#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>
#include <stdlib.h>
#include <iomanip>
#include <unistd.h>
#include <vector>

class ObdSerial
{
public:	
	/*
	 * @brief Constructs a new ObdSerial using given com port
	 * @param port name of port to connect to
	 */
	ObdSerial(const char *port);

	~ObdSerial();
	/*
	 * @brief opens a com port to talk to the ELM327 device
	 * @param port path to com port
	 * @param baudrate desired communicatin speed
	 * @return fd on success or -1 on failure
	 */
	int openPort(const char *port, int baudrate);

	/*
	 * @brief sends a raw command and returns a string of the result
	 * @param command the command to send
	 * @param addReturn set to false to skip adding a carriage return to
	 * the end
	 * @return string of result
	 */
	std::string sendGenCommand(std::string command, bool addReturn = true);

	/*
	 * @brief sends a command and returns a vector of ints representing
	 * each byte returned. should only be used for OBD commands (not AT
	 * commands)
	 * @see sendGenCommand
	 * @param command command to send
	 * @return vector of resulting ints
	 */
	std::vector<int> sendObdCommand(std::string command);

	/*
	 * @brief asks the ELM device what OBD-II protocol is being used
	 * @return the protocol
	 */
	std::string getProtocol();

private:
	/*
	 * @brief sends some basic setup commands
	 * @return true if success, else false
	 */
	bool setup();

	int fd; //file descriptor for the serial port
};

#endif
