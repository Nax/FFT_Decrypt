#ifndef FFT_DECRYPT_DECRYPT_WIDGET_H
#define FFT_DECRYPT_DECRYPT_WIDGET_H

#include <QWidget>
#include <QPlainTextEdit>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>

class DecryptWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DecryptWidget(QWidget* parent = nullptr);
    ~DecryptWidget();

private slots:
    void open();
    void decrypt();

private:
    QLineEdit*          _iso_path;
    QCheckBox*          _force_decryption;
    QPushButton*        _decrypt_button;
    QPlainTextEdit*     _log;
};

#endif
