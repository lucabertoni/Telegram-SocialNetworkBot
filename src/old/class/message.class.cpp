#include <iostream>

#include "message.class.h"

using namespace std;

// Costruttore
Message::Message(void){
	this->Messaggio.message_id = -1;
	this->Messaggio.nUserId = -1;
	this->Messaggio.sNome = "";
	this->Messaggio.sCognome = "";
	this->Messaggio.sUsername = "";
	this->Messaggio.nDate = -1;
	this->Messaggio.sMessage = "";
	this->Messaggio.nChatId = -1;
}

// Cosa fa			:			Aggiorna il valore di message_id
// nMessageId			:			int, valore da associare
void Message::setMessageId(int nMessageId){
	this->Messaggio.message_id = nMessageId;
}

// Cosa fa			:			Aggiorna il valore di userId
// nUserId			:			int, valore da associare
void Message::setUserId(int nUserId){
	this->Messaggio.nUserId = nUserId;
}

// Cosa fa			:			Aggiorna il valore di sNome
// sNome			:			string, valore da associare
void Message::setNome(string sNome){
	this->Messaggio.sNome = sNome;
}

// Cosa fa			:			Aggiorna il valore di sCognome
// sCognome			:			string, valore da associare
void Message::setCognome(string sCognome){
	this->Messaggio.sCognome = sCognome;
}

// Cosa fa			:			Aggiorna il valore di sUsername
// sUsername			:			string, valore da associare
void Message::setUsername(string sUsername){
	this->Messaggio.sUsername = sUsername;
}

// Cosa fa			:			Aggiorna il valore di nDate
// nDate			:			int, valore da associare
void Message::setDate(int nDate){
	this->Messaggio.nDate = nDate;
}

// Cosa fa			:			Aggiorna il valore di sMessage
// sMessage			:			string, valore da associare
void Message::setMessage(string sMessage){
	this->Messaggio.sMessage = sMessage;
}

// Cosa fa			:			Aggiorna il valore di nChatId
// nChatId			:			int, valore da associare
void Message::setChatId(int nChatId){
	this->Messaggio.nChatId = nChatId;
}

// Cosa fa			:			Estrapola il messaggio (l'intera struttura)
// Ritorna			:			struct messaggio -> struttura messaggio contenente tutti i dati
messaggio Message::getMessaggio(){
	return this->Messaggio;
}

// Distruttore
Message::~Message(void){
}