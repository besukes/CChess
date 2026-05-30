# CChess (SDL2)

Este projeto foi iniciado no dia **30 de maio de 2026** por três caloiros de Engenharia Informática naUMinho e consiste num jogo sobre o jogo clássico de xadrez com outras implementações diferentes e criativas.

O jogo utiliza a biblioteca **SDL2** e extensões associadas para criar uma aplicação gráfica em janela, com suporte a imagens, áudio e texto.

## Tecnologias Utilizadas

* Linguagem: **C**
* Bibliotecas:

  * SDL2
  * SDL2_image
  * SDL2_mixer
  * SDL2_ttf

## Estrutura do Projeto
```bash
.
├── gamefiles/  # Ficheiros código fonte (.c)
├── sfx/        # Ficheiros de áudio utilizados
├── musica/     # Música que implementamos para tocar ao longo do jogo
├── library/    # Headers (.h)
├── assets/     # Imagens e fontes necessárias ao projeto
├── build/      # Ficheiros objeto (.o) (gerado automaticamente pelo comando make)
├── Makefile
├── cchess      # Executável final , Jogo CChess(gerado automaticamente)
└── README.md   # Informações sobre o projeto
```

## Assets



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
./CChess
```

## Cŕeditos

Este jogo foi feito por Alberto Silva , Leandro Oliveira e Pedro Coutinho.
