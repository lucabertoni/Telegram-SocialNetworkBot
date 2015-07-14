import urllib.request
import json

class HttpRequests():
	"""Classe che gestisce le richieste Http"""
	def __init__(self):
		pass

	def get(self,sLink,dArg=dict()):
		"""
			Cosa fa			:			Effettua una richiesta di tipo get ad un indirizzo
			sLink			:			stringa, link al quale eseguire la richiesta di get,
										es: https://api.telegram.org/bot108178244:AAFcj19ty1KErq3ndGjnaYgeh_Eo8DbxO5o/getUpdates
			dArg			:			dizionario, contiene eventuali parametri da passare, es:
										dArg["name"] = 'Luca'
			Ritorna			:			sRet -> stringa, valore ritornato dalla richiesta effettuata alla pagina (json)
		"""
		sRet = ''

		data = json.dumps(dArg)

		# Stabilisco una connessione con l'host
		oResponse = urllib.request.urlopen(sLink)

		bJson = oResponse.read()

		return sRet