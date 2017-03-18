#include <QString>

#include "utility.h"

/*!
 * \brief getInstrumentName
 * �Ӻ�Լ��������ȡ����Ʒ����(����ȥ�������·�)
 * ���� cu1703 --> cu, i1705 --> i, CF705 --> CF
 *
 * \param instrumentID ��Լ����
 * \return ����Ʒ����
 */
QString getInstrumentName(const QString &instrumentID) {
    const int len = instrumentID.length();
    int i = 0;
    for (; i < len; i++) {
        if (instrumentID[i].isDigit()) {
            break;
        }
    }
    return instrumentID.left(i);
}
