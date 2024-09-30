#include <iostream>
#include <mysql.h>
#include <mysqld_error.h>
#include <unistd.h>
#include <sstream>
using namespace std;


const char* HOST = "localhost";
const char* USER = "root";
const char* PW = ""; //your password here 
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

class Login{
private:
	string userId, userPW;
	int stId;
public:
	Login(): userId(""), userPW("") {}
	
void setId(string id) {
    userId = id;
 }

 void setstId(int id) {
	stId = id;
 }

 void setPW(string pw) {
    userPW = pw;
 }
 
 string getId() const {
    return userId;
 }

 int getstId() {
	return stId;
 }

string getPW() const {
    return userPW;
 }
 
};

char encryptCh(char ch, int shift){
if(isalpha(ch)){
	char base = isupper(ch) ? 'A' : 'a';
	char encrypted_ch =(ch - base + shift + 26) % 26 + base;
return encrypted_ch;
}
if(isdigit(ch)){
    char encrypted_ch = (ch - '0' + shift + 10) % 10 + '0';
    return encrypted_ch;	
}
return ch;	
}

string encrypt(const string& password, int shift){
	string encrypted = "";
for(int i=0; i<password.length(); i++){
char ch = password[i];
char encryptedChar = encryptCh(ch,shift);
encrypted += encryptedChar;
}
return encrypted;
}

char decryptCh(char ch, int shift) {
if (isalpha(ch)) {
    char base = isupper(ch) ? 'A' : 'a';
    char decrypted_ch = (ch - base - shift + 26) % 26 + base;
    return decrypted_ch;
} 
else if (isdigit(ch)) {
    char decrypted_ch = (ch - '0' - shift + 10) % 10 + '0';
    return decrypted_ch;
} 
else{
	return ch;
}	
}

string decrypt(const string& encrypted,int shift){
string decrypted = "";
 for (size_t i = 0; i < encrypted.length(); i++) {
    char ch = encrypted[i];
    char decryptedChar = decryptCh(ch, shift);
    decrypted += decryptedChar;
 }
 return decrypted;	

}
string DBpw(MYSQL* conn, const string& id){
	string encryptedPW;
	
string get= "SELECT PW FROM password WHERE Id='"+id+"' ";
if (mysql_query(conn, get.c_str())) {
    cout << "Error: " << mysql_error(conn) << endl;
}
else{
MYSQL_RES* res;
res = mysql_store_result(conn);
if(res){
MYSQL_ROW	row = mysql_fetch_row(res);
if(row){
	encryptedPW = row[0];
}
}
}
return encryptedPW;
}

string stDBpw(MYSQL* conn, int id){
	string encryptedPW;
	stringstream ss;
ss<<id;
string Sq = ss.str();
string get= "SELECT PW FROM stpassword WHERE id='"+Sq+"' ";
if (mysql_query(conn, get.c_str())) {
    cout << "Error: " << mysql_error(conn) << endl;
}
else{
MYSQL_RES* res;
res = mysql_store_result(conn);
if(res){
MYSQL_ROW	row = mysql_fetch_row(res);
if(row){
	encryptedPW = row[0];
}
}
}
return encryptedPW;
}


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
 	while(row==mysql_fetch_row(res)){
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
	display(conn);
/*int Sid;
cout<<"Enter Your ID: ";
cin>>Sid;*/

stringstream ss;
ss<<s.getId();
string Sq = ss.str();
   cout << "" +Sq+""  << endl;


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
	Login l;
	Library li;

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
int shift = 1;
while(!exit){
	int val;
cout << "Welcome To Library Management System" << endl;
cout << "************************************" << endl;
cout << "1. Administration." << endl;
cout << "2. User." << endl;
cout << "0. Exit." << endl;
cout<<"Enter Choice: ";
cin>>val;

if(val==1){
	cout << "1. Signup." << endl;
cout << "2. Login." << endl;
cout << "0. Exit." << endl;
cout << "Enter Your Choice: ";
int val;
cin>>val;

if(val==1){

	// Admin password logic 
    string id, pw;
cout << "Enter username ID For Signup: ";
cin >> id;
l.setId(id);
cout << "Enter A Strong Password: ";
cin >> pw;
l.setPW(pw);

string encryptedPW = encrypt(l.getPW(),shift);

string Sup= "INSERT INTO password (Id, PW) VALUES ('"+l.getId()+"', '"+encryptedPW+"' )";
if(mysql_query(conn,Sup.c_str())){
	cout<<"Error: "<<mysql_error(conn)<<endl;
}
else{
	cout<<"Singup Successfuly"<<endl;
}
usleep(30000);	
}

else if(val==2){
string id, pw;
cout << "Enter username ID: ";
cin >> id;
cout << "Enter Your password: ";
cin >> pw;

string getDB = DBpw(conn,id);

if(!getDB.empty()){
string decryptedPW = decrypt(getDB,shift)	;

if(decryptedPW == pw){
	cout<<"Welcome"<<endl;
	admin(conn,li,s);	

}
else{
	cout<<"Incorrect Password. Try Again!"<<endl;
}
}
else{
	cout<<"User ID not found Try Again!";
}

usleep(50000);
	
}

else if(val==0){
	exit = true;
	cout<<"Bye!"<<endl;
}
else{
	cout<<"Invalid Input"<<endl;
}



}

	// User password logic 

else if(val==2){
	cout << "1. Signup." << endl;
cout << "2. Login." << endl;
cout << "0. Exit." << endl;
cout << "Enter Your Choice: ";
int val;
cin>>val;

if(val==1){
    int id;
	string pw;
cout << "Enter numeric ID For Signup: ";
cin >> id;
l.setstId(id);
cout << "Enter A Strong Password: ";
cin >> pw;
l.setPW(pw);

string encryptedPW = encrypt(l.getPW(),shift);

stringstream ss;
ss<<l.getstId();
string Sq = ss.str();
string Sup= "INSERT INTO stpassword (id, PW) VALUES ('"+Sq+"', '"+encryptedPW+"' )";
 string st = "INSERT INTO student (id) VALUES('"+Sq+"')";
 
if(mysql_query(conn,Sup.c_str()) || mysql_query(conn, st.c_str())){
	cout<<"Error: "<<mysql_error(conn)<<endl;
}
else{
	cout<<"Singup Successfuly"<<endl;
}
usleep(30000);	
}// if1

else if(val==2){
int id;
string pw;
cout << "Enter numeric ID: ";
cin >> id;
cout << "Enter Your password: ";
cin >> pw;

string getDB = stDBpw(conn,id);

if(!getDB.empty()){
string decryptedPW = decrypt(getDB,shift)	;

if(decryptedPW == pw){
	cout<<"Welcome"<<endl;
	s.setId(id);
	user(conn,li,s);

}
else{
	cout<<"Incorrect Password. Try Again!"<<endl;
}
}
else{
	cout<<"User ID not found Try Again!";
}

usleep(50000);
	
}//if2

else if(val==0){
	exit = true;
	cout<<"Bye!"<<endl;
}
else{
	cout<<"Invalid Input"<<endl;
}
usleep(50000);	

}//while



else if(val==0){
	exit= true;
	cout<<"Good Luck!"<<endl;
	usleep(30000);
}


mysql_close(conn);
	return 0;

}

}
