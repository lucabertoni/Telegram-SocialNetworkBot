#include "messages.class.h"
#include "facebookApi.class.h"

using namespace std;

Messages::Messages(int nUserId){
	this->oApiFB = new FacebookApi();
	this->stRisposte.start = "Welcome in SocialNetworkBot. Use /help to see what command you can use.";
	this->stRisposte.login = "/login social-network-name\nLogin into your social network using this command followed by SocialNetwork name (ex: facebook,twitter...)";
	this->stRisposte.facebookOAuthUrl = "Click on the following link to authenticate this app in Facebook "+this->oApiFB->getOAuthUrl(nUserId);
	this->stRisposte.unknownCommand = "This is an unknown command, please read the manual using /help command";
}

// Cosa fa			:				Estrapola il messaggio associato ad una determinata chiave, per poi essere usato
//									nei metodi che utilizzano questa classe (es: quello per inviare i messaggi all'utente)
string Messages::getMessage(string sKey){
	if(sKey == "start") return this->stRisposte.start;
	else if(sKey == "login") return this->stRisposte.login;
	else if(sKey == "facebookOAuthUrl") return this->stRisposte.facebookOAuthUrl;
	else return this->stRisposte.unknownCommand;
}