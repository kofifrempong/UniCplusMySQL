#include <iostream>
#include </usr//local/mysql-5.6.41-macos10.13-x86_64/include/mysql.h>
#include </opt//local/include/mysql57/mysql/mysqld_error.h>
#include <unistd.h>
#include <sstream>
using namespace std;


const char* HOST = "localhost";
const char* USER = "root";
const char* PW = "";
const char* DB = "new_schema";

class Student{
private:
 int Id;
public:
Student() : Id(0) {}

void setId(int id) {
  Id = id;
 }
 
 int getId() {
  return Id;
 }
 
};

class Library{
private:
 string Name;
 int Quantity;
public:
Library() : Name(""), Quantity(0) {}

void setName(string name) {
  Name = name;
}

void setQuantity(int quantity) {
  Quantity = quantity;
}

int getQuantity() {
  return Quantity;
}
string getName() {
  return Name;
}

	
};

void admin(MYSQL* conn, Library l, Student s){
	bool closed = false;
	while(!closed){
	int choice;
cout << "1. Add Book." << endl;
 cout << "2. Add Student." << endl;
 cout << "0. Exit." << endl;
 cout << "Enter Choice: ";
 cin >> choice;
 
 if(choice==1){
 	system("cls");
string name;
int quantity;

cout<<"Book Name: ";
cin>>name;
l.setName(name);

cout<<"Enter Quantity: ";
cin>>quantity;
l.setQuantity(quantity);

int Iq = l.getQuantity();
stringstream ss;
ss<<Iq;
string Sq = ss.str();

string book = "INSERT INTO library (Name,Quantity) VALUES('"+l.getName()+"', '"+Sq+"') ";
if(mysql_query(conn,book.c_str())){
	cout<<"Error: "<<mysql_error(conn)<<endl;
}
else{
	cout<<"Book Inserted Successfuly"<<endl;
}
 }// if1
 
 else if(choice==2){
 	system("cls");
int id;
 cout << "Enter Student ID: ";
 cin >> id;
 s.setId(id);

 stringstream ss;
ss<<id;
string Sq = ss.str();

 
  string st = "INSERT INTO student (id) VALUES('"+Sq+"')";
 if (mysql_query(conn, st.c_str())) {
 cout << "Error: " << mysql_error(conn) << endl;
 }
else {
  cout << "Student Inserted Successfully" << endl; 
}
}//if2
else if(choice ==0){
	closed = true;
	cout<<"System is closing"<<endl;
}
	}//while
usleep(30000);
}//function

//display function
void display(MYSQL* conn){
	system("cls");
cout<<"Available Books"<<endl;
cout<<"***************"<<endl;

string disp= "SELECT * FROM library";
 if (mysql_query(conn, disp.c_str())) {
  cout << "Error: " << mysql_error(conn) << endl;
 }
 else{
 	MYSQL_RES* res;
 	res= mysql_store_result(conn);
 	if(res){
 		int num= mysql_num_fields(res);
 	MYSQL_ROW row;
 	while(row=mysql_fetch_row(res)){
 		for(int i=0; i< num; i++){
 			cout<<" "<<row[i];
		 }
		cout<<endl;
	 }
	 mysql_free_result(res);
	 }
 }
}

//book function

int book(MYSQL* conn, string Bname){
string exist = "SELECT Name, Quantity FROM library WHERE Name = '" + Bname + "'";
if (mysql_query(conn, exist.c_str())) {
 cout << "Error: " << mysql_error(conn) << endl;
 }
else{
MYSQL_RES* res;
res = mysql_store_result(conn);
if(res){
	int num = mysql_num_fields(res);
MYSQL_ROW row;
while(row=mysql_fetch_row(res)){
	for(int i=0; i< num; i++){
	if(Bname == row[i]){
	int quantity = atoi(row[i+1]);
	return quantity;	
	}
	else{
		cout<<"Book Not Found."<<endl;
	}
	}
} 
mysql_free_result(res);
}
	
}//else if exist
return 0;
usleep(50000);
}//function

// user function

void user(MYSQL* conn, Library l, Student s){
	system("cls");
	display(conn);
int Sid;
cout<<"Enter Your ID: ";
cin>>Sid;

stringstream ss;
ss<<Sid;
string Sq = ss.str();

string com = "SELECT * FROM student WHERE id = '"+Sq+"'";
 if (mysql_query(conn, com.c_str())) {
   cout << "Error: " << mysql_error(conn) << endl;
 }
 else{
MYSQL_RES* res;
res=mysql_store_result(conn);
if(res){
	int num= mysql_num_rows(res);
	if(num==1){
		cout<<"Student ID Found."<<endl;
	string Bname;
	cout<<"Enter Book Name: ";
	cin>>Bname;
	if(book(conn,Bname) > 0){
		int bookQuantity = book(conn,Bname)-1;
		stringstream ss;
		ss<<bookQuantity;
		string Sq = ss.str();

string upd ="UPDATE library SET Quantity ='"+Sq+"' WHERE Name = '"+Bname+"' ";
if(mysql_query(conn,upd.c_str())){
	cout<<"Error: "<<mysql_error(conn)<<endl;
}
else{
	cout<<"Book is available. Borrowing Book...."<<endl;
}
	}
	else{
		cout<<"Book is not Available."<<endl;
	}
	}
else if(num==0){
	cout<<"This Student is Not Registered."<<endl;
}
}
mysql_free_result(res);
 }	
}

int main() {
	Student s;
	Library l;

MYSQL* conn;
conn = mysql_init(NULL);

if(!mysql_real_connect(conn,HOST, USER, PW,DB,3306,NULL,0)){
	cout<<"Error: "<<mysql_error(conn)<<endl;
}
else{
	cout<<"Logged In!"<<endl;
}
usleep(30000);
bool exit = false;
while(!exit){
	system("cls");
	int val;
cout << "Welcome To Library Management System" << endl;
cout << "************************************" << endl;
cout << "1. Administration." << endl;
cout << "2. User." << endl;
cout << "0. Exit." << endl;
cout<<"Enter Choice: ";
cin>>val;

if(val==1){
	system("cls");
admin(conn,l,s);	
}//if1 main

else if(val==2){
user(conn,l,s);
usleep(50000);	
}
else if(val==0){
	exit= true;
	cout<<"Good Luck!"<<endl;
	usleep(30000);
}

}//while
mysql_close(conn);
	return 0;
}
