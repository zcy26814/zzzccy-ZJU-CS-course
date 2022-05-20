#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define MAXTEXTLEN 500
#define MAXWORDLEN 20
#define gearIIINum 0
#define gearIINum 1
#define gearINum 2
#define ROTORNUM 5
#define reflectorNum 5
#define plugboardNum 6
#define ALPHANUM 26
const char reflector[] = "YRUHQSLDPXNGOKMIEBFZCWVJAT"; 
const char rotor_table[ROTORNUM][ALPHANUM + 1] = 
    {
    	"EKMFLGDQVZNTOWYHXUSPAIBRCJ",
    	"AJDKSIRUXBLHWTMCQGZNPYFVOE",
    	"BDFHJLCPRTXVZNYEIWGAKMUSQO",
    	"ESOVPZJAYQUIRHXLNFTGKDCMWB",
        "VZBRGITYUPSDNHLXAWMJQOFECK"
    };
const char step_char[ROTORNUM] = {'R', 'F', 'W', 'K', 'A'}; // Royal Flags Wave Kings Above
char plugboard[ALPHANUM + 1] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

void initSetting(int* rotorIII, char ringSetting[], char cypherText[], char word[]);
void setPlugboard(char plugCharI, char plugCharII);
void emulate(char plainText[], char cypherText[], char messageKey[], char ringSetting[], int rotorNum[]);
char plugTransform(char pn);
void royalGear(char messageKey[], int rotorNum[]);
char rotorChar(char plainChar, int rotorNum[], int delta[]);
int findChar(int pn, int rn);
int reverseFindChar(int pn, int rn);
void decrypt(int rotorNum[], char messageKey[], char ringSetting[], char plainText[], char cypherText[], char word[]);
void printResult(char messageKey[], char plainText[], int rotorNum[]);

int main() 
{
	int rotorNum[3];
	char ringSetting[3], messageKey[3], plainText[MAXTEXTLEN + 1], cypherText[MAXTEXTLEN + 1], word[MAXWORDLEN+1];
	initSetting(rotorNum, ringSetting, cypherText, word); 
	decrypt(rotorNum, messageKey, ringSetting, plainText, cypherText, word);
	printResult(messageKey, plainText, rotorNum);
	return 0;
} 


void initSetting(int* rotorIII, char ringSetting[], char cypherText[], char word[])
{
	int i;
	char plugCharI, plugCharII;
	while(1) {
		plugCharI = toupper(getchar());
		plugCharII = toupper(getchar());
		setPlugboard(plugCharI, plugCharII);
		if(getchar() == '\n') break;
	} //输入对应的10对字母
	for(i = 0; i < 3; i++){
		ringSetting[i] = toupper(getchar());
	}
	scanf("%s", cypherText); //输入密文
	scanf("%s", word);  //输入已知单词
	scanf("%d", rotorIII); //输入最左侧齿轮编号
	strupr(cypherText);
	strupr(word);
	(*rotorIII)--; 
} //设置初始输入内容

void setPlugboard(char plugCharI, char plugCharII)
{
	plugboard[plugCharI - 'A'] = plugCharII;
	plugboard[plugCharII - 'A'] = plugCharI;
} //进行插接板操作

void emulate(char plainText[], char cypherText[], char messageKey[], char ringSetting[], int rotorNum[])
{
	int i, j, len, delta[3];
	char orgMessageKey[3] = {messageKey[0], messageKey[1], messageKey[2]};
	
	len = strlen(plainText);
	for(i = 0; i < len; i++) {
		royalGear(messageKey, rotorNum);
		for(j = 0; j < 3; j++){
			delta[j] = messageKey[j] - ringSetting[j];
		}
		cypherText[i] = plugTransform(rotorChar(plugTransform(plainText[i]), rotorNum, delta));	
	} 
	cypherText[i] = '\0';
	for(j = 0; j < 3; j++){
		messageKey[j] = orgMessageKey[j];
	}
} //配置plug完成后的加密过程（由对称性地得解密过程）

char plugTransform(char pn)
{
	return findChar(pn - 'A', plugboardNum) + 'A';
} //用plug转换

void royalGear(char messageKey[], int rotorNum[])
{
	char tmp = (messageKey[gearIINum] - 'A' + 1) % ALPHANUM + 'A';
	messageKey[gearINum] = (messageKey[gearINum] - 'A' + 1) % ALPHANUM + 'A';
	if(tmp == step_char[rotorNum[gearIINum]]) {
		messageKey[gearIIINum] = (messageKey[gearIIINum] - 'A' + 1) % ALPHANUM + 'A';
		messageKey[gearIINum] = tmp;
	} else if(messageKey[gearINum] == step_char[rotorNum[gearINum]]) {
		messageKey[gearIINum] = tmp;
	}
} //齿轮转动过程

char rotorChar(char plainChar, int rotorNum[], int delta[])
{
	int i, plainNum = plainChar - 'A';
	for(i = gearINum; i >= gearIIINum; i--) {
		plainNum = (plainNum + delta[i] + ALPHANUM) % ALPHANUM;
		plainNum = findChar(plainNum, rotorNum[i]);
		plainNum = (plainNum - delta[i] + ALPHANUM) % ALPHANUM;
	}
	plainNum = findChar(plainNum, reflectorNum);
	for(i = gearIIINum; i <= gearINum; i++) {
		plainNum = (plainNum + delta[i] + ALPHANUM) % ALPHANUM;
		plainNum = reverseFindChar(plainNum, rotorNum[i]);
		plainNum = (plainNum - delta[i] + ALPHANUM) % ALPHANUM;
	}
	return plainNum + 'A';
} //配置plug前的加密解密过程 

int findChar(int pn, int rn)
{
	int cn;
	if(rn < ROTORNUM) {
		cn = rotor_table[rn][pn] - 'A';
	} else if(rn == reflectorNum){
		cn = reflector[pn] - 'A';
	} else {
		cn = plugboard[pn] - 'A';
	}
	return cn;
} //经过反射器之前

int reverseFindChar(int pn, int rn)
{
	int cn;
	if(rn < ROTORNUM) {
		for(cn = 0; cn < ALPHANUM; cn++) {
			if(pn == rotor_table[rn][cn] - 'A') break;
		}
	} else if(rn == reflectorNum){
		cn = reflector[pn] - 'A';
	} else {
		cn = plugboard[pn] - 'A';
	}
	return cn;
} //经过反射器之后

void decrypt(int rotorNum[], char messageKey[], char ringSetting[], char plainText[], char cypherText[], char word[])
{
	for(rotorNum[1] = 0; rotorNum[1] < ROTORNUM; rotorNum[1]++) {
		if(rotorNum[1] != rotorNum[0]) {
			for(rotorNum[2] = 0; rotorNum[2] < ROTORNUM; rotorNum[2]++) {
				if(rotorNum[2] != rotorNum[0] && rotorNum[2] != rotorNum[1]) {
					for(messageKey[0] = 'A'; messageKey[0] < 'A' + ALPHANUM; messageKey[0]++) {
						for(messageKey[1] = 'A'; messageKey[1] < 'A' + ALPHANUM; messageKey[1]++) {
							for(messageKey[2] = 'A'; messageKey[2] < 'A' + ALPHANUM; messageKey[2]++){
								emulate(cypherText, plainText, messageKey, ringSetting, rotorNum);
								if(strstr(plainText, word) != NULL) return;
							}
						}
					} 
				}
			}
		}
	}
	exit(0);
} //用穷举法找出齿轮编号

void printResult(char messageKey[], char plainText[], int rotorNum[])
{
	printf("MessageKey=%c%c%c\n", messageKey[0], messageKey[1], messageKey[2]);
	printf("PlainText=%s\n", plainText);
	printf("RotorNum=%d%d%d\n", rotorNum[0]+1, rotorNum[1]+1, rotorNum[2]+1);
} //最终输出结果