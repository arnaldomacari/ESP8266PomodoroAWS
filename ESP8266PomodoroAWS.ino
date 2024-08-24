#include <ESP8266WiFi.h>
#include <Wire.h>
#include <RTClib.h>
#include <TM1638.h>

// Configuração do RTC DS3231
#define SQW_Pin D4 
RTC_DS3231 rtc;
DateTime tNow;
bool SQW_Estado = LOW; 
bool SQW_sinc = false;
bool fSegundo = false;
bool ponto = false;
const char* diasDaSemana[7] = {"doM", "SEG", "tEr", "QUA", "QUI", "SEt", "SAb"};
const char* mes[12] = {"JA", "FE", "Mc", "Ab", "MI", "Jn", "JL", "AG", "SE", "Ot", "no","dE" };

// Pomodoro
unsigned long tContReg;
unsigned long tMinutos;
unsigned long tSegundos;


//Configuração do Display TM1638
#define STB_Pin D5 // Pino STB do TM1638
#define CLK_Pin D6 // Pino CLK do TM1638
#define DIO_Pin D7 // Pino DIO do TM1638
TM1638 tm(CLK_Pin,DIO_Pin,STB_Pin);

//Configuração do medidor de bateria
#define Bateria_Pin A0  //ESP8266 Analog Pin ADC0 = A0
int tensBat = 0;  //Valor lido da bateria

#define Beep_Pin D8 //Pino para o Beep
int contaBeep = 0;

//Buffer para preparo de escrita
char buffer[15];  

//Automato Controle de Menu
int automato = 0;
unsigned long botaoTimer[8];  //antiruido para os 8 botoes da placa
#define antiRuido 100 // milessegundo para estabilizar ruido no botão
unsigned long aceiteTimer;
#define aceite 2500 // milessegundo para executar comendo menu


//Declaração de funções
bool botao(int b);
void printString(const char* text);
char letras( char caracter, bool ponto);


void setup() {
  pinMode(SQW_Pin, INPUT);
  pinMode(Beep_Pin, OUTPUT);
  digitalWrite(Beep_Pin, LOW);
  sprintf(buffer, "8888.88.88\0");
  printString(buffer);

  Serial.begin(115200);
  while(!Serial) yield();
 

  //Inicializa o RTC
  if (!rtc.begin()) {
    Serial.println("Não foi possível encontrar o RTC DS3231");
    while (1);
  }
  
  //Configura o SQW para 1Hz
  rtc.writeSqwPinMode(DS3231_SquareWave1Hz);

  //Inicializa o Display TM1638
  tm.reset();
  delay(100);

  contaBeep=2;
  while ( digitalRead(SQW_Pin)) {;} // aguarda SQW = LOW para iniciar setup sincronizado
  SQW_sinc = true;
}


int conta_dia_temp = 0;

void loop() {

  SQW_Estado = digitalRead(SQW_Pin); 
  if ( SQW_sinc && SQW_Estado) {
    SQW_sinc = false; 
    if ( contaBeep >= 0) digitalWrite(Beep_Pin, LOW);
    switch (automato){
      case 0:
      if (ponto) {
        buffer[4]=buffer[5];// apaga o ponto da hora e da data
        buffer[5]=buffer[6];
        buffer[6]=buffer[8];
        buffer[7]=buffer[9];
        buffer[8]='\0';
        printString(buffer);
        ponto = false;
      }
      break;
    };

  }; 

  if ( !SQW_sinc && !SQW_Estado){
    SQW_sinc = true;
    fSegundo = true;
    if ( contaBeep > 0) {
      digitalWrite(Beep_Pin, HIGH);
      contaBeep--;
    }
  }

  switch (automato){
    case 0:
    if (fSegundo){
        fSegundo = false;            
        tNow = rtc.now();   
        if ( (tNow.second() > 20 && tNow.second() < 25)  || (tNow.second() > 40 && tNow.second() < 45)){
          sprintf(buffer, "%s .%02d.%s\0", diasDaSemana[tNow.dayOfTheWeek()], tNow.day(), mes[tNow.month()-1]);
          printString(buffer);
        }else{
          sprintf(buffer, "Hr%02d.%02d.%02d\0", tNow.hour(), tNow.minute(), tNow.second());
          printString(buffer);
        }
        ponto=true;

      }


      if (botao(S1)){        
        printString("Pomodoro");
        ponto=false;
        aceiteTimer = millis(); 
        fSegundo = false;
        automato = 1;
      };
    break;


    case 1:
      if ( fSegundo && aceiteTimer + aceite < millis()) {
        fSegundo = false;
        tContReg = 25*60;
        //printString("P   25.00");
        automato = 2;
      };

      if (botao(S1)){
        printString("dAtAHorA");
        aceiteTimer = millis(); 
        fSegundo = false;
        automato = 4;
      }; 
    break;


    case 2:
      if (fSegundo) {
        fSegundo = false;
        tMinutos = tContReg/60;
        tSegundos = tContReg%60;
        sprintf(buffer, "P25 %02d.%02d\0", tMinutos, tSegundos);
        printString(buffer);
        tContReg--;
        if (tContReg <= 0) {
          contaBeep=1;
          tContReg = 5*60;
          automato = 3;
        }       
      };

      if (botao(S2)){
          tContReg = 5*60;
          automato = 3;
      }; 

      if (botao(S1)){
        printString("dAtAHorA");
        aceiteTimer = millis(); 
        fSegundo = false;
        automato = 4;
      };
      
    break;


    case 3:
      if (fSegundo) {
        fSegundo = false;
        tMinutos = tContReg/60;
        tSegundos = tContReg%60;
        sprintf(buffer, "P5  %02d.%02d\0", tMinutos, tSegundos);
        printString(buffer);
        tContReg--;
        if (tContReg <= 0) {
          contaBeep=2;
          tContReg =25*60;
          automato = 2;
        }        
      }

      if (botao(S2)){
          tContReg = 25*60;
          automato = 2;
      };

      if (botao(S1)){
        printString("dAtAHorA");
        aceiteTimer = millis(); 
        fSegundo = false;
        automato = 4;
      }; 
    break;



    case 4:
      if ( fSegundo && aceiteTimer + aceite < millis()) {
        fSegundo = false;
        automato = 0;
      };

      if (botao(S1)){
        printString("Pomodoro");
        aceiteTimer = millis(); 
        fSegundo = false;
        automato = 1;
      };
    break;
  }  
}


bool botao(button_t b){
  if (tm.getButton(b)){
    botaoTimer[b] = millis();
    }else{
      if (botaoTimer[b] != 0){   // não usei && para não chamar millis() o tempo todo;
        if (botaoTimer[b] + antiRuido < millis()){
          botaoTimer[b] = 0;
          return true;
        }
      }
    }
  return false;     
}


void printString(const char* text) {
    int i = 0; //conta string
    int j = 0; //conta posi no display
    while (text[i] != '\0' && j<8  ) {  // Continua até encontrar o caractere nulo ('\0')
        if (text[i+1] == '.'){
          tm.displayDig(7-j,converte( text[i], true));
          //Serial.print(text[i]);
          i++;
        }else{
          tm.displayDig(7-j,converte( text[i], false));
        }
        //Serial.print(text[i]);
        i++;  // Avança para a próxima letra
        j++;  // Avança para a próxima posição do display
        
    }
}


//--------------------------------------
//Converte 

char converte(char caracter, bool ponto){
  char temp = 0;
  switch(caracter){
    case ' ': temp = 0b00000000; break;//Display 7 Segmento
    case '0': temp = 0b00111111; break;//  0bPGFEDCBA
    case '1': temp = 0b00000110; break;//    --A--
    case '2': temp = 0b01011011; break;//    F   B
    case '3': temp = 0b01001111; break;//    --G-- 
    case '4': temp = 0b01100110; break;//    E   C
    case '5': temp = 0b01101101; break;//    --D--  .P
    case '6': temp = 0b01111101; break; 
    case '7': temp = 0b00000111; break; 
    case '8': temp = 0b01111111; break; 
    case '9': temp = 0b01101111; break; 
    case 'A': temp = 0b01110111; break;
    case 'b': temp = 0b01111100; break; 
    case 'c': temp = 0b01011000; break; 
    case 'd': temp = 0b01011110; break; 
    case 'E': temp = 0b01111001; break; 
    case 'F': temp = 0b01110001; break; 
    case 'G': temp = 0b00111101; break; 
    case 'H': temp = 0b01110110; break; 
    case 'I': temp = 0b00110000; break; 
    case 'i': temp = 0b00010000; break; 
    case 'J': temp = 0b00011110; break;
    case 'L': temp = 0b00111000; break; 
    case 'M': temp = 0b00110111; break;
    case 'm': temp = 0b00110111; break; 
    case 'n': temp = 0b01010100; break; 
    case 'O': temp = 0b00111111; break; 
    case 'o': temp = 0b01011100; break; 
    case 'P': temp = 0b01110011; break; 
    case 'Q': temp = 0b10111111; break; 
    case 'r': temp = 0b01010000; break; 
    case 'S': temp = 0b01101101; break; 
    case 't': temp = 0b01111000; break; 
    case 'U': temp = 0b00111110; break; 
    case 'u': temp = 0b00011100; break; 
    case 'W': temp = 0b00110110; break; 
    case 'w': temp = 0b00010100; break;
    case '-': temp = 0b01000000; break;  
  };
  if (ponto) temp += 0b10000000; 
  return temp;
}

