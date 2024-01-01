#include <iostream>
#include <string>
#include <conio.h>
#include <iomanip>
#include <Windows.h>
#include <chrono>
#include <mysql.h> //libmysql
using namespace std;

struct Student
{
    string id;
    string name;
    int age;
    string gender;
    double height;
    double weight;
    double bmi;
    string status;

};

int qstate;
MYSQL* conn;
MYSQL_ROW row;
MYSQL_RES* res;

Student* stud = new Student[10000];
Student* stud2 = new Student[10000];

class db_response
{
public:
    static void ConnectionFunction()
    {
        conn = mysql_init(0);
        if (conn)
            cout << "Database Connected" << endl;
        else
            cout << "Failed To Connect!" << endl;

        conn = mysql_real_connect(conn, "localhost", "root", "", "algorithm analysis", 3306, NULL, 0);
        if (conn)
            cout << "Database Connected To MySql" << endl;
        else
            cout << "Failed To Connect!" << endl;
    }
};

void loadingBar()
{
    // 0 - black background,
    // A - Green Foreground
    //system("color 0D");
    cout << "\u001b[40m\u001b[35m";

    // Initialize char for printing
    // loading bar
    char a = 177, b = 219;

    printf("\n\n\t\t\t\t\t The Data are being sorted ...\n\n");
    printf("\t\t\t\t\t");

    // Print initial loading bar
    for (int i = 0; i < 26; i++)
        printf("%c", a);

    // Set the cursor again starting
    // point of loading bar
    printf("\r");
    printf("\t\t\t\t\t");

    // Print loading bar progress
    for (int i = 0; i < 30; i++) {
        printf("%c", b);

        // Sleep for 1 second
        Sleep(500);
    }
}

void display(Student* studArr) {

    //studArr[0].id = studArr[0].id.substr(0, studArr[0].id.size() - 1);
    for (int i = 0; i < 100; i++) {

        cout << setw(8) << left << studArr[i].id << setw(50) << left << studArr[i].name << setw(8) << left << studArr[i].age << setw(8) << left << studArr[i].gender << setw(8) << left << studArr[i].height << setw(8) << left << studArr[i].weight << setw(8) << left << setprecision(4) << studArr[i].bmi << setw(8) << left << studArr[i].status << endl;
    }

}

void Category(Student* studArr)
{
    for (int i = 0; i < 10000; i++) {

        if (studArr[i].bmi < 18.5)
        {
            studArr[i].status = "UNDERWEIGHT";
        }
        else if (studArr[i].bmi < 25)
        {
            studArr[i].status = "NORMAL";
        }
        else if (studArr[i].bmi < 30)
        {
            studArr[i].status = "OVERWEIGHT";
        }
        else
        {
            studArr[i].status = "OBESE";
        }
    }
}

void CalculateBMI(Student* studArr)
{
    for (int i = 0; i < 10000; i++) {
        studArr[i].bmi = studArr[i].weight / (studArr[i].height * studArr[i].height);
    }
    Category(studArr);
    // display(studArr);
}

int insertionSort(Student* studArr)
{

    int i, j, swap = 0;
    Student key;

    for (i = 1; i < 10000; i++)
    {
        key = studArr[i];
        j = i - 1;

        while (j >= 0 && studArr[j].id > key.id)
        {
            studArr[j + 1] = studArr[j];
            swap++;
            j = j - 1;
        }
        studArr[j + 1] = key;
    }

    return swap;
}

int merge(Student* stud, int low, int mid, int high) {

    int i, j, k, nl, nr;
    int swapl = 0, swapr = 0, swap;

    //size of left and right sub-arrays
    nl = mid - low + 1;
    nr = high - mid;

    Student* leftArr = new Student[nl];
    Student* rightArr = new Student[nr];

    //fill left and right sub-arrays
    for (i = 0; i < nl; i++)
        leftArr[i] = stud[low + i];

    for (j = 0; j < nr; j++)
        rightArr[j] = stud[mid + 1 + j];

    i = 0;
    j = 0;
    k = low;

    //marge temp arrays to real array
    while (i < nl && j < nr) {
        if (leftArr[i].id <= rightArr[j].id) {
            stud[k] = leftArr[i];
            swapl++;
            i++;
        }
        else {
            stud[k] = rightArr[j];
            swapr++;
            j++;
        }
        k++;
    }
    while (i < nl) {       //extra element in left array
        stud[k] = leftArr[i];
        swapl++;
        i++;
        k++;
    }

    while (j < nr) {     //extra element in right array
        stud[k] = rightArr[j];
        swapr++;
        j++;
        k++;
    }
    return swap = swapl + swapr;
   cout << "Number of Swapped for Merge Sort : " << swap << endl; 
}

int mergeSort(Student* stud, int low, int high) {

    int swap;
    if (low < high) {
        int mid = low + (high - low) / 2;
        // Sort first and second arrays
        mergeSort(stud, low, mid);
        mergeSort(stud, mid + 1, high);
        swap = merge(stud, low, mid, high);
        return swap;
    }

}

int sentinelSearch(Student* studArr, string target)
{
    // Last element of the array
    Student last = studArr[9999];

    // Element to be searchd is placed at the last index
    studArr[9999].id = target;
    int i = 0;

    while (studArr[i].id != target) {
        i++;
    }

    // Put the last element back
    studArr[9999] = last;

    if ((i < 9999) || (studArr[9999].id == target)) {

        // return target
        return i;
    }

    else
        return -1;

}

int binarySearch(Student* studArr, int l, int r, string x)
{
    //generateTarget();

    if (r >= l) {
        int mid = l + (r - l) / 2;

        // If the element is present at the middle
        // itself
        if (studArr[mid].id == x)
            return mid;

        // If element is smaller than mid, then
        // it can only be present in left subarray
        if (studArr[mid].id > x)
            return binarySearch(studArr, l, mid - 1, x);

        // Else the element can only be present
        // in right subarray
        return binarySearch(studArr, mid + 1, r, x);
    }

    // We reach here when element is not
    // present in array
    return -1;

}

string* generateTarget() {

    static string target[100];
    srand(time(0));
    int tmp = rand() % 999999;
    srand(tmp);
    for (int i = 0; i < 100; i++) {
        target[i] = "S" + to_string(rand() % 20000);
        // cout << target[i] << endl;
    }
    return target;
}

int main()
{
    int i = 0;
    int swapM;
    int swapIS;
    int resultBinary[100];
    int resultSentinel[100];
    string* wanted;

    system("cls");
    system("title My Project");
    db_response::ConnectionFunction();
    system("cls");
    // Using time point and system_clock
    std::chrono::time_point<std::chrono::system_clock> start, end;

    cout << "\t\t\t\t\t--- Algorithm Analysis Project --- " << endl;
    cout << "\t\tThis will take a while, we hope that you can sabr,because sabr is half oh the iman :)" << endl;
    cout << "\t\t\t\t\t          HAPPY NEW YEAR ! " << endl;

    qstate = mysql_query(conn, "select * from student order by rand() ");

    if (!qstate)
    {
        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            stud[i].id = row[0];
            stud[i].name = row[1];
            stud[i].age = stoi(row[2]);
            stud[i].gender = row[3];
            stud[i].height = stod(row[4]);
            stud[i].weight = stod(row[5]);
            //stud[i].bmi = stod(row[6]);
            //stud[i].status = row[7];

            stud2[i].id = row[0];
            stud2[i].name = row[1];
            stud2[i].age = stoi(row[2]);
            stud2[i].gender = row[3];
            stud2[i].height = stod(row[4]);
            stud2[i].weight = stod(row[5]);
            //stud2[i].bmi = stod(row[6]);
            //stud2[i].status = row[7];
            i++;
        }

    }

    wanted = generateTarget();

    CalculateBMI(stud);

    cout << "\n";
    start = chrono::system_clock::now();
    swapIS = insertionSort(stud);
    end = chrono::system_clock::now();
    chrono::duration<double> time_span = chrono::duration_cast<chrono::microseconds>(end - start);
    loadingBar();
    cout << "\u001b[0m";
    system("cls");
    display(stud);
    cout << "Number of Swapped for Insertion Sort : " << swapIS << endl;
    cout << "Running Time for Insertion Sort : " << time_span.count() << " microseconds" << endl;

    cout << "\n";
    start = chrono::system_clock::now();
    swapM = mergeSort(stud2, 0, 9999);
    end = chrono::system_clock::now();
    time_span = chrono::duration_cast<chrono::microseconds>(end - start);
    //system("cls");
    display(stud);
    cout << "Number of Swapped for Merge Sort : " << swapM << endl;
    cout << "Running Time for Merge Sort : " << time_span.count() << " microseconds" << endl;

    cout << "\n";
    start = chrono::system_clock::now();
    for (int i = 0; i < 100; i++) {
        resultBinary[i] = binarySearch(stud, 0, 9999, wanted[i]);
    }
    end = chrono::system_clock::now();
    time_span = chrono::duration_cast<chrono::microseconds>(end - start);

    cout << "\n----- Binary Search Result ----" << endl;
    for (int i = 0; i < 100; i++) {

        (resultBinary[i] == -1) ? cout << "" : cout << "Element is present at index " << resultBinary[i] << endl;
    }
    cout << "Running Time for Binary Search : " << time_span.count() << " microseconds" << endl;

    cout << "\n";
    start = chrono::system_clock::now();
    for (int i = 0; i < 100; i++) {

        resultSentinel[i] = sentinelSearch(stud, wanted[i]);

    }
    end = chrono::system_clock::now();
    time_span = chrono::duration_cast<chrono::microseconds>(end - start);

    cout << "\n----- Sentinel Search Result -----" << endl;
    for (int i = 0; i < 100; i++) {

        (resultSentinel[i] == -1) ? cout << "" : cout << "Element is present at index " << resultSentinel[i] << endl;

    }
    cout << "Running Time for Sentinel Search : " << time_span.count() << " microseconds" << endl;


    return 0;
}