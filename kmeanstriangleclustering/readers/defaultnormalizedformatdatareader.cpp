#include "defaultnormalizedformatdatareader.h"

#include <QTextStream>
#include <QFile>

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
	int vectors, dimensions, lines;

}
