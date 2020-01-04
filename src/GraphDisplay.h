#ifndef GRAPH_DISPLAY_H_
#define GRAPH_DISPLAY_H_

#include <vector>

#include <QWidget>
#include <QSharedPointer>
#include <QPoint>

#include "GraphManager.h"
#include <vector>

class GraphDisplay: public QWidget
{
  Q_OBJECT

public:
  GraphDisplay(QWidget *parent=0, Qt::WindowFlags f=0);
  void update(const std::vector <ElementInfo> &info);
  void paintEvent(QPaintEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);

  void keyPressEvent(QKeyEvent* event);

  QSharedPointer<GraphManager> m_pGraph;

private slots:
  void addRequestPad(int row, int collumn);

signals:
  void signalAddPlugin();
  void signalClearGraph();

private:

  enum MoveAction
  {
    None = 0,
    MoveComponent,
    MakeConnect,
    Select
  };

  struct MoveInfo
  {
    MoveInfo(): m_action(None)
    {
    }

    MoveAction m_action;
    std::string m_elementName;
    std::string m_padName;
    QPoint m_position;
    QPoint m_startPosition;
  };

  struct ElementDisplayInfo
  {
    QRect m_rect;
    std::string m_name;
    bool m_isSelected;
  };

  void calculatePositions();
  ElementDisplayInfo calculateOnePosition(const ElementInfo &info, const ElementDisplayInfo *oldDispInfo = NULL);
  void showContextMenu(QMouseEvent *event);
  void showElementProperties(std::string name);
  void showPadProperties(std::string elementName, std::string padName);
  void renderPad(std::string elementName, std::string padName, bool capsAny);
  void removePlugin(std::string name);
  void removeSelected();
  void getNameByPosition(const QPoint &pos, std::string &elementName, std::string &padName);
  QPoint getPadPosition(std::string elementName, std::string padName);
  void disconnect(std::string elementName, std::string padName);
  void requestPad(std::string elementName);
  void connectPlugin(std::string elementName, std::string destElementName);
  void addPlugin();
  void clearGraph();

  ElementInfo* getElement(std::string elementName);
  PadInfo* getPad(std::string elementName, std::string padName);

  std::vector <ElementInfo> m_info;
  std::vector <ElementDisplayInfo> m_displayInfo;

  MoveInfo m_moveInfo;
};

#endif
