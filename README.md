![Static Badge](https://img.shields.io/badge/ESP8266-violet) ![Static Status](https://img.shields.io/badge/Pomodoro-blue)  ![Static Status](https://img.shields.io/badge/Alexa-green)  ![Static Status](https://img.shields.io/badge/AWS-yellow)  ![Static Status](https://img.shields.io/badge/Python-orange)   ![Static Status](https://img.shields.io/badge/Flask-red) ![Static Badge](https://img.shields.io/badge/Streamlit-violet) ![Static Status](https://img.shields.io/badge/KiCad-blue)



# ESP8266 Pomodoro AWS Alexa

<hr style="border:0; height: 5px; background-image: linear-gradient(to right, rgba(0, 0, 0, 0), rgba(0, 0, 255, 1), rgba(0, 0, 0, 0));">

## Justificativa
**Este projeto foi criado para fins didáticos** e mostra a integração de várias tecnologias para obter um **IoT** funcional. A segunda justificativa é que, particularmente, eu quero um bom temporizador pomodoro, com um cronômetro para academia e que seja prático de usar.

## Objetivo
Desenvolver um temporizador multipropósito:
- Pomodoro para usar no home-office ou para estudo.
- Temporizadores pré-programados para exercícios na academia.
- Controlado por botões e pela Alexa.
- Alimentado por baterias recarregáveis. 
- Os dados de tempo dos exercícios e do trabalho devem ser enviados para a AWS e verificados em um dashboard

## Introdução
Usando Wemos D1 Mini Nodemcu ESP8266,
Display de sete segmentos Tm1638,
Relógio interno Rtc3231 sincronizado por NTP
Bateria íon-lítio, 
sincronizando com AWS usando Flask e apresentando um dashboard com Streamlit

<hr style="border:0; height: 5px; background-image: linear-gradient(to right, rgba(0, 0, 0, 0), rgba(0, 0, 255, 1), rgba(0, 0, 0, 0));">

<a id="ancora"></a>
## Índice 
[Etapas](#ancora0)
[Componentes utilizados](#ancora1)
[Bibliotecas utilizadas](#ancora2)
[Circuito montado no Protoboard](#ancora3)

<hr style="border:0; height: 5px; background-image: linear-gradient(to right, rgba(0, 0, 0, 0), rgba(0, 0, 255, 1), rgba(0, 0, 0, 0));">

<a id="ancora0"></a>
## Etapas

| Etapa    |  Status  |
| :--------| :------: |
| Descrição do projeto              |  ![Static Status](https://img.shields.io/badge/Finalizado-0000FF) |
| Construção do circuito eletrônico no protoboard| ![Static Status](https://img.shields.io/badge/Finalizado-0000FF) |
| Programação para Tm1638           | ![Static Status](https://img.shields.io/badge/Finalizado-0000FF) |
| Programação para Rtc3231          | ![Static Status](https://img.shields.io/badge/Finalizado-0000FF) |
| Programação para mostrar data e hora| ![Static Status](https://img.shields.io/badge/Finalizado-0000FF) |
| Programação para Temporizador Pomodoro         | ![Static Status](https://img.shields.io/badge/Executando-00BF00) |
| Detecção da carga da bateria       | ![Static Status](https://img.shields.io/badge/Executando-00BF00) |
| Programação para WPS              | ![Static Status](https://img.shields.io/badge/Aguardando-FFFF00) |
| Programação para NTP              | ![Static Status](https://img.shields.io/badge/Aguardando-FFFF00) |
| Programação para Alexa            | ![Static Status](https://img.shields.io/badge/Aguardando-FFFF00) |
| Programação para Flask            | ![Static Status](https://img.shields.io/badge/Aguardando-FFFF00) |
| Programação para Streamlit        | ![Static Status](https://img.shields.io/badge/Aguardando-FFFF00) |
| Deploy para AWS                   | ![Static Status](https://img.shields.io/badge/Aguardando-FFFF00) |
| Testes e ajustes                  | ![Static Status](https://img.shields.io/badge/Aguardando-FFFF00) |
| Desenho do circuito eletrônico    | ![Static Status](https://img.shields.io/badge/Aguardando-FFFF00) |
| Desenho da placa de circuito impresso| ![Static Status](https://img.shields.io/badge/Aguardando-FFFF00) |
| Confecção da placa e soldagem dos componentes | ![Static Status](https://img.shields.io/badge/Aguardando-FFFF00) |
| Testes e ajustes finais           | ![Static Status](https://img.shields.io/badge/Aguardando-FFFF00) |
| Divulgação do trabalho            | ![Static Status](https://img.shields.io/badge/Aguardando-FFFF00) |

<hr style="border:0; height: 5px; background-image: linear-gradient(to right, rgba(0, 0, 0, 0), rgba(0, 0, 255, 1), rgba(0, 0, 0, 0));">
<a id="ancora1"></a> 

## Componentes utilizados.
<br>

### Wemos D1 Mini Nodemcu Esp8266
![Esp8266](imagens/Esp8266.png)

<hr style="border:0; height: 1px; background-image: linear-gradient(to right, rgba(0, 0, 0, 0), rgba(0, 0, 255, 0.5), rgba(0, 0, 0, 0));">

### Display Tm1638 7 Segmentos 8x7 Led&key
![Tm1638](imagens/Tm1638.png)

<hr style="border:0; height: 1px; background-image: linear-gradient(to right, rgba(0, 0, 0, 0), rgba(0, 0, 255, 0.5), rgba(0, 0, 0, 0));">

### Módulo Real Time Rtc Ds3231
![Rtc3231](imagens/Rtc3231.png)

<hr style="border:0; height: 1px; background-image: linear-gradient(to right, rgba(0, 0, 0, 0), rgba(0, 0, 255, 0.5), rgba(0, 0, 0, 0));">

### Carregador De Bateria Lítio Tp4056
![Tp4056](imagens/Tp4056.png)
Pinos soldados para uso no protoboard.
![Tp4056](imagens/Tp4056_protoboard.png)

<hr style="border:0; height: 1px; background-image: linear-gradient(to right, rgba(0, 0, 0, 0), rgba(0, 0, 255, 0.5), rgba(0, 0, 0, 0));">

### DC-DC Boost Converter Step Up Module
![DC-DC-Step-Up](imagens/DC-DC-Step-Up.png)
Pinos soldados para uso no protoboard.
![DC-DC-Step-Up](imagens/DC-DC-Step-Up_protoboard.png)

<hr style="border:0; height: 1px; background-image: linear-gradient(to right, rgba(0, 0, 0, 0), rgba(0, 0, 255, 0.5), rgba(0, 0, 0, 0));">

### Buzzer Ativo 5v
![Buzzer](imagens/Buzzer.png)

<hr style="border:0; height: 1px; background-image: linear-gradient(to right, rgba(0, 0, 0, 0), rgba(0, 0, 255, 0.5), rgba(0, 0, 0, 0));">

### Transistor BC 548
![BC548](imagens/BC548.png) 

<hr style="border:0; height: 1px; background-image: linear-gradient(to right, rgba(0, 0, 0, 0), rgba(0, 0, 255, 0.5), rgba(0, 0, 0, 0));">


### Resistores 4k7, 47k e 100k por 1/4W (pode ser 1/8W)
![Resistores](imagens/Resistores.png)

<hr style="border:0; height: 1px; background-image: linear-gradient(to right, rgba(0, 0, 0, 0), rgba(0, 0, 255, 0.5), rgba(0, 0, 0, 0));">

### Bateria recarregável de lítio 18650
![Bateria](imagens/Bateria.png)

<hr style="border:0; height: 1px; background-image: linear-gradient(to right, rgba(0, 0, 0, 0), rgba(0, 0, 255, 0.5), rgba(0, 0, 0, 0));">

### 2x Protoboard 400 Pontos
![Protoboard](imagens/Protoboard.png)
[Retornar para o Índice](#ancora)
<br><br><br>

<a id="ancora2"></a>
<hr style="border:0; height: 5px; background-image: linear-gradient(to right, rgba(0, 0, 0, 0), rgba(0, 0, 255, 1), rgba(0, 0, 0, 0));">

## Bibliotecas

![biblio_TM1638](imagens/biblio_TM1638.png)
https://github.com/dvarrel/TM1638

<hr style="border:0; height: 1px; background-image: linear-gradient(to right, rgba(0, 0, 0, 0), rgba(0, 0, 255, 0.5), rgba(0, 0, 0, 0));">

![biblio_RTClib](imagens/biblio_RTClib.png)
https://github.com/adafruit/RTClib


<hr style="border:0; height: 1px; background-image: linear-gradient(to right, rgba(0, 0, 0, 0), rgba(0, 0, 255, 0.5), rgba(0, 0, 0, 0));">

![biblio_NTPClient](imagens/biblio_NTPClient.png)
https://github.com/arduino-libraries/NTPClient

<hr style="border:0; height: 1px; background-image: linear-gradient(to right, rgba(0, 0, 0, 0), rgba(0, 0, 255, 0.5), rgba(0, 0, 0, 0));">

[Retornar para o Índice](#ancora)
<br><br><br>

<a id="ancora3"></a>
<hr style="border:0; height: 5px; background-image: linear-gradient(to right, rgba(0, 0, 0, 0), rgba(0, 0, 255, 1), rgba(0, 0, 0, 0));">

## Circuito montado no Protoboard

[Retornar para o Índice](#ancora)