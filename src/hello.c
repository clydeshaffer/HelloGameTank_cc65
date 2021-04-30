#include "gametank.h"

extern void wait ();

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
    vram[VX] = 0;
    vram[VY] = SCREEN_HEIGHT-1;
    vram[WIDTH] = SCREEN_WIDTH-1;
    vram[HEIGHT] = 1;
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
    char col = 0, row = 0;
    int dx = 1, dy = 1;
    *dma_flags = DMA_NMI | DMA_ENABLE | DMA_IRQ | DMA_TRANS;

  while (1) {                                     //  Run forever
    CLS(3);
    FillRect(col, row, 8, 8, 92);
    col += dx;
    row += dy;
    if(col == 1) {
        dx = 1;
    } else if(col == 111) {
        dx = -1;
    }
    if(row == 1) {
        dy = 1;
    } else if(row == 100) {
        dy = -1;
    }
    wait();
  }

  return (0);                                     //  We should never get here!
}
