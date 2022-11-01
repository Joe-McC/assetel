#ifndef UTILITIES_H
#define UTILITIES_H

#include <QObject>
#include <QMessageBox>
#include <QApplication>

namespace Misc
{
/**
 * @brief The Utilities class
 *
 * The @c Utilitities module provides commonly used functionality to the rest of the
 * application. For example, showing a messagebox with a nice format or revealing files in
 * the operating system's preffered file manager.
 */
class Utilities : public QObject
{
    Q_OBJECT

public:
    // clang-format off
    static Utilities &getInstance();
    static int showMessageBox(const QString &text,
                              const QString &informativeText,
                              const QString &windowTitle = qAppName(),
                              QMessageBox::StandardButtons bt = QMessageBox::Ok);
    //clang-format on

public slots:
    static void aboutQt();
    static void openLogFile();
    static void configureDarkUi();
    static void revealFile(const QString& pathToReveal);
};
}

#endif // UTILITIES_H
