#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>
using namespace std;


enum Specialnist { KN, PM, FI };
string specialnistStr[] = { "КН", "ПМ", "ФІ" };


struct Student {
    string prizv;
    int kurs;
    Specialnist specialnist;
    union {
        struct {
            int ocinka_fizyka;
            int ocinka_matematyka;
            int ocinka_informatyka;
        };
        int ocinki[3];
    };
};


void CreateStudents(Student* students, const int N) {
    int specialnist;
    for (int i = 0; i < N; i++) {
        cout << "Студент № " << i + 1 << ":" << endl;
        cout << " Прізвище: ";
        cin >> students[i].prizv;
        cout << " Курс: ";
        cin >> students[i].kurs;
        cout << " Спеціальність (0 - КН, 1 - ПМ, 2 - ФІ): ";
        cin >> specialnist;
        students[i].specialnist = (Specialnist)specialnist;


        cout << " Оцінка з фізики: ";
        cin >> students[i].ocinka_fizyka;
        cout << " Оцінка з математики: ";
        cin >> students[i].ocinka_matematyka;
        cout << " Оцінка з інформатики: ";
        cin >> students[i].ocinka_informatyka;
        cout << endl;
    }
}


void CountProgrammingGrades(const Student* students, const int N, int& count5, int& count4, int& count3) {
    count5 = count4 = count3 = 0;
    for (int i = 0; i < N; i++) {
        if (students[i].ocinka_informatyka == 5) count5++;
        else if (students[i].ocinka_informatyka == 4) count4++;
        else if (students[i].ocinka_informatyka == 3) count3++;
    }
}


double CalculateHighPhysicsMathPercentage(const Student* students, const int N) {
    int count = 0;
    for (int i = 0; i < N; i++) {
        if ((students[i].ocinka_fizyka >= 4) && (students[i].ocinka_matematyka >= 4)) {
            count++;
        }
    }
    return (N == 0) ? 0 : (static_cast<double>(count) / N) * 100;
}


void PrintStudents(const Student* students, const int N) {
    cout << "=============================================================================================================" << endl;
    cout << "| № | Прізвище        | Курс | Спеціальність | Оцінка з фізики | Оцінка з математики | Оцінка з інформатики |" << endl;
    cout << "-------------------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < N; i++) {
        cout << "|" << setw(2) << i + 1
            << " |  " << setw(15) << left << students[i].prizv
            << "|   " << setw(3) << students[i].kurs
            << "|" << setw(15) << specialnistStr[students[i].specialnist]
            << "|   " << setw(14) << students[i].ocinka_fizyka
            << "|   " << setw(18) << students[i].ocinka_matematyka
            << "| " << setw(20) << students[i].ocinka_informatyka << " |" << endl;
    }
    cout << "=============================================================================================================" << endl;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int N;
    cout << "Введіть кількість студентів: ";
    cin >> N;

    Student* students = new Student[N];

    CreateStudents(students, N);
    PrintStudents(students, N);

    int count5, count4, count3;
    CountProgrammingGrades(students, N, count5, count4, count3);
    cout << "Кількість оцінок з програмування:" << endl;
    cout << "5: " << count5 << endl;
    cout << "4: " << count4 << endl;
    cout << "3: " << count3 << endl;

    double highPhysicsMathPercentage = CalculateHighPhysicsMathPercentage(students, N);
    cout << "Відсоток студентів з оцінками «4» або «5» з фізики і математики: ";
    cout << fixed << setprecision(2) << highPhysicsMathPercentage << "%" << endl;

    delete[] students;
    return 0;
}