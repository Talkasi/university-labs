#include <QMessageBox>
#include "errors.h"

void error_message(err_t error)
{
    QMessageBox messageBox;
    switch (error) {
    case SUCCESS:
        break;
    case UNDEFINED_COMMAND:
        messageBox.critical(0, "Произошла ошибка!", "В программе произошел вызов неверной команды."); /* Why is it even here? */
        break;
    default:
        messageBox.critical(0, "Произошла ошибка!", "Unexpected error."); /* Why is it even here? */
        break;
    }
}
