#include <decrypt_window.h>
#include <decrypt_widget.h>

DecryptWindow::DecryptWindow(QWidget* parent)
: QMainWindow(parent)
{
    DecryptWidget* widget;

    setWindowTitle("FFT Decrypt");
    widget = new DecryptWidget;
    setFixedSize(500, 500);
    setCentralWidget(widget);
}

DecryptWindow::~DecryptWindow()
{

}
