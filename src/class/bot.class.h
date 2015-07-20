#include "telegram.class.h"
#include "../include/rapidjson/document.h"

using namespace rapidjson;

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

		// Converto il json in un oggetto DOM per accedere ai vari elementi
		Document document;
		document.Parse(sMessages.c_str());

		bool bIsMessage = this->isMessage(document);

		bool bRet = false;

		return bRet;
	}

	public: bool isMessage(Document document){
		cout << "Has:";
		cout << document.HasMember("result") << endl;
		return true;
	}

	public: void distruttore(){
		this->oApi->distruttore();
		delete oApi;
		this->oApi = NULL;
	}
	
};