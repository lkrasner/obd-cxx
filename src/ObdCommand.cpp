

#include "ObdCommand.hpp"

ObdCommand::ObdCommand(ObdSerial *serial, string n, string c, string function)
{
	name = n;
	command = c;

	obd = serial;
	parser.SetExpr(function);
	parser.DefineVar("A", &A);
	parser.DefineVar("B", &B);
	parser.DefineVar("C", &C);
	parser.DefineVar("D", &D);
}

double ObdCommand::run()
{
	vector<int> vals = obd->sendObdCommand(command);
	if(vals.size() == 0)
	{
		throw -1;
		return -1.0;
	}
	
	else
	{
		A = vals[0];
		B = vals[1];
		C = vals[2];
		D = vals[3];

		return parser.Eval();
	}
}

string ObdCommand::getName()
{
	return name;
}

string ObdCommand::getCommand()
{
	return command;
}
