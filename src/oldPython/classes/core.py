from classes.telegrambot import TelegramBot
import json

class Core():

	dUpdates = dict()

	oTelegramBot = TelegramBot()

	"""Classe che gestisce il cuore del bot, instradando le varie richieste e generando le risposte"""
	def __init__(self):
		pass

	def getUpdates(self):
		"""
			Cosa fa			:			Esegue un update per vedere se ci sono nuovi messaggi
			Ritorna			:			Nulla, imposta self.dUpdates con il contenuto estratto da self.oTelegramBot.getUpdates()
			{"ok":true,"result":[{"update_id":956297541,
			"message":{"message_id":6,"from":{"id":67462525,"first_name":"Luca","last_name":"Bertoni","username":"lucabertoni"},"chat":{"id":67462525,"first_name":"Luca","last_name":"Bertoni","username":"lucabertoni"},"date":1436451392,"text":"Asdf"}},{"update_id":956297542,
			"message":{"message_id":7,"from":{"id":67462525,"first_name":"Luca","last_name":"Bertoni","username":"lucabertoni"},"chat":{"id":67462525,"first_name":"Luca","last_name":"Bertoni","username":"lucabertoni"},"date":1436451400,"text":"Hsjajxnja"}},{"update_id":956297543,
			"message":{"message_id":8,"from":{"id":67462525,"first_name":"Luca","last_name":"Bertoni","username":"lucabertoni"},"chat":{"id":67462525,"first_name":"Luca","last_name":"Bertoni","username":"lucabertoni"},"date":1436451561,"text":"Hajsjqj"}}]}
		"""

		sJson = self.oTelegramBot.getUpdates()

		#dJson = json.loads(sJson)
		#print(dJson)

		print(self.dUpdates)
		
		return