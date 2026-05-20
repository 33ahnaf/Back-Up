import sys
from PyQt5 import QtWidgets
from PyQt5.QtWidgets import QApplication, QMainWindow
from PyQt5.QtGui import QIcon

class my_window(QMainWindow):
    def __init__(self): # Create the main class
        super(my_window, self).__init__()
        self.setGeometry(450, 150, 500, 500) # set the size
        self.setWindowTitle("My 2nd application") # set the title
        self.setToolTip("Welcome!") # set the tool-tip
        self.setWindowIcon(QIcon("drift.jpg")) # set the icon
        self.initUI() # init the bottom function

    def initUI(self):
        self.lbl_first_name = QtWidgets.QLabel(self)
        self.lbl_first_name.setText("Enter first name: ")
        self.lbl_first_name.move(150, 150) # Create a label
        
        self.lbl_last_name = QtWidgets.QLabel(self)
        self.lbl_last_name.setText("Enter last name: ")
        self.lbl_last_name.move(150, 200) # Create another label


        self.text_first_name = QtWidgets.QLineEdit(self)
        self.text_first_name.move(250, 150) # Create a text box

        self.text_last_name = QtWidgets.QLineEdit(self)
        self.text_last_name.move(250, 200) # Create another text box


        self.btn_print = QtWidgets.QPushButton(self)
        self.btn_print.setText("Print")
        self.btn_print.clicked.connect(self.clicked)
        self.btn_print.move(250, 250) # Create a button


        self.lbl_result = QtWidgets.QLabel(self)
        self.lbl_result.setText("RESULT: ")
        self.lbl_result.move(250, 270)
        self.lbl_result.resize(250, 300) # Create a label for result
    

    def clicked(self): # Create a function for printing result
        self.lbl_result.setText("First name: " + self.text_first_name.text() + "\nLast name: " + self.text_last_name.text())

def window(): # Create the main function
    app = QApplication(sys.argv)
    win = my_window()
    win.show()
    sys.exit(app.exec_())

window() # call the main function