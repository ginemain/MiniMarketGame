#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
#include <ctime>
#include <iomanip> // для красивого баланса с двумя знаками .00

using namespace std;

/*
                    Shop Game Market

    При запуске программа читает следующие данные из файлов:

        1) Данные ( логин и пароль ) пользователя из .txt
        2) Товары ( продукты и их цены )
        3) Баланс
        4) Корзина (Инвентарь) что есть у человека и т д

    Можно покупать продавать товары
    И самое главное игра не на один раз!

    Отдельный файл с логином и паролем и можно будет входить в тот же аккаунт с
    тем же балансом и продуктами которые хранятся

*/

class User {
private:
    string login;
    string password;
    double balance = 0.0;

public:
    // регистрация
    void Register(string log, string pas, bool& verif) {

        ifstream check_file_login;
        // проверка на уже существующий такой файл с таким логином
        check_file_login.open(log + ".txt");
        if (check_file_login.is_open()) {
            cout << "Такой логин уже занят :(" << endl;
        }
        else {

            this->login = log;
            this->password = pas;
            this->balance = 100;

            ofstream regfile;
            regfile.open(login + ".txt");

            if (!regfile.is_open()) {
                cout << "Не удалось создать аккаунт, попробуйте еще раз!" << endl;
            }
            // создаем 2 файла: с паролем и балансом
            else {
                regfile << this->password;

                ofstream balance_file;
                balance_file.open(login + "_balance.txt");

                if (!balance_file.is_open()) {
                    cout << "Не удалось создать файл с балансом!" << endl;
                }
                else {
                    balance_file << this->balance;
                    cout << "На ваш баланс успешно зачислено " << balance << " USD" << endl;
                }
                balance_file.close();

                cout << "Поздравляем! Вы успешно создали аккаунт!" << endl;
                cout << "Ваш баланс составляет: " << balance << " USD" << endl;
                regfile.close();
                verif = true;
            }
            regfile.close();
            // создание автоматически ПУСТОГО инвентаря игрока
            ofstream inventory_file;
            inventory_file.open(login + "_inventory.txt");

            if (!inventory_file.is_open()) {
                cout << "Не удалось создать файл с инвентарем!" << endl;
            }
            else {
                // создаем пустой инвентарь
                cout << "Инвентарь был создан успешно! " << endl;
            }
            inventory_file.close();
        }

        check_file_login.close();
    }
    // ЛОГИН    
    void Login(string log, string pass, bool& verif) {
        ifstream log_file;
        log_file.open(log + ".txt");

        // проверка на уже существующий такой файл с таким логином
        if (!log_file.is_open()) {
            cout << "Аккаунта с таким логином не существует!" << endl;

        }
        else {
            string check_pass;

            getline(log_file, check_pass);

            // проверка на схожесть паролей
            if (check_pass == pass) {
                cout << "Рады вас снова видеть, " << log << "! Вы успешно вошли в аккаунт!" << endl;
                verif = true;
                this->login = log;
                this->password = pass;

                // загрузка баланса
                ifstream balance_file(log + "_balance.txt");
                if (balance_file.is_open()) {
                    balance_file >> balance; // чтение из файла баланс
                    balance_file.close();
                }
                cout << "Ваш текущий баланс: " << balance << " USD" << endl;
            }
            else {
                cout << "Неверный пароль!" << endl;
            }

        }

        log_file.close();
    }
    // проверка ассортимента магазина   
    void Check_Shop() {
        ifstream products_file("products.txt");
        if (!products_file.is_open()) {
            cout << "Не удалось открыть файл products.txt!" << endl;
        }
        else {
            cout << "\n--- Ассортимент магазина ---\n";
            string name;
            double price;

            while (products_file >> name >> price) {
                cout << name << " — " << price << " USD" << endl;
            }
        }
        products_file.close();
    }
    // проверка баланса
    void Check_Balance() {
        // открываем файл с балансом
        ifstream balance_check_file;

        balance_check_file.open(this->login + "_balance.txt");

        if (!balance_check_file.is_open()) {
            cout << "Не удалось открыть файл _balance.txt" << endl;
        }
        else {
            double temp_balance;
            balance_check_file >> temp_balance;
            cout << "Ваш баланс: " << temp_balance << " USD" << endl;
        }
        balance_check_file.close();

    }
    // проверка инвентаря
    void Check_Inventory() {
        ifstream checkInv_file;
        checkInv_file.open(this->login + "_inventory.txt");

        if (!checkInv_file.is_open()) {
            cout << "Не удалось открыть файл с вашим инвентарем!" << endl;
        }
        else {
            cout << "У вас хранится в инвентаре" << endl;

            string item;
            double price;
            // выводим на экран с файла через переменную string item;
            while (checkInv_file >> item >> price) {
                cout << item << " - " << price << " USD" << endl;
            }
        }
        checkInv_file.close();
    }
    // покупка
    void Buy() {
        ifstream products_file("products.txt");
        if (!products_file.is_open()) {
            cout << "Не удалось открыть файл products.txt!" << endl;
        }
        else {
            // открываем файл с балансом
            ifstream balance_check_file;

            balance_check_file.open(this->login + "_balance.txt");

            if (!balance_check_file.is_open()) {
                cout << "Не удалось открыть файл _balance.txt" << endl;
            }
            else {
                //int temp_balance;
                balance_check_file >> balance;
                cout << "Ваш баланс: " << balance << " USD" << endl;
            }
            balance_check_file.close();

            cout << "\n--- Ассортимент магазина ---\n";
            string name;
            double price;

            while (products_file >> name >> price) {
                cout << name << " — " << price << " USD" << endl;
            }
            // ЗАКРЫЛ ФАЙЛ
            products_file.close();

            string buy_item;
            cout << "Что желаете купить? Введите товар: ";
            cin >> buy_item;

            string item_name;
            double item_price;

            // заново открываем файл
            ifstream buy_file("products.txt");
            if (!buy_file.is_open()) {
                cout << "Не удалось открыть файл products.txt!" << endl;
            }
            else {
                // цикл для нахождения товара
                while (buy_file >> item_name >> item_price) {
                    // если нашелся товар
                    if (buy_item == item_name) {
                        if (item_price > balance) {
                            cout << "Недостаточно средств для покупки." << endl;
                            break;
                        }
                        if (item_price <= balance) {
                            // открываем файл с балансом
                            ofstream buy_item_file;

                            buy_item_file.open(this->login + "_balance.txt");

                            if (!buy_item_file.is_open()) {
                                cout << "Транзакция не прошла. Не удалось открыть файл _balance.txt" << endl;
                            }
                            else {
                                // обновление баланса ( списывание )
                                balance = balance - item_price;
                                // запись нового баланса в файл _balance.txt
                                buy_item_file << balance;

                                // добавление товара в инвентарь
                                ofstream inventory_file;
                                inventory_file.open(login + "_inventory.txt", ofstream::app);

                                if (!inventory_file.is_open()) {
                                    cout << "Не удалось открыть файл с инвентарем!" << endl;
                                }
                                else {
                                    // добавляем предмет в инвентарь и цену в 2 раза дешевле
                                    inventory_file << buy_item << " " << (item_price / 2) << "\n";
                                    cout << "Поздравляем вы купили " << buy_item << endl;
                                    cout << buy_item << " успешно добавлен(а/o) в Ваш инвентарь" << endl;
                                }
                                inventory_file.close();
                            }
                            buy_item_file.close();
                        }
                    }
                }

            }
            buy_file.close();

        }
    }
    // продажа
    void Sell() {
        // открываем для чтения старый инвентарь
        ifstream inv_file;
        inv_file.open(login + "_inventory.txt");

        if (!inv_file.is_open()) {
            cout << "Не удалось открыть инвентарь" << endl;
        }
        else {
            cout << "введите наименование товара который хотите продать: ";

            string sell_item;
            cin >> sell_item;

            // создаем новый файл с инвентарем (новый временный который затем будет основным )
            ofstream temp_inv_file;
            temp_inv_file.open(login + "_temp_inventory.txt");
            if (!temp_inv_file.is_open()) {
                cout << "Не удалось создать или открыть новый инвентарь" << endl;
            }
            else {
                string old_item;
                double old_price;

                bool found = false;

                // читаем построчно старый инвентарь item и price
                while (inv_file >> old_item >> old_price) {
                    // пока не нашли совпадение
                    if (sell_item != old_item) {
                        temp_inv_file << old_item << " " << old_price << "\n";
                    }
                    // если нашли совпадение
                    else {
                        found = true;
                        // запись нового баланса в login_balance.txt
                        cout << "Предмет " << old_item << " успешно продан по цене : " << old_price << " USD" << endl;
                        this->balance += old_price;
                    }
                }

                // закрываем файлы
                inv_file.close();
                temp_inv_file.close();

                // обновление баланса файла если только он есть в инвентаре
                if (found) {
                    ofstream bal_file;
                    bal_file.open(login + "_balance.txt");
                    if (!bal_file.is_open()) cout << "Не удалось открыть файл с балансом" << endl;
                    else bal_file << balance;
                    bal_file.close();
                }
                else {
                    cout << "Товар " << sell_item << " не найден в вашем инвентаре" << endl;
                }
            }

            // удаляем старый файл инвентарь
            // и добавляем переименовываем временный файл с инвентарем
            remove((login + "_inventory.txt").c_str());
            rename((login + "_temp_inventory.txt").c_str(),
                (login + "_inventory.txt").c_str());

        }
    }
    // система казино
    void Casino() {
        double bet;          // ставка игрока
        double get_balance;  // текущий баланс игрока

        int card_bot;        // карта бота (1–10)
        int card_user;       // карта игрока (1–10)

        int bill_bot;        // сумма очков бота
        int bill_user;       // сумма очков игрока

        int choose;          // выбор игрока (1 - стоп, 2 - ещё карта)

        cout << "\tТы зашел в казино!" << endl;
        cout << "Для игры в Black-Jack выберите ставку: ";
        cin >> bet;

        // Загружаем баланс игрока из файла
        ifstream balance_file(login + "_balance.txt");
        if (!balance_file.is_open()) {
            cout << "Не удалось открыть баланс" << endl;
            return;
        }
        balance_file >> get_balance;
        balance_file.close();

        if (bet > get_balance) {
            cout << "Недостаточно средств!" << endl;
            return;
        }

        bill_user = 0;
        bill_bot = 0;

        // Ход игрока
        do {
            card_user = rand() % 10 + 1;
            bill_user += card_user;

            cout << "Вы взяли карту: " << card_user << endl;
            cout << "У вас очков: " << bill_user << endl;

            if (bill_user > 21) {
                cout << "Вы проиграли, перебор!" << endl;
                get_balance -= bet;
                break;
            }

            cout << "1 - достаточно, 2 - беру еще" << endl;
            cout << "Ваш выбор: ";
            cin >> choose;

        } while (choose == 2);

        // Ход бота
        if (bill_user <= 21) {
            cout << "\nХод бота..." << endl;
            while (bill_bot < 17 || (bill_bot < 19 && rand() % 2 == 0)) {
                card_bot = rand() % 10 + 1;
                bill_bot += card_bot;
                cout << "Бот взял карту: " << card_bot << " (сумма: " << bill_bot << ")" << endl;
            }

            cout << "Очков у игрока: " << bill_user << endl;
            cout << "Очков у бота: " << bill_bot << endl;

            if ((bill_bot <= 21 && bill_bot > bill_user) || bill_user > 21) {
                cout << "Вы проиграли :(" << endl;
                get_balance -= bet;
            }
            else if ((bill_user <= 21 && bill_user > bill_bot) || bill_bot > 21) {
                cout << "Вы выиграли!" << endl;
                get_balance += bet;
            }
            else {
                cout << "Ничья!" << endl;
            }
        }

        // Записываем новый баланс
        ofstream balance_f(login + "_balance.txt");
        if (!balance_f.is_open()) {
            cout << "Не удалось открыть файл с балансом" << endl;
        }
        else {
            balance_f << get_balance;
            balance_f.close();
        }

        cout << "Ваш баланс теперь: " << fixed << setprecision(2) << get_balance << " USD" << endl;
    }
};

// создание продуктов
void Create_Products() {
    // Проверяем, существует ли файл
    ifstream check("products.txt");
    if (check.is_open()) {
        cout << "Файл products.txt уже существует, магазин не перезаписан." << endl;
        check.close();
    }
    else {
        // Если файла нет — создаём
        ofstream products_file("products.txt");
        if (!products_file.is_open()) {
            cout << "Не удалось создать файл products.txt!" << endl;
            return;
        }

        // Записываем товары и цены
        products_file << "bread 3.0\n";
        products_file << "milk 5.0\n";
        products_file << "sausages 4.0\n";
        products_file << "cucumber 2.0\n";
        products_file << "shashlik 15.0\n";
        products_file << "pizza 30.0\n";
        products_file << "salami 10.0\n";
        products_file << "cheese 7.5\n";
        products_file << "apple 1.5\n";
        products_file << "chocolate 6.0\n";

        products_file.close();
        cout << "Файл products.txt успешно создан!" << endl;
    }
}


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    srand(time(NULL)); // для казино

    Create_Products();

    cout << "\tДобро пожаловать в игру Shop-Market" << endl;

    User a;
    bool success = false;
    bool valid_choice = false;

    // Авторизация или регистрация
    do {
        cout << "У вас уже есть аккаунт? (Yes - 1) / (No - 2): ";
        int check;
        cin >> check;

        if (check == 1) {
            string log_login, log_password;
            cout << "\tОтлично! Войти в свой аккаунт:" << endl;
            cout << "Введите ваш логин: ";
            cin >> log_login;
            cout << "Введите ваш пароль: ";
            cin >> log_password;

            a.Login(log_login, log_password, success);
        }
        else if (check == 2) {
            string create_login, create_password;
            cout << "\tВы попали в окно регистрации аккаунта!" << endl;
            cout << "Придумайте логин: ";
            cin >> create_login;
            cout << "Придумайте пароль: ";
            cin >> create_password;

            a.Register(create_login, create_password, success);
        }
        else {
            cout << "Ошибка, допустимо только 1 или 2" << endl;
        }

        valid_choice = (check == 1 || check == 2);

    } while (!valid_choice || !success);

    // Если регистрация или авторизация прошла успешно
    if (success) {
        string command;
        int choice;

        cout << "Введите команду (menu - для меню, exit - для выхода): ";
        while (cin >> command) {
            if (command == "menu") {
                cout << "\nМеню:\n"
                    << "1 - Магазин\n"
                    << "2 - Инвентарь\n"
                    << "3 - Купить\n"
                    << "4 - Продать\n"
                    << "5 - Баланс\n"
                    << "6 - Казино\n"
                    << "0 - Выход\n"
                    << "Ваш выбор: ";
                cin >> choice;

                switch (choice) {
                case 1: a.Check_Shop(); break;
                case 2: a.Check_Inventory(); break;
                case 3: a.Buy(); break;
                case 4: a.Sell(); break;
                case 5: a.Check_Balance(); break;
                case 6: a.Casino(); break;
                case 0: return 0;
                }
            }
            else if (command == "exit") {
                break;
            }
            else {
                cout << "Неизвестная команда. Введите menu или exit." << endl;
            }
            cout << "\nВведите команду (menu для меню, exit для выхода): ";
        }
    }

    return 0;
}
