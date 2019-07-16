#ifndef ANGLE_H
#define ANGLE_H
#include <QString>
#include <QtMath>
#include <QVector3D>

class PointsVectors {
public:
    QVector3D x_axis,y_axis,z_axis;
    QVector3D entry,cannula;
    std::vector<QVector3D> targets;

public:
    void calculate_new_targets(QVector3D target_point,QVector3D &nTP)
    {
        nTP.setX(QVector3D::dotProduct(operator-(target_point,entry),x_axis));//target in FrameCS; target - entry;
        nTP.setY(QVector3D::dotProduct(operator-(target_point,entry),y_axis));
        nTP.setZ(QVector3D::dotProduct(operator-(target_point,entry),z_axis));

    }

public:
    void calculate_new_cannula(QVector3D cannula,QVector3D &nC)
    {
        nC.setX(QVector3D::dotProduct(operator-(entry,cannula),x_axis));//cannula in FrameCS; oppsite direction  entry-cannula;
        nC.setY(QVector3D::dotProduct(operator-(entry,cannula),y_axis));
        nC.setZ(QVector3D::dotProduct(operator-(entry,cannula),z_axis));

    }

public:
    std::vector<QString> calculate_point_angle(QVector3D point_1, QVector3D point_2)
    {
        std::vector<QString> rotate_angle;

        double pitch_1 = qAtan(point_1.x()/point_1.y());
        double distance_1 = qSqrt(qPow(point_1.x(),2)+qPow(point_1.y(),2));
        double roll_1 = qAtan(point_1.z()/distance_1);

        double pitch_2 = qAtan(point_2.x()/point_2.y());
        double distance_2 = qSqrt(qPow(point_2.x(),2)+qPow(point_2.y(),2));
        double roll_2 = qAtan(point_2.z()/distance_2);

        double pitch_1to2 = pitch_2 - pitch_1;
        double roll_1to2 = roll_2 - roll_1;

//        float a =  qAtan(tan(M_PI/4))*180/M_PI;
//        float b =  qAtan(tan(M_PI/3))*180/M_PI;
        rotate_angle.push_back(QString::number(pitch_1to2*180/M_PI));
        rotate_angle.push_back(QString::number(roll_1to2*180/M_PI));

        return rotate_angle;
    }
};

#endif // ANGLE_H

