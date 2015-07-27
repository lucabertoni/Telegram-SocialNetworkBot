#include <stdlib.h>
#include <unistd.h>
#include "http.class.h"

using namespace std;

#ifndef TELEGRAM_CLASS_H
#define TELEGRAM_CLASS_H
// Classe che gestisce le richieste alle api per i bot di telegram
class TelegramBotApi
{
	private:
		Http *oHttp;
		string sUrl;
		string sToken;

	public:
		TelegramBotApi();
		~TelegramBotApi();
		string getUpdates();
		void sendMessage(int nChatId, string sText);
};

#endif