## Запуск программы и тестов

```bash
mkdir build
cd build
cmake ..
cmake --build . --config Debug

./Debug/app.exe

# Тесты
ctest --output-on-failure -C Debug
```