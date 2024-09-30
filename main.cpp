#include <iostream>
#include <mysql.h>
#include <mysqld_error.h>
#include <unistd.h>
#include <sstream>
using namespace std;

const char* HOST = "localhost";
const char* USER = "root"; // Enter your username
const char* PW = ""; // Enter your password
const char* DB = "new_schema"; // Enter your database name

class University{
	private:
		int Id;
		string Name, Subject, Gender;
		float Gpa;
	public:
	University():Id(0),Name(""),Subject(""),Gpa(0.0),Gender("") {}
	
	void setId(int id){
		Id = id;
	}
	
 void setName(string name){
	Name=name;
 }	
	
 void setSubject(string subject){
	Subject=subject;
 }
	
 void setGrade(float Gpa){
	Gpa= Gpa;
 }	
 void setGender(string Gender){
	Gender= Gender;
 
 }	
 
 
 //getter fucntions
 
 int getId(){
 	return Id;
 }
	
 string getName(){
    return Name;
 }
	
 string getSubject(){
     return Subject;
 }
 string getGender(){
     return Gender;
 }
	
 float getGrade(){
  return Gpa;
 }
};


class Room {
	private:
		string Name;
		int Bed;
	    float Price;


	public:
		Room():Name(""),Bed(0),Price(0.0){
			
		}

		
	void setName(string name){
	Name=name;
 }	
	
 void setBed(int bed){
	Bed=bed;
 }
	
 void setPrice(float price){
	Price= price;
 }	

	string getName(){
		return Name;
	}
	
	int getBed(){
		return Bed;
	}
	
	float getPrice(){
		return Price;
	}
};


//insert function
void insertS(MYSQL* conn, University u){
	 int id;
 string name,subject,gender;
 float Gpa;
 
 cout<<"Enter Id: ";
 cin>>id;
 u.setId(id);
 
  cout<<"Enter Name: ";
 cin>>name;
 u.setName(name);

 cout<<"Enter Subject: ";
 cin>>subject;
 u.setSubject(subject);

 cout<<"Enter Gpa: ";
 cin>>Gpa;
 u.setGrade(Gpa);
 
  cout<<"Enter Gender: ";
 cin>>gender;
 u.setGender(gender);

 int iId= u.getId();
 float fGrade = u.getGrade();
 
 stringstream ss;
 ss<<iId;
 string sId = ss.str();
 
  stringstream as;
 as<<fGrade;
 string sGrade= as.str();
 
 string ins= "INSERT INTO student (Id, Name, Subject, Gpa, Gender) VALUES ('"+sId+"', '"+u.getName()+"', '"+u.getSubject()+"', '"+sGrade+"', '"+u.getGender()+"')";
 if(mysql_query(conn,ins.c_str())){
 	cout<<"Error: "<<mysql_error(conn)<<endl;
 }
 else{
 	cout<<"Data Inserted Successfuly."<<endl;
 }
 usleep(30000);
}

//show function

void showRecord(MYSQL* conn){
string show= "SELECT * FROM student";
 if(mysql_query(conn,show.c_str())){
 	cout<<"Error: "<<mysql_error(conn)<<endl;
 }
 else{
 	MYSQL_RES* res ;
 	res = mysql_store_result(conn);
 	if(res){
 	int num = mysql_num_fields(res);
 	MYSQL_ROW row;
 	while(row=mysql_fetch_row(res)){
 		for(int i=0; i< num; i++){
 		cout<<" "<<row[i];
		 }
		 cout<<endl;
	 }
	 }
 }
 usleep(50000);
}

//search function
void searchS(MYSQL* conn){
	 int id;
 cout<<"Enter Student ID: ";
 cin>>id;
 	
 stringstream ss;
 ss<<id;
 string sId= ss.str();
 
 string show = "SELECT * FROM student WHERE Id ='"+sId+"' ";
 if(mysql_query(conn,show.c_str())){
cout<<"Error: "<<mysql_error(conn)<<endl;
}
else{
MYSQL_RES* res;
res = mysql_store_result(conn);
if(res){
	MYSQL_ROW row = mysql_fetch_row(res);
if(row){
	int num = mysql_num_fields(res);
	for(int i=0; i<num; i++){
		cout<<" "<<row[i];
	}
}
mysql_free_result(res);
}
}
usleep(50000);
}

// update function

void updateS(MYSQL* conn, University u){
	int id;
    cout << "Enter Id: ";
    cin >> id;

    // Assuming u is a student object that has been properly initialized
    // and has getters and setters for the fields: Subject, Name, GPA, and Gender.
    
    string subject;
    cout << "Enter New Subject: ";
    cin >> subject;
    u.setSubject(subject);

    string name;
    cout << "Enter New Name: ";
    cin >> name;
    u.setName(name);

    float gpa;
    cout << "Enter New GPA: ";
    cin >> gpa;
    u.setGrade(gpa);

    string gender;
    cout << "Enter New Gender: ";
    cin >> gender;
    u.setGender(gender);

    // Safely construct the SQL query without converting the id to a string.
    stringstream ss;
    ss << "UPDATE student SET "
       << "Subject = '" << u.getSubject() << "', "
       << "Name = '" << u.getName() << "', "
       << "GPA = " << u.getGrade() << ", "
       << "Gender = '" << u.getGender() << "' "
       << "WHERE Id = " << id;

    string upd = ss.str();

 if(mysql_query(conn,upd.c_str())){
cout<<"Error: "<<mysql_error(conn)<<endl;
}

else{
 cout<<"Data Updated Successfuly"<<endl;
}
usleep(30000);
}

//delete function

void deleteS(MYSQL* conn){
 int id;
 cout<<"Enter Student ID: ";
 cin>>id;
 	

 stringstream ss;
 ss<<id;
 string sId= ss.str();	
 
 string del = "DELETE FROM student WHERE Id ='"+sId+"' ";
 if(mysql_query(conn,del.c_str())){
 cout<<"Error: "<<mysql_error(conn)<<endl;
}

else{
 cout<<"Data Deleted"<<endl;
}
usleep(30000);
}






Room insertroom(MYSQL* conn, Room r) {
string n;
int b;
float p;


	cout<<endl;
cout<<"Enter Room Name: ";
cin>>n;
	r.setName(n);

	cout<<endl;
cout<<"Enter number of Beds: ";
cin>>b;
	r.setBed(b);


cout<<endl;
cout<<"Enter Price (in floating point format): ";
cin>>p;
	r.setPrice(p);




int intB =r.getBed();
float floatP = r.getPrice(); 

stringstream ss;
ss<<intB;
string strB = ss.str();

stringstream as;
as<<floatP;
string strP = as.str();

string insert= "INSERT INTO room(Name, Bed, Price) VALUES ('"+r.getName()+"', '"+strB+"', '"+strP+"' )";
if(mysql_query(conn,insert.c_str())){
	cout<<"Error: "<<mysql_error(conn)<<endl;
}
else{
	cout<<"Inserted Successfuly!"<<endl;
}
return r;

}

void roomRegister(MYSQL* conn, Room r) {

/*
*/



	string n;
	cout<<endl;
cout<<"Enter Student Name: ";
cin>>n;

int total;
string check= "SELECT Bed FROM room WHERE Name = '"+r.getName()+"'";

if(mysql_query(conn,check.c_str())){
	cout<<"Error: "<<mysql_error(conn)<<endl;
}
else{
MYSQL_RES* res; 
res= mysql_store_result(conn);
if(res){
	MYSQL_ROW row = mysql_fetch_row(res);
if(row){
	total = atoi(row[0]);
}
mysql_free_result(res);
}
}

if(total > 0){
	total--;
stringstream zs;
zs<<total;
string strT = zs.str();

string update= "UPDATE room SET Bed = '"+strT+"' WHERE Name='"+r.getName()+"' ";
if(mysql_query(conn,update.c_str())){
	cout<<"Error: "<<mysql_error(conn)<<endl;
}
else{
	cout<<endl;
cout<<"Bed is Reserved Successfuly in "<<r.getName()<< " room For Student "<<n<<endl;
cout<<"Please Pay "<<r.getPrice()<<" Dollars."<<endl;
}
}
else if(total ==0){
	cout<<endl;
	cout<<"Sorry! No Bed Available"<<endl;
}
usleep(80000);

}


int main() {
	
	University u;
	Room r;
	
MYSQL* conn;
conn = mysql_init(NULL);

if(!mysql_real_connect(conn,HOST,USER,PW,DB,3306,NULL,0)){
	cout<<"Error: "<<mysql_error(conn)<<endl;
}
else{
	cout<<"Logged in!"<<endl;
}
usleep(30000);

bool exit = false;

while(!exit){
	system("cls");
	int val;
	cout<<"Welcome to University Management System"<<endl;
	cout<<"***************************************"<<endl;
	cout<<"1. Insert Student Data"<<endl;
	cout<<"2. Show Student Data"<<endl;
	cout<<"3. Search Student Data"<<endl;
 	cout<<"4. Update Student Data"<<endl;
 	cout<<"5. Delete Student Data"<<endl;
	cout<<"6. Register Student Room"<<endl;

 	cout<<"0. Exit"<<endl;
 	cout<<"Enter choice: ";
 	cin>>val;
 	
 	cout<<endl;
 	
 	if(val==1){
 	insertS(conn,u);	
	 }
	 
	else if(val==2){
	showRecord(conn);	
	}
	
	else if(val==3){
	searchS(conn);	
	}
	
	else if(val==4){
	updateS(conn,u);	
	}
	
	else if(val==5){
	deleteS(conn);	
	}

	else if (val==6) {
			

		roomRegister(conn, insertroom(conn, r));
	}
	
	else if(val==0){
		exit = true;
		cout<<"Good Luck!"<<endl;
		usleep(30000);
	}
	else{
		cout<<"Invalid Input"<<endl;
		usleep(3000);
	}
}

    return 0;
}

