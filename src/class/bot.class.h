#include "telegram.class.h"

class Bot
{
	private:
		TelegramBotApi *oApi;

	public: void costruttore(){
		this->oApi = new TelegramBotApi();
		this->oApi->costruttore();
	}

	// Cosa fa			:			Esegue un update dei messaggi e poi li inserisce in coda
	// Ritorna			:			bRet -> logico, true se tutto ok, altrimenti false
	public: bool updateQueue(){
		string sMessages = this->oApi->getUpdates();
		cout << sMessages << endl;
		bool bRet = false;
		return bRet;
	}

	public: void distruttore(){
		this->oApi->distruttore();
		delete oApi;
		this->oApi = NULL;
	}
	
};