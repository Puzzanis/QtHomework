# Домашнее задание к занятию "Работа с сетью. UDP клиент"

### Задание 1. 

Доработать представленное приложение, чтобы появился функционал отправки и приема пользовательских датаграмм.

1. В текущее приложение добавить:
 * виджет для ввода текста;
 * кнопку "Отправить датаграмму".
2. При нажатии на кнопку "Отправить датаграмму" приложение должно отправить введенный пользователем текст при помощи объекта класса QUdpSocket на адрес 127.0.0.1 (localhost)
3. Приложение должно принять эту датаграмму и отобразить в виджете "Принятые данные" сообщение вида: "Принято сообщение от ***адрес отправителя***, 
   размер сообщения(байт) ***Х***
   * Х - размер введенного в виджет текста
   * Адрес отправителя - адрес с которого была осуществлена отправка датаграммы

------

