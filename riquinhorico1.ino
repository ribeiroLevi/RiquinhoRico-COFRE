#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// https://wokwi.com/projects/344891391763022419

// setup do keypad
const byte KEYPAD_ROWS = 4;
const byte KEYPAD_COLS = 3;
byte ROW_PINS[KEYPAD_ROWS] = {5, 4, 3, 2};
byte COL_PINS[KEYPAD_COLS] = {A1, A2, A3};
char keys[KEYPAD_ROWS][KEYPAD_COLS] = {
    {'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}, {'*', '0', '#'}};
Keypad keypad =
    Keypad(makeKeymap(keys), ROW_PINS, COL_PINS, KEYPAD_ROWS, KEYPAD_COLS);

String senha;
bool trancado = true;

Servo myservo;

int erros = 0;
// setup do display - prestar atenção ao primeiro parâmetro(endereço) - 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  senha = "1234";

  Serial.begin(9600);
  lcd.init();
  lcd.setCursor(0, 0);
  lcd.backlight();
  lcd.display();

  myservo.attach(7);
  myservo.write(90);

  initialMessage();
}

void loop() {
  char caracter = keypad.getKey();
  if (caracter != NO_KEY && trancado == true) {
    lcd.clear();
    passwordInsert();
  }
}

void initialMessage() {
  lcd.clear();
  lcd.setBacklight(HIGH);
  lcd.setCursor(2, 0);
  String nome = "RiquinhoRico";
  String message = "Aprt Qlqr Tcla";

  for (int i = 0; i < nome.length(); i++) {
    delay(100);
    lcd.print(nome[i]);
  }
  lcd.setCursor(1, 1);
  for (int i = 0; i < message.length(); i++) {
    delay(50);
    lcd.print(message[i]);
  }
  trancado = true;
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

  if (result == senha) {
    acessoLiberado();
  } else {
    acessoNegado();
  }
}

void acessoLiberado() {
  myservo.write(0);
  trancado = false;
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
      logicaRedefinir();
      break;
    } else if (key == '#') {
      logicaTrancado();
      break;
    }
  }
}
void logicaRedefinir() {
  lcd.clear();
  senha = ' ';
  String novaSenha;
  String testeSenha;
  lcd.print("NOVA SENHA:");
  lcd.setCursor(5, 1);
  String placeholder = "[____]";
  lcd.print(placeholder);

  while (novaSenha.length() < 4) {
    char key = keypad.getKey();

    for (int i = 0; i < novaSenha.length(); i++) {
      lcd.setCursor(i + 6, 1);
      lcd.print("*");
    }
    if (key >= '0' && key <= '9') {
      novaSenha += key;
    }
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("REPITA A SENHA");
  lcd.setCursor(5, 1);
  lcd.print(placeholder);
  while (testeSenha.length() < 4) {
    char key = keypad.getKey();

    for (int i = 0; i < testeSenha.length(); i++) {
      lcd.setCursor(i + 6, 1);
      lcd.print("*");
    }
    if (key >= '0' && key <= '9') {
      testeSenha += key;
    }
  }
  if (testeSenha == novaSenha) {
    lcd.clear();
    lcd.print("SENHA REDEFINIDA");
    delay(2000);

    senha = novaSenha;
    lcd.clear();
    lcd.print("PRESSIONE #");
    lcd.setCursor(0, 1);
    lcd.print("PARA TRANCAR");
    while (true) {
      if (keypad.getKey() == '#') {
        logicaTrancado();
        break;
      }
    }
  }
  if (testeSenha != novaSenha) {
    lcd.clear();
    lcd.print("SENHAS NÃO");
    lcd.setCursor(0, 1);
    lcd.print("CORRESPONDEM");
    delay(2000);
    logicaRedefinir();
  }
}
void logicaTrancado() {
  myservo.write(90);
  lcd.clear();
  lcd.print("TRANCADO!");
  delay(3000);
  trancado = true;
  initialMessage();
}
void acessoNegado() {
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
