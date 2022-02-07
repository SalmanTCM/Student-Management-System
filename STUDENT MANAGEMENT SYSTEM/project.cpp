/*
PROBLEMS:
1. FIX ISSUES WITH SAVING CHANGES TO FILE.
2. CLEAR SCREEN? clrscr()?
3. fseek(); SEEK LINE #1 OF FILE AND INPUT TOTAL NUMBER OF PATIENTS THRERE BEFORE EXITING THE PROGRAM.
4. [FIXED] SHOULD int main::total_patient BE GLOBAL? (fixed! using references.)
5. [FIXED] KEEPING COUNT OF TOTAL NUMBER OF PATIENTS. (SEE 4)
*/



#include<iostream>
#include<cstring>
#include<fstream>
#include<stdio.h>
#include<fstream>
#include<stdlib.h>
//#include<iomanip>
//#include<conio.h>
#define CAP 200 //MAX PATIENT CAPACITY FOR THE HOSPITAL.
using namespace std;
class student{
    string name;
    string last_name; //CURRENTLY NOT IMPLEMENTED.
    int age;
    string roll;
    float cgpa; //HOW BEST TO IMPLEMENT THIS FEATURE?
public:
    void set_name(string name){this->name=name;}
    void set_age(int age){this->age=age;}
    void set_roll(string roll){this->roll=roll;}
    void set_cgpa(float cgpa){this->cgpa=cgpa;}
    string get_name(){return name;}
    int get_age(){return age;}
    string get_roll(){return roll;}
    float get_cgpa(){return cgpa;}
};
fstream file("data.txt", ios::in|ios::out|ios::app);
void load_records(student[], int&);
void add_record(student[], int&);
void find_record(student[], int&);
void modify_record(student[], int&);
void delete_record(student[], int&);
void list_records(student[], int&);
void exit_program(student[], int&);
int CHANGES=0;//GLOBAL VARIABLE TO COUNT THE NUMBER OF CHANGES MADE.
int main()
{
    if(file.is_open())
    {
        student ara[CAP];
        int total_student;
        file >> total_student;
        //patient ara[total_patient];
        load_records(ara, total_student);
        char choice;
        while(1)
        {
            cout << "\n\n";
            cout << "\t\t     STUDENT MANAGEMENT SYSTEM";
            cout << "\n\n";
            cout << "\n\t\t\t       Main Menu";
            cout << "\n\t\t\t======================";
            cout << "\n \t\t\t  1. Add New Student";//DONE.
            cout << "\n \t\t\t  2. Find Record";//DONE.
            cout << "\n \t\t\t  3. Edit Record";//DONE.
            cout << "\n \t\t\t  4. Delete Record"; //INEFFICIENT. ALSO, CAN'T SAVE CHANGES TO FILE.
            cout << "\n \t\t\t  5. List All Records";
            cout << "\n \t\t\t  6. Exit Program";   //PROBLEMS; STUCK.
            cout << "\n\t\t\t======================";
            cout << "\n\n";
            cout << "\t\t\t Select Your Choice: ";
            cin  >> choice;
            cout << "\n\n";

            switch(choice)
            {
                case '1' :
                    system("cls");
                    add_record(ara, total_student);
                    break;
                case '2' :
                    system("cls");
                    find_record(ara, total_student);
                    break;
                case '3' :
                    system("cls");
                    modify_record(ara, total_student);
                    break;
                case '4' :
                    system("cls");
                    delete_record(ara, total_student);
                case '5':
                    system("cls");
                    list_records(ara, total_student);
                    break;
                case '6' :
                    system("cls");
                    exit_program(ara, total_student);
                    break;
                default  :
                    system("cls");
                    cout<<"(!)ERROR: Invalid selection."<<endl;
                    system("pause");
                    system("cls");
            }
        }
        return 0;
    }
    else
    {
        cout<<"(!)ERROR: Failed to open file: data.txt"<<endl;
        return 0;
    }
}
void load_records(student ara[], int &n)
{
    string temp_name;
    int temp_age;
    string temp_roll;
    float temp_cgpa;
    for(int i=0; i<n; i++)
    {
        file >> temp_name >> temp_age >> temp_roll >> temp_cgpa;
        ara[i].set_name(temp_name);
        ara[i].set_age(temp_age);
        ara[i].set_roll(temp_roll);
        ara[i].set_cgpa(temp_cgpa);
    }
}
void add_record(student ara[], int &n)
{
    if(n<CAP)
    {
        string temp_name;
        int temp_age;
        string temp_roll;
        float temp_cgpa;
        cout<< "\nEnter student name: ";
        cin >> temp_name;
        cout<<endl;
        cout<< "Enter student age: ";
        cin >> temp_age;
        cout<<endl;
        cout<< "Enter roll no: ";
        cin >> temp_roll;
        cout<<endl;
        cout<< "Enter CGPA of student : ";
        cin >> temp_cgpa;
        cout<<endl;

        ara[n].set_name(temp_name);
        ara[n].set_age(temp_age);
        ara[n].set_roll(temp_roll);
        ara[n].set_cgpa(temp_cgpa);
        n++;
        CHANGES++;
        system("cls");
        cout<<"\n(!)NOTIFICATION: Records added."<<endl;
    }
    else
    {
        system("cls");
        cout<<"Maximum number of student reached."<<endl;
    }
}
void find_record(student ara[], int &n)
{
    string temp_name;
    int hits=0;
    cout<<"Enter student name: ";
    cin>>temp_name;
    system("cls");
    for(int i=0; i<n; i++)
    {
        if(ara[i].get_name()==temp_name)
        {
            cout<<"\n(!)NOTIFICATION: Student found.\n"<<endl;
            cout<<"\nShowing records for "<<temp_name<<":\n"<<endl;
            cout<<"Name: "<<ara[i].get_name()<<endl;
            cout<<"Age: "<<ara[i].get_age()<<endl;
            cout<<"roll: "<<ara[i].get_roll()<<endl;
            cout<<"Bill: "<<ara[i].get_cgpa()<<endl;
            cout<<endl;
            hits++; //WHAT IF MORE THAN ONE PATIENT HAS THE SAME (FIRST) NAME? ADD A LAST NAME FEATURE PERHAPS?
        }
    }
    if(hits==0)
    {
        cout<<"(!)NOTIFICATION: student not found."<<endl;
    }
    system("pause");
    system("cls");
}
void modify_record(student ara[], int &n)
{
    char choice;
    string temp_name;
    int temp_age;
    string temp_roll;
    float temp_cgpa;
    int hits=0;
    cout<<"Enter student name: ";
    cin >>temp_name;
    cout<<endl;
    system("cls");
    for(int i=0; i<n; i++)
    {
        if(ara[i].get_name()==temp_name)
        {
            hits++;
            cout<<"\n(!)NOTIFICATION: student found.\n"<<endl;
            cout << "Edit records for "<<temp_name<<" ? (Y/N)"<<endl;
            cin  >> choice;
            system("cls");
            if(choice == 'Y' || choice == 'y')
            {
                while(1)
                {
                    cout << "\n\n";
                    cout << "\n\t\t\t Record Edit Sub-Menu";
                    cout << " \n\t\t\t=========================";
                    cout << "\n \t\t\t  1. Edit name";
                    cout << "\n \t\t\t  2. Edit age";
                    cout << "\n \t\t\t  3. Edit roll no.";
                    cout << "\n \t\t\t  4. Edit cgpa";
                    cout << "\n \t\t\t  5. Return to Main Menu";
                    cout << " \n\t\t\t=========================";
                    cout << "\n\n";
                    cout << "\t\t\t Select Your Choice: ";
                    cin  >> choice;
                    cout << "\n\n";
                    switch(choice)
                    {
                        case '1' :
                            system("cls");
                            cout<<"Enter new name: ";
                            cin >> temp_name;
                            cout<<endl;
                            ara[i].set_name(temp_name);
                            break;
                        case '2' :
                            system("cls");
                            cout<<"Enter updated age: ";
                            cin >> temp_age;
                            cout<<endl;
                            ara[i].set_age(temp_age);
                            break;
                        case '3' :
                            system("cls");
                            cout<<"Enter new roll no: ";
                            cin >> temp_roll;
                            cout<<endl;
                            ara[i].set_roll(temp_roll);
                            break;
                        case '4' :
                            system("cls");
                            temp_cgpa = ara[i].get_cgpa();
                            int update;
                            cout<<"Current cgpa   : "<<ara[i].get_cgpa()<<endl;
                            cout<<"Add new amount : ";
                            cin >> update;
                            temp_cgpa+=update;
                            ara[i].set_cgpa(temp_cgpa);
                            cout<<"Updated cgpa   : "<<ara[i].get_cgpa()<<endl;
                            system("pause");
                            break;
                        case '5' :
                            system("cls");
                            return;
                            //break; //IS THIS NECCESSARY?
                        default :
                            system("cls");
                            cout<<"Invalid selection."<<endl;
                    }
                    CHANGES++;
                    system("cls");
                    cout<<"\n(!)NOTTIFICATION: Records updated."<<endl;
                }
            }
            else
            {
                system("cls");
                return;
            }
        }
    }
    if(hits==0)
    {
        system("cls");
        cout<<"\(!)NOTIFICATION: student not found."<<endl;
    }
}
void delete_record(student ara[], int &n)
{
    ///NEED HINTS TO MAKE THIS MODULE MORE EFFICIENT.

    string temp_name;
    int hits=0;
    cout<<"Enter student name: ";
    cin>>temp_name;
    cout<<endl;
    system("cls");
    for(int i=0; i<n; i++)
    {
        if(ara[i].get_name()==temp_name)
        {
            hits++;
            cout<<"\n(!)NOTTIFICATION: Patient found.\n"<<endl;
            cout<<"Delete records for student: "<<ara[i].get_name()<<"? (Y/N)"<<endl;
            char choice;
            cin>>choice;
            system("cls");
            if(choice == 'y' || choice == 'Y')
            {
                int temp_age;
                string temp_roll;
                float temp_cgpa;
                for(int j=i; j<n-1; j++)
                {
                    /*temp_name = ara[j].get_name();
                    temp_age = ara[j].get_age();
                    temp_room = ara[j].get_room();
                    temp_bill = ara[j].get_bill();*/
                    ara[j].set_name(ara[j+1].get_name());
                    ara[j].set_age(ara[j+1].get_age());
                    ara[j].set_roll(ara[j+1].get_roll());
                    ara[j].set_cgpa(ara[j+1].get_cgpa());
                }
                n--;//ONE RECORD DELETED, i.e. total_patient - 1
                CHANGES++;
                cout<<"\n(!)NOTTIFICATION: Records deleted."<<endl;
            }
            else
            {
                cout<<"\n(!)NOTTIFICATION: Records not deleted."<<endl;
                break;
            }
        }
    }
    if(hits==0)
    {
        system("cls");
        cout<<"\n(!)NOTTIFICATION: student not found."<<endl;
    }
}
void list_records(student ara[], int &n)
{
    cout<<"#"<<"\tName"<<"\t\t roll no "<<"\t\t cgpa " <<endl;
    for(int i=0; i<n; i++)
    {
        cout<<i+1<<".\t"<<ara[i].get_name()<<"\t\t  "<<ara[i].get_roll()<<"\t\t  "<<ara[i].get_cgpa()<<endl;
    }
    cout<<endl;
    system("pause");
    system("cls");
}
void exit_program(student ara[], int &n) ///NEED HINTS ("seek line" and saving changes)
{
    //WRITE CODE TO SEEK LINE #1 OF THE FILE AND INPUT TOTAL NUMBER OF PATIENTS THRERE.
    if(CHANGES!=0)
    {
        cout<<"Save changes before exiting? (Y/N)"<<endl;
        char choice;
        cin>>choice;
        system("cls");
        if(choice == 'Y' || choice == 'y')
        {
            file << n;
            for(int i=0; i<n; i++)
            {
                file << ara[i].get_name() << endl;
                file << ara[i].get_age()  << endl;
                file << ara[i].get_roll() << endl;
                file << ara[i].get_cgpa() << endl;
            }
            file.close();
            cout<<"\n(!)NOTIFICATION: Changes saved."<<endl;
            cout<<"\n(!)NOTIFICATION: Program terminated."<<endl;
            exit(1);
        }
        else
        {
            file.close();
            cout<<"\n(!)NOTIFICATION: Changes not saved."<<endl;
            cout<<"\n(!)NOTIFICATION: Program terminated."<<endl;
            exit(1);
        }
    }
    else
    {
        file.close();
        cout<<"\n(!)NOTIFICATION: Program terminated."<<endl;
        exit(1);
    }
}

