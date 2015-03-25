/*
 * tokenizer.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "tokenizer.h"
/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */


/*
 * TKCreate creates a new TokenizerT object for a given token stream
 * (given as a string).
 * 
 * TKCreate should copy the arguments so that it is not dependent on
 * them staying immutable after returning.  (In the future, this may change
 * to increase efficiency.)
 *
 * If the function succeeds, it returns a non-NULL TokenizerT.
 * Else it returns NULL.
 *
 * You need to fill in this function as part of your implementation.
 */

TokenizerT *TKCreate( char * ts ) {

	TokenizerT* tok=(TokenizerT*)malloc(sizeof(TokenizerT));	/*creates the tokenizer*/
	tok->curr=ts;
	tok->word=(char*)malloc(sizeof(char)*500);
	tok->state='s';
	return tok;
}

/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */

void TKDestroy( TokenizerT * tk ) {
	free(tk->curr);					/*frees the memory allocated for the tokenizer*/
	free(tk->word);
	free(tk);
}

/*
 * TKGetNextToken returns the next token from the token stream as a
 * character string.  Space for the returned token should be dynamically
 * allocated.  The caller is responsible for freeing the space once it is
 * no longer needed.
 *
 * If the function succeeds, it returns a C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */


TokenizerT *Alpha (TokenizerT *tk){
	int tklen;
	int count;
	tklen = strlen(tk->curr);
	count=0;
	while(tk->curr[0]!='\0'){
		/*printf("while loop in alpha \n");*/
		if(isalpha(tk->curr[0])){		/*adds each letter from curr to word*/
			tk->word[count]=tk->curr[0];
			tk->curr++;
			count++;
		}else if(isdigit(tk->curr[0])){		/*adds each digit from curr to word and changes to alphanumeric*/
			tk->word[count]=tk->curr[0];
			tk->curr++;
			count++;
			tk->state='a';
		}else if(isspace(tk->curr[0])){		/*gets rid of the white space before returning*/
			tk->curr++;
			return tk;
		}else{
			return tk;
		}

	}
	return tk;	
}



TokenizerT *Digit (TokenizerT *tk){
	int tklen;
	int count;
	tklen = strlen(tk->curr);
	count=0;
	while(tk->curr[0]!='\0'){
		/*printf("while loop in digit \n");*/
		if(isdigit(tk->curr[0])){			/*checks for digits */
			tk->word[count]=tk->curr[0];
			tk->curr++;
			count++;
			if(tk->curr[0]=='e'){			/*checks for float */
				tk->word[count]=tk->curr[0];
				tk->curr++;
				count++;
				tk->state='f';
			
				if(tk->curr[0]=='+'||tk->curr[0]=='-'){  /*checks for appropriate +/- */
					tk->word[count]=tk->curr[0];
					tk->curr++;
					count++;
				
					while(isdigit(tk->curr[0])){
						tk->word[count]=tk->curr[0];
						tk->curr++;
						count++;
					}
				}

			return tk;
			}
		}else if(tk->curr[0]=='.'){			/*checks for decimal */
			tk->word[count]=tk->curr[0];
			tk->curr++;
			count++;
			tk->state='e';
				if(isdigit(tk->curr[0])){
					tk->word[count]=tk->curr[0];		/*must be a digit after decimal */
					tk->curr++;
					count++;
					
					while(isdigit(tk->curr[0])){
						tk->word[count]=tk->curr[0];
						tk->curr++;
						count++;
					}
						if(tk->curr[0]=='e'){			/*checks for float*/
							tk->word[count]=tk->curr[0];
							tk->curr++;
							count++;
							tk->state='f';
			
							if(tk->curr[0]=='+'||tk->curr[0]=='-'){	/* must be +/- */
								tk->word[count]=tk->curr[0];
								tk->curr++;
								count++;
				
								if(isdigit(tk->curr[0])){
								while(isdigit(tk->curr[0])){
									tk->word[count]=tk->curr[0];
									tk->curr++;
									count++;
								}
								}else{
									tk->state='u';
									return tk;

								}
							}else if(isdigit(tk->curr[0])){
								while(isdigit(tk->curr[0])){
									tk->word[count]=tk->curr[0];
									tk->curr++;
									count++;
								}

							}else{
								tk->state='u';
								return tk;
							}
						
						return tk;
				}
				}else if(tk->curr[0]=='.'){
					tk->word[count]=tk->curr[0];
					tk->curr++;
					count++;
					tk->state='u';
					return tk;
				}else{
					tk->state='u';
					return tk;
				}
			
		}else if(isspace(tk->curr[0])){
			tk->curr++;
			return tk;
		
		}else{
			return tk;
		}
		}
	return tk;



}

TokenizerT *Zero(TokenizerT *tk){
	int count;
	count=0;


	tk->word[count]=tk->curr[0];
	tk->curr++;
	count++;


	while(tk->curr[0]!='\0'){
		if(tk->curr[0]=='x'||tk->curr[0]=='X'){			/* checks for hex*/
			tk->word[count]=tk->curr[0];
			tk->curr++;
			count++;
			tk->state='h';
			if((isdigit(tk->curr[0]))||(tk->curr[0]>='a'&&tk->curr[0]<='f')||(tk->curr[0]>='A'&&tk->curr[0]<='F')){
				tk->word[count]=tk->curr[0];
				tk->curr++;
				count++;
				
			
				while((isdigit(tk->curr[0]))||(tk->curr[0]>='a'&&tk->curr[0]<='f')||(tk->curr[0]>='A'&&tk->curr[0]<='F')){
					tk->word[count]=tk->curr[0];
					tk->curr++;
					count++;

				}
			}else{
				tk->state='u';
				return tk;
			}
			return tk;
			
		}else if(tk->curr[0]>='0'&&tk->curr[0]<='7'){		/*checks for octal*/
			tk->word[count]=tk->curr[0];
			tk->curr++;
			count++;
			tk->state='o';
			while(tk->curr[0]>='0'&&tk->curr[0]<='7'){
				tk->word[count]=tk->curr[0];
				tk->curr++;
				count++;
			}
			return tk;
		}else if(tk->curr[0]=='.'){				/*checks for decimal*/
			tk->word[count]=tk->curr[0];
			tk->curr++;
			count++;
			tk->state='e';
			if(isdigit(tk->curr[0])){
				tk->word[count]=tk->curr[0];
				tk->curr++;
				count++;
			}else{
				tk->state='u';
				return tk;
			}
			return tk;
		}else if(isalpha(tk->curr[0])){				/*checks for alphanumeric*/
			tk->word[count]=tk->curr[0];
			tk->curr++;
			count++;
			tk->state='a';
			while (isalpha(tk->curr[0])){
				tk->word[count]=tk->curr[0];
				tk->curr++;
				count++;
			}
			return tk;
		}else if(isdigit(tk->curr[0])){
			tk->word[count]=tk->curr[0];
			tk->curr++;
			count++;
			tk->state='d';
			while(isdigit(tk->curr[0])){
				tk->word[count]=tk->curr[0];
				tk->curr++;
				count++;
			}
			return tk;
		}else if(isspace(tk->curr[0])){
			tk->curr++;
			tk->state='s';
		}else{
			tk->state='u';
			return tk;
		}
	}
	return tk;
}


TokenizerT *Character( TokenizerT *tk){
	int count;
	count=0;
		if((tk->curr[0]<48&&tk->curr[0]>=0)||(tk->curr[0]>57&&tk->curr[0]<65)||(tk->curr[0]>90&&tk->curr[0]<97)||(tk->curr[0]>122&&tk->curr[0]<=127)){
			if(tk->curr[0]=='+'){
				tk->word[count]=tk->curr[0];
				tk->curr++;
				count++;
				if(tk->curr[0]=='+'){
					tk->word[count]=tk->curr[0];
					tk->curr++;
					count++;
					return tk;
				}else if(tk->curr[0]=='='){
					tk->word[count]=tk->curr[0];
					tk->curr++;
					count++;	
					return tk;
				}else{
					return tk;
				}
			
			
			}else if(tk->curr[0]=='>'){

				tk->word[count]=tk->curr[0];
				tk->curr++;
				count++;
				if(tk->curr[0]=='>'){					
					tk->word[count]=tk->curr[0];
					tk->curr++;
					count++;
					return tk;
				}else if(tk->curr[0]=='='){
					tk->word[count]=tk->curr[0];
					tk->curr++;
					count++;	
					return tk;
				}else{
					return tk;
				}

			}else if(tk->curr[0]=='<'){
				tk->word[count]=tk->curr[0];
				tk->curr++;
				count++;
				if(tk->curr[0]=='<'){					
					tk->word[count]=tk->curr[0];
					tk->curr++;
					count++;
					return tk;
				}else if(tk->curr[0]=='='){
					tk->word[count]=tk->curr[0];
					tk->curr++;
					count++;	
					return tk;
				}else{
					return tk;
				}
			}else if(tk->curr[0]=='-'){

				tk->word[count]=tk->curr[0];
				tk->curr++;
				count++;
				if(tk->curr[0]=='-'){					
					tk->word[count]=tk->curr[0];
					tk->curr++;
					count++;
					return tk;
				}else if(tk->curr[0]=='='){
					tk->word[count]=tk->curr[0];
					tk->curr++;
					count++;	
					return tk;
				}else{
					return tk;
				}
			}else if(tk->curr[0]=='|'){

				tk->word[count]=tk->curr[0];
				tk->curr++;
				count++;
				if(tk->curr[0]=='|'){					
					tk->word[count]=tk->curr[0];
					tk->curr++;
					count++;
					return tk;
				}else{
					return tk;
				}
			}else if(tk->curr[0]=='&'){

				tk->word[count]=tk->curr[0];
				tk->curr++;
				count++;
				if(tk->curr[0]=='&'){					
					tk->word[count]=tk->curr[0];
					tk->curr++;
					count++;
					return tk;
				}else{
					return tk;
				}
			}
			tk->word[count]=tk->curr[0];
			tk->curr++;
			count++;
			return tk;
		}

		tk->word[count]=tk->curr[0];
		tk->curr++;
		count++;
		tk->state='u';
		return tk;

}
TokenizerT *TKGetNextToken( TokenizerT * tk ) {
	int tklen;
	char* word;
	int wordlen;
	int count;
	word = (char*)malloc(sizeof(char)*500);
	tklen = strlen(tk->curr);
	wordlen = 0;
	count =0;							/*begins to check for the appropriate category for each token */
	
		if(isalpha(tk->curr[0])){
			tk->state='w';
			Alpha(tk);
		}else if(tk->curr[0]=='0'){	
			Zero(tk);
		}else if(isdigit(tk->curr[0])&&tk->curr[0]!='0'){
			tk->state='d';
			Digit(tk);
		}else if(tk->curr[0]=='.'){
			tk->state='e';
			Digit(tk);
		}else if(isspace(tk->curr[0])){	
			tk->curr++;
			tk->state='s';
		}else{	
			tk->state='c';
			Character(tk);
		}
	return tk;
	
}
	
TokenizerT* reset(TokenizerT* tok, char* r){

	tok->curr=r;					/*resets the pointer in order to free it later*/

	return tok;


}

/*
 * main will have a string argument (in argv[1]).
 * The string argument contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on a separate line.
 */

int main(int argc, char **argv) {
	char* word;
	int i;
	int j;
	char* wordsafe;
	if(argc!=2){
		printf("invalid number of command arguements");
		return 0;
	}
		
	word=(char *)malloc(sizeof(char)*500);				/*takes in the command line input*/
	wordsafe=(char *)malloc(sizeof(char)*500);
	for(i = 1; i<argc; i++){
		strcat(word, argv[i]);
			if (argc > i+1){
				strcat(word, " ");
			}
		}
	strcat(word, " ");
	printf("You have entered: %s\n", word);
	wordsafe=word;
	/*printf("wordsafe = %s\n",wordsafe);*/				/*makes the tokenizer*/
	TokenizerT *tok=TKCreate(word);
	char* r = tok->curr;
	/*printf("token = %s\n",tok->curr);*/
	
	while(tok->curr[0]!='\0'){					/*prints the appropriate category*/
		TKGetNextToken(tok);
		if(tok->state=='w'){
			printf("word = %s\n",tok->word);
		}else if(tok->state=='a'){
			printf("alphanumeric = %s\n",tok->word);
		}else if(tok->state=='d'){
			printf("digit = %s\n",tok->word);
		}else if(tok->state=='o'){
			printf("octal = %s\n",tok->word);
		}else if(tok->state=='h'){
			printf("hex = %s\n",tok->word);
		}else if(tok->state=='f'){
			printf("float = %s\n",tok->word);
		}else if(tok->state=='c'){
			printf("c operator = %s\n",tok->word);
		}else if(tok->state=='e'){
			printf("decimal = %s\n",tok->word);
		}else if(tok->state=='u'){
			printf("unknown = %s\n",tok->word);
		}else{
		}
									/*RESET WORD HERE*/
		for(j=0;j<strlen(tok->word);j++){
			tok->word[j]=' ';
		}
		/*printf("while loop in main \n");*/
	}
	/*printf("DONE. Next step is to destroy \n");*/
	reset(tok,r);							/*reset the pointer for freeing later*/
	/*printf("test:%s\n",tok->curr);*/
	TKDestroy(tok);							/*frees the memory*/
  return 0;
}

