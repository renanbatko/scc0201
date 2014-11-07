#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	char filename[20];
	scanf(" %s", filename);
	
	FILE *metafile;
	metafile = fopen(filename, "r");
	if (metafile == NULL) exit(1);
	
	
	
	return 0;
}
