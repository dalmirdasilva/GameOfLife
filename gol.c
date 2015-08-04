#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void show(void *u, int w, int h) {
	int (*univ)[w] = u;
	int x, y;
	printf("\033[H");
	for (y = 0; y < h; y++) {
		for (x = 0; x < w; x++) {
			printf(univ[y][x] ? "\033[07m  \033[m" : "  ");
		}
		printf("\033[E");
	}
	fflush(stdout);
}
 
void evolve(void *u, int w, int h) {
	unsigned (*univ)[w] = u;
	unsigned new[h][w];
	int x, y, y1, x1;
	for (y = 0; y < h; y++) {
		for (x = 0; x < w; x++) {
			int n = 0;
			for (y1 = y - 1; y1 <= y + 1; y1++) {
				for (x1 = x - 1; x1 <= x + 1; x1++) {
					if (univ[(y1 + h) % h][(x1 + w) % w]) {
						n++;
					}
				}
			}
			if (univ[y][x]) {
				n--;
			}
			new[y][x] = (n == 3 || (n == 2 && univ[y][x]));
		}
	}
	for (y = 0; y < h; y++){
		for (x = 0; x < w; x++) { 
			univ[y][x] = new[y][x]; 
		}
	}
}
 
void game(int w, int h) {
	unsigned univ[h][w];
	int x, y;
	for (x = 0; x < w; x++) {
		for (y = 0; y < h; y++) {
			univ[y][x] = rand() < RAND_MAX / 10 ? 1 : 0;
		}
	}
	while (1) {
		show(univ, w, h);
		evolve(univ, w, h);
		usleep(200000);
	}
}
 
int main(int c, char **v) {
	int w = 0, h = 0;
	if (c > 1) w = atoi(v[1]);
	if (c > 2) h = atoi(v[2]);
	if (w <= 0) w = 30;
	if (h <= 0) h = 30;
	game(w, h);
}
