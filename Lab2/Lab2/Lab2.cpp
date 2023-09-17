// Ulianov, Nikita
//Lab 2
/****Instructor's feedback DO NOT DELETE:

****/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;

struct Record
{
    string ID;
    string Model;
    int Quantity;
    double Price;
};

enum MENU_OPTIONS
{
    printValid = 1,
    printInvalid,
    search,
    quit
};

const int MAX_RECORDS = 50;

void ReadFile(Record* records, int& numRecords);
int checkValid(Record record, string* errors);
bool isAlphaNum(char c);
void PrintRecords(Record* records, int numRecords);
void PrintInvalid();
int Search(string value, Record* records, int numRecords, Record* results);
int Search(int price, Record* records, int numREcords, Record* results);
string ToLower(string input);
bool isNumber(string input);

int main()
{
    bool newWorks = true;
    Record* records = new Record[MAX_RECORDS];//DELETE THIS INITIALIZATION
    Record* searchResult = new Record[MAX_RECORDS];//same here
    try
    {
        records = new Record[MAX_RECORDS];
        searchResult = new Record[MAX_RECORDS];
    }
    catch (std::bad_alloc&)
    {
        newWorks = false;
        cout << "array allocation failed" << endl;
    }

    if (newWorks)
    {
        int numRecords = 0;
        ReadFile(records, numRecords);

        bool menu = true;
        int choice;
        while (menu)
        {
            cout << "\n\n"
                << printValid << " print records\n"
                << printInvalid << " print errors\n"
                << search << " search\n"
                << quit << " quit" << endl;

            cin >> choice;

            string input = "";

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

            case search:
                cout << "\n1 search by ID/model\n2 search by price" << endl;

                cin >> choice;

                if (choice == 1)
                {
                    cout << "What do you want to search for?" << endl;
                    cin >> input;

                    int numResults = Search(input, records, numRecords, searchResult);

                    if (numResults == 0)
                    {
                        cout << "No matches" << endl;
                    }
                    else
                    {
                        PrintRecords(searchResult, numResults);
                    }
                }
                else if (choice == 2)
                {
                    cout << "Enter price" << endl;
                    cin >> input;

                    if (isNumber(input))
                    {
                        int numResults = Search(stoi(input), records, numRecords, searchResult);

                        if (numResults == 0)
                        {
                            cout << "No matches" << endl;
                        }
                        else
                        {
                            PrintRecords(searchResult, numResults);
                        }
                    }
                    else
                    {
                        cout << "Invalid input" << endl;
                    }
                }
                else
                {
                    cout << "Invalid choice" << endl;
                }

                break;

            default:
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid option" << endl;
                break;
            }
        }
    }

    delete[] records;

    return 0;
}

void ReadFile(Record* records, int& numRecords)
{
    ifstream recordFile;
    recordFile.open("Records.txt");

    ofstream ErrorFile;
    ErrorFile.open("Error.txt");

    bool filesWork = recordFile && ErrorFile;
    if (!filesWork)
    {
        cout << "Unable to open file" << endl;
    }

    bool ErrorHappened = false;

    ErrorFile << std::setprecision(2);

    while (recordFile && numRecords < MAX_RECORDS && filesWork)
    {
        //reading record
        Record temp;
        recordFile >> temp.ID;
        recordFile >> temp.Model;
        recordFile >> temp.Quantity;
        recordFile >> temp.Price;

        //checking validity
        string errorMessages[15];
        //This^ is an array of all the error messages for a record.
        //15 is the maximum number of errors one record could have, plus a few just in case.
        int numErrors = checkValid(temp, errorMessages);
        if (numErrors == 0)
        {
            //storing record
            records[numRecords] = temp;
            numRecords++;
        }
        else if (temp.ID.length() > 0)
        {
            if (!ErrorHappened)//If there hasn't been an error before
                //This is done inside the loop because it changes as the loop runs
                //At the beginning of the loop I have read 0 records, so there have been no errors.
            {
                ErrorHappened = true;

                //write the header
                ErrorFile << setw(96) << setfill('_') << "\n"
                    << "|    ID    |    Model    |  Stock  |    Price    |                Error Message               |\n"
                    << setw(96) << setfill('-') << "\n";
            }

            //writing the record
            ErrorFile << setfill(' ') << "|"
                << std::setw(10) << std::left << temp.ID << "|"
                << std::setw(13) << temp.Model << "|"
                << std::setw(9) << std::right << temp.Quantity << "|"
                << std::setw(13) << std::fixed << temp.Price << "|"
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
        ErrorFile << setfill('-') << setw(95) << "\n";
    }

    if (numRecords == 0)
    {
        cout << "No vald records." << endl;
    }
    else if (numRecords >= MAX_RECORDS)
    {
        cout << "Too many records, stored first " << MAX_RECORDS << "." << endl;
    }

    recordFile.close();
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
    cout << std::setprecision(2)
        << setfill('_') << setw(51) << "\n"
        << "|    ID    |    Model    |  Stock  |    Price    |\n"
        << setfill('-') << setw(51) << "\n";

    cout << std::setfill(' ');
    for (int i = 0; i < numRecords; i++)
    {
        //printing the values
        cout << "|"
            << std::setw(10) << std::left << records[i].ID << "|"
            << std::setw(13) << records[i].Model << "|"
            << std::setw(9) << std::right << records[i].Quantity << "|"
            << std::setw(13) << std::fixed << records[i].Price << "|" << "\n";
    }
    //printing bottom of table
    cout << setfill('-') << setw(51) << "\n" << endl;
}

void PrintInvalid()
{
    ifstream errorFile;
    errorFile.open("Error.txt");

    if (errorFile.peek() != '_')
    {
        cout << "file was empty" << endl;
    }
    else if (errorFile)
    {
        cout << errorFile.rdbuf() << endl;
    }
    else
    {
        cout << "unable to open recordFile" << endl;
    }

    errorFile.close();
}

int Search(string value, Record* records, int numRecords, Record* results)
{
    int numResults = 0;

    for (int i = 0; i < numRecords; i++)
    {
        if (ToLower(records[i].ID).find(ToLower(value)) != string::npos || ToLower(records[i].Model).find(ToLower(value)) != string::npos)
        {
            results[numResults] = records[i];
            numResults++;
        }
    }

    return numResults;
}
int Search(int price, Record* records, int numRecords, Record* results)
{
    int numResults = 0;

    double percent = price * 0.15;

    for (int i = 0; i < numRecords; i++)
    {
        if (records[i].Price > price - percent && records[i].Price < price + percent)
        {
            results[numResults] = records[i];
            numResults++;
        }
    }

    return numResults;
}

string ToLower(string input)
{
    string result = "";
    for (int i = 0; i < input.size(); i++)
    {
        result += tolower(input[i]);
    }

    return result;
}

bool isNumber(string input)
{
    bool isNumber = true;
    for (int i = 0; i < input.size(); i++)
    {
        if (!isdigit(input[i]))
        {
            isNumber = false;
        }
    }

    return isNumber;
}

/*
Records:
AB12MP349 Fusion5 20 17000.00
35KMOP324 Focus3 15 4000.00
Zb1K2l456 YeetCar 42 12345.67
O2o#$%YoO 3% -2 -5.21
AB12MP349 Fusion1 0 17000.00
BB12MP349 Fusion2 1 17000.00
CB12MP349 Fusion3 2 17000.00
DB12MP349 Fusion4 3 17000.00
EB12MP349 Fusion5 4 17000.00
FB12MP349 Fusion6 5 17000.00
GB12MP349 Fusion7 6 17000.00
HB12MP349 Fusion8 7 17000.00
IB12MP349 Fusion9 8 17000.00
JB12MP349 Fusion0 9 17000.00
KB12MP349 Fusio15 10 17000.00
LB12MP349 Fusio25 11 17000.00
MB12MP349 Fusio35 12 17000.00
NB12MP349 Fusio45 13 17000.00
OB12MP349 Fusio55 14 17000.00
PB12MP349 Fusio65 15 17000.00
QB12MP349 Fusio75 16 17000.00
RB12MP349 Fusio85 17 17000.00
SB12MP349 Fusio95 18 17000.00
TB12MP349 Fusio05 19 17000.00
UB12MP349 Fusi1n5 21 17000.00
VB12MP349 Fusi2n5 22 17000.00
WB12MP349 Fusi3n5 23 17000.00
XB12MP349 Fusi4n5 24 17000.00
YB12MP349 Fusi5n5 25 17000.00
ZB12MP349 Fusi6n5 26 17000.00
AC12MP349 Fusi7n5 27 17000.00
AD12MP349 Fusi8n5 28 17000.00
AE12MP349 Fusi9n5 29 17000.00
AF12MP349 Fusi0n5 30 17000.00
AG12MP349 Fus1on5 31 17000.00
AH12MP349 Fus2on5 32 17000.00
AI12MP349 Fus3on5 33 17000.00
AJ12MP349 Fus4on5 34 17000.00
AK12MP349 Fus5on5 35 17000.00
AL12MP349 Fus6on5 36 17000.00
AM12MP349 Fus7on5 37 17000.00
AN12MP349 Fus8on5 38 17000.00
AO12MP349 Fus9on5 39 17000.00
AP12MP349 Fus0on5 30 17000.00
AQ12MP349 Fu1ion5 40 17000.00
AR12MP349 Fu2ion5 41 17000.00
AS12MP349 Fu3ion5 42 17000.00
AT12MP349 Fu4ion5 43 17000.00
AU12MP349 Fu5ion5 44 17000.00
AV12MP349 Fu6ion5 45 17000.00
AW12MP349 Fu7ion5 46 17000.00
AX12MP349 Fu8ion5 47 17000.00
AY12MP349 Fu9ion5 48 17000.00
AZ12MP349 Fu0ion5 49 17000.00
AB22MP349 F1sion5 50 17000.00
AB32MP349 F2sion5 51 17000.00
AB42MP349 F3sion5 52 17000.00
AB52MP349 F4sion5 53 17000.00
AB62MP349 F5sion5 54 17000.00
AB72MP349 F6sion5 55 17000.00
AB82MP349 F7sion5 56 17000.00
AB92MP349 F8sion5 57 17000.00
AB02MP349 F9sion5 58 17000.00
AB11MP349 F0sion5 59 17000.00
AB13MP349 1usion5 60 17000.00
AB14MP349 2usion5 61 17000.00
AB15MP349 3usion5 62 17000.00
AB16MP349 4usion5 63 17000.00
AB17MP349 5usion5 64 17000.00
AB18MP349 6usion5 65 17000.00
AB19MP349 7usion5 66 17000.00
AB10MP349 8usion5 67 17000.00
AB12NP349 9usion5 68 17000.00
AB12OP349 0usion5 69 17000.00
AB12PP349 Fusio1 70 17000.00
AB12QP349 Fusio2 71 7000.00
AB12MP349 Fusio3 72 17000.00
AB12RP349 Fusio4 73 17000.00
AB12SP349 Fusio5 74 17000.00
AB12TP349 Fusio6 75 17000.00
AB12UP349 Fusio7 76 17000.00
AB12VP349 Fusio8 77 17000.00
AB12WP349 Fusio9 78 17000.00
AB12XP349 Fusio0 79 17000.00
AB12YP349 Fusi1 80 17000.00
AB12ZP349 Fusi2 81 17000.00
AB12MQ349 Fusi3 82 17000.00
AB12MR349 Fusi4 83 17000.00
AB12MS349 Fusi5 84 17000.00
AB12MT349 Fusi6 85 17000.00
AB12MU349 Fusi7 86 17000.00
AB12MV349 Fusi8 87 17000.00
AB12MW349 Fusi9 88 17000.00
AB12MX349 Fusi0 89 17000.00
AB12MY349 Fusion 90 17000.00
AB12MZ123 Fusio5 91 17000.00
AB12MP456 Fusin5 92 17000.00
AB12MP789 Fuson5 93 17000.00
AB12MP012 Fuion5 94 17000.00
AB12MP345 Fsion5 95 17000.00

Console:
 ./main
Too many records, stored first 50.


1 print records
2 print errors
3 quit
1
__________________________________________________
|    ID    |    Model    |  Stock  |    Price    |
--------------------------------------------------
|AB12MP349 |Fusion5      |       20|     17000.00|
|Zb1K2l456 |YeetCar      |       42|     12345.67|
|AB12MP349 |Fusion1      |        0|     17000.00|
|BB12MP349 |Fusion2      |        1|     17000.00|
|CB12MP349 |Fusion3      |        2|     17000.00|
|DB12MP349 |Fusion4      |        3|     17000.00|
|EB12MP349 |Fusion5      |        4|     17000.00|
|FB12MP349 |Fusion6      |        5|     17000.00|
|GB12MP349 |Fusion7      |        6|     17000.00|
|HB12MP349 |Fusion8      |        7|     17000.00|
|IB12MP349 |Fusion9      |        8|     17000.00|
|JB12MP349 |Fusion0      |        9|     17000.00|
|KB12MP349 |Fusio15      |       10|     17000.00|
|LB12MP349 |Fusio25      |       11|     17000.00|
|MB12MP349 |Fusio35      |       12|     17000.00|
|NB12MP349 |Fusio45      |       13|     17000.00|
|PB12MP349 |Fusio65      |       15|     17000.00|
|QB12MP349 |Fusio75      |       16|     17000.00|
|RB12MP349 |Fusio85      |       17|     17000.00|
|SB12MP349 |Fusio95      |       18|     17000.00|
|TB12MP349 |Fusio05      |       19|     17000.00|
|UB12MP349 |Fusi1n5      |       21|     17000.00|
|VB12MP349 |Fusi2n5      |       22|     17000.00|
|WB12MP349 |Fusi3n5      |       23|     17000.00|
|XB12MP349 |Fusi4n5      |       24|     17000.00|
|YB12MP349 |Fusi5n5      |       25|     17000.00|
|ZB12MP349 |Fusi6n5      |       26|     17000.00|
|AC12MP349 |Fusi7n5      |       27|     17000.00|
|AD12MP349 |Fusi8n5      |       28|     17000.00|
|AE12MP349 |Fusi9n5      |       29|     17000.00|
|AF12MP349 |Fusi0n5      |       30|     17000.00|
|AG12MP349 |Fus1on5      |       31|     17000.00|
|AH12MP349 |Fus2on5      |       32|     17000.00|
|AI12MP349 |Fus3on5      |       33|     17000.00|
|AJ12MP349 |Fus4on5      |       34|     17000.00|
|AK12MP349 |Fus5on5      |       35|     17000.00|
|AL12MP349 |Fus6on5      |       36|     17000.00|
|AM12MP349 |Fus7on5      |       37|     17000.00|
|AN12MP349 |Fus8on5      |       38|     17000.00|
|AP12MP349 |Fus0on5      |       30|     17000.00|
|AQ12MP349 |Fu1ion5      |       40|     17000.00|
|AR12MP349 |Fu2ion5      |       41|     17000.00|
|AS12MP349 |Fu3ion5      |       42|     17000.00|
|AT12MP349 |Fu4ion5      |       43|     17000.00|
|AU12MP349 |Fu5ion5      |       44|     17000.00|
|AV12MP349 |Fu6ion5      |       45|     17000.00|
|AW12MP349 |Fu7ion5      |       46|     17000.00|
|AX12MP349 |Fu8ion5      |       47|     17000.00|
|AY12MP349 |Fu9ion5      |       48|     17000.00|
|AZ12MP349 |Fu0ion5      |       49|     17000.00|
--------------------------------------------------



1 print records
2 print errors
3 quit
2
_______________________________________________________________________________________________
|    ID    |    Model    |  Stock  |    Price    |                Error Message               |
-----------------------------------------------------------------------------------------------
|35KMOP324 |Focus3       |       15|      4000.00|                       ID first char invalid|
|          |             |         |             |                      ID second char invalid|
|          |             |         |             |                           ID char 5 invalid|
|          |             |         |             |               Price must be 5000.00 or more|
|O2o#$%YoO |3%           |       -2|        -5.21|                       ID first char invalid|
|          |             |         |             |                      ID second char invalid|
|          |             |         |             |                           ID char 3 invalid|
|          |             |         |             |                           ID char 4 invalid|
|          |             |         |             |                           ID char 5 invalid|
|          |             |         |             |                           ID char 6 invalid|
|          |             |         |             |                           ID char 7 invalid|
|          |             |         |             |                           ID char 8 invalid|
|          |             |         |             |                           ID char 9 invalid|
|          |             |         |             |                        Model name too short|
|          |             |         |             |           Model name must start with letter|
|          |             |         |             |                        Model char 2 invalid|
|          |             |         |             |                  Quantity must be 0 or more|
|          |             |         |             |               Price must be 5000.00 or more|
|OB12MP349 |Fusio55      |       14|     17000.00|                       ID first char invalid|
|AO12MP349 |Fus9on5      |       39|     17000.00|                      ID second char invalid|
----------------------------------------------------------------------------------------------



1 print records
2 print errors
3 quit
a
Invalid option


1 print records
2 print errors
3 quit
4
Invalid option


1 print records
2 print errors
3 quit
3
*/