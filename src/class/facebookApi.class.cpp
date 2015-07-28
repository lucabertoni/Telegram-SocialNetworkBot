#include <string>

#include "facebookApi.class.h"
#include "http.class.h"

using namespace std;

FacebookApi::FacebookApi(void){
	this->oHttp = new Http();
	this->sBaseUrl = "https://www.facebook.com";
	this->sBaseUrlApi = "https://graph.facebook.com";
	this->sAppId = "1472234743092947";
	this->sAppSecrete = "0b1c5e4da8eebce7c6e79be19ffd762c";
	this->sOAuthUrl = "https://www.facebook.com/dialog/oauth?client_id="+this->sAppId+"&response_type=code&redirect_uri=http://socialnetworkbot.altervista.org/getFacebookApiCode.php?id=";
}

// Cosa fa			:			Genera l'url per autenticare l'app su Facebook
// nUserId			:			intero -> id (di telegram) dell'utente del quale generare l'autenticazione'
// Ritorna			:			sAuthUrl -> stringa, url per effetuare l'autenticazione dell'app
string FacebookApi::getOAuthUrl(int nUserId){
	string sAuthUrl = this->sOAuthUrl+to_string(nUserId);
	return sAuthUrl;
}
