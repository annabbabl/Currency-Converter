#ifndef PLOT_H_

#include <iostream>
#include <QPainterPath>
#include <QWidget>
#include <vector>
#include <QPainter>
#include <set>
#include <unordered_map>
#include "date.h"

// this class should draw graphic in a widget
class PlotWidget : public QWidget {
public:
  explicit PlotWidget(QWidget *parent = nullptr);
  ~PlotWidget();
  void processData(const std::vector<std::pair<Date,float>>& passed_data);
  void reset();

private:
  int m_lev_distance_y;
  int m_lev_y;
  int m_lev_x;

  std::vector<std::pair<Date,int>> data;

  const int accurate = 1000;
  const int level_difference = 0.05 * accurate;

  // this might be a bit confusing
  const int y_labels_offset = 30; // this is the offset for the labels that go along the Y axis. So it moves graph along X axis right
  const int x_labels_offset = 30; // this is the offset for the labels that go along the X axis. So it moves graph along Y axis up

  /*
    Graph example

    ^ Y, rate
    |
    |
    |
     --------> X, dates 
  
  */
  
  const int graph_offset_x = 0; // left margin relatively to the background(that means that labels offsets are included too)
  const int graph_dot_distance = 90; // distance between the dots
  const int graph_dot_radius = 3; // radius of the dot


  std::unordered_map<int,int> m_lines_y_pos; // <value, position>
  
  std::unordered_map<int,int> m_points_y_pos; // <value, position>


  int find_level_exceed(const int& x);
  

  int find_element(const int& element, const std::vector<int>& arr); // returns the index of the found element or the -1 if not found

  void paintEvent(QPaintEvent* ev);
  std::vector<int> m_levels;
};

#endif