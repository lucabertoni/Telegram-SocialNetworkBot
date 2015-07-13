#!/usr/bin/python3
from classes.core import Core
from time import sleep

oCore = Core()


# Estraggo i messaggi in arrivo...
while True:
	print("Aggiorno...\n")
	oCore.getUpdates()
	print("\n\nAggiornato, vado in pausa per 3 secondi...\n\n")
	sleep(3)
