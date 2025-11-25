/* File:	count.c
 * Copyright:	2023, Ayden Dauenhauer
 * Date:	Jan 12, 2023
 * Description:	To count every word within a textfile and return the number of words.
 * */

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# define MAX_WORD_LENGTH 30

// Main function to run the code
int main(int argc, char *argv[]) {
	char word[MAX_WORD_LENGTH];
        int count = 0;
        FILE *fp;

	// Check to make sure the directory works
	if (argc != 2) {
		printf("Please enter the correct directory. \n");
		return;
	}

	fp = fopen(argv[1], "r");

	// Check to make sure there is a file
        if ((fp = fopen(argv[1], "r")) == NULL) {
                printf("The file could not be opened. \n");
                return;
        }

	// Counts the number of words within the file
        while (fscanf(fp, "%s", word) == 1) {
                count++;
        }

	printf("%d total words \n", count);
        fclose(fp);
}
