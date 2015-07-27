#include "telegram.class.h"
#include "../include/rapidjson/document.h"
#include <unistd.h>
#include "message.class.h"
#include "database.class.h"

using namespace rapidjson;
using namespace std;

#ifndef BOT_CLASS_H
#define BOT_CLASS_H

class Bot
{
	public:
		Bot();
		~Bot();

	public:
		bool updateQueue();
		sql::ResultSet *getMessageFromCoda();
		void setStatusInLavorazione(int nMessageId, int nStatus);
		void deleteMessageFromCoda(int nMessageId);
		void parse(string sMessage);
		void addMessaggioProcessato(int nMessageId);
		void sendMessage(int nChatId, string sMessage);
		bool isMessageProcessato(int nMessageId);

	private:
		TelegramBotApi *oApi;
		Message *oMessaggio;
		Database *oDb;
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
		bool isMessageInCoda(int nMessageId);
		void saveMessage(messaggio oMessaggio);
};

#endif