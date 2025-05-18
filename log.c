#include "inc/stdint.h"

static uint16_t* const VIDEO_MEMORY = (uint16_t*) 0xB8000;
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

// Posição atual do cursor
uint8_t cursor_row = 0;
uint8_t cursor_col = 0;

// Cor padrão: texto branco (0x0F)
uint8_t vga_color = 0x0F;

void put_char(char c) {
    if (c == '\n') {
        cursor_row++;
        cursor_col = 0;
        return;
    }

    uint16_t pos = cursor_row * VGA_WIDTH + cursor_col;
    VIDEO_MEMORY[pos] = (vga_color << 8) | c;
    cursor_col++;

    if (cursor_col >= VGA_WIDTH) {
        cursor_col = 0;
        cursor_row++;
    }

    if (cursor_row >= VGA_HEIGHT) {
        // Scroll simples
        for (int i = 0; i < (VGA_HEIGHT - 1) * VGA_WIDTH; i++) {
            VIDEO_MEMORY[i] = VIDEO_MEMORY[i + VGA_WIDTH];
        }

        // Limpa a última linha
        for (int i = (VGA_HEIGHT - 1) * VGA_WIDTH; i < VGA_HEIGHT * VGA_WIDTH; i++) {
            VIDEO_MEMORY[i] = (vga_color << 8) | ' ';
        }

        cursor_row = VGA_HEIGHT - 1;
    }
}

// Função para limpar a tela
void clear() {
    for (int i = 0; i < VGA_HEIGHT * VGA_WIDTH; i++) {
        VIDEO_MEMORY[i] = (vga_color << 8) | ' ';  // Preenche com espaço em branco
    }

    cursor_row = 0;  // Resetando a posição do cursor
    cursor_col = 0;
}

void log_sys(){
    clear();
}

// Escreve string na tela
void klog(const char* message) {
    while (*message) {
        put_char(*message++);
    }
}
