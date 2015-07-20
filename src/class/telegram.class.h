#include "http.class.h"

using namespace std;

// Classe che gestisce le richieste alle api per i bot di telegram
class TelegramBotApi
{
	private:
		Http *oHttp;
		string sUrl;
		string sToken;

	public: void costruttore(){
		this->oHttp = new Http();
		this->sUrl = "https://api.telegram.org/bot";
		this->sToken = "108178244:AAFcj19ty1KErq3ndGjnaYgeh_Eo8DbxO5o";
	}

	// Cosa fa			:			Estrapola i messaggi ricevuti dal bot
	// Ritorna			:			sJson -> stringa, json estratto dalla richiesta get (getUpdates)
	public: string getUpdates(){
		string sFunction,sUrlRequest,sJson;

		sFunction = "/getUpdates";

		sUrlRequest = this->sUrl + this->sToken + sFunction;

		sJson = oHttp->get(sUrlRequest);
		
		return sJson;
	}

	public: void distruttore(){
		delete oHttp;
		oHttp = NULL;
	}
};