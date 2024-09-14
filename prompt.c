
#include <stdio.h>
#include <string.h>

extern int partType;
char typedData[1000];

extern const char *helptext;

void launchPrompt(){
	char running = 1;
	while(running){
		printf(">");
		scanf("%s", typedData);
		char *firstWord = strtok(typedData, " ");
		if(memcmp(firstWord, "quit", 4)==0)
			running=0;
		if(memcmp(firstWord, "help", 4)==0)
			printf(helptext);
	}
}

// UTILISER STRTOK