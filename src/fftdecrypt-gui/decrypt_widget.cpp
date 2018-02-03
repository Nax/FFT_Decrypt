#include <QLabel>
#include <QVboxLayout>
#include <QHboxLayout>
#include <QPixmap>
#include <QFileDialog>
#include <fft/decrypt.h>
#include <decrypt_widget.h>

DecryptWidget::DecryptWidget(QWidget* parent)
    : QWidget(parent)
{
    QVBoxLayout* vbox;
    vbox = new QVBoxLayout;
    vbox->setAlignment(Qt::AlignCenter);
    setLayout(vbox);

    QLabel* image;
    image = new QLabel;
    image->setAlignment(Qt::AlignCenter);
    image->setPixmap(QPixmap(":/images/escutcheon2.png"));
    vbox->addWidget(image);

    QLabel* title;
    title = new QLabel("FFT Decrypt");
    title->setFont(QFont("Helvetica", 32, QFont::Bold));
    title->setAlignment(Qt::AlignCenter);
    vbox->addWidget(title);

    QLabel* subtitle;
    subtitle = new QLabel("Version " FFT_DECRYPT_VERSION);
    subtitle->setFont(QFont("Helvetica", 16));
    subtitle->setAlignment(Qt::AlignCenter);
    vbox->addWidget(subtitle);

    QHBoxLayout* iso_open_hbox;
    iso_open_hbox = new QHBoxLayout;

    QLabel* iso_label;
    iso_label = new QLabel("ISO: ");
    iso_open_hbox->addWidget(iso_label);
    _iso_path = new QLineEdit;
    _iso_path->setReadOnly(true);
    iso_open_hbox->addWidget(_iso_path);
    vbox->addLayout(iso_open_hbox);

    QPushButton* open_button;
    open_button = new QPushButton("Open ISO...");
    open_button->setFixedWidth(150);
    vbox->addWidget(open_button);
    vbox->setAlignment(open_button, Qt::AlignCenter);
    connect(open_button, SIGNAL(released()), this, SLOT(open()));

    _force_decryption = new QCheckBox("Force decryption");
    vbox->addWidget(_force_decryption);
    vbox->setAlignment(_force_decryption, Qt::AlignCenter);

    _decrypt_button = new QPushButton("Decrypt");
    _decrypt_button->setFixedWidth(150);
    _decrypt_button->setEnabled(false);
    vbox->addWidget(_decrypt_button);
    vbox->setAlignment(_decrypt_button, Qt::AlignCenter);
    connect(_decrypt_button, SIGNAL(released()), this, SLOT(decrypt()));

    _log = new QPlainTextEdit;
    _log->setReadOnly(true);
    _log->setFont(QFont("Courier"));
    vbox->addWidget(_log);
}

DecryptWidget::~DecryptWidget()
{

}

void DecryptWidget::open()
{
    QString filename;

    filename = QFileDialog::getOpenFileName(this, "Open ISO", "", "ISO (*.iso)");

    if (filename == "")
        return;

    _iso_path->setText(filename);
    _decrypt_button->setEnabled(true);
}

void DecryptWidget::decrypt()
{
    QString filename;
    QByteArray filename_bytes;
    FFTD_Decryptor* decryptor;

    filename = _iso_path->text();

    if (filename == "")
        return;

    filename_bytes = filename.toUtf8();
    decryptor = FFTD_Open(filename_bytes.constData());

    if (!decryptor)
    {
        _log->appendPlainText("Failed to open the ISO.\n");
        return;
    }

    if (!FFTD_IsTactics(decryptor))
    {
        _log->appendPlainText("The provided ISO file does not seems to be FFT:WotL.\nAbort.\n");
        goto end;
    }

    if (FFTD_IsDecrypted(decryptor))
    {
        if (!_force_decryption->isChecked())
        {
            _log->appendPlainText("The provided ISO is already decrypted. Nothing to do.\n");
            _log->appendPlainText("You can force the decryption by checking the checkbox.\n");
            goto end;
        }
        else
        {
            _log->appendPlainText("The provided ISO is already decrypted. Forcing re-decryption.\n");
        }
    }

    _log->appendPlainText("Decrypting...\n");
    FFTD_Decrypt(decryptor);
    _log->appendPlainText("Done!\n");

end:
    FFTD_Close(decryptor);
}
