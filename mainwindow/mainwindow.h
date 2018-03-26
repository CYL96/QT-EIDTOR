#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>//菜单
#include <QToolBar>//任务栏
#include <QAction>//动作
#include <QTextEdit>

#include <QColorDialog>
#include <QFontDialog>

#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    QMenu *fm,*fm2;
    QToolBar *tl,*tl2;
    QAction *na,*oa,*sa,*saa,*ca;
    QAction *ct,*pst,*cp,*ft,*cl,*ud,*rd,*sall,*clr;
    QTextEdit *te;
    QColor color;
    QFont font;

    QString filename,otherfile;
    int c_flag=0,l_flag=0;
    void show_message();


private slots:
    void show_color();
    void show_font();

    void show_file();
    void show_save();
    void show_saveas();
    void show_new();
    void text_changed();
};

#endif // MAINWINDOW_H
