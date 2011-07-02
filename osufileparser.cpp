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
    //
    // example of spinner data:
    //   256,192,21409,12,0,23025
    //   [x],[y],[time],[color],??,[duration]
    QStringList hit_point_list = spinner_string.split(",");

    HitPointDetails hit_positions;
    hit_positions.type = 4;
    hit_positions.x = QString(hit_point_list.at(0).toLocal8Bit().data()).toInt();
    hit_positions.y = QString(hit_point_list.at(1).toLocal8Bit().data()).toInt();
    hit_positions.time = QString(hit_point_list.at(2).toLocal8Bit().data()).toInt();
    hit_positions.duration = QString(hit_point_list.at(5).toLocal8Bit().data()).toInt();

    hit_marks_.push_back(hit_positions);
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
    //
    // examples of slider data:
    //   304,224,58186,2,0,B|344:248|384:224,4,80,0|2|0|2|0
    //   [x],[y],[time],[color],??,B|[extra_points?, defined as x:y],[repetitions],[duration],??
    QStringList hit_point_list = slider_string.split(",");

    // beginning of slider
    HitPointDetails hit_positions;
    hit_positions.type = 2;
    hit_positions.x = QString(hit_point_list.at(0)).toInt();
    hit_positions.y = QString(hit_point_list.at(1)).toInt();
    hit_positions.time = QString(hit_point_list.at(2)).toInt();
    hit_positions.duration = 0;
    hit_marks_.push_back(hit_positions);

    QStringList inner_hit_point_list = QString(hit_point_list.at(5)).split("|");

    for (int i = 1; i < inner_hit_point_list.size(); ++i)
    {
        //first one is goning to be "B", so let's skip it, and others are defined as x:y
        QStringList inner_list_coordinates = QString(inner_hit_point_list.at(i)).split(":");
        HitPointDetails inner_positions;

        inner_positions.type = 0;
        inner_positions.x = QString(inner_list_coordinates.at(0)).toInt();
        inner_positions.y = QString(inner_list_coordinates.at(1)).toInt();
        inner_positions.time = 50;
        inner_positions.duration = 0;

        hit_marks_.push_back(inner_positions);

        //qDebug() << inner_positions.type << " x:" << inner_positions.x << " y:" << inner_positions.y << " time:" << inner_positions.time;

    }
}

void OsuFileParser::AddHitPoint(QString hit_point_string)
{
    // array indicates:
    //   [0]: it's a hit point (= 1)
    //   [1]: x
    //   [2]: y
    //   [3]: initialization time
    //
    // examples of hitPoint data:
    //   128,192,7735,1,0
    //   [x],[y],[time],[color],??
    QStringList hit_point_list = hit_point_string.split(",");

    HitPointDetails hit_positions;
    hit_positions.type = 1;
    hit_positions.x = QString(hit_point_list.at(0).toLocal8Bit().data()).toInt();
    hit_positions.y = QString(hit_point_list.at(1).toLocal8Bit().data()).toInt();
    hit_positions.time = QString(hit_point_list.at(2).toLocal8Bit().data()).toInt();
    hit_positions.duration = 0;

    hit_marks_.push_back(hit_positions);
}
void OsuFileParser::TraceVector()
{
    for (std::vector<HitPointDetails>::iterator it = hit_marks_.begin(); it < hit_marks_.end(); ++it)
    {
        qDebug() << (*it).type << " x:" << (*it).x << " y:" << (*it).y << " time:" << (*it).time;
    }
}
