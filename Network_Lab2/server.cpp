#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define PORT 8080
#define BUFFER_SIZE 1024

struct Person {
    int client_id;
    char name[25]; // имя
    int faculty;   // факультет
    int informatica; // баллы информатика
    int math;       // баллы мат
    int russ;       // баллы рус
} Student;

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};

    // Создание сокета
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Привязка сокета к порту
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Начало прослушивания
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    std::cout << "Сервер запущен, ожидает подключения..." << std::endl;

    while (true) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        // Чтение и отправка данных
        while (true) {
            memset(buffer, 0, BUFFER_SIZE); // Очистка буфера
            ssize_t receivedBytes = recv(new_socket, &Student, sizeof(Student), 0);
            if (receivedBytes <= 0) {
                std::cout << "Клиент отключился." << std::endl;
                break; // Выход из внутреннего цикла, если клиент отключился
            }

            int points = Student.informatica + Student.math + Student.russ;
            const char* message;

            switch (Student.faculty) {
                case 90303:
                    message = (points >= 238) ? "Поздравляем! Вы проходите на это направление" : "Сожалеем, но вы не проходите на это направление";
                    break;
                case 20303:
                    message = (points >= 237) ? "Поздравляем! Вы проходите на это направление" : "Сожалеем, но вы не проходите на это направление";
                    break;
                case 20302:
                    message = (points >= 245) ? "Поздравляем! Вы проходите на это направление" : "Сожалеем, но вы не проходите на это направление";
                    break;
                case 10302:
                    message = (points >= 233) ? "Поздравляем! Вы проходите на это направление" : "Сожалеем, но вы не проходите на это направление";
                    break;
                default:
                    message = "Некорректный факультет.";
            }

            std::cout << "ID клиента: " << Student.client_id << std::endl;
            send(new_socket, message, strlen(message), 0); // Отправка сообщения клиенту
            std::cout << "Сообщение отправлено клиенту" << std::endl;
        }

        close(new_socket); // Закрытие сокета клиента
    }

    close(server_fd); // Закрытие серверного сокета
    return 0;
}
