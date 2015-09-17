#制作高亮语法编辑器
> 开发平台:Qt5.4.1

-------------------
###搭建一个编辑器
>QPlainTextEdit

通过继承QPlainTextEdit添加更多的功能:

1.    添加高亮显示当前编辑行
2.    添加显示行号

####1.   添加高亮显示当前编辑行
当光标位置发生改变之后,会触发这个信号:
```c++
    cursorPositionChanged()
```

在处理这个信号槽时,我们可以这样做
```c++
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(Qt::yellow).lighter(160);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
```
主要工作就是通过设置这个结构体来对当前光标选择的行进行操作:
```
    struct ExtraSelection
    {
        QTextCursor cursor;
        QTextCharFormat format;
    };
```
进行上述操作之后,QPlainTextEdit上就可以高亮显示当前编辑行了.
####2.   添加显示行号
行号的显示其实是在QPlainTextEdit左面放置一个QWidget,然后在Qwidget上画出对应的行号.

*注意:*

因为行号的长度是变化的,所以显示行号的Qwidget的宽度也应该是变化的,因此要获取QPlainTextEdit的所有行数目.
主要方法是:
```
void CodeEditor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), Qt::lightGray);


    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::black);
            painter.drawText(-2, top, lineNumberArea->width(), fontMetrics().height(),
                             Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }
}
```

###添加语法高亮
>QSyntaxHighlighter

通过继承QSyntaxHighlighter类并实现
```
highlightBlock(const QString &text)
```
即可实现语法高亮,具体的语法需要自己通过这则表达式实现规则.
![这里写图片描述](http://img.blog.csdn.net/20150917111311626)
[github](http://example.com/ "optional title")
