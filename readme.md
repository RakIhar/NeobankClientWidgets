# About

### Pages
* Визуальная состоявляющая приложения (View)
* Содержат различные элементы управления и валидаторы
* Сигналами могут запросить обновление данных 
* Слотами получают обновленные данные или информацию об ошибке
* Сигналами могут запросить смену страницы
* Никаких данных напрямую не хранят
* pr_ запрос смены page, r_ запрос данных и остальное

### MainWindow
* Хранит сокет
* Принимает запросы на смену страницы от pages (в лямбдах)
* Принимает запросы от pages
    * обработчики - onRequest... 
    * вызываются сервисы, создающие протокол
    * протокол передается в сокет
* На сообщения от сокета вызывает роутер - вызываются все обработчики в сервисах
    * Связывает ответы сервисов со слотами pages

### Services
* Могут содержать соответствующую модель данных
* Прослойка между mainwindow и pages
* Переводят набор данных в протокол
* Обработчики запроса генерируют сигналы, которые направляются в соответствующую страницу

*наверное это очень плохой дизайн, что mainwindow много всякого перенаправляет*

## Socket Wrapper
Сетевой уровень приложения
* Public:
    * void send(QByteArray)
    * void connect(...)
    * void disconnect()
* Signals:
    * void connected()
    * void disconnected()
    * void sent()
    * void received(QByteArray)    
    * void errorOccurred(QString)



- bullet
+ other bullet
* another bullet
    * child bullet

1. ordered
2. next ordered

Some *italic* and **bold** text and `inline code`.

An empty line starts a new paragraph.

Use two spaces at the end  
to force a line break.

A horizontal ruler follows:

---

Add links inline like [this link to the Qt homepage](https://www.qt.io),
or with a reference like [this other link to the Qt homepage][1].

    Add code blocks with
    four spaces at the front.

> A blockquote
> starts with >
>
> and has the same paragraph rules as normal text.

First Level Heading in Alternate Style
======================================

Paragraph.

Second Level Heading in Alternate Style
---------------------------------------

Paragraph.

[1]: https://www.qt.io
