#include <LiquidCrystal.h>
#include <DHT.h>

#define dht11 A2
#define DHTTYPE DHT11

DHT dht(dht11, DHTTYPE);

#define MQ135_PIN A0
#define MQ7_PIN A1

int fan = 6;
int buzzer = 7;
int heart = 8;

LiquidCrystal lcd(0, 1, 5, 4, 3, 2);

int mq135Value;
int mq7Value;
float voltageMQ135;
float voltageMQ7;
float amonyak;
float temp,hum; 

void setup() {

  

  pinMode(MQ135_PIN, INPUT);
  pinMode(MQ7_PIN, INPUT);
  pinMode(fan, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(heart, OUTPUT);
  lcd.begin(20,4);
  lcd.print("Hos Geldiniz");
  delay(500);
  lcd.clear();
  dht.begin();

  

}

void loop() {
    

    mq135Value = analogRead(MQ135_PIN);
    mq7Value = analogRead(MQ7_PIN);

    voltageMQ135 = mq135Value * (5.0 / 1023.0);
    voltageMQ7 =  mq7Value * (100.0 / 1023.0);

    amonyak = calculateNH3Concentration(voltageMQ135);

    if(voltageMQ7 > 50 || temp > 21)
    {
        digitalWrite(fan, HIGH);
        digitalWrite(buzzer, HIGH);
    }else
    {
        digitalWrite(fan, LOW);
        digitalWrite(buzzer, LOW);
    }
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Amanyok : ");
    lcd.print(amonyak);
    lcd.print(" ppm");
    lcd.setCursor(0, 1);
    
    lcd.print("CO : ");
    lcd.print(voltageMQ7);
    lcd.print(" ppm");

    lcd.setCursor(0, 2);
    hum = dht.readHumidity();
    temp = dht.readTemperature();
    lcd.print("Nem = %");
    lcd.print(hum);
    lcd.setCursor(0, 3);
    lcd.print("Isi = ");
    lcd.print(temp);
    lcd.print("C");
    if(temp < 18)
    {
      digitalWrite(heart,HIGH);
    }else
    {
      digitalWrite(heart, LOW);
    }

    delay(200); 

}
float calculateNH3Concentration(float voltage) {
  // Burada datasheet'ten alınan kalibrasyon eğrisini kullanarak NH3 konsantrasyonunu hesaplayın
  float ppm = (voltage - 0.1) * 100.0;  // Örnek formül
  return ppm;
}
