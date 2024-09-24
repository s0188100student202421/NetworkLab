#include <iostream>
#include <fstream>
#include <unistd.h>
#include <string>


using namespace std;
//
struct Person
{
    int client_id;
    char name[25]; //имя
    int faculty;//факультет
    int informatica; //баллы инф
    int math; // баллы мат
    int russ;// баллы рус
}Student;

int answer;
long size_pred;
int main()
{
    ifstream fR;
    ofstream fA;
    setlocale(LC_ALL, "rus");
    const string nameR = "request.bin";
//файл запросов клиентов
    string nameA = "answers.bin";
//файл ответов сервера
    cout << "server is working"<< endl;
// начальные установки
    fR.open(nameR, ios::binary);
//открытие файла REQUEST
    fR.seekg(0, ios::end);
    size_pred = fR.tellg();
//стартовая позиция сервера в файле REQUEST
    fR.close();
    while (true)
    {
        fR.open(nameR, ios::binary);
        fR.seekg(0, ios::end);
//переход в конец файла REQUEST
// есть новые запросы от клиентов? как только fR.tellg() станет больше переходим к след.операции
        while (size_pred >= fR.tellg())
        {
            sleep(10);
            fR.seekg(0, ios::end);}
// получен новый запрос
        fR.seekg(size_pred, ios::beg);
//переход к началу полученного запроса
        fR.read((char*)&Student, sizeof(Student));
        cout << "\033[3;97;102m Получены данные о студенте:     \033[0m";
        cout << Student.client_id << endl;
//считывание данных клиента
        size_pred = fR.tellg();
// на конец обработанных данных
        fR.close();
// определение баллов
        int points = Student.informatica + Student.math + Student.russ;
        switch(Student.faculty) {
            case 90303:
                answer = points >= 238 ? 1 : 0;
            case 20303:
                answer = points >= 237 ? 1 : 0;
            case 20302:
                answer = points >= 245 ? 1 : 0;
            case 10302:
                answer = points >= 233 ? 1 : 0;

        }
// передача ответа клиенту
        fA.open(nameA, ios::binary | ios::app);
//открытие файла ANSWER
        fA.write( (char*)&answer, sizeof(answer));
//запись ответа клиенту
        fA.close();
    }
}