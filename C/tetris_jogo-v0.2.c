/*
 * TETRIS EM C - ANSI/UTF-8
 * C99, sem bibliotecas externas.
 *
 * Controles:
 * A/a = esquerda
 * D/d = direita
 * S/s = acelerar
 * Espaço = girar
 * R/r = reiniciar
 * Q/q = sair
 *
 * Compilar:
 *   gcc -o tetris_jogo tetris_jogo.c -std=c99
 *
 * Executar:
 *   ./tetris_jogo
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>

#define GRADE_LARGURA 10
#define GRADE_ALTURA 20
#define TAMANHO_BLOCO 30
#define VEL_QUEDA_BASE 30
#define TOTAL_FASES 10

typedef struct {
    unsigned char r, g, b, a;
} Color;

typedef struct {
    int x, y;
    int tipo;
    int rotacao;
} Tetrominó;

typedef struct {
    int grade[GRADE_ALTURA][GRADE_LARGURA];
    int pontuacao;
    int fase;
    int linhas_eliminadas;
    Tetrominó peça_atual;
    Tetrominó proxima_peça;
    int contador_queda;
    int velocidade_queda;
    int fim_jogo;
    int frames_emoji;
} EstadoJogo;

typedef struct {
    Color fundo;
    Color grade;
    Color blocos[7];
    Color texto;
} PaletaFase;

static struct termios terminal_original;
static int terminal_configurado = 0;

/* Formatos base dos 7 tetrominós.
   Cada peça ocupa uma matriz 4x4. */
static const int FORMAS[7][4][4] = {
    /* I */
    {
        {0,0,0,0},
        {1,1,1,1},
        {0,0,0,0},
        {0,0,0,0}
    },
    /* O */
    {
        {0,1,1,0},
        {0,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    },
    /* T */
    {
        {0,1,0,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    },
    /* S */
    {
        {0,1,1,0},
        {1,1,0,0},
        {0,0,0,0},
        {0,0,0,0}
    },
    /* Z */
    {
        {1,1,0,0},
        {0,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    },
    /* J */
    {
        {1,0,0,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    },
    /* L */
    {
        {0,0,1,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    }
};

static const char *NOMES_FASES[TOTAL_FASES] = {
    "NEON PURPURA",
    "LARANJA QUEIMADO",
    "VERDE FLORESTA",
    "AZUL PROFUNDO",
    "VERMELHO FOGO",
    "ROSA PASTEL",
    "VERDE NEON",
    "AZUL OCEANO",
    "ROXO MISTICO",
    "ARCO-IRIS"
};

static void limpar_tela(void) {
    printf("\033[2J\033[H");
}

static void mover_cursor(int linha, int coluna) {
    printf("\033[%d;%dH", linha, coluna);
}

static void cor_texto(Color c) {
    printf("\033[38;2;%d;%d;%dm", c.r, c.g, c.b);
}

static void cor_fundo(Color c) {
    printf("\033[48;2;%d;%d;%dm", c.r, c.g, c.b);
}

static void resetar_cor(void) {
    printf("\033[0m");
}

static void configurar_terminal(void) {
    if (tcgetattr(STDIN_FILENO, &terminal_original) == -1)
        return;

    struct termios novo = terminal_original;
    novo.c_lflag &= (tcflag_t) ~(ICANON | ECHO);
    novo.c_cc[VMIN] = 0;
    novo.c_cc[VTIME] = 0;

    tcsetattr(STDIN_FILENO, TCSANOW, &novo);
    terminal_configurado = 1;

    printf("\033[?25l");
}

static void restaurar_terminal(void) {
    if (terminal_configurado)
        tcsetattr(STDIN_FILENO, TCSANOW, &terminal_original);

    printf("\033[0m\033[?25h\n");
}

static int entrada_disponivel(void) {
    int bytes = 0;
    ioctl(STDIN_FILENO, FIONREAD, &bytes);
    return bytes > 0;
}

static int ler_tecla(void) {
    unsigned char tecla;
    if (!entrada_disponivel())
        return -1;

    if (read(STDIN_FILENO, &tecla, 1) == 1)
        return tecla;

    return -1;
}

static const char *converter_numeral_romano(int numero) {
    static char romano[64];
    static const struct {
        int valor;
        const char *simbolo;
    } tabela[] = {
        {1000,"M"},{900,"CM"},{500,"D"},{400,"CD"},
        {100,"C"},{90,"XC"},{50,"L"},{40,"XL"},
        {10,"X"},{9,"IX"},{5,"V"},{4,"IV"},{1,"I"}
    };

    romano[0] = '\0';

    if (numero == 0)
        return "0";

    for (size_t i = 0; i < sizeof(tabela)/sizeof(tabela[0]); ++i) {
        while (numero >= tabela[i].valor) {
            strcat(romano, tabela[i].simbolo);
            numero -= tabela[i].valor;
        }
    }

    return romano;
}

static PaletaFase obter_paleta(int fase) {
    PaletaFase p;
    memset(&p, 0, sizeof(p));

    /* 10 paletas, uma por fase. */
    switch (fase) {
        case 1:
            p.fundo=(Color){18,8,28,255}; p.grade=(Color){70,30,90,255};
            p.blocos[0]=(Color){0,255,255,255}; p.blocos[1]=(Color){220,0,255,255};
            p.blocos[2]=(Color){255,0,180,255}; p.blocos[3]=(Color){120,40,255,255};
            p.blocos[4]=(Color){255,30,180,255}; p.blocos[5]=(Color){80,100,255,255};
            p.blocos[6]=(Color){190,60,255,255}; p.texto=(Color){240,220,255,255}; break;
        case 2:
            p.fundo=(Color){35,16,5,255}; p.grade=(Color){120,55,10,255};
            p.blocos[0]=(Color){255,150,0,255}; p.blocos[1]=(Color){255,220,20,255};
            p.blocos[2]=(Color){255,70,120,255}; p.blocos[3]=(Color){255,100,20,255};
            p.blocos[4]=(Color){255,40,40,255}; p.blocos[5]=(Color){255,190,50,255};
            p.blocos[6]=(Color){255,90,180,255}; p.texto=(Color){255,235,190,255}; break;
        case 3:
            p.fundo=(Color){5,28,16,255}; p.grade=(Color){20,95,55,255};
            p.blocos[0]=(Color){0,240,210,255}; p.blocos[1]=(Color){180,255,0,255};
            p.blocos[2]=(Color){0,255,100,255}; p.blocos[3]=(Color){50,210,80,255};
            p.blocos[4]=(Color){0,180,130,255}; p.blocos[5]=(Color){100,255,40,255};
            p.blocos[6]=(Color){0,255,180,255}; p.texto=(Color){210,255,225,255}; break;
        case 4:
            p.fundo=(Color){5,15,40,255}; p.grade=(Color){20,70,130,255};
            p.blocos[0]=(Color){0,220,255,255}; p.blocos[1]=(Color){50,100,255,255};
            p.blocos[2]=(Color){160,50,255,255}; p.blocos[3]=(Color){0,180,220,255};
            p.blocos[4]=(Color){70,50,255,255}; p.blocos[5]=(Color){100,150,255,255};
            p.blocos[6]=(Color){170,80,255,255}; p.texto=(Color){215,235,255,255}; break;
        case 5:
            p.fundo=(Color){38,5,5,255}; p.grade=(Color){120,25,15,255};
            p.blocos[0]=(Color){255,60,30,255}; p.blocos[1]=(Color){255,190,0,255};
            p.blocos[2]=(Color){255,30,30,255}; p.blocos[3]=(Color){255,100,0,255};
            p.blocos[4]=(Color){220,20,10,255}; p.blocos[5]=(Color){255,120,20,255};
            p.blocos[6]=(Color){255,220,50,255}; p.texto=(Color){255,225,205,255}; break;
        case 6:
            p.fundo=(Color){35,12,28,255}; p.grade=(Color){130,55,100,255};
            p.blocos[0]=(Color){255,170,220,255}; p.blocos[1]=(Color){255,220,240,255};
            p.blocos[2]=(Color){230,80,190,255}; p.blocos[3]=(Color){255,120,210,255};
            p.blocos[4]=(Color){255,70,150,255}; p.blocos[5]=(Color){245,200,255,255};
            p.blocos[6]=(Color){255,150,255,255}; p.texto=(Color){255,235,250,255}; break;
        case 7:
            p.fundo=(Color){8,35,8,255}; p.grade=(Color){40,120,25,255};
            p.blocos[0]=(Color){50,255,80,255}; p.blocos[1]=(Color){190,255,30,255};
            p.blocos[2]=(Color){0,255,130,255}; p.blocos[3]=(Color){100,255,0,255};
            p.blocos[4]=(Color){20,230,60,255}; p.blocos[5]=(Color){230,255,255,255};
            p.blocos[6]=(Color){140,255,50,255}; p.texto=(Color){230,255,225,255}; break;
        case 8:
            p.fundo=(Color){4,25,38,255}; p.grade=(Color){20,100,130,255};
            p.blocos[0]=(Color){0,200,255,255}; p.blocos[1]=(Color){40,240,220,255};
            p.blocos[2]=(Color){40,120,255,255}; p.blocos[3]=(Color){0,255,190,255};
            p.blocos[4]=(Color){30,170,255,255}; p.blocos[5]=(Color){180,245,255,255};
            p.blocos[6]=(Color){80,255,255,255}; p.texto=(Color){220,250,255,255}; break;
        case 9:
            p.fundo=(Color){22,5,38,255}; p.grade=(Color){80,25,120,255};
            p.blocos[0]=(Color){200,50,255,255}; p.blocos[1]=(Color){255,80,220,255};
            p.blocos[2]=(Color){130,50,255,255}; p.blocos[3]=(Color){230,0,180,255};
            p.blocos[4]=(Color){180,30,255,255}; p.blocos[5]=(Color){100,160,255,255};
            p.blocos[6]=(Color){255,100,255,255}; p.texto=(Color){245,220,255,255}; break;
        default:
            p.fundo=(Color){10,10,18,255}; p.grade=(Color){90,90,100,255};
            p.blocos[0]=(Color){0,255,255,255}; p.blocos[1]=(Color){255,255,0,255};
            p.blocos[2]=(Color){180,0,255,255}; p.blocos[3]=(Color){0,255,0,255};
            p.blocos[4]=(Color){255,0,0,255}; p.blocos[5]=(Color){0,100,255,255};
            p.blocos[6]=(Color){255,140,0,255}; p.texto=(Color){255,255,255,255}; break;
    }

    return p;
}

static Tetrominó gerar_tetrominó(void) {
    Tetrominó t;
    t.tipo = rand() % 7;
    t.rotacao = 0;
    t.x = (GRADE_LARGURA / 2) - 2;
    t.y = 0;
    return t;
}

static void bloco_rotacionado(const Tetrominó *p, int linha, int coluna, int *valor) {
    int x = coluna;
    int y = linha;

    switch (p->rotacao % 4) {
        case 0:
            *valor = FORMAS[p->tipo][y][x];
            break;
        case 1:
            *valor = FORMAS[p->tipo][3-x][y];
            break;
        case 2:
            *valor = FORMAS[p->tipo][3-y][3-x];
            break;
        default:
            *valor = FORMAS[p->tipo][x][3-y];
            break;
    }
}

static int pode_mover(const EstadoJogo *jogo, const Tetrominó *p, int dx, int dy, int nova_rotacao) {
    Tetrominó teste = *p;
    teste.x += dx;
    teste.y += dy;
    teste.rotacao = nova_rotacao;

    for (int y = 0; y < 4; ++y) {
        for (int x = 0; x < 4; ++x) {
            int ocupado;
            bloco_rotacionado(&teste, y, x, &ocupado);

            if (!ocupado)
                continue;

            int gx = teste.x + x;
            int gy = teste.y + y;

            if (gx < 0 || gx >= GRADE_LARGURA || gy >= GRADE_ALTURA)
                return 0;

            if (gy >= 0 && jogo->grade[gy][gx] != 0)
                return 0;
        }
    }

    return 1;
}

static void colocar_peça(EstadoJogo *jogo) {
    Tetrominó p = jogo->peça_atual;

    for (int y = 0; y < 4; ++y) {
        for (int x = 0; x < 4; ++x) {
            int ocupado;
            bloco_rotacionado(&p, y, x, &ocupado);

            if (!ocupado)
                continue;

            int gx = p.x + x;
            int gy = p.y + y;

            if (gy >= 0 && gy < GRADE_ALTURA && gx >= 0 && gx < GRADE_LARGURA)
                jogo->grade[gy][gx] = p.tipo + 1;
        }
    }
}

static int detectar_linhas_completas(EstadoJogo *jogo) {
    int eliminadas = 0;

    for (int y = GRADE_ALTURA - 1; y >= 0; --y) {
        int completa = 1;

        for (int x = 0; x < GRADE_LARGURA; ++x) {
            if (jogo->grade[y][x] == 0) {
                completa = 0;
                break;
            }
        }

        if (completa) {
            for (int yy = y; yy > 0; --yy)
                memcpy(jogo->grade[yy], jogo->grade[yy - 1],
                       sizeof(jogo->grade[yy]));

            memset(jogo->grade[0], 0, sizeof(jogo->grade[0]));
            ++eliminadas;
            ++y; /* verifica novamente a linha que caiu */
        }
    }

    return eliminadas;
}

static void mudar_fase(EstadoJogo *jogo) {
    int nova_fase = (jogo->linhas_eliminadas / 10) + 1;

    if (nova_fase > TOTAL_FASES)
        nova_fase = TOTAL_FASES;

    if (nova_fase != jogo->fase) {
        jogo->fase = nova_fase;
        jogo->velocidade_queda = VEL_QUEDA_BASE - ((jogo->fase - 1) * 2);

        if (jogo->velocidade_queda < 4)
            jogo->velocidade_queda = 4;

        jogo->frames_emoji = 35;
    }
}

static void adicionar_pontuacao(EstadoJogo *jogo, int linhas) {
    switch (linhas) {
        case 1: jogo->pontuacao += 10; break;
        case 2: jogo->pontuacao += 20; break;
        case 3: jogo->pontuacao += 30; break;
        case 4: jogo->pontuacao += 40; break;
        default: break;
    }

    jogo->linhas_eliminadas += linhas;
    mudar_fase(jogo);
}

static void inicializar_jogo(EstadoJogo *jogo) {
    memset(jogo, 0, sizeof(*jogo));

    jogo->fase = 1;
    jogo->velocidade_queda = VEL_QUEDA_BASE;
    jogo->peça_atual = gerar_tetrominó();
    jogo->proxima_peça = gerar_tetrominó();
    jogo->contador_queda = 0;
    jogo->fim_jogo = 0;
    jogo->frames_emoji = 0;
}

static void reiniciar_jogo(EstadoJogo *jogo) {
    inicializar_jogo(jogo);
}

static void processar_entrada(EstadoJogo *jogo) {
    int tecla;

    while ((tecla = ler_tecla()) != -1) {
        switch (tecla) {
            case 'a':
            case 'A':
                if (pode_mover(jogo, &jogo->peça_atual, -1, 0,
                               jogo->peça_atual.rotacao))
                    jogo->peça_atual.x--;
                break;

            case 'd':
            case 'D':
                if (pode_mover(jogo, &jogo->peça_atual, 1, 0,
                               jogo->peça_atual.rotacao))
                    jogo->peça_atual.x++;
                break;

            case 's':
            case 'S':
                if (pode_mover(jogo, &jogo->peça_atual, 0, 1,
                               jogo->peça_atual.rotacao))
                    jogo->peça_atual.y++;
                break;

            case ' ':
                if (pode_mover(jogo, &jogo->peça_atual, 0, 0,
                               jogo->peça_atual.rotacao + 1))
                    jogo->peça_atual.rotacao =
                        (jogo->peça_atual.rotacao + 1) % 4;
                break;

            case 'r':
            case 'R':
                reiniciar_jogo(jogo);
                break;

            case 'q':
            case 'Q':
                jogo->fim_jogo = 1;
                break;
        }
    }
}

static void atualizar_jogo(EstadoJogo *jogo) {
    if (jogo->fim_jogo)
        return;

    jogo->contador_queda++;

    if (jogo->contador_queda < jogo->velocidade_queda)
        return;

    jogo->contador_queda = 0;

    if (pode_mover(jogo, &jogo->peça_atual, 0, 1,
                   jogo->peça_atual.rotacao)) {
        jogo->peça_atual.y++;
        return;
    }

    colocar_peça(jogo);

    int linhas = detectar_linhas_completas(jogo);
    if (linhas > 0)
        adicionar_pontuacao(jogo, linhas);

    jogo->peça_atual = jogo->proxima_peça;
    jogo->peça_atual.x = (GRADE_LARGURA / 2) - 2;
    jogo->peça_atual.y = 0;
    jogo->peça_atual.rotacao = 0;
    jogo->proxima_peça = gerar_tetrominó();

    if (!pode_mover(jogo, &jogo->peça_atual, 0, 0,
                   jogo->peça_atual.rotacao))
        jogo->fim_jogo = 1;
}

static void desenhar_bloco(Color c) {
    cor_fundo(c);
    printf("  ");
    resetar_cor();
}

static void desenhar_tela(const EstadoJogo *jogo) {
    PaletaFase paleta = obter_paleta(jogo->fase);
    limpar_tela();

    cor_texto(paleta.texto);
    printf("╔════════════════════════════════════╗   TETRIS ANSI\n");
    printf("║            T E T R I S             ║   FASE %s\n",
           converter_numeral_romano(jogo->fase));
    printf("╚════════════════════════════════════╝   %s\n\n",
           NOMES_FASES[jogo->fase - 1]);

    printf("    ╔");
    for (int x = 0; x < GRADE_LARGURA; ++x) printf("══");
    printf("╗\n");

    Tetrominó queda = jogo->peça_atual;

    for (int y = 0; y < GRADE_ALTURA; ++y) {
        printf("    ║");

        for (int x = 0; x < GRADE_LARGURA; ++x) {
            int valor = jogo->grade[y][x];

            for (int py = 0; py < 4; ++py) {
                for (int px = 0; px < 4; ++px) {
                    int ocupado;
                    bloco_rotacionado(&queda, py, px, &ocupado);

                    if (ocupado && queda.x + px == x && queda.y + py == y)
                        valor = queda.tipo + 1;
                }
            }

            if (valor > 0) {
                desenhar_bloco(paleta.blocos[valor - 1]);
            } else {
                cor_texto(paleta.grade);
                printf("· ");
                resetar_cor();
            }
        }

        printf("║\n");
    }

    printf("    ╚");
    for (int x = 0; x < GRADE_LARGURA; ++x) printf("══");
    printf("╝\n");

    cor_texto(paleta.texto);
    printf("\n    Pontuação: %s    Linhas: %s\n",
           converter_numeral_romano(jogo->pontuacao),
           converter_numeral_romano(jogo->linhas_eliminadas));

    printf("    Próxima peça: ");
    const char *nomes[7] = {"I","O","T","S","Z","J","L"};
    printf("%s\n", nomes[jogo->proxima_peça.tipo]);

    printf("\n    ⌨ A/D mover   S acelerar   ESPAÇO girar   R reiniciar   Q sair\n");

    if (jogo->frames_emoji > 0)
        printf("\n    😊 FASE %s ALCANÇADA! 🎉\n",
               converter_numeral_romano(jogo->fase));

    if (jogo->fim_jogo) {
        printf("\n    ☠️  FIM DE JOGO! Pressione R para reiniciar ou Q para sair.\n");
    }

    fflush(stdout);
}

int main(void) {
    srand((unsigned int)time(NULL));

    EstadoJogo jogo;
    inicializar_jogo(&jogo);

    configurar_terminal();
    atexit(restaurar_terminal);

    /* Aproximadamente 30 FPS. */
    while (!jogo.fim_jogo || 1) {
        processar_entrada(&jogo);

        if (jogo.fim_jogo) {
            desenhar_tela(&jogo);

            /* Permite R/Q no estado de fim de jogo. */
            while (jogo.fim_jogo) {
                usleep(50000);
                processar_entrada(&jogo);
                if (jogo.fim_jogo)
                    desenhar_tela(&jogo);
            }

            continue;
        }

        atualizar_jogo(&jogo);
        desenhar_tela(&jogo);

        if (jogo.frames_emoji > 0)
            jogo.frames_emoji--;

        usleep(33333);
    }

    return 0;
}
