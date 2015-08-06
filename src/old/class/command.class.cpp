#include "command.class.h"
#include "facebookApi.class.h"
#include "../include/common.h"

using namespace std;

Command::Command(){
	// Imposto di defaul che l'id dell'utente che ha in uso la sessione è 0
	nUserId = 0;

	// Creo il vettore con la lista di comandi ammessi
	this->aCommandList.push_back("/start");
	this->aCommandList.push_back("/login");
	this->aCommandList.push_back("/help");

	// Associo ad un comando la sua guida
	this->oApiFB = new FacebookApi();
	this->stRisposte.start = "Welcome in SocialNetworkBot. Use /help to see what command you can use.";
	this->stRisposte.login = "/login <social-network-name>\nLogin into your social network using this command followed by SocialNetwork name (ex: facebook,twitter...)";
	this->stRisposte.facebookOAuthUrl = "Click on the following link to authenticate this app in Facebook "+this->oApiFB->getOAuthUrl(this->nUserId);
	this->stRisposte.unknownCommand = "This is an unknown command, please read the manual using /help command";
}

// Cosa fa			:				Estrapola il messaggio associato ad una determinata chiave, per poi essere usato
//									nei metodi che utilizzano questa classe (es: quello per inviare i messaggi all'utente)
// Ritorna			:				
string Command::getMessage(string sKey){
	if(sKey == "start") return this->stRisposte.start;
	else if(sKey == "login") return this->stRisposte.login;
	else if(sKey == "facebookOAuthUrl") return this->stRisposte.facebookOAuthUrl;
	else if(sKey == "unknownCommand") return this->stRisposte.unknownCommand;
	else return this->stRisposte.unknownCommand;
}

// Cosa fa			:			Controlla se il comando è valido (se è presente nel vettore con la lista dei comandi)
// sComando			:			stringa, comando, es: /start oppure /login
// Ritorna			:			bRet -> true se il comando è ammesso, altrimenti false
bool Command::isAllowedCommand(string sComando){
	bool bRet = false;
	// Cosa fa			:			Verifica se un elemento stringa è presente in un vettore di stringhe
	// aVector			:			vettore di stringhe, vettore nel quale cercare l'elemento
	// sElement			:			stringa, elemento da cercare nel vettore
	// Ritorna			:			bRet -> logico, true se l'elemento è presente nel vettore, altrimenti false
	if(isInStringVector(this->aCommandList, sComando)){
		bRet = true;
	}
	return bRet;
}

// Cosa fa			:			Imposta l'id dell'utente che ha in uso la "sessione"
void Command::setUserId(int nUserId){
	this->nUserId = nUserId;
}