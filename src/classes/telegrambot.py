import classes.httprequests

class TelegramBot():
	"""Classe che gestisce le connessioni con le api dei bot di Telegram"""

	# Token di accesso alle api
	sToken = '108178244:AAFcj19ty1KErq3ndGjnaYgeh_Eo8DbxO5o'

	# Link di accesso alle api
	sLink = 'https://api.telegram.org/bot'+sToken+'/'

	# Oggetto per gestire le connessioni Http
	oHttp = classes.httprequests.HttpRequests()
	
	def __init__(self):
		pass

	def getUpdates(self):
		"""
			Cosa fa			:			Esegue un update per vedere se ci sono nuovi messaggi
			Ritorna			:			sRet -> stringa, json generato dalle api telegram, es:
			{"ok":true,"result":[{"update_id":956297541,
			"message":{"message_id":6,"from":{"id":67462525,"first_name":"Luca","last_name":"Bertoni","username":"lucabertoni"},"chat":{"id":67462525,"first_name":"Luca","last_name":"Bertoni","username":"lucabertoni"},"date":1436451392,"text":"Asdf"}},{"update_id":956297542,
			"message":{"message_id":7,"from":{"id":67462525,"first_name":"Luca","last_name":"Bertoni","username":"lucabertoni"},"chat":{"id":67462525,"first_name":"Luca","last_name":"Bertoni","username":"lucabertoni"},"date":1436451400,"text":"Hsjajxnja"}},{"update_id":956297543,
			"message":{"message_id":8,"from":{"id":67462525,"first_name":"Luca","last_name":"Bertoni","username":"lucabertoni"},"chat":{"id":67462525,"first_name":"Luca","last_name":"Bertoni","username":"lucabertoni"},"date":1436451561,"text":"Hajsjqj"}}]}
		"""
		sRet = ''
		sLink = self.sLink+'getUpdates'
		sRet = self.oHttp.post(sLink)
		
		return sRet