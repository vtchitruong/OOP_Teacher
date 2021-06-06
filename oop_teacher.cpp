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
        fflush(stdin);
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
        fflush(stdin);
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
            cout << "--Those are: " << endl;
            for (int i = 0; i < SubjectNumber; ++i)
            {
                cout << "----";
                this->sj[i].Output();
            }
        }
    }

    Teacher* getTeacher()
    {
        return this;
    }
};

//-------------------------------------
class Thesis
{
private:
    string Name;
    string StudentName;
    int DefenseYear;

public:
    Thesis()
    {
        Name = "";
        StudentName = "";
        DefenseYear = 0;
    }

    const Thesis& operator=(const Thesis &t)
    {
        this->Name = t.Name;
        this->StudentName = t.StudentName;
        this->DefenseYear = t.DefenseYear;
        return t;
    }

    void Input()
    {
        cout << "----Input thesis name: ";
        fflush(stdin);
        getline(cin, Name);

        cout << "----Input student name: ";
        fflush(stdin);
        getline(cin, StudentName);

        cout << "----Input defense year: ";
        cin >> DefenseYear;
    }

    void Output()
    {
        cout << "----Thesis: " << Name << "--by student: " << StudentName << "--defensed in " << DefenseYear << endl;
    }
};



//-------------------------------------------------------
class Teacher2 : public Teacher
{
private:
    int ThesisNumber; // number of thesis that the teacher can guide
    Thesis *ts;
public:
    Teacher2() : Teacher()
    {
        ThesisNumber = 0;
        ts = NULL;
    }

    ~Teacher2()
    {
        if (ThesisNumber) delete ts;
    }

    Teacher2& operator=(Teacher2& tc);
    void Input();
    void Output();
};

Teacher2& Teacher2::operator=(Teacher2& tc)
{
    Teacher *t1, *t2;
    t1 = this->getTeacher();
    t2 = tc.getTeacher();

    *t1 = *t2;

    int n = tc.ThesisNumber;
    this->ThesisNumber = n;

    if (this->ts) delete ts;
    if (n)
    {
        this->ts = new Thesis[n];
        for (int i = 0; i < n; ++i)
        {
            this->ts[i] = tc.ts[i];
        }
    }

    return tc;
}

void Teacher2::Input()
{
    Teacher::Input();
    cout << "Input the number of guiding thesis: ";
    cin >> ThesisNumber;

    if (this->ts) delete ts;
    if (ThesisNumber)
    {
        this->ts = new Thesis[ThesisNumber];
        for (int i = 0; i < ThesisNumber; ++i)
        {
            this->ts[i].Input();
        }
    }
}

void Teacher2::Output()
{
    Teacher::Output();
    cout << "Number of guiding thesis: " << ThesisNumber << endl;\

    if (ThesisNumber)
    {
        cout << "Those are:" << endl;
        for (int i = 0; i < ThesisNumber; ++i)
        {
            this->ts[i].Output();
        }
    }
}

//-------------------------------------------------------------------
#define Teacher Teacher2
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
    void Sort(); // Sort teachers by their number of subjects
};

void Faculty::Input()
{
    cout << "Input the faculty name: ";
    fflush(stdin);
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

// Sort teachers by their number of subjects
void Faculty::Sort()
{
    Teacher tmp;
    if (TeacherNumber)
    {
        for (int i = 0; i < TeacherNumber - 1; ++i)
        {
            for (int j = i + 1; j < TeacherNumber; ++j)
            {
                if (tc[i].getSubjectNumber() < tc[j].getSubjectNumber())
                {
                    tmp = tc[i];
                    tc[i] = tc[j];
                    tc[j] = tmp;
                }
            }
        }
    }
}
#undef Teacher

//------------------------------------------------
int main()
{
    Faculty fc;

    fc.Input();
    fc.Sort();
    fc.Output(); 


    return 0;
}