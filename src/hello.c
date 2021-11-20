#include "gametank.h"

extern void wait ();

/*
 * Because the high bit of WIDTH/HEIGHT has special meaning,
 * the maximum size of a blitter operation is 127x127
 * which means a full screen clear requires four calls.
 * However, because the bottom five or so rows don't show up on a TV
 * we can skip those and only perform two draw calls.
 */
void CLS(char c) {
    SET_COLORFILL
    vram[VX] = 1;
    vram[VY] = 7;
    vram[GX] = 0;
    vram[GY] = 0;
    vram[WIDTH] = SCREEN_WIDTH-2;
    vram[HEIGHT] = SCREEN_HEIGHT-7-8;
    vram[COLOR] = ~c;
    vram[START] = 1;
    wait();
}

void FillRect(char x, char y, char w, char h, char c) {
    SET_COLORFILL
    vram[VX] = x;
    vram[VY] = y;
    vram[GX] = 0;
    vram[GY] = 0;
    vram[WIDTH] = w;
    vram[HEIGHT] = h;
    vram[COLOR] = ~c;
    vram[START] = 1;
    wait();
}

void CLB(char c) {
    FillRect(0, 0, SCREEN_WIDTH - 1, 8, c);
    FillRect(1, 120, SCREEN_WIDTH - 1, 8, c);
    FillRect(0, 8, 1, SCREEN_HEIGHT - 8, c);
    FillRect(127, 0, 1, SCREEN_HEIGHT - 8, c);
}

void Sleep(int frames) {
    int i;
    for(i = 0; i < frames; i++) {
        frameflag = 1;
        while(frameflag) {}
    }
}

void FlipPages() {
    frameflip ^= DMA_PAGE_OUT;
    bankflip ^= BANK_VRAM_MASK;
    flagsMirror = DMA_NMI | DMA_ENABLE | DMA_IRQ | DMA_TRANS | frameflip | DMA_AUTOTILE;
    *dma_flags = flagsMirror;
    *banking_reg = bankflip;
}

int main () {
    char col = 30, row = 20;
    int dx = 1, dy = 1;

    bankflip = 0;

    FlipPages();

    CLB(0);

    FlipPages();

    CLB(0);

    while (1) {                                     //  Run forever
        CLS(3);
        FillRect(col, row, 8, 8, 92);
        col += dx;
        row += dy;
        if(col == 1) {
            dx = 1;
        } else if(col == 119) {
            dx = -1;
        }
        if(row == 8) {
            dy = 1;
        } else if(row == 112) {
            dy = -1;
        }
        
        FlipPages();
        Sleep(1);
    }

  return (0);                                     //  We should never get here!
}

void NMIHandler() {
    frameflag = 0;
}