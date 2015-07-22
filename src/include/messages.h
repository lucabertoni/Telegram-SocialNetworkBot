#include <iostream>
#include <map>

using namespace std;

class Messages
{
	public:
		string getMessage(string sKey);
		map<string, string> messages;
};

