#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>
#include <Keypad.h>

int cont = 0;
int num1 = 0;
int num2 = 0;
int num3 = 0;
int numT = 0;
int numtemp = 0;
int indice = 0;
int temp1 = 0;
int buz = 4;

LiquidCrystal_I2C lcd(0x27, 16, 2);
const byte filas = 4; //four rows
const byte columnas = 3; //three columns
char teclas[filas][columnas] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte pinesFilas[filas] = {13, 12, 11, 10};
byte pinesColumnas[columnas] = {7, 6, 5};

Keypad keypad = Keypad( makeKeymap(teclas), pinesFilas, pinesColumnas, filas, columnas );

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  delay(2000);
  lcd.setCursor(1, 0);
  lcd.print("Hola, buen dia.");
  Serial.print("m");
  delay(2000);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Decrementador:");
  lcd.setCursor(5, 1);
  lcd.print("1-240");
  Serial.print("n");
  delay(2000);
  lcd.clear();
  pinMode(buz,OUTPUT);
  digitalWrite(buz,HIGH);
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.println("Ingrese 1 numero");
  Serial.print('x');
  lcd.setCursor(6, 1);
  char pulsacion = keypad.getKey();
  if (pulsacion) {
    if (pulsacion >= '0' && pulsacion <= '9') {
      if (cont == 0) {
        cont++;
        num1 = int(pulsacion) - 48;
        Serial.print('f');
        delay(100);
        lcd.setCursor(6, 1);
        lcd.print(num1);
        Serial.print(num1);
      } else if (cont == 1) {
        cont++;
        num2 = int(pulsacion) - 48;
        Serial.print('j');
        delay(100);
        lcd.setCursor(7, 1);
        lcd.print(num2);
        Serial.print(num2);
      } else if (cont == 2) {
        cont++;
        num3 = int(pulsacion) - 48;
        Serial.print('k');
        delay(100);
        lcd.setCursor(8, 1);
        lcd.print(num3);
        Serial.print(num3);
      }
    }
  }
  
  if (pulsacion == '#') {
    lcd.clear();
    Serial.print('y');
    delay(100);
    descontar();
  }
}

void descontar() {
  lcd.clear();
  if (cont == 3) {
    num1 *= 100;
    num2 *= 10;
    numT = num1 + num2 + num3;
  } else if (cont == 2) {
    num1 *= 10;
    numT = num1 + num2;
  } else if (cont == 1) {
    numT = num1;
  }
  EEPROM.write(indice, numT);
  temp1 = EEPROM.read(indice);
    indice++;
  cont = 0;
  numtemp = numT;
  if (numT > 240) {
    lcd.setCursor(0, 0);
    lcd.print("numero erroneo");
    Serial.print('z');
    delay(1000);
    return;
  }
  Serial.println('q');
  delay(100);
  for (int i = 1; i <= numT; i++) {
    lcd.setCursor(0, 0);
    lcd.print("Decrementando...");
    lcd.setCursor(6, 1);
    lcd.print(numtemp--);
    
    if(((numtemp+1)/100) > 1){
      Serial.print((numtemp+1-((numtemp+1)%100))/100);
      Serial.print((numtemp+1-((numtemp+1)%10))/10);
      Serial.print(numtemp+1);
      delay(1000);
    }

    else if(((numtemp+1)/10) > 1){
      Serial.print((numtemp+1-((numtemp+1)%10))/100);
      Serial.print(numtemp+1);
      delay(1000);
    }

    else {
      Serial.print(numtemp+1);
      delay(1000);
    }
    lcd.clear();
  }
  lcd.println("CUENTA TERMINADA");
  Serial.println("t");
  digitalWrite(buz,LOW);
  delay(500);
  digitalWrite(buz,HIGH);
  delay(1500);
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("GRACIAS");
  lcd.setCursor(2, 1);
  lcd.print("Pase buen dia");
  Serial.print('u');
  delay(2000);
  lcd.clear();
}
