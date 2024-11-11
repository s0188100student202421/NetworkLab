#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define PORT 8080
#define BUFFER_SIZE 1024

using namespace std;

struct Person {
    int client_id;
    char name[25]; // имя
    int faculty;   // факультет
    int informatica; // баллы инф
    int math;       // баллы мат
    int russ;       // баллы рус
} Student;

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};

    // Создание сокета
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        cerr << "Ошибка создания сокета" << endl;
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Преобразование IPv4 адреса в структурированный формат
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        cerr << "Неверный адрес / Адрес не поддерживается" << endl;
        return -1;
    }

    // Подключение к серверу
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        cerr << "Ошибка подключения" << endl;
        return -1;
    }

    while (true) {
        cout << "Введите свой id если хотите продолжить, 27 для выхода: ";
        cin >> Student.client_id;
        if (Student.client_id == 27) break;

        cout << "Введите фамилию, факультет, баллы информатика, баллы математика, баллы рус: ";
        cin >> Student.name >> Student.faculty >> Student.informatica >> Student.math >> Student.russ;

        send(sock, &Student, sizeof(Student), 0);
        cout << "Сообщение отправлено серверу" << endl;

        memset(buffer, 0, BUFFER_SIZE); // Очистка буфера
        read(sock, buffer, sizeof(buffer));
        cout << "Сообщение от сервера: " << buffer << endl;
    }
    close(sock);
    return 0;
}
