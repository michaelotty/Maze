#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct coordinate {
	int row;
	int col;
}coordinate_t;

typedef enum tile {
	EMPTY,
	R,
	B,
	BR,
	L,
	LR,
	LB,
	LBR,
	T,
	TR,
	TB,
	TBR,
	TL,
	TLR,
	TLB,
	TLBR
}tile_t;

CreateMaze(tile_t **maze, FILE *input, coordinate_t start, coordinate_t end, coordinate_t size);
coordinate_t GetMazeSize(FILE *input);


int main(int argc, char *argv[])
{
	coordinate_t startPoint = { 0, 0 }, endPoint = { 0, 0 }, mazeSize = { 0, 0 };
	FILE *mazeFile, *outputFile;
	int displayMaze = 0;
	int i, j;
	tile_t **maze = NULL;

	switch (argc) {
	case 0:
		perror("argc should never be 0");
		getchar();
		return ( -1 );
		break;

	case 3: // If only input and output files are inputed
		mazeFile = fopen(argv[1], "r");
		outputFile = fopen(argv[2], "w");

		if (mazeFile == NULL || outputFile == NULL) {
			perror("File load error");
			return ( -1 );
		}
		break;

	case 4: // If it is all arguments including the -d flag
		if (!strcmp(argv[1], "-d")) {
			displayMaze = 1;
		}

		mazeFile = fopen(argv[2], "r");
		outputFile = fopen(argv[3], "w");

		if (mazeFile == NULL || outputFile == NULL) {
			perror("File load error");
			return ( -1 );
		}
		break;

	default:
		printf("Syntax is \"Maze.exe <flag> <input-file> <output-file>\"");
		getchar();
		return ( 0 );
		break;
	}
	mazeSize = GetMazeSize(mazeFile);

	maze = malloc(mazeSize.row * sizeof(tile_t));
	for (i = 0; i < mazeSize.row; i++) {
		maze[i] = malloc(mazeSize.col * sizeof(tile_t));
	}

	CreateMaze(maze, mazeFile, startPoint, endPoint, mazeSize);
	for (i = 0; i < mazeSize.row; i++) {
		for (j = 0; j < mazeSize.col; j++) {
			printf("%d ", maze[i][j]);
		}
		printf("\n");
	}

	getchar();

	for (i = 0; i < mazeSize.row; i++) {
		free(maze[i]);
	}
	free(maze);

	fclose(mazeFile);
	fclose(outputFile);
	return ( 0 );
}

CreateMaze(tile_t **maze, FILE *input, coordinate_t start, coordinate_t end, coordinate_t size)
{
	int i, j;
	fscanf(input, "%d %d", &start.row, &start.col);
	fscanf(input, "%d %d", &end.row, &end.col);

	for (i = 0; i < size.row; i++) {
		for (j = 0; j < size.col; j++) {
			fscanf(input, "%d", &maze[i][j]);
		}
	}
}

coordinate_t GetMazeSize(FILE *input)
{
	coordinate_t size;// = { 0, 0 };
	fscanf(input, "%d %d", &size.row, &size.col);
	return ( size );
}