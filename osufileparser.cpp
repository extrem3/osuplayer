#include "osufileparser.h"
#include <QDebug>

OsuFileParser::OsuFileParser(QString file_name)
{

}

void OsuFileParser::AddSpinner(QString spinner_string)
{
    // array indicates:
    //   [0]: it's a spinner (= 4)
    //   [1]: initialization time
    //   [2]: x
    //   [3]: y
}

void OsuFileParser::AddSlider(QString slider_string)
{
    // array indicates:
    //   [0]: it's a slider (= 2)
    //   [1]: initialization time
    //   [2]: x
    //   [3]: y
    // slider then calls MousePress, until you hit [0] = 3
    //   and then it calls MouseRelease
    // until then, arrays are structured as:
    //   [0]: it's a slider continuation (= 0)
    //   [1]: when to hover it
    //   [2]: x
    //   [3]: y
}

void OsuFileParser::AddHitPoint(QString hit_point_string)
{
    // array indicates:
    //   [0]: it's a hit point (= 1)
    //   [1]: x
    //   [2]: y
    //   [3]: initialization time
    QStringList hit_point_list = hit_point_string.split(",");

    std::vector<int> hit_positions;
    hit_positions.push_back(1);
    for (int i = 0; i < hit_point_list.size(); ++i)
    {
        int get_number = QString(hit_point_list.at(i).toLocal8Bit().data()).toInt();
        qDebug() << get_number;
        hit_positions.push_back(get_number);
    }
    hit_marks_.push_back(hit_positions);
}
