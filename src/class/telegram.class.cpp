#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <string>

#include "http.class.h"
#include "telegram.class.h"

using namespace std;

TelegramBotApi::TelegramBotApi(void){
	this->oHttp = new Http();
	this->sUrl = "https://api.telegram.org/bot";
	this->sToken = "108178244:AAFcj19ty1KErq3ndGjnaYgeh_Eo8DbxO5o";
}

// Cosa fa			:			Estrapola i messaggi ricevuti dal bot
// Ritorna			:			sJson -> stringa, json estratto dalla richiesta get (getUpdates)
string TelegramBotApi::getUpdates(void){
	string sFunction,sUrlRequest,sJson;

	sFunction = "/getUpdates";

	sUrlRequest = this->sUrl + this->sToken + sFunction;

	sJson = oHttp->get(sUrlRequest);
	
	return sJson;
}


// Cosa fa			:			Invia un messaggio ad un utente
// nChatId			:			intero, Id della chat alla quale inviare il messaggio
// sText			:			stringa, testo da inviare
void TelegramBotApi::sendMessage(int nChatId, string sText){
	string sFunction,sUrlRequest;

	sFunction = "/sendMessage";

	CURL* curl = curl_easy_init();

	char* testo = curl_easy_escape(curl, sText.c_str(), 0);

	string sTesto = testo;

	cout << "Url:";
	cout << to_string(nChatId) << endl;
	sUrlRequest = this->sUrl + this->sToken + sFunction + "?chat_id="+to_string(nChatId)+"&text="+sTesto;
	cout << sUrlRequest << endl;
	oHttp->get(sUrlRequest);
	
}

TelegramBotApi::~TelegramBotApi(void){
	delete oHttp;
	oHttp = NULL;
}