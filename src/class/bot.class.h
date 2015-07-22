#include "telegram.class.h"
#include "../include/rapidjson/document.h"

using namespace rapidjson;

class Bot
{
	private:
		TelegramBotApi *oApi;
		struct coda
		{
			int message_id;
			int userId;
			string sNome;
			string sCognome;
			string sUsername;
			int nDate;
			string sMessage;
		};
		struct user
		{
			int userId;
			string sNome;
			string sCognome;
			string sUsername;
		};

	public: void costruttore(){
		this->oApi = new TelegramBotApi();
		this->oApi->costruttore();
	}

	// Cosa fa			:			Esegue un update dei messaggi e poi li inserisce in coda
	// Ritorna			:			bRet -> logico, true se tutto ok, altrimenti false
	public: bool updateQueue(){
		bool bRet = false;
		coda stCoda;
		user stUser;

		string sMessages = this->oApi->getUpdates();
		// cout << sMessages << endl;

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
				stCoda.message_id = oMessage["message_id"].GetInt();


				// Estraggo l'id dell'utente
				stCoda.userId = oFrom["id"].GetInt();
				stUser.userId = oFrom["id"].GetInt();

				// Estraggo il nome dell'utente
				stCoda.sNome = oFrom["first_name"].GetString();
				stUser.sNome = oFrom["first_name"].GetString();


				// Estraggo il cognome dell'utente
				stCoda.sCognome = oFrom["last_name"].GetString();
				stUser.sCognome = oFrom["last_name"].GetString();

				// Estraggo il cognome dell'utente
				stCoda.sUsername = oFrom["username"].GetString();
				stUser.sUsername = oFrom["username"].GetString();

				// Estraggo la data del messaggio e il messaggio
				stCoda.nDate = oMessage["date"].GetInt();
				stCoda.sMessage = oMessage["text"].GetString();

/*
				cout << stCoda.message_id << endl;

				cout << stCoda.userId << endl;
				cout << stUser.userId << endl;

				// Estraggo il nome dell'utente
				cout << stCoda.sNome << endl;
				cout << stUser.sNome << endl;


				// Estraggo il cognome dell'utente
				cout << stCoda.sCognome << endl;
				cout << stUser.sCognome << endl;

				// Estraggo il cognome dell'utente
				cout << stCoda.sUsername << endl;
				cout << stUser.sUsername << endl;

				cout << stCoda.nDate << endl;
				cout << stCoda.sMessage << endl;
*/
			}

			//cout << aMessage.IsObject();
		}else{
			return bRet;
		}

		//bool bIsMessage = this->isMessage(document);

		bRet = true;
		return bRet;
	}

	public: void distruttore(){
		this->oApi->distruttore();
		delete oApi;
		this->oApi = NULL;
	}
	
};