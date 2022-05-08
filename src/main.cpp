/**
 *  Autores:
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

  srand(time(NULL));

  // DECLAÇÃO DE VARIÁVEIS
  int bird_x = 15, bird_y = 10;
  int placar_x = 60, placar_y = 1;
  int obstaculo_x = 130, obstaculo_y;
  int game_over_x = 60, game_over_y = 10;
  int tecla, numeroAleatorio, velocidade = 200, placar = 0;
  bool estaVoando = true;

  // DESENHO DO CENÁRIO
  cout << "-----------------------------------------------------------------------------------------------------------------------------------";
  cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
  cout << "-----------------------------------------------------------------------------------------------------------------------------------";

  numeroAleatorio = rand() % 15 + 3; // GERA NÚMEROS ALEATÓRIOS 3 e 17

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

    // POSICIONA O OBSTÁCULO
    obstaculo_y = 1;
    while (obstaculo_y < 20)
    {
      coord.X = obstaculo_x;
      coord.Y = obstaculo_y;
      SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

      if (obstaculo_y < numeroAleatorio - 2 || obstaculo_y > numeroAleatorio + 2) // CRIA ESPAÇAMENTO DE DOIS ESPAÇOS PARA CIMA E PARA BAIXO NO OBSTÁCULO
      {
        cout << char(219);
      }
      else
      {
        cout << " ";
      }

      obstaculo_y++;

      coord.X = obstaculo_x + 1; // ADICIONA COMPRIMENTO AO OBSTÁCULO
      SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
      cout << " ";
    }

    if (bird_y <= 0 || bird_y >= 20) // PAUSA O JOGO CASO HAJA UMA COLISÃO COM O TETO OU O CHÃO
    {
      system("cls"); // LIMPA O TERMINAL DO JOGO
      // POSICIONA A MENSAGEM DE GAME OVER
      coord.X = game_over_x;
      coord.Y = game_over_y;
      SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
      cout << "GAME OVER";

      estaVoando = false; // NÃO ESTÁ MAIS VOANDO POR QUE COLIDIU COM O TETO OU O CHÃO
      system("pause");    // PAUSA O JOGO
    }

    // VERIFICA COLISÃO
    if (kbhit())       // VERIFICA COMANDO DO JOGADOR
    {                  // VERIFICA SE UMA TECLA FOI PRESSIONADA
      tecla = getch(); // VERIFICA COMANDO DO JOGADOR
    }

    if (bird_x == obstaculo_x + 1) // ADICIONA PONTUAÇÃO AO PLACAR AO PASSAR DO OBSTÁCULO
    {
      placar++;                                              // ADICIONA MAIS UM NA PONTUAÇÃO
      if (placar != 0 && placar % 5 == 0 && velocidade > 40) // SE O VALOR DA PONTUAÇÃO É DIFERENTE DE ZERO E MULTIPLO DE CINCO E VELOCIDADE MAIOR QUE QUARENTA PARA NÃO FICAR IMPOSSÍVEL DE JOGAR
      {
        velocidade -= 20; // A VELOCIDADE É AUMENTADA
      }
    }

    if (tecla == 'w') // PÁSSARO CAI 1 POSIÇÃO SE NÃO FOR PRESSIONADO PARA SUBIR
    {
      bird_y--;
      tecla = '0';
    }
    else
    {
      bird_y++;
    }

    obstaculo_x--; // OBSTÁCULO AVANÇA UMA POSIÇÃO PARA ESQUERDA

    Sleep(velocidade); // TEMPO DE ESPERA

    // REMOVE O RASTRO DO PÁSSARO PARA CIMA
    coord.Y = bird_y - 1;
    coord.X = bird_x;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    if (!(bird_y == 1))
    {
      cout << " ";
    }

    // REMOVE O RASTRO DO PÁSSARO PARA BAIXO
    coord.Y = bird_y + 1;
    coord.X = bird_x;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    if (!(bird_y == 19))
    {
      cout << " ";
    }

    if (obstaculo_x == bird_x && (bird_y < numeroAleatorio - 2 || bird_y > numeroAleatorio + 2)) // PAUSA O JOGO CASO HAJA UMA COLISÃO COM O OBSTÁCULO
    {
      system("cls"); // LIMPA O TERMINAL DO JOGO
      // POSICIONA A MENSAGEM DE GAME OVER
      coord.X = game_over_x;
      coord.Y = game_over_y;
      SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
      cout << "GAME OVER";

      estaVoando = false; // NÃO ESTÁ MAIS VOANDO POR QUE COLIDIU COM O OBSTÁCULO
      system("pause");    // PAUSA O JOGO
    }

    if (obstaculo_x < 0) // SE A POSIÇÃO DO OBSTÁCULO É MENOR QUE ZERO NO CENÁRIO
    {
      coord.X = obstaculo_x + 1; // ADICIONA MAIS UM PARA EXCLUIR O RASTRO DA POSIÇÃO ZERO DO CENÁRIO A CORDENADA
      while (obstaculo_y > 0)    // ENQUANTO O Y DO OBSTÁCULO FOR MAIOR QUE ZERO
      {
        // REMOVE O RASTRO DA ÚLTIMA POSIÇÃO DO OBSTÁCULO NO CENÁRIO
        coord.Y = obstaculo_y; // ADICIONA O VALOR ATUAL DO Y DO OBSTÁCULO A CORDENADA
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        cout << " ";
        obstaculo_y--; // PEGA A POSIÇÃO ATUAL DO Y DO OBSTÁCULO E SUBTRAI POR UM
      }

      numeroAleatorio = rand() % 15 + 3; // GERA NÚMEROS ALEATÓRIOS 3 e 17
      obstaculo_x = 130;                 // VOLTA O OBSTÁCULO PARA A POSIÇÃO INICIAL
    }
  }

  return 0;
}
