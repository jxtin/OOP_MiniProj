#include <Windows.h> // For Windows only, to add color
#include <iostream>
using namespace std;

class distance_ // class definition

{
private:
    int km, m, cm; // private data members

public:
    distance_() // default constructor
    {
        km = 0;
        m = 0;
        cm = 0;
    }

    distance_(int _km, int _m, int _cm) // parameterised constructor
    {
        km = _km;
        m = _m;
        cm = _cm;
        carry_over();
    }

    // kinda useless since overloaded istream operator
    void input() // input function for the class
    {
        cout << "Enter km: ";
        cin >> km;
        cout << "Enter m: ";
        cin >> m;
        cout << "Enter cm: ";
        cin >> cm;
        if (km < 0 || m < 0 || cm < 0) // check for negative input
        {
            cout << "Invalid input" << endl;
            return;
        }

        carry_over(); // checking for any  carries
    }

    void carry_over() // function to check for carries to avoid overflowing (m<1000, cm<100)
    {

        /*
        this  function  checks  for  carries  in  the  data  members  and  adjusts  them  accordingly
        100cm = 1m
        110cm = 1m, 10cm
        1000m = 1km
        1100m = 1km, 10m
        110010cm = 1km, 100m, 10cm
         */
        if (cm >= 100)
        {
            m += cm / 100;
            cm = cm % 100;
        }
        if (m >= 1000)
        {
            km += m / 1000;
            m = m % 1000;
        }
    }

    // kinda useless since overloaded ostream operator
    void display() // display function for the distance class
    {
        cout << km << " km, " << m << " m, " << cm << " cm" << endl;
    }

    friend ostream &operator<<(ostream &out, distance_ &d); // overloaded ostream operator
    friend istream &operator>>(istream &in, distance_ &d);  // overloaded istream operator

    distance_ operator+(distance_ d) // overload + operator
    {
        distance_ temp;      // create a temporary object
        temp.km = km + d.km; // add the km
        temp.m = m + d.m;    // add the m
        temp.cm = cm + d.cm; // add the cm
        temp.carry_over();   // carry over the values
        return temp;         // return the temporary object
    }
    distance_ operator-(distance_ d) // overload - operator
    {
        distance_ temp;      // create a temporary object
        temp.km = km - d.km; // subtract the km
        temp.m = m - d.m;    // subtract the m
        temp.cm = cm - d.cm; // subtract the cm
        temp.carry_over();   // carry over the values

        while (temp.cm < 0) // if cm is negative
        {
            temp.m--;       // decrement m (borrow)
            temp.cm += 100; // add 100 to cm
        }
        while (temp.m < 0) // check for negative values
        {
            temp.km--;      // decrement km (borrow)
            temp.m += 1000; // 1000m = 1km
            if (temp.km < 0)
            {
                cout << "Invalid input" << endl;
                cout << "Result is negative" << endl;
                cout << "Returning distance 0" << endl;
               return distance_(0, 0, 0); // if km is negative, return null distance
            }
        }
        return temp; // return the temporary object
    }
};

ostream &operator<<(ostream &out, distance_ &d) // overloaded ostream operator
{
    out << d.km << " km, " << d.m << " m, " << d.cm << " cm" << endl;
    return out;
}
istream &operator>>(istream &in, distance_ &d) // overloaded istream operator
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);                          // To add color
    SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY);  // To add color
    cout << "Enter km: ";                                                // input
    SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY); // To add color
    in >> d.km;                                                          // input
    SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY);  // To add color
    cout << "Enter m: ";                                                 // input
    SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY); // To add color
    in >> d.m;                                                           // input
    SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY);  // To add color
    cout << "Enter cm: ";                                                // input
    SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY); // To add color
    in >> d.cm;                                                          // input
    if (d.km < 0 || d.m < 0 || d.cm < 0)                                 // check for negative input
    {
        SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY); // To add color
        cout << "Invalid input" << endl;                                   // output
    }
    d.carry_over(); // carry over the values
    return in;      // return the input
}

int main()
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);                        // To add color
    SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY); // To add color
    distance_ d1(1, 4, 6), d2(2, 7, 4);                                // create two objects with parameterised constructor
    cout << "d1 = ";
    d1.display(); // display d1 using function (deprecated since overloaded ostream operator)
    cout << "d2 = ";
    d2.display();           // display d2 (deprecated since overloaded ostream operator)
    distance_ d3 = d1 + d2; // add d1 and d2
    cout << "d3 = ";
    d3.display(); // display d3 (deprecated since overloaded ostream operator)

    // array of distance_
    distance_ d[10];  // array of distance_
    int choice;       // user choice
    int i = 0;        // index of the item in array d
    distance_ result; // result of the addition
    int d1_choice;
    int d2_choice;
    do
    {
        SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY); // To add color
        cout << "\n-------------------Menu-------------------\n"
             << endl;                                                        // menu
        SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY); // To add color
        cout << "1. Input distance (stored in array) " << endl;              // menu
        cout << "2. Display distance" << endl;                               // menu
        cout << "3. Add distances" << endl;                                  // menu
        cout << "4. Subtract distances" << endl;                             // menu
        cout << "5. Exit" << endl;                                           // menu
        cin >> choice;
        switch (choice) // switch case
        {
        case 1:
            cin >> d[i]; // input distance
            i++;         // increment index
            break;
        case 2:
            SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY); // To add color
            for (int j = 0; j < i; j++)                                        // to display all the items
            {
                cout << "Distance " << j + 1 << " = ";
                cout << d[j] << endl;
            }
            break;
        case 3:
            SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY);  // To add color
            cout << "which distances do you want to add? " << endl;              // Ask user to input the distances
            SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY);  // To add color
            cout << "choose distance 1" << endl;                                 // Ask user to input the distances
            SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY); // To add color
            cin >> d1_choice;
            SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY); // To add color
            cout << "Chosen distance 1 = " << d[d1_choice - 1] << endl;
            SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY); // To add color
            cout << "choose distance 2" << endl;
            SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY); // To add color
            cin >> d2_choice;
            SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY); // To add color
            cout << "Chosen distance 2 = " << d[d2_choice - 1] << endl;
            result = d[d1_choice - 1] + d[d2_choice - 1];                      // add the two distances
            SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY); // To add color
            cout << "\nResult = " << result << endl;                           // display the result
            break;
        case 4:
            SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY);  // To add color
            cout << "which distances do you want to subtract? " << endl;              // Ask user to input the distances
            SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY);  // To add color
            cout << "choose distance 1" << endl;                                 // Ask user to input the distances
            SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY); // To add color
            cin >> d1_choice;
            SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY); // To add color
            cout << "Chosen distance 1 = " << d[d1_choice - 1] << endl;
            SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY); // To add color
            cout << "choose distance 2" << endl;
            SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY); // To add color
            cin >> d2_choice;
            SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY); // To add color
            cout << "Chosen distance 2 = " << d[d2_choice - 1] << endl;
            result = d[d1_choice - 1] - d[d2_choice - 1];                      // add the two distances
            SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY); // To add color
            cout << "\nResult = " << result << endl;                           // display the result
            break;

        case 5:
            SetConsoleTextAttribute(h, FOREGROUND_RED); // To add color
            cout << "Exitting" << endl;                 // exit
            return 0;                                   // return
            break;
        }
    } while (1);
}
