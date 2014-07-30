// ParseConfig.cpp

#include "ParseConfig.hpp"

std::vector<std::vector<std::string> > getPids(std::string file)
{
	std::ifstream ifs(file);

	std::string line;
	std::vector<std::string> tokens;
	std::vector<std::vector<std::string> > res;
	while (std::getline(ifs, line))
	{
		boost::split(tokens, line, boost::is_any_of(","));

		for (auto& t : tokens)
			boost::trim(t);
		
		res.push_back(tokens);
	}

return res;
}
