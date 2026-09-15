#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>

// ============= CONSTANTES =============
#define GRADE_LARGURA 10
#define GRADE_ALTURA 20
#define TAMANHO_BLOCO 30
#define VEL_QUEDA_BASE 30
#define TOTAL_FASES 10

// ============= TIPOS DE CORES =============
typedef struct {
    unsigned char r, g, b, a;
} Color;

// ============= ESTRUTURAS =============
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

// ============= CORES POR FASE =============
typedef struct {
    Color fundo;
    Color grade;
    Color blocos[7];
    Color texto;
} PaletaFase;

// ============= PROTÓTIPOS =============
void inicializar_jogo(EstadoJogo *estado);
void processar_entrada(EstadoJogo *estado);
void atualizar_jogo(EstadoJogo *estado);
void desenhar_tela(EstadoJogo *estado, PaletaFase paleta);
void gerar_tetrominó(Tetrominó *t, int tipo);
int pode_mover(EstadoJogo *estado, int dx, int dy, int rotacao);
void colocar_peça(EstadoJogo *estado);
void detectar_linhas_completas(EstadoJogo *estado);
void mudar_fase(EstadoJogo *estado);
PaletaFase obter_paleta(int fase);
void converter_numeral_romano(int num, char *str);
void limpar_tela(void);
void mover_cursor(int x, int y);
void cor_texto(int r, int g, int b);
void cor_fundo(int r, int g, int b);
void resetar_cor(void);
void configurar_terminal(void);
void restaurar_terminal(void);

// ============= TETROMINÓS (7 TIPOS) =============
int tetrominós[7][4][4] = {
    // I (Cyan)
    {
        {0, 0, 0, 0},
        {1, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    // O (Amarelo)
    {
        {1, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    // T (Roxo)
    {
        {0, 1, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    // S (Verde)
    {
        {0, 1, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    // Z (Vermelho)
    {
        {1, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    // J (Azul)
    {
        {1, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    // L (Laranja)
    {
        {0, 0, 1, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }
};

// ============= FUNÇÕES GRÁFICAS ANSI =============

void limpar_tela(void) {
    printf("\033[2J\033[H");
    fflush(stdout);
}

void mover_cursor(int x, int y) {
    printf("\033[%d;%dH", y + 1, x + 1);
    fflush(stdout);
}

void cor_texto(int r, int g, int b) {
    printf("\033[38;2;%d;%d;%dm", r, g, b);
    fflush(stdout);
}

void cor_fundo(int r, int g, int b) {
    printf("\033[48;2;%d;%d;%dm", r, g, b);
    fflush(stdout);
}

void resetar_cor(void) {
    printf("\033[0m");
    fflush(stdout);
}

void configurar_terminal(void) {
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    tty.c_lflag &= ~(ICANON | ECHO);
    tty.c_cc[VMIN] = 0;
    tty.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

void restaurar_terminal(void) {
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    tty.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

// ============= FUNÇÕES DE JOGO =============

PaletaFase obter_paleta(int fase) {
    PaletaFase paleta;
    
    switch(fase) {
        case 1: // Neon Púrpura
            paleta.fundo = (Color){20, 10, 30, 255};
            paleta.grade = (Color){80, 40, 120, 255};
            paleta.blocos[0] = (Color){0, 255, 255, 255};
            paleta.blocos[1] = (Color){255, 255, 0, 255};
            paleta.blocos[2] = (Color){200, 50, 200, 255};
            paleta.blocos[3] = (Color){0, 255, 100, 255};
            paleta.blocos[4] = (Color){255, 50, 100, 255};
            paleta.blocos[5] = (Color){0, 150, 255, 255};
            paleta.blocos[6] = (Color){255, 150, 0, 255};
            paleta.texto = (Color){255, 100, 255, 255};
            break;
            
        case 2: // Laranja Queimado
            paleta.fundo = (Color){40, 20, 10, 255};
            paleta.grade = (Color){120, 60, 20, 255};
            paleta.blocos[0] = (Color){0, 200, 255, 255};
            paleta.blocos[1] = (Color){255, 200, 0, 255};
            paleta.blocos[2] = (Color){255, 80, 80, 255};
            paleta.blocos[3] = (Color){0, 255, 100, 255};
            paleta.blocos[4] = (Color){255, 100, 200, 255};
            paleta.blocos[5] = (Color){100, 200, 255, 255};
            paleta.blocos[6] = (Color){255, 150, 0, 255};
            paleta.texto = (Color){255, 150, 100, 255};
            break;
            
        case 3: // Verde Floresta
            paleta.fundo = (Color){10, 30, 20, 255};
            paleta.grade = (Color){40, 100, 60, 255};
            paleta.blocos[0] = (Color){0, 255, 200, 255};
            paleta.blocos[1] = (Color){200, 255, 0, 255};
            paleta.blocos[2] = (Color){100, 200, 100, 255};
            paleta.blocos[3] = (Color){0, 200, 100, 255};
            paleta.blocos[4] = (Color){255, 100, 150, 255};
            paleta.blocos[5] = (Color){100, 150, 255, 255};
            paleta.blocos[6] = (Color){200, 100, 0, 255};
            paleta.texto = (Color){100, 255, 150, 255};
            break;
            
        case 4: // Azul Profundo
            paleta.fundo = (Color){10, 20, 40, 255};
            paleta.grade = (Color){40, 80, 150, 255};
            paleta.blocos[0] = (Color){0, 255, 255, 255};
            paleta.blocos[1] = (Color){255, 200, 0, 255};
            paleta.blocos[2] = (Color){200, 100, 255, 255};
            paleta.blocos[3] = (Color){100, 255, 100, 255};
            paleta.blocos[4] = (Color){255, 100, 100, 255};
            paleta.blocos[5] = (Color){0, 200, 255, 255};
            paleta.blocos[6] = (Color){255, 150, 0, 255};
            paleta.texto = (Color){100, 200, 255, 255};
            break;
            
        case 5: // Vermelho Fogo
            paleta.fundo = (Color){40, 10, 10, 255};
            paleta.grade = (Color){150, 50, 30, 255};
            paleta.blocos[0] = (Color){0, 255, 200, 255};
            paleta.blocos[1] = (Color){255, 255, 0, 255};
            paleta.blocos[2] = (Color){255, 100, 50, 255};
            paleta.blocos[3] = (Color){0, 255, 100, 255};
            paleta.blocos[4] = (Color){255, 50, 150, 255};
            paleta.blocos[5] = (Color){50, 150, 255, 255};
            paleta.blocos[6] = (Color){255, 150, 0, 255};
            paleta.texto = (Color){255, 150, 100, 255};
            break;
            
        case 6: // Rosa Pastel
            paleta.fundo = (Color){40, 20, 35, 255};
            paleta.grade = (Color){150, 100, 130, 255};
            paleta.blocos[0] = (Color){200, 255, 200, 255};
            paleta.blocos[1] = (Color){255, 200, 200, 255};
            paleta.blocos[2] = (Color){200, 200, 255, 255};
            paleta.blocos[3] = (Color){255, 200, 255, 255};
            paleta.blocos[4] = (Color){255, 255, 200, 255};
            paleta.blocos[5] = (Color){200, 255, 255, 255};
            paleta.blocos[6] = (Color){255, 150, 200, 255};
            paleta.texto = (Color){255, 150, 200, 255};
            break;
            
        case 7: // Verde Neon
            paleta.fundo = (Color){10, 20, 10, 255};
            paleta.grade = (Color){50, 150, 50, 255};
            paleta.blocos[0] = (Color){0, 255, 200, 255};
            paleta.blocos[1] = (Color){200, 255, 0, 255};
            paleta.blocos[2] = (Color){150, 255, 50, 255};
            paleta.blocos[3] = (Color){0, 255, 100, 255};
            paleta.blocos[4] = (Color){255, 100, 200, 255};
            paleta.blocos[5] = (Color){100, 200, 255, 255};
            paleta.blocos[6] = (Color){255, 200, 0, 255};
            paleta.texto = (Color){150, 255, 100, 255};
            break;
            
        case 8: // Azul Oceano
            paleta.fundo = (Color){10, 25, 40, 255};
            paleta.grade = (Color){30, 100, 150, 255};
            paleta.blocos[0] = (Color){100, 255, 255, 255};
            paleta.blocos[1] = (Color){255, 200, 100, 255};
            paleta.blocos[2] = (Color){150, 100, 255, 255};
            paleta.blocos[3] = (Color){100, 255, 150, 255};
            paleta.blocos[4] = (Color){255, 150, 100, 255};
            paleta.blocos[5] = (Color){150, 200, 255, 255};
            paleta.blocos[6] = (Color){200, 255, 150, 255};
            paleta.texto = (Color){150, 220, 255, 255};
            break;
            
        case 9: // Roxo Místico
            paleta.fundo = (Color){30, 10, 40, 255};
            paleta.grade = (Color){100, 50, 150, 255};
            paleta.blocos[0] = (Color){200, 100, 255, 255};
            paleta.blocos[1] = (Color){255, 200, 255, 255};
            paleta.blocos[2] = (Color){200, 150, 255, 255};
            paleta.blocos[3] = (Color){100, 200, 255, 255};
            paleta.blocos[4] = (Color){255, 100, 200, 255};
            paleta.blocos[5] = (Color){150, 255, 200, 255};
            paleta.blocos[6] = (Color){255, 200, 100, 255};
            paleta.texto = (Color){200, 150, 255, 255};
            break;
            
        default: // 10 - Arco-íris
            paleta.fundo = (Color){20, 20, 20, 255};
            paleta.grade = (Color){80, 80, 80, 255};
            paleta.blocos[0] = (Color){255, 0, 0, 255};
            paleta.blocos[1] = (Color){255, 128, 0, 255};
            paleta.blocos[2] = (Color){255, 255, 0, 255};
            paleta.blocos[3] = (Color){0, 255, 0, 255};
            paleta.blocos[4] = (Color){0, 0, 255, 255};
            paleta.blocos[5] = (Color){75, 0, 130, 255};
            paleta.blocos[6] = (Color){148, 0, 211, 255};
            paleta.texto = (Color){255, 200, 255, 255};
    }
    
    return paleta;
}

void converter_numeral_romano(int num, char *str) {
    int valores[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const char *simbolos[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    
    strcpy(str, "");
    for (int i = 0; i < 13; i++) {
        while (num >= valores[i]) {
            strcat(str, simbolos[i]);
            num -= valores[i];
        }
    }
}

void gerar_tetrominó(Tetrominó *t, int tipo) {
    t->tipo = tipo % 7;
    t->x = 3;
    t->y = 0;
    t->rotacao = 0;
}

int bloco_rotacionado(int tipo, int rotacao, int x, int y) {
    int rx = x;
    int ry = y;

    switch (rotacao % 4) {
        case 1:
            rx = 3 - y;
            ry = x;
            break;
        case 2:
            rx = 3 - x;
            ry = 3 - y;
            break;
        case 3:
            rx = y;
            ry = 3 - x;
            break;
        default:
            break;
    }

    if (rx < 0 || rx >= 4 || ry < 0 || ry >= 4) {
        return 0;
    }

    return tetrominós[tipo][ry][rx];
}

int pode_mover(EstadoJogo *estado, int dx, int dy, int rotacao) {
    Tetrominó t = estado->peça_atual;
    t.x += dx;
    t.y += dy;
    int nova_rotacao = (t.rotacao + rotacao) % 4;

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (!bloco_rotacionado(t.tipo, nova_rotacao, x, y)) {
                continue;
            }

            int px = t.x + x;
            int py = t.y + y;

            if (px < 0 || px >= GRADE_LARGURA || py >= GRADE_ALTURA) {
                return 0;
            }
            if (py >= 0 && estado->grade[py][px] != 0) {
                return 0;
            }
        }
    }
    return 1;
}

void colocar_peça(EstadoJogo *estado) {
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (bloco_rotacionado(estado->peça_atual.tipo, estado->peça_atual.rotacao, x, y)) {
                int px = estado->peça_atual.x + x;
                int py = estado->peça_atual.y + y;

                if (py >= 0) {
                    estado->grade[py][px] = estado->peça_atual.tipo + 1;
                }
            }
        }
    }
    
    detectar_linhas_completas(estado);
    
    estado->peça_atual = estado->proxima_peça;
    gerar_tetrominó(&estado->proxima_peça, rand() % 7);
    
    if (!pode_mover(estado, 0, 0, 0)) {
        estado->fim_jogo = 1;
    }
}

void detectar_linhas_completas(EstadoJogo *estado) {
    int linhas_removidas = 0;
    
    for (int y = GRADE_ALTURA - 1; y >= 0; y--) {
        int linha_completa = 1;
        
        for (int x = 0; x < GRADE_LARGURA; x++) {
            if (estado->grade[y][x] == 0) {
                linha_completa = 0;
                break;
            }
        }
        
        if (linha_completa) {
            linhas_removidas++;
            
            for (int yy = y; yy > 0; yy--) {
                for (int x = 0; x < GRADE_LARGURA; x++) {
                    estado->grade[yy][x] = estado->grade[yy - 1][x];
                }
            }
            for (int x = 0; x < GRADE_LARGURA; x++) {
                estado->grade[0][x] = 0;
            }
            y++;
        }
    }
    
    if (linhas_removidas > 0) {
        estado->linhas_eliminadas += linhas_removidas;
        
        switch(linhas_removidas) {
            case 1:
                estado->pontuacao += 10;
                break;
            case 2:
                estado->pontuacao += 20;
                break;
            case 3:
                estado->pontuacao += 30;
                break;
            case 4:
                estado->pontuacao += 40;
                break;
        }
        
        if (estado->linhas_eliminadas % 10 == 0 && estado->fase < TOTAL_FASES) {
            mudar_fase(estado);
            estado->frames_emoji = 120;
        }
    }
}

void mudar_fase(EstadoJogo *estado) {
    estado->fase++;
    estado->velocidade_queda = VEL_QUEDA_BASE - (estado->fase - 1) * 2;
    if (estado->velocidade_queda < 3) {
        estado->velocidade_queda = 3;
    }
}

void inicializar_jogo(EstadoJogo *estado) {
    estado->fase = 1;
    estado->pontuacao = 0;
    estado->linhas_eliminadas = 0;
    estado->velocidade_queda = VEL_QUEDA_BASE;
    estado->contador_queda = 0;
    estado->fim_jogo = 0;
    estado->frames_emoji = 0;
    
    for (int y = 0; y < GRADE_ALTURA; y++) {
        for (int x = 0; x < GRADE_LARGURA; x++) {
            estado->grade[y][x] = 0;
        }
    }
    
    gerar_tetrominó(&estado->peça_atual, rand() % 7);
    gerar_tetrominó(&estado->proxima_peça, rand() % 7);
}

void processar_entrada(EstadoJogo *estado) {
    char c;
    if (read(STDIN_FILENO, &c, 1) > 0) {
        switch(c) {
            case 'a':
            case 'A':
                if (pode_mover(estado, -1, 0, 0)) {
                    estado->peça_atual.x--;
                }
                break;
            case 'd':
            case 'D':
                if (pode_mover(estado, 1, 0, 0)) {
                    estado->peça_atual.x++;
                }
                break;
            case 's':
            case 'S':
                if (pode_mover(estado, 0, 1, 0)) {
                    estado->peça_atual.y++;
                }
                break;
            case ' ':
                if (pode_mover(estado, 0, 0, 1)) {
                    estado->peça_atual.rotacao = (estado->peça_atual.rotacao + 1) % 4;
                }
                break;
            case 'r':
            case 'R':
                inicializar_jogo(estado);
                break;
            case 'q':
            case 'Q':
                exit(0);
                break;
        }
    }
}

void atualizar_jogo(EstadoJogo *estado) {
    if (estado->fim_jogo) return;
    
    estado->contador_queda++;
    
    if (estado->contador_queda >= estado->velocidade_queda) {
        estado->contador_queda = 0;
        
        if (pode_mover(estado, 0, 1, 0)) {
            estado->peça_atual.y++;
        } else {
            colocar_peça(estado);
        }
    }
    
    if (estado->frames_emoji > 0) {
        estado->frames_emoji--;
    }
}

void desenhar_tela(EstadoJogo *estado, PaletaFase paleta) {
    limpar_tela();
    
    int offset_x = 2;
    int offset_y = 1;
    
    cor_texto(200, 200, 200);
    mover_cursor(0, 0);
    printf("╔════════════════════════════════════════════════════════╗");
    mover_cursor(0, 1);
    printf("║                    TETRIS - FASE %d/%d                 ║", estado->fase, TOTAL_FASES);
    mover_cursor(0, 2);
    printf("╚════════════════════════════════════════════════════════╝");
    
    // Desenhar grade
    for (int y = 0; y < GRADE_ALTURA; y++) {
        mover_cursor(offset_x, offset_y + 3 + y);
        printf("║");
        
        for (int x = 0; x < GRADE_LARGURA; x++) {
            if (estado->grade[y][x] != 0) {
                int tipo = estado->grade[y][x] - 1;
                cor_fundo(paleta.blocos[tipo].r, paleta.blocos[tipo].g, paleta.blocos[tipo].b);
                printf("██");
                resetar_cor();
            } else {
                printf("  ");
            }
        }
        
        printf("║");
    }
    
    // Desenhar peça atual
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (bloco_rotacionado(estado->peça_atual.tipo, estado->peça_atual.rotacao, x, y)) {
                int px = offset_x + 1 + (estado->peça_atual.x + x) * 2;
                int py = offset_y + 3 + (estado->peça_atual.y + y);

                if (py >= offset_y + 3) {
                    mover_cursor(px, py);
                    cor_fundo(paleta.blocos[estado->peça_atual.tipo].r,
                             paleta.blocos[estado->peça_atual.tipo].g,
                             paleta.blocos[estado->peça_atual.tipo].b);
                    printf("██");
                    resetar_cor();
                }
            }
        }
    }
    
    // Rodapé da grade
    mover_cursor(offset_x, offset_y + 3 + GRADE_ALTURA);
    printf("╚════════════════════════════════════════════════════════╝");
    
    // Painel lateral
    int painel_x = offset_x + 24;
    int painel_y = offset_y + 3;
    
    cor_texto(paleta.texto.r, paleta.texto.g, paleta.texto.b);
    
    mover_cursor(painel_x, painel_y);
    printf("📊 STATUS");
    
    mover_cursor(painel_x, painel_y + 2);
    printf("Fase: %d/%d", estado->fase, TOTAL_FASES);
    
    char romano[20];
    converter_numeral_romano(estado->pontuacao, romano);
    
    mover_cursor(painel_x, painel_y + 4);
    cor_texto(paleta.blocos[0].r, paleta.blocos[0].g, paleta.blocos[0].b);
    printf("Pontos: %s", romano);
    
    cor_texto(paleta.texto.r, paleta.texto.g, paleta.texto.b);
    mover_cursor(painel_x, painel_y + 6);
    printf("Linhas: %d", estado->linhas_eliminadas);
    
    mover_cursor(painel_x, painel_y + 8);
    printf("🎲 Proxima Peca:");
    
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (tetrominós[estado->proxima_peça.tipo][y][x]) {
                mover_cursor(painel_x + x * 2, painel_y + 10 + y);
                cor_fundo(paleta.blocos[estado->proxima_peça.tipo].r,
                         paleta.blocos[estado->proxima_peça.tipo].g,
                         paleta.blocos[estado->proxima_peça.tipo].b);
                printf("██");
                resetar_cor();
            }
        }
    }
    
    mover_cursor(painel_x, painel_y + 13);
    printf("⌨️  CONTROLES:");
    
    mover_cursor(painel_x, painel_y + 15);
    printf("A/D : Mover");
    
    mover_cursor(painel_x, painel_y + 16);
    printf("S   : Acelerar");
    
    mover_cursor(painel_x, painel_y + 17);
    printf("Esp: Girar");
    
    mover_cursor(painel_x, painel_y + 18);
    printf("R   : Reiniciar");
    
    mover_cursor(painel_x, painel_y + 19);
    printf("Q   : Sair");
    
    // Emoji de fase completa
    if (estado->frames_emoji > 0) {
        mover_cursor(painel_x - 5, painel_y + 28);
        cor_texto(255, 200, 100);
        printf("🎉 Fase Completa! 😊");
        resetar_cor();
    }
    
    // Tela de fim de jogo
    if (estado->fim_jogo) {
        mover_cursor(10, 15);
        cor_texto(255, 0, 0);
        printf("╔══════════════════════════════════════╗");
        mover_cursor(10, 16);
        printf("║   ☠️  FIM DE JOGO  ☠️                ║");
        mover_cursor(10, 17);
        printf("╚══════════════════════════════════════╝");
        
        mover_cursor(12, 19);
        cor_texto(255, 200, 100);
        printf("Pontuacao Final: %s", romano);
        
        mover_cursor(12, 21);
        cor_texto(200, 200, 200);
        printf("Alcancou a Fase: %d", estado->fase);
        
        mover_cursor(10, 24);
        cor_texto(255, 255, 0);
        printf("Pressione R para Reiniciar");
        
        resetar_cor();
    }
    
    resetar_cor();
    fflush(stdout);
}

// ============= MAIN =============

int main(void) {
    srand((unsigned int)time(NULL));
    
    configurar_terminal();
    
    EstadoJogo estado;
    inicializar_jogo(&estado);
    
    const int fps = 60;
    const int frame_time_ms = 1000 / fps;
    
    while (1) {
        processar_entrada(&estado);
        atualizar_jogo(&estado);
        
        PaletaFase paleta = obter_paleta(estado.fase);
        desenhar_tela(&estado, paleta);
        
        usleep(frame_time_ms * 1000);
    }
    
    restaurar_terminal();
    return 0;
}