#include "osufileparser.h"

OsuFileParser::OsuFileParser(QString file_name)
{
    ParseFile(file_name);
}
void OsuFileParser::ParseFile(QString file_name)
{
    bool hit_points_found = false;
    QFile file(file_name);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    QString line = in.readLine();
    while (!line.isNull()) {
        switch (DetermineLineType(line, hit_points_found))
        {
            case 5:
                hit_points_found = true;
                break;
            case 1:
                AddHitPoint(line);
                break;
            case 2:
                AddSlider(line);
                break;
            case 4:
                AddSpinner(line);
                break;
        }
        line = in.readLine();
    }
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

    hit_marks_.push_back(hit_positions);

    //now to indicate we can release it
    hit_positions.type = 3;
    hit_positions.time = QString(hit_point_list.at(5).toLocal8Bit().data()).toInt();

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
    hit_marks_.push_back(hit_positions);

    QStringList inner_hit_point_list = QString(hit_point_list.at(5)).split("|");
    HitPointDetails inner_positions;

    for (int i = 1; i < inner_hit_point_list.size(); ++i)
    {
        //first one is goning to be "B", so let's skip it, and others are defined as x:y
        QStringList inner_list_coordinates = QString(inner_hit_point_list.at(i)).split(":");

        if (i == inner_hit_point_list.size() - 1)
        {
            inner_positions.type = 3;
        }else
        {
            inner_positions.type = 0;
        }
        inner_positions.x = QString(inner_list_coordinates.at(0)).toInt();
        inner_positions.y = QString(inner_list_coordinates.at(1)).toInt();
        inner_positions.time = 50;

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

    hit_marks_.push_back(hit_positions);
}
void OsuFileParser::TraceVector()
{
    for (std::vector<HitPointDetails>::iterator it = hit_marks_.begin(); it < hit_marks_.end(); ++it)
    {
        qDebug() << (*it).type << " x:" << (*it).x << " y:" << (*it).y << " time:" << (*it).time;
    }
}

int OsuFileParser::DetermineLineType(QString line, bool hit_points_section_found)
{
    if (hit_points_section_found == false)
    {
        if (line == "[HitObjects]")
        {
            return 5;
        }
    }else
    {
        if (line.contains("|"))
        {
            //its a slider
            return 2;
        }
        if (line.count(",") == 5)
        {
            //its a spinner
            return 4;
        }
        //else its a hit_point
        return 1;
    }
    return 0;
}
