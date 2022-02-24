void motore(int x,int y){

int sxa,sxi,dxa,dxi;
int rdx,rsx;


sxa = map(y,150,50,0,1024); // sinistra avanti
sxi = map(y,50,150,0,1024);   // sinistra indietro
dxa = map(y,150,50,0,1024); // destra avanti
dxi = map(y,50,150,0,1024);   // destra indietro
Serial.print("xvalFormat: ");Serial.print(x);Serial.print("yvalFormat: ");Serial.print(y);Serial.println("+++");
Serial.print(" |-| motSXA: "); Serial.print(sxa);Serial.print(" |-| motDXA: "); Serial.print(dxa);Serial.print(" |-| motSXI: "); Serial.print(sxi);Serial.print(" |-| motDXI: "); Serial.print(dxi);

rdx = map(x,50,150,0,1024);   // ruoto a dx
rsx = map(x,150,50,0,1024);     // ruoto a sx

Serial.print("      <-- "); Serial.print(rsx); Serial.print(" --||-- "); Serial.print(rdx); Serial.println(" -->"); 

// se ruoto mentre accellero, sottraggo il valore di rotazione ai motori
sxa = sxa - rsx;
sxi = sxi - rsx;

dxa = dxa - rdx;
dxi = dxi - rdx;


      analogWrite(MotoreSxAvanti, sxa);
      analogWrite(MotoreDxAvanti, dxa);
      analogWrite(MotoreSxIndietro, sxi);
      analogWrite(MotoreDxIndietro, dxi);



}
