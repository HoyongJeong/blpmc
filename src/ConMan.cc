////////////////////////////////////////////////////////////////////////////////
//   ConMan.cc
//
//   Definitions of ConMan class's member functions.
// All actions must be initialized here in order to use multi thread.
//
// - Author: Hoyong Jeong     (hoyong5419@korea.ac.kr)
//           Antonino Cannavo (acannavo@bnl.gov      )
////////////////////////////////////////////////////////////////////////////////



//------------------------------------------------------------------------------
// Headers
//------------------------------------------------------------------------------
#include "ConMan.hh"



//------------------------------------------------------------------------------
// Contructor
//------------------------------------------------------------------------------
ConMan::ConMan()
{
}



//------------------------------------------------------------------------------
// Detructor
//------------------------------------------------------------------------------
ConMan::~ConMan()
{
}



//------------------------------------------------------------------------------
// Load conf file
//------------------------------------------------------------------------------
bool ConMan::Load(const std::string& filename)
{
	std::ifstream file(filename);
	if ( !file )
	{
		std::cerr << "Failed to open config file: " << filename << std::endl;
		return false;
	}

	std::string line;
	while ( std::getline(file, line) )
	{
		line = Trim(line);
		// Ignore comments and empty lines
		if ( line . empty() || line[0] == '#' ) continue;

		size_t pos = line . find('=');
		if ( pos == std::string::npos ) continue;

		std::string key   = Trim(line . substr(0, pos) );
		std::string value = Trim(line . substr(pos + 1));

		m_Config[key] = value;
	}

	return true;
}



//------------------------------------------------------------------------------
// Config getter
//------------------------------------------------------------------------------
std::string ConMan::Get(const std::string& key, const std::string& defaultValue) const
{
	auto it = m_Config . find(key);

	return (it != m_Config . end()) ? it -> second : defaultValue;
}



//------------------------------------------------------------------------------
// String trimmer
//------------------------------------------------------------------------------
std::string ConMan::Trim(const std::string& str)
{
	size_t first = str . find_first_not_of(" \t");
	if ( first == std::string::npos ) return "";
	size_t last  = str . find_last_not_of(" \t");
	return str . substr(first, (last - first + 1));
}
