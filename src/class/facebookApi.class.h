#include "http.class.h"


using namespace std;

#ifndef FACEBOOKAPI_CLASS_H
#define FACEBOOKAPI_CLASS_H

class FacebookApi
{
	private:
		Http *oHttp;
		string sBaseUrl;
		string sBaseUrlApi;
		string sAppId;
		string sAppSecrete;
		string sOAuthUrl;
	public:
		FacebookApi();
		~FacebookApi();
		string getOAuthUrl(int nUserId);

};

#endif