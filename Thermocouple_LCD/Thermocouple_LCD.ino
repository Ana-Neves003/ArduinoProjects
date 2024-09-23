#include <SPI.h>  // Biblioteca para comunicação SPI
#include <Adafruit_MAX31855.h>  // Biblioteca da Adafruit para o módulo MAX31855
#include <LiquidCrystal.h>  // Biblioteca para controle de display LCD 16x2

// Definição dos pinos utilizados pelo MAX31855
int thermoDO = 3;  // Pino de saída de dados (MISO) 
int thermoCS = 4;  // Pino de Chip Select (CS) 
int thermoCLK = 5; // Pino de clock (CLK) 

// Criação do objeto para comunicação com o MAX31855, utilizando os pinos definidos
Adafruit_MAX31855 thermocouple(thermoCLK, thermoCS, thermoDO);

// Definição dos pinos para o display LCD 16x2
const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
// Criação do objeto para controlar o display LCD
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // Inicializa o LCD com 16 colunas e 2 linhas
  lcd.begin(16, 2);
  // Exibe uma mensagem temporária no LCD
  lcd.print("Iniciando...");

  // Inicializa a comunicação serial para depuração
  Serial.begin(9600);

  // Verifica se o MAX31855 está funcionando corretamente
  if (!thermocouple.begin()) {
    lcd.clear();  // Limpa o LCD
    lcd.print("Erro MAX31855");  // Exibe mensagem de erro
    while (1);  // Para a execução do código se houver erro na inicialização do MAX31855
  }

  // Limpa o LCD e exibe uma mensagem de prontidão
  lcd.clear();
  lcd.print("Pronto!");
  delay(2000);  // Pausa por 2 segundos para que a mensagem seja exibida
}

void loop() {
  // Lê a temperatura em Celsius a partir do termopar tipo K
  double tempC = thermocouple.readCelsius();
  
  // Verifica se houve algum erro na leitura da temperatura (retorna NaN em caso de erro)
  if (isnan(tempC)) {
    lcd.clear();  // Limpa o LCD
    lcd.print("Erro leitura");  // Exibe mensagem de erro
  } else {
    // Limpa o LCD e exibe a temperatura lida
    lcd.clear();
    lcd.setCursor(0, 0);  // Move o cursor para a primeira linha
    lcd.print("Temp: ");  // Exibe o texto "Temp: "
    lcd.print(tempC);  // Exibe a temperatura lida em Celsius
    lcd.print(" C");  // Adiciona o símbolo de graus Celsius

    // Envia os dados da temperatura para o monitor serial
    Serial.print("Temperatura: ");
    Serial.print(tempC);
    Serial.println(" C");
  }

  // Aguarda 1 segundo antes de fazer a próxima leitura
  delay(1000);
}
