#include<fstream> // for file
#include<conio.h>
#include<string.h> // for string
#include<iostream>
#include <thread>
#include<bits/stdc++.h>
using namespace std;





class product
{
	int product_number; //variable part
	char product_name[50];
	float product_price,product_quantity,tax,product_discount;
    char date[10];

	public:

	void create_product()  // ADD PRODUCT
	{
		cout<<endl<<"Please Enter The Product Number: ";
		cin>>product_number;
		cout<<endl<<"Please Enter The Name of The Product: ";
		cin.ignore();
		cin.getline(product_name ,50);
		cout<<endl<<"Please Enter The Price of The Product: ";
		cin>>product_price;
		cout<<endl<<"Please Enter The Discount (%): ";
		cin>>product_discount;
		cin.ignore();
		cout<<endl<<"Please Enter The Date : ";
		cin>>date;
		cin.ignore();
		cout<<endl<<"Please Enter The Quantity : ";
		cin>>product_quantity;
		cin.ignore();



	}


	void show_product() // DISPLAY KORBE
	{
	    cout<<endl<<"Date : "<<date;
		cout<<endl<<"Product #: "<<product_number;
		cout<<endl<<"Product Name: "<<product_name;
		cout<<endl<<"Product Price: "<<product_price;
		cout<<endl<<"Discount : "<<product_discount<<" %";
		cout<<endl<<"Quantity : "<<product_quantity;


	}

	int getProduct() // PRODUCT WILL BE RETURN FROM THE FUNCTION
	{
		return product_number;
	}

	float getPrice()
	{
		return product_price;
	}

	char* getName()
	{
		return product_name;
	}

	float getDiscount()
	{
		return product_discount;
	}
	string getdate()
	{
	    return date;
	}
	int getquntity()
	{
		return product_quantity;
	}


};



fstream fp;
product produc;


void save_product()
{
	fp.open("database.dat",ios::out|ios::app);
	produc.create_product();
	fp.write((char*)&produc,sizeof(product));
	fp.close();
	cout<<endl<<endl<<"The Product Has Been Sucessfully Created...";
	getchar();

}


void show_all_product() // DISPLAY PRODUCT
{
	system("cls");
	cout<<endl<<"\t===========================================\n";
	cout<<endl<<"\t\tRECORDS.";
	cout<<endl<<"\t===========================================\n";
	fp.open("database.dat",ios::in);
	while(fp.read((char*)&produc,sizeof(product)))
	{
		produc.show_product();
		cout<<endl<<"\t===========================================\n"<<endl;
		getchar();
	}
	fp.close();
}
void searchbydate()
{
     string date;

				cout<<"\n\n\tPlease Enter The Product date: ";
				cin>>date;
	bool found=false;
	fp.open("database.dat",ios::in);
	while(fp.read((char*)&produc,sizeof(product)))
	{
		if(produc.getdate()==date)
		{
			system("cls");
			produc.show_product();
			found=true;
		}
	}
	cout<<"\n\n press enter to continue..";

	fp.close();
	if(found != true)
	cout<<"\n\nNo record found";
	getchar();

}
void searchbynumber()
{
    int num;

				cout<<"\n\n\tPlease Enter The Product number: ";
				cin>>num;
	bool found=false;
	fp.open("database.dat",ios::in);
	while(fp.read((char*)&produc,sizeof(product)))
	{
		if(produc.getProduct()==num)
		{
			system("cls");
			produc.show_product();
			found=true;
		}
	}
	cout<<"\n\n press enter to continue..";

	fp.close();
	if(found != true)
	cout<<"\n\nNo record found";
	getchar();
}
void searchbyname()
{
   string name;

				cout<<"\n\n\tPlease Enter The Product name: ";
				cin>>name;
	bool found=false;
	fp.open("database.dat",ios::in);
	while(fp.read((char*)&produc,sizeof(product)))
	{
		if(produc.getName()==name)
		{
			system("cls");
			produc.show_product();
			found=true;
		}
	}
	cout<<"\n\n press enter to continue..";

	fp.close();
	if(found != true)
	cout<<"\n\nNo record found";
	getchar();
}

void display_record()//search product
{
      int option;
    cout<<"\t===========================================\n";
		cout<<"\n\t1. Search by date : ";
		cout<<"\n\t2. Search by number :";
        cout<<"\n\t3. Search by name :\n";
		cout<<"\t===========================================\n";

		cout<<"\n\tOption: ";
		cin>>option;

		switch(option)
		{
			case 1: searchbydate();
					break;

			case 2: searchbynumber();
					break;
			case 3: searchbyname();
			        break;



			default :cout<<"Invalid Input...\n";
		}



}



void edit_product() // MODIFY PRODUCT
{
	int num;
	bool found=false;
	system("cls");
	cout<<endl<<endl<<"\tPlease Enter The Product #: ";
	cin>>num;

	fp.open("database.dat",ios::in|ios::out);
	while(fp.read((char*)&produc,sizeof(product)) && found==false)
	{
		if(produc.getProduct()==num)
		{
			produc.show_product();
			cout<<"\nPlease Enter The New Details of Product: "<<endl;
			produc.create_product();
			long long pos=-1*sizeof(produc);
			fp.seekp(pos,ios::cur);
			fp.write((char*)&produc,sizeof(product));
			cout<<endl<<endl<<"\t Record Successfully Updated...";
			found=true;
		}
	}
	fp.close();
	if(found==false)
		cout<<endl<<endl<<"Record Not Found...";
	getchar();
}


void delete_product() // DELETE PRODUCT
{
	int num;
	system("cls");
	cout<<endl<<endl<<"Please Enter The product #: ";
	cin>>num;
	fp.open("database.dat",ios::in|ios::out);
	fstream fp2;
	fp2.open("Temp.dat",ios::out);
	fp.seekg(0,ios::beg);
	while(fp.read((char*)&produc,sizeof(product)))
	{
		if(produc.getProduct()!=num)
		{
			fp2.write((char*)&produc,sizeof(product));
		}
	}
	fp2.close();
	fp.close();
	remove("database.dat");
	rename("Temp.dat","database.dat");
	cout<<endl<<endl<<"\tRecord Deleted...";
	getchar();
}


void product_menu() //BUY PRODUCT ER FUCTION PRODUCT SHOW KORBE THEN BUY KORBE
{
	system("cls");
	fp.open("database.dat",ios::in);

	cout<<endl<<endl<<"\t\tProduct MENU\n\n";
	cout<<"\t===========================================\n";
	cout<<"P.NO.\t\tNAME\t\tPRICE\t\tQuantity\t\n";
	cout<<"\t===========================================\n";
	while(fp.read((char*)&produc,sizeof(product)))
	{
		cout<<produc.getProduct()<<"\t\t"<<produc.getName()<<"\t\t"<<produc.getPrice()<<"\t\t"<<produc.getquntity()<< endl;
	}
	fp.close();
}



void place_order() // PRODUCT SHOW KORAR POR BUY HOBE ....
{
	int order_arr[50],quan[50],c=0;
	float amt,damt,total=0;
	char ch='Y';
	product_menu();
	cout<<"\n=================================================";
	cout<<"\n PLACE YOUR ORDER";
	cout<<"\n-------------------------------------------------\n";
	do{
		cout<<"\n\nEnter The Product #: ";
		cin>>order_arr[c];
		cout<<"\nQuantity: ";
		cin>>quan[c];
		c++;
		cout<<"\nDo You Want To Order Another Product ? (y/n)";
		cin>>ch;
		}while(ch=='y' ||ch=='Y');
	cout<<"\n\nThank You...";
	getchar();
	system("cls");
	cout<<"\n\n********************************INVOICE************************\n";
	cout<<"\nPr No.\tPr Name\tQuantity \tPrice \tAmount \tAmount after discount\n";
	for(int x=0;x<=c;x++)
	{
		fp.open("database.dat",ios::in);
		fp.read((char*)&produc,sizeof(product));
		while(!fp.eof())
		{
			if(produc.getProduct()==order_arr[x])
			{
				amt=produc.getPrice()*quan[x];
				damt=amt-(amt*produc.getDiscount()/100);
				cout<<"\n"<<order_arr[x]<<"\t"<<produc.getName()<<"\t"<<quan[x]<<"\t\t"<<produc.getPrice()<<"\t"<<amt<<"\t\t"<<damt;
				total+=damt;
			}
			fp.read((char*)&produc,sizeof(product));
		}
		fp.close();
	}
	cout<<"\n\n\t\t\t\t\tTOTAL = "<<total;
	cout<<"\n\n\n\n press any key to continue : ";
	getchar();
}



void admin_menu() // MENU SOB FUNCTION ER
{
	system("cls");
	int option;
	cout<<"\t==============MAIN MENU=====================\n";
	cout<<"\n\tPress 1 to CREATE PRODUCT";
	cout<<"\n\tPress 2 to DISPLAY ALL PRODUCTS";
	cout<<"\n\tPress 3 to SEARCH PRODUCT ";
	cout<<"\n\tPress 4 to MODIFY PRODUCT";
	cout<<"\n\tPress 5 to DELETE PRODUCT";
	cout<<"\n\tPress 6 to BUY A PRODUCT";
	cout<<"\n\tPress 7 to EXIT \n";
	cout<<"\t===========================================\n";

	cout<<"\n\n\tOption: ";
	cin>>option;
	switch(option)
	{
		case 1: system("cls");
				save_product();

				break;

		case 2: show_all_product();
				break;

		case 3:
				system("cls");
				display_record();
				break;

		case 4: edit_product();
		break;

		case 5: delete_product();
		        break;

		case 6: place_order();
				break;
        case 7:
					cout<<"\t===========================================\n";
					cout<<"\n\tGood Bye!";
					cout<<"\t===========================================\n";
					exit(0);

		default:admin_menu();
	}
}

class User{
public:
    string firstName;
    string lastName;
    string username;
    string password;


void registerUser() {

    cout << "Enter first name: ";
    cin >> firstName;
    cout << "Enter last name: ";
    cin >> lastName;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;



    ofstream file("users.txt", ios_base::app);
    file << firstName << " " << lastName << " " <<username << " " << password << endl;
    file.close();
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\tUser registered successfully, Please login.." << endl;
    cout<<endl;
    User logic;
}

bool authenticateUser(string username, string password) {
    ifstream file("users.txt");
    string savedFirstName, savedLastName, savedUsername, savedPassword;
    while (file >> savedFirstName >> savedLastName >> savedUsername >> savedPassword) {
        if (username == savedUsername && password == savedPassword) {
            cout << "Welcome " << savedFirstName << " " << savedLastName << "!" << endl;
            admin_menu();
            return true;
        }

    }
    cout<<"Invalid user name or password";

    User();


}

void resetPassword() {
    string username, newPassword;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter new password: ";
    cin >> newPassword;
    ifstream fileIn("users.txt");
    ofstream fileOut("temp.txt");
    string savedFirstName, savedLastName, savedUsername, savedPassword;
    bool foundUser = false;
    while (fileIn >> savedFirstName >> savedLastName >> savedUsername >> savedPassword) {
        if (username == savedUsername) {
            fileOut << savedFirstName << " " << savedLastName << " " << savedUsername << " " << newPassword << endl;
            cout << "Password reset successful." << endl;
            foundUser = true;
        } else {
            fileOut << savedFirstName << " " << savedLastName << " " << savedUsername << " " << savedPassword << endl;
        }
    }
    fileIn.close();
    fileOut.close();
    remove("users.txt");
    rename("temp.txt", "users.txt");
    if (!foundUser) {
        cout << "User not found." << endl;
    }
}

User(){
int choice;
    cout<<endl;
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tWelcome to the Login System\n\n" << endl;
    cout << "\t\t\t1. Register" << endl;
    cout << "\t\t\t2. Login" << endl;
    cout << "\t\t\t3. Reset password" << endl;
    cout<<endl;
    cout << "Enter your choice: ";
    cin >> choice;
    cout<<endl;
    switch (choice) {
        case 1:
            registerUser();
            break;
        case 2:
            {
                string username, password;
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;
               authenticateUser(username, password);
            }
            break;
        case 3:
            resetPassword();
            break;
        default:
            cout << "Invalid choice." << endl;
            User();
            break;
    }


}
};

int main(int argc, char *argv[])
{
	system("cls");
	system("color cf");
	const string loading_frames[] = {
	    "\t\t\t\t\n\n\n\n\n",
        "\t\t\t\tLOADING..[=>                                       ]",
        "\t\t\t\tLOADING..[==>                                      ]",
        "\t\t\t\tLOADING..[===>                                     ]",
        "\t\t\t\tLOADING..[====>                                    ]",
        "\t\t\t\tLOADING..[ =====>                                  ]",
        "\t\t\t\tLOADING..[  ======>                                ]",
        "\t\t\t\tLOADING..[   ======>                               ]",
        "\t\t\t\tLOADING..[    ======>                              ]",
        "\t\t\t\tLOADING..[     =======>                            ]",
        "\t\t\t\tLOADING..[       ========>                         ]",
        "\t\t\t\tLOADING..[       ==============>                   ]",
        "\t\t\t\tLOADING..[        ====================>            ]",
        "\t\t\t\tLOADING..[========================================>]",
        "\t\t\t\t\n\n\n\n\n",

    };
    const int num_frames = sizeof(loading_frames) / sizeof(loading_frames[0]);
    const int frame_delay_ms = 100;
    const int console_width = 80;



    for (int i = 0; i < num_frames; i++) {
        cout << loading_frames[i] << "\r" << flush;
        this_thread::sleep_for(chrono::milliseconds(frame_delay_ms));
    }

    string message = "\t\t\tLoading successful";
    int message_length = message.length();
    int padding_length = (console_width - message_length) / 2;

    cout << string(padding_length, ' ') << message << endl;
    cout<<"\n\n\tpress any one key and enter : ";

    char op;
	cin>>op;
	switch(op)
	{

default:

		User();
		break;
	}

	int option;

	for(;;) // PROTITA FUNCTION ER KAJ SESH E SHOW KORE MAIN MENU TE NIYE JAWAR JONNO BA PRODUCT BUY KORAR JONNO BA EXIT ER JONNO
	{

		cout<<"\t===========================================\n";
		cout<<"\n\t1. BUY PRODUCT ";
		cout<<"\n\t2. GO TO MAIN MENU ";
		cout<<"\n\t3. EXIT\n";
		cout<<"\t===========================================\n";

		cout<<"\n\tOption: ";
		cin>>option;

		switch(option)
		{
			case 1: system("cls");
					place_order();//buy product
					getchar();
					break;

			case 2: admin_menu();
					break;

			case 3:
					cout<<"\t===========================================\n";
					cout<<"\n\tGood Bye!";
					cout<<"\t===========================================\n";
					exit(0);

			default :cout<<"Invalid Input...\n";
		}

	}
return 0;
}

