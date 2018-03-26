#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
#if 0
    fm=menuBar()->addMenu("文件");
    fm->addAction(QIcon("1.png"),"1");
    fm->addAction(QIcon("2.png"),"2");

    tl=addToolBar("file");
    tl->addAction(QIcon("1.png"),"3");
    tl->addAction(QIcon("2.png"),"4");
#else
    na =new QAction(QIcon("new.png"),"新的文件");//设置动作
    na->setShortcut(QKeySequence::New);//设置快捷方式
    na->setStatusTip("新的文件...");//设置在状态栏显示的字符串
    oa = new QAction(QIcon("open.png"),"打开文件");
    oa->setShortcut(QKeySequence::Open);
    oa->setStatusTip("打开文件...");
    sa=new QAction(QIcon("save.png"),"保存");
    sa->setShortcut(QKeySequence::Save);
    sa->setStatusTip("保存...");
    saa=new QAction(QIcon("saveas.png"),"另存为");
    saa->setShortcut(QKeySequence::SaveAs);
    saa->setStatusTip("另存为...");
    ca=new QAction(QIcon("close"),"关闭");
    ca->setShortcut(QKeySequence::Close);
    ca->setStatusTip("关闭...");

    ct=new QAction(QIcon("cut.png"),"剪切");
    ct->setShortcut(QKeySequence::Cut);
    ct->setStatusTip("剪切...");
    pst=new QAction(QIcon("paste.png"),"粘贴");
    pst->setShortcut(QKeySequence::Paste);
    pst->setStatusTip("粘贴...");
    cp=new QAction(QIcon("copy.png"),"复制");
    cp->setShortcut(QKeySequence::Copy);
    cp->setStatusTip("复制...");
    cl=new QAction(QIcon("color.png"),"颜色");
    cl->setStatusTip("颜色...");
    ft=new QAction(QIcon("paste.png"),"字体");
    ft->setStatusTip("字体...");
    ud=new QAction(QIcon("undo.png"),"撤销");
    ud->setShortcut(QKeySequence::Undo);
    ud->setStatusTip("撤销...");
    rd=new QAction(QIcon("redo.png"),"重做");
    rd->setShortcut(QKeySequence::Redo);
    rd->setStatusTip("重做...");
    sall=new QAction(QIcon("ALL.png"),"全选");
    sall->setShortcut(QKeySequence::SelectAll);
    sall->setStatusTip("全选...");
    clr=new QAction(QIcon("clear.png"),"清空");
    clr->setStatusTip("清空");

    fm=menuBar()->addMenu("文件");//菜单栏设置
    fm->addAction(na);
    fm->addAction(oa);
    fm->addAction(sa);
    fm->addAction(saa);
    fm->addAction(ca);

    fm2=menuBar()->addMenu("编辑");
    fm2->addAction(ud);
    fm2->addAction(rd);
    fm2->addAction(sall);
    fm2->addAction(ft);
    fm2->addAction(cl);
    fm2->addAction(cp);
    fm2->addAction(ct);
    fm2->addAction(pst);
    fm2->addAction(clr);

    tl=addToolBar("文件");//快捷栏设置
    tl->addAction(na);
    tl->addAction(oa);
    tl->addAction(sa);
    tl->addAction(saa);
    tl->addAction(ca);
    tl2=addToolBar("编辑");
    tl2->addAction(ud);
    tl2->addAction(rd);
    tl2->addAction(sall);
    tl2->addAction(ft);
    tl2->addAction(cl);
    tl2->addAction(cp);
    tl2->addAction(ct);
    tl2->addAction(pst);
    tl2->addAction(clr);
#endif
    setWindowTitle("文本编辑器");
    te= new QTextEdit;
    setCentralWidget(te);
    statusBar();

    connect(ct,SIGNAL(triggered(bool)),te,SLOT(cut()));
    connect(cp,SIGNAL(triggered(bool)),te,SLOT(copy()));
    connect(pst,SIGNAL(triggered(bool)),te,SLOT(paste()));
    connect(ud,SIGNAL(triggered(bool)),te,SLOT(undo()));
    connect(rd,SIGNAL(triggered(bool)),te,SLOT(redo()));
    connect(sall,SIGNAL(triggered(bool)),te,SLOT(selectAll()));
    connect(ca,SIGNAL(triggered(bool)),this,SLOT(close()));

    connect(cl,SIGNAL(triggered(bool)),this,SLOT(show_color()));
    connect(ft,SIGNAL(triggered(bool)),this,SLOT(show_font()));

    connect(oa,SIGNAL(triggered(bool)),this,SLOT(show_file()));
    connect(sa,SIGNAL(triggered(bool)),this,SLOT(show_save()));
    connect(saa,SIGNAL(triggered(bool)),this,SLOT(show_saveas()));

    connect(na,SIGNAL(triggered(bool)),this,SLOT(show_new()));

    connect(te,SIGNAL(textChanged()),this,SLOT(text_changed()));
    connect(clr,SIGNAL(triggered(bool)),te,SLOT(clear()));
}

MainWindow::~MainWindow()
{

}

void MainWindow::show_message()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("警告：");
    msgBox.setText("文件已被修改");
    msgBox.setInformativeText("需要保存文件吗");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    int ret = msgBox.exec();
    switch (ret) {
      case QMessageBox::Save:
        show_save();
        break;
      case QMessageBox::Discard:
        c_flag=0;
        break;
      case QMessageBox::Cancel:

        break;
      default:
        break;
    }
}

void MainWindow::show_color()
{
    color=QColorDialog::getColor();
    te->setTextColor(color);
}

void MainWindow::show_font()
{
    bool ok;
    font= QFontDialog::getFont(&ok,QFont(),this);
    if(ok)
        te->setFont(font);
}

void MainWindow::show_file()
{
    if(c_flag==1)
    {
        show_message();
    }
    if(c_flag==0)
    {
        QString fn;
        fn=QFileDialog::getOpenFileName(this,tr("打开文件"),".");
        if(fn.isEmpty())
            return;
        filename=fn;
        QFile file(filename);
        setWindowTitle(filename);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::critical(this,"错误：","打开失败！");
            return;
        }
        te->setText("");
        while(!file.atEnd())
        {
            QByteArray arr=file.readAll();
            te->append(arr);
        }
        c_flag=0;
        file.close();
    }
}

void MainWindow::show_save()
{
    if(filename.isEmpty())
    {
        show_saveas();
    }
    else
    {
        QFile file(filename);
        if(!file.open(QIODevice::WriteOnly| QIODevice::Text))
        {
            QMessageBox::critical(this,"错误：","不能打开文件！");
            return;
        }
        QTextStream myfile(&file);
        myfile<<te->toPlainText();
        file.close();
        c_flag=0;
        QMessageBox::information(this,"信息：","保存成功");
    }
}

void MainWindow::show_saveas()
{
    filename=QFileDialog::getSaveFileName(this,"另存为",".");
    if(filename.isEmpty())
    {
        QMessageBox::warning(this,"错误：","保存失败！");
        return;
    }
    show_save();
    setWindowTitle(filename);

//}sssssssssssss

void MainWindow::show_new()
{
    if(c_flag==1)
    {
        show_message();
        if(!filename.isEmpty())
        {
            filename.clear();
            te->setText("");
            c_flag=0;
        }
    }
    if(c_flag==0)
    {
        setWindowTitle("文本编辑器");
        te->setText("");
        filename.clear();
        c_flag=0;
    }
}

void MainWindow::text_changed()
{
    if(filename.isEmpty())
    {
        c_flag=0;
        if(te->toPlainText()!="")
            c_flag=1;
    }
    else
    {
        c_flag=1;
    }
}

