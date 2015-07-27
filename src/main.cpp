#include <iostream>

#include "class/bot.class.h"

using namespace std;

// Cosa fa			:			Estrapola le richieste (messaggi) inviati al bot e le aggiunge in coda
int main(){
	string sJson;
	Bot *oBot = new Bot();
	bool bRet;

	while(true){
		cout << "Aggiorno..." << endl;

		bRet = oBot->updateQueue();

		if(bRet == false){
			cout << "Errore durante l'aggiornamento!" << endl;
		}else{
			cout << "Aggiornato!" << endl;
		}
		cout << "Vado in pausa per 3 secondi..." << endl;
		sleep(3);
	}

	delete oBot;
	return 0;
}