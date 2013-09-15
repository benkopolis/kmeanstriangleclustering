#include "defaultnormalizedformatdatareader.h"


#include <QTextStream>
#include <QFile>

#include "spaces/normalizedpointsspace.h"

DefaultNormalizedFormatDataReader::DefaultNormalizedFormatDataReader()
{
}

AbstractPointsSpace* DefaultNormalizedFormatDataReader::readPointSpaceFromFile(QString fileName, AbstractPointsSpace* container)
{
	if(container == 0)
	{
		QTextStream err(stderr);
		err << "Can not open file for reading: " << fileName;
		return 0;
	}
	QFile file(fileName);
	QTextStream *in;
	if(file.open(QFile::ReadOnly))
		in = new QTextStream(&file);
	else
	{
		QTextStream err(stderr);
		err << "Can not open file for reading: " << fileName;
		return 0;
	}
    NormalizedPointsSpace * space = new NormalizedPointsSpace();
    PointId pointIndex = 0;
    unsigned int coordtIndex = 0;
    unsigned int numP=0, numD=0;
    *in >> numP >> numD;
    space->setNumberOfDimensions(numD);
    space->setNumberOfPoints(numP);
    Coord c = 0.0;
    char separator;
    while(!in->atEnd())
    {
        QString line = in->readLine();
        QTextStream line_in(&line);
        Point p;
        while(!line_in.atEnd())
        {
            line_in >> coordtIndex >> separator >> c;
            if(!p.contains(coordtIndex))
                p.insert(coordtIndex, c);
        }
        space->insertPoint(p, pointIndex);
        ++pointIndex;
    }
}
