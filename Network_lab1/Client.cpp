#include <iostream>
#include <fstream>
#include <unistd.h>

// #TODO !! : to make ANSII symbols work + add some color, font and cursor : https://stackoverflow.com/questions/4842424/list-of-ansi-color-escape-sequences ,https://en.wikipedia.org/wiki/ANSI_escape_code


using namespace std;

struct Person
{
    int client_id;
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
    while (true)
    {
        cout << "\033[3;32;103m Введите id-номер клиента: \033[0m\n";
        cin >> client_id;
        if (client_id == 27) {
            cout << "\033[31m Завершение работы...\033[0m\n";
            sleep(5);
            break;
        }
// передача данных от клиента серверу
        cout <<"\033[36m Введите запрос: Фамилия студента   Номер направления  Баллы Информатика   Баллы математика    Баллы Русский язык  \033[0m"<<endl;
        cin >> Student.name >> Student.faculty  >> Student.informatica >> Student.math >> Student.russ;
        Student.client_id = client_id;
        if (!isdigit(Student.faculty) && Student.faculty != 10302 && Student.faculty != 20302 && Student.faculty != 20303 && Student.faculty != 90303){
            cout << "\033[31;40m Введите корректный номер направления (010302 - пми , 020302 - пи, 020303 - фундам, 090303 - матобес ): \033[0m";
            cin >> Student.faculty;
        }
        cout << "\033[96;107m Студент:   " << Student.name <<"\t"<< "0" <<Student.faculty <<"\t"<< Student.informatica <<"\t"<< Student.math <<"\t"<< Student.russ << endl << "\033[0m";
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
            case 0: {cout <<"\033[1;31;40m   Сожалеем, но вы не проходите на это направление :) \033[0m \n";break;}
            case 1: {cout << "\033[3;97;102m  Поздравляем! Вы проходите на введеное вами направление \033[0m \n"<< "\n";break;}
        }
    }
}