from tkinter import *
from tkinter import messagebox
from mydb import mydb
class TestQuestion: # класс Тестовый вопрос
    def __init__(self,text,correct_variant,variant_of_ansver):
        self.text = text # текст вопроса
        self.correct_variant = correct_variant # правильный вариант
        self.variant_of_answer= variant_of_ansver # варианты ответа
class Test: # класс Тест
    def __init__(self,title='test',test_question_list = []):
        self.title = title # название теста
        self.test_question_list = test_question_list # список тестовых вопросов
        self.total_questions = len(test_question_list) # количество вопросов в тесте
class UserForm(Toplevel):
    def __init__(self, parent):
        super().__init__(parent)
        self.geometry("225x150")# геометрия окна
        self.title("Регистрация") # надпись вверху окна
        self.email = StringVar()
        self.fio = StringVar()
        self.password= StringVar()

        label = Label(self, text="Создать пользователя" )
        entry_email = Entry(self, textvariable=self.email)
        entry_fio = Entry(self, textvariable=self.fio)
        entry_pass = Entry(self, textvariable=self.password, show="*")
        btn = Button(self, text="Принять", command=self.destroy)

        label.grid(row=0, columnspan=3)
        Label(self, text="Email:").grid(row=1, column=0)
        Label(self, text="ФИО:").grid(row=2, column=0)
        Label(self, text="Пароль:").grid(row=3, column=0)
        entry_email.grid(row=1, column=1)
        entry_fio.grid(row=2, column=1)
        entry_pass.grid(row=3, column=1)
        btn.grid(row=4, columnspan=3)
    def open(self):
        self.grab_set()
        self.wait_window()
        fio = self.fio.get()
        password = self.password.get()
        email = self.email.get()
        return (email, fio, password)
class LoginForm(Toplevel):
    def __init__(self, parent):
        super().__init__(parent)
        self.geometry("225x150")# геометрия окна
        self.title("Авторизация") # надпись вверху окна
        self.email = StringVar()
        self.password= StringVar()

        label = Label(self, text="Авторизация пользователя" )
        entry_email = Entry(self, textvariable=self.email)
        entry_pass = Entry(self, textvariable=self.password, show="*")
        btn = Button(self, text="Принять", command=self.destroy)

        label.grid(row=0, columnspan=3)
        Label(self, text="Email:").grid(row=1, column=0)
        Label(self, text="Пароль:").grid(row=2, column=0)
        entry_email.grid(row=1, column=1)
        entry_pass.grid(row=2, column=1)
        btn.grid(row=3, columnspan=3)
    def open(self):
        self.grab_set()
        self.wait_window()
        password = self.password.get()
        email = self.email.get()
        return (email,password)
class TestInterface: # интерфейс для теста
    def __init__(self,test):
        self.root = Tk() # основное окно
        self.root.title(test.title) # надпись вверху окна
        self.root.geometry("1000x800")# геометрия окна
        self.font = "Times 14"# шрифт виджетов
        self.lbl_text = StringVar()# переменная lbl
        self.lbl_text.set("Для инициализации запуска программы нажмите кнопку <<Войти>>")
        self.lbl = Label(textvariable=self.lbl_text,font = self.font,wraplength =300)
        self.lbl.pack(side=TOP)#расположение вверху окна
        self.checkbtn_list =[] #список галочек
        self.score = 0 #счет
        self.variant = StringVar() # вариант ответа выбранный пользователем
        self.variant.set(0) # вариант не выбран
        self.n = 0 # счетчик шагов
        self.lbl_checked = Label(font = "Times 14") # lbl который пишет Правильно\ неправильно
        self.lbl_checked.pack(side=BOTTOM) # внизу окна
        self.loginbtn = Button(text="Войти",font = "Times 14", command=self.open_windowlogin) # кнопка авторизации и начала тестирования
        self.loginbtn.pack(side=BOTTOM) #
        self.btn = Button(text="Регистрация",font = "Times 14", command=self.open_windowusers) # кнопка регистрации
        self.btn.pack(side=BOTTOM) #
        self.db=mydb()#тут добавляем дб и вызываем ее создание
        self.db.create_schema()
        self.root.mainloop() #обновление окна
    def open_windowusers(self):
        registration = UserForm(self.root)
        email,fio,password=registration.open()
        self.db.register(email,fio,password) # регистрация с формы
    def open_windowlogin(self):
        login = LoginForm(self.root)
        email,password=login.open()
        self.userid=self.db.login(email,password) # авторизация с формы
        if(self.userid is None):
            messagebox.showerror("Ошибка авторизации","Такого пользователя не существует!")
        else:
            self.change_lbl_text()
            self.loginbtn.destroy()
    def change_lbl_text(self): #изменение текста верхнего lbl
        if self.n< test.total_questions:# если число шагов меньше количества вопросов в тесте:
            self.btn.config(text="Следующий вопрос", state=DISABLED,command = self.next_quest) #кнопка меняет текст и тд...
            self.lbl_text.set("Вопрос № {}\n{}".format(self.n+1,test.test_question_list[self.n].text)) # меняется текст лейбла
            self.set_check_btn()# метод установки галочек
        else:
            print("Конец.") # чтобы понять что вопросы кончились
            self.end() # метод конец
    def set_check_btn(self): #метод установки галочек
        for key,value in test.test_question_list[self.n].variant_of_answer.items(): # для ключ,значение присвоить ключ,значение из каждого варианта ответа тестового вопроса
            ch =Checkbutton(text ="{}) {}".format(key,value),font = "Times 14",onvalue =key,variable =self.variant,command = self.checked,)# создает галочку
            ch.pack() # прикручивает к окну
            self.checkbtn_list.append(ch) # добавляет в список галочек
    def remove_check_btn(self): # метод удаляет галочки с окна
        if self.checkbtn_list: # если список не пустой
            for ch in self.checkbtn_list: # каждую галочку
                ch.destroy() # убирает с окна
            self.checkbtn_list.clear() # очищает список
    def checked(self): # проверка варианта с вариантом ответа
        if self.variant.get() == test.test_question_list[self.n].correct_variant: # если сходится
            self.score+=1 # прибавлет балл
            self.btn.config(state = NORMAL) #делает кнопку активной
        else:
            self.btn.config(state = NORMAL) #делает кнопку активной
    def reset(self): # обнуляет переменные в начальное положение
        self.n = 0
        self.score = 0
        self.variant.set(0)
        self.remove_check_btn()
        self.lbl_text.set("Тест МДК.03.01. Сопровождение и продвижение программного обеспечения отраслевой направленности Специальности 09.02.05 Прикладная информатика по отраслям")
        self.lbl_checked.config(text='')
        self.btn.config(text="Начать", command=self.change_lbl_text)
    def next_quest(self): # следующий шаг
        self.n+=1
        self.variant.set(0)# обнуляет вариант ответа
        self.remove_check_btn()# удаляет старые галки
        self.change_lbl_text() # изменяет лейбл на следующий вопрос
    def end(self): # титры в конце
        self.remove_check_btn()
        self.lbl_checked.config(text="Набрано баллов: {}".format(self.score))
        if self.score <= 10:
            self.lbl_text.set("Тест окончен. Ваша оценка - 2")
        elif (self.score >= 11)&(self.score <= 20):
            self.lbl_text.set("Тест окончен. Ваша оценка - 3")
        elif (self.score >= 21)&(self.score <= 30):
            self.lbl_text.set("Тест окончен. Ваша оценка - 4")
        elif(self.score >= 35):
            self.lbl_text.set("Тест окончен. Ваша оценка - 5")
        self.db.saveresult(self.userid,self.score)
        self.btn.config(text="Пройти тест снова", command=self.reset)
test_question_list=[]
test_question_list.append(TestQuestion("Программное обеспечение  – это:", 'a', {'a': 'совокупность программ, выполненных вычислительной системой.', 'b': 'программа, выполненная вычислительной системой', 'c': 'устройство ввода информации.', 'd': 'операционная система'}))
test_question_list.append(TestQuestion("Совместимость – это:", 'b', {'a': 'способность пользователей взаимодействовать друг с другом', 'b': 'способность компонентов взаимодействовать друг с другом', 'c': 'доверительные отношения компонентов персонального компьютера между собой.'}))
test_question_list.append(TestQuestion("Программа-оболочка:", 'b', {'a': 'это программы, управляющие файловой системой и планирующие задания для компьютера;', 'b': ' это программы, созданные для упрощения работы со сложными программными системами,\n такими, например, как DOS. Они преобразуют неудобный командный пользовательский интерфейс\n в дружественный графический интерфейс или интерфейс типа "меню".', 'c': 'это комплекс взаимосвязанных системных программ, назначение которого — организовать'}))
test_question_list.append(TestQuestion("Не существующая среда обитания вирусов:", 'b', {'a': 'Загрузочная', 'b': 'Игровая', 'c': 'Файловая'}))
test_question_list.append(TestQuestion("Основная цель AppLocker:", 'b', {'a': 'Решение  проблем совместимости, т. е. позволяет выполнять программы,\n написанные для более ранних версий Windows', 'b': 'Предоставление администраторам возможности создания правил,\n которые разрешают или запрещают выполнение файлов', 'c': 'Решение проблемы проверки DLL файлов'}))
test_question_list.append(TestQuestion("Event Viewer – это:", 'a', {'a': 'Это средство, предназначенное для просмотра подробных сведений о значимых событиях,\n которые возникают в системе', 'b': 'Программа виртуализации, позволяющая запускать прямо в рабочей среде различные операционные системы', 'c': 'Это программа, которая решает проблемы совместимости,\n т. е. позволяет выполнять программы, написанные для более ранних версий Windows'}))
test_question_list.append(TestQuestion("Профиль не существующий в Windows:", 'c', {'a': 'блуждающий', 'b': 'локальный', 'c': 'глобальный'}))
test_question_list.append(TestQuestion("DNS – это:", 'c', {'a': 'Разрешение доменных имен', 'b': 'Главная вычислительная машина', 'c': 'Служба доменных имен'}))
test_question_list.append(TestQuestion("TCP/IP – это:", 'b', {'a': 'Интернет-протокол; протокол сетевого уровня из набора протоколов Интернет', 'b': 'Протокол управления передачей информации, основной протокол транспортного и сеансового уровней', 'c': 'Разрешение доменных имен; процесс преобразования имени компьютера в соответствующий IP-адрес'}))
test_question_list.append(TestQuestion("Ранжирование – это:", 'b', {'a': 'Внутренняя и внешняя оптимизация сайта', 'b': 'Степень соответствия содержания страницы к запросу пользователя', 'c': 'Упорядочивание результатов поиска в соответствии с запросом пользователя'}))
test_question_list.append(TestQuestion("Релевантность – это:", 'a', {'a': 'Степень соответствия содержания страницы к запросу пользователя', 'b': 'Упорядочивание результатов поиска в соответствии с запросом пользователя', 'c': 'Внутренняя и внешняя оптимизация сайта'}))
test_question_list.append(TestQuestion("Вид маркетингового исследования, использующийся в случае, когда человек не хочет представить информацию самостоятельно:", 'c', {'a': 'Опрос', 'b': 'Анкетирование', 'c': 'Наблюдение'}))
test_question_list.append(TestQuestion("Верное утверждение:", 'a', {'a': 'Компьютерный вирус – вид вредоносного программного обеспечения,\n способный создавать копии самого себя и внедрятся в код других программ.', 'b': 'Компьютерные вирусы могут существовать в системе в разных стадиях функционирования.', 'c': 'Латентные стадии размножают свой код всеми им доступными способами'}))
test_question_list.append(TestQuestion("Драйвер устройств - это:", 'a', {'a': 'Специальные системные программы, применяемые для управления внешними устройствами компьютера', 'b': 'Программы, облегчающая процесс создания новых программ для компьютера', 'c': 'Программы для создания графического интерфейса'}))
test_question_list.append(TestQuestion("Толчок для внедрения CRM системы:", 'a', {'a': 'увеличение конкуренции', 'b': 'увеличение объемов производства', 'c': 'освоение новых рынков сбыта'}))
test_question_list.append(TestQuestion("Предоставление скидок на основе накопления:", 'a', {'a': 'позволяют получить долгосрочную лояльность клиента', 'b': 'позволяет привлечь новых клиентов', 'c': 'увеличивает себестоимость продукции'}))
test_question_list.append(TestQuestion("База данных – это:", 'b', {'a': 'Минимальное подмножество полей таблицы, значения которых однозначно определяют запись.', 'b': 'Совокупность специальным образом организованных данных о конкретной предметной области.', 'c': 'База данных, представленная в виде таблиц.'}))
test_question_list.append(TestQuestion("Язык SQL предназначен в первую очередь:", 'c', {'a': 'Создание программ.', 'b': 'Устранения совместимости ПО.', 'c': 'Выполнения запросов.'}))
test_question_list.append(TestQuestion("Жизненный цикл ПО – это период времени начинающийся:", 'a', {'a': 'с момента понятия о необходимости создания ПО', 'b': 'с момента создания', 'c': 'с момента выхода в продажу','d': 'с момента начала пользования'}))
test_question_list.append(TestQuestion("Исправление ошибок наиболее затратное:", 'b', {'a': 'на ранних этапах', 'b': 'на поздних этапах', 'c': 'на любых этапах'}))
test_question_list.append(TestQuestion("Использование разрешения экрана 640 х 480 означает:", 'c', {'a': 'Ограничение набора цветов в программе.\n Некоторые старые программы используют ограниченный набор цветов', 'b': 'Отключение тем оформления в программе', 'c': 'Запуск программы в уменьшенном окне'}))
test_question_list.append(TestQuestion("Идентификация – это:", 'b', {'a': 'Средство, предназначенное для просмотра подробных сведений о значимых событиях,\n которые возникают в системе', 'b': 'Присвоение пользователю соответствующей ему разграничительной политики доступа на защищаемом объекте,\n при указании им своего имени', 'c': 'Проверка правильности вводимого пароля,\n подтверждение однозначного соответствия между регистрирующимся пользователем\n и идентифицированным пользователем'}))
test_question_list.append(TestQuestion("Аутентификация – это:", 'a', {'a': 'Проверка правильности вводимого пароля,\n подтверждение однозначного соответствия между регистрирующимся пользователем\n и идентифицированным пользователем', 'b': 'Средство, предназначенное для просмотра подробных сведений о значимых событиях,\n которые возникают в системе', 'c': 'Присвоение пользователю соответствующей ему разграничительной политики доступа на защищаемом объекте,\n при указании им своего имени'}))
test_question_list.append(TestQuestion("URL – это:", 'a', {'a': 'Унифицированный указатель информационного ресурса', 'b': 'Разрешение доменных имен', 'c': 'Интернет-протокол; протокол сетевого уровня из набора протоколов Интернет'}))
test_question_list.append(TestQuestion("Сайт «Вконтакте» относится к виду:", 'c', {'a': 'Внутрисетевой', 'b': 'Экстра-сетевой', 'c': 'Публичный'}))
test_question_list.append(TestQuestion("ERP-система – это:", 'c', {'a': 'автоматизация процессов изготовления для снижения себестоимости продукции', 'b': 'перестройка деловых процессов для достижения улучшения деятельности компании', 'c': 'автоматизация управления ресурсами предприятия для достижения улучшения деятельности компании'}))
test_question_list.append(TestQuestion("Реклама в СМИ:", 'b', {'a': 'позволяет завоевать лояльность клиента', 'b': 'позволяет привлечь новых клиентов', 'c': 'увеличивают себестоимость продукции'}))
test_question_list.append(TestQuestion("Жизненный цикл ПО – это период времени:", 'a', {'a': 'до полного его изъятия.', 'b': 'до создания', 'c': 'до выхода в продажу', 'd': 'до начала пользования'}))
test_question_list.append(TestQuestion("Достоинство каскадной модели жизненного цикла ПО:", 'b', {'a': 'Взаимодействие заказчика с разрабатываемой системой начинается на раннем этапе.', 'b': 'На каждой стадии формируется законченный набор проектной документации,\n отвечающий критериям полноты и согласованности', 'c': 'Обеспечивает определение полных требований к ПО'}))
test_question_list.append(TestQuestion("Метод, не относящийся  к маркетинговому исследованию:", 'd', {'a': 'Наблюдение', 'b': 'Опрос', 'c': 'Анкетирование','d': 'Приобретение'}))
test_question_list.append(TestQuestion("Основные этапы жизненного цикла:", 'a', {'a': 'Анализ', 'b': 'Изобретение', 'c': 'Реализация', 'd':'Выборка'}))
test_question_list.append(TestQuestion("Мобильность – это:", 'a', {'a': 'Способность программного обеспечения бить перенесенным из одного окружения в другое', 'b': 'Способность программного обеспечения сохранять свой уровень данных', 'c': 'Способность программного обеспечения передавать результат своей работы из одного окружения в другое'}))
test_question_list.append(TestQuestion("Мониторинг – это:", 'a', {'a': 'Непрерывный процесс наблюдения и регистрации параметров объекта, в сравнении с заданными критериями.', 'b': 'Выборочный процесс наблюдения и регистрации параметров объекта', 'c': 'Способность программного продукта регистрировать параметры.'}))
test_question_list.append(TestQuestion("Тестирование – это:", 'a', {'a': 'Процесс, позволяющий убедиться в том, что в программе нет ошибок.', 'b': 'Процесс, позволяющий исправить ошибки в программе', 'c': 'Процесс, позволяющий перенести программный продукт из одного окружения в другое'}))
test_question_list.append(TestQuestion("Мотивация – это:", 'a', {'a': 'Процесс стимулирования кого-либо  к деятельности, направленной на достижение целей.', 'b': 'Процесс отбора более квалифицированных кадров среди персонала', 'c': 'Вид маркетингового исследования, заключающийся в наблюдении за объектами'}))
test_question_list.append(TestQuestion("Вид шрифта наиболее читаемый:", 'a', {'a': 'С засечками', 'b': 'Гротеск (без засечек)', 'c': 'Шрифты имеют одинаковую читабельность'}))
test_question_list.append(TestQuestion("Тег <TITLE>:", 'a', {'a': 'Задает заголовок сайта', 'b': 'Задает ключевые слова', 'c': ' Даёт описание страницы'}))
test_question_list.append(TestQuestion("Тег <DESCRIPTION >:", 'c', {'a': 'Задает заголовок сайта', 'b': 'Задает ключевые слова', 'c': 'Даёт описание страницы'}))
test_question_list.append(TestQuestion("Внешняя оптимизация сайта – это:", 'b', {'a': 'Подбор ключевых слов и фраз для сайта', 'b': 'Процесс наращивания количества и качества внешних ссылок', 'c': 'Упорядочивание результатов поиска в соответствии с запросом пользователя'}))
test_question_list.append(TestQuestion("Бизнес-процесс – это:", 'c', {'a': 'Это средство, предназначенное для просмотра подробных сведений о значимых событиях,\n которые возникают в системе', 'b': 'Перестройка деловых процессов для достижения улучшения деятельности компании', 'c': 'Совокупность взаимосвязанных мероприятий или задач,\n направленных на создание определённого продукта или услуги для потребителей'}))
test = Test("Тест МДК.03.01. Сопровождение и продвижение программного обеспечения отраслевой направленности",test_question_list) #  класс тест принимает на вход список из тестовыйх вопросов
TestInterface(test) # интерфейс принимает тест