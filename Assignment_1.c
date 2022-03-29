/* Solution to comp10002 Assignment 1, 2019 semester 2.

   Authorship Declaration:

   (1) I certify that the program contained in this submission is completely
   my own individual work, except where explicitly noted by comments that
   provide details otherwise.  I understand that work that has been developed
   by another student, or by me in collaboration with other students,
   or by non-students as a result of request, solicitation, or payment,
   may not be submitted for assessment in this subject.  I understand that
   submitting for assessment work developed by or in collaboration with
   other students or non-students constitutes Academic Misconduct, and
   may be penalized by mark deductions, or by other penalties determined
   via the University of Melbourne Academic Honesty Policy, as described
   at https://academicintegrity.unimelb.edu.au.

   (2) I also certify that I have not provided a copy of this work in either
   softcopy or hardcopy or any other form to any other student, and nor will
   I do so until after the marks are released. I understand that providing
   my work to other students, regardless of my intention or any undertakings
   made to me by that other student, is also Academic Misconduct.

   (3) I further understand that providing a copy of the assignment
   specification to any form of code authoring or assignment tutoring
   service, or drawing the attention of others to such services and code
   that may have been made available via such a service, may be regarded
   as Student General Misconduct (interfering with the teaching activities
   of the University and/or inciting others to commit Academic Misconduct).
   I understand that an allegation of Student General Misconduct may arise
   regardless of whether or not I personally make use of such solutions
   or sought benefit from such actions.

   Signed by: Hanjoo Kim 1078371
   Dated:     22/09/2019

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


#define MAXINPUT 1000		// maximum number of input characters in a line


int mygetchar();
void condition_b(), condition_p();
int condition_l(), condition_w();

int
main(int argc, char *argv[]) {
	char line[MAXINPUT], c, word[MAXINPUT];
	int MAXCHARLINE = 50;	// maximum number of characters allowed in a line
	int SPACENUM = 4;	// number of whitespaces at the start of a line
	int wordindex = 0; 	// word index to insert the characters in
	int flagn = 1; 		// to not have empty lines in between the lineㄴ
	int flagt = 1; 		// in order to have single whitespaces between words
	int flagc = 0;		// check whether a paragraph has been split
	//int flagb = 0;
	int length, wordlength;
	
	memset(line, ' ', SPACENUM); 
	
	// make a line that starts with SPACENUM 
	// amount of spaces
	
	while((c = mygetchar())) {
		/*  get each word, concatenate to a line, if the length of the line 
			becomes larger than the MAXCHARLINE + SPACENUM then don't put it in 
			but print the line out, then reset the line and repeat the 
			concatenation */
			
		length = strlen(line);
		wordlength = strlen(word);
		if(c == EOF) {		
			
			// to make sure the last line is printed out as well 
			// (it won't print out if it's smaller than MAXCHARLINE + SPACENUM)
			
			printf("%s\n", line);
			break;
		}
		else {
			if(c == '.') {		
				if(flagn == 1) {
					c = mygetchar();
					if(c == 'b') {
						if(flagc == 0) {
							printf("%s\n", line);
						}
						while(mygetchar() != '\n') {
							flagn = 1;
						}
						flagc = 1;
					}
					
					else if(c == 'p') {
						if(flagc == 0) {
							printf("%s\n\n", line);
						}
						while(mygetchar() != '\n') {
							flagn = 1;
						}
						flagc = 1;
					}
					
					else if(c == 'l') {
						SPACENUM = condition_l();
						if(flagc == 0) {
							printf("%s\n\n", line);
						}
						while(mygetchar() != '\n') {
							flagn = 1;
						}
						flagc = 1;
					}
					
					else if(c == 'w') {
						printf("%s$", line);
						if(flagc == 0) {
							printf("\n\n");
						}
						MAXCHARLINE = condition_w();
						while(mygetchar() != '\n') {
							flagn = 1;
						}
						flagc = 1;
					}
					
					else {
						word[wordindex] = '.';
						wordindex++;
						word[wordindex] = c;
						flagn = 0;
					}
					memset(line, '\0', MAXINPUT);
					memset(line, ' ', SPACENUM);
					memset(word, '\0', MAXINPUT);
					continue;
				}
			}
			
			
			
			
			if(c == ' ' || c == '\t' || c == '\n') {
				// to get rid of multiple spaces and to also discriminate 
				// each 'word'
				if(flagt == 0) {		
					// this flag is for the whitespaces and tabs
				}
				else {			
					// we assign the first whitespace after a word, but 
					// not any consequent white spaces
					word[wordindex] = ' ';
					flagt = 0;
					flagn = 0;
				}
				if(c == ' ' || c == '\t') {
					flagn = 0;
				}
				
				if(c == '\n') {			
				
				// to make sure that we skip the lines that are empty 
				// by using flagn (flag for '\n')
				
					if(flagn == 1) {
						continue;
					}
					else {
						flagn = 1;
					}
					flagc = 0;
				}
				
				
				if(wordlength > MAXCHARLINE) {			
					//	if a single word exceeds the character limit, 
					// then just print it out
					printf("%s\n", line);
					memset(line, '\0', MAXINPUT);
					memset(line, ' ', SPACENUM);
					strcat(line, word);
					printf("%s", line);
					memset(word, '\0', MAXINPUT);
					memset(line, '\0', MAXINPUT);
					memset(line, ' ', SPACENUM);
				}
				
				if(length + wordlength > MAXCHARLINE + SPACENUM) {			
					// check if the line length is bigger than 
					// MAXCHARLINE + SPACENUM and if it is, print it out
					
					printf("%s\n", line);
					memset(line, '\0', MAXINPUT);
					memset(line, ' ', SPACENUM);
					strcat(line, word);
					memset(word, '\0', MAXINPUT);
				}
				else {							
					// if it's not, just keep concatenating the words
					
					strcat(line, word);
					memset(word, '\0', MAXINPUT);
				}
				wordindex = 0;
			}
	
			else {
				// making a word character by character
				
				word[wordindex] = c;			
				wordindex++;
				flagt = 1;
				flagn = 0; 
			}
		}
	}
	return 0;
}


int
	mygetchar() {
		// function provided in the assignment 1 FAQ to make sure no error 
		// occurs when submitting
		int c;
		while ((c = getchar())=='\r') {
		}
		return c;
	}
	
/* void
	condition_b(char line[MAXINPUT], int SPACENUM) {
		printf("%s\n", line);
		memset(line, '\0', MAXINPUT);
		memset(line, ' ', SPACENUM);
	}
	*/
	
/* void
	condition_p(char line[MAXINPUT], int SPACENUM) {
		printf("%s\n\n", line);
		memset(line, '\0', MAXINPUT);
		memset(line, ' ', SPACENUM);
	} */

int
	condition_l() {
		int result;
		char number[2];
		mygetchar();
		number[0] = mygetchar();
		number[1] = mygetchar();
		result = atoi(number);
		return result;
	}
	
int
	condition_w() {
		int result;
		char number[2];
		mygetchar();
		number[0] = mygetchar();
		number[1] = mygetchar();
		result = atoi(number);
		return result;
	}