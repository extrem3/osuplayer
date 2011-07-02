#ifndef OSUFILEPARSER_H
#define OSUFILEPARSER_H

#include <QDebug>
#include <vector>
#include <QString>
#include <QStringList>

class OsuFileParser
{
    std::vector< std::vector<int> > hit_marks_;
public:
    OsuFileParser(QString file_name);
    void AddHitPoint(QString hit_point_string);
    void AddSlider(QString slider_string);
    void AddSpinner(QString spinner_string);
};

#endif // OSUFILEPARSER_H
