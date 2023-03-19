// progressbar.h

#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <QWidget>
#include <QProgressBar>
#include <QPushButton>
#include <QVBoxLayout>

class ProgressBar : public QWidget {
    Q_OBJECT

    public:
        explicit ProgressBar(QWidget *parent = nullptr, int max = 100);
        int getMax();

    signals:
        void cancelled();

    public slots:
        void updateProgress(int value);
        void cancel();

    private:
        QProgressBar *m_progressBar;
        QPushButton *m_cancelButton;
        int m_max;
};

#endif // PROGRESSBAR_H
