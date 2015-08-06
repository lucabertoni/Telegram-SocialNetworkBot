#include <curl/curl.h>
#include <string>
#include <cstddef>

using namespace std;

#ifndef HTTP_CLASS_H
#define HTTP_CLASS_H

// Classe che gestisce le richieste http
class Http
{

	private:
		static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
	public:
		string get(string sUrl);	
};

#endif