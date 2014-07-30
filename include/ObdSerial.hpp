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
	ObdSerial(const char *port);

	~ObdSerial();
	/*
	 * @brief opens a com port to talk to the ELM327 device
	 * @param port path to com port
	 * @param baudrate desired communicatin speed
	 * @return fd on success or -1 on failure
	 */
	int openPort(const char *port, int baudrate);

	bool setup();

	std::string sendGenCommand(std::string command, bool addReturn = true);

	std::vector<int> sendObdCommand(std::string command);
	
	std::string getProtocol();

private:
	int fd;
};

#endif
