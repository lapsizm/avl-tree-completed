
## Описание

Проект представляет собой реализацию сбалансированного бинарного дерева поиска (BST) и словаря, который использует это дерево для хранения и поиска пар ключ-значение. 

### Классы

- **`BstTree`**: Реализует сбалансированное бинарное дерево поиска.
- **`dictionary`**: Реализует словарь, использующий `BstTree` для хранения данных.

## Основные функции

### Класс `BstTree`

- **`BstTree()`**: Конструктор по умолчанию. Создает пустое дерево.
- **`BstTree(K key, V value)`**: Конструктор, создающий дерево с одним узлом, содержащим заданный ключ и значение.

#### Публичные методы

- **`void Insert(K key, V value)`**: Вставляет новый элемент в дерево.
- **`bool Contains(K key)`**: Проверяет наличие элемента с указанным ключом в дереве.
- **`void Remove(K key)`**: Удаляет элемент с указанным ключом из дерева.
- **`size_t size() const`**: Возвращает количество элементов в дереве.
- **`size_t height()`**: Возвращает высоту дерева.
- **`void PrintOnTheSide() const`**: Выводит дерево на экран в виде графической структуры.
- **`void inorderTraversal()`**: Выполняет обход дерева в порядке "in-order" (сначала левое поддерево, затем корень, затем правое поддерево).
- **`void preorderTraversal()`**: Выполняет обход дерева в порядке "pre-order" (сначала корень, затем левое поддерево, затем правое поддерево).
- **`void postorderTraversal()`**: Выполняет обход дерева в порядке "post-order" (сначала левое поддерево, затем правое поддерево, затем корень).

#### Приватные методы

- **`void RotateWithLeftChild(std::unique_ptr<TreeNode> &node) noexcept`**: Выполняет вращение с левым ребенком.
- **`void RotateWithRightChild(std::unique_ptr<TreeNode> &node) noexcept`**: Выполняет вращение с правым ребенком.
- **`void RotateDoubleWithRightChild(std::unique_ptr<TreeNode> &node) noexcept`**: Выполняет двойное вращение с правым ребенком.
- **`void RotateDoubleWithLeftChild(std::unique_ptr<TreeNode> &node) noexcept`**: Выполняет двойное вращение с левым ребенком.
- **`void FixHeight(std::unique_ptr<TreeNode> &t) noexcept`**: Обновляет высоту узла.
- **`void Balance(std::unique_ptr<TreeNode> &t)`**: Балансирует дерево.
- **`std::unique_ptr<TreeNode> &Insert(K key, V value, std::unique_ptr<TreeNode> &node)`**: Вставляет элемент в поддерево.
- **`bool Contains(K key, std::unique_ptr<TreeNode> &node)`**: Проверяет наличие элемента в поддереве.
- **`TreeNode *Search(K key, std::unique_ptr<TreeNode> &node)`**: Ищет узел с указанным ключом.
- **`void Remove(K key, std::unique_ptr<TreeNode> &node)`**: Удаляет узел с указанным ключом.
- **`std::unique_ptr<TreeNode> &findMin(std::unique_ptr<TreeNode> &node)`**: Находит узел с минимальным ключом в поддереве.
- **`std::unique_ptr<TreeNode> &findMax(std::unique_ptr<TreeNode> &node) const`**: Находит узел с максимальным ключом в поддереве.
- **`void PrintTree(const std::unique_ptr<TreeNode> &node, int space) const`**: Выводит дерево на экран в виде графической структуры.
- **`uint8_t HeightOfTree(std::unique_ptr<TreeNode> &node)`**: Возвращает высоту поддерева.
- **`void inorderTraversal(std::unique_ptr<TreeNode> &node)`**: Выполняет обход поддерева в порядке "in-order".
- **`void preorderTraversal(std::unique_ptr<TreeNode> &node)`**: Выполняет обход поддерева в порядке "pre-order".
- **`void postorderTraversal(std::unique_ptr<TreeNode> &node)`**: Выполняет обход поддерева в порядке "post-order".

### Класс `dictionary`

- **`dictionary()`**: Конструктор по умолчанию. Создает пустой словарь.
- **`dictionary(K key, V value)`**: Конструктор, создающий словарь с одной парой ключ-значение.

#### Публичные методы

- **`V &operator[](K key)`**: Оператор доступа по ключу.
- **`void Insert(K key, V value)`**: Вставляет новую пару ключ-значение в словарь.
- **`void Remove(K key)`**: Удаляет элемент с указанным ключом из словаря.
- **`void Print()`**: Выводит дерево на экран в виде графической структуры.
- **`size_t Size()`**: Возвращает количество элементов в словаре.
- **`bool empty() const`**: Проверяет, пуст ли словарь.
- **`typename BstTree<K, V>::TreeNode *Find(K key)`**: Ищет узел с указанным ключом.
- **`bool Contains(K key)`**: Проверяет наличие элемента с указанным ключом в словаре.
- **`void Clear()`**: Удаляет все элементы из словаря.


## Сборка и установка

1. Убедитесь, что у вас установлен компилятор C++.
2. Создайте файл `CMakeLists.txt` (если используется CMake) для сборки проекта:

    ```cmake
    cmake_minimum_required(VERSION 3.10)
    project(BMSTU)

    set(CMAKE_CXX_STANDARD 17)

    add_executable(bmstu main.cpp)  # Замените main.cpp на ваш файл с основным кодом
    ```

3. Выполните следующие команды для сборки:

    ```sh
    mkdir build
    cd build
    cmake ..
    make
    ```

