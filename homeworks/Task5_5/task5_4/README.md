# Task 5.4 — Библиотека + GoogleTest с опцией сборки

## Структура

```
task5_4/
├── CMakeLists.txt          # опция BUILD_TESTS
├── main.cpp
├── lib/                    # библиотека
│   ├── CMakeLists.txt
│   ├── average.h / .cpp
│   └── mode_average.h / .cpp
└── tests/                  # тесты
    ├── CMakeLists.txt
    ├── average_test.cpp
    └── mode_average_test.cpp
```

---

## Сборка с тестами (по умолчанию)

```powershell
mkdir build
cd build
cmake ..
cmake --build . --config Debug

# Запуск приложения
.\Debug\app.exe

# Тесты — способ 1: CTest
ctest --output-on-failure -C Debug

# Тесты — способ 2: gtest-бинарник
.\Debug\lib_tests.exe
```

## Сборка без тестов

```powershell
mkdir build
cd build
cmake .. -DBUILD_TESTS=OFF
cmake --build . --config Debug

.\Debug\app.exe      # работает
dir .\Debug          # lib_tests.exe отсутствует
```

## Переключение опции без удаления build/

```powershell
cmake .. -DBUILD_TESTS=ON
cmake --build . --config Debug

cmake .. -DBUILD_TESTS=OFF
cmake --build . --config Debug
```

## Полная пересборка

```powershell
Remove-Item -Recurse -Force build
mkdir build; cd build
cmake ..                          # или -DBUILD_TESTS=OFF
cmake --build . --config Debug
```

---

## Полезные команды

```powershell
# Только упавшие тесты
ctest --rerun-failed --output-on-failure -C Debug

# Фильтр по имени
.\Debug\lib_tests.exe --gtest_filter="AverageTest.*"
.\Debug\lib_tests.exe --gtest_filter="-*Failure*"   # исключить провальные

# Текущее значение опции
cmake -LA -N . | Select-String "BUILD_TESTS"
```

---

## Ожидаемый результат

| Режим | `cmake ..` выводит | Появляется |
|---|---|---|
| `ON` | `Tests: ENABLED — подключаю googletest и tests/` | `app.exe`, `lib_tests.exe` |
| `OFF` | `Tests: DISABLED — googletest и tests/ не подключаются` | только `app.exe` |

При `ON`: 9 тестов, 7 passed, 2 failed (специально — для демонстрации `ASSERT_` vs `EXPECT_`).

---

## Разница ASSERT_ vs EXPECT_

| | `EXPECT_*` | `ASSERT_*` |
|---|---|---|
| При провале | Тест продолжается | Тест прерывается |
| Когда | По умолчанию | Когда дальше нет смысла |

Тесты-демки: `AverageTest.ExpectContinuesAfterFailure`, `AverageTest.AssertStopsAfterFailure`.

---

## Как работает опция

```cmake
option(BUILD_TESTS "Build unit tests with GoogleTest" ON)

if(BUILD_TESTS)
    FetchContent_MakeAvailable(googletest)
    enable_testing()
    add_subdirectory(tests)
endif()
```

`-DBUILD_TESTS=OFF` → gtest не скачивается, `tests/` не подключается.