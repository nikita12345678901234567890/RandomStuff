#include <iostream>
using namespace std;

void Option1(int num, bool first = true, double value = 0);
void Option2(int num, int count = 1, double value = 0);

enum MENU
{
    Series1 = 1,
    Series2,
    Exit
};

int main()
{
    bool running = true;
    int input = 0;
    while (running)
    {
        cout << "\n\n1 Series1\n2 Series2\n3 Quit" << endl;
        cin >> input;

        switch (input)
        {
            case Series1:
                cout << "\nNumber of terms?" << endl;
                cin >> input;

                if (input <= 0)
                {
                    cout << "Invalid option, need number greater than 0" << endl;
                }
                else
                {
                    Option1(input);
                }
                break;

            case Series2:
                cout << "\nNumber of terms?" << endl;
                cin >> input;

                if (input <= 0)
                {
                    cout << "Invalid option, need number greater than 0" << endl;
                }
                else
                {
                    Option2(input);
                }
                break;

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

void Option1(int num, bool first, double value)
{
    if (first)
    {
        cout << "n=" << num << " ";
    }

    if (num <= 1)
    {
        return;
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

    if (count == num)
    {
        cout << "[" << count << "*" << count << "*" << count << "] = " << value + (count * count * count) << endl;
    }
    else
    {
        cout << "[" << count << "*" << count << "*" << count << "] + ";
        Option2(num, count + 1, value + (count * count * count));
    }
}

/*
1 Series1
2 Series2
3 Quit
1

Number of terms?
4
n=4 4/(4-1) + 3/(3-1) + 2 = 4.83333


1 Series1
2 Series2
3 Quit
2

Number of terms?
4
n=4 1 + [2*2*2] + [3*3*3] + [4*4*4] = 100


1 Series1
2 Series2
3 Quit
f
Invalid option


1 Series1
2 Series2
3 Quit
1

Number of terms?
f
Invalid option, need number greater than 0


1 Series1
2 Series2
3 Quit
Invalid option


1 Series1
2 Series2
3 Quit
2

Number of terms?
f
Invalid option, need number greater than 0


1 Series1
2 Series2
3 Quit
Invalid option


1 Series1
2 Series2
3 Quit
3
*/