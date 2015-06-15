#if defined(__GNUC__)
  // Ensure we get the 64-bit variants of the CRT's file I/O calls
  #ifndef _FILE_OFFSET_BITS
    #define _FILE_OFFSET_BITS 64
  #endif
  #ifndef _LARGEFILE64_SOURCE
    #define _LARGEFILE64_SOURCE 1
  #endif
#endif
#include "osrng.h"
using CryptoPP::AutoSeededRandomPool;
#include<conio.h>
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <string>
using std::string;

#include <cstdlib>
using std::exit;

#include "cryptlib.h"
using CryptoPP::Exception;

#include "hex.h"
using CryptoPP::HexEncoder;
using CryptoPP::HexDecoder;

#include "filters.h"
using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::StreamTransformationFilter;

#include "aes.h"
using CryptoPP::AES;

#include "modes.h"
using CryptoPP::CFB_Mode;
#include<fstream>
#include<iostream>
#include<string>
#include<stdio.h>
#include<conio.h>
#include<windows.h>

#include<string.h>
#define MAX 10000
#include "miniz.c"
using namespace std;

class FileFinder
{
   int file_ctr;//How many files are there?
public:
    FileFinder(){file_ctr=0;}
    void getfile();
    void search(const char* path,const char* filename);
};

void FileFinder::getfile()
{
    char drive[10]={"D:\\"};//make it a 2D array and add all your Drives
    char filename[MAX];
    cout<<"Enter the File name\n";
    cin>>filename;
    FILE* fptr=fopen("test.txt","wt");//Delete the previous contents of File
    fclose(fptr);
	search(drive,filename);//loop through all drive[i]
    if(file_ctr==0)
       {
        printf("\nNo File FOund!!!\n");
        exit(0);
       }
    else if(file_ctr==1)
    {
	char tmp[MAX];
	FILE* fptr=fopen("test.txt","rt");
	fgets(tmp,MAX,fptr);
	fclose(fptr);
	tmp[strlen(tmp)-1]=NULL;
	cout<<"\nFile found at Directory\t";
	printf("%s",tmp);
    }
    else
    {
       char tmp[MAX];
       FILE* fptr=fopen("test.txt","rt");
        cout<<"\n"<<file_ctr<<" Files Found!!\n";
       cout<<"\nFiles Found AT\n";
       for(int i=1;i<=file_ctr;i++)
       {
        fgets(tmp,MAX,fptr);
        tmp[strlen(tmp)-1]=NULL;
        cout<<"\n"<<i<<"\t"<<tmp;
        }
       fclose(fptr);
    }
    cout<<"\n\nPress any key to exit...";
    _getch( );
}
void FileFinder::search(const char* path,const char* filename)
{
    char tmp[MAX];
    WIN32_FIND_DATA FindFileData;
    HANDLE hFind;
    strcpy(tmp,path);
    strcat(tmp,filename);
    hFind = FindFirstFile(tmp, &FindFileData);
    if(hFind != INVALID_HANDLE_VALUE)
    {
	while(hFind != INVALID_HANDLE_VALUE)
	{
	    char tmp1[MAX];
	    FILE* fptr=fopen("test.txt","at");
	    strcpy(tmp1,path);
	    cout<<"\nSearching...  "<<tmp1;
	    strcat(tmp1,FindFileData.cFileName);
	    fputs(tmp1,fptr);
	    fputs("  \n",fptr);
	    fclose(fptr);
	    file_ctr++;
        if (!FindNextFile(hFind, &FindFileData))
		{
			FindClose(hFind);
			hFind = INVALID_HANDLE_VALUE;
		}
	}
    }
    strcpy(tmp,path);
    strcat(tmp,"*.*");
    hFind = FindFirstFile(tmp, &FindFileData);
    while(hFind != INVALID_HANDLE_VALUE)
    {
       if(strcmp(FindFileData.cFileName,".")!=0 && strcmp(FindFileData.cFileName,"..")!=0 &&
			      FindFileData.dwFileAttributes==FILE_ATTRIBUTE_DIRECTORY)
       {
        char temp1[MAX];
        strcpy(temp1,path);
        strcat(temp1,FindFileData.cFileName);
        strcat(temp1,"\\");
        system("CLS");
        cout<<"\nSearching...  "<<temp1;
        search(temp1,filename);
       }
        if (!FindNextFile(hFind, &FindFileData))
		{
			FindClose(hFind);
			hFind = INVALID_HANDLE_VALUE;
		}
    }
}

static char *s_pTest_str=new char(MAX);
static const char *s_pComment = "This is a comment";
namespace zipping
{
	typedef unsigned char uint8;
    typedef unsigned short uint16;
    typedef unsigned int uint;
}
int main(void)
{
	FileFinder f;
    f.getfile();
	
	//Encryptinh using the Aes encryption alogorithm
	//Encrypt then zip
	char arr[MAX];
	fstream obj1;
	//fstream obj3;
	obj1.open("test.txt");

	if(obj1.is_open())
	{
		
				//obj1.getline(arr,MAX,'\n');
			//stub for encryption
					
				AutoSeededRandomPool prng;

				byte key[AES::DEFAULT_KEYLENGTH];
				prng.GenerateBlock(key, sizeof(key));

				byte iv[AES::BLOCKSIZE];
				prng.GenerateBlock(iv, sizeof(iv));

				string plain ;
				string cipher, encoded, recovered;

				char ch;	
				while(obj1.get(ch))
				{
					plain+=ch;
				}	
				obj1.close();
				// Pretty print key
				encoded.clear();
				StringSource(key, sizeof(key), true,new HexEncoder(new StringSink(encoded))); // StringSource
				cout << "\n\nkey: " << encoded << endl;

				// Pretty print iv
				encoded.clear();
				StringSource(iv, sizeof(iv), true,new HexEncoder(new StringSink(encoded))); // StringSource
				cout << "iv: " << encoded << endl;

				_getch();

				try
				{
					cout << "plain text: \n\n" << plain << endl;

					CFB_Mode< AES >::Encryption e;
					e.SetKeyWithIV(key, sizeof(key), iv);

					// CFB mode must not use padding. Specifying
					//  a scheme will result in an exception
					StringSource(plain, true,new StreamTransformationFilter(e,new StringSink(cipher))); // StringSource
				}
				catch(const CryptoPP::Exception& e)
				{
					cerr << e.what() << endl;
					exit(1);
				}
				encoded.clear();
				StringSource(cipher,true,new HexEncoder(new StringSink(encoded))); 

				//out<<"Cipher text\n\n"<<encoded;

				obj1.open("test.txt",fstream::out);
				for(int i=0;i<cipher.length();i++)
					obj1.put(encoded.at(i));
				obj1.close();
				cout<<"\nSuccessfully Encoded Using AES encryption standard\n";
				

			}
			
		

	
	else
	
		cout<<"\nError opening Directory listing\n";


//Encryption Okay
	char ch;
	string rd;
	ifstream obj;
	obj.open("test.txt");
	if(!obj)
	cout<<"Error";
	while(obj.get(ch))
	{
	   rd+=ch;
	}
	obj.close();
	remove("test.txt");

	int fix=0;
	while(fix<rd.size())
	{
	  if(rd.at(fix)!='\n')
	  s_pTest_str[fix]=rd.at(fix);
	  else s_pTest_str[fix]='\n';
	 fix++;	
	}
//	s_pTest_str[fix]='\0';
	cout<<endl;
	cout<<s_pTest_str;
	int i, sort_iter;
    mz_bool status;
    size_t uncomp_size;
    mz_zip_archive zip_archive;
    void *p;
    const int N = 1;
    char data[2048];
    char archive_filename[64];
    static const char *s_Test_archive_filename = "Final.zip";
  //  assert((strlen(s_pTest_str) + 64) < sizeof(data));
    printf("\n\nminiz.c version: %s\n", MZ_VERSION);
  // Delete the test archive, so it doesn't keep growing as we run this test
  remove(s_Test_archive_filename);
  // Append a  text file to the test archive
    sprintf(archive_filename, "Details.txt");
    sprintf(data,"%s",s_pTest_str);
    status = mz_zip_add_mem_to_archive_file_in_place(s_Test_archive_filename, archive_filename,data, strlen(data) + 1, s_pComment, (zipping::uint16)strlen(s_pComment),MZ_BEST_COMPRESSION);
    if (!status)
    {
      printf("mz_zip_add_mem_to_archive_file_in_place failed!\n");
      return EXIT_FAILURE;
    }
  printf("Success.\n");
  _getch();
  return EXIT_SUCCESS;
}
