#include <unistd.h>
#include <iostream>
#include <string>

#include "bot.class.h"
#include "telegram.class.h"
#include "../include/rapidjson/document.h"

using namespace rapidjson;
using namespace std;

Bot::Bot(void){
	oApi = new TelegramBotApi();
	oMessaggio = new Message();
	oDb = new Database();
}

// Cosa fa			:			Controlla se un messaggio è già in coda
// Ritorna			:			bRet -> logico, true se già in coda, altrimenti false
bool Bot::isMessageInCoda(int nMessageId){
	bool bRet;
	bRet = false;
	sql::ResultSet  *res;
	sql::Statement *oStmt;
	sql::Connection *oConn;
	int id;
	
	oConn = this->oDb->getConnection();

	oStmt = oConn->createStatement();
	
	string sSql = "SELECT id from CodaMessaggi where nMessageId="+to_string(nMessageId);
	res = oStmt->executeQuery(sSql);

	if(res->next()){
		bRet = true;
	}
	return bRet;
}

// Cosa fa			:			Controlla se un messaggio è già stato processato
// Ritorna			:			bRet -> logico, true se già in coda, altrimenti false
bool Bot::isMessageProcessato(int nMessageId){
	bool bRet;
	bRet = false;
	sql::ResultSet  *res;
	sql::Statement *oStmt;
	sql::Connection *oConn;
	int id;
	
	oConn = this->oDb->getConnection();

	oStmt = oConn->createStatement();
	
	string sSql = "SELECT id from MessaggiProcessati where nMessageId="+to_string(nMessageId);
	res = oStmt->executeQuery(sSql);

	if(res->next()){
		bRet = true;
	}
	return bRet;
}

// Cosa fa			:			Salva il contenuto di Messaggio nella tabella del database
void Bot::saveMessage(messaggio stMessaggio){
	sql::PreparedStatement  *oStmt;
	sql::Connection *oConn;
	int nMessageId = stMessaggio.message_id;
	bool bIsInCoda;
	bool bIsProcessato;

	bIsInCoda = this->isMessageInCoda(nMessageId);
	bIsProcessato = this->isMessageProcessato(nMessageId);

	if(bIsInCoda or bIsProcessato){
		return;
	}

	oConn = this->oDb->getConnection();
	oStmt = oConn->prepareStatement("INSERT INTO CodaMessaggi(nMessageId,nUserId,sNome,sCognome,sUsername,nDate,sMessage,nChatId) VALUES (?, ?, ?, ?, ?, ?, ?, ?)");

	oStmt->setInt(1, stMessaggio.message_id);
	oStmt->setInt(2, stMessaggio.nUserId);
	oStmt->setString(3, stMessaggio.sNome);
	oStmt->setString(4, stMessaggio.sCognome);
	oStmt->setString(5, stMessaggio.sUsername);
	oStmt->setInt(6, stMessaggio.nDate);
	oStmt->setString(7, stMessaggio.sMessage);
	oStmt->setInt(8, stMessaggio.nChatId);

	oStmt->execute();

	delete oStmt;
	oStmt = NULL;

}

// Cosa fa			:			Esegue un update dei messaggi e poi li inserisce in coda
// Ritorna			:			bRet -> logico, true se tutto ok, altrimenti false
bool Bot::updateQueue(void){
	bool bRet = false;
	string sMessages = this->oApi->getUpdates();
	messaggio stMessaggio;

	// Converto il json in un oggetto DOM per accedere ai vari elementi
	Document oDocument;
	oDocument.Parse(sMessages.c_str());

	if (oDocument["result"].IsArray()){
		Value& aData = oDocument["result"];

		// Per ogni messaggio estraggo i dati che mi servono (vedi struct coda e struct user)
		for(int i = 0; i<aData.Size();i++){
			Value& oResult = aData[i];
			Value& oMessage = oResult["message"];
			Value& oFrom = oMessage["from"];
			Value& oChat = oMessage["chat"];

			// Estraggo l'id del messaggio
			oMessaggio->setMessageId(oMessage["message_id"].GetInt());

			// Estraggo l'id dell'utente
			oMessaggio->setUserId(oFrom["id"].GetInt());

			// Estraggo il nome dell'utente
			oMessaggio->setNome(oFrom["first_name"].GetString());


			// Estraggo il cognome dell'utente
			oMessaggio->setCognome(oFrom["last_name"].GetString());

			// Estraggo il cognome dell'utente (potrebbe non esserci)
			if (oFrom.HasMember("username")){
				oMessaggio->setUsername(oFrom["username"].GetString());
			}

			// Estraggo la data del messaggio e il messaggio
			oMessaggio->setDate(oMessage["date"].GetInt());
			oMessaggio->setMessage(oMessage["text"].GetString());

			// Estraggo l'id della chat
			oMessaggio->setChatId(oChat["id"].GetInt());

			stMessaggio = oMessaggio->getMessaggio();

			// Salvo il messaggio nel db
			this->saveMessage(stMessaggio);
		}

		//cout << aMessage.IsObject();
	}else{
		return bRet;
	}

	//bool bIsMessage = this->isMessage(document);

	bRet = true;
	return bRet;
}

// Cosa fa			:			Estrae un messaggio dalla coda
// Ritorna			:			oRet -> oggetto contenente il messaggio
sql::ResultSet *Bot::getMessageFromCoda(){
	sql::ResultSet  *res;
	sql::Statement *oStmt;
	sql::Connection *oConn;
	
	oConn = this->oDb->getConnection();

	oStmt = oConn->createStatement();
	
	string sSql = "SELECT * from CodaMessaggi where bInLavorazione=0 ORDER BY nMessageId DESC";
	res = oStmt->executeQuery(sSql);

	return res;
}

// Cosa fa			:			Aggiorna lo stato (campo bInLavorazione della tabella) del messaggio in coda
// nMessageId		:			intero, id del messaggio a cui aggiornare lo stato(campo nMessageId della tabella)
// nStatus			:			intero, 0 oppure 1, 0=false(non in lavorazione), 1=true(in lavorazione)
void Bot::setStatusInLavorazione(int nMessageId, int nStatus){
	sql::PreparedStatement  *oStmt;
	sql::Connection *oConn;
	
	oConn = this->oDb->getConnection();
	
	oStmt = oConn->prepareStatement("UPDATE CodaMessaggi SET bInLavorazione=? WHERE nMessageId=?");
	oStmt->setInt(1, nStatus);
	oStmt->setInt(2, nMessageId);
	oStmt->execute();
}

// Cosa fa			:			Elimina un messaggio dalla coda
// nMessageId		:			intero, id del messaggio da cancellare (campo nMessageId nella tabella)
void Bot::deleteMessageFromCoda(int nMessageId){
	sql::PreparedStatement  *oStmt;
	sql::Connection *oConn;
	
	oConn = this->oDb->getConnection();

	oStmt = oConn->prepareStatement("DELETE from CodaMessaggi WHERE nMessageId=?");
	oStmt->setInt(1, nMessageId);
	oStmt->execute();
}

// Cosa fa			:			Fa il parse del messaggio e...
void Bot::parse(string sMessage){
}

// Cosa fa			:			Invia un messaggio ad un utente
// nChatId			:			intero, Id della chat alla quale inviare il messaggio
// sText			:			stringa, testo da inviare
void Bot::sendMessage(int nChatId, string sMessage){
	// Cosa fa			:			Invia un messaggio ad un utente
	// nChatId			:			intero, Id della chat alla quale inviare il messaggio
	// sText			:			stringa, testo da inviare
	this->oApi->sendMessage(nChatId,sMessage);

}

// Cosa fa			:			Aggiunge il messaggio alla tabella dei messaggi già processati
// nMessageId		:			intero, id del messaggio da aggiungere alla tabella dei processati
void Bot::addMessaggioProcessato(int nMessageId){
	sql::PreparedStatement  *oStmt;
	sql::Connection *oConn;
	
	oConn = this->oDb->getConnection();

	oStmt = oConn->prepareStatement("INSERT INTO MessaggiProcessati(nMessageId) VALUES (?)");
	oStmt->setInt(1, nMessageId);
	oStmt->execute();
}

Bot::~Bot(void){
	delete oApi;
	this->oApi = NULL;

	delete oMessaggio;
	this->oMessaggio = NULL;

	delete this->oDb;
	this->oDb = NULL;
}