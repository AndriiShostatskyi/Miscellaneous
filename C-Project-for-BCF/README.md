# C++-Project-for-BCF

This is a small C++ project that consists of three tasks (matrix, file movement, planner) mentioned below. 

For all those tasks, I used Ubuntu 16.04 and Qt 5 given it’s “Write once, compile anywhere” concept and easiness to implement GUI compared, for example, to WinAPI.

## Task 1

Write a program which performs addition, subtraction, multiplication of matrices.

The dimensions of both the matrices would be specified by the user (dynamic memory allocation required).

Use of structure or a class to define the matrix would be a good idea.

### Comments on my code (see Matrix folder)

Use Mode/View design:

a)  Model

Implemented Matrix class that inherits from QAbstractTableModel and contains addition, subtraction, and multiplication methods. 

I use QScopedArrayPointer < QScopedArrayPointer< double > > as data structure for matrix and to meet dynamic memory allocation requirement.

b) View 

Set Matrix class as model for QTableView widget in main window.  

## Task 2

Write a program which will perform the job of moving the file from one location to another.

The source and destination path will be entered by the user.

Perform the required error checking and handle the exceptions accordingly.

### Comments on my code (see Filemove folder)

No separate class is implemented, as I just needed a few functions, so I put them in MainWindow class. 

In order to move a given file, first, the program tries to move the file and, if fails, it tries to copy and remove that file. For that, I use rename method of QDir, copy and remove methods of QFile. 

All move file work is wrapped in try and catch. 

Inputs of the user in QLineEdit are checked (i.e. whether a given file exists).  

## Task 3

Write a program which would act as a personal planner.

In which a user can input an event, note of thing to-do on certain date.

Use prefered database engine.

### Comments on my code (see Planner folder)

Use Model/View design: 

a)  Model

Implemented Scheduler class that inherits from QSqlTableModel and contains main methods for planning.  

As preferred database engine, I use SQLite because it isn’t a client–server database engine, it’s quite simple, and for this program no sophisticated functionality is needed. 

DB table contains, inter alia, plan description, date and time, info whether it’s completed, priority and importance of the plan.  

Separate Database class is implemented to handle DB connections and table creation. However, all insert, update, and delete work is on QSqlTableModel.

b) View 

Set Scheduler as a model for QTableView widget in the main window. In QTableView, I used QLineEdit, QComboBox, and QDateTime. 

Moreover, I implemented separate delegate classes for QComboBox and QDateTime.



