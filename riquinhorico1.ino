#include <EEPROM.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// https://wokwi.com/projects/344891391763022419

// setup do keypad
const byte KEYPAD_ROWS = 4;
const byte KEYPAD_COLS = 3;
byte ROW_PINS[KEYPAD_ROWS] = {10,9,8,7};
byte COL_PINS[KEYPAD_COLS] = {6,5,4};
char keys[KEYPAD_ROWS][KEYPAD_COLS] = {
    {'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}, {'*', '0', '#'}};
Keypad keypad =
    Keypad(makeKeymap(keys), ROW_PINS, COL_PINS, KEYPAD_ROWS, KEYPAD_COLS);

String password;
bool locked = true;

Servo myservo;

int erros = 0;
// setup do display - prestar atenção ao primeiro parâmetro(endereço) - 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  if (isPasswordSetInEEPROM()) {
    password = readPasswordFromEEPROM();
  } else {
    password = "1234";                // Set the default password
    writePasswordToEEPROM(password);  // Store the default password in EEPROM
  }
  Serial.begin(9600);
  lcd.init();
  lcd.setCursor(0, 0);
  lcd.backlight();
  lcd.display();

  myservo.attach(14);
  myservo.write(90);

  initialMessage();
}

void loop() {
    char customKey = keypad.getKey();
  
  if (customKey){
    Serial.println(customKey);
  }
  Serial.println(password);
  char caracter = keypad.getKey();
  if (caracter != NO_KEY && locked == true) {
    lcd.clear();
    passwordInsert();
  }
}

void initialMessage() {
  lcd.clear();
  lcd.setBacklight(HIGH);
  lcd.setCursor(2, 0);
  String name = "RiquinhoRico";
  String message = "Aprt Qlqr Tcla";

  for (int i = 0; i < name.length(); i++) {
    delay(100);
    lcd.print(name[i]);
  }
  lcd.setCursor(1, 1);
  for (int i = 0; i < message.length(); i++) {
    delay(50);
    lcd.print(message[i]);
  }
  locked = true;
}

void passwordInsert() {
  String result = "";

  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Insira a Senha");

  lcd.setCursor(5, 1);
  String placeholder = "[____]";
  lcd.print(placeholder);

  while (result.length() < 4) {
    char key = keypad.getKey();

    for (int i = 0; i < result.length(); i++) {
      Serial.println(result);
      lcd.setCursor(i + 6, 1);
      lcd.print("*");
      if (key == '*') {
        // limpa a senha
        passwordInsert();
      }
    }
    if (key >= '0' && key <= '9') {
      result += key;
    }
  }
  if (result == password) {
    accessGranted();
  } else {
    accessDenied();
  }
}

void accessGranted() {
  myservo.write(0);
  locked = false;
  erros = 0;

  lcd.clear();
  lcd.print("Acesso Liberado!");
  delay(2000);
  lcd.clear();
  lcd.print("*-RDFN SENHA");
  lcd.setCursor(0, 1);
  lcd.print("#-TRANCAR");

  while (true) {
    char key = keypad.getKey();
    key == ' ';
    if (key == '*') {
      resetLogic();
      break;
    } else if (key == '#') {
      lockedLogic();
      break;
    }
  }
}
void resetLogic() {
  lcd.clear();
  password = "";
  String newPassword;
  String passwordTest;
  lcd.print("NOVA SENHA:");
  lcd.setCursor(5, 1);
  String placeholder = "[____]";
  lcd.print(placeholder);

  while (newPassword.length() < 4) {
    char key = keypad.getKey();

    for (int i = 0; i < newPassword.length(); i++) {
      lcd.setCursor(i + 6, 1);
      lcd.print("*");
    }
    if (key >= '0' && key <= '9') {
      newPassword += key;
    }
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("REPITA A SENHA");
  lcd.setCursor(5, 1);
  lcd.print(placeholder);
  while (passwordTest.length() < 4) {
    char key = keypad.getKey();

    for (int i = 0; i < passwordTest.length(); i++) {
      lcd.setCursor(i + 6, 1);
      lcd.print("*");
    }
    if (key >= '0' && key <= '9') {
      passwordTest += key;
    }
  }
  if (passwordTest == newPassword) {
    lcd.clear();
    lcd.print("SENHA REDEFINIDA");
    delay(2000);
    for (int i = 0; i < 4; i++) {
      EEPROM.put(i, newPassword[i]);
      char character = EEPROM.read(i);
      password += character;
    }
    lcd.clear();
    lcd.print("PRESSIONE #");
    lcd.setCursor(0, 1);
    lcd.print("PARA TRANCAR");
    while (true) {
      if (keypad.getKey() == '#') {
        lockedLogic();
        break;
      }
    }
  }
  if (passwordTest != newPassword) {
    lcd.clear();
    lcd.print("SENHAS NÃO");
    lcd.setCursor(0, 1);
    lcd.print("CORRESPONDEM");
    delay(2000);
    resetLogic();
  }
}
void lockedLogic() {
  myservo.write(90);
  lcd.clear();
  lcd.print("TRANCADO!");
  delay(3000);
  locked = true;
  initialMessage();
}

void accessDenied() {
  erros++;
  lcd.clear();
  lcd.print("Acesso Negado!");
  delay(2000);

  if (erros == 1) {
    lcd.clear();
    for (int i = 10; i >= 0; i--) {
      delay(1000);
      lcd.clear();
      lcd.print("Aguarde: " + String(i) + "s");
      delay(1000);
    }
    passwordInsert();
  } else if (erros == 2) {
    lcd.clear();
    for (int i = 30; i >= 0; i--) {
      delay(1000);
      lcd.clear();
      lcd.print("Aguarde: " + String(i) + "s");
      delay(1000);
    }
    passwordInsert();
  } else if (erros == 3) {
    lcd.clear();
    for (int i = 60; i >= 0; i--) {
      delay(1000);
      lcd.clear();
      lcd.print("Aguarde: " + String(i) + "s");
      delay(1000);
    }
    passwordInsert();
  } else if (erros >= 4) {
    lcd.clear();
    lcd.print("Acesso Bloqueado!");
  }
}

bool isPasswordSetInEEPROM() {
  for (int i = 0; i < 4; i++) {
    char character = EEPROM.read(i);
    if (character != 0) {
      return true;
    }
  }
  return false;
}

String readPasswordFromEEPROM() {
  String result = "";
  for (int i = 0; i < 4; i++) {
    char character = EEPROM.read(i);
    result += character;
  }
  return result;
}

void writePasswordToEEPROM(const String& newPassword) {
  for (int i = 0; i < 4; i++) {
    EEPROM.write(i, newPassword[i]);
  }
}
