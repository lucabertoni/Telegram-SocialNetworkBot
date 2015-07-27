#include "telegram.class.h"
#include "../include/rapidjson/document.h"
#include <unistd.h>

using namespace rapidjson;

#ifndef BOT_CLASS_H
#define BOT_CLASS_H

class Bot
{
	public:
		Bot();
		~Bot();

	public:
		bool updateQueue();

	private:
		TelegramBotApi *oApi;
		struct coda
		{
			int message_id;
			int userId;
			string sNome;
			string sCognome;
			string sUsername;
			int nDate;
			string sMessage;
			int nChatId;
		};
		struct user
		{
			int userId;
			string sNome;
			string sCognome;
			string sUsername;
		};
};

#endif