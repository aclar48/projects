/**
  @file graphtemplate.cpp
  @author Alex Clarke
  @version 1.0

  @section DESCRIPTION

  A class representing a graph template
  */

#include "graphtemplate.h"
/**
 * @brief GraphTemplate::GraphTemplate Default Constructor
 */
GraphTemplate::GraphTemplate()
{
    _bgColour = QColor(255,255,255,255);
    _bgAxisColour = QColor(255,255,255,255);
    _bgLegendColour = QColor(255,255,255,255);
    _graphColour = QColor(255,255,255,255);
    _legendPos = Qt::AlignRight|Qt::AlignTop;

}
/**
 * @brief GraphTemplate::GraphTemplate Construct from a list of preferences
 * @param prefs list of preferences
 */
GraphTemplate::GraphTemplate(const QVector<QString> &prefs)
{
    parseInPrefs(prefs);
}
/**
 * @brief GraphTemplate::bgImage get background image
 * @return
 */
QString GraphTemplate::bgImage() const
{
    return _bgImage;
}
/**
 * @brief GraphTemplate::setBgImage set background image
 * @param bgImage
 */
void GraphTemplate::setBgImage(const QString &bgImage)
{
    _bgImage = bgImage;
}
/**
 * @brief GraphTemplate::bgAxisImg get the axis background image
 * @return
 */
QString GraphTemplate::bgAxisImg() const
{
    return _bgAxisImg;
}
/**
 * @brief GraphTemplate::setBgAxisImg set the axis background image
 * @param bgAxisImg
 */
void GraphTemplate::setBgAxisImg(const QString &bgAxisImg)
{
    _bgAxisImg = bgAxisImg;
}
/**
 * @brief GraphTemplate::bgColour get the background colour
 * @return
 */
QColor GraphTemplate::bgColour() const
{
    return _bgColour;
}
/**
 * @brief GraphTemplate::setBgColour set the background colour
 * @param bgColour
 */
void GraphTemplate::setBgColour(const QColor &bgColour)
{
    _bgColour = bgColour;
}
/**
 * @brief GraphTemplate::bgAxisColour set axis background colour
 * @return
 */
QColor GraphTemplate::bgAxisColour() const
{
    return _bgAxisColour;
}
/**
* @brief GraphTemplate::setBgAxisColour get axis background colour
* @param bgAxisColour
*/
void GraphTemplate::setBgAxisColour(const QColor &bgAxisColour)
{
    _bgAxisColour = bgAxisColour;
}
/**
 * @brief GraphTemplate::bgLegendColour get the legend background colour
 * @return
 */
QColor GraphTemplate::bgLegendColour() const
{
    return _bgLegendColour;
}
/**
 * @brief GraphTemplate::setBgLegendColour set the legend background colour
 * @param bgLegendColour
 */
void GraphTemplate::setBgLegendColour(const QColor &bgLegendColour)
{
    _bgLegendColour = bgLegendColour;
}
/**
 * @brief GraphTemplate::graphColour get the graph colour
 * @return
 */
QColor GraphTemplate::graphColour() const
{
    return _graphColour;
}
/**
 * @brief GraphTemplate::setGraphColour set the graph colour
 * @param graphColour
 */
void GraphTemplate::setGraphColour(const QColor &graphColour)
{
    _graphColour = graphColour;
}
/**
 * @brief GraphTemplate::legendPos get the position of the legend
 * @return
 */
int GraphTemplate::legendPos() const
{
    return _legendPos;
}
/**
 * @brief GraphTemplate::setLegendPos set the position of the legend
 * @param legendPos
 */
void GraphTemplate::setLegendPos(int legendPos)
{
    _legendPos = legendPos;
}
/**
 * @brief GraphTemplate::getStringPrefs output the preferences to a list of strings
 * @return the list of strings, nicely formatted
 */
QVector<QString> &GraphTemplate::getStringPrefs()
{
    QVector<QString> *results = new QVector<QString>;
    results->append(_bgImage);
    results->append(_bgAxisImg);
    results->append(parseOutColour(_bgColour));
    results->append(parseOutColour(_bgAxisColour));
    results->append(parseOutColour(_bgLegendColour));
    results->append(parseOutColour(_graphColour));
    results->append(QString::number(_legendPos));


    return *results;
}
/**
 * @brief GraphTemplate::parseInPrefs parse in preferences from a list of strings
 * @param prefs the list of strings
 */
void GraphTemplate::parseInPrefs(const QVector<QString> &prefs)
{
    if(prefs.size() == 7) {
        _bgImage = prefs[0];
        _bgAxisImg = prefs[1];
        _bgColour = parseColour(prefs[2]);
        _bgAxisColour = parseColour(prefs[3]);
        _bgLegendColour = parseColour(prefs[4]);
        _graphColour = parseColour(prefs[5]);
        _legendPos = prefs[6].toInt();


    }


}
/**
 * @brief GraphTemplate::parseOutColour convert from QColor to nicely formatted string
 * @param colour input colour
 * @return nicely formatted string
 */
QString &GraphTemplate::parseOutColour(const QColor &colour)
{
    QString *results = new QString();
    *results = QString::number(colour.red()) + "," + QString::number(colour.green()) + "," + QString::number(colour.blue()) + "," + QString::number(colour.alpha());
    return *results;
}

/**
 * @brief GraphTemplate::parseColour covert from nicely formatted string to QColor
 * @param colour the nicely formatted string
 * @return the generated QColor
 */

QColor &GraphTemplate::parseColour(const QString &colour)
{
    QStringList temp = colour.split(",");
    QColor *result = new QColor(temp[0].toInt(),temp[1].toInt(),temp[2].toInt(),temp[3].toInt());
   return *result;
}








