#include "facebookApi.class.h"

using namespace std;

#ifndef MESSAGES_CLASS_H
#define MESSAGES_CLASS_H

struct risposte{
	string start;
	string login;
	string facebookOAuthUrl;
	string help;
	string unknownCommand;
};

class Messages
{
	public:
		Messages(int nUserId);
		string getMessage(string sKey);
	private:
		risposte stRisposte;
		FacebookApi *oApiFB;
};

#endif