#include<stdio.h>
#include<ctype.h>
#include<string.h>
void keyw(char *p);
int i=0,id=0,kw=0,num=0,op=0;
char keys[32][10]={"degilse","kir","vaka","karakter","sabit","yakala","ekle"
"yap","duble","basla","bitir","noktali","artsin","aralik",
"eger","tam","uzun","register","don","kisa","katar","sec",
"boyut","statik","yapi","tiptani","varsayilan","tek",
"yaz","calistir","topla","durumlarinda","tanimla"};
main()
{
	char ch,str[25],seps[15]=" \t\n,|:(){}[]#\"<>",oper[]="!%^&*-+=~<>/?";
	int j;
	char fname[50];
	FILE *f1;
	//clrscr();
printf("Calistirmak istediginiz kodu isim.txt seklinde girin:\n");
scanf("%s",fname);
f1 = fopen(fname,"r");
//f1 = fopen("Input","r");
	if(f1==NULL)
	{
	 printf("dosya bulununamadi...");
	 exit(0);
	}
	while((ch=fgetc(f1))!=EOF)
	{
for(j=0;j<=14;j++)
{
if(ch==oper[j])
{
printf("%c bir islem operatorudur.\n",ch);
op++;
str[i]='\0';
keyw(str);
}
}
for(j=0;j<=14;j++)
{
if(i==-1)
break;
if(ch==seps[j])
{

if(ch=='#')
{
while(ch!=')')
{
printf("%c",ch);
ch=fgetc(f1);
}
printf("%c bir ustbilgi dosyadir.\n",ch);
i=-1;
break;
}
if(ch=='"')
{
do
{
ch=fgetc(f1);
printf("%c",ch);
}while(ch!='"');
printf("\b bir degiskendir.\n");
i=-1;
break;
}
str[i]='\0';
keyw(str);
}
}
if(i!=-1)
{
str[i]=ch;
i++;
}
else
i=0;
	}
printf("anahtar kelime: %d\nbelirtici: %d\nislem operatoru: %d\nsayi: %d\n",kw,id,op,num);
//getch();
}
void keyw(char *p)
{
int k,flag=0;
for(k=0;k<=31;k++)
{
if(strcmp(keys[k],p)==0)
{
printf("%s bir anahtar kelimedir.\n",p);
kw++;
flag=1;
break;
}
}
if(flag==0)
{
if(isdigit(p[0]))
{
printf("%s bir sayidir.\n",p);
num++;
}
else
{
//if(p[0]!=13&&p[0]!=10)
if(p[0]!='\0')
{
printf("%s belirticidir\n",p);
id++;
}
}
}
i=-1;
}
