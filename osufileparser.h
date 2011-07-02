#ifndef OSUFILEPARSER_H
#define OSUFILEPARSER_H

#include <QDebug>
#include <vector>
#include <QString>
#include <QStringList>
#include <QFile>

struct HitPointDetails
{
    int type;
    int x;
    int y;
    int time;
};

class OsuFileParser
{
public:
    OsuFileParser();
    void ParseFile(QString file_name);
    std::vector<HitPointDetails> GetParsedFile();
    void TraceVector(std::vector<HitPointDetails> song);
private:
    std::vector< HitPointDetails > hit_marks_;
    void AddHitPoint(QString hit_point_string);
    void AddSlider(QString slider_string);
    void AddSpinner(QString spinner_string);
    int DetermineLineType(QString line, bool hit_points_section_found);
};

#endif // OSUFILEPARSER_H
