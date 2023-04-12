<h1 align="center"> > Ge0 Collab-Manager < </h1>

.

## > Установка

Клонирование и конфигурирование/сборка с помощью CMake с использованием X86-MSVC

```bash
cmake -B build -A win32 # Configure
cmake --build build --config Release # Build
```

Установка зависимостей с помощью пакетного менеджера vcpkg. Обязательное нахождение по пути ```C:\Program Files\vcpkg```

Установите **cpr**

```bash
cd "C:\Program Files\vcpkg"
./vcpkg install cpr
```

## > Полезные ссылки

[Geode](https://docs.geode-sdk.org/classes/MenuLayer)

[re-script](https://github.com/matcool/re-scripts/blob/main/classes_gd2.cpp)

[Дампы функций](https://github.com/matcool/re-scripts/blob/main/func_dump.txt)

[Для более подробной информации о том, как работает моддинг](https://github.com/matcool/gd-mod-example)

## > VCPkg

[Интеграция с CMake](https://learn.microsoft.com/en-us/vcpkg/users/buildsystems/cmake-integration)
