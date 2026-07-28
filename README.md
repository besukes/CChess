# CChess (SDL2)

Este projeto foi iniciado no dia **30 de maio de 2026** por dois caloiros de Engenharia Informática na UMinho e consiste num jogo sobre o jogo clássico de xadrez com outras implementações diferentes e criativas.

O jogo utiliza a biblioteca **SDL2** e extensões associadas para criar uma aplicação gráfica em janela, com suporte a imagens, áudio e texto.

## Tecnologias Utilizadas

* Linguagem: **C**
* Bibliotecas:

  * SDL2
  * SDL2_image
  * SDL2_mixer
  * SDL2_ttf
  * SDL2_gfxPrimitives
  * Sys
  * Dirent


## Estrutura do Projeto
```bash
.
├── animations/    # Animações ao longo do jogo
├── assets/        # Imagens e fontes necessárias ao projeto
├── build/         # Ficheiros objeto (.o) (gerado automaticamente pelo comando make)
├── chess_engine/  # Ficheiros relativos a movimentação de peças + CChess IA
├── gamefiles/     # Ficheiro relativo ao progresso do utilizador no jogo (client settings)
├── library/       # Headers (.h) e ficheiros relativos a texturas
├── sfx/           # Ficheiros de áudio utilizados
├── src/           # Ficheiros fonte do jogo (maior parte dos .c)
├── music/        # Músicas que implementamos para tocar ao longo do jogo
├── cchess         # Executável final , Jogo CChess (gerado automaticamente)
├── Makefile
├── README.md      # Informações detalhadas sobre o projeto
├── todoList.txt   # Informações sobre adições pendentes do projeto
└── unused.txt     # Código não utilizado no projeto mas que pode ser útil
```

## Assets

Créditos especiais ao gemini e ao claude pois neste projeto são utilizadas várias imagens geradas por ambas as inteligências artificiais.

## Compilação

Para compilar o projeto, utilize o `make cchess`:

```bash
make
```

Será gerado um executável:

```
cchess
```

### Verificar dependências

Antes de compilar, pode verificar se todas as dependências estão instaladas:

```bash
make check
```

### Limpar ficheiros compilados

```bash
make clean
```

## Execução

Após compilação:

```bash
./cchess
```

