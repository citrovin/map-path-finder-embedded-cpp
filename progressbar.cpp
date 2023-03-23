#include "qwidget.h"
#include "progressbar.h"

ProgressBar::ProgressBar(QWidget *parent, int max) : QWidget(parent) {
    // set max progress
    m_max = max;

    // Create the progress bar widget
    m_progressBar = new QProgressBar(this);

    // Set the maximum value of the progress bar to 100
    m_progressBar->setMaximum(100);

    // Create the cancel button widget
    m_cancelButton = new QPushButton(tr("Cancel"), this);

    // Create a vertical layout for the progress bar and cancel button
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_progressBar);
    layout->addWidget(m_cancelButton);

    // Set the layout of the window
    setLayout(layout);

    // Connect the cancel button to a slot that cancels the operation
    connect(m_cancelButton, &QPushButton::clicked, this, &ProgressBar::cancel);
}

// Slot for cancelling the operation
void ProgressBar::cancel() {
    emit cancelled();
}

// Slot for updating the progress bar value
void ProgressBar::updateProgress(int value) {
    m_progressBar->setValue((int)(value/m_max)/100);
}

int ProgressBar::getMax() {
    return m_max;
}
