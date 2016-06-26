#include <stdio.h>
#include <vector>
 
class Feature
{
public:
	enum FeatureType {eUnknown = 0 , eCircle = 3, eTriangle = 6, eSquare = 8};
    Feature(): 
		type(eUnknown)
	{}
 
    ~Feature() 
	{}
 
    bool isValid() { return type != eUnknown;}
 
    bool read(FILE* file)
    {        
	    type = eUnknown;
	    
	    if (file == NULL) {
	        return false;
	    }

        if (fread(&type, sizeof(FeatureType), 1, file) != sizeof(FeatureType)) {
			return false;
		}
		
        short n = 0;
        switch (type) 
        {
        case eCircle: 
			n = 3; 
			break;
        case eTriangle: 
			n = 6; 
			break;
        case eSquare: 
			n = 8; 
			break;
        default: 
			type = eUnknown;
			return false;
        }
		
        points.resize(n);
        
		if (fread(&points[0], sizeof(double), n, file) != n*sizeof(double)) {
			type = eUnknown;
			return false;
		}
		
        return  true;
    }
	
	
	
    void draw()
    {
	
	if ( points.size() != type ) {
		return;
	}	
		
	switch (type)
    {
    case eCircle: 
		drawCircle(points[0], points[1], points[2]); 
		break;
    case eTriangle: 
		drawPolygon(&points[0], 6); 
		break;
    case eSquare: 
		drawPolygon(&points[0], 8); 
		break;
    }
		
		
    }
 
protected:
    void drawCircle(double centerX, double centerY, double radius);
    void drawPolygon(double* points, int size);
    
	std::vector<double> points;
    FeatureType type;        
};
 
int main(int argc, char* argv[])
{
    Feature feature;
    FILE* file = fopen("features.dat", "r");
    feature.read(file);
    if (!feature.isValid())
        return 1;
    return 0;
}
