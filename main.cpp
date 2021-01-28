// Basé sur :
// CC-BY Edouard.Thiel@univ-amu.fr - 22/01/2019

#include "princ.h"
#include <QApplication>
#include <CGAL/Simple_cartesian.h>

typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Point_2 Point_2;
typedef Kernel::Segment_2 Segment_2;

int main(int argc, char *argv[])
{

    Point_2 p(1,1), q(10,10);
      std::cout << "p = " << p << std::endl;
      qDebug() << "q = " << q.x() << " " << q.y();
      qDebug() << "sqdist(p,q) = "
                << CGAL::squared_distance(p,q) ;
      Segment_2 s(p,q);
      Point_2 m(5, 9);
      std::cout << "m = " << m << std::endl;
      qDebug() << "sqdist(Segment_2(p,q), m) = "
                << CGAL::squared_distance(s,m);
      qDebug() << "p, q, and m ";
      switch (CGAL::orientation(p,q,m)){
      case CGAL::COLLINEAR:
        qDebug() << "are collinear\n";
        break;
      case CGAL::LEFT_TURN:
        qDebug() << "make a left turn\n";
        break;
      case CGAL::RIGHT_TURN:
        qDebug() << "make a right turn\n";
        break;
      }
      std::cout << " midpoint(p,q) = " << CGAL::midpoint(p,q) << std::endl;

    QApplication a(argc, argv);
    Princ w;
    w.show();

    return a.exec();
}
