#include "./config_editor.h"
#include "./ui_config_editor.h"
#include "./Functions/premises_exporter.h"
#include <QFile>
#include <QTextStream>

Config_Editor::Config_Editor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Config_Editor) {
    ui->setupUi(this);
    load_config("config.config");
}

Config_Editor::~Config_Editor() {
    delete ui;
}

void Config_Editor::on_button_save_clicked() {
  PremisesExporter::export_config(ui->textBrowser->toPlainText(), "config.config");
  emit accepted();
  this->close();
}

void Config_Editor::on_button_close_clicked() {
    this->close();
}

void Config_Editor::load_config(QString file_name) {
  if ( PremisesExporter::fileExists("VirtualConcierge/" + file_name) ) {
    ui->textBrowser->setText("");
    // load the text file
    QFile textfile("VirtualConcierge/" + file_name);
    // open the text file
    textfile.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream ascread(&textfile);

    if ( textfile.isOpen() ) {
      // read each line of the file
      QString line = ascread.readLine();
      while ( !line.isNull() ) {
      ui->textBrowser->setText(ui->textBrowser->toPlainText() + line + "\n");

      // read next line
      line = ascread.readLine();
      }

        // close the textfile
        textfile.close();
    }
  }
}
