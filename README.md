- [[#Требования]]
- [[#Сборка Debian-пакета]]
- [[#Сборка из исходников]]
- [[#Тестирование]]
- [[#Структура проекта]]
- [[#CI/CD]]

# Требования

Для сборки проекта необходимы:
- **CMake** >= 3.5
- **Qt5** (модули: Widgets, Core, Gui, Test)
- Компилятор с поддержкой **C++17** (GCC/Clang)

Установка зависимостей в Ubuntu / Astra Linux:

```bash
sudo apt-get update
sudo apt-get install -y build-essential cmake qtbase5-dev qtbase5-dev-tools
```

# Сборка Debian-пакета
Для создания установочного пакета `.deb`:

## 1. Клонирование репозитория
```bash
git clone https://github.com/Sibro18/astra_developer_test_task.git
cd astra_developer_test_task
```

## 2.Убедитесь, что установлены инструменты упаковки:
  ```bash
  sudo apt-get install -y debhelper dpkg-dev
  ```

## 3.Соберите пакет из корневой директории проекта:
  ```bash
  dpkg-buildpackage -us -uc -b
  ```

## 4.Установите полученный пакет:
  ```bash
  sudo dpkg -i ../astra-developer-test-task_0.1-1_amd64.deb
  ```

## 5. Запустите установленное приложение:
  ```bash
  astra_developer_test_task
  ```

# Сборка из исходников

## 1. Клонирование репозитория
```bash
git clone https://github.com/Sibro18/astra_developer_test_task.git
cd astra_developer_test_task
```

## 2. Конфигурация и сборка
Создайте директорию сборки и сконфигурируйте проект:
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

## 3. Запуск приложения
```bash
./build/astra_developer_test_task
```

# Тестирование
Проект включает юнит-тесты для проверки утилитных функций.

## 1. Включение тестов при сборке
```bash
cmake -B build -DBUILD_TESTS=ON
cmake --build build
```
## 2. Запуск тестов
```bash
cd build
ctest -V
```
Или запустите бинарники тестов напрямую для подробного вывода:
```bash
./tests/test_format_utils
./tests/test_file_utils
```

# Структура проекта
```
.
├── src/
│   ├── main.cpp
│   ├── main_window/                    # Главное окно приложения
│   ├── custom_system_model/            # Кастомная модель файловой системы с асинхронным расчётом
│   ├── custom_system_model_delegate/   # Делегат для форматирования ячеек столбца "Размер"
│   ├── custom_sort_filter_proxy_model/ # Прокси-модель для фильтрации
│   └── utils/                          # Библиотека утилит (FormatUtils, FileUtils)
├── tests/                              # Юнит-тесты (Qt Test)
├── debian/                             # Файлы для упаковки в deb пакет
├── CMakeLists.txt                      # Основная конфигурация CMake
└── README.md
```

# CI/CD

Проект использует GitHub Actions для непрерывной интеграции:

- **Build**: Компиляция проекта на Ubuntu.
- **Test**: Автоматический запуск юнит-тестов.
- **Package**: Сборка `.deb` артефакта при каждом пуше в ветку `main`.

Статус сборок доступен во вкладке [Actions](https://github.com/Sibro18/astra_developer_test_task/actions).
