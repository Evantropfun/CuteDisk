
/*
The main file contain the main code,
but also the code responsible for file loading.
*/

#include <stdio.h>

enum PART_TYPES{
	UNKNOW,
	MBR
};

int partType;
extern const char *test;
extern void launchPrompt(void);

unsigned char WorkSector[512];

// Charge un LBA vers un buffer demandé.

void loadLBA(FILE *f, void *buffer){
	fread(buffer,512,1,f);
}

// Liste les infos des partitions MBR.
// buffer <- Secteur MBR.

void listPartitionsMBR(void *buffer){
	printf("Looking for little partitions... :3\n\n");
	int entryOffset = 0x1BE;
	for(char i = 0; i < 4; i++){
		unsigned int lbaStart = *((unsigned int *)(buffer+entryOffset+8));
		entryOffset += 0x10;
		printf("Partition %d\nLBA Start : %u\n\n", (int)i, lbaStart);
	}
}

int main(int argc, char const *argv[])
{

	partType = UNKNOW;

	printf("===================\nCute Disk V1.0.0\nWelcome :3 \n===================\n");
	if(argc==1){
		printf("But how can I know what disk to open if You don't say me what disk to open !!!\n):<\n");
		return 0;
	}
	if(argc>2){
		printf("ONE argment NOT TWOOO OR THREE OR DONT MIND ONLY OOOONE ):<\n");
		return 0;
	}

	printf("Opening %s...\n", argv[1]);

	FILE *f = fopen(argv[1], "rb");
	if(f==NULL){
		printf("):< ARE YOU DUMB ???\nYou can't ask me to open a disk that do not even exists !  O: \n");
		return 0;
	}

	printf("File openned correctly (:\n");

	fseek(f, 0, SEEK_END); // Va à la fin du fichier pour déterminer la taille.
	long fileSize = ftell(f);

	fseek(f, 0, SEEK_SET); // S'assure que la tête soit au début du fichier.

	loadLBA(f, WorkSector);
	if(WorkSector[0x1FE]==0x55 && WorkSector[0x1FF]==0xAA){
		printf("MBR detected !\n");
		partType=MBR;
	}

	if(partType!=UNKNOW){
		listPartitionsMBR(WorkSector);
	}else{
		printf("No partition detected )':\nSorry, I m so sorry i cant do anything for you.\nMaybe I do not support this file format,\nMaybe I need to improve myself ): \n");
		fclose(f);
		return 0;
	}

	launchPrompt();

	fclose(f);

	return 0;
}