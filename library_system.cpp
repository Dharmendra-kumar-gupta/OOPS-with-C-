#include<iostream>
#include<fstream>
#include<string.h>
//#include<stdio>
//#include<conio.h>
#include<stdlib.h>

using namespace std;
class book
{
private:
	int bookid;
	char title[20];
	float price;
public:
	book()
	{
		bookid=0;
		strcpy(title,"No title");
		price=0;
	}
void getbookdata()
{
	cout<<"Enter book ID: ";
	cin>>bookid;
	cout<<"Enter book title: ";
	cin.ignore();
	cin.getline(title,19);
	cout<<"Enter book price: ";
	cin>>price;
}
void showbookdata()
{
	cout<<bookid<<" "<<title<<" "<<price;
}

int storebook();
void viewallbook();
void searchbook(char *);
void deletebook(char *);
void updatebook(char *);

};


int book :: storebook()
{
	if(bookid==0 && price==0)
	{
		cout<<"Book data not initilizaed";
		return(0);
	}
	else
	{
		ofstream fout;
		fout.open("file.txt",ios::app|ios::binary);
		fout.write((char *)this,sizeof(* this));
		fout.close();
		return(1);
	}
}

void book :: viewallbook()
{
	ifstream fin;
	fin.open("file.txt",ios::in|ios::binary);
	if(!fin)
		cout<<"File not found";
	else
	{
		fin.read((char *)this,sizeof(* this));
		while(!fin.eof())
		{
			showbookdata();
			fin.read((char *)this,sizeof(* this));
		}
	fin.close();
	}
} 

void book :: searchbook(char *t)
{
	int counter=0;
	ifstream fin;
	fin.open("file.txt",ios::in|ios::binary);
	if(!fin)
		cout<<"\nFile not found";
	else
	{
		fin.read((char *)this,sizeof(* this));
		while(!fin.eof())
		{
			if(!strcmp(t,title))
			{
				showbookdata();
				counter++;
			}
			fin.read((char *)this,sizeof(* this));
		}
		if(counter==0)
			cout<<"\n Record not found";
			fin.close();
	}
}

void book :: deletebook(char *t)
{
	ifstream fin;
	ofstream fout;
	fin.open("file.txt",ios::in|ios::binary);
	if(!fin)
		cout<<"\nFile not found";
	else
	{
		fout.open("temp.txt",ios::out|ios::binary);
		fin.read((char *)this,sizeof(* this));
		while(!fin.eof())
		{
			if(strcmp(title,t))
				{
				fout.write((char *)this,sizeof(* this));
				fin.read((char *)this,sizeof(* this));
				}
		}
		fin.close();
		fout.close();
		remove("file.txt");
		rename("temp.txt","file.txt");
	}
}

void book :: updatebook(char *t)
{
	fstream file;
	file.open("file.txt",ios::in|ios::out|ios::ate|ios::binary);
	file.seekg(0);
	file.read((char *)this,sizeof(* this));
	while(!file.eof())
	{
		if(!strcmp(t,title))
		{
			getbookdata();
			long int p=sizeof(* this);
			file.seekp(file.tellp()-p);
			file.write((char *)this,sizeof(* this));
		}
		file.read((char *)this,sizeof(* this));
	}
	file.close();
}

int menu()
{
	int choice;
	cout<<"\nBook Management";
	cout<<"\n1.  Insert book record";
	cout<<"\n2.  View all book recore";
	cout<<"\n3.  Search book record";
	cout<<"\n4.  Delete book record";
	cout<<"\n5.  Update book record";
	cout<<"\n6.  Exit";
	cout<<"\n\n Enter choice what you want to do: ";
	cin>>choice;
	return(choice);
}

int main()
{
	book b1;
	char title[20];
	while(1)
	{
		system("clear");
		switch(menu())
		{
		case 1:
			b1.getbookdata();
			b1.storebook();
			cout<<"\n Record inserted";
			break;
		case 2:
			b1.viewallbook();				
			break;
		case 3:
			cout<<"\nEnter title of book to search: ";
			cin.ignore();
			cin.getline(title,19);
			b1.searchbook(title);
			break;
		case 4:
			cout<<"\nEnter title of book to delete: ";
			cin.ignore();
			cin.getline(title,19);
			b1.deletebook(title);
			break;
		case 5:
			cout<<"\nEnter title of book to update: ";
			cin.ignore();
			cin.getline(title,19);
			b1.updatebook(title);
			break;
		case 6:
			cout<<"\nThank you for using this application";
			cout<<"\nPress any key to exit";
			//getch();
			exit(0);
		default:
			cout<<"\nInvalid choice";
		}
	//getch();
	}
}	



