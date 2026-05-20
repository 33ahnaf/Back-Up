import sys
from PyQt5 import QtWidgets
from PyQt5.QtWidgets import QApplication, QMainWindow
from PyQt5.QtGui import QIcon

def window(): # Create the main function
    app = QApplication(sys.argv)
    win = QMainWindow() # Create a application

    win.setGeometry(450, 150, 500, 500) # set the size
    win.setWindowTitle("My first application") # set the title
    win.setWindowIcon(QIcon("drift.jpg")) # set the icon
    win.setToolTip("Hay!") # set tool-tip
    

    lbl_first_name = QtWidgets.QLabel(win) # Create a label
    lbl_first_name.setText("Enter first name:")
    lbl_first_name.move(150, 200)

    lbl_last_name = QtWidgets.QLabel(win) # Create another label
    lbl_last_name.setText("Enter last name:")
    lbl_last_name.move(150, 250)


    text_first_name = QtWidgets.QLineEdit(win) # Create a text box
    text_first_name.move(250, 200)

    text_last_name = QtWidgets.QLineEdit(win) # Create another text box
    text_last_name.move(250, 250)


    def clicked(self): # Create a function to print first and last name
        print("Button clicked!")
        print("Name: " + text_first_name.text()) # We can also use print(f"Name: {text_first_name.text()}")
        print("Surname: " + text_last_name.text()) # We can also use print(f"Surname: {text_last_name.text()}")

    btn_print = QtWidgets.QPushButton(win) # Create a button
    btn_print.setText("Print")
    btn_print.clicked.connect(clicked)
    btn_print.move(250, 300)


    win.show()
    sys.exit(app.exec_())

window() # call the main function