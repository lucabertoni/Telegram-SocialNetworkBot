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
		cout << "Messaggio già presente" << endl;
	}
	return bRet;
}

// Cosa fa			:			Salva il contenuto di Messaggio nella tabella del database
void Bot::saveMessage(messaggio stMessaggio){
	sql::PreparedStatement  *oStmt;
	sql::Connection *oConn;
	int nMessageId = stMessaggio.message_id;
	bool bIsInCoda;

	bIsInCoda = this->isMessageInCoda(nMessageId);

	if(bIsInCoda){
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
//			stUser.userId = oFrom["id"].GetInt();

			// Estraggo il nome dell'utente
			oMessaggio->setNome(oFrom["first_name"].GetString());
//			stUser.sNome = oFrom["first_name"].GetString();


			// Estraggo il cognome dell'utente
			oMessaggio->setCognome(oFrom["last_name"].GetString());
//			stUser.sCognome = oFrom["last_name"].GetString();

			// Estraggo il cognome dell'utente (potrebbe non esserci)
			if (oFrom.HasMember("username")){
				oMessaggio->setUsername(oFrom["username"].GetString());
//				stUser.sUsername = oFrom["username"].GetString();
			}else{
				oMessaggio->setUsername("");
//				stUser.sUsername = "";
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


Bot::~Bot(void){
	delete oApi;
	this->oApi = NULL;

	delete oMessaggio;
	this->oMessaggio = NULL;

	delete this->oDb;
	this->oDb = NULL;
}