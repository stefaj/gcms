#ifndef CONFIG_EDITOR_H
#define CONFIG_EDITOR_H

#include <QDialog>

namespace Ui {
class Config_Editor;
}

class Config_Editor : public QDialog
{
    Q_OBJECT

public:
    explicit Config_Editor(QWidget *parent = 0);
    ~Config_Editor();

private slots:
    void on_button_save_clicked();

    void on_button_close_clicked();

private:
    Ui::Config_Editor *ui;
    void load_config(QString file_name);
};

#endif // CONFIG_EDITOR_H
