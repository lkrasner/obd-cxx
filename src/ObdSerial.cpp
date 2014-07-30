/*
 * Luke Krasner (luke@lukekrasner.com)
 *
 * A simple communication library for ELM 327 devices under linux.
 */
#include "ObdSerial.hpp"

using namespace std;

ObdSerial::ObdSerial(const char *port)
{
	fd = openPort(port, B38400);

}

ObdSerial::~ObdSerial()
{
	close(fd);
	cout << "closing" << endl;
}
int ObdSerial::openPort(const char *port, int baudrate)
{
	struct termios options;
	int fd;

	cout << "Opening com port: " << port << endl;

	fd = open(port, O_RDWR | O_NOCTTY | O_NDELAY);

	if(fd == -1)
	{
		cout << "Failed to connect!" << endl;
		return -1;
	}
	else 
	{
		fcntl(fd, F_SETFL, 0);

		// Get the current options for the port
		tcgetattr(fd, &options);
	
		//very important stuff that I absolutely fully understand
		options.c_cflag |= (CLOCAL | CREAD);
		options.c_lflag &= !(ICANON | ECHO | ECHOE | ISIG);
		options.c_oflag &= !(OPOST);
		options.c_cc[VMIN] = 0;
		options.c_cc[VTIME] = 100;

		tcflush(fd, TCIOFLUSH);
		tcsetattr(fd, TCSANOW, &options);

		cfsetispeed(&options, baudrate);
		cfsetospeed(&options, baudrate);
		tcsetattr(fd, TCSANOW, &options);
		tcflush(fd, TCIOFLUSH);
	}
	
	cout << "Connected!" << endl;
	return fd;
}

bool ObdSerial::setup()
{
	sendGenCommand("0100"); //just to make sure buffer is clear
	sendGenCommand("ATZ"); //reset
	sendGenCommand("ATE0"); //disable echo
	sendGenCommand("ATL0"); //disable line feeds
	sendGenCommand("ATS0"); //disable spaces
	sendGenCommand("ATSP0"); //auto mode

	return true;
}


std::string ObdSerial::sendGenCommand(std::string command, bool addReturn)
{
	if(addReturn)
		command += "\r";
	
	write(fd, command.c_str(), command.length());

	char buf[1];
	std::string response = "";

	while(response.back() != '>')
	{
		read(fd, (void*) buf, 1);
		response.append(buf);
	}
	
	return response;
}

std::vector<int> ObdSerial::sendObdCommand(std::string command)
{
	vector<int> res;
	std::string r = sendGenCommand(command);
	r.erase(0, 5); // delete command info
	r.pop_back(); // delete prompt char (">")
	r.pop_back();
	
	for(unsigned int i = 0; i < r.length() - 1; i+=2)
		res.push_back(stoi(r.substr(i,2), nullptr, 16));
	return res;
}
