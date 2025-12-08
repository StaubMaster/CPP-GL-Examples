


struct Point2D;



float Normal0ToPixel(float val, float size);
float PixelToNormal0(float val, float size);
float Normal0ToNormal1(float val);
float Normal1ToNormal0(float val);



Point2D Normal0ToPixel(Point2D p, Point2D size);
Point2D PixelToNormal0(Point2D p, Point2D size);
Point2D Normal0ToNormal1(Point2D p);
Point2D Normal1ToNormal0(Point2D p);


