Benjamin Bancala
CS214
PA1
ReadMe

My program takes in a command line arguement and stores in it
a char*. I then call TKCreate to make my tokenizer which
consists of 2 char*s, curr which holds the rest of the
input line, and word which stores the phrase to be output,
and 1 char which holds the "state". As the token goes
through the GetNextToken method, it calls upon many
other methods depending on the state. Certain states
lead to others, while some are dead ends. I was able
to code cases for words, alphanumeric, digits, decimals,
hex, octal, floats, c operators, and unknowns. 

Words are just letters. 
Digits are numbers without a decimal or 
arent octal. 
Decimal have a decimal somewhere in the number.
Hex starts 0x then the remaining characters are between 0-F.
Octal are digits between 0-7.
Floats have an e followed by a number, a + ,or a -. 
C operators are the different operations that c can 
perform.
Unknown are certain cases such as 5. (a decimal without 
numbers after).

When the tok is returned back to main based on the
state it has, it is output in main with the
appropriate word before it. After everything has been
output, the memory is freed. 

I think the hardest part was figuring out the basis
for the tokenizer. Once I figured out which
direction I wanted to go in, the code wasn't too bad
to write. It was also hard to identify every character
and output the correct name. Such as right bracket = [
So I output everything as c operator = [.