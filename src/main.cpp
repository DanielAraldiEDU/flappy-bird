/**
 *  /// AUTORES:
 *
 *  Bruno Ferreira Jimenez
 *  Daniel Sansão Araldi
 *  Enzo Luigi Schork
 *  Jonathas Meine
 */

/* Versão beta desenvolvida por Thiago Felski Pereira para disciplina de Algoritmos */
#include <iostream>
#include <windows.h>
#include <conio.h> // para o getch()
#include <time.h>
// https://stackoverflow.com/questions/34474627/linux-equivalent-for-conio-h-getch

using namespace std;

/**
    F L A P P Y B I R D (M2 Algoritmos)
    - Lembrando: não permitido o uso de funções e variáveis compostas como structs, vetores e matrizes
    - Corrigir os rastros (pássaro e obstáculos)
    - Implementar colisão
    - Implementar pontuação (mais um ponto para cada obstáculo superado)
    - Fazer 2 obstáculos simultâneos (obstaculo1 e obstaculo2)
    - Deixar a pontuação visível durante todo o jogo
    - Definir marcos para acelerar a velocidade
*/

int main()
{
  /// ALERTA: NÃO MODIFICAR O TRECHO DE CÓDIGO, A SEGUIR.
  // INICIO: COMANDOS PARA QUE O CURSOR NÃO FIQUE PISCANDO NA TELA
  HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO cursorInfo;
  GetConsoleCursorInfo(out, &cursorInfo);
  cursorInfo.bVisible = false; // set the cursor visibility
  SetConsoleCursorInfo(out, &cursorInfo);
  // FIM: COMANDOS PARA QUE O CURSOR NÃO FIQUE PISCANDO NA TELA
  // INÍCIO: COMANDOS PARA REPOSICIONAR O CURSOR NO INÍCIO DA TELA
  COORD coord;
  // FIM: COMANDOS PARA REPOSICIONAR O CURSOR NO INÍCIO DA TELA
  /// ALERTA: NÃO MODIFICAR O TRECHO DE CÓDIGO, ACIMA.

  system("cls"); // LIMPA O TERMINAL AO COMEÇAR O JOGO

  srand(time(NULL)); // SEMENTE RANDOMICA GERADA A PARTIR DO HORÁRIO DO SISTEMA

  // DECLAÇÃO DE VARIÁVEIS
  int bird_x = 15, bird_y = 10;
  int placar_x = 60, placar_y = 1;
  int obstaculo1_x = 130, obstaculo1_y;
  int obstaculo2_x = 130, obstaculo2_y;
  int game_over_x = 50, game_over_y = 10;
  int tecla, coordPassagemObstaculo1, coordPassagemObstaculo2, velocidade = 200, placar = 0;
  bool estaVoando = true;

  // DESENHO DO CENÁRIO
  cout << "-----------------------------------------------------------------------------------------------------------------------------------";
  cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
  cout << "-----------------------------------------------------------------------------------------------------------------------------------";

  coordPassagemObstaculo1 = rand() % 15 + 3; // GERA NÚMEROS ALEATÓRIOS 3 e 17
  coordPassagemObstaculo2 = rand() % 15 + 3; // GERA NÚMEROS ALEATÓRIOS 3 e 17

  while (estaVoando) // ESSE LAÇO FAZ O JOGO RODAR SEMPRE
  {
    // POSICIONA O PLACAR
    coord.X = placar_x;
    coord.Y = placar_y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "PLACAR: " << placar;

    // POSICIONA O PÁSSARO
    coord.X = bird_x;
    coord.Y = bird_y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << char(190);

    // POSICIONA O OBSTÁCULO 1
    obstaculo1_y = 1;
    while (obstaculo1_y < 20)
    {
      coord.X = obstaculo1_x;
      coord.Y = obstaculo1_y;
      SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

      if (obstaculo1_y < coordPassagemObstaculo1 - 2 || obstaculo1_y > coordPassagemObstaculo1 + 2) // CRIA ESPAÇAMENTO DE DOIS ESPAÇOS PARA CIMA E PARA BAIXO NO OBSTÁCULO 1
      {
        cout << char(219);
      }
      else
      {
        cout << " ";
      }

      obstaculo1_y++;

      coord.X = obstaculo1_x + 1; // APAGA O RASTRO DO OBSTÁCULO 1
      SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
      cout << " ";
    }

    if (obstaculo1_x <= 65 || obstaculo2_x <= 65)
    {
      // POSICIONA O OBSTÁCULO 2
      obstaculo2_y = 1;
      while (obstaculo2_y < 20)
      {
        coord.X = obstaculo2_x;
        coord.Y = obstaculo2_y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

        if (obstaculo2_y < coordPassagemObstaculo2 - 2 || obstaculo2_y > coordPassagemObstaculo2 + 2) // CRIA ESPAÇAMENTO DE DOIS ESPAÇOS PARA CIMA E PARA BAIXO NO OBSTÁCULO 2
        {
          cout << char(219);
        }
        else
        {
          cout << " ";
        }

        obstaculo2_y++;

        coord.X = obstaculo2_x + 1; // APAGA O RASTRO DO OBSTÁCULO 2
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        cout << " ";
      }
    }

    if ((bird_y <= 0 || bird_y >= 20) ||
        (obstaculo1_x == bird_x && (bird_y < coordPassagemObstaculo1 - 2 || bird_y > coordPassagemObstaculo1 + 2)) ||
        (obstaculo2_x == bird_x && (bird_y < coordPassagemObstaculo2 - 2 || bird_y > coordPassagemObstaculo2 + 2))) // PAUSA O JOGO CASO HAJA UMA COLISÃO COM O OBSTÁCULO, TETO OU O CHÃO
    {
      system("cls");      // LIMPA O TERMINAL DO JOGO
      estaVoando = false; // NÃO ESTÁ MAIS VOANDO POR QUE COLIDIU COM O OBSTÁCULO, TETO OU O CHÃO

      // POSICIONA A MENSAGEM DE GAME OVER
      coord.X = game_over_x;
      coord.Y = game_over_y;
      SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
      cout << "GAME OVER";

      // POSICIONA O PLACAR
      coord.Y = game_over_y + 2;
      SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
      cout << "PLACAR: " << placar;

      // POSICIONA A MENSAGEM DE PRESSIONAR PRÓXIMA TECLA PARA CONTINUAR
      coord.X = game_over_x - 15;
      coord.Y = game_over_y + 4;
      SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
      system("pause"); // PAUSA O JOGO
    }

    if (bird_x == obstaculo1_x + 1 || bird_x == obstaculo2_x + 1) // ADICIONA PONTUAÇÃO AO PLACAR AO PASSAR PELOS OBSTÁCULOS
    {
      placar++; // ADICIONA MAIS UM NA PONTUAÇÃO

      if (placar != 0 && placar % 5 == 0 && velocidade > 40) // SE O VALOR DA PONTUAÇÃO É DIFERENTE DE ZERO E MULTIPLO DE CINCO E VELOCIDADE MAIOR QUE QUARENTA PARA NÃO FICAR IMPOSSÍVEL DE JOGAR
      {
        velocidade -= 20; // A VELOCIDADE É AUMENTADA
      }
    }

    if (kbhit())       // VERIFICA COMANDO DO JOGADOR
    {                  // VERIFICA SE UMA TECLA FOI PRESSIONADA
      tecla = getch(); // VERIFICA COMANDO DO JOGADOR
    }

    if (tecla == 'w' || tecla == 'W') // SE TECLOU "W" OU "w"
    {
      bird_y--; // PASSÁRO VAI PARA CIMA
      tecla = '0';
    }
    else
    {
      bird_y++; // PASSÁRO VAI PARA BAIXO
    }

    obstaculo1_x--; // OBSTÁCULO 1 AVANÇA UMA POSIÇÃO PARA ESQUERDA

    if (obstaculo1_x <= 65 || obstaculo2_x <= 65) // SE O X DO OBSTÁCULO 1 OU X DO OBSTÁCULO 2 FOREM MENOR OU IGUAL A 65
    {
      obstaculo2_x--; // OBSTÁCULO 2 AVANÇA UMA POSIÇÃO PARA ESQUERDA
    }

    Sleep(velocidade); // TEMPO DE ESPERA

    // REMOVE O RASTRO DO PÁSSARO PARA CIMA
    coord.Y = bird_y - 1;
    coord.X = bird_x;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    if (bird_y != 1)
    {
      cout << " ";
    }

    // REMOVE O RASTRO DO PÁSSARO PARA BAIXO
    coord.Y = bird_y + 1;
    coord.X = bird_x;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    if (bird_y != 19)
    {
      cout << " ";
    }

    if (obstaculo1_x < 0) // SE A POSIÇÃO DO OBSTÁCULO 1 É MENOR QUE ZERO NO CENÁRIO
    {
      coord.X = obstaculo1_x + 1; // ADICIONA MAIS UM PARA EXCLUIR O RASTRO DA POSIÇÃO ZERO DO CENÁRIO A CORDENADA
      while (obstaculo1_y > 0)    // ENQUANTO O Y DO OBSTÁCULO 1 FOR MAIOR QUE ZERO
      {
        // REMOVE O RASTRO DA ÚLTIMA POSIÇÃO DO OBSTÁCULO 1 NO CENÁRIO
        coord.Y = obstaculo1_y; // ADICIONA O VALOR ATUAL DO Y DO OBSTÁCULO 1 A CORDENADA
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        cout << " ";
        obstaculo1_y--; // PEGA A POSIÇÃO ATUAL DO Y DO OBSTÁCULO 1 E SUBTRAI POR UM
      }

      coordPassagemObstaculo1 = rand() % 15 + 3; // GERA NÚMEROS ALEATÓRIOS 3 e 17
      obstaculo1_x = 130;                        // VOLTA O OBSTÁCULO 1 PARA A POSIÇÃO INICIAL
    }
    else if (obstaculo2_x < 0)
    {
      coord.X = obstaculo2_x + 1; // ADICIONA MAIS UM PARA EXCLUIR O RASTRO DA POSIÇÃO ZERO DO CENÁRIO A CORDENADA
      while (obstaculo2_y > 0)    // ENQUANTO O Y DO OBSTÁCULO 2 FOR MAIOR QUE ZERO
      {
        // REMOVE O RASTRO DA ÚLTIMA POSIÇÃO DO OBSTÁCULO 2 NO CENÁRIO
        coord.Y = obstaculo2_y; // ADICIONA O VALOR ATUAL DO Y DO OBSTÁCULO 2 A CORDENADA
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        cout << " ";
        obstaculo2_y--; // PEGA A POSIÇÃO ATUAL DO Y DO OBSTÁCULO 2 E SUBTRAI POR UM
      }

      coordPassagemObstaculo2 = rand() % 15 + 3; // GERA NÚMEROS ALEATÓRIOS 3 e 17
      obstaculo2_x = 130;                        // VOLTA O OBSTÁCULO 2 PARA A POSIÇÃO INICIAL
    }
  }

  return 0;
}
