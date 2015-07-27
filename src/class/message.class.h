#include <string>

using namespace std;

struct messaggio
{
	int message_id;
	int nUserId;
	string sNome;
	string sCognome;
	string sUsername;
	int nDate;
	string sMessage;
	int nChatId;
};

#ifndef MESSAGE_CLASS_H
#define MESSAGE_CLASS_H

class Message
{
	public:
		Message();
		~Message();
		messaggio Messaggio;
		void setMessageId(int nMessageId);
		void setUserId(int nUserId);
		void setNome(string sNome);
		void setCognome(string sCognome);
		void setUsername(string sUsername);
		void setDate(int nDate);
		void setMessage(string sMessage);
		void setChatId(int nChatId);
		messaggio getMessaggio();
};

#endif