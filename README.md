# Atividade 2: Temporizador com Botão - Raspberry Pi Pico W

## Descrição
Nesta atividade, utilizamos o **Raspberry Pi Pico W** para controlar três **LEDs RGB** através de um **botão pushbutton**. O sistema implementa um temporizador de **3 segundos** para alterar o estado dos LEDs de acordo com a sequência programada.

## Funcionalidades Principais
- Ao pressionar o botão, **todos os LEDs são acesos** simultaneamente.
- Após **3 segundos**, apenas **dois LEDs permanecem acesos**.
- Após **6 segundos**, apenas **um LED permanece aceso**.
- Após **9 segundos**, **todos os LEDs são desligados**.
- Durante a execução do temporizador, **o botão não pode reiniciar a sequência**.
- Utiliza **resistores de pull-up** e **software debounce** para garantir um comportamento estável do botão.

## Componentes Utilizados
- **Raspberry Pi Pico W**.
- **3 LEDs (azul, vermelho e verde)**.
- **Resistores de 330 Ω** para cada LED.
- **Botão (Pushbutton)**.

## Tecnologias de Software Utilizadas
- Linguagem: **C**.
- Ferramentas: **Pico SDK**, **Visual Studio Code**.
- Simulação: **Wokwi**.

## Como Executar
1. **Configuração do Código**:
   - Compile o código utilizando o **Pico SDK** e um **CMakeLists.txt** adequado.
   - Carregue o código no **Raspberry Pi Pico W**.

2. **Execução**:
   - Pressione o **botão pushbutton** conectado à **GPIO 5** para iniciar a sequência.
   - Os LEDs acenderão e apagarão gradualmente conforme a programação de temporização.
   - O botão **somente funcionará novamente** após o último LED ser desligado.

3. **Simulação no Wokwi**:
   - Utilize o simulador Wokwi integrado ao VS Code para testar o projeto.

## Funções do Código
- **Função `init()`**: Inicializa as GPIOs dos LEDs e do botão.
- **Função `set_state()`**: Atualiza os LEDs conforme o estado atual.
- **Função `turn_off_callback()`**: Implementa o temporizador de **3 segundos** para desligar os LEDs gradualmente.
- **Função `main()`**: Aguarda o acionamento do botão e gerencia a lógica do sistema.
