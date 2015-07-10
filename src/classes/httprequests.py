import requests

class HttpRequests():
	"""Classe che gestisce le richieste Http"""
	def __init__(self):
		pass

	def post(self,sLink,dArg=dict()):
		"""
			Cosa fa			:			Effettua una richiesta di tipo post ad un indirizzo
			sLink			:			stringa, link al quale eseguire la richiesta di post
			dArg			:			dizionario, contiene eventuali parametri da passare, es:
										dArg["name"] = 'Luca'
			Ritorna			:			sRet -> stringa, valore ritornato dalla richiesta effettuata alla pagina
		"""
		sRet = ''

		oRequest = requests.get(sLink, params=dArg)
		sRet = oRequest.text
		
		return sRet