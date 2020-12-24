#include <Stepper.h> //dodajemy do szkicu bibliotekę obsługującą silniki krokowe
#include <IRremote.h>


#define ILOSC_KROKOW 15 //definiujemy stałą gdzie podajemy ilość kroków zależną od użytego silnika w naszym przypadku 32

Stepper mojSilnik(ILOSC_KROKOW, 10, 8, 9, 11); //tutaj podajemy piny w Arduino, którymi sterujemy silnikiem

int ThermistorPin = 1;
int Vo;
int temperaturaC ;
int input_pin = 2; // wpisujemy nazwę pinu, po którym nastepuje komunikacja
int zadanaTemp;

IRrecv irrecv(input_pin);
decode_results signals;

void setup()

{
    Serial.begin(9600);
    mojSilnik.setSpeed(300); //podajemy prędkość obrotu wyrażona w rpm  - do góry
    mojSilnik.step(512); //linijka powoduje obrót ośki silnika o 90 stopni
    mojSilnik.setSpeed(300);
    mojSilnik.step(-300);


    irrecv.enableIRIn(); // włączenie odbierania danych
}

void loop ()

{
/*
mojSilnik.setSpeed(300); //podajemy prędkość obrotu wyrażona w rpm  - do góry

mojSilnik.step(412); //linijka powoduje obrót ośki silnika o 90 stopni

//delay(2000); // linijka powoduje odczekanie 2 sekund (wartosc w milisekundach 1000 = 1s)

mojSilnik.setSpeed(300);

mojSilnik.step(-300);    //nadół

//delay(2000);
*/

 Vo = analogRead(ThermistorPin);

temperaturaC = map(Vo,181,80,0,100); // zmapowane aby obrucić wynik.  
    Serial.print("Temperature:;;;;;; "); 
  Serial.print(temperaturaC);
  Serial.println(" C");  

  delay(2000);


  
if (irrecv.decode(&signals)) {
        Serial.println(signals.decode_type); // typ nadajnika
        Serial.print(F("wynik = 0x"));
        Serial.println(signals.value, HEX); // wynik w systemie szesnatkowym
        Serial.println(signals.bits); // ilość przesłanych danych
        irrecv.blink13(true); // mrugamy diodami w arduino
        
        // Przykładowe porównanie:
        if (signals.value == 0xE0E036C9)    // A
        {
          Serial.println("Wcisnieto klawisz A");
     
        }
           if (signals.value == 0xE0E028D7)    // B
        {
          Serial.println("Wcisnieto klawisz B");
        }
          if (signals.value == 0xE0E0A857)    // C
        {
          Serial.println("Wcisnieto klawisz C");
          mojSilnik.setSpeed(300);
          mojSilnik.step(-300);     //nadół
        }
          if (signals.value == 0xE0E06897)    // D
        
        {
          Serial.println("Wcisnieto klawisz B");
        } 
        

  if (signals.value == 0xE0E0A25D)    // <<
        {
          Serial.println("Wcisnieto klawisz <<");
        }
           if (signals.value == 0xE0E0E21D )    // >
        {
          Serial.println("Wcisnieto klawisz >");
        }
          if (signals.value == 0xE0E052AD)    // ||
        {
          Serial.println("Wcisnieto klawisz ||");
        }
          if (signals.value == 0xE0E012ED)    // >>
        
        {
          Serial.println("Wcisnieto klawisz >>");
        } 















          
        
        
        // ... i tak dalej
        
        irrecv.resume(); // nasłuchujemy na następne nadanie     
    }







}
