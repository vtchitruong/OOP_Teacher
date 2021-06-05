#include <iostream>
#include <string>

using namespace std;

class Subject
{
private:
    string Name;
    int LessonNumber;

public:
    // constructor
    Subject()
    {
        Name = "";
        LessonNumber = 0;
    }

    // assigning function
    const Subject& operator=(const Subject& s)
    {
        this->Name = s.Name;
        this->LessonNumber = s.LessonNumber;

        return s;
    }

    void Input()
    {
        cout << "Input subject name: ";
        getline(cin, Name);

        cout << "Input lesson number of the subject: ";
        cin >> LessonNumber;
    }

    void Output()
    {
        cout << "Subject: " << Name << " with " << LessonNumber << " lessons." << endl;
    }
};

//-------------------------------------------------------------
class Teacher
{
private:
    string Name;
    int BirthYear;
    int SubjectNumber; // number of subjects that he/she can teach
    Subject *sj;

public:
    // constructor
    Teacher()
    {
        Name = "";
        BirthYear = SubjectNumber = 0;
        sj = NULL;
    }    

    // destructor
    ~Teacher()
    {
        Name = "";
        BirthYear = SubjectNumber = 0;
        if (sj) delete sj;
    }

    int getSubjectNumber()
    {
        return SubjectNumber;
    }

    const Teacher& operator=(const Teacher& t)
    {
        this->Name = t.Name;
        this->BirthYear = t.BirthYear;
        
        int n = t.SubjectNumber;
        this->SubjectNumber = n;

        if (this->sj) delete sj;

        if (n)
        {
            this->sj = new Subject[n];
            for (int i = 0; i < n; ++i)
            {
                this->sj[i] = t.sj[i];
            }
        }

        return t;
    }

    void Input()
    {
        cout << "Input teacher's name: ";
        getline(cin, Name);
        cout << "Input year of birth: ";
        cin >> BirthYear;
        cout << "Input number of subjects to be taken on: ";
        cin >> SubjectNumber;
        if (this->sj) delete this->sj;

        if (SubjectNumber)
        {
            this->sj =  new Subject[SubjectNumber];            
            for (int i =0; i < SubjectNumber; ++i)
            {
                cout << "--";
                this->sj[i].Input();
            }
        }
    }

    void Output()
    {
        cout << "Teacher's name: " << Name << "-- born in " << BirthYear << "-- can teach " << SubjectNumber << " subjects." << endl;
        if (SubjectNumber)
        {
            cout << "--Those are: ";
            for (int i = 0; i < SubjectNumber; ++i)
            {
                cout << "----";
                this->sj[i].Output();
            }
        }
    }
};

//-------------------------------------------------------------------
class Faculty
{
private:
    string Name;
    int TeacherNumber;
    Teacher *tc;
public:
    Faculty()
    {
        Name = "";
        TeacherNumber = 0;
        tc = NULL;
    }

    void Input();
    void Output();
    void Sort();
};

void Faculty::Input()
{
    cout << "Input the faculty name: ";
    getline(cin, Name);
    cout << "Input the number of teachers in the faculty: ";
    cin >> TeacherNumber;

    if (tc) delete tc;
    if (TeacherNumber)
    {
        cout << "Input teacher's info:" << endl;
        tc = new Teacher[TeacherNumber];
        for (int i = 0; i < TeacherNumber; ++i)
        {
            tc[i].Input();
        }
    }
}

void Faculty::Output()
{
    cout << "Faculty: " << Name << "--includes " << TeacherNumber << " teachers." << endl;
    if (TeacherNumber)
    {   
        cout << "Teachers are listed below:" << endl;
        for (int i = 0; i < TeacherNumber; ++i)
        {
            tc[i].Output();
        }
    }

}

int main()
{
    

    return 0;
}