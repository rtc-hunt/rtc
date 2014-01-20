#include "branch.h"
#include "strings.h"
#include "string.h"
#include "ctype.h"

char letters[29][5] = {
{'`','b','e','i','o'},
{'a','a','b','b','n'},
{'e','i','l','r','r'},
{'a','l','n','r','u'},
{'`','`','e','n','t'},
{'`','b','b','t','y'},
{'`','`','a','l','r'},
{'d','f','j','o','u'},
{'e','e','m','r','w'},
{'a','e','n','r','s'},
{'`','h','n','n','s'},
{'a','e','k','o','w'},
{'`','`','a','l','u'},
{'e','i','j','j','t'},
{'`','a','a','r','t'},
{'`','c','e','m','p'},
{'`','a','e','k','t'},
{'n','o','s','s','u'},
{'`','a','l','m','o'},
{'`','`','n','n','o'},
{'`','b','c','h','t'},
{'a','e','j','o','y'},
{'`','d','n','r','r'},
{'`','c','e','p','s'},
{'`','e','r','s','t'},
{'`','a','e','l','v'},
{'d','i','o','r','s'},
{'`','o','o','r','s'},
{'`','g','i','r','y'}};

int fill(int n){
	int row = n/5;
	int ex[27];
	for(int i=0; i<27; ++i) ex[i]=0;
	for(int i=0; i<5; ++i) ++ex[letters[row][i]-'`'];
	for(int i=0; i<=n%5; ++i) --ex[x[row*5+i]];
	for(int i=0; i<27; ++i) if(ex[i]<0) return 0;
	return 1;
}

int zeros(int n){
	if(n==3 || n==20 || n==24 || n==27 || n==31 || n==33 || n==54 || n==61 || n==63 || n==72 || n==75 || n==84 || n==91 || n==95 || n==97 || n==103 || n==114 || n==118 || n==123 || n==127 || n==136 || n==140){
		if(x[n]!='`'-'`') return 0;
	}
	else{
		if(x[n]=='`'-'`') return 0;
	}
	return 1;
}


char *wordlist[27][27][1000];
int ends[27][27];
int indexthing[676];
int hash(char* x) {return (26*tolower(x[0])+tolower(x[1])-'a'-26*'a');}
#define HBIT(s) [tolower(s[0])-'`'][tolower(s[1])-'`']
int wordinit(char* string){
   FILE *in;
   in=fopen("words","r");
   int i=0,j=0;
   for(i=0;i<26;i++) for(j=0;j<26;j++) ends[i][j]=0;
   int phash=0;
   while(!feof(in)){
      char *buf;
      size_t siz=0;
      getline(&buf,&siz,in);
//      fgets(buf,80,in);
      for(i=0;buf[i]!='\n'&&i<79;i++);
      buf[i]='\0';
      if(strlen(buf)>2&&'`'<=tolower(buf[0])&&tolower(buf[0])<='z'&&'`'<=tolower(buf[1])&&tolower(buf[1])<='z'){
//      if(!strcasecmp(buf,string)) {fclose(in);return 1;}
//      if(phash!=hash(buf)) indexthing[hash(buf)]=j;
//      phash=hash(buf);
      (wordlist)HBIT(buf)[(ends)HBIT(buf)++]=buf;
//[buf[0]-'a'][buf[1]-'a'][ends[buf[0]-'a'][buf[1]-'a']++]=buf;
}
//      strcpy(wordlist[buf[0]-'a'][buf[1]-'a'][ends[buf[0]-'a'][buf[1]-'a']++],buf);
   }
//#   fclose(in);
   return 0;
}

int word(char* string){
   int i;
   for(i=0;i<ends[string[0]-'`'][string[1]-'`'];i++){
      if(!strcasecmp(string,wordlist[string[0]-'`'][string[1]-'`'][i])) return 1;
   }
   return 0;
}

int partialword(char* string){
   int i;
   for(i=0;i<ends[string[0]-'`'][string[1]-'`'];i++){
      char* sp=string-1;
      char* pt=wordlist[string[0]-'`'][string[1]-'`'][i]-1;
      while(*(++pt)&&(*(++sp) == *(pt)));
      if(!*pt) return 1;
   }
   return 0;
}

	char tw[100];

int iswords(int n){
	for(int i=0; i<100; ++i) tw[i]=0;
	if(n==15){ for(int i=0; i<4; ++i) tw[i] = x[0+5*i] +'`'; return word(tw);}
//	if(n==19){ for(int i=0; i<4; ++i) tw[i] = x[4+5*i] +'`'; return word(tw);}
	if(n==141){ tw[0] = x[141]; for(int i=0; i<5; ++i) tw[i+1] = x[2+5*i] +'`'; return word(tw);}
	if(n==26){ for(int i=0; i<6; ++i) tw[i] = x[1+5*i] +'`'; return word(tw);}
	if(n==28){ for(int i=0; i<5; ++i) tw[i] = x[8+5*i] +'`'; return word(tw);}
	if(n==56){ for(int i=0; i<5; ++i) tw[i] = x[36+5*i] +'`'; return word(tw);}
	if(n==58){ for(int i=0; i<5; ++i) tw[i] = x[38+5*i] +'`'; return word(tw);}
	if(n==67){ for(int i=0; i<8; ++i) tw[i] = x[32+5*i] +'`'; return word(tw);}
	if(n==70){ for(int i=0; i<10; ++i) tw[i] = x[25+5*i] +'`'; return word(tw);}
	if(n==86){ for(int i=0; i<5; ++i) tw[i] = x[66+5*i] +'`'; return word(tw);}
	if(n==90){ for(int i=0; i<3; ++i) tw[i] = x[80+5*i] +'`'; return word(tw);}
	if(n==92){ for(int i=0; i<4; ++i) tw[i] = x[77+5*i] +'`'; return word(tw);}
	if(n==98){ for(int i=0; i<7; ++i) tw[i] = x[68+5*i] +'`'; return word(tw);}
	if(n==109){ for(int i=0; i<5; ++i) tw[i] = x[89+5*i] +'`'; return word(tw);}
	if(n==113){ for(int i=0; i<2; ++i) tw[i] = x[108+5*i] +'`'; return word(tw);}
	if(n==122){ for(int i=0; i<5; ++i) tw[i] = x[102+5*i] +'`'; return word(tw);}
	if(n==131){ for(int i=0; i<8; ++i) tw[i] = x[96+5*i] +'`'; return word(tw);}
	if(n==135){ for(int i=0; i<8; ++i) tw[i] = x[100+5*i] +'`'; return word(tw);}
	if(n==142){ for(int i=0; i<3; ++i) tw[i] = x[132+5*i] +'`'; return word(tw);}
	if(n==143){ for(int i=0; i<4; ++i) tw[i] = x[128+5*i] +'`'; for(int i=0; i<4; ++i) tw[i+4] = x[4+5*i] +'`'; return word(tw);}
	if(n==144){ for(int i=0; i<6; ++i) tw[i] = x[119+5*i] +'`'; return word(tw);}
	
//Partial tests
if(n<15) return 1;
//        if(n<15){ for(int i=0; i<4&&((0+5*i)<n); ++i) tw[i] = x[0+5*i] +'`'; return partialword(tw);}
	if(n<26){ for(int i=0; i<6&&((1+5*i)<n); ++i) tw[i] = x[1+5*i] +'`'; return partialword(tw);}
	if(n<28){ for(int i=0; i<5&&((8+5*i)<n); ++i) tw[i] = x[8+5*i] +'`'; return partialword(tw);}
if(n<37) return 1;
	if(n<56){ for(int i=0; i<5&&((36+5*i)<n); ++i) tw[i] = x[36+5*i] +'`'; printf("\n %s",tw); return partialword(tw);}
	if(n<58){ for(int i=0; i<5&&((38+5*i)<n); ++i) tw[i] = x[38+5*i] +'`'; return partialword(tw);}
	if(n<67){ for(int i=0; i<8&&((32+5*i)<n); ++i) tw[i] = x[32+5*i] +'`'; return partialword(tw);}
	if(n<70){ for(int i=0; i<10&&((25+5*i)<n); ++i) tw[i] = x[25+5*i] +'`'; return partialword(tw);}
	if(n<86){ for(int i=0; i<5&&((66+5*i)<n); ++i) tw[i] = x[66+5*i] +'`'; return partialword(tw);}
	if(n<90){ for(int i=0; i<3&&((80+5*i)<n); ++i) tw[i] = x[80+5*i] +'`'; return partialword(tw);}
	if(n<92){ for(int i=0; i<4&&((77+5*i)<n); ++i) tw[i] = x[77+5*i] +'`'; return partialword(tw);}
	if(n<98){ for(int i=0; i<7&&((68+5*i)<n); ++i) tw[i] = x[68+5*i] +'`'; return partialword(tw);}
	if(n<109){ for(int i=0; i<5&&((89+5*i)<n); ++i) tw[i] = x[89+5*i] +'`'; return partialword(tw);}
	if(n<113){ for(int i=0; i<2&&((108+5*i)<n); ++i) tw[i] = x[108+5*i] +'`'; return partialword(tw);}
	if(n<122){ for(int i=0; i<5&&((102+5*i)<n); ++i) tw[i] = x[102+5*i] +'`'; return partialword(tw);}
	if(n<131){ for(int i=0; i<8&&((96+5*i)<n); ++i) tw[i] = x[96+5*i] +'`'; return partialword(tw);}
	if(n<135){ for(int i=0; i<8&&((100+5*i)<n); ++i) tw[i] = x[100+5*i] +'`'; return partialword(tw);}
	if(n<141) return 1;
//	if(n<141){ tw[0] = x[141]; for(int i=0; i<5; ++i) tw[i+1] = x[2+5*i] +'`'; return partialword(tw);}
	if(n<142){ for(int i=0; i<3&&((132+5*i)<n); ++i) tw[i] = x[132+5*i] +'`'; return partialword(tw);}
        if(n<143) return 1;
//	if(n<143){ for(int i=0; i<4&&(128+5*i)<=n; ++i) tw[i] = x[128+5*i] +'`'; for(int i=0; i<4; ++i) tw[i+4] = x[4+5*i] +'`'; return partialword(tw);}
	if(n<144){ for(int i=0; i<6&&((119+5*i)<n); ++i) tw[i] = x[119+5*i] +'`'; return partialword(tw);}

	return 1;
}



int main(){
        wordinit("FOO");
	init();

	for(int i=0; i<145; ++i){
		inline_branch 0 to 26 inline_prune if(fill(i) && zeros(i) && iswords(i)) nokill
if(i==28){		sprint }
	}
	sprint
	}



