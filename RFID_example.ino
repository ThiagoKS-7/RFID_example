//BIBLIOTECAS
#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10 //PINO SDA
#define RST_PIN 9 //PINO DE RESET
 
MFRC522 rfid(SS_PIN, RST_PIN); //PASSAGEM DE PARÂMETROS REFERENTE AOS PINOS
 
void setup() {
  Serial.begin(9600);
  SPI.begin(); //INICIALIZA O BARRAMENTO SPI
  rfid.PCD_Init(); //INICIALIZA MFRC522
}
 
void loop() {
  verificaID();
  rfid.PICC_HaltA(); //PARADA DA LEITURA DO CARTÃO
  rfid.PCD_StopCrypto1(); //PARADA DA CRIPTOGRAFIA NO PCD
}

void verificaID() {
    if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) //VERIFICA SE O CARTÃO PRESENTE NO LEITOR É DIFERENTE DO ÚLTIMO CARTÃO LIDO. CASO NÃO SEJA, FAZ
      return; //RETORNA PARA LER NOVAMENTE
   
    /***INICIO BLOCO DE CÓDIGO RESPONSÁVEL POR GERAR A TAG RFID LIDA***/
    String strID = "";
    for (byte i = 0; i < 4; i++) {
    strID +=
    (rfid.uid.uidByte[i] < 0x10 ? "0" : "") +
    String(rfid.uid.uidByte[i], HEX) +
    (i!=3 ? ":" : "");
  }
  strID.toUpperCase();
  /***FIM DO BLOCO DE CÓDIGO RESPONSÁVEL POR GERAR A TAG RFID LIDA***/
  if(strID == "86:61:6C:AF") {
    Serial.println("Chaveiro novo (2)");
  };
  if (strID == "9E:53:1B:A3") {
    Serial.println("Chaveiro da chave (1)");
  };
  if (strID == "A0:42:49:28") {
    Serial.println("Cartão (1)");
  }
  if (strID == "A9:17:0D:4D") {
    Serial.println("Cartão (2)");
  }
}
