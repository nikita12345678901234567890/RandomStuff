#include <iostream>
using namespace std;

void Option1(int num, bool first = true, double value = 0);
void Option2(int num, int count = 1, double value = 0);

enum MENU
{
    PRINT_VALID = 1,
    PRINT_INVALID,
    SEARCH,
    QUIT
};

const int MAX_RECORDS = 50;
const float SEARCH_PERCENT = 0.15;

void ReadFile(Record records[], int& numRecords);
int checkValid(Record record, string errors[]);
bool isAlphaNum(char c);
void PrintRecords(Record records[], int numRecords);
void PrintInvalid();
int Search(string value, Record records[], int numRecords, Record results[]);
int Search(int price, Record records[], int numREcords, Record results[]);
string ToUpper(string input);
bool isNumber(string input);

int main()
{
    bool running = true;
    int input = 0;
    while (running)
    {
        cout << "\n\n1 Series1\n2 Series2\n3 Quit" << endl;
        cin >> input;

    if (newWorks)
    {
        int numRecords = 0;
        ReadFile(records, numRecords);

        bool menu = true;
        int choice;
        while (menu)
        {
            cout << "\n\n"
                << PRINT_VALID << " records\n"
                << PRINT_INVALID << " errors\n"
                << SEARCH << " search\n"
                << QUIT << " quit" << endl;

            cin >> choice;

            string input = "";

            int numResults = 0;

            switch (choice)
            {
            case PRINT_VALID:
                PrintRecords(records, numRecords);
                break;

            case PRINT_INVALID:
                PrintInvalid();
                break;

            case QUIT:
                menu = false;
                break;

            case SEARCH:
                cout << "\n1 search by ID/model\n2 search by price" << endl;

                cin >> choice;

                switch (choice)
                {
                case 1:
                    cout << "What do you want to search for?" << endl;
                    cin >> input;

                    numResults = Search(input, records, numRecords, searchResult);

                    if (numResults == 0)
                    {
                        cout << "No matches" << endl;
                    }
                    else
                    {
                        PrintRecords(searchResult, numResults);
                    }
                    break;

                case 2:
                    cout << "Enter price" << endl;
                    cin >> input;

                    if (isNumber(input))
                    {
                        numResults = Search(stoi(input), records, numRecords, searchResult);

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
                    break;

                default:
                    cout << "Invalid choice" << endl;
                    break;
                }

            case Exit:
                running = false;
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

void ReadFile(Record records[], int& numRecords)
{
    if (first)
    {
        cout << "n=" << num << " ";
    }

    bool ErrorHappened = false;

    ErrorFile << std::setprecision(2) << std::fixed;

    while (recordFile && numRecords < MAX_RECORDS && filesWork)
    {
        //reading record
        Record temp;
        recordFile >> temp.ID;
        recordFile >> temp.Model;
        recordFile >> temp.Quantity;
        recordFile >> temp.Price;

        temp.ID = ToUpper(temp.ID);
        temp.Model = ToUpper(temp.Model);

        //checking validity
        string errorMessages[15];
        //This^ is an array of all the error messages for a record.
        //15 is the maximum number of errors one record could have, plus a few just in case.
        int numErrors = checkValid(temp, errorMessages);
        if (numErrors == 0)
        {
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
                << std::setw(13) << temp.Price << "|"
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

int checkValid(Record record, string messages[])
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

    if (num == 2)
    {
        cout << num << " = " << value + 2 << endl;
    }
    else
    {
        cout << num << "/(" << num << "-1) + ";
        value += (double)num / (num - 1);
    }

    Option1(num - 1, false, value);
}

void Option2(int num, int count, double value)
{
    if (count == 1)
    {
        cout << "n=" << num << " 1 + ";
        value += 1;
        count++;
    }

void PrintRecords(Record records[], int numRecords)
{
    //printing header
    cout << std::setprecision(2)
        << setfill('_') << setw(51) << "\n"
        << "|    ID    |    Model    |  Stock  |    Price    |\n"
        << setfill('-') << setw(51) << "\n";

    cout << std::setfill(' ') << std::fixed;
    for (int i = 0; i < numRecords; i++)
    {
        //printing the values
        cout << "|"
            << std::setw(10) << std::left << records[i].ID << "|"
            << std::setw(13) << records[i].Model << "|"
            << std::setw(9) << std::right << records[i].Quantity << "|"
            << std::setw(13) << records[i].Price << "|" << "\n";
    }
    else
    {
        cout << "[" << count << "*" << count << "*" << count << "] + ";
        Option2(num, count + 1, value + (count * count * count));
    }
}

int Search(string value, Record records[], int numRecords, Record results[])
{
    int numResults = 0;

    value = ToUpper(value);

    for (int i = 0; i < numRecords; i++)
    {
        if (records[i].ID.find(value) != string::npos || records[i].Model.find(value) != string::npos)
        {
            results[numResults] = records[i];
            numResults++;
        }
    }

    return numResults;
}
int Search(int price, Record records[], int numRecords, Record results[])
{
    int numResults = 0;

    double percent = price * SEARCH_PERCENT;

    cout << "Searching within " << SEARCH_PERCENT * 100 << "%, from " << price - percent << " to " << price + percent << endl;

    for (int i = 0; i < numRecords; i++)
    {
        if (records[i].Price > price - percent && records[i].Price < price + percent)
        {
            results[numResults] = records[i];
            numResults++;
        }
    }


string ToUpper(string input)
{
    string result = "";
    for (int i = 0; i < input.size(); i++)
    {
        result += toupper(input[i]);
    }

    return result;
}


1 Series1
2 Series2
3 Quit
1

/*
./main
Too many records, stored first 50.

1 Series1
2 Series2
3 Quit
Invalid option

1 print records
2 print errors
3 search
4 quit
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
3 search
4 quit
2

1 print records
2 print errors
3 search
4 quit
3

1 search by ID/model
2 search by price
1
What do you want to search for?
a
__________________________________________________
|    ID    |    Model    |  Stock  |    Price    |
--------------------------------------------------
|AB12MP349 |Fusion5      |       20|     17000.00|
|Zb1K2l456 |YeetCar      |       42|     12345.67|
|AB12MP349 |Fusion1      |        0|     17000.00|
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
3 search
4 quit
3

1 search by ID/model
2 search by price
1
What do you want to search for?
u
__________________________________________________
|    ID    |    Model    |  Stock  |    Price    |
--------------------------------------------------
|AB12MP349 |Fusion5      |       20|     17000.00|
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
3 search
4 quit
3

1 search by ID/model
2 search by price
2
Enter price
0
No matches


1 print records
2 print errors
3 search
4 quit
3

1 search by ID/model
2 search by price
2
Enter price
16000
__________________________________________________
|    ID    |    Model    |  Stock  |    Price    |
--------------------------------------------------
|AB12MP349 |Fusion5      |       20|     17000.00|
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
3 search
4 quit
4
*/