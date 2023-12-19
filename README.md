
# RiquinhoRico - Cofre em Arduino
Projeto com Arduino e Manufatura Aditiva para o processo seletivo do Laboratório de Computação Física da Universidade Federal do Ceará



## Funcionalidades
Simula um cofre com abertura por meio de senha digital que pode ser redefinida. Possui armazenamente físico em EEPROM.

## Aprendizados

#### Utilização de novos tipos de manufatura
Por conta da inviabilidade se utilizar a impressão 3D para construção das paredes do cofre, tive de usar o que se chama de Manufatura Subtrativa, ou seja, máquinas como a de corte a laser (CNC) foram utilizadas para o sucesso do projeto.

#### Aprendizagem de novos protocolos
Ao utilizar o display, afim de economizar espaço, utilizei o display com comunicação I2C, o que acarretou na construção de novos conhecimentos acerca de protocolos de comunicação.

#### Armazenamento físico
Como as senhas podem ser alteradas pelo usuário, é interessante que elas se mantivessem mesmo que o aparelho fosse desligado. Assim, estudei acerca do armazenamento físico EEPROM que permitiu com que se mantivessem as senhas alteradas mesmo que o arduino fossse desligado
## Screenshots

#### Protipação
![PROTÓTIPO FISICO](https://github.com/ribeiroLevi/RiquinhoRico-COFRE/assets/126264441/94e6c618-3b22-4e24-a5b3-81ea3e18546d)
![CIRCUITO](https://github.com/ribeiroLevi/RiquinhoRico-COFRE/assets/126264441/7a05528c-ef70-4ec2-8a40-0605412d3a41)

#### Modelagem
![TAMPA SUPERIOR](https://github.com/ribeiroLevi/RiquinhoRico-COFRE/assets/126264441/7f1e1696-7f4a-40f7-b51f-22d6818f70c9)
![TAMPA INFERIOR](https://github.com/ribeiroLevi/RiquinhoRico-COFRE/assets/126264441/15889221-a699-4982-954c-e617d4d75471)
![MACANETA](https://github.com/ribeiroLevi/RiquinhoRico-COFRE/assets/126264441/938e4ca1-925c-4aab-8399-2c517b72c168)
#### Fatiamento
![FATIAMENTO SUPERIOR](https://github.com/ribeiroLevi/RiquinhoRico-COFRE/assets/126264441/cce0f62f-4ca7-43bf-a489-740b118f9d1b)
![FATIAMENTO INFERIOR](https://github.com/ribeiroLevi/RiquinhoRico-COFRE/assets/126264441/04297bc2-7888-4037-a7d9-08c199dcc213)
#### Impressão
![IMPRESSAO](https://github.com/ribeiroLevi/RiquinhoRico-COFRE/assets/126264441/6ae2b1b8-3b02-4520-8f56-dfe345876874)
#### Render
![RENDER3 15](https://github.com/ribeiroLevi/RiquinhoRico-COFRE/assets/126264441/d7016476-a0b6-4168-bc4c-f11503638137)
#### Modelo Final
![MODELO FISICO](https://github.com/ribeiroLevi/RiquinhoRico-COFRE/assets/126264441/d493b450-0bd9-4378-81fd-4ab7fde2ff75)

## Referência

 - [EEPROM](https://dribbble.com/ribeiroLevi/collections/6805829-to-do-list?utm_source=Clipboard_%22clipboard_collection%22&utm_campaign=%22ribeiroLevi%22&utm_content=%22to%20do%20list%22&utm_medium=Social_Share](https://docs.arduino.cc/learn/built-in-libraries/eeprom))
 - [I2C](https://www.figma.com/file/8Ya5dHpaKLQA0GVnCIEoFs/TO-DO-LIST?type=design&node-id=0%3A1&mode=design&t=ttbOdhDaXNS6dCQZ-1](https://reference.arduino.cc/reference/en/libraries/liquidcrystal-i2c/)https://reference.arduino.cc/reference/en/libraries/liquidcrystal-i2c/)
 - [Arduino](https://www.arduino.cc/reference/en/)


