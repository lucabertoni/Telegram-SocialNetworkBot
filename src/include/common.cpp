#include "common.h"

using namespace std;

// Cosa fa			:			Esplode una stringa su un carattere
// s				:			stringa, testo da esplodere
// delim			:			carattere, delimitatore su quale esplodere la stringa
// Ritorna			:			result -> array, array di stringhe esplose
std::vector<std::string> explode(std::string const & s, char delim)
{
    std::vector<std::string> result;
    std::istringstream iss(s);

    for (std::string token; std::getline(iss, token, delim); )
    {
        result.push_back(std::move(token));
    }

    return result;
}

// Cosa fa			:			Verifica se un elemento stringa è presente in un vettore di stringhe
// aVector			:			vettore di stringhe, vettore nel quale cercare l'elemento
// sElement			:			stringa, elemento da cercare nel vettore
// Ritorna			:			bRet -> logico, true se l'elemento è presente nel vettore, altrimenti false
bool isInStringVector(std::vector<string> aVector, string sElement){
	bool bRet = false;
	if(std::find(aVector.begin(), aVector.end() , sElement) != aVector.end()){
		bRet = true;
	}
	return bRet;
}