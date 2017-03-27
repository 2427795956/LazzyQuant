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

/*!
 * \brief makeOptionID
 *
 * \param futureID ����ڻ���Լ����
 * \param dir Call or Put
 * \param exercisePrice ��Ȩ��
 * \return ��Ȩ��Լ����
 */
QString makeOptionID(const QString &futureID, const OPTION_DIR dir, const int exercisePrice)
{
    QString middle = (dir == CALL_OPT) ? "-C-" : "-P-"; // FIXME SR705C6400
    QString optionID = futureID + middle + QString::number(exercisePrice);
    return optionID;
}


#define String const QString&

// ͨ����Լ������ļ�����չ��
QString getSuffix(String instrumentID) {
    const QString instrumentLowerCase = getInstrumentName(instrumentID).toLower();
    for (String instr : SQ) {
        if (instrumentLowerCase == instr) {
            return ".SQ";
        }
    }
    for (String instr : SY) {
        if (instrumentLowerCase == instr) {
            return ".SY";
        }
    }
    for (String instr : DL) {
        if (instrumentLowerCase == instr) {
            return ".DL";
        }
    }
    for (String instr : DY) {
        if (instrumentLowerCase == instr) {
            return ".DY";
        }
    }
    for (String instr : ZZ) {
        if (instrumentLowerCase == instr) {
            return ".ZZ";
        }
    }
    for (String instr : ZY) {
        if (instrumentLowerCase == instr) {
            return ".ZY";
        }
    }
    for (String instr : ZJ) {
        if (instrumentLowerCase == instr) {
            return ".ZJ";
        }
    }
    return ".notfound";
}
#undef String
