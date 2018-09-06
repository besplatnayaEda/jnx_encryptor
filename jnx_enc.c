
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

#include <windows.h>
//#include <iostream.h>
//#include <locale.h>


#define ERROR_FILE_OPEN -3
#define SIZE 64

#define SYSVERSION	(1)
#define SUBVERSION	(4)

unsigned long crc32( unsigned long crc, const void *buf, int size );

int htoi(char s[]);

char *strcasestr(const char *str, const char *pattern);

long str2hex(const char *s);

void f_MyEnd (void);


/*
 *
 */
long str2hex(const char *s)
{   long res=0;
    size_t  i=2;
    
    if(s == NULL)
        exit(EXIT_FAILURE);
  
    if((s[0] == 0) || (s[0] != '0'))
        exit(EXIT_FAILURE);
    
    if((s[1] == 0) || ((s[1] != 'x') && (s[1] != 'X')))
        exit(EXIT_FAILURE);
    
    if(s[2] == 0)
        exit(EXIT_FAILURE);
    
    do
    {   res<<=4;
        if(s[i]>='0' && s[i]<='9') 
            res=res | (char)(s[i]-'0');
        else
            if(s[i]>='A' && s[i]<='F') 
                res=res | (char)(s[i]-'A'+10);
            else
                if(s[i]>='a' && s[i]<='f')
                    res=res | (char)(s[i]-'a'+10);
                else
                    exit(EXIT_FAILURE);
        
        i++;
    }
    while(i<18 && s[i] != 0);
    
    return res;
}

/*
 *
 */
char *strcasestr(const char *str, const char *pattern) {
    size_t i;

    if (!*pattern)
        return (char*)str;

    for (; *str; str++) {
        if (toupper(*str) == toupper(*pattern)) {
            for (i = 1;; i++) {
                if (!pattern[i])
                    return (char*)str;
                if (toupper(str[i]) != toupper(pattern[i]))
                    break;
            }
        }
    }
    return NULL;
}

void f_MyEnd (void)
{   
   //Вывод сообщения о завершении работы
   puts ("\nPress AnyKey to Exit");
   _getch();
}

/*
 *
 */

 long seed  = 0x59AB6C98;
 long m = 3541*2617;
 char cnt = 0;
 char compare[64];
 
#define RRRANDOM seed = (seed * seed ) % m  // bbs random gen

unsigned char getRand(char size) {			// генератор bbs
	RRRANDOM;
	if(cnt >= size)
	{
		memset(&compare[0],0,sizeof(compare));
		cnt = 0;
	}
	char out = seed % size;
	
	if(out < 0)
		out = out *(-1);
	//printf("%2X[%d] ",compare[out],out);
	do{
		if(compare[out])
			RRRANDOM;
		else
		{	compare[out] = 1;
			break;
		}
		
		out = seed % size;
	
		if(out < 0)
			out = out *(-1);
		//printf("%2X[%d] ",compare[out],out);
	}while(compare[out]);
	compare[out] = 1;
	cnt++;
	return out;
}



/*
 *
 */
 static const unsigned long crc32_tab[] = {
	0x00000000, 0x77073096, 0xee0e612c, 0x990951ba, 0x076dc419, 0x706af48f,
	0xe963a535, 0x9e6495a3,	0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988,
	0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91, 0x1db71064, 0x6ab020f2,
	0xf3b97148, 0x84be41de,	0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
	0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec,	0x14015c4f, 0x63066cd9,
	0xfa0f3d63, 0x8d080df5,	0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172,
	0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b,	0x35b5a8fa, 0x42b2986c,
	0xdbbbc9d6, 0xacbcf940,	0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
	0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116, 0x21b4f4b5, 0x56b3c423,
	0xcfba9599, 0xb8bda50f, 0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924,
	0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d,	0x76dc4190, 0x01db7106,
	0x98d220bc, 0xefd5102a, 0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
	0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818, 0x7f6a0dbb, 0x086d3d2d,
	0x91646c97, 0xe6635c01, 0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e,
	0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457, 0x65b0d9c6, 0x12b7e950,
	0x8bbeb8ea, 0xfcb9887c, 0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
	0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2, 0x4adfa541, 0x3dd895d7,
	0xa4d1c46d, 0xd3d6f4fb, 0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0,
	0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9, 0x5005713c, 0x270241aa,
	0xbe0b1010, 0xc90c2086, 0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
	0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4, 0x59b33d17, 0x2eb40d81,
	0xb7bd5c3b, 0xc0ba6cad, 0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a,
	0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683, 0xe3630b12, 0x94643b84,
	0x0d6d6a3e, 0x7a6a5aa8, 0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
	0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe, 0xf762575d, 0x806567cb,
	0x196c3671, 0x6e6b06e7, 0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc,
	0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5, 0xd6d6a3e8, 0xa1d1937e,
	0x38d8c2c4, 0x4fdff252, 0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
	0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60, 0xdf60efc3, 0xa867df55,
	0x316e8eef, 0x4669be79, 0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,
	0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f, 0xc5ba3bbe, 0xb2bd0b28,
	0x2bb45a92, 0x5cb36a04, 0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
	0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a, 0x9c0906a9, 0xeb0e363f,
	0x72076785, 0x05005713, 0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38,
	0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21, 0x86d3d2d4, 0xf1d4e242,
	0x68ddb3f8, 0x1fda836e, 0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
	0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c, 0x8f659eff, 0xf862ae69,
	0x616bffd3, 0x166ccf45, 0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2,
	0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db, 0xaed16a4a, 0xd9d65adc,
	0x40df0b66, 0x37d83bf0, 0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
	0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6, 0xbad03605, 0xcdd70693,
	0x54de5729, 0x23d967bf, 0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94,
	0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d
};

unsigned long crc32( unsigned long crc, const void *buf, int size )
{
const unsigned char *p;

	p = buf;
	crc = crc ^ ~0U;
	int size1 = size;
	
	while( size-- )
		//crc = crc32_tab[(crc ^ *p++) & 0xFF] ^ (crc >> 8);
	{
		if(( size < (size1 - 20)) && (size >= (size1 - 24)) )
		{	crc = crc32_tab[(crc ^ 0x00) & 0xFF] ^ (crc >> 8);
//			p++;
		}
		else
//			crc = crc32_tab[(crc ^ *p++) & 0xFF] ^ (crc >> 8);
			crc = crc32_tab[(crc ^ *p ) & 0xFF] ^ (crc >> 8);
		p++;
	}

	return( crc ^ ~0U );
}

int main(int argc, char **argv) {

  FILE * tmpbin = NULL;
 // const char filename[] = "./tmp.bin";
    
  FILE * inpbin = NULL;		// бинарник прошивки
  FILE * tmpbin1 = NULL;
  
  char inpbin_fn[MAX_PATH] = " ";		// входной бинарник прошивки
  char outldr_fn[MAX_PATH] = " ";		// выходной hex.ldr с прошивкой 
  char outjnx_fn[MAX_PATH] = " ";		// выходной hex.jnx с прошивкой 
  char inpldr_fn[MAX_PATH] = " ";		// входной бинарник с загрузчиком
  char outbin_fn[MAX_PATH] = " ";		// выходной бинарник с загрузчиком и прошивкой
  
  char NPath[MAX_PATH] 	   = " ";		// родительский каталог
  
  long lSize;
  unsigned char * buffer;
  unsigned char buffer1[32];
  size_t result;
  long crc;
  unsigned char type = 0x00;		// тип прошивки
  int AppID = 1;
  
  long count;
  char *ch;
  unsigned char magic[] = {0x12,0x34,0x56,0x78,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88};
  char off = 4;
  
  
  puts("\niHex generator and encryptor");
  printf("v%u.%u, %s, %s by K.Artemev\n\n",SYSVERSION,SUBVERSION,__DATE__, __TIME__);
  

   //Проверка регистрации функции MyEnd_s
   if (atexit (f_MyEnd) != 0)  
   {   
      puts ("Error reg f_MyEnd");
   }
  
  
  // поиск ключей
  
  if (argc < 3 || argc > 15)
  {	fputs ("Invalid number of arguments\n",stderr);
	puts ("-i  [filename.bin]	Input bin firmware file");
	puts ("-ol [filename.ldr]	Output hex firmware file");
	puts ("-oj [filename.jnx]	Output hex firmware file");
	puts ("-t  <hex number>		Firmware type");
	puts ("-l  [filename.bin]	Input loader bin firmware file");
	puts ("-b  [filename.bin]	Output bin firmware and loader file");
	puts ("-a  <app id>			Application identifier");
	exit (1);
  }
  
  // поиск -i
  for(int i = 0; i < argc; i++)
  {
	  if(strcmp(argv[i], "-i") == 0)
		  break;
	  
	  if( i == argc)
	  {
		  fputs ("Missing input file",stderr);

		  exit (1);
	  }
		  
  }
  
  // обработка остальных ключей ( необходимо добавить проверку на валидность значений аргумента ключей)
  for(int i = 0; i < argc; i++)
  {
	  if( i == 0 )							// определение родительского каталога
	  {
			strcpy(NPath,argv[i]);
			
		  	for(int j = 0; j < MAX_PATH; j++)	// замена символов
			{
				if(NPath[j] == 0x5C)	// '\'
					NPath[j] = 0x2F;	// '/'
			}


			for(int j = MAX_PATH-1; j >=0; j--)
			{
				if(NPath[j] == 0x2F)	// '/'
					break;
				NPath[j] = 0x00;
			}
	  }		
	  
	  if(strcmp(argv[i], "-i") == 0)		// бинарник прошивки
	  {
			strcpy(inpbin_fn,argv[i+1]);
			
			char ch[] = ".bin";
			char *istr ;
			istr = strcasestr(inpbin_fn, ch);
			if( istr == NULL){fputs ("Input firmware binary file error",stderr); exit (1);}
				
			inpbin = fopen ( inpbin_fn , "rb+" );
			if (inpbin==NULL) {fputs ("Input binary file error",stderr); exit (1);}
			
			for(int j = 0; j < MAX_PATH; j++)	// замена символов
			{
				if(inpbin_fn[j] == 0x5C)	// '\'
					inpbin_fn[j] = 0x2F;	// '/'
			}
			
			printf("Input binary file       : [%s]\n",inpbin_fn);
	  }
	  
	  if(strcmp(argv[i], "-ol") == 0)		// выходной hex файл с прошивкой
	  {
			strcpy(outldr_fn,argv[i+1]);
			
			char ch[] = ".ldr";
			char *istr ;
			istr = strcasestr(outldr_fn, ch);
			if( istr == NULL){fputs ("Output firmware ihex file error",stderr); exit (1);}
			
			for(int j = 0; j < MAX_PATH; j++)	// замена символов
			{
				if(outldr_fn[j] == 0x5C)	// '\'
					outldr_fn[j] = 0x2F;	// '/'
			}
			
			printf("Output firmware ihex.ldr: [%s]\n",outldr_fn);
			
	  }
	  
	  if(strcmp(argv[i], "-oj") == 0)		// выходной hex файл с прошивкой
	  {
			strcpy(outjnx_fn,argv[i+1]);
			
			char ch[] = ".jnx";
			char *istr ;
			istr = strcasestr(outjnx_fn, ch);
			if( istr == NULL){fputs ("Output firmware ihex file error",stderr); exit (1);}
			
			for(int j = 0; j < MAX_PATH; j++)	// замена символов
			{
				if(outjnx_fn[j] == 0x5C)	// '\'
					outjnx_fn[j] = 0x2F;	// '/'
			}
			
			printf("Output firmware ihex.jnx: [%s]\n",outjnx_fn);
			
	  }
	  
	  if(strcmp(argv[i], "-t") == 0)		// тип прошивки
	  {
			type = str2hex(argv[i+1]);
			
			if( type > 0xFF){fputs ("Firmware type error",stderr); exit (1);}
			
			printf("Firmvare type           : (0x%Xh)\n",type);
	  }
	  
	  if(strcmp(argv[i], "-l") == 0)		// бинарник загрузчика
	  {
			strcpy(inpldr_fn,argv[i+1]);
			
			char ch[] = ".bin";
			char *istr ;
			istr = strcasestr(inpldr_fn, ch);
			if( istr == NULL){fputs ("Input loader binary file type error",stderr); exit (1);}
			
			for(int j = 0; j < MAX_PATH; j++)	// замена символов
			{
				if(inpldr_fn[j] == 0x5C)	// '\'
					inpldr_fn[j] = 0x2F;	// '/'
			}
			
			printf("Input loader binary file: [%s]\n",inpldr_fn);
	  }
	  
	  if(strcmp(argv[i], "-b") == 0)		// бинарник загрузчика и прошивки
	  {
			strcpy(outbin_fn,argv[i+1]);
			
			char ch[] = ".bin";
			char *istr ;
			istr = strcasestr(outbin_fn, ch);
			if( istr == NULL){fputs ("Output merge loader and firmware binary file error",stderr); exit (1);}
			
			for(int j = 0; j < MAX_PATH; j++)	// замена символов
			{
				if(outbin_fn[j] == 0x5C)	// '\'
					outbin_fn[j] = 0x2F;	// '/'
			}
			
			printf("Output merge binary file: [%s]\n",outbin_fn);
	  }
	  
	  if(strcmp(argv[i], "-a") == 0)		// ID прошивки
	  {
			AppID = (int)argv[i+1];
			printf("Firmvare AppID		    : (%d)\n",AppID);
	  }
	  
	    
  }
  
   putchar ('\n');
  
  // расчет смещения будет по определению заголовка


  
  // временный бинарник без индентефикатора
  tmpbin = fopen ( "./tmp.bin" , "wb+" );
  if (tmpbin==NULL) {fputs ("Temporary binary file error",stderr); exit (1);}
  
  // дополнительный временный бинарник с индентификитором
  tmpbin1 = fopen ( "./tmp1.bin" , "wb+" );
  if (tmpbin1==NULL) {fputs ("Second Temporary binary file error",stderr); exit (1);}

  // читаем исходный бинарник
  result = fread (buffer1,1,sizeof(buffer1),inpbin);
  if (result != sizeof(buffer1)) {fputs ("Input binary file reading error",stderr); exit (3);}
  
  // расчет смещения
  char res = FALSE;
  for(int i = 0; i < (sizeof(buffer1) - sizeof(magic)); i++)
  {
	  if(memcmp(&buffer1[i],magic,sizeof(magic)) == 0)
	  {
		  off = i;
		  res = TRUE;
		  break;
	  }
	  //printf("%X\n",memcmp(&buffer1[4],magic,sizeof(magic)));
  }
  if(res == FALSE){fputs ("Input binary file data error",stderr); exit (3);}
	  
  

  // получаем размер прошивки
  fseek (inpbin , 0 , SEEK_END);
  lSize = ftell (inpbin)-off;
  rewind (inpbin);

  printf("Size input bin file  = %8X\n",lSize);
  
  fseek (inpbin , off , SEEK_SET);
  // allocate memory to contain the whole file:
  buffer = (char*) malloc (sizeof(char)*lSize);
  if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}
  
    
  // копируем данные прошивки в буфер
  result = fread (buffer,1,lSize,inpbin);
  if (result != lSize) {fputs ("Input binary file reading error",stderr); exit (3);}

  unsigned char tmp[lSize];
  memcpy(&tmp[0],&buffer[0],lSize);
	
	tmp[15] = AppID;
	
	
// запись размера прошивки	
	tmp[16] = lSize >> 24;
	tmp[17] = lSize >> 16;
	tmp[18] = lSize >> 8;
	tmp[19] = lSize;

	tmp[24] = (type) ;
	tmp[25] = (type) ;
	tmp[26] = (type) ;
	tmp[27] = (type);

 
// расчет и запись crc32 

   crc = crc32( 0xFFFFFFFF, &tmp[0], lSize );
	
	tmp[20] = crc >> 24;
	tmp[21] = crc >> 16;
	tmp[22] = crc >> 8;
	tmp[23] = crc;
	
   printf("CRC32 input bin file = %8X\n",crc);
 
 // шифрование
 
 
   int strings;		// количество блоков по 64
   char tail;		// хвост 
   
   strings = lSize / SIZE;
   tail = lSize % SIZE;
   
   long gptx = 0;	// глобальный индекс элементов
   int gIs = 0;		// глобальный индекс строк
   
   seed = crc;
   
   unsigned char crypt[lSize];


   unsigned char *ptmp = &tmp[0];

   ///
	unsigned char crcidx[8];
	unsigned char crcrnd[8];
	
	
   // мешаем первую строку
   for(gptx = 0; gptx < SIZE; gptx++)
   {
	
	unsigned char tmpr = getRand(SIZE);
	if( ((gptx >= 16) && (gptx <= 24)))  		// не трогаем место с crc и размером
	{

			crypt[gptx] = ptmp[gptx];
		
	}
	else
		crypt[gptx] = ptmp[gptx] ^ tmpr;

	
	 //  printf("%2X[%d]  %2X{%d} \n",crypt[gptx],gptx,ptmp[gptx],tmpr);
   }

   //(crcrnd[i] != crcidx[i]) && !(((crcrnd[i] >= 16) && (crcrnd[i] <= 23)) || ((crcidx[i] >= 16) && (crcidx[i] <= 23)))
 /*  for(int i = 0; i < sizeof(crcrnd); i++)
   {
	   //printf("[%d]  {%d} \n",crcrnd[i],crcidx[i]);
	   
	   if(((crcrnd[i] >= 16) && (crcrnd[i] <= 23)) ^ ((crcidx[i] >= 16) && (crcidx[i] <= 23)))
	   {
			if( (crcrnd[i] >= 16) && (crcrnd[i] <= 23) )
			{
				//crypt[crcrnd[i]] = ptmp[crcrnd[i]];
				crypt[crcidx[i]] = ptmp[crcidx[i]] ^ crcidx[i];
			}
			else if ( (crcidx[i] >= 16) && (crcidx[i] <= 23) )
			{
				//crypt[crcidx[i]] = ptmp[crcidx[i]];
				crypt[crcrnd[i]] = ptmp[crcrnd[i]] ^ crcrnd[i];
			}
	   }
	   else if(!(((crcrnd[i] >= 16) && (crcrnd[i] <= 23)) && ((crcidx[i] >= 16) && (crcidx[i] <= 23))))
		   crypt[crcrnd[i]] = ptmp[crcidx[i]] ^ crcidx[i];
		
   }
   */
  
   ptmp +=SIZE;
   
   for(gIs = 1; gIs < strings; gIs++)				// заполняем остальное
   {
	   for(; gptx < (gIs+1)*SIZE; gptx++)
	   {
			unsigned char tmpr = getRand(SIZE);
			
			crypt[gptx] = ptmp[tmpr] ^ tmpr;			
	   }
	   ptmp +=SIZE;
   }

   for(; gptx < (strings*SIZE+tail); gptx++)		// заполняем хвост
	{
		unsigned char tmpr = getRand(tail);

		crypt[gptx] = ptmp[tmpr] ^ tmpr;
	}
   

	// потом убрать
	unsigned char encrypt[lSize];
	seed = crc;
	///

	unsigned char eperm[SIZE];
	int cnt = 0;
	int i = 0;
	///
	for(i = 0; i < (SIZE); i++)
	{
		unsigned char rndidx = getRand(SIZE);
	
	

	if(((i >= 16) && (i <= 23)) || ((rndidx >= 16) && (rndidx <= 23)) )
	{
		if( (i >= 16) && (i <= 23) )
			crcidx[i-16] = rndidx;
		
		if( (rndidx >= 16) && (rndidx <= 23) )
			crcrnd[rndidx-16] = i;
		
		if( (i >= 16) && (i <= 23) )
			encrypt[i] = crypt[i];
/*		switch(i){
			case 20:
				crcidx[0] = rndidx;
				break;
			case 21:
				crcidx[1] = rndidx;
				break;
			case 22:
				crcidx[2] = rndidx;
				break;
			case 23:
				crcidx[3] = rndidx;
				break;
		}*/
/*		switch(rndidx){
			case 20:
				crcrnd[0] = i;
				break;
			case 21:
				crcrnd[1] = i;
				break;
			case 22:
				crcrnd[2] = i;
				break;
			case 23:
				crcrnd[3] = i;
				break;
		}*/
//		if((i >= 20) && (i <= 23))
//			encrypt[i] = crypt[i];
	}
		else
		{
			if(rndidx / (SIZE/2))
				encrypt[rndidx+(i / SIZE)] = ~crypt[i];
			else
				encrypt[rndidx+(i / SIZE)] = crypt[i];
		}
		
		
	}
	//if(i == SIZE)
		{
			for(int j = 0; j < 4; j++)
				encrypt[crcidx[j]] = crypt[crcrnd[j]];
		}
	
//	for(int i = 0; i<32;i++)
//		printf("%2X",encrypt[i]);
	
	/*for(; i < (lSize - tail); i++)
	{
		unsigned char rndidx = getRand(SIZE);

		{
			
			if(rndidx / (SIZE/2))
				encrypt[rndidx+(i / SIZE)*SIZE] = ~crypt[i];
			else
				encrypt[rndidx+(i / SIZE)*SIZE] = crypt[i];
		}
	}

	for(; i < lSize; i++)
	{
		unsigned char rndidx = getRand(tail);

		{
			printf("%d \n",(i / SIZE)*SIZE);
			if(rndidx / (tail/2))
				encrypt[rndidx+(i / SIZE)*SIZE] = ~crypt[i];
			else
				encrypt[rndidx+(i / SIZE)*SIZE] = crypt[i];
		}
	}
	*/
//	FILE *encrpt = fopen ( "./encrpt.bin" , "wb+" );		//пишем з
//	fwrite(&encrypt, 1, lSize, encrpt);
//	fclose (encrpt);
	
	//for(int i = 0; i < 4; i++)
	//	printf("%d --%2X[%d] - %2X[%d] \n",i,encrypt[crcidx[i]],crcidx[i],crypt[crcrnd[i]],crcrnd[i]);
	
   
	//GetCurrentDirectoryA(MAX_PATH, NPath);
/*	sprintf(NPath,"%s",argv[0]);
//printf("%s %d\n",NPath,MAX_PATH);
	for(int i = 0; i < MAX_PATH; i++)
		{
			if(NPath[i] == 0x5C)	// '\'
				NPath[i] = 0x2F;	// '/'
				//printf("%2X\n",NPath[i]);
						//	  'c'					   'r'						'c'						 'r'
			if((NPath[i] == 0x63) && (NPath[i+1] == 0x72) && (NPath[i+2] == 0x63) && (NPath[i+3] == 0x00))
			{
				
				//NPath[i] 	= 0x00;
				//NPath[i+1] = 0x00;		// 'b'
				//NPath[i+2] = 0x00;		// 'i'
				///NPath[i+3] = 0x00;		// 'n'
				//break;
			}
		}
//printf("%s %d\n",NPath,MAX_PATH);
	for(int i = MAX_PATH-1; i >=0; i--)
	{
		if(NPath[i] == 0x2F)
		{
			//for(int j = i + 1; j < MAX_PATH; j++)
				
			break;
		}
		NPath[i] = 0x00;
	}
//printf("%s %d\n",NPath,MAX_PATH);
   */
  /* the whole file is now loaded in the memory buffer. */
  
  // записываем зашифрованный бинарник в 
	fwrite(&crypt, 1, lSize, tmpbin);
	fclose (tmpbin);
	
	char a[] = {0x07,0x03,0x00,0x08};
	fwrite(&a, 1, 4, tmpbin1);
	fseek (tmpbin1 , off , SEEK_SET);
	fwrite(&tmp, 1, lSize, tmpbin1);

  fclose (inpbin);
  fclose (tmpbin1);
  char str_srec[3*MAX_PATH];
  
  // формируем hex файл
  sprintf(str_srec,"%ssrec_cat.exe  ./tmp.bin -Binary -crop 0x00000000 0xFFFFFFFF -offset 0x00080000 -o ./TMP.hex -Intel -Output_Block_Size=64",NPath);
//  sprintf(str_srec,"%ssrec_cat.exe  ./crpt.bin -Binary -crop 0x00000000 0xFFFFFFFF -offset 0x00080000 -o ./TMP.hex -Intel -Output_Block_Size=64",NPath);
 // system(str_srec);
 // sprintf(str_srec,"%ssrec_cat.exe  ./tmp.bin -Binary -crop 0x00000000 0xFFFFFFFF -offset 0x00080000 -o ./TMP1.hex -Intel -Output_Block_Size=64",NPath);
  system(str_srec);
  
  FILE * pFile = fopen ( "TMP.hex" , "r+" );
  if (pFile==NULL) {fputs ("Temporary hex file open error",stderr); exit (1);}
  
  FILE * output = NULL;
  char current_symbol;
  
  // записываем .ldr

  if(strcmp(outldr_fn, " "))		// если задано имя выходного файла
	  output = fopen ( outldr_fn , "w+" );
  else if(strcmp(outjnx_fn, " ") != 0)
	  goto jnxfile;
  else
  {
		char str[MAX_PATH];
		sprintf(str,"%s", inpbin_fn);
		for(int i = 0; i < (MAX_PATH-3); i++)
		{
			if(str[i] == 0x5C)	// '\'
				str[i] = 0x2F;	// '/'
					//	  '.'				   'b'			         'i'					 'n'
			if((str[i] == '.') && (str[i+1] == 'b') && (str[i+2] == 'i') && (str[i+3] == 'n'))
			{
				str[i] 	 = '.';
				str[i+1] = 'l';		// 'l' 0x6C		'b' 0x62	
				str[i+2] = 'd';		// 'd' 0x64		'i' 0x69		
				str[i+3] = 'r';		// 'r' 0x72		'n' 0x6E		
			}
		}
		output = fopen ( str , "w+" );
  }
  
  if (output==NULL) {fputs ("Output hex file error",stderr); exit (1);}
  
  
  // формируем выходной hex файл
  fprintf(output,"$hexfile\n");
  
   
   
  while (!feof(pFile)) {
	  current_symbol = fgetc(pFile);
        if (current_symbol == EOF)
            break;
  fprintf(output, "%c", current_symbol);
  }
  
  fclose (output);
  
jnxfile:
  
  // записываем .jnx
  fseek (pFile , 0 , SEEK_SET);

  if(strcmp(outjnx_fn, " "))		// если задано имя выходного файла
	  output = fopen ( outjnx_fn , "w+" );
  else
  {
		char str[MAX_PATH];
		sprintf(str,"%s", inpbin_fn);
		for(int i = 0; i < (MAX_PATH-3); i++)
		{
			if(str[i] == 0x5C)	// '\'
				str[i] = 0x2F;	// '/'
					//	  '.'				   'b'			         'i'					 'n'
			if((str[i] == '.') && (str[i+1] == 'b') && (str[i+2] == 'i') && (str[i+3] == 'n'))
			{
				str[i] 	 = '.';//0x2E;
				str[i+1] = 'j';		// 'j' 0x6A		'b' 0x62	
				str[i+2] = 'n';		// 'n' 0x6E		'i' 0x69		
				str[i+3] = 'x';		// 'x' 0x78		'n' 0x6E		
			}
		}
		output = fopen ( str , "w+" );
  }
  
  if (output==NULL) {fputs ("Output hex file error",stderr); exit (1);}
  
  
  // формируем выходной hex файл
  fprintf(output,"$jnxfile\n");
  

   
  while (!feof(pFile)) {
	  current_symbol = fgetc(pFile);
        if (current_symbol == EOF)
            break;
  fprintf(output, "%c", current_symbol);
  }
  
  fclose (output);
  
  fclose (pFile);
  
  

  
  
  // склеиваем загрузчик и прошивку
  if(strcmp(inpldr_fn, " "))
	{
		/// добавить проверку загрузчика
		FILE * loader = fopen ( inpldr_fn , "r" );
		if (loader==NULL) {fputs ("Loader bin file open error",stderr); exit (1);}
		
		char idr[] = {0x07, 0x03, 0x00, 0x08, 0x12, 0x34, 0x56, 0x78, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x08, 0x01, 0x00, 0x00};
		char ldrbuff[sizeof(idr)];
		
		result = fread (ldrbuff,1,sizeof(ldrbuff),loader);
		if (result != sizeof(ldrbuff)) {fputs ("Loader bin file reading error",stderr); exit (3);}
		
		if(memcmp(ldrbuff,idr,sizeof(idr)) != 0)
			{fputs ("Loader bin file data error",stderr); exit (3);}
		
		fclose (loader);
		
		char str[4*MAX_PATH];
		char outstr[4*MAX_PATH];
		if(strcmp(outbin_fn, " "))		// если указан путь выходного файла
			sprintf(str,"%sImageMerge.exe -a %s -b tmp1.bin -o %s",NPath,inpldr_fn,outbin_fn);
		else
		{
			if(strcmp(outjnx_fn, " "))	// если указан выходной hex файл
			{
				sprintf(outstr,"%s",outjnx_fn);
				for(int i = 0; i < (4*MAX_PATH-3); i++)
				{
					if(outstr[i] == 0x5C)	// '\'
						outstr[i] = 0x2F;	// '/'
						//	  '.'					   'j'						'n'						 'x'
					if((outstr[i] == '.') && (outstr[i+1] == 'j') && (outstr[i+2] == 'n') && (outstr[i+3] == 'x'))
					{
						outstr[i] 	= '.';
						outstr[i+1] = 'b';		// 'b'
						outstr[i+2] = 'i';		// 'i'
						outstr[i+3] = 'n';		// 'n'
					}
				}
			}
			else if(strcmp(outldr_fn, " ") && strcmp(outjnx_fn, " "))	// если указан выходной hex jnx файл
			{
				sprintf(outstr,"%s",outldr_fn);
				for(int i = 0; i < (4*MAX_PATH-3); i++)
				{
					if(outstr[i] == 0x5C)	// '\'
						outstr[i] = 0x2F;	// '/'
						//	  '.'					   'l'						'd'						 'r'
					if((outstr[i] == '.') && (outstr[i+1] == 'l') && (outstr[i+2] == 'd') && (outstr[i+3] == 'r'))
					{
						outstr[i] 	= '.';
						outstr[i+1] = 'b';		// 'b'
						outstr[i+2] = 'i';		// 'i'
						outstr[i+3] = 'n';		// 'n'
					}
				}
			}
			else
			{
				char ldrstr[MAX_PATH] = "";
				char binstr[MAX_PATH] = "";
				char ldrname[MAX_PATH]= "";
				char binname[MAX_PATH]= "";
				sprintf(ldrstr,"%s",inpldr_fn);
				sprintf(binstr,"%s",inpbin_fn);
				

				
				char * dot;
				char * slash;
				int ch;
				for(int i = 0; i < MAX_PATH; i++)	// находим имя файла загрузчика
				{
					if(ldrstr[i] == 0x5C)	// '\'
						ldrstr[i] = 0x2F;	// '/'
				}
				
				ch = '.';
				dot = strrchr (ldrstr,ch);
				
				ch = '/';
				slash = strrchr (ldrstr,ch);
				
				if(slash)
					strncpy(ldrname,&ldrstr[slash-ldrstr+1],dot-slash-1);
				else
					strncpy(ldrname,ldrstr,dot-ldrstr);
				
							
				for(int i = 0; i < MAX_PATH; i++)	// находим имя файла прошивки
				{
					if(binstr[i] == 0x5C)	// '\'
						binstr[i] = 0x2F;	// '/'
				}
				
				ch = '.';
				dot = strrchr (binstr,ch);
				
				ch = '/';
				slash = strrchr (binstr,ch);
				
				if(slash)
					strncpy(binname,&binstr[slash-binstr+1],dot-slash-1);
				else
					strncpy(binname,binstr,dot-binstr);

				
				
				sprintf(outstr,"%s%s_%s.bin",NPath,ldrname,binname);
				
				
			}
		}
			
//printf("\n [%s] \n", outstr);
		sprintf(str,"%sImageMerge.exe -a %s -b tmp1.bin -o %s",NPath,inpldr_fn,outstr);
		system(str);
	}
  
  remove("TMP.hex");

  remove("tmp.bin");
  remove("tmp1.bin");
  //remove("crpt.bin");
  
  free (buffer);
 // puts ("\nPress AnyKey to Exit");
  //_getch();
  return 0;
	
}
