from cmath import nan
import sqlite3
class mydb: 
    def __init__(self): #создание базы
        self.con = sqlite3.connect('example.db')
    def close(self):    #закрытие базы
        self.con.close()
    def create_schema(self): #создание таблиц
        cur=self.con.cursor()
        try: 
            # создание юзера
            cur.execute('''CREATE TABLE users
                        (id integer primary key autoincrement,email text UNIQUE,fio text,pass text)''')
            # хранение тестов
            cur.execute('''CREATE TABLE testresult
                        (id integer primary key autoincrement,userid integer,result integer,FOREIGN KEY(userid) REFERENCES users(id) on delete cascade)''')
            self.con.commit()
        except sqlite3.OperationalError:
            pass
    def register(self,email,fio,password):  #регистрация
        if '' in (email,fio,password):
            return
        cur=self.con.cursor()
        try: 
            # регистрация юзера
            cur.execute('''INSERT INTO users(email,fio,pass) values
                        (?,?,?)''',(email,fio,password))
            self.con.commit()
        except sqlite3.OperationalError:  
            pass  
    def login(self,email,password): #авторизация
        if '' in (email,password):
            return None
        cur=self.con.cursor()
        try: 
            # авторизация юзера
            cur.execute('''SELECT id from users WHERE (email=? and pass=?)
                        ''',(email,password))
            resultid=cur.fetchall()
            if(len(resultid)<1):
                return None
            else:
                return resultid[0][0]
        except sqlite3.OperationalError:  
            pass  
    def saveresult(self,userid,result): #сохранение результата
        cur=self.con.cursor()
        try: 
            # вставка результата в таблицу
            cur.execute('''INSERT INTO testresult(userid,result) values
                        (?,?)''',(userid,result))
            self.con.commit()
        except sqlite3.OperationalError:  
            raise 