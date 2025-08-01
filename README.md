# database
база данных

1)Перед запуском программы вызывается комманда:

make



2)Запуск программы:
Подается три файла: файл с командами, файл со списком студентов, файл для записи результатов. Программа должна получать все параметры в качестве аргументов командной строки и стандарт-
ного ввода. Аргументы командной строки:
filename – имя файла, откуда надо прочитать список.
Например, запуск
cat commands.txt | ./a.out a.txt > result.txt
означает, что файл commands.txt подается на стандартный ввод, список надо прочитать из файла
a.txt, а результаты будут перенаправлены со стандартного вывода в файл result.txt.



Все команды имеют следующий вид:

• Разделителем команд является “;”, разделителями аргументов команды являются пробел, сим-
вол табуляции и символ новой строки.

• quit; – завершить работу

• insert (<name>, <phone>, <group>); – добавить объект типа record с указанными полями
в список;

• select <условия на выводимые поля> [where <условие поиска>] [order by <условия сор-
тировки>]; – вывести элементы списка, удовлетворяющие указанным в команде условиям
(утверждение where), и в указанном в команде виде (утверждение <условия на выводимые
поля>) и в указанном порядке (утверждение order by <условия сортировки>). При отсутствии
утверждения where запросу удовлетворяют все элементы списка, при отсутствии утверждения
order by <условия сортировки> найденные элементы выводятся без сортировки.

• delete [where <условие поиска>]; – удалить элементы списка, удовлетворяющие указанным в
команде условиям. При отсутствии утверждения where запросу удовлетворяют все элементы
списка (т.е. по запросу delete; удаляется весь список).



<условия на выводимые поля> имеют вид:

• <список полей> – выводить указанные поля в указанном порядке, список состоит из разде-
ленных запятыми имен полей без повторений; например, group, name – выводить только поле
поле group и поле name (в этом порядке);

• * – выводить все поля, эквивалентен name, phone, group



<условие поиска> имеют вид:

• <условие поиска на одно поле> – задает одно условие на одно поле записи record.

• <условие поиска на одно поле 1> and <условие поиска на одно поле 2>

• <условие поиска на одно поле 1> or <условие поиска на одно поле 2>

• <условие поиска на одно поле 1> and <условие поиска на одно поле 2> and <условие
поиска на одно поле 3>

• <условие поиска на одно поле 1> or <условие поиска на одно поле 2> or <условие поиска
на одно поле 3>
Если в <условие поиска> участвует более одного условия на поля записи record, то они задают
условия на разные поля записи record.



<условие поиска на одно поле> записи record имеет вид:

• <поле> <оператор> <выражение>, где
– <поле> – имя поля (name, phone, value)
– <оператор> – логический оператор отношения: = – равно, <> – не равно, <, >, <=, >= –
соответствуют языку C
– <выражение> – константное выражение соответствующего типа

• <поле> like <образец> где
– <поле> – имя поля символьного типа (т.е. только name)
– <образец> – образец поиска. Может включать в себя специальные символы:
6∗ ’_’ – соответствует 1 любому символу, а символы "\_" и "\\" соответствуют лите-
ральным символам "_" и "\"
∗ ’%’ – соответствует 0 или более любым символам, а символы "\%" и "\\" соответ-
ствуют литеральным символам "%" и "\"
∗ ’[n–m]’ (n, m – символы) – соответствует 1 любому символу, имеющему код в диа-
пазоне n . . . m, а символы "\[", "\]" и "\\" соответствуют литеральным символам "[",
"]" и "\"
∗ ’[bn–m]’ (n, m – символы) соответствует любому символу, имеющему код, не со-
держащийся в диапазоне n . . . m, а символы "\[", "\]", "\b" и "\\" соответствуют
литеральным символам "[", "]", "b" и "\"
Условие выполнено, если <поле> соответствует образцу поиска.

• <поле> not like <образец> где
– <поле> – имя поля символьного типа (т.е. только name)
– <образец> – образец поиска.
Условие выполнено, если <поле> не соответствует образцу поиска.



Примеры команд:

• insert (Student, 1234567, 208); – добавить запись с указанными полями (если такой не суще-
ствует).

• select group, name where phone = 1234567 and name = Student; – вывести поля group и name
для всех элементов списка, у которых поле phone равно 1234567 и поле name равно "Student".

• select * where phone >= 1234567 and name like St% order by group; – вывести все поля
для всех элементов списка, у которых поле phone больше или равно 1234567 и поле name
соответствует образцу поиска "St%". При выводе упорядочить результаты по значению поля
group.

• select name, phone where group = 208 and phone <> 1234567; – вывести поля name и phone
для всех элементов списка, у которых поле group равно 208 и поле phone не равно 1234567.

• select * where name = Student or phone = 1234567; – вывести все поля для всех элементов
списка, у которых поле name равно "Student" или поле phone равно 1234567.

• select name where name not like St% and phone = 1234567 and group = 208 order by name; –
вывести поле name для всех элементов списка, у которых поле name не соответствует образцу
поиска "St% поле phone равно 1234567 и поле group равно 208. При выводе упорядочить
результаты по значению поля name.

• select * order by name, phone, group; – вывести все поля всех элементов списка, упорядочив
по значению поля name, для записей с одинаковым значением поля name упорядочить их по
значению поля phone, если и поле phone тоже одинаковое, то упорядочить по значению поля
group.

• delete where name = Student; – удалить все элементы списка, у которых поле name равно
"Student".

• delete where phone = 1234567 and group = 208 and name not like Student; – удалить все
элементы списка, у которых поле phone равно 1234567, поле group равно 208, а имя не равно
"Student".



В указанном файле находится дерево в формате:

Слово-1   Целое-число-1   Целое-число-2

Слово-2   Целое-число-3   Целое-число-4

  ...          ...
  
Слово-n   Целое-число-2n-1 Целое-число-2n


где слово – последовательность алфавитно-цифровых символов без пробелов(имя человека/студента). Длина слова неизвестна. Далее записаны два числа(номер телефона студента и номер группы). Все записи в файле различны (т.е. нет двух, у которых совпадают все 3 поля). Концом ввода считается конец файла.
Файл a.txt приложен как пример
