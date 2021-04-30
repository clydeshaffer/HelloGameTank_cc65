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
    vram[VX] = 0;
    vram[VY] = 0;
    vram[GX] = DMA_GX_SOLIDCOLOR_FLAG;
    vram[GY] = 0;
    vram[WIDTH] = SCREEN_WIDTH-1;
    vram[HEIGHT] = SCREEN_HEIGHT-1;
    vram[COLOR] = ~c;
    vram[START] = 1;
    wait ();
    vram[VX] = SCREEN_WIDTH-1;
    vram[VY] = 0;
    vram[WIDTH] = 1;
    vram[HEIGHT] = SCREEN_HEIGHT-1;
    vram[START] = 1;
    wait ();
}

void FillRect(char x, char y, char w, char h, char c) {
    vram[VX] = x;
    vram[VY] = y;
    vram[GX] = DMA_GX_SOLIDCOLOR_FLAG;
    vram[GY] = 0;
    vram[WIDTH] = w;
    vram[HEIGHT] = h;
    vram[COLOR] = ~c;
    vram[START] = 1;
    wait ();
}

int main () {
    char col = 30, row = 20;
    int dx = 1, dy = 1;
    *dma_flags = DMA_NMI | DMA_ENABLE | DMA_IRQ | DMA_TRANS;

  while (1) {                                     //  Run forever
    CLS(3);
    FillRect(8, 8, 112, 92, 2);
    FillRect(col, row, 8, 8, 92);
    col += dx;
    row += dy;
    if(col == 8) {
        dx = 1;
    } else if(col == 112) {
        dx = -1;
    }
    if(row == 8) {
        dy = 1;
    } else if(row == 92) {
        dy = -1;
    }
    wait();
  }

  return (0);                                     //  We should never get here!
}
