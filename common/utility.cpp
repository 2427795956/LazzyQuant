#include <QStringList>

#include "utility.h"

/*!
 * \brief getInstrumentName
 * ���ڻ�����Ȩ��Լ��������ȡ����Ʒ����
 * ���� cu1703 --> cu, i1705 --> i, CF705 --> CF
 *      m1707-C-2700 --> m
 *
 * \param instrumentID �ڻ�/��Ȩ��Լ����
 * \return ����Ʒ����
 */
QString getInstrumentName(const QString &instrumentID)
{
    const int len = instrumentID.length();
    int i = 0;
    for (; i < len; i++) {
        if (instrumentID[i].isDigit()) {
            break;
        }
    }
    return instrumentID.left(i);
}

/*!
 * \brief getFutureIDFromOptionID
 * ����Ȩ��Լ��������ȡ��Ӧ����ڻ���Լ����
 * ���� m1707-C-2700 --> m1707, SR705C6400 --> SR705
 *
 * \param instrumentID ��Ȩ��Լ����
 * \return ����ڻ���Լ����
 */
QString getFutureIDFromOptionID(const QString &instrumentID)
{
    const int len = instrumentID.length();
    int i = 0;
    for (; i < len; i++) {
        if (instrumentID[i].isDigit()) {
            break;
        }
    }
    for (; i < len; i++) {
        if (!instrumentID[i].isDigit()) {
            break;
        }
    }
    return instrumentID.left(i);
}
