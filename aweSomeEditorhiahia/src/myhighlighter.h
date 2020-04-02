#ifndef MYHIGHLIGHTER_H
#define MYHIGHLIGHTER_H
#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QTextDocument>
class MyHighLighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    MyHighLighter(QTextDocument *parent = 0);

protected:
    void highlightBlock(const QString &text) Q_DECL_OVERRIDE;

private:
    struct HighlightingRule
    {
        QRegExp pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;

    QRegExp commentStartExpression;//多行注释用开始标识符
    QRegExp commentEndExpression;//多行注释用结束标识符

    QTextCharFormat keywordFormat;//关键字
    QTextCharFormat classFormat;//类
    QTextCharFormat singleLineKey;//单行关键字
    QTextCharFormat singleLineValue;//单行值
    QTextCharFormat singleLineCommentFormat;//单行注释
    QTextCharFormat multiLineCommentFormat;//多行注释
    QTextCharFormat quotationFormat;//变量标识符
    QTextCharFormat functionFormat;//方法标识符
};
#endif // MYHIGHLIGHTER_H
