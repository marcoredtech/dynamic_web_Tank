Ciao a tutti, in questa prima prima versione ho inserito il codice per pilotare un mezzo cingolato tramite un Joystick visualizzabile tramite un browser.

Il principio di funzionamento è il seguente:

Joystick su web Browser [invio tramite header GET i dati]
Ricevo i dati tramite il web server async installato su di un microcontrollore (ESP8266)
Decodifico i dati (coordinate X e Y) e le elaboro per poter mandare i comandi ai motori

## Materiale:
