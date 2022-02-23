Ciao a tutti, in questa prima prima versione ho inserito il codice per pilotare un mezzo cingolato tramite un Joystick visualizzabile tramite un browser.

Il principio di funzionamento è il seguente:

Joystick su web Browser [invio tramite header GET i dati]
Ricevo i dati tramite il web server async installato su di un microcontrollore (ESP8266)
Decodifico i dati (coordinate X e Y) e le elaboro per poter mandare i comandi ai motori

## Materiale:


- ESP8266
- Driver motori LM298
- Batteria superiore ai 7V, massimo 12v
- Dc-Dc step down (alimentazione del micro 3.3v o 5v)
- Pezzi cingolato e motori, suggerisco: [cingolato giocattolo](https://it.banggood.com/3V-9V-DIY-Shock-Absorbed-Smart-Robot-Tank-Chassis-Crawler-Car-Kit-With-260-Motor-p-1184648.html?rmmds=myorder&cur_warehouse=CN)
