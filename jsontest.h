#ifndef JSONTEST_H
#define JSONTEST_H

#include <QMainWindow>

namespace Ui {
class jsontest;
}

class jsontest : public QMainWindow
{
    Q_OBJECT

public:
    explicit jsontest(QWidget *parent = 0);
    ~jsontest();

private:
    Ui::jsontest *ui;
};

#endif // JSONTEST_H
