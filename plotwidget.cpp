#include "plotwidget.h"

PlotWidget::PlotWidget(QWidget* parent) : QWidget{parent}
{
  this->setFixedSize(QSize(500,300));  
}

PlotWidget::~PlotWidget() {
}

void PlotWidget::processData(const std::vector<std::pair<Date,float>>& passed_data) {
  for(int i = 0; i < passed_data.size(); i++)
    data.push_back(std::pair<Date,int>(passed_data[i].first, int(passed_data[i].second * accurate)));

  int mx = 0;
  for(int i = 0; i < data.size();i++) // find the highest value
    if(mx < data[i].second)
      mx = data[i].second;
  
  int mn = data[0].second;
  for(int i = 0; i < data.size();i++) // find the lowest value
    if(mn > data[i].second)
      mn = data[i].second;
  
  mn -= find_level_exceed(mn); // mn now will have the closest value that is divisible by levels_difference and that less than mn

  for(int i = mn; i <= mx+level_difference;i+=level_difference)
    m_levels.push_back(i);
  
  m_lev_y = m_levels.size();

  int division_value_height = (this->size().height() - x_labels_offset) / m_lev_y;
  m_lev_distance_y = division_value_height;
  
  std::sort(m_levels.begin(),m_levels.end());

  // using lambda function as functor to sort data
  std::sort(data.begin(),data.end(), [](const std::pair<Date,int>& first, const std::pair<Date,int>& second) {
    return (first.first < second.first);
  });

  repaint();
}

void PlotWidget::reset() {
  m_levels.clear();
  data.clear();
  m_lines_y_pos.clear();
  m_points_y_pos.clear();
  m_lev_y = 0;
  m_lev_x = 0;
  m_lev_distance_y = 0;
  repaint();
}

int PlotWidget::find_level_exceed(const int& x) {
  // if the value is not belong to the levels line then it should be somewhere
  // in between two lines so this block of code is calculating the points y
  // including its offset
  int level_exceed = x;
  while (level_exceed >= level_difference) level_exceed -= level_difference;

  return level_exceed;
}

int PlotWidget::find_element(const int& element, const std::vector<int>& arr) {
  for (int i = 0; i < arr.size(); i++)
    if (arr[i] == element) return i;

  return -1;
}

void PlotWidget::paintEvent(QPaintEvent* ev) {
  Q_UNUSED(ev);

  if(m_levels.empty()) // nothing to draw
    return;

  const int width = this->size().width() - y_labels_offset;
  const int height = this->size().height() - x_labels_offset;

  QPainter painter(this);
  painter.setPen(QPen(Qt::black,1,Qt::NoPen, Qt::FlatCap));
  painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));

  painter.drawRect(y_labels_offset, -x_labels_offset, width, height); // draw background

  painter.setPen(QPen(Qt::black,1,Qt::SolidLine, Qt::FlatCap));

  painter.setPen(QPen(QColor(58, 61, 59,90),1,Qt::SolidLine, Qt::FlatCap));
  for(int i = 0; i < m_lev_y; i++) {// draw lines and labels that are located by Y axis
    if(m_lines_y_pos.find(m_levels[i]) == m_lines_y_pos.end())
      m_lines_y_pos[m_levels[i]] = height - (i*m_lev_distance_y);

    painter.drawText(0,m_lines_y_pos[m_levels[i]] - x_labels_offset, QString::number(float(m_levels[i]) / float(accurate)));
    painter.drawLine(y_labels_offset,m_lines_y_pos[m_levels[i]] - x_labels_offset, width + y_labels_offset,m_lines_y_pos[m_levels[i]] - x_labels_offset); // draw background
  }

  // then rotate the painter and draw labels by X axis
  int offset = graph_offset_x + y_labels_offset;
  painter.translate(offset,height + 8);
  for(int i = 0; i < data.size(); i++) {
    QString label = QString::fromStdString(data[i].first.get_month()) + '-' +QString::fromStdString(data[i].first.get_day());
    
    painter.rotate(-90);
    painter.drawText(0, 0, label);
    painter.rotate(90);
    painter.translate(graph_dot_distance,0);
    offset += graph_dot_distance;

  }
  painter.translate(-offset,-height - 8);

  painter.setPen(QPen(Qt::black,1,Qt::NoPen, Qt::FlatCap));
  painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));

  for(int i = 0; i < data.size(); i++) {  // drawing graph
    
    int level_exceed = find_level_exceed(data[i].second);

    int y = (m_lines_y_pos[data[i].second - level_exceed] -(level_exceed*m_lev_distance_y/level_difference)); // some maths
    int x = i*graph_dot_distance;

    // add the value's y to the our database prototype so we could just get it in future
    if(m_points_y_pos.find(data[i].second) == m_points_y_pos.end()) // non found
      m_points_y_pos[data[i].second] = y;

    painter.drawEllipse(x - graph_dot_radius + graph_offset_x + y_labels_offset, 
                            y - graph_dot_radius - x_labels_offset,graph_dot_radius*2,graph_dot_radius*2);
    
    if(i > 0) { // if it's not the first point
      // the future is here, for example
      painter.setPen(QPen(Qt::black,1,Qt::SolidLine, Qt::FlatCap));

      int prev_dot_x = (i-1) * graph_dot_distance;

      painter.drawLine(prev_dot_x + graph_offset_x + y_labels_offset, m_points_y_pos[data[i-1].second] - x_labels_offset,
                        x + graph_offset_x + y_labels_offset,m_points_y_pos[data[i].second] - x_labels_offset);
      painter.setPen(QPen(Qt::black,1,Qt::NoPen, Qt::FlatCap));
    }
  }
  

}
