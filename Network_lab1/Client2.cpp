#include <iostream>
#include <fstream>
#include <unistd.h>
using namespace std;
// структура данных запроса клиента
struct Person
{
    int id_client;
    char name[25]; //имя
    int faculty;//факультет
    int informatica; //баллы инф
    int math; // баллы мат
    int russ;// баллы рус
} Student;

int main()
{
    setlocale(LC_ALL, "rus");
    char* nameR = "request.bin";
//файл запросов клиентов
    char* nameA = "answers.bin";
//файл для ответов сервера
    int client_id;
    ofstream f_REQ;
    ifstream f_ANS;
    long pred_size;
    int answer;
    cout << "Введите id-номер клиента: ";
    cin >> client_id;
    if (client_id == 27) {
        cout << "Завершение работы...";
        sleep(5);
    }
    while (true)
    {
        cout << "Введите id-номер клиента: ";
        cin >> client_id;
        if (client_id == 27) {
            cout << "Завершение работы...";
            sleep(5);
            break;
        }
// передача данных от клиента серверу
        cout << "Введите запрос: Фамилия студента   Номер направления  Баллы Информатика   Баллы математика    Баллы Русский язык"<<endl;
        cin >> Student.name >> Student.faculty  >> Student.informatica >> Student.math >> Student.russ;
        if (!isdigit(Student.faculty) && Student.faculty != 10302 && Student.faculty != 20302 && Student.faculty != 20303 && Student.faculty != 90303){
            cout << "Введите корректный номер направления (010302 - пми , 020302 - пи, 020303 - фундам, 090303 - матобес ): ";
            cin >> Student.faculty;
        }
        cout << Student.name <<"\t"<< "0" <<Student.faculty <<"\t"<< Student.informatica <<"\t"<< Student.math <<"\t"<< Student.russ;
        f_REQ.open( nameR, ios::app |ios::binary);
//открытие файла REQUEST
        f_REQ.write((char*)&Student, sizeof(Student));
//запись запроса в файл REQUEST
        f_REQ.close();
// поступил ответ от сервера?
        f_ANS.open(nameA, ios::binary);
//открытие файла ANSWER
        f_ANS.seekg(0, ios::end);
//переход в конец файла ANSWER
        pred_size = f_ANS.tellg();
        while (pred_size >= f_ANS.tellg())
        {
            sleep(10);
// ждем и переходим в конец файла ANSWER
            f_ANS.seekg(0, ios::end);}
// получение ответа от сервера
        f_ANS.seekg(pred_size, ios::beg);
// на начало нового ответа
        f_ANS.read ((char*)&answer, sizeof(answer)) ;
//считывание ответа
        f_ANS.close();
// расшифровка ответа
        switch (answer) {
            case 0: {cout <<"   Сожалеем, но вы не проходите на это направление :) \n";break;}
            case 1: {cout << "  Поздравляем! Вы проходите на введеное вами направление"<< "\n";break;}
        }
    }
}