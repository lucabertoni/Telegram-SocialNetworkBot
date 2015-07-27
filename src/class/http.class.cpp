#include <curl/curl.h>

#include "http.class.h"

size_t Http::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// Cosa fa			:			Esegue una richiesta di tipo get ad una pagina web ed estrapola il risultato
// sUrl				:			stringa, url al quale effettuare la richiesta
// Ritorna			:			sRet -> stringa, valore di ritorno estratto dalla pagina
string Http::get(string sUrl){

	// Converto il tipo dell'url perchè "curl_easy_setopt(curl, CURLOPT_URL,sUrl" si aspetta che sUrl sia di tipo const char*
	const char *sUrlRequest = sUrl.c_str();
	CURL *curl;
	CURLcode res;
	string sRet;

	curl = curl_easy_init();

	if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL, sUrlRequest);
		curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, this->WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &sRet);
		res = curl_easy_perform(curl);

		curl_easy_cleanup(curl);
	}

	return sRet;
}