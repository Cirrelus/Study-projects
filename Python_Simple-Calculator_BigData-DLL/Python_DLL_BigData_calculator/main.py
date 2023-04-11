import ctypes # Для работы с типами из C
import os.path # Для получения текущего путя до файла
import sys
import tkinter  # Для создания формы интерфейса
import tkinter.messagebox  # Для работы с всплывающими окнами

# подключение необходимых DLL
lib = ctypes.cdll.msvcrt   # подключаем библиотеку msvcrt.dll
dll_name = "BigDataDLL.dll"
dll_abs_path = os.path.abspath(os.path.join(os.path.dirname(__file__), dll_name))
MyDLL = ctypes.cdll.LoadLibrary(dll_abs_path)

# Функция сложения, выводит ответ дважды - в поле ответа и поле для истории операций
def Plus():
    Plus_from_c = getattr(MyDLL,"Plus")
    arg1_bytes = arg1.get().encode("utf-8")
    arg2_bytes = arg2.get().encode("utf-8")
    result = ctypes.c_char_p(Plus_from_c(ctypes.c_char_p(arg1_bytes), ctypes.c_char_p(arg2_bytes))).value
    answer_text.delete(0, tkinter.END)
    answer_text.insert(0, result)
    all_answers_text.insert(1.0, arg1_bytes.decode("utf-8") + "+" + arg2_bytes.decode("utf-8") + "=" + result.decode("utf-8") + "\n")

# Функция вычитания, выводит ответ дважды - в поле ответа и поле для истории операций
def Minus():
    Minus_from_c = getattr(MyDLL,"Minus")
    arg1_bytes = arg1.get().encode("utf-8")
    arg2_bytes = arg2.get().encode("utf-8")
    result = ctypes.c_char_p(Minus_from_c(ctypes.c_char_p(arg1_bytes), ctypes.c_char_p(arg2_bytes))).value
    answer_text.delete(0, tkinter.END)
    answer_text.insert(0, result)
    all_answers_text.insert(1.0, arg1_bytes.decode("utf-8") + "-" + arg2_bytes.decode("utf-8") + "=" + result.decode("utf-8") + "\n")

# Функция умножения, выводит ответ дважды - в поле ответа и поле для истории операций
def Multiply():
    Multiply_from_c = getattr(MyDLL,"Multiply")
    arg1_bytes = arg1.get().encode("utf-8")
    arg2_bytes = arg2.get().encode("utf-8")
    result = ctypes.c_char_p(Multiply_from_c(ctypes.c_char_p(arg1_bytes), ctypes.c_char_p(arg2_bytes))).value
    answer_text.delete(0, tkinter.END)
    answer_text.insert(0, result)
    all_answers_text.insert(1.0, arg1_bytes.decode("utf-8") + "*" + arg2_bytes.decode("utf-8") + "=" + result.decode("utf-8") + "\n")

# Функция деления, выводит ответ дважды - в поле ответа и поле для истории операций
def Divide():
    try:
        Divide_from_c = getattr(MyDLL,"Divide")
        arg1_bytes = arg1.get().encode("utf-8")
        arg2_bytes = arg2.get().encode("utf-8")
        result = ctypes.c_char_p(Divide_from_c(ctypes.c_char_p(arg1_bytes), ctypes.c_char_p(arg2_bytes))).value
        answer_text.delete(0, tkinter.END)
        answer_text.insert(0, result)
        all_answers_text.insert(1.0, arg1_bytes.decode("utf-8") + "/" + arg2_bytes.decode("utf-8") + "=" + result.decode("utf-8") + "\n")
    except WindowsError:
        result = "NaN"
        answer_text.delete(0, tkinter.END)
        answer_text.insert(0, result)
        all_answers_text.insert(1.0, arg1_bytes.decode("utf-8") + "/" + arg2_bytes.decode("utf-8") + "=" + result + "\n")


# создание формы
window = tkinter.Tk()
window.title("Калькулятор для работы с большими числами из C")

# установление размера формы
window.geometry('1000x700')
window.columnconfigure(1, weight=1)

# добавление надписи Первый аргумент:
first_argument_label = tkinter.Label(window, text='Первый аргумент:', font=("Times New Roman", 14))
first_argument_label.grid(column=0, row=0)

# добавление поля для ввода первого аргумента
arg1 = tkinter.Entry(window, width=100)
arg1.grid(column=1, row=0)

# добавление двух кнопок - для сложения и вычитания
plus_button = tkinter.Button(window, text='+', font=("Times New Roman", 14), width=4, height=2, command=lambda: Plus())
plus_button.grid(column=2, row=0, padx=10, pady=10)
minus_button = tkinter.Button(window, text='-', font=("Times New Roman", 14), width=4, height=2, command=lambda: Minus())
minus_button.grid(column=3, row=0, padx=10, pady=10, sticky=tkinter.E)

# добавление надписи Второй аргумент:
second_argument_label = tkinter.Label(window, text="Второй аргумент:", font=("Times New Roman", 14))
second_argument_label.grid(column=0, row=1)

# добавление поля для ввода второго аргумента
arg2 = tkinter.Entry(window, width=100)
arg2.grid(column=1, row=1)

# добавление двух кнопок - для умножения и деления
multiply_button = tkinter.Button(window, text='*', font=("Times New Roman", 14), width=4, height=2, command=lambda: Multiply())
multiply_button.grid(column=2, row=1, padx=10, pady=10)
divide_button = tkinter.Button(window, text='/', font=("Times New Roman", 14), width=4, height=2, command=lambda: Divide())
divide_button.grid(column=3, row=1, padx=10, pady=10, sticky=tkinter.E)

# Добавление надписи Ответ
answer_label = tkinter.Label(window, text="Ответ:", font=("Times New Roman", 14))
answer_label.grid(column=0, row=2)

# Добавление поля для ответа
answer_text = tkinter.Entry(window, width=100)
answer_text.grid(column=1, row=2)

# Добавление надписи История операций
answer_label = tkinter.Label(window, text="История операций:", font=("Times New Roman", 14))
answer_label.grid(column=0, row=3)

# Добавление поля для истории операций
all_answers_text = tkinter.Text(window, wrap=tkinter.NONE, width=100)
all_answers_text.grid(column=1, row=3, pady=10)

# Добавление вертикальной полосы прокрутки
scrollbar = tkinter.Scrollbar(window, orient='vertical', command=all_answers_text.yview)
scrollbar.grid(column=2, row=3, sticky=tkinter.N+tkinter.S+tkinter.W)

# Добавление горизонтальной полосы прокрутки
scrollbar2 = tkinter.Scrollbar(window, orient='horizontal', command=all_answers_text.xview)
scrollbar2.grid(column=1, row=4, sticky=tkinter.N+tkinter.E+tkinter.W)

window.resizable(width=False, height=False)

# запуск формы
window.mainloop()
