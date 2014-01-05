#ifndef GRAPHTEMPLATE_H
#define GRAPHTEMPLATE_H
#include <QString>
#include <QColor>
#include <QVector>

class GraphTemplate
{
public:
    GraphTemplate();
    GraphTemplate(const QVector<QString> &prefs);

    QString bgImage() const;
    void setBgImage(const QString &bgImage);

    QString bgAxisImg() const;
    void setBgAxisImg(const QString &bgAxisImg);

    QColor bgColour() const;
    void setBgColour(const QColor &bgColour);

    QColor bgAxisColour() const;
    void setBgAxisColour(const QColor &bgAxisColour);

    QColor bgLegendColour() const;
    void setBgLegendColour(const QColor &bgLegendColour);

    QColor graphColour() const;
    void setGraphColour(const QColor &graphColour);

    QVector<QString> &getStringPrefs();

    int legendPos() const;
    void setLegendPos(int legendPos);

        void parseInPrefs(const QVector<QString> &prefs);

private:

    QColor &parseColour(const QString &colour);
    QString &parseOutColour(const QColor &colour);
    QString _bgImage;
    QString _bgAxisImg;
    QColor _bgColour;
    QColor _bgAxisColour;
    QColor _bgLegendColour;
    QColor _graphColour;
    int _legendPos;


};

#endif // GRAPHTEMPLATE_H
