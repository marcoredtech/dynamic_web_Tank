![photo_2022-02-25_08-41-41](https://user-images.githubusercontent.com/44021742/155675168-04c24b46-b71e-421e-b997-57af2e202cdb.jpg)


Ciao a tutti, in questa prima versione ho inserito il codice per pilotare un mezzo cingolato tramite un Joystick visualizzabile tramite un browser.

Il principio di funzionamento è il seguente:

- Joystick su web Browser [invio tramite header GET i dati]
- Ricevo i dati tramite il web server async installato su di un microcontrollore (ESP8266)
- Decodifico i dati (coordinate X e Y) e le elaboro per poter mandare i comandi ai motori

## Materiale:


- ESP8266
- Driver motori LM298
- Batteria superiore ai 7V, massimo 12v
- Dc-Dc step down (alimentazione del micro 3.3v o 5v)
- Pezzi cingolato e motori, suggerisco: [cingolato giocattolo](https://it.banggood.com/3V-9V-DIY-Shock-Absorbed-Smart-Robot-Tank-Chassis-Crawler-Car-Kit-With-260-Motor-p-1184648.html?rmmds=myorder&cur_warehouse=CN)

## Librerie

- [web server async](https://github.com/me-no-dev/ESPAsyncWebServer)
- [ESPAsyncTCP](https://github.com/me-no-dev/ESPAsyncTCP)
- [Plug-in per lo SPIFF](https://github.com/esp8266/arduino-esp8266fs-plugin/releases) , ti consiglio di leggere questa guida molto ben fatta di [Renzo Mischianti](https://www.mischianti.org/it/2019/08/30/wemos-d1-mini-esp8266-sistema-operativo-integrato-spiffs-parte-2/) da cui ho preso numerosi spunti e ringrazio.

## Interfaccia grafica

Come Joystik ho usato quello creato da Roberto D'Amico 
https://github.com/bobboteck/JoyStick 

![image](https://user-images.githubusercontent.com/44021742/155380700-e82b2d04-7dc6-47b7-b091-1b8cc5ef1045.png)

il codice essenziale utilizzato per inviare i dati dal Joystick verso il server tramite il metodo GET è il seguente: 

````
    if ( letsDoIt ) {
      letsDoIt = false;
      fetch("/index?X="+joy1IinputPosX.value+"&Y="+joy1InputPosY.value).then( () => {
        letsDoIt = true;
      })
    }
    
````

In questo caso è un semaforo, una volta inviati i dati è sufficiente rispondere con qualunque informazione.

## Software microcontrollore

Il codice di risposta sull'ESP8266 che da adesso chiameremo uP è il seguente:

````
// richiesta di esempio personalizzata di prova
  httpServer.on("/index", HTTP_GET, [](AsyncWebServerRequest *request){    
    String inputMessage1;
    String inputMessage2;
      if (request->hasParam(input_parameter1) && request->hasParam(input_parameter2)) {
        inputMessage1 = request->getParam(input_parameter1)->value();
        inputMessage2 = request->getParam(input_parameter2)->value();
        Serial.println("X pos: " + inputMessage1 + " Y pos: " + inputMessage2);
        motore(inputMessage1.toInt(),inputMessage2.toInt());
        request->send(200, "text/plain", "next");
      }
    });
`````


````
httpServer.on("/index", HTTP_GET, [](AsyncWebServerRequest *request){
````
- Tutto quello che mi arriva su index come GET viene catturato e recuperato in request.
- Dopodichè vado a recuperare le informazioni all'interno attraverso alla funzione 'getParam()' che fa un parser del valore inserito nella stringa input_paramaterX
- All'interno di questa funzione ho anche l'azione che vado a compiere immediatamente dopo aver ricevuto l'informazione utilizzando la funzione motore()
- Al termine invio una risposta 'request->send(200, "text/plain", "next");'

Perchè invio una risposta in un sistema Async? il problema in fase di progettazione lo ho avuto nel momento che il browser inviava una mole di GET superiori a quelli che avrei potuto gestire con il uP.


Un altra parte importante del progetto è il caricamento dei dati sul uP nella flash, questo argomento è facilmente ricercabile in rete,ma per semplificare inserisco questo link:
https://arduino-esp8266.readthedocs.io/en/latest/filesystem.html#uploading-files-to-file-system
Altro non è che la guida ufficiale, ma se avete difficoltà basta guardare su youtube i numerosi documenti, ma i passaggi sono abbastanza semplici.

## Circuito elettrico

Schema stile Paint XD
![image](https://user-images.githubusercontent.com/44021742/155512256-6e49583c-c060-4e82-8204-c67af4bd0586.png)


## Ringraziamenti speciali

- Ringrazio il gruppo su telegram di Arduino italia https://t.me/ArduinoItalia
- Ringrazio il gruppo su telegram di Javascript https://t.me/javascript_ita in modo particolare l'utente @fatshotty autore della funzione alla base dell'invio dei dati sullo script js.
- Ringrazio [Renzo Mischianti](https://www.mischianti.org) per i numerosi spunti che ho appreso leggendo il suo sito.


![photo_2022-02-25_08-41-44](https://user-images.githubusercontent.com/44021742/155675296-d49b774f-4346-4831-878e-06537b89680d.jpg)
![photo_2022-02-25_08-41-38](https://user-images.githubusercontent.com/44021742/155675319-0c47770b-1286-4cf7-916d-92141adc93bc.jpg)
![photo_2022-02-25_08-41-34](https://user-images.githubusercontent.com/44021742/155675343-2bae2be2-4cc6-4639-ad36-f1185c7e89bb.jpg)


