#include <QApplication>
#include <decrypt_window.h>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    DecryptWindow win;

    win.show();

    return app.exec();
}
