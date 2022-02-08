#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

class distance_ // distance class
{
public:
    int km, m, cm; // Data members

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
        try
        {
            cout << "Enter km: ";
            cin >> km;
            cout << "Enter m: ";
            cin >> m;
            cout << "Enter cm: ";
            cin >> cm;
            if (km < 0 || m < 0 || cm < 0) // check for negative input
            {
                throw "Negative input";
            }

            carry_over(); // checking for any  carries
        }
        catch (const char *msg)
        {
            cout << msg << endl;
            cout << "Enter again: ";
            input();
        }
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
    int isEmpty() // function to check
    {
        if (km == 0 && m == 0 && cm == 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
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

        try
        {
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
                    throw "Negative value"; // throw exception
                }
            }
            return temp; // return the temporary object
        }
        catch (const char *msg)
        {
            cout << msg << endl;
            cout << "Result is negative" << endl;
            cout << "Returning distance 0" << endl;

            return distance_(0, 0, 0); // return null distance
        }
    }
};

ostream &operator<<(ostream &out, distance_ &d) // overloaded ostream operator
{
    out << d.km << " km, " << d.m << " m, " << d.cm << " cm" << endl;
    return out;
}
istream &operator>>(istream &in, distance_ &d) // overloaded istream operator
{
    try
    {
        cout << "Enter km: ";
        in >> d.km; // input km
        cout << "Enter m: ";
        in >> d.m; // input m
        cout << "Enter cm: ";
        in >> d.cm;                          // input cm
        if (d.km < 0 || d.m < 0 || d.cm < 0) // check for negative input
        {
            throw "Negative input";
        }
        d.carry_over(); // carry over function called
        return in;      // return the istream object
    }
    catch (const char *msg)
    {
        cout << msg << endl;
        cout << "Enter again: ";
        in >> d; // input again
    }
}
class city_pair
{
public:
    char city1[20], city2[20]; // Data members
    distance_ dist;            // distance class object

    city_pair() // Default constructor
    {
        strcpy(city1, " ");
        strcpy(city2, " ");
    }

    city_pair(char *_city1, char *_city2, distance_ _dist) // Parameterized constructor
    {
        strcpy(city1, _city1);
        strcpy(city2, _city2);
        dist = _dist;
    }

    void input() // Input function for the city_pair class
    {
        cout << "Enter city1: ";
        cin >> city1;
        cout << "Enter city2: ";
        cin >> city2;
        dist.input(); // input the distance
    }

    void display() // display function for the city_pair class
    {
        cout << city1 << " to " << city2 << ": ";
        dist.display();
    }

    void append_to_file()
    {
        ofstream outfile;
        outfile.open("city_pairs.txt", ios::app | ios::binary);
        outfile.write((char *)this, sizeof(*this));
        outfile.close();
    }
};

city_pair find_city_pair(char *city1, char *city2)
{
    ifstream infile;
    infile.open("city_pairs.txt", ios::in | ios::binary);
    city_pair temp;
    try
    {
        while (infile.read((char *)&temp, sizeof(temp)))
        {
            if ((strcmp(temp.city1, city1) == 0 && strcmp(temp.city2, city2) == 0) ||
                (strcmp(temp.city1, city2) == 0 && strcmp(temp.city2, city1) == 0))
            {
                infile.close();
                return temp;
            }
        }
        infile.close();
        throw "No such city pair found";
    }
    catch (const char *msg)
    {
        cout << msg << endl;
        city_pair empty_pair;
        return empty_pair;
    }
}

void distance_via_city()
{
    cout << "Enter starting city: ";
    char start[20];
    cin >> start;
    cout << "Enter the city travelling via: ";
    char via[20];
    cin >> via;
    cout << "Enter destination city: ";
    char dest[20];
    cin >> dest;
    try
    {
        city_pair temp1 = find_city_pair(start, via);
        city_pair temp2 = find_city_pair(via, dest);
        if (temp1.dist.isEmpty() || temp2.dist.isEmpty())
        {
            throw "No such city pair found";
        }

        distance_ dist = temp1.dist + temp2.dist;
        cout << "Distance between " << start << " and " << dest << " via " << via
             << " is : ";
        dist.display();
    }
    catch (const char *msg)
    {
        cout << msg << endl;
        cout << "Do you want to try again?" << endl;
        char ch;
        cin >> ch;
        if (ch == 'y')
        {
            distance_via_city();
        }
    }
}

void find_city_pair()
{
    try
    {
        cout << "Enter the city pair to be searched: ";
        char city1[20], city2[20];
        cin >> city1 >> city2;
        city_pair temp = find_city_pair(city1, city2);
        if (temp.dist.km == 0)
        {
            throw "No such city pair found";
        }
        else
        {
            cout << "City pair found" << endl;
            temp.display();
        }
    }
    catch (const char *msg)
    {
        cout << msg << endl;
        cout << "Do you want to try again?" << endl;
        char ch;
        cin >> ch;
        if (ch == 'y')
        {
            find_city_pair();
        }
    }
}

void print_all_stored_cities()
{
    ifstream infile;
    infile.open("city_pairs.txt", ios::in | ios::binary);
    city_pair temp;
    while (infile.read((char *)&temp, sizeof(temp)))
    {
        cout << temp.city1 << " " << temp.city2 << endl;
    }
    infile.close();
}

void city_operations()
{
    int n;
    cout << "Enter number of city pairs: ";
    cin >> n;
    city_pair *cities = new city_pair[n]; // create an array of city_pair objects
    for (int i = 0; i < n; i++)
    {
        cities[i].input();          // input the cities and distance
        cities[i].append_to_file(); // append to file
    }
    cout << "City pairs are stored in city_pairs.txt" << endl;
    cout << "Display all stored cities? (y/n)" << endl;
    char ch;
    cin >> ch;
    if (ch == 'y')
    {
        print_all_stored_cities();
    }
    int choice;
    do
    {
        cout << "-----CITY-MENU-----" << endl;
        cout << "1. Find distance between two cities" << endl;
        cout << "2. Find distance between two cities via another city" << endl;
        cout << "3. Print all stored cities" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
            find_city_pair();
            break;
        case 2:
            distance_via_city();
            break;
        case 3:
            print_all_stored_cities();
            break;
        case 4:
            cout << "Exiting..." << endl;
            return;
        default:
            cout << "Invalid choice" << endl;
            break;
        }
    } while (choice != '4');
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
        cout << "5. City Operations" << endl;
        cout << "6. Exit" << endl; // menu
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
            city_operations();
            break;

        case 6:
            cout << "Exitting" << endl;
            return 0;
            break;
        }
    } while (1);
}