#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

//Store class for Store offering class data.
class Class{

    public:
    int crn;
    string rubric;
    string section;
    string courseName;
    string Instructor;
    int days;
    int time;
    int seats;
    string opening;

    Class(int crnL, string rubricL, string sectionL,string courseNameL,string InstructorL,int daysL,int timeL,int seatsL, string openingL) {
        crn=crnL;
        rubric = rubricL;
        section = sectionL;
        courseName = courseNameL;
        Instructor = InstructorL;
        days=daysL;
        time=timeL;
        seats=seatsL;
        opening = openingL;

    };

    ~Class() {};

};

//Store class for Store Registered Student data for every class.
class RegisteredStudent{
    public:
    int studentId;
    string firstName;
    string lastName;
    string middleName;
    string studentEmail;

    RegisteredStudent(int studentIdL, string firstNameL,string lastNameL,string middleNameL,string studentEmailL) {
        studentId = studentIdL;
        firstName = firstNameL;
        lastName = lastNameL;
        middleName = middleNameL;
        studentEmail = studentEmailL;
    };

    ~RegisteredStudent() {};
};

//Store Student Attendance data for every class.
class StudentAttendance{
    public:
    int studentId;
    int numberOfAttend;

    StudentAttendance(int studentIdL, int numberOfAttendL) {
        studentId = studentIdL;
        numberOfAttend = numberOfAttendL;
    };

    ~StudentAttendance() {};
};

//Store Student grades data for every class.
class StudentGrades{
    public:
    string firstName;
    string lastName;
    double testGrades[4];
    double finalTestGrade;

    StudentGrades(string firstNameL, string lastNameL,double testGradesL[],double finalTestGradeL) {
        firstName = firstNameL;
        lastName = lastNameL;
        testGrades[0] = testGradesL[0];
        testGrades[1] = testGradesL[1];
        testGrades[2] = testGradesL[2];
        testGrades[3] = testGradesL[3];
        finalTestGrade = finalTestGradeL;
    };

    ~StudentGrades() {};
};



class Classes{
    public:

    vector <Class> offeredClass;

    //Function to read in class offering information for this semester.
    void readOfferingInformation(string fileName){
        offeredClass.clear();
        int crn;
        string rubric;
        string section;
        string courseName;
        string Instructor;
        int days;
        int time;
        int seats;
        string opening;

        ifstream infile;
        infile.open(fileName);
        while (infile >> crn >> rubric >> section >>courseName >>Instructor >>days >> time >>seats>>opening)
        {
            offeredClass.push_back(Class(crn,rubric,section,courseName,Instructor,days,time,seats,opening));
        }

    }

    //Function to output the class offering report.
    void createOfferingsReport(string outfileName){
        ofstream outfile;
        outfile.open(outfileName);
        for(Class i : offeredClass){
            outfile << left << setw(10) << setfill(' ') << i.crn;
            outfile << left << setw(15) << setfill(' ') << i.rubric;
            outfile << left << setw(10) << setfill(' ') << i.section;
            outfile << left << setw(10) << setfill(' ') << i.courseName;
            outfile << left << setw(10) << setfill(' ') << i.Instructor;
            outfile << left << setw(10) << setfill(' ') << i.days;
            outfile << left << setw(10) << setfill(' ') << i.time;
            outfile << left << setw(10) << setfill(' ') << i.seats;
            outfile << left << setw(10) << setfill(' ') << i.opening;
            outfile << endl;
        }
        outfile.close();
    }

    int getClassDays(string className){
        for(Class i : offeredClass){
            if(className.compare(i.courseName)==0){
                return i.days;
            }
        }
        return 0;
    }

};


class ClassSection{

    vector <RegisteredStudent> registeredStudent;
    vector <StudentAttendance> studentAttendance;
    vector <StudentGrades> sg;

    public:

    //Function to read in students registered for a particular class section.
    void  readRegisteredStudent(string fileName){
        registeredStudent.clear();
        int studentId;
        string firstName;
        string lastName;
        string middleName;
        string studentEmail;

        ifstream infile;
        infile.open(fileName);
        while (infile >> studentId >> firstName >> lastName >>middleName>>studentEmail)
        {
            registeredStudent.push_back(RegisteredStudent(studentId,firstName,lastName,middleName,studentEmail));
        }
    }

    RegisteredStudent getStudentDetails(int studentId){
        RegisteredStudent  rs=RegisteredStudent(0,"","","","");
        for(RegisteredStudent i : registeredStudent){
            if(i.studentId==studentId){
                return i;
            }
        }
        return rs;
    }
    //Function to output the Roster report.
    void createRosterReport(string outfileName){
        ofstream outfile;
        outfile.open(outfileName);

        for(RegisteredStudent i : registeredStudent){
            outfile << left << setw(10) << setfill(' ') << i.studentId;
            outfile << left << setw(15) << setfill(' ') << i.firstName;
            outfile << left << setw(10) << setfill(' ') << i.lastName;
            outfile << left << setw(10) << setfill(' ') << i.middleName;
            outfile << left << setw(10) << setfill(' ') << i.studentEmail;
            outfile << endl;
        }
        outfile.close();
    }

    //Function to read in students attendance for a particular class section.
    void  readStudentAttendance(string fileName){
        studentAttendance.clear();
        int studentId;
        int numberOfAttend;

        ifstream infile;
        infile.open(fileName);
        while (infile >> studentId >> numberOfAttend)
        {
            studentAttendance.push_back(StudentAttendance(studentId,numberOfAttend));
        }
    }

    //Function to output the attendance report.
     void createAttendanceReport(string outfileName,int classDays){
        ofstream outfile;
        outfile.open(outfileName);
        double attendanceGrade;

        outfile << left << setw(15) << setfill(' ') << "First Name";
        outfile << left << setw(15) << setfill(' ') << "Last Name";
        outfile << left << setw(10) << setfill(' ') << "Attended";
        outfile << left << setw(10) << setfill(' ') << "Missed";
        outfile << left << setw(10) << setfill(' ') << "Attendance Grade";
        outfile << endl;
        for(StudentAttendance i : studentAttendance){
            RegisteredStudent studentDetails=getStudentDetails(i.studentId);
            attendanceGrade=round(((i.numberOfAttend*1.0)/classDays)*100);
            outfile << left << setw(15) << setfill(' ') << studentDetails.firstName;
            outfile << left << setw(15) << setfill(' ') << studentDetails.lastName;
            outfile << left << setw(10) << setfill(' ') << i.numberOfAttend;
            outfile << left << setw(10) << setfill(' ') << (classDays-i.numberOfAttend);
            outfile << left << setw(10) << setfill(' ') << attendanceGrade;
            outfile << endl;
        }
        outfile.close();
    }

    //Function to read in student grades for aparticular class section.
    void readStudentGrades(string fileName){
        sg.clear();
        string firstName;
        string lastName;
        double testGrades[4];
        double finalTestGrade;


        ifstream infile;
        infile.open(fileName);
        while (infile >> firstName >> lastName >> testGrades[0] >>testGrades[1] >>testGrades[2] >>testGrades[3] >> finalTestGrade)
        {
            sg.push_back(StudentGrades(firstName,lastName,testGrades,finalTestGrade));
        }
    }



    /*
    Function to calculateone student grade average.
    */
    double studentGradeAverage(StudentGrades s){
        double sum=0;
        double avr=0;
        for(int i = 0; i < 4; i++) {
          sum=sum+s.testGrades[i];
        }
        avr=round((sum+2*s.finalTestGrade)/6);
        return avr;
    }
     /*
        Function to calculate letter grade for 1 student.
     */
    char calculateLetterGrade(double avr){
        if(avr > 80){
            return 'A';
        }else if(avr > 65){
            return 'B';
        }else if(avr > 50){
            return 'C';
        }else if(avr > 35){
            return 'D';
        }else{
            return 'F';
        }
    }

    /*
        Function to calculate the averages of 1 test.
     */
    double averagesOfOneTest(int testNumber){
        double sum=0;
        double avr=0;
        for(StudentGrades i : sg){
            if(testNumber==5){
                sum=sum+i.finalTestGrade;
            }else{
                sum=sum+i.testGrades[testNumber];
            }
        }

        avr=round(sum/sg.size());
        return avr;
    }

    /*
        Function to calculate the overall Test Average.
     */
    double averagesOfOverall(vector <double> stuAves){
        double sum=0;
        double avr=0;
        for(double i : stuAves){
            sum=sum+i;
        }
        avr=round(sum/stuAves.size());
        return avr;
    }

    /*
        Function to find student with highest class grade.
     */
    char highestClassGrade(vector <double> stuAves){
        double highest=0;
        for(double i : stuAves){
            if(i>highest){
                highest=i;
            }
        }
        return calculateLetterGrade(highest);
    }

    /*
    Function to find all students who get highest class grade.
    */
    void highestClassGradeStudent(char highestGrade,string highestStudent[]){
        char grade;
        int k=0;
        for(StudentGrades i : sg){
            grade=calculateLetterGrade(studentGradeAverage(i));
            if(grade==highestGrade){
                highestStudent[k]=i.firstName;
                highestStudent[k+1]=i.lastName;
                k++;
                k++;
            }
        }

    }
    /*
    Function to output the class grade report to a file.
    */
    void createGradeReport(string outfileName){
        ofstream outfile;
        outfile.open(outfileName);
        double stuAve;
        char highestGrade;
        vector<double> stuAves;
        string highestGradeStudent[60];
        for(StudentGrades i : sg){
            stuAve=studentGradeAverage(i);
            stuAves.push_back(stuAve);
            outfile << left << setw(15) << setfill(' ') << i.firstName;
            outfile << left << setw(15) << setfill(' ') << i.lastName;
            outfile << left << setw(10) << setfill(' ') << i.testGrades[0];
            outfile << left << setw(10) << setfill(' ') << i.testGrades[1];
            outfile << left << setw(10) << setfill(' ') << i.testGrades[2];
            outfile << left << setw(10) << setfill(' ') << i.testGrades[3];
            outfile << left << setw(10) << setfill(' ') << i.finalTestGrade;
            outfile << left << setw(10) << setfill(' ') << stuAve;
            outfile << left << setw(10) << setfill(' ') << (calculateLetterGrade(stuAve));
            outfile << endl;
        }
        highestGrade=highestClassGrade(stuAves);
        outfile << endl;
        outfile << left << setw(15) << setfill(' ') << "";
        outfile << left << setw(15) << setfill(' ') << "";
        outfile << left << setw(10) << setfill(' ') << averagesOfOneTest(1);
        outfile << left << setw(10) << setfill(' ') << averagesOfOneTest(2);
        outfile << left << setw(10) << setfill(' ') << averagesOfOneTest(3);
        outfile << left << setw(10) << setfill(' ') << averagesOfOneTest(4);
        outfile << left << setw(10) << setfill(' ') << averagesOfOneTest(5);
        outfile << left << setw(10) << setfill(' ') << averagesOfOverall(stuAves);
        outfile << left << setw(10) << setfill(' ') << highestGrade;
        outfile << endl;
        outfile << endl;

        highestClassGradeStudent(highestGrade,highestGradeStudent);
        size_t i = 0;
        outfile <<"student(s) with the highest class grade"<<endl;
        while (!highestGradeStudent[i].empty()){
            outfile << left << setw(15) << setfill(' ') << highestGradeStudent[i] << left << setw(15) << setfill(' ') << highestGradeStudent[i+1]<< left << setw(15) << setfill(' ')<<highestGrade <<endl;
            i++;
            i++;
        }

        outfile.close();

    }

    double round(double var)
    {
        double value = (int)(var * 100 + .5);
        return (double)value / 100;
    }
};


int main() {

    Classes c;
    c.readOfferingInformation("classes.txt");
    c.createOfferingsReport("OfferingsReport.txt");

    ClassSection s1;
    s1.readRegisteredStudent("CIT1325RegisteredStudent.txt");
    s1.createRosterReport("CIT1325RosterReport.txt");
    s1.readStudentAttendance("CIT1325AttendanceSheet.txt");
    s1.createAttendanceReport("CIT1325AttendanceReport.txt", c.getClassDays("CIT1325"));
    s1.readStudentGrades("CIT1325.txt");
    s1.createGradeReport("CIT1325GradeReport.txt");

    ClassSection s2;
    s2.readStudentGrades("CIT1350.txt");
    s2.createGradeReport("CIT1350GradeReport.txt");


    return 0;
}