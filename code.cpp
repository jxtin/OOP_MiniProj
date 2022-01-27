#include <iostream>
using namespace std;

class distance_ // distance class
{
private:
    int km, m, cm; // Data members

public:
    distance_() // Default constructor
    {
        km = 0;
        m = 0;
        cm = 0;
    }

    distance_(int _km, int _m, int _cm) // Parameterized constructor
    {
        km = _km;
        m = _m;
        cm = _cm;
        carry_over(); // carry over function called
    }

    // kinda useless since overloaded istream operator
    void input() // Input function for distance class
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
        temp.carry_over();   // carry over function called
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
    cout << "Enter km: ";
    in >> d.km; // input km
    cout << "Enter m: ";
    in >> d.m; // input m
    cout << "Enter cm: ";
    in >> d.cm;                          // input cm
    if (d.km < 0 || d.m < 0 || d.cm < 0) // check for negative input
    {
        cout << "Invalid input" << endl;
        return in;
    }
    d.carry_over(); // carry over function called
    return in;      // return the istream object
}

int main()
{
    cout << "\033[1;31mCode Started!" << endl;
    distance_ d1(1, 2999, 305), d2(2, 4800, 403); // create two distance objects using parameterized constructor
    cout << "d1 = ";
    d1.display(); // display d1 using function (deprecated since overloaded ostream operator)
    cout << "d2 = ";
    d2.display();           // display d2 using function (deprecated since overloaded ostream operator)
    distance_ d3 = d1 + d2; // add d1 and d2 using + operator
    d3.display();           // display d3 using function (deprecated since overloaded ostream operator)

    // array of distance_
    distance_ d[10]; // create an array of distance_
    int choice;
    int i = 0;
    distance_ result;
    int d1_choice;
    int d2_choice;

    do
    {
        cout << "-------------------Menu-------------------" << endl; // menu
        cout << "1. Input distance (stored in array) " << endl;       // menu
        cout << "2. Display distance" << endl;                        // menu
        cout << "3. Add distances" << endl;                           // menu
        cout << "4. Subtract distances" << endl;                      // menu
        cout << "5. Exit" << endl;                                    // menu
        cin >> choice;
        switch (choice)
        {
        case 1:
            cin >> d[i]; // input distance
            i++;         // increment index
            break;
        case 2:
            for (int j = 0; j < i; j++) // display all stored distances
            {
                cout << "Distance " << j + 1 << " = ";
                cout << d[j] << endl;
            }
            break;
        case 3:
            cout << "which distances do you want to add? " << endl; // ask for two distances
            cout << "choose distance 1" << endl;
            cin >> d1_choice;
            cout << "Chosen distance 1 = " << d[d1_choice - 1] << endl;
            cout << "choose distance 2" << endl;
            cin >> d2_choice;
            cout << "Chosen distance 2 = " << d[d2_choice - 1] << endl;
            result = d[d1_choice - 1] + d[d2_choice - 1]; // add the two distances
            cout << "Result = " << result << endl;
            break;

        case 4:
            cout << "which distances do you want to subtract? " << endl; // ask for two distances
            cout << "choose distance 1" << endl;
            cin >> d1_choice;
            cout << "Chosen distance 1 = " << d[d1_choice - 1] << endl;
            cout << "choose distance 2" << endl;
            cin >> d2_choice;
            cout << "Chosen distance 2 = " << d[d2_choice - 1] << endl;
            result = d[d1_choice - 1] - d[d2_choice - 1]; // subtract the two distances
            cout << "Result = " << result << endl;
            break;
        case 5:
            cout << "Exitting" << endl;
            return 0;
            break;
        }
    } while (1);
}