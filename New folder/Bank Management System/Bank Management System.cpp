#include<iostream>
#include<string>
#include<fstream>


using namespace std;


class Account;
class Investment;
class Loansystems;
class Saving;
class Current;

bool checkemail(string email) {
    int flag1 = 0, flag2 = 0;
    for (int i = 0; i < email.size(); i++) {
        if (email[i] == '@')
            flag1++;
        else if (email[i] == '.')
            flag2++;
    }
    if (flag1 == 1 && flag2 == 1)
        return 1;
    return 0;
}

bool checkcontact(string contact) {
    if (contact.size() != 11) {
        return 0;
    }
    for (int i = 0; i < contact.size(); i++) {
        if (contact[i] < '0' || contact[i] > '9') {
            return 0;
        }
    }
    return 1;
}

template<class T, class U>
void transfer(T* a, U* b) {
    double balance;
    cout << "How much money do you want to transfer: ";
    cin >> balance;
    if (a->withdrawal(balance)) {
        b->deposit(balance);
    }
}

class User {
protected:
    string username, email, contact, password;
    int a;
public:
    User() {}
    User(string username, string password, string email, string contact) :username(username), contact(contact), email(email) {
        this->password = encryptpass(password);
    }
    void setdetails(string username, string password, string email, string contact) {
        this->username = username;
        this->contact = contact;
        this->email = email;
        this->password = encryptpass(password);
    }
    string getusername() {
        return username;
    }
    string getpassword() {
        return password;
    }
    string encryptpass(string& password) {
        for (int i = 0; i < password.length(); i++) {
            password[i] += 3;
        }
        return password;
    }
    string decryptpass(string& password) {
        for (int i = 0; i < password.length(); i++) {
            password[i] -= 3;
        }
        return password;
    }
    void setusername(const string username) {
        this->username = username;
    }
    void setpassword(const string password) {
        this->password = password;
    }
    bool verifypassword(const string pass) {
        return ((password == pass));
    }

};
class Account : public User {
public:
    static int totalregisteredusers;
    int accnumber;
    int a, b;
    friend bool withdrawal(Account& accs, double balance);
    friend void deposit(Account& acsss, double balance);

    Account() {
        accnumber = 4687 + (totalregisteredusers * 2);
        totalregisteredusers++;
    }
    Account(string username, string password, string email, string contact) :User(username, password, email, contact) {
        accnumber = 4687 + (totalregisteredusers * 2);
        totalregisteredusers++;
    }
    void setaccdetails(string username, string password, string email, string contact) {
        setdetails(username, password, email, contact);
        totalregisteredusers++;
    }
    int getaccnumber() { return accnumber; }

    virtual void details() = 0;
    virtual bool withdrawal(double balance) = 0;
    virtual void deposit(double balance) = 0;

};

// int Account :: totalregisteredusers = 0;
int Account::totalregisteredusers = 0;



//Investment
class Investment : virtual public Account {
protected:

    float returnrate;
    double amount;//invested amount
    int year;
public:
    static int invaccounts;
    Investment() {
        returnrate = 15;
    }
    void setinvdetails(string username, string password, string email, string contact, double balance, int year) {
        this->username = username;
        this->password = password;
        this->email = email;
        this->contact = contact;
        this->amount = balance;
        this->year = year;
        invaccounts++;
    }
    void setreturnrate(const float rr) { returnrate = rr; }
    Investment(string username, string password, string email, string contact, double investedamount, int year) :Account(username, password, email, contact) {
        invaccounts++;
        this->amount = investedamount;
        cout << "Investment Account created" << endl;
    }
    double profitperannum(double am, int yrs) {
        return ((am * (returnrate / 100)) * yrs);
    }
    double  balancewithprofitperannum(int yrs) {
        amount = amount + profitperannum(amount, yrs - year);
        year = yrs;
        return (amount);
    }


    void setamount(double invest) { amount = invest; }
    double getamount() { return amount; }
    void details() {
        cout << "Username: " << username << endl
            << "Account Number: " << accnumber << endl
            << "Email: " << email << endl
            << "Contact: " << contact << endl
            << "Invested Amount including profits: " << amount << endl
            << "NOTE: This amount is with respect to year " << year << endl
            << "If this not the year " << year << ",Kindly update the year" << endl;
    }
    bool withdrawal(double balance) {
        double a;
        if (amount >= balance) {
            amount -= balance;
            return 1;
        }
        return 0;
    }
    void deposit(double balance) {
        amount += balance;
    }

};
int Investment::invaccounts = 0;

//Loan 
class Loansystems : virtual public Account {
protected:

    float interestrate;
    double amount;//loan amount
    double propertyvalue;
    int year;
public:
    static int numofloanaccount;
    Loansystems(string username, string password, string email, string contact, double propertyvalue, double loanamount) :Account(username, password, email, contact), propertyvalue(propertyvalue), amount(loanamount) { numofloanaccount++; }
    Loansystems() {
        interestrate = 17;
        amount = 0;
        propertyvalue = 0;
    }
    bool setloandetails(string username, string password, string email, string contact, int year, double propertyvalue, double loanamount) {
        if (propertyvalue <= loanamount) {
            return 0;
        }
        this->username = username;
        this->password = password;
        this->email = email;
        this->contact = contact;
        this->amount = loanamount;
        this->propertyvalue = propertyvalue;
        this->year = year;
        numofloanaccount++;
        return 1;
    }
    int getyear() { return year; }
    double tobepaidpermonth(int months, double tax = 3) {
        return ((amount * tax / 100) * months);
    }
    double tobepaidperyrs(int yrs, double tax = 17) {
        amount += ((amount * tax / 100) * yrs);
        year = yrs;
        return amount;
    }
    void setamount(double invest) { amount = invest; }
    double getamount() { return amount; }
    void payment(double depositedamount) {
        if (amount > depositedamount) { deposit(depositedamount); cout << "Rest of the amount to be paid: " << amount; }
        else if (amount == depositedamount) { deposit(depositedamount); cout << "Propert papers returned"; }
        else if (amount < depositedamount) { deposit(amount); cout << "Property papers returned with the cashback of " << depositedamount - amount << endl; }
    }
    void wantmoreloan(double balance) {
        if (propertyvalue >= (amount + balance)) {
            withdrawal(balance);
            cout << "Loan Granted" << endl;
        }
        else {
            cout << "Cant give more loan" << endl;
        }
    }
    void details() {
        cout << "Username: " << username << endl
            << "Account Number: " << getaccnumber() << endl
            << "Email: " << email << endl
            << "Contact: " << contact << endl
            << "Loan Amount: " << amount << endl
            << "NOTE: This amount is with respect to year(s) " << year << endl
            << "If this not the year " << year << ",Kindly update the year" << endl;

    }
    bool withdrawal(double balance) {
        amount += balance;
        return 1;
    }
    void deposit(double balance) {
        amount -= balance;
    }
};
int Loansystems::numofloanaccount = 0;

//Saving
class Saving : virtual public Account {
protected:
    double amount;//saving amount
    float rateperannum;

    float zakaat;
public:
    static int numofsavingaccount;
    Saving() {
        rateperannum = 13;
        zakaat = 2.5;
    }
    Saving(string username, string password, string email, string contact, double deposit) :Account(username, password, email, contact), amount(deposit) {
        rateperannum = 13;
        zakaat = 2.5;
        numofsavingaccount++;
    }
    void setsavdetails(string username, string password, string email, string contact, double deposit) {
        this->username = username;
        this->password = password;
        this->email = email;
        this->contact = contact;
        this->amount = deposit;
        numofsavingaccount++;
    }
    double profitperannum(int yrs) { return ((amount * rateperannum / 100) * yrs); }
    double setamount(int yrs) {
        amount += profitperannum(yrs);
        return amount;
    }
    double zakaatdeduction(int yrs) {
        amount -= ((amount * zakaat / 100) * yrs);
        return amount;
    }
    void setamount(double invest) { amount = invest; }
    double getamount() { return amount; }
    bool withdrawal(double balance) {
        if (amount >= balance) {
            amount -= balance;
            return 1;
        }
        return 0;
    }
    void deposit(double balance) {
        amount += balance;
    }
    void details() {
        cout << "Username: " << username << endl
            << "Account Number: " << getaccnumber() << endl
            << "Email: " << email << endl
            << "Contact: " << contact << endl
            << "Balance: " << amount << endl;
    }
};
int Saving::numofsavingaccount = 0;

//Current
class Current : virtual public Account {
protected:
    double amount;

public:
    static int numofcurrentaccount;
    Current() {}
    Current(string username, string password, string email, string contact, double deposit) :Account(username, password, email, contact), amount(deposit) { numofcurrentaccount++; }
    void setamount(double deposited) {
        amount = deposited;
    }
    void setcurrdetails(string username, string password, string email, string contact, double deposit) {
        this->username = username;
        this->password = password;
        this->email = email;
        this->contact = contact;
        this->amount = deposit;
        numofcurrentaccount++;
    }
    double getamount() { return amount; }
    void details() {
        cout << "Username: " << username << endl
            << "Account Number: " << getaccnumber() << endl
            << "Email: " << email << endl
            << "Contact: " << contact << endl
            << "Balance: " << amount << endl;
    }

    bool withdrawal(double balance) {
        if (amount >= balance) {
            amount -= balance;
            return 1;
        }

        return 0;
    }
    void deposit(double balance) {
        amount += balance;
    }
};
int Current::numofcurrentaccount = 0;


class Bank {
protected:

    Investment* investmentaccounts = new Investment[25];
    Loansystems* loanaccounts = new Loansystems[25];
    Saving* savaccounts = new Saving[25];
    Current* currentaccounts = new Current[25];

    bool flag;
    int opt, year;
    double amount, loan;
    string nme;
    int accnum;
    Investment& checkaccnuminv() {
        int num, j;
        cout << "Enter account num: ";
        cin >> num;
        for (int i = 0; i < Investment::invaccounts; i++)
        {
            if (investmentaccounts[i].getaccnumber() == num) {
                j = i;
            }
        }
        return investmentaccounts[j];

    }
    Saving& checkaccnumsav() {
        int num, j;
        cout << "Enter account num: ";
        cin >> num;
        for (int i = 0; i < Saving::numofsavingaccount; i++)
        {
            if (savaccounts[i].accnumber == num) {
                j = i;
            }
        }
        return savaccounts[j];

    }
    Current& checkaccnumcurr() {
        int num, j;
        cout << "Enter account num: ";
        cin >> num;
        for (int i = 0; i < Current::numofcurrentaccount; i++)
        {
            if (currentaccounts[i].accnumber == num) {
                j = i;
            }
        }
        return currentaccounts[j];
    }
    void investmentaccountsservices(Investment& a) {
        int opt, opt1;
        int yr; double amount;
        while (1) {
            cout << "Services available for Investment Account: " << endl << endl
                << "1.Update profits by updating year" << endl
                << "2.get roughly idea of profit per annum with the balance to be deposited" << endl
                << "3.Withdraw" << endl
                << "4.deposit" << endl
                << "5.Tranfer Funds" << endl
                << "6.Display all the information" << endl
                << "0.LOGOUT" << endl;
            cin >> opt;
            switch (opt) {
            case 0:
                break;
            case 1:
                cout << "Enter the current year" << endl;
                cin >> yr;
                cout << "New balance after including profits is: " << a.balancewithprofitperannum(yr) << endl;
                break;
            case 2:
                cout << "Enter the Amount: ";
                cin >> amount;
                cout << "Enter the years that have passed: ";
                cin >> yr;
                cout << "Profit after " << yr << "years : " << a.profitperannum(amount, yr);
                break;
            case 3:
                cout << "How much do you want to withdraw: " << endl;
                cin >> amount;
                if (a.withdrawal(amount)) {
                    cout << "Successful withdrawal" << endl;
                }
                else {
                    cout << "You dont have enough balance in account to withdraw" << endl;
                }
                break;
            case 4:
                cout << "How do you want to to deposit: " << endl;
                cin >> amount;
                a.deposit(amount);
                break;
            case 5:
                cout << "Accout type to which you want to transfer: " << endl
                    << "1.Saving" << endl
                    << "2.Current" << endl;
                cin >> opt1;
                if (opt1 == 1) {
                    transfer<Investment, Saving>(&a, &checkaccnumsav());
                }

                //For fund transfers

                break;
            case 6:
                a.details();
                break;

            default:
                cout << "INVALID INPUT" << endl;
            }
            if (opt == 0) {
                break;
            }

        }

    }

    void loanaccountsservices(Loansystems& a) {
        int opt;
        int yr; double amount, interest;
        while (1) {
            cout << "Services available for Loan Accounts: " << endl << endl
                << "1.Get rough idea of loan to be paid by entering number of months passed and get the amount to be paid" << endl
                << "2.Update number of years passed and get the updated amount to be paid" << endl
                << "3.Pay off your debt" << endl
                << "4.Want more loan" << endl
                << "5.Display all the information" << endl
                << "0.EXIT" << endl;
            cin >> opt;
            switch (opt) {
            case 0:
                break;
            case 1:
                cout << "Enter number of months passed: " << endl;
                cin >> yr;
                cout << "Enter current interest rate: ";
                cin >> interest;
                cout << "Loan to be paid after including interest" << a.tobepaidpermonth(yr, interest) << endl;
                break;
            case 2:
                cout << "Enter current year: ";
                cin >> yr;
                cout << "New balance after including interest" << a.tobepaidperyrs(yr - a.getyear()) << endl;
                break;
            case 3:
                cout << "Enter how much do you want to payoff: " << endl;
                cin >> amount;
                a.payment(amount);
                break;
            case 4:
                cout << "How much do you want: " << endl;
                cin >> amount;
                a.wantmoreloan(amount);
                break;
            case 5:
                a.details();
                break;
            default:
                cout << "INVALID INPUT" << endl;
            }
            if (opt == 0) {
                break;
            }

        }
    }
    void Savingaccountservice(Saving& a) {
        int opt;
        int yr; double amount, interest;
        while (1) {
            cout << "Services available for Saving Accounts: " << endl << endl
                << "1.Update number of years passed and get the updated amount" << endl
                << "2.Update number of years passed and deduce zakaat from amount" << endl
                << "3.Deposit money to your account" << endl
                << "4.Withdraw some money" << endl
                << "5.Display all the information" << endl
                << "0.EXIT" << endl;
            cin >> opt;
            switch (opt) {
            case 0:
                break;
            case 1:
                cout << "Enter number of months that have passed: " << endl;
                cin >> yr;
                cout << "New balance after including interest: " << a.setamount(yr) << endl;
                break;
            case 2:
                cout << "Enter number of years that have passed: ";
                cin >> yr;
                cout << "New balance after including interest " << a.zakaatdeduction(yr) << endl;
                break;
            case 3:
                cout << "Enter how much do you want to deposit: " << endl;
                cin >> amount;
                a.deposit(amount);
                break;
            case 4:
                cout << "How much do you want to withdraw: " << endl;
                cin >> amount;
                if (a.withdrawal(amount)) {
                    cout << "Successful Withdraw" << endl;
                }
                else {
                    cout << "You dont have enough balance to withdraw the amount" << endl;
                }
                break;
            case 5:
                a.details();
                break;
            default:
                cout << "INVALID INPUT" << endl;
            }
            if (opt == 0) {
                break;
            }

        }
    }
    void currentaccountservices(Current& a) {
        int opt;
        int yr; double amount, interest;
        while (1) {
            cout << "Services available for Current Accounts: " << endl << endl
                << "1.Deposit amount" << endl
                << "2.Withdraw amount" << endl
                << "3.Display all the information" << endl
                << "0.EXIT" << endl;
            cin >> opt;
            switch (opt) {
            case 0:
                break;
            case 1:
                cout << "Enter the amount you wish to deposit: " << endl;
                cin >> amount;
                a.deposit(amount);
                cout << "Amount Deposited " << endl;
                break;
            case 2:
                cout << "Enter the amount you want to withdraw: ";
                cin >> amount;
                a.withdrawal(amount);
                break;
            case 3:
                a.details();
                break;
            default:
                cout << "INVALID INPUT" << endl;
            }
            if (opt == 0) {
                break;
            }

        }

    }
public:
    Bank() {}
    void openaccount(string name, string password, string email, string contact) {
        flag = 0;
        string username, nme;
        username = name;

        flag = 1;
        cout << "Which type of account do you want to open?" << endl << endl
            << "1.INVESTMENT ACCOUNT" << endl
            << "2.LOAN ACCOUNT" << endl
            << "3.SAVING ACCOUNT" << endl
            << "4.CURRENT ACCOUNT" << endl;
        do {
            cin >> opt;
            switch (opt) {
            case 1:
                cout << "Enter the initial balance of your account: " << endl;
                cin >> amount;
                cout << "Enter current year: ";
                cin >> year;
                investmentaccounts[Investment::invaccounts].setinvdetails(username, password, email, contact, amount, year);
                cout << "Investment Account successfully created" << endl;
                flag = 0;
                break;
            case 2:
                cout << endl << "Enter value of property papers given to take loan: ";
                cin >> amount;
                cout << "Enter Loan Value: ";
                cin >> loan;
                cout << "Enter current year: ";
                cin >> year;
                if (loanaccounts[Loansystems::numofloanaccount].setloandetails(username, password, email, contact, year, amount, loan)) {
                    cout << "Loan Account successfully created" << endl;
                }
                else {
                    cout << "Loan cannot be granted" << endl;
                }
                flag = 0;
                break;
            case 3:
                cout << "Enter the initial balance of your account: " << endl;
                cin >> amount;
                savaccounts[Saving::numofsavingaccount].setsavdetails(username, password, email, contact, amount);
                flag = 0;
                break;
            case 4:
                cout << "enter initial balance of account: " << endl;
                cin >> amount;
                currentaccounts[Current::numofcurrentaccount].setcurrdetails(username, password, email, contact, amount);
                cout << "Current Account successfully created" << endl;
                flag = 0;
                break;
            default:
                cout << "Invalid input" << endl;
                break;
            }

        } while (flag == 1);
    }

    bool loginsystem(string name, string password) {
        bool flag = 0;
        for (int i = 0; i < Investment::invaccounts; i++) {
            if (investmentaccounts[i].getusername() == name) {
                if (investmentaccounts[i].getpassword() == password) {
                    flag = 1;
                    investmentaccountsservices(investmentaccounts[i]);
                }
            }
        }
        for (int i = 0; i < Loansystems::numofloanaccount; i++) {
            if (loanaccounts[i].getusername() == name) {
                if (loanaccounts[i].getpassword() == password) {
                    flag = 1;
                    loanaccountsservices(loanaccounts[i]);
                }
            }
        }
        for (int i = 0; i < Saving::numofsavingaccount; i++) {
            if (savaccounts[i].getusername() == name) {
                if (savaccounts[i].getpassword() == password) {
                    flag = 1;
                    Savingaccountservice(savaccounts[i]);
                }
            }
        }
        for (int i = 0; i < Current::numofcurrentaccount; i++) {
            if (currentaccounts[i].getusername() == name) {
                if (currentaccounts[i].getpassword() == password) {
                    flag = 1;
                    currentaccountservices(currentaccounts[i]);
                }
            }
        }
        if (flag == 0) {
            return 0;
        }
        return 1;
    }

    void WriteIntoFile(ofstream* file) {
        int account[4] = { Investment::invaccounts,Loansystems::numofloanaccount,Saving::numofsavingaccount,Current::numofcurrentaccount };
        file->write((char*)&account, sizeof(account));
        file->write((char*)investmentaccounts, sizeof(Investment) * Investment::invaccounts);
        file->write((char*)loanaccounts, sizeof(Loansystems) * Loansystems::numofloanaccount);
        file->write((char*)savaccounts, sizeof(Saving) * Saving::numofsavingaccount);
        file->write((char*)currentaccounts, sizeof(Current) * Current::numofcurrentaccount);
    }

    void ReadFromFile(ifstream* file) {
        int account[4] = { 0,0,0,0 };
        file->read((char*)&account, sizeof(account));
        Investment::invaccounts = account[0];
        Loansystems::numofloanaccount = account[1];
        Saving::numofsavingaccount = account[2];
        Current::numofcurrentaccount = account[3];
        file->read((char*)investmentaccounts, sizeof(Investment) * Investment::invaccounts);
        file->read((char*)loanaccounts, sizeof(Loansystems) * Loansystems::numofloanaccount);
        file->read((char*)savaccounts, sizeof(Saving) * Saving::numofsavingaccount);
        file->read((char*)currentaccounts, sizeof(Current) * Current::numofcurrentaccount);
    }

    ~Bank() {
        delete[] investmentaccounts;
        delete[] loanaccounts;
        delete[] savaccounts;
        delete[] currentaccounts;
    }
};

int main() {
    Bank abcbank;
    int opt;
    string name, password, email, contact;
    ifstream output;
    ofstream input;
    output.open("BankManagementSystem.txt", ios::in | ios::binary);
    if (!output.is_open()) {
        cout << "Error: Cannot open file to read" << endl;
        return 1;
    }
    output.seekg(0);
    // Read the bank data from file (if it exists)
    abcbank.ReadFromFile(&output);
    // User menu
    while (1) {
        cout << "*****************  WELCOME TO THE BANK APP  *****************" << endl;
        cout << "Press 1 if you wish to make an account with us " << endl
            << "Press 2 to login into your account" << endl
            << "Press 0 to leave the Bank App" << endl;
        cin >> opt;
        if (opt == 1) {
            cout << "Enter Your Name: ";
            cin >> name;
            cout << "Enter your Password: ";
            cin >> password;
            do {
                cout << "Enter your Email address: ";
                cin >> email;
                if (!checkemail(email))
                    cout << "Invalid email" << endl;
            } while (!checkemail(email));
            do {
                cout << "Enter your Contact number : ";
                cin >> contact;
                if (!checkcontact(contact))
                    cout << "The contact number is incorrect, Please try again" << endl;
            } while (!checkcontact(contact));
            abcbank.openaccount(name, password, email, contact);
        }
        else if (opt == 2) {
            cout << "Enter Name: ";
            cin >> name;
            cout << "Enter Password: ";
            cin >> password;
            if (!abcbank.loginsystem(name, password)) {
                cout << "Incorrect credentials" << endl;
            }
        }
        else if (opt == 0) {
            break;
        }
        else {
            cout << "Invalid input" << endl;
            continue;
        }
    }
    output.close();
    input.open("BankManagementSystem.txt", ios::out | ios::binary | ios::trunc);
    if (!input.is_open()) {
        cout << "Error Cannon open file to write" << endl;
        return 1;
    }
    input.seekp(0);
    // Write the updated bank data to file
    abcbank.WriteIntoFile(&input);
    if (!input) {
        cout << "Error: Failed to write to file" << endl;
        return 1;
    }

    input.close();
    return 0;
}