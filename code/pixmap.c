#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pixmap.h"
#include "video_gr.h"
#include "Utilities.h"

int num_of_pixmaps=0;
Pixmap* pixmaps;//List of pixmaps

int addPixmap(Pixmap *pm)
{
	if (num_of_pixmaps==0) ALLOC(Pixmap,1,pixmaps);//pixmaps=(Pixmap*) malloc(sizeof(Pixmap)* 1);
	else REALLOC(Pixmap,(num_of_pixmaps+1),pixmaps);  //pixmaps=(Pixmap*) realloc(pixmaps,sizeof(Pixmap)* num_of_pixmaps);
	num_of_pixmaps++;
	//makes a copy //needs to be done this way because pm maybe local variable
	pixmaps[num_of_pixmaps-1].width=pm->width;
	pixmaps[num_of_pixmaps-1].height=pm->height;
	//pixmap is a pointer to allocated stuff so no problem here
	pixmaps[num_of_pixmaps-1].pixmap=pm->pixmap;

	return num_of_pixmaps-1;
}

void pixmap_cleanMemory()
{
	if(num_of_pixmaps==0) return;

	num_of_pixmaps--;//used here as index
	for (;num_of_pixmaps>=0;num_of_pixmaps--)//clean each pixmap data
		free(pixmaps[num_of_pixmaps].pixmap);

	free(pixmaps);//clean pixmaps array
	num_of_pixmaps=0;
}

Pixmap* getPixmap(unsigned int index)
{
	return &pixmaps[index];
}

char *read_xpm(char *map[], int *wd, int *ht)
{
  int width, height, colors;
  char sym[256];
  int  col;
  int i, j;
  char *pix, *pixtmp, *tmp, *line;
  char symbol;

  /* read width, height, colors */
  if (sscanf(map[0],"%d %d %d", &width, &height, &colors) != 3) {
    printf("read_xpm: incorrect width, height, colors\n");
    return NULL;
  }
#ifdef DEBUG
  printf("%d %d %d\n", width, height, colors);
#endif
  if (width > H_RES || height > V_RES || colors > 256) {
    printf("read_xpm: incorrect width, height, colors\n");
    return NULL;
  }

  *wd = width;
  *ht = height;

  for (i=0; i<256; i++)
    sym[i] = 0;

  /* read symbols <-> colors */
  for (i=0; i<colors; i++) {
    if (sscanf(map[i+1], "%c %d", &symbol, &col) != 2) {
      printf("read_xpm: incorrect symbol, color at line %d\n", i+1);
      return NULL;
    }
#ifdef DEBUG
    printf("%c %d\n", symbol, col);
#endif
    if (col > 256) {
      printf("read_xpm: incorrect color at line %d\n", i+1);
      return NULL;
    }
    sym[col] = symbol;
  }

  /* allocate pixmap memory */
  pix = pixtmp = malloc(width*height);

  /* parse each pixmap symbol line */
  for (i=0; i<height; i++) {
    line = map[colors+1+i];
#ifdef DEBUG
    printf("\nparsing %s\n", line);
#endif
    for (j=0; j<width; j++) {
      tmp = memchr(sym, line[j], 256);  /* find color of each symbol */
      if (tmp == NULL) {
    	  printf("read_xpm: incorrect symbol at line %d, col %d\n", colors+i+1, j);
    	  return NULL;
      }
      *pixtmp++ = tmp - sym; /* pointer arithmetic! back to books :-) */
#ifdef DEBUG
      printf("%c:%d ", line[j], tmp-sym);
#endif
    }
  }

  return pix;
}
