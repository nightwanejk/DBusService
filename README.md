# DBusService
DBusService — это проект, который предоставляет сервис для работы с разрешениями на выполнение операций с системой через DBus, используя SQLite для хранения данных. Сервис реализует доступ к различным правам в системе и предоставляет возможности для их проверки и выдачи.

Примечание:
Я не смог до конца разобраться с ошибками DBus и поэтому при решении третьего задания, когда клиент пытается получить разрешение у сервиса com.system.permissions после ошибки UnauthorizedAccess ничего не происходит, программа крашится. 

Требования
Операционная система: Linux (Ubuntu 20.04/22.04 или другая дистрибуция с поддержкой DBus и Qt)
Системы сборки: qmake
Библиотеки:
Qt 5.15 или новее
DBus
SQLite

Сборка
git clone https://github.com/nightwanejk/DBusService.git

cd DBusService

sudo apt update

sudo apt install qt5-qmake qtbase5-dev qtbase5-dev-tools libqt5dbus5 libqt5sql5-sqlite

sudo apt install libdbus-1-dev libsqlite3-dev

Перейдите в директорию проекта и выполните команду для сборки с помощью qmake:

qmake

make

После успешной сборки можно запускать проект

./DBusService

Использование:

Для использования используйте утилиту d-feet.

sudo apt install d-feet.

Перед запуском необходимо прописать в терминале: dbus-launch и export двух этих параметров, так же стоит сделать в другом окне терминала.

В первом окне терминала запустите приложение ./DBusService, во втором окне терминала запустите утилиту d-feet и в поиске найдите com.system.permissions и com.system.time. Можно использовать эти методы согласно ТЗ.

Скриншоты работы:
![1](https://github.com/user-attachments/assets/e0f1afb1-ca22-4a33-bdc1-33bfb32996d0)

![2](https://github.com/user-attachments/assets/92c9dd93-0c77-4953-a9ab-1dfd80f74b18)

![3](https://github.com/user-attachments/assets/d5d73b00-f087-4450-acc3-d962ca06139d)

![4](https://github.com/user-attachments/assets/f1bc8e2f-eb71-412d-afab-d8b5f40707b7)

![5](https://github.com/user-attachments/assets/41425ce8-a36a-4249-99d4-8c0dcc8c64c0)

![6](https://github.com/user-attachments/assets/135549dc-fbc4-4433-b771-b8d6822de607)

![7](https://github.com/user-attachments/assets/edea4d10-7548-4393-a0fc-699c2704c6c1)

![8](https://github.com/user-attachments/assets/237f5674-5e87-4d23-bf24-6f39900229a8)


