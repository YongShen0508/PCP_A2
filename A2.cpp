#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cmath>
#include <cctype>
#include <iomanip>
#include <Windows.h>
#include <string>
#include <time.h>

using namespace std;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);


//function declaration
string upper(string);
void Main_Menu(string);
void CinemaManagement(int);
void AdministratorMenu(int);
//Customer Feedback (for user)
void CustomerFeedback();
void SearchFeedback(); //by rating
void WriteFeedback();
void ViewFeedback();
void OpenCustomerFeedback(int&, double&);
//open member info files
void OpenMemberDetails(int&);
void OpenPurchaseHistory();
//Membership Details
void MembershipDetails();
void UserLogIn();
void UserRegister();
void WriteMemberDetails(int&);

void MovieManagement(int);
void CinemaHallManagement(int);

//fnb management
void inventoryMenu(int); //menu with available stock 
void addFB(); //function to add new fnb 
void deleteFB(int); //function to delete existing fnb
void inventoryFB(int); //function to add stock or delete stock
void FBManagement(); //add new item, delete item, add and reduce stock
//purchase fnb
void purchaseFB(); //function to purchase fnb

void ReadFBRecord(int&); //read txt file
void LoadFBRecord(int&); //update txt file
//structure declaration
struct mapping_seats
{
	int hall;
	int data;
	int row[50];
	int column[50];
}unavailable[50];
struct MemberDetails
{
	string Details_user, Details_name, Details_password, Details_join, Details_phone, Details_email, Details_status, Details_point;
}Member[100];
struct PurchaseHistory
{
	string Purchase_user, Purchase_name, Purchase_movie[5], Purchase_date[5], Purchase_pax[5], Purchase_food[5];
}Purchase[100];
struct Feedback
{
    int rating;
    string comment;
}feedback[100];

struct foodAndBeverage {
	string foodcode;
	string foodname;
	double regular_price;
	double large_price;
	int stock;
}FNB[100];

//Main Menu
int main()
{
	system("chcp 65001");
	bool decision = true;
	do{
		string selection;
		system("cls");
		Main_Menu("MAIN");
		cout << "\t\t\tPlease input your selection >>> ";
		getline(cin,selection);
		if (selection == "1")//Movie details
			MovieDetails(1);
		else if (selection == "2")//f&b
			cout << "HELLO" << endl;
		else if(selection=="3")//purchase now
			PurchaseNow(3);
		else if(selection=="4")//membership details
			cout << "HELLO" << endl;
		else if(selection=="5")
			AdministratorMenu(5);
		else if(selection=="7")//exit
			decision = false;
		else
			cout << "\t\t\tInvalid input found" << endl;
		cin.clear();
	} while (decision);


	system("pause");
	return 0;
}

//change string to uppercase
string upper(string uppercase)
{
	for (int i = 0; i < uppercase.size(); i++)
		uppercase[i] = toupper(uppercase[i]);
	return uppercase;
}

//CustomerFeedback
void SearchFeedback()
{
    system("cls");
    int nocomment = 0, rating, j = 0, found = 0;
    double averagerating = 0;
    OpenCustomerFeedback(nocomment, averagerating);
    cout << "Enter rating to sort comment (1-5): ";
    cin >> rating;
    cout << endl << endl;
    if (rating > 0 && rating < 6)
    {
        cout << "\t**************************************************************************" << endl << endl;
        for (int i = 0; i < nocomment; i++)
        {
            if (rating == feedback[i].rating)
            {
                found = i;
                cout << "\t\t\t" << ++j << ". Rating: " << feedback[i].rating << endl;
                cout << "\t\t\tComment: " << feedback[i].comment << endl << endl;
                cout << "\t**************************************************************************" << endl << endl;
            }
        }

        if (!(rating == feedback[found].rating))
        {
            cout << "\t\t\tNo comment with rating of " << rating << ". " << endl << endl;
            cout << "\t**************************************************************************" << endl << endl;
        }
    }
    else
        cout << "Invalid input! " << endl;
    system("PAUSE");
}
void OpenCustomerFeedback(int& nocomment, double& averagerating)
{
    ifstream CusFeedback;
    int i = 0, totalrating = 0;

    CusFeedback.open("CustomerFeedback.txt");
    if (CusFeedback.is_open())
    {
        while (!CusFeedback.eof())
        {
            CusFeedback >> feedback[i].rating;
            CusFeedback.ignore();
            getline(CusFeedback, feedback[i].comment);
            i++;
            nocomment = i;
        }
    }
    else
        cout << "Please contact admin for further assistance..." << endl;
    for (int i = 0; i < nocomment; i++)
    {
        totalrating += feedback[i].rating;
    }
    averagerating = double(totalrating) / nocomment;
    CusFeedback.close();
}
void ViewFeedback()
{
    system("cls");
    int nocomment = 0, j = 0, totalrating = 0;
    double averagerating = 0;
    OpenCustomerFeedback(nocomment, averagerating);
    cout << "Total comment: " << nocomment << endl;
    cout << "Average rating: " << fixed << setprecision(1) << averagerating << endl << endl;
    cout << "\t**************************************************************************" << endl << endl;
    for (int i = 0; i < nocomment; i++)
    {
        cout << "\t\t\t" << ++j << ". Rating: " << feedback[i].rating << endl;
        cout << "\t\t\tComment: " << feedback[i].comment << endl << endl;
        cout << "\t**************************************************************************" << endl << endl;
    }
    system("PAUSE");
}
void WriteFeedback()
{
    system("cls");
    char Continue = 'y';
    int i = 0;
    ofstream cusfeedback;
    cusfeedback.open("CustomerFeedback.txt", ios::app);

    cout << "Good day! \nThis comment is anonymous. \nPlease feel free to leave your thoughts. \n";

    cout << "\t\t\tPlease rate our cinema (1-5)" << endl << "\t\t\t";
    cin >> feedback[i].rating;
    cusfeedback << endl << feedback[i].rating << endl;
    cout << "\t\t\tPlease leave your feedback here. (in 100 words) " << endl << "\t\t\t";
    cin.ignore();
    getline(cin, feedback[i].comment);
    cusfeedback << feedback[i].comment;
    cout << endl << "\t\t\tThank you. " << endl;
    system("PAUSE");
    cusfeedback.close();
}
void CustomerFeedback()
{
	system("cls");
	int selection;
	bool decision = true;
	do
	{
		system("cls");
		cout << "<1> Leave comment " << endl;
		cout << "<2> View comment " << endl;
        	cout << "<3> Search comment " << endl;
		cout << "<4> Exit " << endl;
		cout << "\t\t\tPlease input your selection >>> ";
		cin >> selection;
		switch (selection)
		{
		case(1)://allow customer to leave feedback (anonymous)
		{
			WriteFeedback();
			break;
		}
		case(2)://to view others feedback
		{
			ViewFeedback();
			break;
		}
        	case(3)://search particular feedback using rating
        	{
            	SearchFeedback();
            	break;
        	}
		case(4)://exit
		{
			decision = false;
			break;
		}
		default://reinput
		{
			cout << "\t\t\tInvalid input found" << endl;
			break;
		}
		}
	} while (decision);
}
//Administrator Menu (havent implement employee function)
void AdministratorMenu(int option)
{
	//login menu
	bool decision = true, access = true;
	do{
		cin.clear();
		system("cls");
		ReadTextRecord(0);
		cout << "\n\n" << endl;
		for (int i = 0; i < 7; i++)
		{
			cout << "\t\t\t\t\t\t\t\t" << text[14][i] << endl;
		}
		cout << "\n\n\t\t\t" << string(150, char(95)) << endl;
		cout << "\n\t\t\t\tDear Admin, kindly key in your Admin ID and password" << endl;
		cout << "\n\t\t\t" << string(150, char(95)) << endl;
		string id,pass_word;
		int record = 0,password=0, found = 0,number=0;
		ReadEmployeeRecord(record);
		cout << "\n\n\t\t\t\tID=ew001 and password=12345 for lecturer used only!!" << endl;
		cout << "\n\t\t\t\t\tADMIN ID <E>xit >>>";
		getline(cin, id);
		id = upper(id);
		if (id == "E")
		{
			decision = false;
			break;
		}
		cout << "\t\t\t\t\tPassword >>>";
		getline(cin, pass_word);
		for (int i = 0; i < pass_word.size(); i++)	//ensure pass_word only in numeric numbers
		{
			if (isdigit(pass_word[i]))
				number++;
		}
		if (pass_word.size() == number)		//comparing
			password = stoi(pass_word);	//string to integer
		if (id.length() == 5)
		{
			for (int i = 0; i < record; i++)	//checking corrent password
			{
				if (password == employee[i].password && id == employee[i].id)
				{
					found++;
				}
			}
		}
		if (found == 0 || id.length() != 5)
		{
			cout << "\t\t\tPlease reinput your id and password " << endl;
			Sleep(1000);
		}
		else if (found == 1)
			access = false;
	} while (access);
	while(decision)
	{
		system("cls");
		ReadTextRecord(0);
		for (int i = 0; i < 7; i++)
		{
			cout << "\t\t\t" << text[1][i] << endl;
		}
		string selection;
		cout << "\n\n\n" << endl;
		cout << "\t\t\t<1> Cinema Refreshing" << endl;
		cout << "\t\t\t<2> Cinema management" << endl;
		cout << "\t\t\t<3> Food & Beverages management" << endl;
		cout << "\t\t\t<4> Membership Management" << endl;
		cout << "\t\t\t<5> Employee management" << endl;
		cout << "\t\t\t<6> Exit " << endl;
		cout << "\t\t\tPlease input your selection >>> ";
		getline(cin, selection);
		if (selection == "1")
			CinemaRefresh(1);
		if (selection == "2")//Cinema management
			CinemaManagement(2);
		if (selection == "3")//F&B management
			FBManagement();
		if (selection == "4")//Membership managements
			cout << "hello" << endl;
		if (selection == "5")//Employee management
			EmployeeManagement(5);
		if (selection == "6")
			decision = false;
		else//reinput
			cout << "\t\t\tInvalid input found" << endl;
	} 
}
//Cinema Management
void CinemaManagement(int option)
{
	cin.clear();
	string selection;
	bool decision = true;
	do
	{	
		system("cls");
		cout << "\n\n\n\t\t\t<1> Movies management " << endl;
		cout << "\t\t\t<2> Cinema Hall management " << endl;
		cout << "\t\t\t<3> Exit " << endl;
		cout << "\t\t\tPlease input your selection >>> ";
		getline(cin, selection);
		if(selection=="1")//Movie management
			MovieManagement(1);
		if(selection=="2")//Cinema Hall Modification
			CinemaHallManagement(2);
		if(selection=="3")//exit
			decision = false;
		else//reinput
			cout << "\t\t\tInvalid input found" << endl;
	} while (decision);
}
//Cinema Hall Management
void CinemaHallManagement(int option)
{
	int selection;
	bool decision = true;
	do
	{
		system("cls");
		int record = 0;
		bool result = false;
		ReadCinemaHallRecord(record);
		cout << "\n\n\n" << string(100, char(61)) << "\n\n\n";
		for (int w = 0; w < record; w++)
		{
			cout << "\n\n\t\t\t\t HALL " << unavailable[w].hall << "\n\n";
			CinemaSeatPrinting(w);
		}

		cout << string(100, char(61)) << "\n\n\n";
		cout << "\t\t\t<1> Add Cinema Hall" << endl;
		cout << "\t\t\t<2> Modify Cinema Hall space" << endl;
		cout << "\t\t\t<3> Delete Cinema Hall" << endl;
		cout << "\t\t\t<4> Exit" << endl;
		cout << "\t\t\tInput your selection >>> ";
		cin >> selection;

		switch (selection)
		{
		case(1)://Add cinema Hall
		{
			result = AddCinemaHall(result);
			if (result)
			{
				record++;
				unavailable[record - 1].hall = record;
				unavailable[record - 1].data = 0;
				unavailable[record - 1].row[0] = 0;
				unavailable[record - 1].column[0] = 0;
				LoadCinemaHallRecord(record);
			}
			break;
		}
		case(2)://Modify Cinema Seat
		{
			ModifyCinemaHall(record);
			break;
		}
		case(3)://Delete Cinema Hall
		{
			DeleteCinemaHall(record);
			break;
		}
		case(4)://exit
		{
			decision = false;
			break;
		}
		default://reinput
		{
			cout << "\t\t\tInvalid input found" << endl;
			break;
		}
		}
	} while (decision);
}
//Open member info files
void OpenPurchaseHistory()
{
	ifstream Ad_purchase;
	int k = 0;

	Ad_purchase.open("Admin_purchase.txt");
	if (Ad_purchase.is_open())
	{
		while (!Ad_purchase.eof())
		{
			getline(Ad_purchase, Purchase[k].Purchase_user);
			getline(Ad_purchase, Purchase[k].Purchase_name);

			for (int i = 0; i < 5; i++)
			{
				getline(Ad_purchase, Purchase[k].Purchase_date[i]);
				getline(Ad_purchase, Purchase[k].Purchase_pax[i]);
				getline(Ad_purchase, Purchase[k].Purchase_movie[i]);
				getline(Ad_purchase, Purchase[k].Purchase_food[i]);
			}
			k++;
		}
	}
	else
		cout << "Please contact admin for further assistance..." << endl;
	Ad_purchase.close();
}
void OpenMemberDetails(int& nomember)
{
	int i = 0;
	ifstream Ad_memberlist;
	Ad_memberlist.open("Admin_memberlist.txt");
	if (Ad_memberlist.is_open())
	{
		while (!Ad_memberlist.eof())
		{
			getline(Ad_memberlist, Member[i].Details_user);
			getline(Ad_memberlist, Member[i].Details_password);
			getline(Ad_memberlist, Member[i].Details_name);
			getline(Ad_memberlist, Member[i].Details_status);
			getline(Ad_memberlist, Member[i].Details_join);
			getline(Ad_memberlist, Member[i].Details_point);
			getline(Ad_memberlist, Member[i].Details_phone);
			getline(Ad_memberlist, Member[i].Details_email);
			i++;
			nomember = i;
		}
	}
	else
		cout << "Please contact admin for further assistance..." << endl;
	Ad_memberlist.close();
}
//Membership Details (for user)
void UserRegister()
{
	ofstream Add_member, Add_purchase;
	int i = 0, newmember = 0, existing = 0, nomember = 0;
	string username, password;

	system("cls");
	cout << "Good day!\nWelcome to be part of us!\n\n";
	cout << "\t\t\tKindly fill in the below information. \n";
	cout << "\t\t\t*Compulsory\n\n";
	cout << "\t\t\t*Username: ";
	cin.ignore();
	getline(cin, username);

	OpenMemberDetails(nomember);

	for (int i = 0; i < nomember; i++)
	{
		if (!(upper(username) == upper(Member[i].Details_user)))
			newmember = i;
		else if (upper(username) == upper(Member[i].Details_user))
			existing = i;
	}

	if (!(upper(username) == upper(Member[existing].Details_user)))
	{
		Member[newmember].Details_user = username;
		cout << "\t\t\t*Full name as per NRIC: ";
		getline(cin, Member[newmember].Details_name);
		Member[newmember].Details_status = "Classic";
		cout << "\t\t\t*Password: ";
		getline(cin, Member[newmember].Details_password);
		cout << "\t\t\t*Register date (DD MM YYYY): ";
		getline(cin, Member[newmember].Details_join);
		Member[newmember].Details_point = "0";
		cout << "\t\t\t*Phone number: ";
		getline(cin, Member[newmember].Details_phone);
		cout << "\t\t\t*Email: ";
		getline(cin, Member[newmember].Details_email);
		cout << "\n\t\t\tCongratulations!\n\t\t\tYour registration was successful!\n\t\t\tKindly log in to access more.\n\t\t\tThank you ^^\n";
		system("PAUSE");
	}
	else if (upper(username) == upper(Member[existing].Details_user))
	{
		cout << "\t\t\tRegistered member!\n\t\t\tPlease log in to access your account.\n";
		system("PAUSE");
	}

	Add_member.open("Admin_memberlist.txt", ios::app);
	{
		Add_member << Member[newmember].Details_user << endl;;
		Add_member << Member[newmember].Details_password << endl;
		Add_member << Member[newmember].Details_name << endl;
		Add_member << Member[newmember].Details_status << endl;
		Add_member << Member[newmember].Details_join << endl;
		Add_member << Member[newmember].Details_point << endl;
		Add_member << Member[newmember].Details_phone << endl;
		Add_member << Member[newmember].Details_email << endl;
	}
	Add_member.close();

	Add_purchase.open("Admin_purchase.txt", ios::app);
	{
		Purchase[newmember].Purchase_user = Member[newmember].Details_user;
		Purchase[newmember].Purchase_name = Member[newmember].Details_name;
		Add_purchase << Purchase[newmember].Purchase_user << endl;
		Add_purchase << Purchase[newmember].Purchase_name << endl;
		for (int i = 0; i < 5; i++)
		{
			Add_purchase << "N/A" << endl;
			Add_purchase << "N/A" << endl;
			Add_purchase << "N/A" << endl;
			Add_purchase << "N/A" << endl;
		}
	}
	Add_purchase.close();
}

void UserLogIn()
{
	int selection, nomember = 0;
	bool decision = true;
	ifstream Ad_memberlist, Ad_purchase;
	int j = 0, i = 0, k = 0, found = 0;
	string username, password;
	system("cls");
	cout << "Good day! " << endl;
	cout << "Kindly log in for more access. " << endl << endl;

	cout << "\t\t\tPlease enter your username: ";
	cin >> username;

	OpenMemberDetails(nomember);
	for (int i = 0; i < nomember; i++)
	{
		if (upper(username) == upper(Member[i].Details_user))
			found = i;
	}
	OpenPurchaseHistory();
	if (upper(username) == upper(Member[found].Details_user))
	{
		cout << "\t\t\tPlease enter your password: ";
		cin >> password;
		if (password == Member[found].Details_password)
		{
			do {
				system("cls");
				cout << "Welcome back, our beloved member! " << endl;
				cout << "<1> Profile" << endl;
				cout << "<2> Purchase history" << endl;
				cout << "<3> Exit" << endl;

				cout << "\t\t\tPlease input your selection >>> ";
				cin >> selection;
				switch (selection) {
				case(1)://Check personal details
				{
					system("cls");
					cout << "\t**************************************************************************" << endl << endl;
					cout << "\t\t\tName: " << Member[found].Details_name << endl;
					cout << "\t\t\tStatus: " << Member[found].Details_status << endl;
					cout << "\t\t\tJoin date: " << Member[found].Details_join << endl;
					cout << "\t\t\tAccumulated point(s): " << Member[found].Details_point << endl;
					cout << "\t\t\tPhone number: " << Member[found].Details_phone << endl;
					cout << "\t\t\tEmail address: " << Member[found].Details_email << endl << endl;
					cout << "\t**************************************************************************" << endl << endl;
					system("PAUSE");
					break;
				}
				case(2)://Check purchase history
				{
					system("cls");
					cout << "\t**************************************************************************" << endl << endl;
					cout << "\t\t\tName: " << Purchase[found].Purchase_name << endl << endl;
					for (int i = 0; i < 5; i++)
					{
						cout << "\t\t\t" << i + 1 << ". Purchase Date: " << Purchase[found].Purchase_date[i] << endl;
						cout << "\t\t\tNumber of pax (Child Adult): " << Purchase[found].Purchase_pax[i] << endl;
						cout << "\t\t\tMovie: " << Purchase[found].Purchase_movie[i] << endl;
						cout << "\t\t\tF&B: " << Purchase[found].Purchase_food[i] << endl << endl;
					}
					cout << "\t**************************************************************************" << endl << endl;
					system("PAUSE");
					break;
				}
				case(3): //Exit
				{
					decision = false;
					break;
				}
				default://reinput
				{
					cout << "\t\t\tInvalid input found" << endl;
					break;
				}
				}
			} while (decision);
		}
		else
			cout << "\t\t\tInvalid password!\n\t\t\tPlease contact admin to reset password. " << endl;
	}
	else if (!(upper(username) == upper(Member[found].Details_user)))
		cout << "\t\t\tMember doesn't exist! \n";

	system("PAUSE");
}

void MembershipDetails()
{
	int selection;
	bool decision = true;
	system("cls");
	do {
		system("cls");
		cout << "<1> Log in" << endl;
		cout << "<2> Register" << endl;
		cout << "<3> Exit" << endl;

		cout << "\t\t\tPlease input your selection >>> ";
		cin >> selection;
		switch (selection)
		{
		case(1)://Existing member log in
		{
			UserLogIn();
			break;
		}
		case(2)://New member
		{
			UserRegister();
			break;
		}
		case(3): //Exit
		{
			decision = false;
			break;
		}
		default://reinput
		{
			cout << "\t\t\tInvalid input found" << endl;
			break;
		}
		}
	} while (decision);
}

void inventoryMenu(int option)
{
	int record = 0;
	ReadFBRecord(record);
	cout << "\t\t\t" << right << setw(55) << "Regular (RM)" << "\t\t" << "Large (RM)" << "\t\t" << "Available Stock" << endl;
	for (int i = 0; i < record; i++)
	{
		cout << showpoint << fixed << setprecision(2);
		cout << "\t\t\t" << setw(10) << FNB[i].foodcode << setw(30) << FNB[i].foodname << "\t" << setw(10) << FNB[i].regular_price << "\t\t" << setw(8) << FNB[i].large_price << setw(10) << FNB[i].stock << endl;
	}
}

void addFB()
{

	char more = 'N';
	int i = 0;
	ofstream outfile;
	outfile.open("foodAndBeverage.txt", ios::app);
	if (outfile.is_open())
	{
		inventoryMenu(0);
		do {
			cout << right << setw(15);
			cout << " Code: ";
			cin.ignore();
			getline(cin, FNB[i].foodcode);
			cout << right << setw(15) << "Food Name: ";
			getline(cin, FNB[i].foodname);
			cout << right << setw(15) << "Regular Price: ";
			cin >> FNB[i].regular_price;
			cout << right << setw(15) << "Large Price: ";
			cin >> FNB[i].large_price;
			cout << right << setw(15) << "Available stock: ";
			cin >> FNB[i].stock;
			outfile << showpoint << fixed << setprecision(2);
			outfile << endl;
			outfile << FNB[i].foodcode << endl;
			outfile << FNB[i].foodname << endl;
			outfile << FNB[i].regular_price << " " << FNB[i].large_price << endl;
			outfile << FNB[i].stock;
			cout << "\t\t\tDo you wish to add more? Enter 'Y' to add more...";
			cin >> more;
		} while (toupper(more) == 'Y');

		outfile.close();
		inventoryMenu(0);
	}
	else
	{
		cout << "\t\t\t\033[1;31mProblem occur!!! Please contact cinema admin for further assistance...\033[0m" << endl;
	}

}

void deleteFB(int option)
{
	bool found = true;
	int record = 0, detect = 0;
	do {
		string keyword;
		ReadFBRecord(record);
		system("cls");
		inventoryMenu(0);
		cout << "\t\t\tFood Code: ";
		cin >> keyword;
		keyword = upper(keyword);
		for (int i = 0; i < record; i++)
		{
			if (keyword == FNB[i].foodcode)
			{
				detect++;
				for (int j = i; j < record; j++)
				{
					FNB[j].foodcode = FNB[j + 1].foodcode;
					FNB[j].foodname = FNB[j + 1].foodname;
					FNB[j].regular_price = FNB[j + 1].regular_price;
					FNB[j].large_price = FNB[j + 1].large_price;
					FNB[j].stock = FNB[j + 1].stock;
				}
				record--;
			}
		}
		if (detect == 0)
			cout << "\t\t\t\033[1;31mInvalid Food Code found!!!\033[0m" << endl;
		else
			found = false;
		LoadFBRecord(record);
	} while (found);
	
	inventoryMenu(0);
}

void inventoryFB(int option)
{
	int record = 0;
	ReadFBRecord(record);
	//let users to select whether to add or delete stock
	string keyword, line;
	int action, quantity, i = 0, size, index;
	bool decision = true, found = 0;
	do {
		system("cls");
		inventoryMenu(0);
		cout << "\n\n\n\t\t\t<1> Add Stock " << endl;
		cout << "\t\t\t<2> Reduce Stock " << endl;
		cout << "\t\t\t<3> Exit" << endl;
		cout << "\t\t\tEnter your action: ";
		cin >> action;
		if (action == 1 || action == 2)
		{
			cout << "\t\t\tFood Code: ";
			cin >> keyword;
			keyword = upper(keyword);
			size = keyword.length();
			for (int i = 0; i < record; i++)
			{
				if (keyword == FNB[i].foodcode)
					index = i;//record the location of code
			}
			if (size == 4 && keyword == FNB[index].foodcode)
			{
				cout << "\t\t\tQuantity: ";
				cin >> quantity;
				cout << FNB[index].stock << endl;
				if (action == 1)
					FNB[index].stock += quantity;
				else if (action == 2)
					FNB[index].stock -= quantity;
				cout << FNB[index].stock << endl;
				LoadFBRecord(record);
				

				cout << "\t\t\tStock Updated." << endl;
				
			}
			else
				cout << "\t\t\t\033[1;31mInvalid id detected!!!\033[0m" << endl;
		}
		else if (action == 3)
			decision = false;
		else
		{
			cout << "\t\t\t\033[1;31mInvalid Action!!! Please enter <1> <2> <3>\033[0m" << endl;
			
		}
			

	} while (decision);
}

void FBManagement()
{
	bool con = true;
	do {
		int selection;
		cout << "\t\t\t<1> Add New Food and Beverage" << endl;
		cout << "\t\t\t<2> Delete Existing Food and Beverage" << endl;
		cout << "\t\t\t<3> Inventory Management" << endl;
		cout << "\t\t\t<4> Return to Administrator Menu" << endl;
		cout << "\t\t\tPlease enter your selection: ";
		cin >> selection;
		if (selection == 1)
		{
			system("cls");
			addFB();
		}
		else if (selection == 2)
		{
			system("cls");
			deleteFB(selection);
		}
		else if (selection == 3)
		{
			system("cls");
			inventoryFB(selection);
		}
		else if (selection == 4)
		{
			system("cls");
			AdministratorMenu();
			con = false;
		}
		else
			cout << "\t\t\t\033[1;31mWrong Input!!! Please enter <1> <2> <3>\033[0m" << endl;
	} while (con);
}

void purchaseFB()
{
	int record = 0;
	ReadFBRecord(record);
	for (int i = 0; i < record; i++)
	{
		cout << showpoint << fixed << setprecision(2);
		cout << setw(5) << "<" << i + 1 << ">" << setw(30) << FNB[i].foodname << "\t" << setw(10) << FNB[i].regular_price << "\t" << setw(6) << FNB[i].large_price << endl;
	}
	int choice;
	int size;
	double price, total = 0;
	int quantity;
	bool correct = 0;
	char cont;
	do {

		do {
			cout << "\n\n\n\t\t\tEnter your choice: ";
			cin >> choice;
			if (choice <1 || choice>record)
				cout << "\t\t\t\033[1;31mInvalid Input!!!\033[0m" << endl;

			else
				correct = 1;

		} while (correct == 0);
		correct = 0;
		do {
			cout << "\t\t\tSize: <1> Regular <2> Large: ";
			cin >> size;
			if (size < 1 || size>2)
				cout << "\t\t\t\033[1;31mInvalid Input!!!\033[0m" << endl;
			else
				correct = 1;
		} while (correct == 0);
		correct = 0;
		do {
			cout << "\t\t\tQuantity: ";
			cin >> quantity;
			if (quantity < 0)
				cout << "\t\t\t\033[1;31mInvalid Input!!!\033[0m";
			else if (quantity > FNB[choice - 1].stock)
				cout << "\t\t\tOut of Stock!!!" << endl;
			else
				correct = 1;
		} while (correct == 0);

		if (size == 1)
			price = FNB[choice - 1].regular_price * quantity;
		else
			price = FNB[choice - 1].large_price * quantity;

		total += price;

		FNB[choice - 1].stock -= quantity;
		LoadFBRecord(record);

		cout << "\t\t\tDo you want to add another F&B? <Y> to continue...";
		cin >> cont;

	} while (toupper(cont) == 'Y');

	cout << "\t\t\tYou need to pay \033[1;92mRM: "<<total <<"\033[0m"<< endl;
}

void ReadFBRecord(int& record)
{
	ifstream infile;
	infile.open("foodAndBeverage.txt");
	if (infile.is_open())
	{
		while (!infile.eof())
		{
			getline(infile, FNB[record].foodcode);
			getline(infile, FNB[record].foodname);
			infile >> FNB[record].regular_price >> FNB[record].large_price;
			infile >> FNB[record].stock;
			infile.ignore();
			record++;
		}
		infile.close();
	}
	else
		cout << "\t\t\t\033[1;31mPlease contact Cinema Admin for further assistance...\033[0m";
}
void LoadFBRecord(int& record)
{
	ofstream outfile;
	outfile.open("foodAndBeverage.txt");
	for (int i = 0; i < record; i++)
	{
		outfile << FNB[i].foodcode << endl;
		outfile << FNB[i].foodname << endl;
		outfile << FNB[i].regular_price << " " << FNB[i].large_price << endl;
		outfile << FNB[i].stock;
		if (i != record - 1)
			outfile << endl;
	}
}






















void Main_Menu(string Name)
{
	int i = 142, j = 48;
	//system("Color 30");
	cout << "\n\n\n\t\t\t" << string(121, char(61)) << "\n";
	cout << "\t\t\t=" << right << setw(121) << "=\n";
	cout << "\t\t\t=" << string(4, ' ') << string(20, char(126)) << string(20, ' ') << string(25, char(126)) << string(25, ' ') << string(19, char(126)) << string(5, ' ') << " = \n";
	cout << "\t\t\t=" << string(4, ' ') << "[";
	//SetConsoleTextAttribute(console, i);
	cout << " 1. Movie Details ";
	//SetConsoleTextAttribute(console, j);
	cout << "]" << string(20, ' ') << "[";
	//SetConsoleTextAttribute(console, i);
	cout << " 2. Food and Beverages ";
	//(console, j);
	cout << "]" << string(25, ' ') << "[";
	//SetConsoleTextAttribute(console, i);
	cout << " 3. Purchase Now ";
	//SetConsoleTextAttribute(console, j);
	cout << "]" << string(5, ' ') << " = \n";
	cout << "\t\t\t=" << string(4, ' ') << string(20, char(126)) << string(20, ' ') << string(25, char(126)) << string(25, ' ') << string(19, char(126)) << string(5, ' ') << " = \n";
	cout << "\t\t\t=" << right << setw(121) << "=\n";
	cout << "\t\t\t=" << string(24, ' ') << string(22, char(95)) << string(23, ' ') << string(25, char(95)) << string(24, ' ') << " = \n";
	cout << "\t\t\t=" << string(24, ' ') << "[";
	//SetConsoleTextAttribute(console, i);
	cout << " 4. Membership Page ";
	//SetConsoleTextAttribute(console, j);
	cout << "]" << string(23, ' ') << "[";
	//SetConsoleTextAttribute(console, i);
	cout << " 5. Administrator Page ";
	//SetConsoleTextAttribute(console, j);
	cout << "]" << string(24, ' ') << " = \n";
	cout << "\t\t\t=" << string(24, ' ') << string(20, char(126)) << string(25, ' ') << string(25, char(126)) << string(24, ' ') << " = \n";
	cout << "\t\t\t=" << right << setw(121) << "=\n";
	cout << "\t\t\t=" << string(50, ' ') << string(14, char(126)) << string(54, ' ') << " = \n";
	cout << "\t\t\t=" << string(50, ' ') << "[";
	//SetConsoleTextAttribute(console, i);
	cout << " 5.   EXIT  ";
	//SetConsoleTextAttribute(console, j);
	cout << "]" << string(54, ' ') << " = \n";
	cout << "\t\t\t=" << string(50, ' ') << string(14, char(126)) << string(54, ' ') << " = \n";
	cout << "\t\t\t" << string(121, char(61)) << "\n";

}

