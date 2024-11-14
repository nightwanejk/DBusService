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

