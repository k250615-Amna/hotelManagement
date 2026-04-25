#include <iostream>
using namespace std;

//Hotel management system
//1.Person, 2.guest, 3. Employee, 4. Manager, 4. Room, 5.Booking, 
//  6. Payment, 7.CashPayment, 8.CardPayment, 9.OnlinePayment

class AUsers{
	public:
		virtual void displayDetails() const = 0;
		virtual string getRole() const = 0;
		virtual bool login(string Email, string pass) const = 0;
		virtual bool logOut() = 0;
};

class Person : public AUsers{
	protected:
		string name;
		string number;
		string email;
		int id;
		string password;
		
	public:
		Person(){
			name = "";
			number = "";
			email = "@gmail.com";
			id = 0;
			password ="";
		}
		Person(string n,string no,string e,int ID, string passKey) : name(n),number(no), email(e), id(ID), password(passKey){}
		
		void displayDetails() const override  {
			cout<<"Name: "<<name<<endl;
			cout<<"Number: "<<number<<endl;
			cout<<"Email: "<<email<<endl;
			cout<<"ID: "<<id<<endl;
		}
		
		void setContact(string Email, string num){
			number = num;
			email = Email;
		}
		
		virtual string getRole() const = 0;
		
		bool login(string Email , string pass)const override {
			return(email == Email && pass == password);
		}
		bool logOut() override {
			cout<<"Log out successfull"<<endl;
			return true;
		}
		
		
};

class Guest : public Person{
	protected:
		bool isVip;
		int bookingCount;
		string address;
		string nationality;
		
	public:
		Guest(): isVip(false), bookingCount(0), address(""), nationality("") {}
		Guest(string n, string no, string e, int ID, string pass, string add, string nation):Person(n,no,e,ID,pass), isVip(false), bookingCount(0),address(add), nationality(nation){}
		
		string getRole()const override {
			return "Guest";
		}
		
		bool login(string Email, string pass)const override {
			return(email==email && password==pass);
		}
		bool logOut(){
			cout<<"Logged out"<<endl;
			return true;
		}
		
		void displayDetails(){
			Person::displayDetails();
			cout<<"Address: "<<address;
			cout<<"Total number of bookings: "<<bookingCount<<endl;
			cout<<"Nationality: "<<nationality<<endl;
			if(isVip){
				cout<<"Guest is listed as a VIP"<<endl;
			}else{
				cout<<"Guest is not listed as a VIP"<<endl;
			}
		}
		
		void addBooking(){
			bookingCount++;
		}
		
		bool getVIPStatus(){
			if(bookingCount>5){
				cout<<"Discount applicable"<<endl;
				return true;
			}else{
				return false;
			}
		}
		
		void cancelBooking(){
			if(bookingCount>0){
				bookingCount--;
			}else{
				cout<<"You have no prior bookings to cancel"<<endl;
			}
		}
		
		int getBookingCount(){
			return bookingCount;
		}

};

class Employee :  public Person{
	protected:
		string department;
		double salary;
		string shift; //time
		int hoursWorked;  //in a week
		double bonus;
		
	public:
		Employee() : department(""), salary(0), shift(""), hoursWorked(0), bonus(0) {}
		
        Employee(string n, string no, string e, int ID, string p, string d, double s, string sh) : Person(n, no, e, ID, p),
        department(d), salary(s), shift(sh), hoursWorked(0), bonus(2) {}
        
        string getRole() const override {
        	return "Employee";
		}
		
		void displayDetails(){
			Person::displayDetails();
			cout<<"Department: "<<department<<endl;
			cout<<"Salary: "<<salary<<endl;
			cout<<"Shift: "<<shift<<endl;
			cout<<"Hours worked: "<<hoursWorked<<endl;
			cout<<"Bonus: "<<bonus<<endl;
		}
		
		double calculatePay(){
			return (bonus * hoursWorked) + salary; 
		}
		
		void updatesalary(double NewSalary){
			salary = NewSalary;
		}
	
};

class Room{
	private:
		int roomNumber;
		string type;   //single, double, suite
		double pricePerNight;
		bool isAvailable;
		
	public:
		
		Room() {}

        Room(int num, string t, double price) : roomNumber(num), type(t), pricePerNight(price), isAvailable(true) {}
        
        int getRoomNumber()  {
        	return roomNumber;
		}
		double getPrice() const {
			return pricePerNight;
		}
		bool getAvailability(){
			return isAvailable;
		}
		string getType(){
			return type;
		}
		
		bool bookRoom(){
			if(isAvailable){
				cout<<"Room can be booked"<<endl;
				isAvailable = false;
			}else{
				cout<<"Room is already booked"<<endl;
			}
		}
		
		void displayroom () const {
			cout<<"---Room Details---"<<endl;
			cout<<"Room number: "<<roomNumber<<endl;
			cout<<"Type: "<<type<<endl;
			cout<<"Price per night: "<<pricePerNight<<endl;
			if(isAvailable){
				cout<<"The room is available"<<endl;
			}else{
				cout<<"Room is already booked"<<endl;
			}
		}

};

class Booking{
	private:
		int bookingID;
		Guest *guest;
		Room room;
		int days;
		
	public:
		Booking() {}

        Booking(int id, Guest* g, Room r, int d) : bookingID(id), guest(g), room(r), days(d) {}
        
        double calculateBill() const {
        	double total = days * room.getPrice();
        	
        	if(guest->getVIPStatus()){
        		total = total * 0.8;   //20% discount
			}
        	guest->addBooking();
        	
        	return total;
		}
		
		void displayBooking() const{
			cout<<"Booking ID: "<<bookingID<<endl;
			cout<<"Guest details: "<<endl;
			guest->displayDetails();
			
			cout<<"Room Details: "<<endl;
			room.displayroom();
			cout<<"Bill: "<<calculateBill()<<endl;
		}
		
		Guest *getGuest(){
			return guest;
		}
		Room getRoom() const {
			return room;
		}

};

class Payment{
	protected:
		int paymentID;
		double amount;
		string status;
		
	public:
		
		 Payment(int id, double amt) : paymentID(id), amount(amt), status("Pending") {}

         virtual void processPayment() = 0;
         
         virtual void displayPayment() const = 0;
         
};

class Manager : public Employee{
	private:
		int accessLevel;
		
	public:
		Manager(): Employee(), accessLevel(0){}
		
		Manager(string n, string no, string e, int ID, string p, string d, double s, string sh, int al) : Employee(n, no, e, ID, p, d, s, sh), accessLevel(al) {}
		
		string getRole() const override {
			return "Manager";
		}
		
		void displayDetails(){
			Employee::displayDetails();
			cout<<"Access level: "<<accessLevel<<endl;
		}
		
		void setAccessLevel(int acc){
			accessLevel = acc;
		}
		
		
};

int main(){
	
	
	
	
	return 0;
}
