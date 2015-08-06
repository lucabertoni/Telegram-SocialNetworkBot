#include <vector>

#include "facebookApi.class.h"

using namespace std;

#ifndef COMMAND_CLASS_H
#define COMMAND_CLASS_H

struct risposte{
	string start;
	string login;
	string facebookOAuthUrl;
	string help;
	string unknownCommand;
};

class Command
{
	public:
		Command();
		string getMessage(string sKey);
		bool isAllowedCommand(string sComando);
		void setUserId(int nUserId);
	private:
		risposte stRisposte;
		FacebookApi *oApiFB;
		vector<string> aCommandList;
		int nUserId;
};

#endif