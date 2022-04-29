//Libreria pantalla LCD 16X2
#include<LiquidCrystal.h>

//Definimos los pines de comunicacion
LiquidCrystal lcd(12,11,10,9,8,7);

int Temporizador1;
int Temporizador2;

float Tiempo;

int Bandera_A = 0;
int Bandera_B = 0;

//Metros 
float Distancia = 0.16;
//float Distancia = 16.0;


float Velocidad;

int Inflarrojo_1 = 2;
int Inflarrojo_2 = 3;

int buzzer = 4;

void setup(){
  Serial.begin(9600);
  Serial.println("hola");
  pinMode(Inflarrojo_1, INPUT);
  pinMode(Inflarrojo_2, INPUT);
  pinMode(buzzer, OUTPUT);
  
  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(0,0);

  lcd.print("Proy Integrador ");
  lcd.setCursor(0,1);
  lcd.print("LIDTS 4N");
  delay(2000);

  lcd.setCursor(0,0);
  lcd.print(" ---Gilberto--- ");
  lcd.setCursor(0,1);
  lcd.print(" ---Salvador--- ");
  delay(2000);

  lcd.setCursor(0,0);
  lcd.print("  ---Bryan---  ");
  lcd.setCursor(0,1);
  lcd.print("  ---Alexis---  ");
  delay(2000);

  lcd.clear();
}

void loop() {
if(digitalRead (Inflarrojo_1) == LOW && Bandera_A==0){Temporizador1 = millis(); Bandera_A=1;}

if(digitalRead (Inflarrojo_2) == LOW && Bandera_B==0){Temporizador2 = millis(); Bandera_B=1;}

if (Bandera_A==1 && Bandera_B==1){
     if(Temporizador1 > Temporizador2){Tiempo = Temporizador1 - Temporizador2;}
else if(Temporizador2 > Temporizador1){Tiempo = Temporizador2 - Temporizador1;}
 Tiempo=Tiempo/1000;//Convierte de milisegundos a segundos
 Velocidad=(Distancia/Tiempo);//Formula velocidad --> v=d/t
 
 Velocidad=Velocidad*3600;//Multiplicar segundos por hora
 Velocidad=Velocidad/1000;//Dividir metros por kilometro
}

if(Velocidad==0){ 
lcd.setCursor(0, 1); 
if(Bandera_A==0 && Bandera_B==0){lcd.print("No hay nada.....");}
                    else{lcd.print("Buscando...     ");} 
}
else{
    lcd.clear(); 
    lcd.setCursor(0, 0); 
    lcd.print("V =");
    lcd.print(Velocidad,1);
    lcd.print("Km/H  ");
    lcd.setCursor(0, 1); 
  if(Velocidad > 50){lcd.print("Exceso Velocidad"); digitalWrite(buzzer, HIGH);}
            else{lcd.print("Velocidad Normal"); }    
    delay(3000);
    digitalWrite(buzzer, LOW);
    Velocidad = 0;
    Bandera_A = 0;
    Bandera_B = 0;    
 }
}
