#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <QMessageBox>

class MessageBox {
public:
    static void show(const QString& title, const QString& message);
};

#endif // MESSAGEBOX_H
