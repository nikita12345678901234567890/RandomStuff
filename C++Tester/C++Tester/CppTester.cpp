#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

struct Record
{
    string ID;
    string Model;
    int Quantity;
    double Price;
};

enum MenuOptions
{
    printValid,
    printInvalid,
    quit
};

const int maxRecords = 10;

void ReadFile(Record* records, int& numRecords);
int checkValid(Record record, string* errors);
bool isAlphaNum(char c);
void PrintRecords(Record* records, int numRecords);
void PrintInvalid();

int main()
{
    Record* records = new Record[maxRecords];
    int numRecords = 0;
    ReadFile(records, numRecords);

    bool menu = true;
    int choice;
    while (menu)
    {
        //Printing menu
        cout << printValid << " print records\n" << printInvalid << " print errors\n" << quit << " quit" << endl;

        cin >> choice;

        switch (choice)
        {
            case printValid:
                PrintRecords(records, numRecords);
                break;

            case printInvalid:
                PrintInvalid();
                break;

            case quit:
                menu = false;
                break;
        }
    }


    return 0;
}

void ReadFile(Record* records, int &numRecords)
{
    ifstream file;
    file.open("Records.txt");

    ofstream ErrorFile;
    ErrorFile.open("Error.txt");

    bool ErrorHappened = false;

    while (file && numRecords < maxRecords)
    {
        //reading record
        Record temp;
        file >> temp.ID;
        file >> temp.Model;
        file >> temp.Quantity;
        file >> temp.Price;

        //checking validity
        string errorMessages[15];
        int numErrors = checkValid(temp, errorMessages);
        if (numErrors == 0)
        {
            //storing record
            records[numRecords] = temp;
            numRecords++;
        }
        else if(temp.ID.length() > 0)
        {
            if (!ErrorHappened)//If there hasn't been an error before
            {
                ErrorHappened = true;

                //write the header
                ErrorFile << "_______________________________________________________________________________________________\n"//width 75
                          << "|    ID    |    Model    |  Stock  |    Price    |                Error Message               |\n"
                          << "-----------------------------------------------------------------------------------------------" << endl;
            }

            //writing the record
            ErrorFile << "|"
                      << std::setw(10) << std::left << temp.ID << "|"
                      << std::setw(13) << temp.Model << "|"
                      << std::setw(9) << std::right << temp.Quantity << "|"
                      << std::setw(13) << std::fixed << std::setprecision(2) << temp.Price << "|"
                      << std::setw(44) << errorMessages[0] << "|" << endl;

            //If there are multiple errors
            for (int i = 1; i < numErrors; i++)
            {
                ErrorFile << "|          |             |         |             |" << std::setw(44) << errorMessages[i] << "|\n";
            }
        }
    }

    if (ErrorHappened)//If there was an error
    {
        //write the bottom of the table
        ErrorFile << "-----------------------------------------------------------------------------------------------" << endl;
    }

    if (numRecords == 0)
    {
        cout << "No vald records." << endl;
    }
    else if (numRecords >= maxRecords)
    {
        cout << "Too many records, stored first " << maxRecords << "." << endl;
    }

    file.close();
    ErrorFile.close();
}

int checkValid(Record record, string* messages)
{
    int numErrors = 0;

    //Checking ID:
    //checking length of ID
    if (record.ID.length() != 9)
    {
        messages[numErrors] += "ID wrong size";
        numErrors++;
    }

    //Checking that first character is a letter and not O
    if (record.ID.length() >= 0 && (!isalpha(record.ID[0]) || record.ID[0] == 'O' || record.ID[0] == 'o'))
    {
        messages[numErrors] += "ID first char invalid";
        numErrors++;
    }
    //Checking that second character is a letter and not O
    if (record.ID.length() >= 1 && (!isalpha(record.ID[1]) || record.ID[1] == 'O' || record.ID[1] == 'o'))
    {
        messages[numErrors] += "ID second char invalid";
        numErrors++;
    }

    //checking that next 4 characters are alphanumeric and not O:
    if (record.ID.length() >= 6)
    {
        for (int i = 2; i < 6; i++)
        {
            if (!isAlphaNum(record.ID[i]) || record.ID[i] == 'O' || record.ID[i] == 'o')
            {
                messages[numErrors] += "ID char " + to_string(i + 1) + " invalid";
                numErrors++;
            }
        }
    }
    
    if (record.ID.length() >= 9)
    {
        //checking that last 3 characters are numbers
        for (int i = 6; i < 9; i++)
        {
            if (!isdigit(record.ID[i]))
            {
                messages[numErrors] += "ID char " + to_string(i + 1) + " invalid";
                numErrors++;
            }
        }
    }


    //Checking Model:
    //Checking length
    if (record.Model.length() < 3)
    {
        messages[numErrors] += "Model name too short";
        numErrors++;
    }

    //Checking that first character is a letter
    if (!isalpha(record.Model[0]))
    {
        messages[numErrors] += "Model name must start with letter";
        numErrors++;
    }

    //Checking that the rest are alphaNumeric
    for (int i = 1; i < record.Model.length(); i++)
    {
        if (!isAlphaNum(record.Model[i]))
        {
            messages[numErrors] += "Model char " + to_string(i + 1) + " invalid";
            numErrors++;
        }
    }


    //Checking Quantity:
    if (record.Quantity < 0)
    {
        messages[numErrors] += "Quantity must be 0 or more";
        numErrors++;
    }

    
    //Checking Price:
    if (record.Price < 5000)
    {
        messages[numErrors] += "Price must be 5000.00 or more";
        numErrors++;
    }

    return numErrors;
}

bool isAlphaNum(char c)
{
    return isalpha(c) || isdigit(c);
}

void PrintRecords(Record* records, int numRecords)
{
    //printing header
    cout << "__________________________________________________\n"//width 50
         << "|    ID    |    Model    |  Stock  |    Price    |\n"
         << "--------------------------------------------------" << endl;

    cout << std::setfill(' ');
    for (int i = 0; i < numRecords; i++)
    {
        //printing the values
        cout << "|"
             << std::setw(10) << std::left << records[i].ID << "|"
             << std::setw(13) << records[i].Model << "|"
             << std::setw(9) << std::right << records[i].Quantity << "|"
             << std::setw(13) << std::fixed << std::setprecision(2) << records[i].Price << "|" << endl;
    }
    //printing bottom of table
    cout << "--------------------------------------------------" << endl;
}

void PrintInvalid()
{
    ifstream file;
    file.open("Error.txt");

    cout << file.rdbuf() << endl;

    file.close();
}