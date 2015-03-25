#include<stdio.h>
#include<stdlib.h>

struct TokenizerT_{
char state;
char* curr;
char* word;
};
typedef struct TokenizerT_ TokenizerT;

TokenizerT *TkCreate (char* ts);
void TKDestroy(TokenizerT* tk);
TokenizerT *Alpha (TokenizerT *tk);
TokenizerT *Digit (TokenizerT *tk);
TokenizerT *Zero (TokenizerT *tk);
TokenizerT *Character (TokenizerT *tk);
TokenizerT *TKGetNextToken (TokenizerT *tk);
TokenizerT *reset (TokenizerT *tok, char* r);
