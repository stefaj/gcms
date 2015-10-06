#ifndef DIRECTORY_WIZARD_H
#define DIRECTORY_WIZARD_H

#include <QWidget>

namespace Ui {
class Directory_Wizard;
}

class Directory_Wizard : public QWidget
{
    Q_OBJECT

public:
    explicit Directory_Wizard(QWidget *parent = 0);
    ~Directory_Wizard();


private slots:
    void on_buttonCancel_clicked();
    void on_buttonNext_clicked();

    void on_button_add_clicked();

    void on_button_remove_clicked();

    void on_button_add_2_clicked();

    void on_button_remove_2_clicked();
    void load_directories(QString filename);
    void load_nodes(QString filename);
    void add_directory_list();
    void add_this_directory_to_other();
    void on_button_back_clicked();

private:
    Ui::Directory_Wizard *ui;
    QVector<QString> directories, directorylist, display;
};

#endif // DIRECTORY_WIZARD_H
