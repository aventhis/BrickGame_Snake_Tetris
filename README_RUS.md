### README in Russian:

# BrickGame Snake

## Введение

`BrickGame Snake` — это проект на C++, реализующий игру "Змейка" с использованием принципов объектно-ориентированного программирования. Игра включает библиотеку для логики игры и графический интерфейс для взаимодействия с пользователем. Проект также следует паттерну MVC для разделения логики игры и интерфейса.

## Особенности

- Классическая механика игры "Змейка".
- Используется конечный автомат для формализации логики игры.
- Реализован паттерн MVC для разделения логики, представления и контроллера.
- Поддержка системы подсчета очков и записи максимального результата.
- Механика уровней, увеличивающая скорость змейки по мере прогресса игрока.

## Структура проекта

- **Библиотека**: Логика игры находится в папке `src/brick_game/snake`.
- **Графический интерфейс**: Пользовательский интерфейс находится в папке `src/gui/desktop`.
- **Консольный интерфейс**: Поддерживает игру "Змейка" из проекта BrickGame v1.0.

## Механика игры

1. **Движение змейки**: Змейка движется на один блок автоматически при истечении игрового таймера.
2. **Яблоки**: Длина змейки увеличивается на одну клетку при поедании яблока.
3. **Условие победы**: Игрок выигрывает, когда длина змейки достигает 200 единиц.
4. **Условие поражения**: Игрок проигрывает, если змейка врезается в саму себя или в границу поля.
5. **Управление**: Игрок может менять направление движения змейки с помощью стрелок и ускорять её с помощью клавиши действия.

## Дополнительные особенности

### Подсчет очков и рекорд игры

- Игра отслеживает количество очков игрока, за каждое съеденное яблоко начисляется одно очко.
- Максимальный рекорд сохраняется между сеансами.

### Механика уровней

- Скорость змейки увеличивается с каждым новым уровнем (каждые 5 очков), до максимума в 10 уровней.


## Цели Makefile

- **make all**: Собрать весь проект, включая логику игры и графический интерфейс.
- **make clean**: Удалить все скомпилированные объектные файлы и исполняемые файлы.
- **make test**: Скомпилировать и запустить модульные тесты для проверки логики игры.
- **make install**: Установить игру на вашу систему.
- **make uninstall**: Удалить игру с вашей системы.
- **make dist**: Создать пакет для распространения проекта.
- **make dvi**: Сгенерировать документацию проекта.
- **make gcov_report**: Сгенерировать отчет о покрытии кода в формате HTML.