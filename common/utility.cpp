#include "utility.h"

#include <QMap>

/*!
 * \brief getInstrumentName
 * ���ڻ�����Ȩ��Լ��������ȡ���״���
 * ���� cu1703 --> cu, i1705 --> i, CF705 --> CF
 *      m1707-C-2700 --> m
 *
 * \param instrumentID �ڻ�/��Ȩ��Լ����
 * \return ����Ʒ����
 */
QString getCode(const QString &instrumentID)
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
 * \brief parseOptionID
 * ������Ȩ��Լ����, ��ȡ���Ӧ����ڻ���Լ�Ĵ���, ��Ȩ����(����/����) �Լ�ִ�м۸�
 * ���� m1707-C-2700 --> ���m1707, ����Ϊ����, ִ�м۸�2700
 *     SR705P6400   --> ���SR705, ����Ϊ����, ִ�м۸�6400
 *
 * \param optionID ��Ȩ��Լ����
 * \param futureID ����ڻ���Լ���� (�������)
 * \param type ����/���� (�������)
 * \param exercisePrice ִ�м۸� (�������)
 * \return �����ɹ����
 */
bool parseOptionID(const QString &optionID, QString &futureID, OPTION_TYPE &type, int &exercisePrice)
{
    const int len = optionID.length();
    int i = 0;
    for (; i < len; i++) {
        if (optionID[i].isDigit()) {
            break;
        }
    }
    for (; i < len; i++) {
        if (!optionID[i].isDigit()) {
            break;
        }
    }
    futureID = optionID.left(i);
    for (; i < len; i++) {
        if (optionID[i].isLetter()) {
            break;
        }
    }
    type = (optionID[i] == "C" ? CALL_OPT : PUT_OPT);
    for (; i < len; i++) {
        if (optionID[i].isDigit()) {
            break;
        }
    }
    exercisePrice = optionID.right(len - i).toInt();
    return true;    // TODO successfull or not
}

/*!
 * \brief makeOptionID
 * ������Ȩ��Լ�й涨�ĸ�ʽ�ϳ���Ȩ��Լ����
 *
 * \param futureID ����ڻ���Լ����
 * \param type ����/����
 * \param exercisePrice ִ�м۸�
 * \return ��Ȩ��Լ����
 */
QString makeOptionID(const QString &futureID, const OPTION_TYPE type, const int exercisePrice)
{
    static const auto optionIdPatternMap = []() -> QMap<QString, QString> {
        QMap<QString, QString> map;
        map.insert("m", "%1-%2-%3");
        map.insert("SR", "%1%2%3");
        return map;
    }();

    QString middle = (type == CALL_OPT) ? "C" : "P";
    return optionIdPatternMap[getCode(futureID)].arg(futureID).arg(middle).arg(exercisePrice);
}

/*!
 * \brief isOption
 * �ж�һ����Լ�����Ƿ�����Ȩ��Լ
 *
 * \param instrumentID ��Լ����
 * \return �Ƿ�����Ȩ��Լ
 */
bool isOption(const QString &instrumentID)
{
    return instrumentID.length() >= 8;  // FIXME
}


#define String const QString&

// ͨ����Լ������ļ�����չ��
QString getSuffix(String instrumentID) {
    const QString instrumentLowerCase = getCode(instrumentID).toLower();
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
