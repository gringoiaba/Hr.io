Bem vindo ao Hr.io! (l�-se "agario")

Ao iniciar o jogo, a primeira tela apresentada � o menu principal.
Nele, haver�o algumas op��es dispon�veis:

- Start:
        Inicia uma sess�o de jogo. No in�cio, perguntaremos o nome de seu personagem
        que dever� ser exibido ao longo da sess�o (e mantido ao salvar seu jogo).
        Depois de inserir seu nome, o jogo ir� come�ar. Voc� pode controlar seu personagem
        usando o mouse, j� que a sua pe�a sempre segue o cursor. Ao longo do tabuleiro,
        haver�o bolinhas rosas que podem ser comidas para aumentar a sua �rea. Tamb�m haver�o
        bolinhas de outras cores, conforme indicadas na legenda do menu principal (mas cuidado,
        se fores menor que estas outras bolinhas, elas comer�o voc�!). Seu objetivo � ficar
        a maior quantidade de tempo vivo, e se voc� se sair bem, quem sabe at� colocar seu nome
        nos highscores do jogo.
        Voc� tamb�m pode pausar o jogo pressionando ESC, revelando algumas outras op��es:
        - Continue:
            Sai da pausa e continua o seu jogo.
        - Save:
            Salva o seu jogo para que ele possa ser jogado mais tarde.
        - Exit:
            Sai da partida e volta ao menu principal.

- Load:
    Carrega o �ltimo jogo salvo.

- HighScores:
    Mostra as 10 melhores pontua��es no jogo.

- Exit:
    Sai do jogo.

Jogo Por:
    - Eduardo A. Duarte (311408)
    - Pietro B. Carrara (318995)

Instru��es de compila��o:
    - Compile a raylib caso ela ainda n�o esteja compilada (cd raylib/src; make) (mingw32-make para windows)
    - Compile o Hr.io com os seguintes argumentos para o linker (linker settings no Code::Blocks)
        - Windows: -Lraylib/src/ -lraylib -lopengl32 -lgdi32 -lwinmm
        - Linux: -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
    - :D
