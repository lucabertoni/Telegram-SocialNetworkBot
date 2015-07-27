/*
	Demone che gestisce i messaggi in coda
*/

#include "class/bot.class.h"
#include <iostream>

using namespace std;

int main(){
	Bot *oBot;
	oBot = new Bot();
	sql::ResultSet *res;
	int nMessageId;
	string sMessage;

	while(true){
		cout << "Estraggo messaggio dalla coda..." << endl;
		res = oBot->getMessageFromCoda();
		if(res->next()){
			cout << "Messaggio estratto" << endl;
			nMessageId = res->getInt("nMessageId");
			sMessage = res->getString("sMessage");

			// Cosa fa			:			Aggiorna lo stato (campo bInLavorazione della tabella) del messaggio in coda
			// nMessageId		:			intero, id del messaggio a cui aggiornare lo stato(campo nMessageId della tabella)
			// nStatus			:			intero, 0 oppure 1, 0=false(non in lavorazione), 1=true(in lavorazione)
			oBot->setStatusInLavorazione(nMessageId, 1);
			oBot->parse(sMessage);
		}else{
			cout << "Coda vuota o tutti i messaggi già in lavorazione" << endl;
		}
		cout << "Riposo per 3 secondi..." << endl;
		sleep(3);
	}

}