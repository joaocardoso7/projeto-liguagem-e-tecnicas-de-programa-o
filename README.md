# RPG Pokémon em C (Terminal)

**Disciplina:** Linguagem e Técnicas de Programação  
**Docente:** Prof. Dacio Machado  
**Curso:** Engenharia de Software / ADS  

---

## 1. Integrantes da Equipe

| Nome Completo | RA | Responsabilidade Principal |
| :--- | :--- | :--- |
| João Vitor Cardoso da Silva | 26001322-2 | Arquitetura geral, fluxo principal (`main.c`), persistência e documentação técnica |
| Arthur Navarete | 26002044-2 | Modelagem de dados (`pokemon.h` / `tone.h`), catálogo de criaturas, sistema de inventário e música tema |
| André Dias | 26001552-2 | Mecânica de combate (`batalha.c` / `batalha.h`), cálculo de dano e capturas |

---

## 2. Descrição e Definição do Problema

O projeto consiste no desenvolvimento de um jogo de RPG por turnos executado via terminal de comandos (consola), inspirado no universo Pokémon. O utilizador atua como um treinador que explora rotas, enfrenta criaturas selvagens em combates por rondas, gere itens de suporte (poções e pokébolas), recruta novos monstrinhos para a equipa e guarda o progresso no disco.

O desenvolvimento abrange todos os conceitos fundamentais exigidos na ementa da disciplina:
- **Entrada e Saída:** Menus intuitivos e mensagens descritivas ao utilizador.
- **Estruturas de Controlo:** Ciclos de repetição (`while`, `for`) e desvios condicionais (`switch-case`, `if-else`).
- **Modularização:** Organização rigorosa em ficheiros de cabeçalho (`.h`) e código-fonte (`.c`).
- **Estruturas de Dados:** Vetores homogéneos e registos heterogéneos compostos (`struct`).
- **Persistência em Ficheiros:** Gravação e recuperação de gravações de jogo via `fopen`, `fprintf`, `fscanf` e `fclose`.

---

## 3. Arquitetura do Sistema e Modularização

O projeto adota uma divisão modular limpa para manter o código testável e desacoplado:

```text
pokemon-rpg/
├── docs/
│   └── documento_entrega_24_set.pdf
├── include/
│   ├── pokemon.h       # Declarações das structs e catálogo de Pokémon/ataques
│   ├── batalha.h       # Protótipos das funções do motor de combate
│   ├── arquivos.h      # Protótipos das rotinas de salvar/carregar jogo
│   └── tone.h          # Música tema do jogo
├── src/
│   ├── pokemon.c       # Implementação das regras dos Pokémon
│   ├── batalha.c       # Implementação do ciclo de rodadas e cálculo de dano
│   ├── arquivos.c      # Implementação do tratamento e leitura/escrita de arquivos
│   └── main.c          # Ponto de entrada, menu inicial e loop central
├── data/
│   └── save.txt        # Registo persistente dos dados do jogador
└── README.md           # Documentação técnica do repositório
```

---

## 4. Modelagem de Dados (`structs`)

O projeto faz uso de estruturas heterogéneas aninhadas e vetores para mapear as entidades do jogo:

```c
#ifndef POKEMON_H
#define POKEMON_H

#define MAX_ATAQUES 4
#define MAX_TIME 6

// Representação de uma habilidade/golpe
typedef struct {
    char nome[30];
    int poder;
    char tipo[15]; // "Fogo", "Agua", "Planta", "Normal"
} Ataque;

// Representação de uma criatura
typedef struct {
    char nome[30];
    char tipo[15];
    int vida_max;
    int vida_atual;
    int nivel;
    int ataque;
    int defesa;
    Ataque ataques[MAX_ATAQUES]; // Vetor homogéneo de structs
} Pokemon;

// Representação do Jogador / Treinador
typedef struct {
    char nome[50];
    Pokemon time[MAX_TIME];
    int qtd_pokemon;
    int pokebolas;
    int pocoes;
} Treinador;

#endif
```

---

##
